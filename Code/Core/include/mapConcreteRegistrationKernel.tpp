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

#ifndef __CONCRETE_REGISTRATION_KERNEL_TPP
#define __CONCRETE_REGISTRATION_KERNEL_TPP

#include "mapExceptionObjectMacros.h"
#include "mapPointVectorCombinationPolicy.h"

#include "itkVectorLinearInterpolateImageFunction.h"
#include "mapNULLVectorAwareLinearInterpolateImageFunction.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
		typename ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::RepresentationDescriptorConstPointer
		ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::
		getLargestPossibleRepresentation() const
		{
			RepresentationDescriptorConstPointer spRep = TransformPolicyType::getRepresentationDescriptor();
			return spRep;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
		const typename
        ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::TransformType*
		ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::
    getTransformModel() const
		{
			if (!TransformPolicyType::checkAndPrepareField())
			{
				mapDefaultExceptionMacro( << "Error. Cannot return field. checkAndPrepareField() failed.");
			}

			return TransformPolicyType::_spTransform;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
		void
		ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::
		precomputeKernel()
		{
			if (! TransformPolicyType::checkAndPrepareField())
			{
				mapDefaultExceptionMacro( << "Error. Cannot precompute kernel/field.");
			}
		};


    template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
    const ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::MappingVectorType&
    ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::
    getNullVector() const
    {
        return TransformPolicyType::doGetNullVector();
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
    bool
    ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::
    usesNullVector() const
    {
        return TransformPolicyType::doUsesNullVector();
    };

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
		ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::
		ConcreteRegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
		ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::
		~ConcreteRegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
		bool
		ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::
		doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const
		{

			if (! TransformPolicyType::checkAndPrepareField())
			{
				mapDefaultExceptionMacro( <<
										  "Error. Transform is not ready and cannot be prepared. Unable to map point.");
			}


      if (TransformPolicyType::doUseNullVector())
			{
        mapDefaultExceptionMacro(<<
            "Error. NULL vector support is currently deactivated. Has to be reactivated after kernel merge (issue #1505).");

        //typedef itk::map::NULLVectorAwareLinearInterpolateImageFunction<FieldType, continuous::ScalarType>
        //    NULLAwareInterpolatorType;
        //typename NULLAwareInterpolatorType::Pointer spNullAwareInterpolator =
				//	NULLAwareInterpolatorType::New();
				//spNullAwareInterpolator->SetNullVector(Superclass::_nullVector);
				//spNullAwareInterpolator->SetNullVectorUsage(true);
        //spNullAwareInterpolator->SetInputImage(TransformPolicyType::_spTransform);

        //bool result = spNullAwareInterpolator->IsInsideBuffer(inPoint);


        //if (result)
        //{
        //    /*!@todo Unschön da itk im moment ein fixed array rausgibt anstatt eines vectors. an die Bug liste schreiben
        //    später noch mal prüfen ob schon ausgebessert oder doch lieber alte interpolator variante mit dem linearImageInterpolator verwendet werden soll
        //    */
        //    typename FieldType::ValueType vector = spNullAwareInterpolator->Evaluate(inPoint).GetDataPointer();

        //    if (Superclass::_useNullVector && vector == Superclass::_nullVector)
        //    {
        //        result = false;
        //    }
        //    else
        //    {
        //        PointVectorCombinationPolicy<VInputDimensions, VOutputDimensions>::mapPoint(inPoint, vector,
        //            outPoint);
        //    }
        //}

        //return result;
			}
			else
			{
        outPoint = _spTransformModel->TransformPoint(inPoint);
        return true;
      }
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
		void
		ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			TransformPolicyType::PrintSelf(os, indent);
		};

	} // end namespace core
} // end namespace map

#endif
