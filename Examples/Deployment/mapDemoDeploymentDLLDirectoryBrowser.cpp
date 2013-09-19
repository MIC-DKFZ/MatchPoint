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

/*********************************************************
 * Demo: demoDeploymentDLLDirectoryBrowser
 * Topics:
 * - How to use the map::deployment::DLLDirectoryBrowser?
 * - How to get feedback about the browsing status (valid
 *   and invalid DLLs that have been found)?
 * - How to use the deployment events to observe the browsing?
 *
 * In this example a map::deployment::DLLDirectoryBrowser
 * instance will be used to search for DLLs and the instance
 * will be connected to events to stream the search status
 * directly onto the console.\n
 * You may pass additional arguments that will be used as
 * search paths
 *********************************************************/

#undef MAP_SEAL_ALGORITHMS

#include "mapDeploymentDLLDirectoryBrowser.h"
#include "mapString.h"
#include "mapDeploymentEvents.h"

#include "itksys/SystemTools.hxx"
#include "itkCommand.h"

void onValidDLLFound(const itk::Object* pCaller, const itk::EventObject& e, void*)
{
	const map::events::DeploymentEvent* pFoundEvent = dynamic_cast<const map::events::DeploymentEvent*>
			(&e);

	if (pFoundEvent)
	{
		std::cout << std::endl << "+ " << pFoundEvent->getComment() << std::endl;
	}
}

void onInvalidDLLFound(const itk::Object* pCaller, const itk::EventObject& e, void*)
{
	const map::events::DeploymentEvent* pFoundEvent = dynamic_cast<const map::events::DeploymentEvent*>
			(&e);

	if (pFoundEvent)
	{
		std::cout << std::endl << "- " << pFoundEvent->getComment() << std::endl;
	}
}

int main(int argc, char* argv[])
{
	int result = EXIT_SUCCESS;

	map::deployment::DLLDirectoryBrowser::Pointer spBrowser =
		map::deployment::DLLDirectoryBrowser::New();

	/***************************************************************
	 * Set the search paths
	 ***************************************************************/

	//parse command line arguments
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			spBrowser->addDLLSearchLocation(argv[i]);
		}
	}
	else
	{
		//use path of the application as search path
		map::core::String searchPath = itksys::SystemTools::GetProgramPath(argv[0]);
		spBrowser->addDLLSearchLocation(searchPath);
	}


	/***************************************************************
	 * Add observers for deployment events
	 ***************************************************************/
	itk::CStyleCommand::Pointer spValidCommand = itk::CStyleCommand::New();
	spValidCommand->SetConstCallback(&onValidDLLFound);
	spBrowser->AddObserver(map::events::ValidDLLEvent(), spValidCommand);

	itk::CStyleCommand::Pointer spInvalidCommand = itk::CStyleCommand::New();
	spInvalidCommand->SetConstCallback(&onInvalidDLLFound);
	spBrowser->AddObserver(map::events::InvalidDLLEvent(), spInvalidCommand);

	/***************************************************************
	 * Browes for algorithm DLLs
	 ***************************************************************/

	std::cout << "Search for DLLs..." << std::endl << std::endl;

	spBrowser->update();

	std::cout << std::endl << std::endl << "... search done" << std::endl << std::endl;

	/***************************************************************
	 * Display the results
	 ***************************************************************/

	return result;
}