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
#include "mapExceptionObjectMacros.h"

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
  	Element::Pointer streamITKMatrixToSD(const TMatrix& matrix)
    {
      structuredData::Element::Pointer spMatrixElement = structuredData::Element::New();

      spMatrixElement->setTag("Matrix");

      for (unsigned int rowID = 0; rowID < TMatrix::RowDimensions; ++rowID)
      {
        for (unsigned int colID = 0; colID < TMatrix::ColumnDimensions; ++colID)
        {
          structuredData::Element::Pointer spValueElement = structuredData::Element::New();
          spValueElement->setTag(tags::Value);
          spValueElement->setValue(core::convert::toStr(matrix(rowID, colID)));
          spValueElement->setAttribute(tags::Column, core::convert::toStr(colID));
          spValueElement->setAttribute(tags::Row, core::convert::toStr(rowID));
          spMatrixElement->addSubElement(spValueElement);
        }
      }

      return spMatrixElement;
    };

		/** Helper function that streams from a structured data element into an itk::Matrix class.
		* @ingroup SD
		*/
    template<class TMatrix>
		TMatrix streamSDToITKMatrix(const Element* pElement)
    {
      assert(pElement);
      if (!pElement)
      {
        mapDefaultExceptionStaticMacro( << "Cannot convert structured data into itk matrix. Structured element is missing.");
      }

      if (pElement->getSubElementsCount() != TMatrix::RowDimensions * TMatrix::ColumnDimensions)
      {
        mapDefaultExceptionStaticMacro( << "Error: convert structured data into itk matrix. Reason: matrix has wrong number of elements. Expected: " <<
          TMatrix::RowDimensions * TMatrix::ColumnDimensions << "; found: " << pElement->getSubElementsCount());
      }

      TMatrix matrix;

      for (structuredData::Element::ConstSubElementIteratorType pos = pElement->getSubElementBegin();
        pos != pElement->getSubElementEnd(); ++pos)
      {
        if ((*pos)->getTag() != tags::Value)
        {
          mapDefaultExceptionStaticMacro( << "Error: convert structured data into itk matrix. Reason: contains wrong sub elements, only \"Value\" os allowed. Wrong sub element tag: " << (*pos)->getTag());
        }

        unsigned int rowID = core::convert::toUInt((*pos)->getAttribute(tags::Row));
        unsigned int colID = core::convert::toUInt((*pos)->getAttribute(tags::Column));

        matrix(rowID, colID) = core::convert::toValueGeneric<typename TMatrix::ValueType>((*pos)->getValue());
      }

      return matrix;
    };


		/** Helper function that streams an itk::FixedArray (ore derived classes) into a structured data element.
		* @ingroup SD
		*/
    template<class TITKFixedArray>
  	Element::Pointer streamITKFixedArrayToSD(const TITKFixedArray& array)
    {
      structuredData::Element::Pointer spArrayElement = structuredData::Element::New();
      spArrayElement->setTag("FixedArray");

      for (unsigned int rowID = 0; rowID < TITKFixedArray::Dimension; ++rowID)
      {
        structuredData::Element::Pointer spValueElement = structuredData::Element::New();
        spValueElement->setTag(tags::Value);
        spValueElement->setValue(core::convert::toStr(array[rowID]));
        spValueElement->setAttribute(tags::Row, core::convert::toStr(rowID));
        spArrayElement->addSubElement(spValueElement);
      }

      return spArrayElement;
    };

		/** Helper function that streams from a structured data element into an itk::FixedArray (or derived) class.
		* @ingroup SD
		*/
    template<class TITKFixedArray>
		TITKFixedArray streamSDToITKFixedArray(const Element* pElement)
    {
      assert(pElement);
      if (!pElement)
      {
        mapDefaultExceptionStaticMacro( << "Cannot convert structured data into itk fixed array. Structured element is missing.");
      }

      if (pElement->getSubElementsCount() != TITKFixedArray::Dimension)
      {
        mapDefaultExceptionStaticMacro( << "Error: convert structured data into itk fixed array. Reason: matrix has wrong number of elements. Expected: " <<
          TITKFixedArray::Dimension << "; found: " << pElement->getSubElementsCount());
      }

      TITKFixedArray fixedArray;

      for (structuredData::Element::ConstSubElementIteratorType pos = pElement->getSubElementBegin();
        pos != pElement->getSubElementEnd(); ++pos)
      {
        unsigned int rowID = core::convert::toUInt((*pos)->getAttribute(tags::Row));

        fixedArray[rowID] = core::convert::toValueGeneric<typename TITKFixedArray::ValueType>((*pos)->getValue());
      }

      return fixedArray;
    };


	} //end of namespace structuredData

} //end of namespace map
#endif
