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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Utilities/include/mapSimpleLandMarkFileReader.h $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapString.h"
#include <fstream>

namespace map
{
	namespace utilities
	{
		/** Loads a simple land mark file (one land mark per line, values of a landmark seperated by space) into the point set type.
		    This function is used for some tests and examples.
		*/

		template <class TPointSet>
		typename TPointSet::Pointer loadLandMarksFromFile(const core::String &lmFileName)
		{
			typedef TPointSet LandmarksType;

			std::ifstream pointsFile;
			pointsFile.open(lmFileName.c_str());

			typename LandmarksType::Pointer spLMs = NULL;

			if (pointsFile.fail())
			{
				return spLMs;
			}

			typename LandmarksType::PointType point;

			spLMs = LandmarksType::New();
			spLMs->SetPoints(LandmarksType::PointsContainer::New());

			unsigned int pointId = 0;

			pointsFile >> point;

			while (!pointsFile.fail())
			{
				spLMs->SetPoint(pointId, point);
				pointId++;

				pointsFile >> point;
			}

			pointsFile.close();

			return spLMs;
		}
	} //namespace utilities
} //namespace map
