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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapConcreteFieldBasedRegistrationKernel.tpp $
*/

#ifndef __CONCRETE_FIELD_BASED_REGISTRATION_KERNEL_TPP
#define __CONCRETE_FIELD_BASED_REGISTRATION_KERNEL_TPP

#include "mapExceptionObjectMacros.h"
#include "mapPointVectorCombinationPolicy.h"

#include "itkVectorLinearInterpolateImageFunction.h"
#include "mapNULLVectorAwareLinearInterpolateImageFunction.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TFieldPolicy >
		typename ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::RepresentationDescriptorConstPointer
		ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::
		getLargestPossibleRepresentation() const
		{
			RepresentationDescriptorConstPointer spRep = FieldPolicyType::getRepresentationDescriptor();
			return spRep;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TFieldPolicy >
		const typename ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::FieldType *
		ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::
		getField() const
		{
			if (!FieldPolicyType::checkAndPrepareField())
			{
				mapDefaultExceptionMacro( << "Error. Cannot return field. checkAndPrepareField() failed.");
			}

			return FieldPolicyType::_spField;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TFieldPolicy >
		typename ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::FieldType *
		ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::
		getField()
		{
			if (! FieldPolicyType::checkAndPrepareField())
			{
				mapDefaultExceptionMacro( << "Error. Cannot return field. checkAndPrepareField() failed.");
			}

			return FieldPolicyType::_spField;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TFieldPolicy >
		void
		ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::
		precomputeKernel()
		{
			if (! FieldPolicyType::checkAndPrepareField())
			{
				mapDefaultExceptionMacro( << "Error. Cannot precompute kernel/field.");
			}
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TFieldPolicy >
		ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::
		ConcreteFieldBasedRegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TFieldPolicy >
		ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::
		~ConcreteFieldBasedRegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TFieldPolicy >
		bool
		ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::
		doMapPoint(const InputPointType &inPoint, OutputPointType &outPoint) const
		{
			typedef itk::VectorLinearInterpolateImageFunction<FieldType, continuous::ScalarType> InterpolatorType;
			typedef itk::map::NULLVectorAwareLinearInterpolateImageFunction<FieldType, continuous::ScalarType> NULLAwareInterpolatorType;

			if (! FieldPolicyType::checkAndPrepareField())
			{
				mapDefaultExceptionMacro( << "Error. Field is not ready and cannot be prepared. Unable to map point.");
			}

			typename InterpolatorType::Pointer spInterpolator;

			if (Superclass::_useNullVector)
			{
				typename NULLAwareInterpolatorType::Pointer spNullAwareInterpolator = NULLAwareInterpolatorType::New();
				spNullAwareInterpolator->SetNullVector(Superclass::_nullVector);
				spNullAwareInterpolator->SetNullVectorUsage(true);
				spInterpolator = spNullAwareInterpolator;
			}
			else
			{
				spInterpolator = InterpolatorType::New();
			}

			spInterpolator->SetInputImage(FieldPolicyType::_spField);

			bool result = spInterpolator->IsInsideBuffer(inPoint);


			if (result)
			{
				/*!@todo Unschön da itk im moment ein fixed array rausgibt anstatt eines vectors. an die Bug liste schreiben
				  später noch mal prüfen ob schon ausgebessert oder doch lieber alte interpolator variante mit dem linearImageInterpolator verwendet werden soll
				*/
				typename FieldType::ValueType vector = spInterpolator->Evaluate(inPoint).GetDataPointer();

				if (Superclass::_useNullVector && vector == Superclass::_nullVector)
				{
					result = false;
				}
				else
				{
					PointVectorCombinationPolicy<VInputDimensions, VOutputDimensions>::mapPoint(inPoint, vector, outPoint);
				}
			}

			return result;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TFieldPolicy >
		void
		ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, TFieldPolicy>::
		PrintSelf(std::ostream &os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			FieldPolicyType::PrintSelf(os, indent);
		};

	} // end namespace core
} // end namespace map

#endif
