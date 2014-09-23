// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
// Subversion HeadURL: $HeadURL$
*/

/*!@file
* @ingroup Examples
*********************************************************
* Demo: demoDeploymentPropertiedAlgorithm
* Topics:
* - How to use a deployed boxed algorithm via DLL and its
* MetaProperty interface?
*
* This example is very similar to demoHelloWorldDeployment1.
* The difference is that this time a algorithm is loaded via
* DLL which implements the MetaPropertyInterface. The demo
* will used the interface to access the Properties display them
* and change them.
*********************************************************/

#undef MAP_SEAL_ALGORITHMS

#include "../Algorithms/mapDemoHelloWorldRegistration1Helper.h"

#include "mapImageRegistrationAlgorithmInterface.h"
#include "mapRegistrationAlgorithm.h"
#include "mapImageMappingTask.h"
#include "mapDeploymentDLLAccess.h"
#include "mapMetaProperty.h"
#include "mapMetaPropertyAccessor.h"
#include "mapMetaPropertyAlgorithmInterface.h"

#include "itksys/SystemTools.hxx"
#include "itkDynamicLoader.h"
#include "itkCommand.h"

void onRegistrationEvent(itk::Object* pCaller, const itk::EventObject& e, void*)
{
	const map::events::AlgorithmEvent* pChangeEvent = dynamic_cast<const map::events::AlgorithmEvent*>
			(&e);

	if (pChangeEvent)
	{
		std::cout << std::endl << pChangeEvent->GetEventName() << " (@" << pCaller << "): " <<
				  pChangeEvent->getComment() << std::endl;
	}
}


int determinAndTestRegistration(map::deployment::RegistrationAlgorithmBase* pAlgorithmBase,
								AppGlobals& globals)
{
	/***************************************************************
	* Determine registration
	***************************************************************/
	int result = EXIT_FAILURE;

	std::cout << "Starting to determine the registration..." << std::endl;

	typedef map::algorithm::facet::RegistrationAlgorithmInterface<2, 2> RegistrationAlgorithmType;
	RegistrationAlgorithmType::RegistrationType::Pointer spRegistration;

	try
	{
		RegistrationAlgorithmType* pAlgorithmInterface = dynamic_cast<RegistrationAlgorithmType*>
				(pAlgorithmBase);

		if (!pAlgorithmInterface)
		{
			mapDefaultExceptionStaticMacro("Error. Wrong algorithm seemed to be loaded. Not a 2D-2D algorithm. Check DLL.");
		}

		spRegistration = pAlgorithmInterface->getRegistration();
	}
	catch (const map::core::ExceptionObject& e)
	{
		std::cerr << "ERROR: Caught an MatchPoint exception:\n";
		e.Print(std::cerr);
		std::cerr << "\n";
		throw;
	}

	std::cout << std::endl << "Registration determined..." << std::endl;
	//Thats all. Now we have a registration that map the moving image into the target image
	//space. But the algorithm only delivers the registration as a mapping function between
	//moving and target image space. So the moving image must be mapped...


	/***************************************************************
	* Register the data by tasks
	***************************************************************/

	//define registration tasks
	std::cout << "Define registration task..." << std::endl;

	typedef map::core::ImageMappingTask<RegistrationAlgorithmType::RegistrationType, ImageType, ImageType>
	ImageMappingTaskType;

	ImageMappingTaskType::Pointer spImageTask = ImageMappingTaskType::New();
	spImageTask->setInputImage(globals.spMovingImage);
	spImageTask->setRegistration(spRegistration);

	//Process the task
	std::cout << "Process registration task..." << std::endl;
	spImageTask->execute();


	/***************************************************************
	* Save or test the results
	***************************************************************/

	globals.spResultImage = spImageTask->getResultImage();

	if (globals.doTest)
	{
		result = testResults(globals);
	}
	else
	{
		result = saveResults(globals);
	}

	return result;
}

void showProperties(map::deployment::RegistrationAlgorithmBase* pAlgorithmBase, AppGlobals& globals)
{
	try
	{
		typedef map::algorithm::facet::MetaPropertyAlgorithmInterface PropertyInterfaceType;
		PropertyInterfaceType* pPropertyInterface = dynamic_cast<PropertyInterfaceType*>(pAlgorithmBase);

		if (!pPropertyInterface)
		{
			mapDefaultExceptionStaticMacro("Error. Wrong algorithm seemed to be loaded. No MetaPropertyInterface. Check DLL.");
		}

		std::cout << std::endl << std::endl << "Properties:" << std::endl;
		PropertyInterfaceType::MetaPropertyVectorType infos = pPropertyInterface->getPropertyInfos();

		//go through all properties
		PropertyInterfaceType::MetaPropertyVectorType::iterator pos;

		for (pos = infos.begin(); pos != infos.end(); ++pos)
		{
			//print property information
			(*pos)->Print(std::cout);
			std::cout << std::endl;
		}

		//show number of iterations as on example for value access
		std::cout << std::endl << std::endl << "Retrieve value of the property \"NumberOfIterations\"..." <<
				  std::endl;
		map::core::MetaPropertyBase::Pointer spIterationCount =
			pPropertyInterface->getProperty("NumberOfIterations");
		unsigned long count = 0;

		if (!::map::core::unwrapMetaProperty(spIterationCount, count))
		{
			mapDefaultExceptionStaticMacro("Error. Wrong algorithm seemed to be loaded. No property \"NumberOfIterations\" exists. Check DLL.");
		}

		std::cout << "NumberOfIterations: " << count << std::endl;
	}
	catch (const map::core::ExceptionObject& e)
	{
		std::cerr << "ERROR: Caught an MatchPoint exception:\n";
		e.Print(std::cerr);
		std::cerr << "\n";
		throw e;
	}
}

int main(int argc, char* argv[])
{
	AppGlobals globals;
	int result = EXIT_FAILURE;

	//parse command line arguments
	if (parseArguments(argc, argv, globals) == EXIT_FAILURE)
	{
		std::cerr << "Missing Parameters " << std::endl;
		std::cerr << "Usage: " << argv[0];
		std::cerr << " <targetImage> <movingImage>";
		std::cerr << " [[<resultImage>]";
		std::cerr << " |[-test <referenceImage> <imageCheckThreshold> ";
		std::cerr << " <lmCheckThreshold> <testFilePattern>]]" << std::endl;
		return EXIT_FAILURE;
	}

	//load image and landmark files
	std::cout << "Load images..." << std::endl;

	if (loadData(globals) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}


	/***************************************************************
	* Load and prepare registration algorithm
	***************************************************************/

	map::deployment::RegistrationAlgorithmBasePointer spAlgorithmBase = NULL;

	try
	{
		std::cout << "Load registration algorithm..." << std::endl;

		std::string dllPath = itksys::SystemTools::GetProgramPath(argv[0]);
    dllPath = dllPath + "/" + itksys::DynamicLoader::LibPrefix() + "demoPropertiedAlgorithm2D" + map::deployment::getDeploymentDLLExtension();

		std::cout << "DLL location: " << dllPath << std::endl;

		map::deployment::DLLHandle::Pointer spHandle = NULL;

		spHandle = map::deployment::openDeploymentDLL(dllPath);

		std::cout << "Algorithm information: " << std::endl;
		spHandle->getAlgorithmUID().Print(std::cout, 2);

		//Now load the algorthm from DLL
		spAlgorithmBase = map::deployment::getRegistrationAlgorithm(spHandle);

		std::cout << "... algorithm is loaded" << std::endl;

		//Now cast to the right interface (ImageRegistrationAlgorithmBase)
		//to set the images
		typedef map::algorithm::facet::ImageRegistrationAlgorithmInterface<ImageType, ImageType>
		ImageRegistrationAlgorithmInterfaceType;
		ImageRegistrationAlgorithmInterfaceType* pImageInterface =
			dynamic_cast<ImageRegistrationAlgorithmInterfaceType*>(spAlgorithmBase.GetPointer());

		if (pImageInterface)
		{
			//Finally we set moving and target image for that should be
			//used by the image based registration algorithm
			pImageInterface->setMovingImage(globals.spMovingImage);
			pImageInterface->setTargetImage(globals.spTargetImage);
		}
		else
		{
			mapDefaultExceptionStaticMacro("Error. Wrong algorithm seemed to be loaded. Image Registration interface is missing. Check DLL.");
		}

		//The algorithm is set up and ready to run...
	}
	catch (const map::core::ExceptionObject& e)
	{
		std::cerr << "ERROR: Caught an MatchPoint exception:\n";
		e.Print(std::cerr);
		std::cerr << "\n";
		throw;
	}

	//Add observer for algorithm events.
	::itk::CStyleCommand::Pointer spRegCommand = itk::CStyleCommand::New();
	spRegCommand->SetCallback(&onRegistrationEvent);

	spAlgorithmBase->AddObserver(map::events::AlgorithmEvent(), spRegCommand);

	/***************************************************************
	* Show properties
	***************************************************************/
	std::cout << "Show the properties of the algorithm directly loaded from DLL and bevor usage..." <<
			  std::endl;
	showProperties(spAlgorithmBase, globals);

	/***************************************************************
	* Determine registration
	***************************************************************/
	result = determinAndTestRegistration(spAlgorithmBase, globals);

	/***************************************************************
	* Change number of iterations
	***************************************************************/
	std::cout << "Now we change the number of iterations via a meta property..." << std::endl;

	try
	{
		typedef map::algorithm::facet::MetaPropertyAlgorithmInterface PropertyInterfaceType;
		PropertyInterfaceType* pPropertyInterface = dynamic_cast<PropertyInterfaceType*>
				(spAlgorithmBase.GetPointer());

		if (!pPropertyInterface)
		{
			mapDefaultExceptionStaticMacro("Error. Wrong algorithm seemed to be loaded. No MetaPropertyInterface. Check DLL.");
		}

		//show number of iterations as on example for value access
		map::core::MetaPropertyBase::Pointer spIterationCount = map::core::MetaProperty<unsigned long>::New(
					1).GetPointer();
		pPropertyInterface->setProperty("NumberOfIterations", spIterationCount);
	}
	catch (map::core::ExceptionObject& e)
	{
		std::cerr << "ERROR: Caught an MatchPoint exception:\n";
		e.Print(std::cerr);
		std::cerr << "\n";
		throw;
	}

	/***************************************************************
	* Show properties
	***************************************************************/
	std::cout << "Show the properties of the algorithm after the change..." << std::endl;
	showProperties(spAlgorithmBase, globals);

	/***************************************************************
	* Determine registration
	***************************************************************/
	int tempResult = EXIT_FAILURE;

	std::cout << std::endl << std::endl <<
			  "Now compute the registration again. This time it should fail, due to the new number of iterations (not enough to converge to a proper result). ..."
			  << std::endl;
	globals.testShouldFail = true;
	tempResult = determinAndTestRegistration(spAlgorithmBase, globals);

	if (tempResult == EXIT_FAILURE)
	{
		//the second registration should have failed due to the new iteration count!
		result = EXIT_FAILURE;
	}


	return result;
}
