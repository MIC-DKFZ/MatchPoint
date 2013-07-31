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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/FSL/test/mapDummyFlirt.cpp $
*/

#include "mapString.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	std::cout << "MatchPoint FLIRT testing dummy." << std::endl << "This is a mock up exe, used by MatchPoint to test its FSLRegistrationAlgorithm implementation." << std::endl << std::endl;

	std::cout << "Passed command line arguments:" << std::endl;

	std::ofstream file;
	std::ios_base::openmode iOpenFlag = std::ios_base::out | std::ios_base::trunc;
	file.open("flirtDummyCall.log", iOpenFlag);

	map::core::String matFile;
	bool nextIsMatFile = false;
	bool is2D = false;

	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
		file << argv[i] << std::endl;

		if (nextIsMatFile)
		{
			matFile = argv[i];
		}

		nextIsMatFile = argv[i] == map::core::String("-omat");

		if (argv[i] == map::core::String("-2D"))
		{
			is2D = true;
		}
	}

	file.close();

	file.open(matFile.c_str(), iOpenFlag);

	if (is2D)
	{
		file << "1  0  -53.8016" << std::endl;
		file << "0  1  -1.44441" << std::endl;
		file << "0  0  1" << std::endl;
	}
	else
	{
		file << "1.0574  0.0110152  0.120938  -53.8016" << std::endl;
		file << "-0.0184141  0.99621  -0.0121487  -1.44441" << std::endl;
		file << "-0.126757  -0.0109658  1.10909  30.7287" << std::endl;
		file << "0  0  0  1" << std::endl;
	}

	file.close();

	return EXIT_SUCCESS;
}
