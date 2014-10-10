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




#ifndef __ITK_PDE_DEFORMABLE_REGISTRATION_ALGORITHM_H
#define __ITK_PDE_DEFORMABLE_REGISTRATION_ALGORITHM_H

#include "mapITKPDEDeformableRegistrationAlgorithmBase.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKPDEDeformableRegistrationAlgorithm
			@brief The class for an image registration algorithm based on ITK
			@ingroup Algorithms
			@ingroup ITK
			*/
			template < class TImageType,
					 class TIdentificationPolicy,
					 class TDisplacementField =
					 typename core::discrete::Elements<TImageType::ImageDimension>::VectorFieldType ,
					 class TInternalRegistrationFilter =
					 ::itk::PDEDeformableRegistrationFilter<TImageType, TImageType, TDisplacementField> >
			class ITKPDEDeformableRegistrationAlgorithm : public
				ITKPDEDeformableRegistrationAlgorithmBase< TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter >
			{
			public:
				typedef ITKPDEDeformableRegistrationAlgorithm
				< TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter > Self;
				typedef ITKPDEDeformableRegistrationAlgorithmBase< TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter >
				Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKPDEDeformableRegistrationAlgorithm, ITKPDEDeformableRegistrationAlgorithmBase);
				mapNewAlgorithmMacro(Self);

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;

				typedef TIdentificationPolicy IdentificationPolicyType;

				typedef typename
				IterativeRegistrationAlgorithm<TImageType::ImageDimension, TImageType::ImageDimension>::OptimizerMeasureType
				OptimizerMeasureType;
				typedef ImageRegistrationAlgorithmBase<TImageType, TImageType> ImageRegistrationAlgorithmBaseType;

				typedef typename ImageRegistrationAlgorithmBaseType::TargetImageType TargetImageType;
				typedef typename ImageRegistrationAlgorithmBaseType::MovingImageType MovingImageType;
				typedef typename ImageRegistrationAlgorithmBaseType::MovingImageConstPointer
				MovingImageConstPointer;
				typedef typename ImageRegistrationAlgorithmBaseType::TargetImageConstPointer
				TargetImageConstPointer;

				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;

				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;
				typedef typename Superclass::IterationCountType IterationCountType;

				typedef typename MetaPropertyAlgorithmBase::MetaPropertyPointer MetaPropertyPointer;
				typedef typename MetaPropertyAlgorithmBase::MetaPropertyNameType MetaPropertyNameType;
				typedef typename MetaPropertyAlgorithmBase::MetaPropertyVectorType MetaPropertyVectorType;

			protected:
				ITKPDEDeformableRegistrationAlgorithm();
				virtual ~ITKPDEDeformableRegistrationAlgorithm();

				typedef TInternalRegistrationFilter InternalRegistrationMethodType;
				typedef typename Superclass::InterimRegistrationType InterimRegistrationType;
				typedef typename Superclass::InterimRegistrationPointer InterimRegistrationPointer;

				virtual bool doStopAlgorithm();

				/*! This method is the slot for passing relevant input data to the internal algorithm or its components.
				* @remark The default implementation passes _spInternalMoving and _spInternalTargetImage, sets the schedules, the fixed image region of the registration and the metric masks.
				@eguarantee strong
				*/
				virtual void prepSetInternalInputData();

				/*! This method should just execute the iteration loop.
				* @remark If you want to change the initialization or the finalization, then overwrite prepareAlgorithm() or finalizeAlgorithm().
				* @return Indicates of the registration was successfully determined (e.g. could be
				* false if an iterative algorithm was stopped prematurely by the user).
				* @eguarantee strong
				*/
				virtual bool runAlgorithm();

				virtual typename TDisplacementField::Pointer getFinalDisplacementField();

			private:

				ITKPDEDeformableRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKPDEDeformableRegistrationAlgorithm.tpp"
#endif

#endif
