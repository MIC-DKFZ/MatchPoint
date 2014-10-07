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
// @version $Revision: 303 $ (last changed revision)
// @date    $Date: 2013-09-19 18:06:33 +0200 (Do, 19 Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Core/include/mapSDStreamingInterface.h $
*/



#ifndef __MAP_SD_ITK_STREAMING_HELPER_H
#define __MAP_SD_ITK_STREAMING_HELPER_H

#include "itkMatrix.h"
#include "mapSDElement.h"

namespace map
{

  namespace tags
  {
    const char* const Value = "Value";
    const char* const Column = "Column";
    const char* const Row = "Row";
  }

	namespace structuredData
	{

		/** Helper function that streams an itk::Matrix class into a structured data element.
		* @ingroup SD
		*/
    template<class TMatrix>
  	Element::Pointer streamITKMatrixToSD(const TMatrix& matrix);

		/** Helper function that streams from a structured data element into an itk::Matrix class.
		* @ingroup SD
		*/
    template<class TMatrix>
		TMatrix streamSDToITKMatrix(const Element* pElement);

		/** Helper function that streams an itk::FixedArray (ore derived classes) into a structured data element.
		* @ingroup SD
		*/
    template<class TITKFixedArray>
  	Element::Pointer streamITKFixedArrayToSD(const TITKFixedArray& array);

		/** Helper function that streams from a structured data element into an itk::FixedArray (or derived) class.
		* @ingroup SD
		*/
    template<class TITKFixedArray>
		TITKFixedArray streamSDToITKFixedArray(const Element* pElement);

	} //end of namespace structuredData

} //end of namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapSDITKStreamingHelper.tpp"
#endif

#endif
