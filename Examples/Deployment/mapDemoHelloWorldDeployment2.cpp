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
 * Demo: demoHelloWorldDeployment2
 * Topics:
 * - How to search for a deployed algorithm?
 *
 * In the second example a simple way is demonstrated to
 * search for valid deployment DLLs if you want to allow
 * a host application to select algortihms at runtime.
 *********************************************************/

#undef MAP_SEAL_ALGORITHMS

#include "mapDeploymentDLLDirectoryBrowser.h"
#include "mapString.h"

#include "itksys/SystemTools.hxx"


int main(int argc, char* argv[])
{
	int result = EXIT_SUCCESS;
	map::core::String searchPath = "";


	//parse command line arguments
	if (argc > 1)
	{
		searchPath = argv[1];
	}
	else
	{
		//use path of the application as search path
		searchPath = itksys::SystemTools::GetProgramPath(argv[0]);
	}


	/***************************************************************
	 * Browes for algorithm DLLs
	 ***************************************************************/

	std::cout << "Search for DLLs..." << std::endl;
	std::cout << "Search location: " << searchPath << std::endl;

	map::deployment::DLLInfoListType list = map::deployment::peekDeploymentDLLDirectory(searchPath);

	//that's it! Now we just have to dieplay the results
	std::cout << "... search done" << std::endl << std::endl;

	/***************************************************************
	 * Display the results
	 ***************************************************************/

	std::cout << "Found DLLs: " << std::endl;
	map::deployment::DLLInfoListType::iterator pos;

	for (pos = list.begin(); pos != list.end(); ++pos)
	{
		std::cout << "- " << (*pos)->getLibraryFilePath() << std::endl;
		std::cout << "  UID: " << (*pos)->getAlgorithmUID().toStr() << std::endl << std::endl;
	}

	return result;
}