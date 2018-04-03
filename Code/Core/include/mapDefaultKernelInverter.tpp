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

#ifndef __MAP_DEFAULT_KERNEL_INVERTER_TPP
#define __MAP_DEFAULT_KERNEL_INVERTER_TPP

#include "mapDefaultKernelInverter.h"
#include "mapServiceException.h"
#include "mapFieldByModelInversionFunctor.h"
#include "mapFieldByFieldInversionFunctor.h"
#include "mapInvertingRegistrationKernel.h"
#include "mapPreCachedRegistrationKernel.h"

#include "mapGenericVectorFieldTransform.h"

namespace map
{
	namespace core
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		unsigned long
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		getFunctorNumberOfIterations() const
		{
			return _functorNrOfIterations;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		setFunctorNumberOfIterations(unsigned long nrOfIterations)
		{
			_functorNrOfIterations = nrOfIterations;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		double
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		getFunctorStopValue() const
		{
			return _functorStopValue;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		setFunctorStopValue(double stopValue)
		{
			_functorStopValue = stopValue;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType& request) const
		{
			// if the kernel "request" is a regular kernel, then we can handle it.
			const KernelType* pKernel = dynamic_cast<const KernelType*>(&request);
			return (pKernel != NULL);
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "DefaultKernelInverter<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			OStringStream os;
			os << "DefaultKernelInverter, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
			   VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename DefaultKernelInverter<VInputDimensions, VOutputDimensions>::InverseKernelBasePointer
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		invertKernel(const KernelBaseType& kernel,
					 const FieldRepresentationType* pFieldRepresentation,
           const InverseFieldRepresentationType* pInverseFieldRepresentation,
           bool useNullPoint,
           NullPointType nullPoint) const
		{
			const KernelType* pKernel = dynamic_cast<const KernelType*>(&kernel);

			if (pKernel == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot invert kernel. Reason: cannot cast to RegistrationKernel: " << pKernel);
			}

			const typename KernelType::TransformType* pTransformModel = pKernel->getTransformModel();
			typename KernelType::TransformType::InverseTransformBasePointer spInverseTransformModel = pTransformModel->GetInverseTransform();

			InverseKernelBasePointer spResultKernel;
      
			if (spInverseTransformModel.IsNotNull())
			{
				// analytic inversion worked, so we just have to create the kernel and return it
				typedef PreCachedRegistrationKernel<VOutputDimensions, VInputDimensions> InverseKernelType;
				typename InverseKernelType::Pointer spInverseKernel = InverseKernelType::New();
				spInverseKernel->setTransformModel(spInverseTransformModel);
				spResultKernel = spInverseKernel;
			}
			else
			{
				// analytic inversion failed, do numeric inversion
				if (pInverseFieldRepresentation == NULL)
				{
					mapExceptionMacro(ServiceException,
									  << "Error: cannot invert kernel. Reason: pInverseFieldRepresentation not present.");
				}

        typedef InvertingRegistrationKernel<VOutputDimensions, VInputDimensions> InvertingKernelType;
				typename InvertingKernelType::Pointer spInverseKernel = InvertingKernelType::New();

        spInverseKernel->setSourceKernel(pKernel);

        typedef itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, VOutputDimensions, VInputDimensions> FieldTransformType;
        const FieldTransformType* pFieldTransformModel = dynamic_cast<const FieldTransformType*>(pTransformModel);

        if (pFieldTransformModel)
        { //the model is represented by a displacement field -> FieldByFieldInversionFunctor
            typedef functors::FieldByFieldInversionFunctor<VOutputDimensions, VInputDimensions> FunctorType;
            typename FunctorType::Pointer spFunctor = FunctorType::New(pKernel, pInverseFieldRepresentation);
            spFunctor->setStopValue(_functorStopValue);
            spFunctor->setNumberOfIterations(_functorNrOfIterations);
            spFunctor->setNullPointUsage(useNullPoint);
            spFunctor->setNullPoint(nullPoint);
            spInverseKernel->setTransformFunctor(spFunctor.GetPointer());
        }
        else
        { //the model is represented by some transform model -> FieldByModelInversionFunctor
            typedef typename functors::FieldByModelInversionFunctor<VOutputDimensions, VInputDimensions>
                FunctorType;
            typename FunctorType::Pointer spFunctor = FunctorType::New(pTransformModel,
                pInverseFieldRepresentation);
            spFunctor->setStopValue(_functorStopValue);
            spFunctor->setNumberOfIterations(_functorNrOfIterations);
            spFunctor->setNullPointUsage(useNullPoint);
            spFunctor->setNullPoint(nullPoint);

            spInverseKernel->setTransformFunctor(spFunctor.GetPointer());
        }


				spResultKernel = spInverseKernel;
			}

			assert(spResultKernel.IsNotNull());
			return spResultKernel;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		DefaultKernelInverter<VInputDimensions, VOutputDimensions>::
		DefaultKernelInverter(): _functorNrOfIterations(20), _functorStopValue(0.0)
		{};


	} // end namespace core
} // end namespace map

#endif
