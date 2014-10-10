SET(CPP_FILES 
  source/mapConvert.cpp
  source/mapDimensionlessRegistrationKernelBase.cpp  
  source/mapXMLLogger.cpp
  source/mapLogbook.cpp
  source/mapLogbookImplementation.cpp
  source/mapExceptionObject.cpp
  source/mapPMVolume.cpp
  source/mapRegistrationBase.cpp
  source/mapRegistrationException.cpp
  source/mapRepresentationException.cpp
  source/mapServiceException.cpp
  source/mapMissingProviderException.cpp
  source/mapMappingException.cpp
  source/mapEvents.cpp
  source/mapThreadEvents.cpp
  source/mapObserverSentinel.cpp
  source/mapMetaPropertyBase.cpp
  source/mapFileDispatch.cpp
  source/mapModificationTimeValidator.cpp
  source/mapSyncObject.cpp  
  source/mapSDExceptions.cpp
  source/mapSDElement.cpp
  source/mapSDXMLStrReader.cpp
  source/mapSDStreamingInterface.cpp
  source/mapSDXMLFileReader.cpp
  source/mapSDXMLFileWriter.cpp
  source/mapSDXMLStrWriter.cpp
  source/mapFastLockedThreadingPolicy.cpp
  source/mapSingleThreadedThreadingPolicy.cpp
  source/mapFastLockedThreadingStaticPolicy.cpp
  source/mapFastMutexLockSentinel.cpp
)

SET(H_FILES 
	include/mapAffineMatrixDecomposer.h
    include/mapConvert.h
	include/mapClassMacros.h
	include/mapCombinedFieldBasedRegistrationKernel.h
	include/mapConcreteFieldBasedRegistrationKernel.h
	include/mapContinuous.h
	include/mapContinuousElements.h
	include/mapDefaultRegistrationTopologyPolicy.h
	include/mapDimensionlessRegistrationKernelBase.h
	include/mapDiscrete.h
	include/mapDiscreteElements.h
	include/mapEvents.h
	include/mapExceptionObject.h
	include/mapExceptionObjectMacros.h
	include/mapFieldBasedKernelInverter.h
	include/mapFieldBasedRegistrationKernel.h
	include/mapFieldBasedRegistrationKernelInterface.h
	include/mapFieldBasedRegistrationKernels.h
	include/mapFieldFieldKernelCombinator.h
	include/mapFieldModelKernelCombinator.h
	include/mapFieldRepresentationDescriptor.h
	include/mapFileDispatch.h
	include/mapImageByFieldPerformer.h
	include/mapImageByModelPerformer.h
	include/mapImageMappingPerformerBase.h
	include/mapImageMappingPerformerLoadPolicy.h
	include/mapImageMappingPerformerRequest.h
	include/mapImageMappingTask.h
	include/mapInverseRegistrationKernelGenerator.h
	include/mapInvertingFieldBasedRegistrationKernel.h
	include/mapITKDimensionedTransformModel.h
	include/mapITKUnaryTransformModel.h
	include/mapKernelCombinatorLoadPolicy.h
	include/mapKernelInverterLoadPolicy.h
	include/mapLazyFieldPolicy.h
	include/mapLogbook.h
	include/mapLogbookImplementation.h
	include/mapLogbookMacros.h
	include/mapMacros.h
	include/mapMappingException.h
	include/mapMappingPerformerBase.h
	include/mapMappingPerformerRequestBase.h
	include/mapMappingTaskBase.h
	include/mapMappingTaskBatch.h
	include/mapMappingTaskBatchThread.h
	include/mapMetaProperty.h
	include/mapMetaPropertyAccessInterface.h
	include/mapMetaPropertyAccessor.h
	include/mapMetaPropertyBase.h
	include/mapMissingProviderException.h
	include/mapModelBasedKernelInverter.h
	include/mapModelBasedRegistrationKernel.h
	include/mapModelBasedRegistrationKernelInterface.h
	include/mapModelFieldKernelCombinator.h
	include/mapModelModelKernelCombinator.h
	include/mapModificationTimeValidator.h
	include/mapNoneMappingPerformerLoadPolicy.h
	include/mapNullRegistrationKernel.h
	include/mapNullRegistrationKernelCombinator.h
	include/mapNullRegistrationKernelInverter.h
	include/mapObserverSentinel.h
	include/mapPMVolume.h
	include/mapPointSetByFieldPerformer.h
	include/mapPointSetByModelPerformer.h
	include/mapPointSetMappingPerformerLoadPolicy.h
	include/mapPointSetMappingPerformerRequest.h
	include/mapPointSetMappingTask.h
	include/mapPointVectorCombinationPolicy.h
	include/mapPreCachedFieldPolicy.h
	include/mapRegistration.h
	include/mapRegistrationBase.h
	include/mapRegistrationCombinationRequest.h
	include/mapRegistrationCombinator.h
	include/mapRegistrationException.h
	include/mapRegistrationKernelBase.h
	include/mapRegistrationKernelCombinatorBase.h
	include/mapRegistrationKernelInverterBase.h
	include/mapRegistrationManipulator.h
	include/mapRegistrationTopology.h
	include/mapRepresentationException.h
	include/mapServiceException.h
	include/mapSmartMetaProperty.h
	include/mapString.h
	include/mapThreadEvents.h
#	include/mapTransformModel.h
	include/mapTransformModelBase.h
	include/mapVolume.h
	include/mapVolumeSize.h
	include/mapWin32Header.h
	include/mapXMLLogger.h
	include/mapSyncObject.h
	include/mapSyncInterface.h
    include/mapSDExceptions.h
    include/mapSDElement.h
	include/mapSDITKStreamingHelper.h
    include/mapSDXMLStrReader.h
    include/mapSDStreamingInterface.h
    include/mapSDXMLFileReader.h
    include/mapSDXMLFileWriter.h
    include/mapSDXMLStrWriter.h
    include/mapSDTags.h
    include/mapServiceProvider.h
    include/mapServiceStack.h
    include/mapNoneStaticLoadPolicy.h
    include/mapServiceRepositoryPolicyLoadInterface.h
    include/mapGenericStaticLoadPolicyBase.h
    include/mapFastLockedThreadingPolicy.h
    include/mapSingleThreadedThreadingPolicy.h
    include/mapStaticServiceStack.h
    include/mapDefaultSLStaticPolicy.h
    include/mapFastLockedThreadingStaticPolicy.h
    include/mapFastMutexLockSentinel.h
    include/mapFieldGenerationFunctor.h
    include/mapFieldByModelFunctor.h
    include/mapFieldByModelInversionFunctor.h
    include/mapFieldByFieldInversionFunctor.h
    include/mapFieldCombinationFunctorInterface.h
    include/mapFieldByModelFieldCombinationFunctor.h
    include/mapFieldByFieldModelCombinationFunctor.h
    include/mapFieldByFieldFieldCombinationFunctor.h
    include/mapFieldByFileLoadFunctor.h    
)

SET(TPP_FILES
	include/mapAffineMatrixDecomposer.tpp
	include/mapCombinedFieldBasedRegistrationKernel.tpp
	include/mapConcreteFieldBasedRegistrationKernel.tpp
	include/mapFieldBasedKernelInverter.tpp
	include/mapFieldFieldKernelCombinator.tpp
	include/mapFieldModelKernelCombinator.tpp
	include/mapFieldRepresentationDescriptor.tpp
	include/mapImageByFieldPerformer.tpp
	include/mapImageByModelPerformer.tpp
	include/mapImageMappingPerformerBase.tpp
	include/mapImageMappingPerformerLoadPolicy.tpp
	include/mapImageMappingPerformerRequest.tpp
	include/mapImageMappingTask.tpp
	include/mapInverseRegistrationKernelGenerator.tpp
	include/mapInvertingFieldBasedRegistrationKernel.tpp
	include/mapITKDimensionedTransformModel.tpp
	include/mapITKUnaryTransformModel.tpp
	include/mapKernelCombinatorLoadPolicy.tpp
	include/mapKernelInverterLoadPolicy.tpp
	include/mapLazyFieldPolicy.tpp
	include/mapMappingPerformerRequestBase.tpp
	include/mapMappingTaskBase.tpp
	include/mapMappingTaskBatch.tpp
	include/mapMappingTaskBatchThread.tpp
	include/mapMetaProperty.tpp
	include/mapMetaPropertyAccessor.tpp
	include/mapModelBasedKernelInverter.tpp
	include/mapModelBasedRegistrationKernel.tpp
	include/mapModelFieldKernelCombinator.tpp
	include/mapModelModelKernelCombinator.tpp
	include/mapNoneMappingPerformerLoadPolicy.tpp
	include/mapNullRegistrationKernel.tpp
	include/mapNullRegistrationKernelCombinator.tpp
	include/mapNullRegistrationKernelInverter.tpp
	include/mapPointSetByFieldPerformer.tpp
	include/mapPointSetByModelPerformer.tpp
	include/mapPointSetMappingPerformerLoadPolicy.tpp
	include/mapPointSetMappingPerformerRequest.tpp
	include/mapPointSetMappingTask.tpp
	include/mapPreCachedFieldPolicy.tpp
	include/mapRegistration.tpp
	include/mapRegistrationCombinationRequest.tpp
	include/mapRegistrationCombinator.tpp
	include/mapRegistrationKernelBase.tpp
	include/mapRegistrationKernelCombinatorBase.tpp
	include/mapRegistrationManipulator.tpp
	include/mapSmartMetaProperty.tpp
#	include/mapTransformModel.tpp
	include/mapTransformModelBase.tpp
	include/mapVolume.tpp
	include/mapVolumeSize.tpp
    include/mapServiceStack.tpp
    include/mapNoneStaticLoadPolicy.tpp
    include/mapGenericStaticLoadPolicyBase.tpp
    include/mapStaticServiceStack.tpp
    include/mapDefaultSLStaticPolicy.tpp	
    include/mapFieldGenerationFunctor.tpp
    include/mapFieldByModelFunctor.tpp
    include/mapFieldByModelInversionFunctor.tpp
    include/mapFieldByFieldInversionFunctor.tpp
    include/mapFieldCombinationFunctorInterface.tpp
    include/mapFieldByModelFieldCombinationFunctor.tpp
    include/mapFieldByFieldModelCombinationFunctor.tpp
    include/mapFieldByFieldFieldCombinationFunctor.tpp
    include/mapFieldByFileLoadFunctor.tpp  
)

SET( TEST_CPP_FILES
test/mapCoreTests.cpp
test/mapLogbookTest.cpp
test/mapPMVolumeTest.cpp
test/mapVolumeSizeTest.cpp
test/mapFileDispatchTest.cpp
test/mapFieldRepresentationDescriptorTest.cpp
test/mapExceptionObjectMacrosTest.cpp
test/mapRegistrationBaseTest.cpp
test/mapRegistrationTest.cpp
test/mapModelBasedRegistrationKernelTest.cpp
test/mapPreCachedFieldBasedRegistrationKernelTest.cpp
test/mapServiceStackTest.cpp
test/mapTestServiceProvider.h
test/mapTestLoadPolicy.h
test/mapGenericStaticLoadPolicyTest.cpp
test/mapStaticServiceStackTest.cpp
test/mapTestFieldGenerationFunctor.h
test/mapFieldGenerationFunctorTest.cpp
test/mapLazyFieldBasedRegistrationKernelTest.cpp
test/mapFieldByModelFunctorTest.cpp
test/mapFieldByModelInversionFunctorTest.cpp
test/mapFieldByFieldInversionFunctorTest.cpp
test/mapFieldByModelFieldCombinationFunctorTest.cpp
test/mapFieldByFileLoadFunctorTest.cpp
test/mapPointVectorCombinationPolicyTest.cpp
test/mapFieldCombinationFunctorInterfaceTest.cpp
test/mapFieldByFieldModelCombinationFunctorTest.cpp
test/mapFieldByFieldFieldCombinationFunctorTest.cpp
test/mapCombinedFieldBasedRegistrationKernelTest.cpp
test/mapConcreteFieldBasedRegistrationKernelTest.cpp
test/mapModelBasedKernelInverterTest.cpp
test/mapFieldBasedKernelInverterTest.cpp
test/mapInverseRegistrationKernelGeneratorTest.cpp
test/mapInvertingFieldBasedRegistrationKernelTest.cpp
test/mapRegistrationCombinationRequestTest.cpp
test/mapRegistrationKernelCombinatorBaseTest.cpp
test/mapFieldFieldKernelCombinatorTest.cpp
test/mapModelFieldKernelCombinatorTest.cpp
test/mapFieldModelKernelCombinatorTest.cpp
test/mapModelModelKernelCombinatorTest.cpp
test/mapRegistrationCombinatorTest.cpp
test/mapTestKernelBase.h
test/mapPointSetMappingPerformerRequestTest.cpp
test/mapImageMappingPerformerRequestTest.cpp
test/mapPointSetByModelPerformerTest.cpp
test/mapPointSetByFieldPerformerTest.cpp
test/mapImageByModelPerformerTest.cpp
test/mapImageByFieldPerformerTest.cpp
test/mapTestMappingTask.h
test/mapMappingTaskBaseTest.cpp
test/mapTestMappingPerformer.h
test/mapPointSetMappingTaskTest.cpp
test/mapImageMappingTaskTest.cpp
test/mapMappingTaskBatchTest.cpp
test/mapMetaPropertyTest.cpp
test/mapSmartMetaPropertyTest.cpp
test/mapMetaPropertyAccessInterfaceTest.cpp
test/mapMetaPropertyAccessorTest.cpp
test/mapAffineMatrixDecomposerTest.cpp
test/mapSDElementTest.cpp
test/mapSDXMLStrReaderTest.cpp
test/mapSDXMLFileReaderTest.cxx
test/mapSDXMLStrWriterTest.cxx
test/mapSDXMLFileWriterTest.cxx
test/mapArtifactGenerator.h
test/mapArtifactGenerator.cpp
test/mapModificationTimeValidatorTest.cpp
)