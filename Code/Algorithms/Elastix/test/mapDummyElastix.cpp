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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Elastix/test/mapDummyElastix.cpp $
*/

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "mapString.h"
#include "mapFileDispatch.h"

int main(int argc, char *argv[])
{
	std::cout << "MatchPoint Elastix testing dummy." << std::endl << "This is a mock up exe, used by MatchPoint to test its Elastix integration." << std::endl << std::endl;

	std::cout << "Passed command line arguments:" << std::endl;

	std::ofstream file;
	std::ios_base::openmode iOpenFlag = std::ios_base::out | std::ios_base::trunc;
	file.open("elastixDummyCall.log", iOpenFlag);

	map::core::String outputPath;
	bool nextIsOutput = false;

	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
		file << argv[i] << std::endl;

		if (nextIsOutput)
		{
			outputPath = argv[i];
		}

		nextIsOutput = argv[i] == map::core::String("-out");
	}

	file.close();

	//write dummy result
	file.open(map::core::FileDispatch::createFullPath(outputPath, "TransformParameters.0.txt").c_str(), iOpenFlag);

	file << "//dummy transform result" << std::endl;

	file.close();

	return EXIT_SUCCESS;
}
