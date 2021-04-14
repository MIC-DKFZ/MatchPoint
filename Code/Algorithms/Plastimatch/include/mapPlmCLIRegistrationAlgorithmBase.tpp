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
#include "mapPreCachedRegistrationKernel.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"
#include "mapImageWriter.h"
#include "mapProcessExecutor.h"
#include "mapConvert.h"
#include "mapMetaProperty.h"
#include "mapString.h"
#include "mapFieldByFileLoadFunctor.h"
#include "mapFieldDecomposer.h"
#include "mapSimpleLandMarkFileWriter.h"

namespace map
{
    namespace algorithm
    {
        namespace plastimatch
        {


          template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
          ::itk::ModifiedTimeType
            CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
            getNthTargetPointSetMTime(SlotIndexType index) const
          {
            return _targetPSMTime.getMTime();
          };

          template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
          ::itk::ModifiedTimeType
            CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
            getNthMovingPointSetMTime(SlotIndexType index) const
          {
            return _movingPSMTime.getMTime();
          };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::FieldRepRequirement::Type
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                isMovingRepresentationRequired() const
            {
                return FieldRepRequirement::No;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::FieldRepRequirement::Type
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                isTargetRepresentationRequired() const
            {
                return FieldRepRequirement::No;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            bool
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                isStoppable() const
            {
                return false;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::IterationCountType
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                doGetCurrentIteration() const
            {
                return 0;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::IterationCountType
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                doGetMaxIterations() const
            {
                return 0;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            bool
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                hasIterationCount() const
            {
                return false;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            bool
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                hasMaxIterationCount() const
            {
                return false;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            bool
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                hasCurrentOptimizerValue() const
            {
                return false;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                CLIRegistrationAlgorithmBase() : _deleteTempDirectory(true)
            {
                _spInternalMovingImage = NULL;
                _spInternalTargetImage = NULL;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                ~CLIRegistrationAlgorithmBase()
            {
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            bool
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                isReusable() const
            {
                return true;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                configureAlgorithm()
            {
                if (this->isFirstConfiguration())
                {
                    _plastimatchDir = "";
                    ::map::core::String envDir = "";

                    if (itksys::SystemTools::GetEnv("MAP_PLASTIMATCH_PATH", envDir))
                    {
                        _plastimatchDir = envDir;
                    }

                    _workingDir = itksys::SystemTools::GetCurrentWorkingDirectory();

                    _deleteTempDirectory = true;
                }
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
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

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::MetaPropertyPointer
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
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

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
            {
                if (name == "WorkingDirectory")
                {
                    ::map::core::String dir;
                    map::core::unwrapMetaProperty(pProperty, dir);
                    this->_workingDir = dir;
                }
                else if (name == "PlastimatchDirectory")
                {
                    ::map::core::String dir;
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

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::InterimRegistrationPointer
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                determineInterimRegistration(const MovingRepresentationDescriptorType* pMovingRepresentation,
                const TargetRepresentationDescriptorType* pTargetRepresentation) const
            {
                InterimRegistrationPointer spResult = NULL;
                return spResult;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            bool
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                doStopAlgorithm()
            {
                assert(false);

                mapExceptionMacro(AlgorithmException,
                    << "Cannot stop Plastimatch algorithm. Interim stop feature is not supported. Wrong usage of iterative algorithm interface");
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                initializeCurrentTempDir()
            {
                srand(time(NULL));
                ::map::core::OStringStream stream;
                stream << itksys::SystemTools::GetCurrentDateTime("%Y-%m-%d_%H-%M-%S") << "_#" << rand();
                ::map::core::String currentTempDir = core::FileDispatch::createFullPath(_workingDir, stream.str());

                if (!itksys::SystemTools::MakeDirectory(currentTempDir.c_str()))
                {
                    mapExceptionMacro(AlgorithmException,
                        << "Cannot create temporary working sub dir. Please check validity of given working dir and ensure right privileges for the application. Failed temporary sub dir: "
                        << _currentTempDir);
                }

                _currentTempDir = currentTempDir;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                prepareAlgorithm()
            {
                try
                {
                    this->prepCheckValidity();

                    this->_spFinalizedRegistration = NULL;

                    //initialize registration components
                    this->InvokeEvent(::map::events::AlgorithmEvent(this, "Transfer cached MetaProperties."));
                    this->configureAlgorithmByMetaProperties();

                    this->InvokeEvent(::map::events::AlgorithmEvent(this, "Initializing registration."));
                    this->initializeCurrentTempDir();

                    //preparing data
                    this->InvokeEvent(::map::events::AlgorithmEvent(this, "Initializing/Preparing input data."));
                    _spInternalMovingImage = this->getMovingImage();
                    _spInternalTargetImage = this->getTargetImage();

                    this->prepPerpareInternalInputData();

                    //storing temporary images
                    this->InvokeEvent(::map::events::AlgorithmEvent(this,
                        "Passing input data to plastimatch working directory."));
                    this->prepSavePlastimatchInputData();

                    this->InvokeEvent(::map::events::AlgorithmEvent(this, "Generating parameter maps for plastimatch."));
                    this->prepConfigurationPLM();
                    this->ensureCorrectGlobalConfigSettings();

                    this->InvokeEvent(::map::events::AlgorithmEvent(this, "Store plastimatch configuration."));
                    saveConfigurationToFile(this->_configurationPLM, this->getParameterFilePath());
                }
                catch (...)
                {
                    cleanTempDir();
                    throw;
                }
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
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
                    mapLogWarningObjMacro(<< "Cannot clean up. Exception while removing the directory. Directory" <<
                        this->_currentTempDir);
                }
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
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


            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                prepPerpareInternalInputData()
            {
                //default implementation does nothing
            }


            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
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

                if (this->getMovingPointSet().IsNotNull())
                {
                  //add moving mask
                  checkedConfig[0]["moving_landmarks"] = plastimatch::ParamGenerator().add(this->_movingPointSetTempPath);
                }

                if (this->getTargetPointSet().IsNotNull())
                {
                  //add target mask
                  checkedConfig[0]["fixed_landmarks"] = plastimatch::ParamGenerator().add(this->_targetPointSetTempPath);
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
                    ::map::io::ImageWriter < typename TImage::PixelType, typename TImage::PixelType, TImage::ImageDimension >
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


            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                prepSavePlastimatchInputData()
            {
                //save the images
                _movingImageTempPath = core::FileDispatch::createFullPath(_currentTempDir, "moving.mhd");
                _targetImageTempPath = core::FileDispatch::createFullPath(_currentTempDir, "target.mhd");
                _finalFieldTempPath = core::FileDispatch::createFullPath(_currentTempDir, "deformationField.mhd");
                _movingMaskTempPath = "";
                _targetMaskTempPath = "";
                _movingPointSetTempPath = "";
                _targetPointSetTempPath = "";

                this->InvokeEvent(::map::events::AlgorithmEvent(this,
                    "Write temporary moving image. Path: " + _movingImageTempPath));
                saveTempImage(_spInternalMovingImage.GetPointer(), _movingImageTempPath);
                this->InvokeEvent(::map::events::AlgorithmEvent(this,
                    "Write temporary target image. Path: " + _targetImageTempPath));
                saveTempImage(_spInternalTargetImage.GetPointer(), _targetImageTempPath);

                //save the masks
                if (this->getMovingMask().IsNotNull())
                {
                    typedef ::itk::Image<unsigned char, TMovingImage::ImageDimension> MaskImageType;
                    typename MaskImageType::Pointer spMovingMaskImage = generateMaskImage<Superclass::MovingDimensions>
                        (this->getMovingMask(), core::createFieldRepresentation(*(_spInternalMovingImage)).GetPointer());

                    _movingMaskTempPath = core::FileDispatch::createFullPath(_currentTempDir, "movingMask.mhd");
                    this->InvokeEvent(::map::events::AlgorithmEvent(this,
                        "Write temporary moving mask image. Path: " + _movingMaskTempPath));
                    saveTempImage(spMovingMaskImage.GetPointer(), _movingMaskTempPath);
                }

                if (this->getTargetMask().IsNotNull())
                {
                    typedef ::itk::Image<unsigned char, TTargetImage::ImageDimension> MaskImageType;
                    typename MaskImageType::Pointer spTargetMaskImage = generateMaskImage<Superclass::TargetDimensions>
                        (this->getTargetMask(), core::createFieldRepresentation(*(_spInternalTargetImage)).GetPointer());

                    _targetMaskTempPath = core::FileDispatch::createFullPath(_currentTempDir, "targetMask.mhd");
                    this->InvokeEvent(::map::events::AlgorithmEvent(this,
                        "Write temporary target mask image. Path: " + _targetMaskTempPath));
                    saveTempImage(spTargetMaskImage.GetPointer(), _targetMaskTempPath);
                }

                //save the pointsets
                if (this->getMovingPointSet().IsNotNull())
                {
                  _movingPointSetTempPath = core::FileDispatch::createFullPath(_currentTempDir, "movingPointSet.txt");
                  this->InvokeEvent(::map::events::AlgorithmEvent(this,
                    "Write temporary moving point set. Path: " + _movingPointSetTempPath));
                  ::map::utilities::saveLandMarksToFile(_movingPointSetTempPath, this->getMovingPointSet().GetPointer());
                }

                if (this->getTargetPointSet().IsNotNull())
                {
                  _targetPointSetTempPath = core::FileDispatch::createFullPath(_currentTempDir, "targetPointSet.txt");
                  this->InvokeEvent(::map::events::AlgorithmEvent(this,
                    "Write temporary target point set. Path: " + _targetPointSetTempPath));
                  ::map::utilities::saveLandMarksToFile(_targetPointSetTempPath, this->getTargetPointSet().GetPointer());
                }

            }

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            bool
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                runAlgorithm()
            {
                map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();

                typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
                spCommand->SetCallbackFunction(this, &Self::onPlmOutputEvent);
                spExec->AddObserver(map::events::ExternalProcessStdOutEvent(), spCommand);

                map::utilities::ProcessExecutor::ArgumentListType args;
                args.push_back("register");
                args.push_back(this->getParameterFilePath());

                ::map::core::OStringStream ostr;
                ostr << "Calling plastimatch (" << _plastimatchDir << ") with arguments:";

                for (map::utilities::ProcessExecutor::ArgumentListType::const_iterator pos = args.begin();
                    pos != args.end(); ++pos)
                {
                    ostr << " " << *pos;
                }

                this->InvokeEvent(::map::events::AlgorithmEvent(this, ostr.str()));

                if (!spExec->execute(_plastimatchDir, core::FileDispatch::createFullPath(_plastimatchDir,
                    "plastimatch"), args))
                {
                    mapExceptionMacro(AlgorithmException,
                        << "Error when executing plastimatch to determine the registration.");
                }

                return spExec->getExitValue() == 0;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::FinalFieldPointer
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                generateField() const
            {
                typedef map::core::functors::FieldByFileLoadFunctor < Superclass::TargetDimensions, Superclass::MovingDimensions >
                    FunctorType;
                typename FunctorType::Pointer spFunctor = FunctorType::New(_finalFieldTempPath);

                FinalFieldPointer spField;

                ::map::core::FieldDecomposer<Superclass::MovingDimensions, Superclass::TargetDimensions>::decomposeTransform(spFunctor->generateTransform(), spField);

                if (spField.IsNull())
                {
                    mapExceptionMacro(AlgorithmException,
                        << "Error when loading Plastimatch deformation field. File name: " << _finalFieldTempPath);
                }

                return spField;
            };


            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            ::map::core::String
                map::algorithm::plastimatch::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                getParameterFilePath() const
            {
                ::map::core::String result = core::FileDispatch::createFullPath(_currentTempDir, "parameters.txt");
                return result;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            ::map::core::String
                map::algorithm::plastimatch::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                getFinalTransformFilePath() const
            {
                if (this->_configurationPLM.empty())
                {
                    mapExceptionMacro(AlgorithmException,
                        << "Cannot determine final transform file path; no parameter maps are defined.");
                }

                ::map::core::OStringStream ostr;
                ostr << "TransformParameters." << this->_configurationPLM.size() - 1 << ".txt";
                ::map::core::String result = core::FileDispatch::createFullPath(_currentTempDir, ostr.str());
                return result;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                finalizeAlgorithm()
            {
                RegistrationPointer spResult = NULL;

                try
                {
                    _spFinalizedField = this->generateField();

                    typedef typename
                        map::core::PreCachedRegistrationKernel<Superclass::TargetDimensions, Superclass::MovingDimensions> InverseKernelType;

                    typename FieldTransformType::Pointer transform = FieldTransformType::New();
                    transform->SetDisplacementField(_spFinalizedField.GetPointer());

                    typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
                    spIKernel->setTransformModel(transform);

                    //now build the direct kernel via inversion of the inverse kernel
                    typedef core::InverseRegistrationKernelGenerator < RegistrationType::TargetDimensions, RegistrationType::MovingDimensions >
                        GeneratorType;
                    typename GeneratorType::Pointer spGenerator = GeneratorType::New();
                    typedef typename GeneratorType::InverseKernelBaseType DirectKernelType;
                    typename Superclass::MovingRepresentationDescriptorType::ConstPointer spMovingRep =
                        ::map::core::createFieldRepresentation(*(this->getMovingImage())).GetPointer();

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
                    ::map::core::RegistrationManipulator<RegistrationType> manipulator(spResult);

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


            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::RegistrationPointer
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                doGetRegistration() const
            {
                return _spFinalizedRegistration;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            bool
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
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
                        outdated = this->_spInternalMovingImage != this->getMovingImage();
                    }

                    if (!outdated)
                    {
                        //check if the inputs have been changed
                        outdated = this->_spInternalTargetImage != this->getTargetImage();
                    }

                    if (!outdated)
                    {
                      outdated = _spFinalizedRegistration->GetMTime() < this->getTargetImageMTime();
                    }
                    if (!outdated)

                    {
                      outdated = _spFinalizedRegistration->GetMTime() < this->getMovingImageMTime();
                    }

                    if (!outdated)
                    {
                      outdated = _spFinalizedRegistration->GetMTime() < this->getTargetPointSetMTime();
                    }

                    if (!outdated)
                    {
                      outdated = _spFinalizedRegistration->GetMTime() < this->getMovingPointSetMTime();
                    }

                    if (!outdated)
                    {
                      outdated = _spFinalizedRegistration->GetMTime() < this->getTargetMaskMTime();
                    }

                    if (!outdated)
                    {
                      outdated = _spFinalizedRegistration->GetMTime() < this->getMovingMaskMTime();
                    }
                }

                return outdated;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::OptimizerMeasureType
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                doGetCurrentOptimizerValue() const
            {
                OptimizerMeasureType result;

                return result;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                PrintSelf(std::ostream& os, ::itk::Indent indent) const
            {
                Superclass::PrintSelf(os, indent);

                ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::PrintSelf(os, indent);

                os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
                CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
                onPlmOutputEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
            {
                const events::ExternalProcessStdOutEvent* pStdEvent =
                    dynamic_cast<const events::ExternalProcessStdOutEvent*>(&eventObject);

                if (pStdEvent)
                {
                    this->InvokeEvent(::map::events::AlgorithmIterationEvent(this, pStdEvent->getComment()));
                }
            }


            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::MovingPointSetConstPointer
              CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
              doGetNthMovingPointSet(SlotIndexType index) const
            {
              return this->_spMovingPointSet;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            typename CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::TargetPointSetConstPointer
              CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
              doGetNthTargetPointSet(SlotIndexType index) const
            {
              return this->_spTargetPointSet;
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
              CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
              doSetNthMovingPointSet(SlotIndexType index, const MovingPointSetType* pMovingPointSet)
            {
              _spMovingPointSet = pMovingPointSet;
              this->_movingPSMTime.setWatchedObject(pMovingPointSet);
            };

            template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
            void
              CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
              doSetNthTargetPointSet(SlotIndexType index, const TargetPointSetType* pTargetPointSet)
            {
              _spTargetPointSet = pTargetPointSet;
              this->_targetPSMTime.setWatchedObject(pTargetPointSet);
            };



        } // end namespace plastimatch
    } // end namespace algorithm
} // end namespace map

#endif
