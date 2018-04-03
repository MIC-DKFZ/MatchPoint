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




#ifndef __ITK_PDE_DEMONS_REGISTRATION_ALGORITHM_H
#define __ITK_PDE_DEMONS_REGISTRATION_ALGORITHM_H

#include "itkDemonsRegistrationFilter.h"

#include "mapITKPDEDeformableRegistrationAlgorithm.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			/*! @class ITKPDEDemonsRegistrationAlgorithm
			@brief The class for wrapping an algorithm based on itk::DemonsRegistrationFilter.
			@ingroup Algorithms
			@ingroup ITK
			*/
			template < class TImageType,
					 class TIdentificationPolicy,
					 class TDisplacementField = typename
					 core::discrete::Elements<TImageType::ImageDimension>::VectorFieldType >
			class ITKPDEDemonsRegistrationAlgorithm : public
				itk::ITKPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, ::itk::DemonsRegistrationFilter<TImageType, TImageType, TDisplacementField> >
			{
			public:
				typedef ITKPDEDemonsRegistrationAlgorithm < TImageType, TIdentificationPolicy, TDisplacementField >
				Self;
				typedef itk::ITKPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, ::itk::DemonsRegistrationFilter<TImageType, TImageType, TDisplacementField> >
				Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKPDEDemonsRegistrationAlgorithm, ITKPDEDeformableRegistrationAlgorithm);
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
				ITKPDEDemonsRegistrationAlgorithm();
				virtual ~ITKPDEDemonsRegistrationAlgorithm();

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
				ITKPDEDemonsRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKPDEDemonsRegistrationAlgorithm.tpp"
#endif

#endif
