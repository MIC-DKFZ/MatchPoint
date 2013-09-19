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


#ifndef __MAP_FSL_REGISTRATION_ALGORITHM_TPP
#define __MAP_FSL_REGISTRATION_ALGORITHM_TPP

#include "mapAlgorithmException.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"
#include "mapImageWriter.h"
#include "mapProcessExecutor.h"
#include "mapFSLHelper.h"

namespace map
{
	namespace algorithm
	{
		namespace fsl
		{

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::UIDPointer
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			getUID() const
			{
				return this->UID();
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			::map::core::String
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			getAlgorithmProfile() const
			{
				return this->AlgorithmProfile();
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			::map::core::String
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			getAlgorithmDescription() const
			{
				return this->AlgorithmDescription();
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::FieldRepRequirement::Type
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			isMovingRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::FieldRepRequirement::Type
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			isTargetRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			isStoppable() const
			{
				return false;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::IterationCountType
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetCurrentIteration() const
			{
				return 0;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::IterationCountType
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetMaxIterations() const
			{
				return 0;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			hasIterationCount() const
			{
				return false;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			hasMaxIterationCount() const
			{
				return false;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			hasCurrentOptimizerValue() const
			{
				return false;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			FSLRegistrationAlgorithm(): _deleteTempDirectory(true)
			{
				_spInternalMovingImage = NULL;
				_spInternalTargetImage = NULL;
				_finalizedTransformParameters.clear();
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			~FSLRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			isReusable() const
			{
				return true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			configureAlgorithm()
			{
				if (this->isFirstConfiguration())
				{
					_flirtDir = "";
					core::String envDir = "";

					if (itksys::SystemTools::GetEnv("MAPFSLPath", envDir))
					{
						_flirtDir = envDir;
					}
					else if (itksys::SystemTools::GetEnv("FSLDIR", envDir))
					{
						_flirtDir = envDir;
					}

					_workingDir = itksys::SystemTools::GetCurrentWorkingDirectory();

					_costFnc = CostFunction::CorrelationRatio;
					_dof = DegreesOfFreedom::DoF12;
					_deleteTempDirectory = true;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("WorkingDirectory", typeid(map::core::String),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("FlirtDirectory", typeid(map::core::String),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("DeleteTempDirectory", typeid(bool), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("CostFunction", typeid(unsigned int), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("DegreesOfFreedom", typeid(unsigned int),
								true, true));
#endif
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::MetaPropertyPointer
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "WorkingDirectory")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_workingDir);
				}
				else if (name == "FlirtDirectory")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_flirtDir);
				}
				else if (name == "DeleteTempDirectory")
				{
					spResult = map::core::MetaProperty<bool>::New(this->_deleteTempDirectory);
				}
				else if (name == "CostFunction")
				{
					spResult = map::core::MetaProperty<unsigned int>::New(static_cast<unsigned int>(this->_costFnc));
				}
				else if (name == "DegreesOfFreedom")
				{
					spResult = map::core::MetaProperty<unsigned int>::New(static_cast<unsigned int>(this->_dof));
				}
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}

				return spResult;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "WorkingDirectory")
				{
					core::String dir;
					map::core::unwrapMetaProperty(pProperty, dir);
					this->_workingDir = dir;
				}
				else if (name == "FlirtDirectory")
				{
					core::String dir;
					map::core::unwrapMetaProperty(pProperty, dir);
					this->_flirtDir = dir;
				}
				else if (name == "DeleteTempDirectory")
				{
					bool del;
					map::core::unwrapMetaProperty(pProperty, del);
					this->_deleteTempDirectory = del;
				}
				else if (name == "CostFunction")
				{
					unsigned int temp;
					map::core::unwrapMetaProperty(pProperty, temp);
					this->_costFnc = static_cast<CostFunction::Type>(temp);
				}
				else if (name == "DegreesOfFreedom")
				{
					unsigned int temp;
					map::core::unwrapMetaProperty(pProperty, temp);
					this->_dof = static_cast<DegreesOfFreedom::Type>(temp);
				}
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::InterimRegistrationPointer
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			determineInterimRegistration(const MovingRepresentationDescriptorType* pMovingRepresentation,
										 const TargetRepresentationDescriptorType* pTargetRepresentation) const
			{
				InterimRegistrationPointer spResult = NULL;
				return spResult;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doStopAlgorithm()
			{
				assert(false);

				mapExceptionMacro(AlgorithmException,
								  << "Cannot stop FSL algorithm. Interim stop feature is not supported. Wrong usage of iterative algorithm interface");
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			initializeCurrentTempDir()
			{
				srand(time(NULL));
				core::OStringStream stream;
				stream << itksys::SystemTools::GetCurrentDateTime("%Y-%m-%d_%H-%M-%S") << "_#" << rand();
				core::String currentTempDir = core::FileDispatch::createFullPath(_workingDir, stream.str());

				if (!itksys::SystemTools::MakeDirectory(currentTempDir.c_str()))
				{
					mapExceptionMacro(AlgorithmException,
									  << "Cannot create temporary working sub dir. Please check validity of given working dir and ensure right priviledges for the application. Failed temporary sub dir: "
									  << _currentTempDir);
				}

				_currentTempDir = currentTempDir;

			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			prepareAlgorithm()
			{
				try
				{
					if (!this->getMovingImage())
					{
						mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no moving image.");
					}

					if (!this->getTargetImage())
					{
						mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no target image.");
					}

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
					typedef typename
					io::ImageWriter<typename TMovingImage::PixelType, typename TMovingImage::PixelType, TMovingImage::ImageDimension>
					MovingWriterType;
					typedef typename
					io::ImageWriter<typename TTargetImage::PixelType, typename TTargetImage::PixelType, TTargetImage::ImageDimension>
					TargetWriterType;
					typename MovingWriterType::Pointer spMWriter = MovingWriterType::New();
					typename TargetWriterType::Pointer spTWriter = TargetWriterType::New();

					_movingImageTempPath = core::FileDispatch::createFullPath(_currentTempDir, "moving.nii");
					_targetImageTempPath = core::FileDispatch::createFullPath(_currentTempDir, "target.nii");
					_resultMatrixTempPath = core::FileDispatch::createFullPath(_currentTempDir, "result.mat");

					spMWriter->setInput(_spInternalMovingImage);
					spTWriter->setInput(_spInternalTargetImage);
					spMWriter->setFilePath(_movingImageTempPath);
					spTWriter->setFilePath(_targetImageTempPath);
					this->InvokeEvent(events::AlgorithmEvent(this,
									  "Write temporary moving image. Path: " + _movingImageTempPath));
					spMWriter->update();
					this->InvokeEvent(events::AlgorithmEvent(this,
									  "Write temporary target image. Path: " + _targetImageTempPath));
					spTWriter->update();
				}
				catch (...)
				{
					cleanTempDir();
					throw;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
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
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			prepPerpareInternalInputData()
			{
				//default implementation does nothing
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			runAlgorithm()
			{
				map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();

				typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
				spCommand->SetCallbackFunction(this, &Self::onFSLOutputEvent);
				spExec->AddObserver(map::events::ExternalProcessStdOutEvent(), spCommand);

				map::utilities::ProcessExecutor::ArgumentListType args;
				args.push_back("-in");
				args.push_back(_movingImageTempPath);
				args.push_back("-ref");
				args.push_back(_targetImageTempPath);
				args.push_back("-omat");
				args.push_back(_resultMatrixTempPath);
				args.push_back("-out");
				args.push_back(_resultMatrixTempPath + ".nii");

				switch (_dof)
				{
					case DegreesOfFreedom::DoF6:
					{
						args.push_back("-dof");
						args.push_back("6");
						break;
					}

					case DegreesOfFreedom::DoF7:
					{
						args.push_back("-dof");
						args.push_back("7");
						break;
					}

					case DegreesOfFreedom::DoF9:
					{
						args.push_back("-dof");
						args.push_back("9");
						break;
					}

					case DegreesOfFreedom::DoF2D:
					{
						args.push_back("-2D");
						break;
					}

					default:
					{
						if (TTargetImage::ImageDimension == 2)
						{
							args.push_back("-2D");
						}
						else
						{
							args.push_back("-dof");
							args.push_back("12");
						}
					}
				};

				switch (_costFnc)
				{
					case CostFunction::LeastSquares:
					{
						args.push_back("-cost");
						args.push_back("leastsq");
						break;
					}

					case CostFunction::NormalisedCorrelation:
					{
						args.push_back("-cost");
						args.push_back("normcorr");
						break;
					}

					case CostFunction::MutualInformation:
					{
						args.push_back("-cost");
						args.push_back("mutualinfo");
						break;
					}

					case CostFunction::NormalisedMutualInformation:
					{
						args.push_back("-cost");
						args.push_back("normmi");
						break;
					}

					default:
					{
						args.push_back("-cost");
						args.push_back("corratio");
					}
				};

				if (!spExec->execute(_flirtDir, core::FileDispatch::createFullPath(_flirtDir, "flirt"), args))
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error when executing flirt to determine the registration.");
				}

				return spExec->getExitValue() == 0;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			finalizeAlgorithm()
			{
				try
				{
					RegistrationPointer spResult = NULL;

					typedef MatrixConverter<TTargetImage::ImageDimension> MatrixConverterType;
					typename ModelType::Pointer spFinalTransformModel = ModelType::New();

					typename MatrixConverterType::MatrixType fslMatrix;

					try
					{
						fslMatrix = readFSLMatrixFromFile<TTargetImage::ImageDimension>(_resultMatrixTempPath.c_str());
					}
					catch (map::core::ExceptionObject& e)
					{
						mapExceptionMacro(AlgorithmException, << e.GetDescription());
					}
					catch (...)
					{
						mapExceptionMacro(AlgorithmException,
										  << "Unkown error while reading fsl matrix file. Path: " << _resultMatrixTempPath);
					}

					typename Superclass::MovingRepresentationDescriptorType::Pointer movingRep =
						core::createFieldRepresentation(*(this->_spInternalMovingImage));
					typename Superclass::TargetRepresentationDescriptorType::Pointer targetRep =
						core::createFieldRepresentation(*(this->_spInternalTargetImage));

					typename MatrixConverterType::MatrixType tmpMatrix = MatrixConverterType::convertFSLToRAS(fslMatrix,
							targetRep, movingRep);
					tmpMatrix = MatrixConverterType::convertRASToITKTrans(tmpMatrix);

					typename ModelType::TransformType::ParametersType params =
						convertMatrixToAffineTransformParams<TTargetImage::ImageDimension>(tmpMatrix);

					//set the parameter of the final transform model to the final transform parameters of the algorithm
					//We set the parameter by Value and not by using SetParameter() because otherwise
					//it could cause errors with itk transforms that only keep a pointer to their parameters (e.g. itk::BSplineDeformableTransform).
					//This transforms would be invalid as soon as we leave this method.
					spFinalTransformModel->getTransform()->SetParametersByValue(params);

					//now build the inverse kernel (main kernel of an image based registration algorithm)
					typedef core::ModelBasedRegistrationKernel<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions>
					InverseKernelType;

					typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
					spIKernel->setTransformModel(spFinalTransformModel);

					//now build the direct kernel via inversion of the inverse kernel
					typedef core::InverseRegistrationKernelGenerator<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions>
					GeneratorType;
					typename GeneratorType::Pointer spGenerator = GeneratorType::New();
					typedef typename GeneratorType::InverseKernelBaseType DirectKernelType;
					typename DirectKernelType::Pointer spDKernel = spGenerator->generateInverse(*
							(spIKernel.GetPointer()), this->getMovingRepresentation());

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
					_finalizedTransformParameters = params;
				}

				catch (...)
				{
					//delete temp dir even in case of an exception
					cleanTempDir();
					throw;
				}

				this->cleanTempDir();
				_currentTempDir = "";
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::RegistrationPointer
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetRegistration() const
			{
				return _spFinalizedRegistration;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
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
			typename FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::OptimizerMeasureType
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetCurrentOptimizerValue() const
			{
				OptimizerMeasureType result;

				return result;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			PrintSelf(std::ostream& os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::PrintSelf(os, indent);

				os << indent << "Finalized transform parameters: " << _finalizedTransformParameters << std::endl;
				os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			onFSLOutputEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				const events::ExternalProcessStdOutEvent* pItEvent =
					dynamic_cast<const events::ExternalProcessStdOutEvent*>(&eventObject);

				if (pItEvent)
				{
					this->InvokeEvent(events::AlgorithmIterationEvent(this, pItEvent->getComment()));
				}
			}

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
