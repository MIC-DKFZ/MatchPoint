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
 * Demo: demoHelloWorldDeployment1
 * Topics:
 * - How to use a deployed boxed algorithm via DLL?
 *
 * In the first hello world deployment example it is shown how
 * to load a specific deployed and boxed algorithm from a
 * DLL, set the moving an target image via the right
 * facet (ImageRegistrationAlgorithmInterface) and then
 * calculate the registration. Afterwards the moving image
 * will be registered with a appropriated task.
 * The outcome and used algorithm is the very same like
 * demoHelloWorldRegistration2. The differenc is that the later
 * uses static binding to the algorithm (it is integrated
 * in the executable). This example gets the algorithm
 * via DLL at runtime. Thus you may change the used algorithm
 * without changing this demo program by just exchanging the
 * used DLL.
 *********************************************************/

#undef MAP_SEAL_ALGORITHMS

#include "../Algorithms/mapDemoHelloWorldRegistration1Helper.h"

#include "mapImageRegistrationAlgorithmInterface.h"
#include "mapRegistrationAlgorithm.h"
#include "mapImageMappingTask.h"
#include "mapDeploymentDLLAccess.h"

#include "itkDynamicLoader.h"
#include "itksys/SystemTools.hxx"

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
		dllPath = dllPath + "/" + itksys::DynamicLoader::LibPrefix() + "demoRegistrationAlgorithm2D" +
				  itksys::DynamicLoader::LibExtension();

		std::cout << "DLL location: " << dllPath << std::endl;

		map::deployment::DLLHandle::Pointer spHandle = NULL;

		spHandle = map::deployment::openDeploymentDLL(dllPath);

		std::cout << "Algorithm information: " << std::endl;
		spHandle->getAlgorithmUID().Print(std::cout, 2);

		//Now load the algorthm from DLL
		spAlgorithmBase = map::deployment::getRegistrationAlgorithm(spHandle);

		std::cout << "... algorithm is loaded" << std::endl;

		//Now cast to the right interface (ImageRegistrationAlgorithmInterface)
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

	/***************************************************************
	 * Determine registration
	 ***************************************************************/

	std::cout << "Starting to determine the registration..." << std::endl;

	typedef map::algorithm::facet::RegistrationAlgorithmInterface<2, 2> RegistrationAlgorithmType;
	RegistrationAlgorithmType::RegistrationType::Pointer spRegistration;

	try
	{
		RegistrationAlgorithmType* pAlgorithmInterface = dynamic_cast<RegistrationAlgorithmType*>
				(spAlgorithmBase.GetPointer());

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
	 * Map the data by tasks
	 ***************************************************************/

	//define mapping tasks
	std::cout << "Define mapping task..." << std::endl;

	typedef map::core::ImageMappingTask<RegistrationAlgorithmType::RegistrationType, ImageType, ImageType>
	ImageMappingTaskType;

	ImageMappingTaskType::Pointer spImageTask = ImageMappingTaskType::New();
	spImageTask->setInputImage(globals.spMovingImage);
	spImageTask->setRegistration(spRegistration);

	//Process the task
	std::cout << "Process mapping task..." << std::endl;
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
