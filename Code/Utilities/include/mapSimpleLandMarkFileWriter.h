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
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Utilities/include/mapSimpleLandMarkFileReader.h $
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
		    This function is used for some tests and examples. It asumes the standard itk coordinate system (LPS)
		*/
		template <class TPointSet>
		bool saveLandMarksToFile(const core::String& lmFileName, const TPointSet* pointSet)
		{
      using LandmarksType = TPointSet;

			std::ofstream pointsFile;
			pointsFile.open(lmFileName.c_str());

			typename LandmarksType::Pointer spLMs;

			if (pointsFile.fail())
			{
				return false;
			}

      if (pointSet)
      {
        typename LandmarksType::PointType point;

        spLMs = LandmarksType::New();
        spLMs->SetPoints(LandmarksType::PointsContainer::New());

        typename LandmarksType::PointsContainer::ConstPointer points = pointSet->GetPoints();
        typename LandmarksType::PointsContainer::ConstIterator pointIterator = points->Begin();
        typename LandmarksType::PointsContainer::ConstIterator end = points->End();
        while (pointIterator != end)
        {
          typename LandmarksType::PointType p = pointIterator.Value();
          for (unsigned int i = 0; i < LandmarksType::PointDimension; ++i)
          {
            if (i > 0)
            {
              pointsFile << " ";
            }
            pointsFile << p[i];
          }
          pointsFile << std::endl;
          ++pointIterator;
        }
      }

			pointsFile.close();

			return true;
		}

  } //namespace utilities
} //namespace map
