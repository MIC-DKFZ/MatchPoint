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

#ifndef __REGISTRATION_KERNEL_TPP
#define __REGISTRATION_KERNEL_TPP

#include "mapExceptionObjectMacros.h"
#include "mapPointVectorCombinationPolicy.h"
#include "mapNULLVectorAwareLinearInterpolateImageFunction.h"
#include "mapAffineMatrixOffsetDecompositionPolicy.h"

#include "itkVectorLinearInterpolateImageFunction.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
		void
		RegistrationKernel<VInputDimensions, VOutputDimensions>::
		precomputeKernel() const
		{
			if (! this->checkAndPrepareTransform())
			{
				mapDefaultExceptionMacro( << "Error. Cannot precompute kernel/field.");
			}
		};


    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    String
        RegistrationKernel<VInputDimensions, VOutputDimensions>::
        getModelName() const
    {
        if (this->transformExists())
        {
          return this->getTransformModel()->GetNameOfClass();
        }
        else
        {
          return "Unkown";
        }
    };


		template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
		RegistrationKernel<VInputDimensions, VOutputDimensions>::
		RegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
		RegistrationKernel<VInputDimensions, VOutputDimensions>::
		~RegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
		bool
		RegistrationKernel<VInputDimensions, VOutputDimensions>::
		doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const
		{

        if (!this->checkAndPrepareTransform())
			{
				mapDefaultExceptionMacro( <<
										  "Error. Transform is not ready and cannot be prepared. Unable to map point.");
			}

      outPoint = this->getTransformModel()->TransformPoint(inPoint);

      bool result = !this->usesNullPoint() || this->getNullPoint() != outPoint;

      return result;
		};


    template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
    bool
        RegistrationKernel<VInputDimensions, VOutputDimensions>::getAffineMatrixDecomposition(MatrixType& matrix, OutputVectorType& offset) const
    {
        if (this->transformExists())
        {
            return AffineMatrixOffsetDecompositionPolicy<typename TransformType::ScalarType, VInputDimensions, VOutputDimensions>::getAffineMatrixDecomposition(this->getTransformModel(), matrix, offset);
        }

        return false;
    };

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
		void
		RegistrationKernel<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
		};

	} // end namespace core
} // end namespace map

#endif
