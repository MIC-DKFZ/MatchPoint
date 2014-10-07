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




#ifndef __ITK_FAST_SYMMETRIC_FORCES_DEMONS_REGISTRATION_ALGORITHM_H
#define __ITK_FAST_SYMMETRIC_FORCES_DEMONS_REGISTRATION_ALGORITHM_H

#include "itkFastSymmetricForcesDemonsRegistrationFilter.h"

#include "mapITKPDEDeformableRegistrationAlgorithm.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			/*! @class ITKFastSymmetricForcesDemonsRegistrationAlgorithm
			@brief The class for an image registration algorithm based on ITK
			@ingroup Algorithms
			@ingroup ITK
			*/
			template < class TImageType,
					 class TIdentificationPolicy,
                     class TDisplacementField = typename core::discrete::Elements<TImageType::ImageDimension>::VectorFieldType >
			class ITKFastSymmetricForcesDemonsRegistrationAlgorithm : public
				itk::ITKPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, ::itk::FastSymmetricForcesDemonsRegistrationFilter<TImageType, TImageType, TDisplacementField> >
			{
			public:
				typedef ITKFastSymmetricForcesDemonsRegistrationAlgorithm
				< TImageType, TIdentificationPolicy, TDisplacementField > Self;
				typedef itk::ITKPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, ::itk::FastSymmetricForcesDemonsRegistrationFilter<TImageType, TImageType, TDisplacementField> >
				Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKFastSymmetricForcesDemonsRegistrationAlgorithm,
							 ITKPDEDeformableRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;

				typedef typename
				IterativeRegistrationAlgorithm<TImageType::ImageDimension, TImageType::ImageDimension>::OptimizerMeasureType
				OptimizerMeasureType;

                typedef typename Superclass::TargetImageType TargetImageType;
                typedef typename Superclass::MovingImageType MovingImageType;
                typedef typename Superclass::MovingImageConstPointer MovingImageConstPointer;
                typedef typename Superclass::TargetImageConstPointer TargetImageConstPointer;

				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;

				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;
				typedef typename Superclass::IterationCountType IterationCountType;

                typedef typename Superclass::MetaPropertyPointer MetaPropertyPointer;
                typedef typename Superclass::MetaPropertyNameType MetaPropertyNameType;
                typedef typename Superclass::MetaPropertyVectorType MetaPropertyVectorType;
                typedef typename Superclass::MetaPropertyType MetaPropertyType;

			protected:
				ITKFastSymmetricForcesDemonsRegistrationAlgorithm();
				virtual ~ITKFastSymmetricForcesDemonsRegistrationAlgorithm();

				/*! @overwrite
				 * This default implementation does nothing.*/
				virtual void configureAlgorithm();

				/*! @reimplemented*/
				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				/*! @reimplemented*/
				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				/*! @reimplemented*/
				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

			private:
				ITKFastSymmetricForcesDemonsRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKFastSymmetricForcesDemonsRegistrationAlgorithm.tpp"
#endif

#endif
