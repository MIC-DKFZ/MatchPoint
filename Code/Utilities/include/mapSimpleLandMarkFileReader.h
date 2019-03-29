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
		typename TPointSet::Pointer loadLandMarksFromFile(const core::String& lmFileName)
		{
			using LandmarksType = TPointSet;

			std::ifstream pointsFile;
			pointsFile.open(lmFileName.c_str());

			typename LandmarksType::Pointer spLMs = nullptr;

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
