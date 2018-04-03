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


#ifndef __ITK_PDE_DEFORMABLE_REGISTRATION_ALGORITHM_BASE_TPP
#define __ITK_PDE_DEFORMABLE_REGISTRATION_ALGORITHM_BASE_TPP

#include <itkHistogramMatchingImageFilter.h>

#include "mapAlgorithmException.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"
#include "mapMetaProperty.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			typename ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::FieldRepRequirement::Type
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			isMovingRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			typename ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::FieldRepRequirement::Type
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			isTargetRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			bool
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			isStoppable() const
			{
				return true;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			typename ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::IterationCountType
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			doGetCurrentIteration() const
			{
				return this->_currentIterationCount;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			typename ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::IterationCountType
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			doGetMaxIterations() const
			{
				IterationCountType result = 0;

				MetaPropertyPointer prop = this->getProperty("NumberOfIterations");
				map::core::unwrapMetaProperty(prop, result);

				return result;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			bool
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			hasIterationCount() const
			{
				return true;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			bool
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			hasMaxIterationCount() const
			{
				bool result = _internalRegistrationMethod.IsNotNull();

				return result;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			bool
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			hasCurrentOptimizerValue() const
			{
				bool result = _internalRegistrationMethod.IsNotNull();

				return result;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			bool
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			isReusable() const
			{
				return true;
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			ITKPDEDeformableRegistrationAlgorithmBase() : _currentIterationCount(0), _matchHistograms(true),
				_thresholdAtMeanIntensity(true), _numberOfHistogramLevels(1024), _numberOfHistogramMatchPoints(7)
			{
				_spInternalMovingImage = NULL;
				_spInternalTargetImage = NULL;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			~ITKPDEDeformableRegistrationAlgorithmBase()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			configureAlgorithm()
			{
				this->_internalRegistrationMethod = InternalRegistrationMethodType::New();
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			typename ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::InterimRegistrationPointer
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			determineInterimRegistration(const MovingRepresentationDescriptorType* pMovingRepresentation,
										 const TargetRepresentationDescriptorType* pTargetRepresentation) const
			{
				InterimRegistrationPointer spResult = NULL;

				if (this->_currentIterationCount > 0)
				{
					//now build the inverse kernel (main kernel of a image based registration algorithm)
					typedef typename
              ::map::core::PreCachedRegistrationKernel<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions> InverseKernelType;

          typename FieldTransformType::Pointer transform = FieldTransformType::New();
          transform->SetDisplacementField(_internalRegistrationMethod->GetDisplacementField());

					typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
          spIKernel->setTransformModel(transform);

					//now build the direct kernel via inversion of the inverse kernel
					typedef core::InverseRegistrationKernelGenerator<InterimRegistrationType::TargetDimensions, InterimRegistrationType::MovingDimensions>
					GeneratorType;
					typename GeneratorType::Pointer spGenerator = GeneratorType::New();
					typedef typename GeneratorType::InverseKernelBaseType DirectKernelType;
					typename DirectKernelType::Pointer spDKernel = spGenerator->generateInverse(*
							(spIKernel.GetPointer()), pMovingRepresentation);

					if (spDKernel.IsNull())
					{
						mapExceptionMacro(AlgorithmException,
										  << "Error. Cannot determine direct mapping kernel of interim registration. Current inverse kernel: "
										  << spIKernel);
					}

					//now create the registration an set the kernels
					spResult = InterimRegistrationType::New();
					::map::core::RegistrationManipulator<InterimRegistrationType> manipulator(spResult);

					manipulator.setDirectMapping(spDKernel);
					manipulator.setInverseMapping(spIKernel);
					manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();
				}

				return spResult;
			};


			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			prepCheckValidity()
			{
				if (!this->getMovingImage())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no moving image.");
				}

				if (!this->getTargetImage())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no target image.");
				}

				if (this->getTargetRepresentation())
				{
					typename TargetRepresentationDescriptorType::Pointer targetImageRep =
						map::core::createFieldRepresentation(*(this->getTargetImage()));

					if (!(*(this->getTargetRepresentation()) == (*targetImageRep)))
					{
						mapExceptionMacro(AlgorithmException,
										  << "Cannot start algorithm; user defined target representation does not match the target image.");
					}
				}

				if (this->getMovingRepresentation())
				{
					typename MovingRepresentationDescriptorType::Pointer movingImageRep =
						map::core::createFieldRepresentation(*(this->getMovingImage()));

					if (!(*(this->getMovingRepresentation()) == (*movingImageRep)))
					{
						mapExceptionMacro(AlgorithmException,
										  << "Cannot start algorithm; user defined moving representation does not match the moving image.");
					}
				}
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			prepPrepareSubComponents()
			{
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			prepAssembleSubComponents()
			{
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			prepPerpareInternalInputData()
			{
				if (this->_matchHistograms)
				{
					map::core::OStringStream strm;

					strm <<  "Match histograms of images. Threshold: " << this->_thresholdAtMeanIntensity <<
						 "; histogram levels: " << this->_numberOfHistogramLevels << "; match points: " <<
						 this->_numberOfHistogramMatchPoints;
					this->InvokeEvent(::map::events::AlgorithmEvent(this, strm.str()));

					typedef typename ::itk::HistogramMatchingImageFilter< TImageType, TImageType>   MatchingFilterType;
					typename MatchingFilterType::Pointer matcher = MatchingFilterType::New();

					matcher->SetInput(this->_spInternalMovingImage);
					matcher->SetReferenceImage(this->_spInternalTargetImage);

					matcher->SetNumberOfHistogramLevels(this->_numberOfHistogramLevels);
					matcher->SetNumberOfMatchPoints(this->_numberOfHistogramMatchPoints);
					matcher->SetThresholdAtMeanIntensity(this->_thresholdAtMeanIntensity);

					matcher->Update();

					this->_spInternalMovingImage = matcher->GetOutput();
				}
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			prepInitializeTransformation()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			prepFinalizePreparation()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			prepareAlgorithm()
			{
				this->prepCheckValidity();

				this->_currentIterationCount = 0;
				this->_spFinalizedRegistration = NULL;

				//create method
				this->_internalRegistrationMethod = InternalRegistrationMethodType::New();

				//initialize registration components
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Transfer cached MetaProperties."));
				this->configureAlgorithmByMetaProperties();

				//initialize registration components
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Initializing registration components."));
				this->prepPrepareSubComponents();

				//assemble registration components
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Initializing PDE deformable registration method."));
				this->prepAssembleSubComponents();

				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Initializing/Preparing input data."));
				_spInternalMovingImage = this->getMovingImage();
				_spInternalTargetImage = this->getTargetImage();

				this->prepPerpareInternalInputData();

				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Passing input data to internal algorithm."));
				this->prepSetInternalInputData();

				//possibility to initialize internal registration method after assembly
				this->prepInitializeTransformation();

				//initialize registration components after assembly
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Finalizing initialization..."));
				this->prepFinalizePreparation();

				//Register observers
				typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
				spCommand->SetCallbackFunction(this, &Self::onIterationEvent);
				this->_internalRegistrationMethod->AddObserver(::itk::IterationEvent(), spCommand);

				spCommand = ::itk::MemberCommand<Self>::New();
				spCommand->SetCallbackFunction(this, &Self::onGeneralRegistrationMethodEvent);
				this->_internalRegistrationMethod->AddObserver(::itk::AnyEvent(), spCommand);
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			finalizeAlgorithm()
			{
				RegistrationPointer spResult = NULL;

				//now build the inverse kernel (main kernel of a image based registration algorithm)
				typedef typename
				::map::core::PreCachedRegistrationKernel<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions> InverseKernelType;

				typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
        
        typename FieldTransformType::Pointer transform = FieldTransformType::New();
        transform->SetDisplacementField(this->getFinalDisplacementField());
        spIKernel->setTransformModel(transform);

				//now build the direct kernel via inversion of the inverse kernel
				typedef core::InverseRegistrationKernelGenerator<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions>
				GeneratorType;
				typename GeneratorType::Pointer spGenerator = GeneratorType::New();
				typedef typename GeneratorType::InverseKernelBaseType DirectKernelType;

				typename MovingRepresentationDescriptorType::ConstPointer movingImageRep  =
					this->getMovingRepresentation();

				if (movingImageRep.IsNull())
				{
					movingImageRep =  map::core::createFieldRepresentation(*(this->getMovingImage()));
				}

				typename DirectKernelType::Pointer spDKernel = spGenerator->generateInverse(*
						(spIKernel.GetPointer()), movingImageRep);

				if (spDKernel.IsNull())
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine direct mapping kernel of final registration. Current inverse kernel: "
									  << spIKernel);
				}

				//now create the registration an set the kernels
				spResult = RegistrationType::New();
				::map::core::RegistrationManipulator<RegistrationType> manipulator(spResult);

				manipulator.setDirectMapping(spDKernel);
				manipulator.setInverseMapping(spIKernel);
				manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

				//ensure that settings changed to the registration determination process are reseted to default
				this->configureAlgorithm();

				//store the final results
				_spFinalizedRegistration = spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			typename ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::RegistrationPointer
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			doGetRegistration() const
			{
				return _spFinalizedRegistration;
			};


			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			onIterationEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				::map::core::OStringStream os;

				bool hasCurrentValue = this->hasCurrentOptimizerValue();
				OptimizerMeasureType currentValue = this->getCurrentOptimizerValue();

				this->_currentIterationLock.Lock();
				++_currentIterationCount;

				os << "Iteration #" << _currentIterationCount << "; metric value: ";

				if (hasCurrentValue && currentValue.size() > 0)
				{
					os << currentValue[0];
				}
				else
				{
					os << "unkown";
				}

				os << "; RMS error change: " << this->_internalRegistrationMethod->GetRMSChange();
				this->_currentIterationLock.Unlock();

				this->InvokeEvent(::map::events::AlgorithmIterationEvent(this, os.str()));
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			onGeneralRegistrationMethodEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				::map::events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller,
						"internal registration method event");
				this->InvokeEvent(wrappedEvent);
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			bool
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			registrationIsOutdated() const
			{
				bool outdated = _spFinalizedRegistration.IsNull();

				if (_spFinalizedRegistration.IsNotNull())
				{
					if (!outdated)
					{
						outdated = _spFinalizedRegistration->GetMTime() < MetaPropertyAlgorithmBase::GetMTime();
					}

					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = this->_spInternalMovingImage->GetMTime() < this->getMovingImage()->GetMTime();
					}

					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = this->_spInternalTargetImage->GetMTime() < this->getTargetImage()->GetMTime();
					}

				}

				return outdated;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			typename ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::OptimizerMeasureType
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			doGetCurrentOptimizerValue() const
			{
				OptimizerMeasureType result;

				if (this->_internalRegistrationMethod.IsNotNull())
				{
					result.push_back(this->_internalRegistrationMethod->GetMetric());
				}

				return result;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			typename ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::InternalRegistrationMethodType&

			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			getInternalRegistrationMethod()
			{
				return *(this->_internalRegistrationMethod.GetPointer());
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			PrintSelf(std::ostream& os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				ImageRegistrationAlgorithmBase<TImageType, TImageType>::PrintSelf(os, indent);

				os << indent << "Current itertation count: " << _currentIterationCount << std::endl;
				os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MatchHistograms", typeid(bool), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("ThresholdAtMeanIntensity", typeid(bool),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("NumberOfHistogramLevels",
								typeid(unsigned int), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("NumberOfHistogramMatchPoints",
								typeid(unsigned int), true, true));

				infos.push_back(map::algorithm::MetaPropertyInfo::New("NumberOfIterations", typeid(unsigned long),
								true, true));

				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumKernelWidth", typeid(unsigned int),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumKernelError", typeid(double), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("SmoothDisplacementField", typeid(bool), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("DisplacementFieldStandardDeviations",
								typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("SmoothUpdateField", typeid(bool), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UpdateFieldStandardDeviations",
								typeid(double), true, true));
#endif
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			typename ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::MetaPropertyPointer
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "MatchHistograms")
				{
					spResult = map::core::MetaProperty<bool>::New(this->_matchHistograms);
				}
				else if (name == "ThresholdAtMeanIntensity")
				{
					spResult = map::core::MetaProperty<bool>::New(this->_thresholdAtMeanIntensity);
				}
				else if (name == "NumberOfHistogramLevels")
				{
					spResult = map::core::MetaProperty<unsigned int>::New(this->_numberOfHistogramLevels);
				}
				else if (name == "NumberOfHistogramMatchPoints")
				{
					spResult = map::core::MetaProperty<unsigned int>::New(this->_numberOfHistogramMatchPoints);
				}
				else if (name == "NumberOfIterations")
				{
					spResult = map::core::MetaProperty<unsigned long>::New(static_cast<unsigned long>
							   (this->_internalRegistrationMethod->GetNumberOfIterations()));
				}
				else if (name == "MaximumKernelWidth")
				{
					spResult = map::core::MetaProperty<unsigned int>::New(static_cast<unsigned int>
							   (this->_internalRegistrationMethod->GetMaximumKernelWidth()));
				}
				else if (name == "MaximumKernelError")
				{
					spResult = map::core::MetaProperty<double>::New(static_cast<double>
							   (this->_internalRegistrationMethod->GetMaximumError()));
				}
				else if (name == "SmoothDisplacementField")
				{
					spResult = map::core::MetaProperty<bool>::New(
								   this->_internalRegistrationMethod->GetSmoothDisplacementField());
				}
				else if (name == "DisplacementFieldStandardDeviations")
				{
					spResult = map::core::MetaProperty<double>::New(static_cast<double>((
								   this->_internalRegistrationMethod->GetStandardDeviations())[0]));
				}
				else if (name == "SmoothUpdateField")
				{
					spResult = map::core::MetaProperty<bool>::New(
								   this->_internalRegistrationMethod->GetSmoothUpdateField());
				}
				else if (name == "UpdateFieldStandardDeviations")
				{
					spResult = map::core::MetaProperty<double>::New(static_cast<double>((
								   this->_internalRegistrationMethod->GetUpdateFieldStandardDeviations())[0]));
				}
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}

				return spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TInternalRegistrationFilter>
			void
			ITKPDEDeformableRegistrationAlgorithmBase<TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "MatchHistograms")
				{
					bool match;
					map::core::unwrapMetaProperty(pProperty, match);
					this->_matchHistograms = match;
				}
				else if (name == "ThresholdAtMeanIntensity")
				{
					bool thresholdOn;
					map::core::unwrapMetaProperty(pProperty, thresholdOn);
					this->_thresholdAtMeanIntensity = thresholdOn;
				}
				else if (name == "NumberOfHistogramLevels")
				{
					unsigned int value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_numberOfHistogramLevels = value;
				}
				else if (name == "NumberOfHistogramMatchPoints")
				{
					unsigned int value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_numberOfHistogramMatchPoints = value;
				}
				else if (name == "NumberOfIterations")
				{
					unsigned long num;
					map::core::unwrapMetaProperty(pProperty, num);
					this->_internalRegistrationMethod->SetNumberOfIterations(num);
				}
				else if (name == "MaximumKernelWidth")
				{
					unsigned int num;
					map::core::unwrapMetaProperty(pProperty, num);
					this->_internalRegistrationMethod->SetMaximumKernelWidth(num);
				}
				else if (name == "MaximumKernelError")
				{
					double num;
					map::core::unwrapMetaProperty(pProperty, num);
					this->_internalRegistrationMethod->SetMaximumError(num);
				}
				else if (name == "SmoothDisplacementField")
				{
					bool value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_internalRegistrationMethod->SetSmoothDisplacementField(value);
				}
				else if (name == "DisplacementFieldStandardDeviations")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_internalRegistrationMethod->SetStandardDeviations(value);
				}
				else if (name == "SmoothUpdateField")
				{
					bool value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_internalRegistrationMethod->SetSmoothUpdateField(value);
				}
				else if (name == "UpdateFieldStandardDeviations")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_internalRegistrationMethod->SetUpdateFieldStandardDeviations(value);
				}
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
