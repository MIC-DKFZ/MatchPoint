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


#ifndef __MAP_PLM_CLI_REGISTRATION_ALGORITHM_BASE_TPP
#define __MAP_PLM_CLI_REGISTRATION_ALGORITHM_BASE_TPP

#include "itkSpatialObjectToImageFilter.h"
#include "itkImage.h"

#include "mapAlgorithmException.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"
#include "mapImageWriter.h"
#include "mapProcessExecutor.h"
#include "mapConvert.h"
#include "mapMetaProperty.h"
#include "mapString.h"
#include "mapFieldByFileLoadFunctor.h"

namespace map
{
	namespace algorithm
	{
		namespace plastimatch
		{

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::FieldRepRequirement::Type
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			isMovingRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::FieldRepRequirement::Type
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			isTargetRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			isStoppable() const
			{
				return false;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::IterationCountType
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetCurrentIteration() const
			{
				return 0;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::IterationCountType
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetMaxIterations() const
			{
				return 0;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			hasIterationCount() const
			{
				return false;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			hasMaxIterationCount() const
			{
				return false;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			hasCurrentOptimizerValue() const
			{
				return false;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			CLIRegistrationAlgorithmBase() : _deleteTempDirectory(true)
			{
				_spInternalMovingImage = NULL;
				_spInternalTargetImage = NULL;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			~CLIRegistrationAlgorithmBase()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			isReusable() const
			{
				return true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			configureAlgorithm()
			{
				if (this->isFirstConfiguration())
				{
					_plastimatchDir = "";
					core::String envDir = "";

					if (itksys::SystemTools::GetEnv("MAP_PLASTIMATCH_PATH", envDir))
					{
						_plastimatchDir = envDir;
					}

					_workingDir = itksys::SystemTools::GetCurrentWorkingDirectory();

					_deleteTempDirectory = true;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("WorkingDirectory", typeid(map::core::String),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("PlastimatchDirectory",
								typeid(map::core::String), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("DeleteTempDirectory", typeid(bool), true,
								true));
#endif
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::MetaPropertyPointer
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "WorkingDirectory")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_workingDir);
				}
				else if (name == "PlastimatchDirectory")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_plastimatchDir);
				}
				else if (name == "DeleteTempDirectory")
				{
					spResult = map::core::MetaProperty<bool>::New(this->_deleteTempDirectory);
				}
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}

				return spResult;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "WorkingDirectory")
				{
					core::String dir;
					map::core::unwrapMetaProperty(pProperty, dir);
					this->_workingDir = dir;
				}
				else if (name == "PlastimatchDirectory")
				{
					core::String dir;
					map::core::unwrapMetaProperty(pProperty, dir);
					this->_plastimatchDir = dir;
				}
				else if (name == "DeleteTempDirectory")
				{
					bool del;
					map::core::unwrapMetaProperty(pProperty, del);
					this->_deleteTempDirectory = del;
				}
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::InterimRegistrationPointer
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			determineInterimRegistration(const MovingRepresentationDescriptorType* pMovingRepresentation,
										 const TargetRepresentationDescriptorType* pTargetRepresentation) const
			{
				InterimRegistrationPointer spResult = NULL;
				return spResult;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doStopAlgorithm()
			{
				assert(false);

				mapExceptionMacro(AlgorithmException,
								  << "Cannot stop Plastimatch algorithm. Interim stop feature is not supported. Wrong usage of iterative algorithm interface");
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			initializeCurrentTempDir()
			{
				srand(time(NULL));
				core::OStringStream stream;
				stream << itksys::SystemTools::GetCurrentDateTime("%Y-%m-%d_%H-%M-%S") << "_#" << rand();
				core::String currentTempDir = core::FileDispatch::createFullPath(_workingDir, stream.str());

				if (!itksys::SystemTools::MakeDirectory(currentTempDir.c_str()))
				{
					mapExceptionMacro(AlgorithmException,
									  << "Cannot create temporary working sub dir. Please check validity of given working dir and ensure right privileges for the application. Failed temporary sub dir: "
									  << _currentTempDir);
				}

				_currentTempDir = currentTempDir;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			prepareAlgorithm()
			{
				try
				{
					this->prepCheckValidity();

					this->_spFinalizedRegistration = NULL;

					//initialize registration components
					this->InvokeEvent(events::AlgorithmEvent(this, "Transfer cached MetaProperties."));
					this->configureAlgorithmByMetaProperties();

					this->InvokeEvent(events::AlgorithmEvent(this, "Initializing registration."));
					this->initializeCurrentTempDir();

					//preparing data
					this->InvokeEvent(events::AlgorithmEvent(this, "Initializing/Preparing input data."));
					_spInternalMovingImage = this->getMovingImage();
					_spInternalTargetImage = this->getTargetImage();

					this->prepPerpareInternalInputData();

					//storing temporary images
					this->InvokeEvent(events::AlgorithmEvent(this,
									  "Passing input data to plastimatch working directory."));
					this->prepSavePlastimatchInputData();

					this->InvokeEvent(events::AlgorithmEvent(this, "Generating parameter maps for plastimatch."));
					this->prepConfigurationPLM();
					this->ensureCorrectGlobalConfigSettings();

					this->InvokeEvent(events::AlgorithmEvent(this, "Store plastimatch configuration."));
					saveConfigurationToFile(this->_configurationPLM, this->getParameterFilePath());
				}
				catch (...)
				{
					cleanTempDir();
					throw;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			cleanTempDir() const
			{
				try
				{
					if (itksys::SystemTools::FileExists(_currentTempDir.c_str()) && this->_deleteTempDirectory)
					{
						itksys::SystemTools::RemoveADirectory(_currentTempDir.c_str());
					}
				}
				catch (...)
				{
					mapLogWarningObjMacro( << "Cannot clean up. Exception while removing the directory. Directory" <<
										   this->_currentTempDir);
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
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
			}


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			prepPerpareInternalInputData()
			{
				//default implementation does nothing
			}


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			ensureCorrectGlobalConfigSettings()
			{
				if (this->_configurationPLM.empty())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no configuration is defined.");
				}

				if (this->_configurationPLM.size() < 2)
				{
					mapExceptionMacro(AlgorithmException,
									  << "Cannot start algorithm; invalid configuration (need at least the global section and one stage section).");
				}

				ConfigurationType checkedConfig = this->_configurationPLM;

				checkedConfig[0]["moving"] = plastimatch::ParamGenerator().add(this->_movingImageTempPath);
				checkedConfig[0]["fixed"] = plastimatch::ParamGenerator().add(this->_targetImageTempPath);
				checkedConfig[0]["vf_out"] = plastimatch::ParamGenerator().add(this->_finalFieldTempPath);

				if (this->getMovingMask().IsNotNull())
				{
					//add moving mask
					checkedConfig[0]["moving_mask"] = plastimatch::ParamGenerator().add(this->_movingMaskTempPath);
				}

				if (this->getTargetMask().IsNotNull())
				{
					//add target mask
					checkedConfig[0]["fixed_mask"] = plastimatch::ParamGenerator().add(this->_targetMaskTempPath);
				}

				checkedConfig[0].erase("xform_out");
				checkedConfig[0].erase("img_out");
				checkedConfig[0].erase("img_out_fmt");
				checkedConfig[0].erase("img_out_type");

				this->_configurationPLM.swap(checkedConfig);
			}

			template<class TImage>
			void
			saveTempImage(const TImage* image, const core::String& filePath)
			{
				typedef typename
				io::ImageWriter<typename TImage::PixelType, typename TImage::PixelType, TImage::ImageDimension>
				WriterType;
				typename WriterType::Pointer spWriter = WriterType::New();
				spWriter->setInput(image);
				spWriter->setFilePath(filePath);
				spWriter->update();
			};

			template<unsigned int VDimension>
			typename ::itk::Image<unsigned char, VDimension>::Pointer
			generateMaskImage(const ::itk::SpatialObject<VDimension>* so,
							  const core::FieldRepresentationDescriptor<VDimension>* descriptor)
			{
				assert(so);
				assert(descriptor);
				typedef ::itk::Image<unsigned char, VDimension> MaskImageType;
				typedef ::itk::SpatialObject<VDimension> ObjectType;
				typedef ::itk::SpatialObjectToImageFilter<ObjectType, MaskImageType> FilterType;
				typename FilterType::Pointer spFilter = FilterType::New();

				spFilter->SetInput(so);

				typename MaskImageType::SizeType size;

				for (unsigned long i = 0; i < VDimension; ++i)
				{
					size[i] = static_cast<typename MaskImageType::SizeType::SizeValueType>
							  (descriptor->getSize()[i] / descriptor->getSpacing()[i]);
				}

				spFilter->SetSize(size);
				spFilter->SetSpacing(descriptor->getSpacing());
				spFilter->SetOrigin(descriptor->getOrigin());
				spFilter->SetDirection(descriptor->getDirection());
				spFilter->Update();
				spFilter->SetInsideValue(1);
				spFilter->SetOutsideValue(0);

				return spFilter->GetOutput();
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			prepSavePlastimatchInputData()
			{
				//save the images
				_movingImageTempPath = core::FileDispatch::createFullPath(_currentTempDir, "moving.mhd");
				_targetImageTempPath = core::FileDispatch::createFullPath(_currentTempDir, "target.mhd");
				_finalFieldTempPath = core::FileDispatch::createFullPath(_currentTempDir, "deformationField.mhd");
				_movingMaskTempPath = "";
				_targetMaskTempPath = "";

				this->InvokeEvent(events::AlgorithmEvent(this,
								  "Write temporary moving image. Path: " + _movingImageTempPath));
				saveTempImage(_spInternalMovingImage.GetPointer(), _movingImageTempPath);
				this->InvokeEvent(events::AlgorithmEvent(this,
								  "Write temporary target image. Path: " + _targetImageTempPath));
				saveTempImage(_spInternalTargetImage.GetPointer(), _targetImageTempPath);

				//save the masks
				if (this->getMovingMask().IsNotNull())
				{
					//add moving mask
					typedef ::itk::Image<unsigned char, TMovingImage::ImageDimension> MaskImageType;
					MaskImageType::Pointer spMovingMaskImage = generateMaskImage<Superclass::MovingDimensions>
							(this->getMovingMask(), core::createFieldRepresentation(*(_spInternalMovingImage)).GetPointer());

					_movingMaskTempPath = core::FileDispatch::createFullPath(_currentTempDir, "movingMask.mhd");
					this->InvokeEvent(events::AlgorithmEvent(this,
									  "Write temporary moving mask image. Path: " + _movingMaskTempPath));
					saveTempImage(spMovingMaskImage.GetPointer(), _movingMaskTempPath);
				}

				if (this->getTargetMask().IsNotNull())
				{
					//add target mask
					typedef ::itk::Image<unsigned char, TTargetImage::ImageDimension> MaskImageType;
					MaskImageType::Pointer spTargetMaskImage = generateMaskImage<Superclass::TargetDimensions>
							(this->getTargetMask(), core::createFieldRepresentation(*(_spInternalTargetImage)).GetPointer());

					_targetMaskTempPath = core::FileDispatch::createFullPath(_currentTempDir, "targetMask.mhd");
					this->InvokeEvent(events::AlgorithmEvent(this,
									  "Write temporary target mask image. Path: " + _targetMaskTempPath));
					saveTempImage(spTargetMaskImage.GetPointer(), _targetMaskTempPath);
				}

			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			runAlgorithm()
			{
				map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();

				typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
				spCommand->SetCallbackFunction(this, &Self::onPlmOutputEvent);
				spExec->AddObserver(map::events::ExternalProcessStdOutEvent(), spCommand);

				map::utilities::ProcessExecutor::ArgumentListType args;
				args.push_back("register");
				args.push_back(this->getParameterFilePath());

				core::OStringStream ostr;
				ostr << "Calling plastimatch (" << _plastimatchDir << ") with arguments:";

				for (map::utilities::ProcessExecutor::ArgumentListType::const_iterator pos = args.begin();
					 pos != args.end(); ++pos)
				{
					ostr << " " << *pos;
				}

				this->InvokeEvent(events::AlgorithmEvent(this, ostr.str()));

				if (!spExec->execute(_plastimatchDir, core::FileDispatch::createFullPath(_plastimatchDir,
									 "plastimatch"), args))
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error when executing plastimatch to determine the registration.");
				}

				return spExec->getExitValue() == 0;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::FinalFieldPointer
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			generateField() const
			{
				typedef map::core::functors::FieldByFileLoadFunctor<Superclass::TargetDimensions, Superclass::MovingDimensions>
				FunctorType;
				FunctorType::Pointer spFunctor = FunctorType::New(_finalFieldTempPath);

				FinalFieldPointer spField = spFunctor->generateField();

				if (spField.IsNull())
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error when loading Plastimatch deformation field. File name: " << _finalFieldTempPath);
				}

				return spField;
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			core::String
			map::algorithm::plastimatch::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			getParameterFilePath() const
			{
				core::String result = core::FileDispatch::createFullPath(_currentTempDir, "parameters.txt");
				return result;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			core::String
			map::algorithm::plastimatch::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			getFinalTransformFilePath() const
			{
				if (this->_configurationPLM.empty())
				{
					mapExceptionMacro(AlgorithmException,
									  << "Cannot determine final transform file path; no parameter maps are defined.");
				}

				core::OStringStream ostr;
				ostr << "TransformParameters." << this->_configurationPLM.size() - 1 << ".txt";
				core::String result = core::FileDispatch::createFullPath(_currentTempDir, ostr.str());
				return result;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			finalizeAlgorithm()
			{
				RegistrationPointer spResult = NULL;

				try
				{
					_spFinalizedField = this->generateField();

					typedef map::core::FieldKernels<Superclass::TargetDimensions, Superclass::MovingDimensions>::PreCachedFieldBasedRegistrationKernel
					InverseKernelType;
					typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();

					spIKernel->setField(*(_spFinalizedField.GetPointer()));

					//now build the direct kernel via inversion of the inverse kernel
					typedef core::InverseRegistrationKernelGenerator<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions>
					GeneratorType;
					typename GeneratorType::Pointer spGenerator = GeneratorType::New();
					typedef typename GeneratorType::InverseKernelBaseType DirectKernelType;
					typename Superclass::MovingRepresentationDescriptorType::ConstPointer spMovingRep =
						core::createFieldRepresentation(*(this->getMovingImage()));

					if (this->getMovingRepresentation())
					{
						//user has defined a representation descriptor -> use this one
						spMovingRep = this->getMovingRepresentation();
					}

					typename DirectKernelType::Pointer spDKernel = spGenerator->generateInverse(*
							(spIKernel.GetPointer()), spMovingRep);

					if (spDKernel.IsNull())
					{
						mapExceptionMacro(AlgorithmException,
										  << "Error. Cannot determine direct mapping kernel of final registration. Current inverse kernel: "
										  << spIKernel);
					}

					//now create the registration and set the kernels
					spResult = RegistrationType::New();
					core::RegistrationManipulator<RegistrationType> manipulator(spResult);

					manipulator.setDirectMapping(spDKernel);
					manipulator.setInverseMapping(spIKernel);
					manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

					_spFinalizedRegistration = spResult;
				}
				catch (...)
				{
					//delete temp dir even in case of an exception
					cleanTempDir();
					throw;
				}

				//delete temp dir
				cleanTempDir();
				_currentTempDir = "";
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::RegistrationPointer
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetRegistration() const
			{
				return _spFinalizedRegistration;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			registrationIsOutdated() const
			{
				bool outdated = _spFinalizedRegistration.IsNull();

				if (_spFinalizedRegistration.IsNotNull())
				{
					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = this->_spInternalMovingImage != this->getMovingImage();
					}

					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = this->_spInternalTargetImage != this->getTargetImage();
					}
				}

				return outdated;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::OptimizerMeasureType
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetCurrentOptimizerValue() const
			{
				OptimizerMeasureType result;

				return result;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			PrintSelf(std::ostream& os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::PrintSelf(os, indent);

				os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			onPlmOutputEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				const events::ExternalProcessStdOutEvent* pStdEvent =
					dynamic_cast<const events::ExternalProcessStdOutEvent*>(&eventObject);

				if (pStdEvent)
				{
					this->InvokeEvent(events::AlgorithmIterationEvent(this, pStdEvent->getComment()));
				}
			}

		} // end namespace plastimatch
	} // end namespace algorithm
} // end namespace map

#endif
