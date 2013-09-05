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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Elastix/include/mapElxCLIRegistrationAlgorithmBase.tpp $
*/


#ifndef __MAP_ELX_CLI_REGISTRATION_ALGORITHM_BASE_TPP
#define __MAP_ELX_CLI_REGISTRATION_ALGORITHM_BASE_TPP

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
		namespace elastix
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
					_elastixDir = "";
					core::String envDir = "";

					if (itksys::SystemTools::GetEnv("MAP_ELASTIX_PATH", envDir))
					{
						_elastixDir = envDir;
					}

					_workingDir = itksys::SystemTools::GetCurrentWorkingDirectory();

					_deleteTempDirectory = true;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			compileInfos(MetaPropertyVectorType &infos) const
			{
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("WorkingDirectory", typeid(map::core::String), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("ElastixDirectory", typeid(map::core::String), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("DeleteTempDirectory", typeid(bool), true, true));
#endif
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::MetaPropertyPointer
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetProperty(const MetaPropertyNameType &name) const
			{
				MetaPropertyPointer spResult;

				if (name == "WorkingDirectory")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_workingDir);
				}
				else if (name == "ElastixDirectory")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_elastixDir);
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
			doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty)
			{
				if (name == "WorkingDirectory")
				{
					core::String dir;
					map::core::unwrapMetaProperty(pProperty, dir);
					this->_workingDir = dir;
				}
				else if (name == "ElastixDirectory")
				{
					core::String dir;
					map::core::unwrapMetaProperty(pProperty, dir);
					this->_elastixDir = dir;
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
			determineInterimRegistration(const MovingRepresentationDescriptorType *pMovingRepresentation,
			                             const TargetRepresentationDescriptorType *pTargetRepresentation) const
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

				mapExceptionMacro(AlgorithmException, << "Cannot stop Elastix algorithm. Interim stop feature is not supported. Wrong usage of iterative algorithm interface");
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
					mapExceptionMacro(AlgorithmException, << "Cannot create temporary working sub dir. Please check validity of given working dir and ensure right privileges for the application. Failed temporary sub dir: " << _currentTempDir);
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
					this->InvokeEvent(events::AlgorithmEvent(this, "Passing input data to elastix working directory."));
					this->prepSaveElastixInputData();

					this->InvokeEvent(events::AlgorithmEvent(this, "Generating parameter maps for elastix."));
					this->prepParameterMaps();

					if (this->_parameterMaps.empty())
					{
						mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no parameter maps are defined.");
					}

					unsigned int stageNR = 0;

					for (ParameterMapVectorType::const_iterator pos = this->_parameterMaps.begin(); pos != this->_parameterMaps.end(); ++pos, ++stageNR)
					{
						this->InvokeEvent(events::AlgorithmEvent(this, "Store parameter map for stage #" + map::core::convert::toStr(stageNR) + "."));
						saveParameterMapToFile(*pos, this->getParameterFilePath(stageNR));
					}
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
					mapLogWarningObjMacro( << "Cannot clean up. Exception while removing the directory. Directory" << this->_currentTempDir);
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


			template<class TImage>
			void
			saveTempImage(const TImage *image, const core::String &filePath)
			{
				typedef typename io::ImageWriter<typename TImage::PixelType, typename TImage::PixelType, TImage::ImageDimension> WriterType;
				typename WriterType::Pointer spWriter = WriterType::New();
				spWriter->setInput(image);
				spWriter->setFilePath(filePath);
				spWriter->update();
			};

			template<unsigned int VDimension>
			typename ::itk::Image<unsigned char, VDimension>::Pointer
			generateMaskImage(const ::itk::SpatialObject<VDimension> *so, const core::FieldRepresentationDescriptor<VDimension> *descriptor)
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
					size[i] = static_cast<typename MaskImageType::SizeType::SizeValueType>(descriptor->getSize()[i] / descriptor->getSpacing()[i]);
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
			prepSaveElastixInputData()
			{
				//save the images
				_movingImageTempPath = core::FileDispatch::createFullPath(_currentTempDir, "moving.mhd");
				_targetImageTempPath = core::FileDispatch::createFullPath(_currentTempDir, "target.mhd");
				_finalFieldTempPath = core::FileDispatch::createFullPath(_currentTempDir, "deformationField.mhd");
				_movingMaskTempPath = "";
				_targetMaskTempPath = "";

				this->InvokeEvent(events::AlgorithmEvent(this, "Write temporary moving image. Path: " + _movingImageTempPath));
				saveTempImage(_spInternalMovingImage.GetPointer(), _movingImageTempPath);
				this->InvokeEvent(events::AlgorithmEvent(this, "Write temporary target image. Path: " + _targetImageTempPath));
				saveTempImage(_spInternalTargetImage.GetPointer(), _targetImageTempPath);

				//save the masks
				if (this->getMovingMask().IsNotNull())
				{
					//add moving mask
					typedef itk::Image<unsigned char, TMovingImage::ImageDimension> MaskImageType;
					MaskImageType::Pointer spMovingMaskImage = generateMaskImage<Superclass::MovingDimensions>(this->getMovingMask(), core::createFieldRepresentation(*(_spInternalMovingImage)).GetPointer());

					_movingMaskTempPath = core::FileDispatch::createFullPath(_currentTempDir, "movingMask.mhd");
					this->InvokeEvent(events::AlgorithmEvent(this, "Write temporary moving mask image. Path: " + _movingMaskTempPath));
					saveTempImage(spMovingMaskImage.GetPointer(), _movingMaskTempPath);
				}

				if (this->getTargetMask().IsNotNull())
				{
					//add target mask
					typedef itk::Image<unsigned char, TTargetImage::ImageDimension> MaskImageType;
					MaskImageType::Pointer spTargetMaskImage = generateMaskImage<Superclass::TargetDimensions>(this->getTargetMask(), core::createFieldRepresentation(*(_spInternalTargetImage)).GetPointer());

					_targetMaskTempPath = core::FileDispatch::createFullPath(_currentTempDir, "targetMask.mhd");
					this->InvokeEvent(events::AlgorithmEvent(this, "Write temporary target mask image. Path: " + _targetMaskTempPath));
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
				spCommand->SetCallbackFunction(this, &Self::onElxOutputEvent);
				spExec->AddObserver(map::events::ExternalProcessStdOutEvent(), spCommand);

				map::utilities::ProcessExecutor::ArgumentListType args;
				args.push_back("-m");
				args.push_back(_movingImageTempPath);
				args.push_back("-f");
				args.push_back(_targetImageTempPath);
				args.push_back("-out");
				args.push_back(_currentTempDir);

				if (this->getMovingMask().IsNotNull())
				{
					//add moving mask
					args.push_back("-mMask");
					args.push_back(_movingMaskTempPath);
				}

				if (this->getTargetMask().IsNotNull())
				{
					//add target mask
					args.push_back("-tMask");
					args.push_back(_targetMaskTempPath);
				}

				unsigned int stageNR = 0;

				for (ParameterMapVectorType::const_iterator pos = this->_parameterMaps.begin(); pos != this->_parameterMaps.end(); ++pos, ++stageNR)
				{
					args.push_back("-p");
					args.push_back(this->getParameterFilePath(stageNR));
				}

				core::OStringStream ostr;
				ostr << "Calling elastix (" << _elastixDir << ") with arguments:";

				for (map::utilities::ProcessExecutor::ArgumentListType::const_iterator pos = args.begin(); pos != args.end(); ++pos)
				{
					ostr << " " << *pos;
				}

				this->InvokeEvent(events::AlgorithmEvent(this, ostr.str()));

				if (!spExec->execute(_elastixDir, core::FileDispatch::createFullPath(_elastixDir, "elastix"), args))
				{
					mapExceptionMacro(AlgorithmException, << "Error when executing elastix to determine the registration.");
				}

				return spExec->getExitValue() == 0;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::FinalFieldPointer
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			generateField() const
			{
				map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();

				map::utilities::ProcessExecutor::ArgumentListType args;
				args.push_back("-def");
				args.push_back("all");
				args.push_back("-out");
				args.push_back(_currentTempDir);
				args.push_back("-tp");
				args.push_back(this->getFinalTransformFilePath());

				core::OStringStream ostr;
				ostr << "Calling transformix (" << _elastixDir << ") with arguments:";

				for (map::utilities::ProcessExecutor::ArgumentListType::const_iterator pos = args.begin(); pos != args.end(); ++pos)
				{
					ostr << " " << *pos;
				}

				this->InvokeEvent(events::AlgorithmEvent(NULL, ostr.str()));

				if (!spExec->execute(_elastixDir, core::FileDispatch::createFullPath(_elastixDir, "transformix"), args))
				{
					mapExceptionMacro(AlgorithmException, << "Error when executing transformix to generate the deformation field.");
				}

				typedef map::core::functors::FieldByFileLoadFunctor<Superclass::TargetDimensions, Superclass::MovingDimensions> FunctorType;
				FunctorType::Pointer spFunctor = FunctorType::New(_finalFieldTempPath);

				FinalFieldPointer spField = spFunctor->generateField();

				if (spField.IsNull())
				{
					mapExceptionMacro(AlgorithmException, << "Error when loading transformix deformation field. File name: " << _finalFieldTempPath);
				}

				return spField;
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			core::String
			map::algorithm::elastix::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			getParameterFilePath(unsigned int stageNr) const
			{
				core::OStringStream ostr;
				ostr << "parameters_stage_#" << stageNr << ".txt";
				core::String result = core::FileDispatch::createFullPath(_currentTempDir, ostr.str());
				return result;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			core::String
			map::algorithm::elastix::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			getFinalTransformFilePath() const
			{
				if (this->_parameterMaps.empty())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot determine final transform file path; no parameter maps are defined.");
				}

				core::OStringStream ostr;
				ostr << "TransformParameters." << this->_parameterMaps.size() - 1 << ".txt";
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

					typedef map::core::FieldKernels<Superclass::TargetDimensions, Superclass::MovingDimensions>::PreCachedFieldBasedRegistrationKernel InverseKernelType;
					typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();

					spIKernel->setField(*(_spFinalizedField.GetPointer()));

					//now build the direct kernel via inversion of the inverse kernel
					typedef core::InverseRegistrationKernelGenerator<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions> GeneratorType;
					typename GeneratorType::Pointer spGenerator = GeneratorType::New();
					typedef typename GeneratorType::InverseKernelBaseType DirectKernelType;
					typename Superclass::MovingRepresentationDescriptorType::ConstPointer spMovingRep = core::createFieldRepresentation(*(this->getMovingImage()));

					if (this->getMovingRepresentation())
					{
						//user has defined a representation descriptor -> use this one
						spMovingRep = this->getMovingRepresentation();
					}

					typename DirectKernelType::Pointer spDKernel = spGenerator->generateInverse(*(spIKernel.GetPointer()), spMovingRep);

					if (spDKernel.IsNull())
					{
						mapExceptionMacro(AlgorithmException, << "Error. Cannot determine direct mapping kernel of final registration. Current inverse kernel: " << spIKernel);
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
			PrintSelf(std::ostream &os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::PrintSelf(os, indent);

				os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>::
			onElxOutputEvent(::itk::Object *caller, const ::itk::EventObject &eventObject)
			{
				const events::ExternalProcessStdOutEvent *pStdEvent = dynamic_cast<const events::ExternalProcessStdOutEvent *>(&eventObject);

				if (pStdEvent)
				{
					this->InvokeEvent(events::AlgorithmIterationEvent(this, pStdEvent->getComment()));
				}
			}

		} // end namespace elastix
	} // end namespace algorithm
} // end namespace map

#endif
