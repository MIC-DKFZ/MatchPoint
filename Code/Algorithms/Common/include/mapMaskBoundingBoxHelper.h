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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/Common/include/mapMaskedRegistrationAlgorithmInterface.h $
*/




#ifndef __MASK_BOUNDING_BOX_HELPER_H
#define __MASK_BOUNDING_BOX_HELPER_H

#include "itkIndent.h"
#include "itkSpatialObject.h"
#include "itkImageBase.h"

#include "mapExceptionObjectMacros.h"

namespace map
{
  namespace algorithm
  {

    template<unsigned int VDimension>
    class MaskBoundingBoxHelper
    {
    public:
      typedef MaskBoundingBoxHelper<VDimension> Self;

      typedef ::itk::SpatialObject<VDimension> MaskBaseType;
      typedef ::itk::ImageBase<VDimension> ImageBaseType;
      typedef typename ImageBaseType::RegionType ImageRegionType;
      typedef typename ImageBaseType::PointType PointType;

    public:

      /*! @brief computes the image region for an given image (geometry) which guarantees to cover the bounding box of the passed mask.
      It is not guaranteed that the returned bounding box is within the largest possible or buffered region of the image. Thus using the returning
      region you can be sure that any inside point of the mask is within the region (and has a pixel correspondence, if it is also covered by the
      largest possible region).
      @pre mask must be a valid pointer
      @pre refImage must be a valid pointer
      @eguarante strong
      @param [in] mask Pointer to the mask object.
      @param [in] refImage Pointer to the image on which geomtry the bounding region should be computed
      @oaram [out] boundingRegion The computed bounding image region.
      @return Indicates if boundingRegion has a valid value.
      */
      static bool computeBoundingImageRegion(const MaskBaseType* mask, const ImageBaseType* refImage, ImageRegionType& boundingRegion)
      {
        ImageRegionType resultRegion;
        bool result = false;

        if (!mask)
        {
          mapDefaultExceptionStaticMacro(<<"Cannot compute bounding box. Mask pointer is Null.");
        }
        if (!refImage)
        {
          mapDefaultExceptionStaticMacro(<<"Cannot compute bounding box. Reference image pointer is Null.");
        }

        if (mask->ComputeBoundingBox())
        {
          //there is really a bounding box
          typename MaskBaseType::BoundingBoxType::Pointer spBBox = mask->GetBoundingBox();
          const typename MaskBaseType::BoundingBoxType::PointsContainer* cornerPoints = spBBox->GetCorners();

          typename ImageBaseType::IndexType minIndex;
          minIndex.Fill(::itk::NumericTraits<typename ImageBaseType::IndexType::IndexValueType>::max());
          typename ImageBaseType::IndexType maxIndex;
          maxIndex.Fill(::itk::NumericTraits<typename ImageBaseType::IndexType::IndexValueType>::NonpositiveMin());

          for (typename MaskBaseType::BoundingBoxType::PointsContainer::ConstIterator pos = cornerPoints->Begin(); pos != cornerPoints->End(); ++pos)
          {
            typename ImageBaseType::IndexType index;
            typename ImageBaseType::PointType point = pos.Value();

            refImage->TransformPhysicalPointToIndex(point, index);

            for (unsigned int i = 0; i < ImageBaseType::GetImageDimension(); ++i)
            {
              if (index[i] < minIndex[i])
              {
                minIndex[i] = index[i];
              };
              if (index[i] > maxIndex[i])
              {
                maxIndex[i] = index[i];
              };
            }

          }

          resultRegion.SetIndex(minIndex);
          resultRegion.SetUpperIndex(maxIndex);
          boundingRegion = resultRegion;
          result = true;
        }

        return result;
      };

    protected:
      /*! @brief virtual destructor
      */
      virtual ~MaskBoundingBoxHelper() {};

      MaskBoundingBoxHelper() {};

    private:
      //No copy constructor allowed
      MaskBoundingBoxHelper(const Self& source);
      void operator=(const Self&);  //purposely not implemented
    };
  }
}

#endif
