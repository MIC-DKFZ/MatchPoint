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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Core/include/mapAffineMatrixOffsetDecompositionPolicy.h $
*/

#ifndef __MAP_AFFINE_MATRIX_DECOMPOSITION_POLICY_H
#define __MAP_AFFINE_MATRIX_DECOMPOSITION_POLICY_H

#include "mapFieldRepresentationDescriptor.h"
#include "mapRegistrationTopology.h"

#include <itkMatrixOffsetTransformBase.h>
#include <itkTranslationTransform.h>
#include <itkIdentityTransform.h>

namespace map
{
  namespace core
  {
    /*! @class AffineMatrixOffsetDecompositionPolicy
    * @brief Class defines the rule for decomposing an itk::transforms of any dimensionality into an affine matrix and offset (if that is possible).
    *
    * This helper class is used by MatchPoint for decomposition purposes of arbitrary dimensionality.
    * It can be seen like a trait pattern, because not all combinations of dimension allow all decomposition strategies.
    *
    * @ingroup Registration
    * @tparam VInDimensions Dimension count of the input type.
    * @tparam VOutDimensions Dimension count of the output type.
    */
    template <typename TScalarType, unsigned int VInDimensions, unsigned int VOutDimensions>
    class AffineMatrixOffsetDecompositionPolicy
    {
    public:
      typedef ::itk::Transform<TScalarType, VInDimensions, VOutDimensions> TransformType;

      using OutputPointType = typename continuous::Elements<VOutDimensions>::PointType;
      using OutputVectorType = typename continuous::Elements<VOutDimensions>::VectorType;

      typedef itk::Matrix<TScalarType, VOutDimensions, VInDimensions> MatrixType;

      /*! Tries to decompose the transform model into an affine matrix and an offset. It is indicated by the return value if
      * the actual model can be decomposed.\n
      * Usage of the return values: Point_trans = Matrix*Point + Offset
      *
      * @eguarantee strong
      * @remark Implement the function for special transform model classes.
      * @param [in] Pointer to the transfrom that should be decomposed
      * @param [out] matrix Reference to the matrix that define the affine non-translation part (e.g. rotation and scaling).
      * @param [out] offset Reference to a vector that defines the translation offset.
      * @return Indicates if the transform model can be decomposed in a affine transformation matrix plus offset. If it returns false, it cannot be decomposed
      * and the referenced output parameters are invalid. If the passed transform is invalid, it will also return false.*/
      static bool  getAffineMatrixDecomposition(const TransformType* transform, MatrixType& matrix, OutputVectorType& offset)
      {
        if (!transform)
        {
          return false;
        }

        typedef ::itk::TranslationTransform<TScalarType, VOutDimensions> TranslationTransformType;
        typedef ::itk::IdentityTransform<TScalarType, VOutDimensions> IdentityTransformType;

        bool result = false;

        const TranslationTransformType* translationModel = dynamic_cast<const TranslationTransformType*>(transform);
        const IdentityTransformType* identityModel = dynamic_cast<const IdentityTransformType*>(transform);

        if (translationModel)
        {
          matrix.SetIdentity();
          offset = translationModel->GetOffset();
          result =  true;       
        }
        else if (identityModel)
        {
          matrix.SetIdentity();
          offset.Fill(0);
          result =  true;       
        }

        return result;
      };

    private:

      typedef AffineMatrixOffsetDecompositionPolicy<TScalarType, VInDimensions, VOutDimensions> Self;
      AffineMatrixOffsetDecompositionPolicy(); //purposely not implemented
      virtual ~AffineMatrixOffsetDecompositionPolicy();  //purposely not implemented
      AffineMatrixOffsetDecompositionPolicy(const Self&);  //purposely not implemented
      void operator=(const Self&);  //purposely not implemented
    };

    /*! @class AffineMatrixOffsetDecompositionPolicy<VDimensions>
    * @brief Template specialization for the case that input and output are of the same dimensionality.
    *
    * @ingroup Registration
    * @tparam VDimensions Dimensionality of the operands.
    */
    template <typename TScalarType, unsigned int VDimensions>
    class AffineMatrixOffsetDecompositionPolicy<TScalarType, VDimensions, VDimensions>
    {
    public:
      typedef ::itk::Transform<TScalarType, VDimensions, VDimensions> TransformType;

      using OutputPointType = typename continuous::Elements<VDimensions>::PointType;
      using OutputVectorType = typename continuous::Elements<VDimensions>::VectorType;

      typedef itk::Matrix<TScalarType, VDimensions, VDimensions> MatrixType;

      /*! Tries to decompose the transform model into an affine matrix and an offset. It is indicated by the return value if
      * the actual model can be decomposed.\n
      * Usage of the return values: Point_trans = Matrix*Point + Offset
      *
      * @eguarantee strong
      * @remark Implement the function for special transform model classes.
      * @param [in] Pointer to the transform that should be decomposed
      * @param [out] matrix Reference to the matrix that define the affine non-translation part (e.g. rotation and scaling).
      * @param [out] offset Reference to a vector that defines the translation offset.
      * @return Indicates if the transform model can be decomposed in a affine transformation matrix plus offset. If it returns false, it cannot be decomposed
      * and the referenced output parameters are invalid. If the passed transform is invalid, it will also return false.*/
      static bool  getAffineMatrixDecomposition(const TransformType* transform, MatrixType& matrix, OutputVectorType& offset)
      {
        if (!transform)
        {
          return false;
        }

        typedef ::itk::MatrixOffsetTransformBase<TScalarType, VDimensions, VDimensions> MatrixOffsetTransformType;
        typedef ::itk::TranslationTransform<TScalarType, VDimensions> TranslationTransformType;
        typedef ::itk::IdentityTransform<TScalarType, VDimensions> IdentityTransformType;

        bool result = false;

        const MatrixOffsetTransformType* matrixBasedModel = dynamic_cast<const MatrixOffsetTransformType*>(transform);
        const TranslationTransformType* translationModel = dynamic_cast<const TranslationTransformType*>(transform);
        const IdentityTransformType* identityModel = dynamic_cast<const IdentityTransformType*>(transform);

        if (matrixBasedModel)
        {
          matrix = matrixBasedModel->GetMatrix();
          offset = matrixBasedModel->GetOffset();
          result =  true;       
        }
        else if (translationModel)
        {
          matrix.SetIdentity();
          offset = translationModel->GetOffset();
          result =  true;       
        }
        else if (identityModel)
        {
          matrix.SetIdentity();
          offset.Fill(0);
          result =  true;       
        }

        return result;
      };

    private:

      typedef AffineMatrixOffsetDecompositionPolicy<TScalarType, VDimensions, VDimensions> Self;
      AffineMatrixOffsetDecompositionPolicy(); //purposely not implemented
      virtual ~AffineMatrixOffsetDecompositionPolicy();  //purposely not implemented
      AffineMatrixOffsetDecompositionPolicy(const Self&);  //purposely not implemented
      void operator=(const Self&);  //purposely not implemented
    };


  } // end namespace core
} // end namespace map

#endif
