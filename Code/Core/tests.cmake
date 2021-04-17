SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)

SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)
SET(EXAMPLES_DATA_ROOT "${MatchPoint_SOURCE_DIR}/Examples/Data")

#-----------------------------------------------------------------------------
ADD_TEST(mapLogbookTest ${MODULE_TESTS} mapLogbookTest "${TEMP}/logbook_test.log")
ADD_TEST(mapPMVolumeTest ${MODULE_TESTS} mapPMVolumeTest)
ADD_TEST(mapVolumeSizeTest ${MODULE_TESTS} mapVolumeSizeTest)
ADD_TEST(mapFileDispatchTest ${MODULE_TESTS} mapFileDispatchTest)
ADD_TEST(mapExceptionObjectMacrosTest ${MODULE_TESTS} mapExceptionObjectMacrosTest)
ADD_TEST(mapFieldRepresentationDescriptorTest ${MODULE_TESTS} mapFieldRepresentationDescriptorTest)
ADD_TEST(mapRegistrationBaseTest ${MODULE_TESTS} mapRegistrationBaseTest)
ADD_TEST(mapRegistrationTest ${MODULE_TESTS} mapRegistrationTest)
ADD_TEST(mapAffineMatrixDecomposerTest ${MODULE_TESTS} mapAffineMatrixDecomposerTest)
ADD_TEST(mapPreCachedRegistrationKernelTest ${MODULE_TESTS} mapPreCachedRegistrationKernelTest)
ADD_TEST(mapServiceStackTest ${MODULE_TESTS} mapServiceStackTest)
ADD_TEST(mapGenericStaticLoadPolicyTest ${MODULE_TESTS} mapGenericStaticLoadPolicyTest)
ADD_TEST(mapStaticServiceStackTest ${MODULE_TESTS} mapStaticServiceStackTest)
ADD_TEST(mapFieldGenerationFunctorTest ${MODULE_TESTS} mapFieldGenerationFunctorTest)
ADD_TEST(mapLazyRegistrationKernelTest ${MODULE_TESTS} mapLazyRegistrationKernelTest)
ADD_TEST(mapFieldByModelFunctorTest ${MODULE_TESTS} mapFieldByModelFunctorTest)
ADD_TEST(mapFieldByModelInversionFunctorTest ${MODULE_TESTS} mapFieldByModelInversionFunctorTest 40 0.1 0.1)
ADD_TEST(mapFieldByFieldInversionFunctorTest ${MODULE_TESTS} mapFieldByFieldInversionFunctorTest 40 0.1 0.1)
ADD_TEST(mapPointVectorCombinationPolicyTest ${MODULE_TESTS} mapPointVectorCombinationPolicyTest)
ADD_TEST(mapCombinationFunctorInterfaceTest ${MODULE_TESTS} mapCombinationFunctorInterfaceTest)
ADD_TEST(mapFieldByFileLoadFunctorTest ${MODULE_TESTS} mapFieldByFileLoadFunctorTest "${TEST_DATA_ROOT}/Core/mapTestField.mhd")
ADD_TEST(mapGenericFieldGeneratingCombinationFunctorTest ${MODULE_TESTS} mapGenericFieldGeneratingCombinationFunctorTest)
ADD_TEST(mapGenericKernelCombiningFieldSourceTest ${MODULE_TESTS} mapGenericKernelCombiningFieldSourceTest)
ADD_TEST(mapRegistrationKernelTest ${MODULE_TESTS} mapRegistrationKernelTest)
ADD_TEST(mapCombinedRegistrationKernelTest ${MODULE_TESTS} mapCombinedRegistrationKernelTest)
ADD_TEST(mapDefaultKernelInverterTest ${MODULE_TESTS} mapDefaultKernelInverterTest)
ADD_TEST(mapInverseRegistrationKernelGeneratorTest ${MODULE_TESTS} mapInverseRegistrationKernelGeneratorTest)
ADD_TEST(mapInvertingRegistrationKernelTest ${MODULE_TESTS} mapInvertingRegistrationKernelTest)
ADD_TEST(mapRegistrationCombinationRequestTest ${MODULE_TESTS} mapRegistrationCombinationRequestTest)
ADD_TEST(mapRegistrationKernelCombinatorBaseTest ${MODULE_TESTS} mapRegistrationKernelCombinatorBaseTest)
ADD_TEST(mapLazyFieldKernelCombinatorTest ${MODULE_TESTS} mapLazyFieldKernelCombinatorTest)
ADD_TEST(mapPreCachedKernelCombinatorTest ${MODULE_TESTS} mapPreCachedKernelCombinatorTest)
ADD_TEST(mapRegistrationCombinatorTest ${MODULE_TESTS} mapRegistrationCombinatorTest)
ADD_TEST(mapPointSetMappingPerformerRequestTest ${MODULE_TESTS} mapPointSetMappingPerformerRequestTest)
ADD_TEST(mapImageMappingPerformerRequestTest ${MODULE_TESTS} mapImageMappingPerformerRequestTest)
ADD_TEST(mapPointSetByModelPerformerTest ${MODULE_TESTS} mapPointSetByModelPerformerTest)
ADD_TEST(mapImageByModelPerformerTest ${MODULE_TESTS} mapImageByModelPerformerTest "${TEST_DATA_ROOT}/Core/mapTestImage.png" "${TEST_DATA_ROOT}/Core/mapTestImage_X15Y10.png" 1e-11 "${TEMP}/mapImageByModelPerformerTest")
ADD_TEST(mapMappingTaskBaseTest ${MODULE_TESTS} mapMappingTaskBaseTest)
ADD_TEST(mapPointSetMappingTaskTest ${MODULE_TESTS} mapPointSetMappingTaskTest)
ADD_TEST(mapImageMappingTaskTest ${MODULE_TESTS} mapImageMappingTaskTest)
ADD_TEST(mapMappingTaskBatchTest ${MODULE_TESTS} mapMappingTaskBatchTest)
ADD_TEST(mapMetaPropertyTest ${MODULE_TESTS} mapMetaPropertyTest)
ADD_TEST(mapSmartMetaPropertyTest ${MODULE_TESTS} mapSmartMetaPropertyTest)
ADD_TEST(mapMetaPropertyAccessInterfaceTest ${MODULE_TESTS} mapMetaPropertyAccessInterfaceTest)
ADD_TEST(mapMetaPropertyAccessorTest ${MODULE_TESTS} mapMetaPropertyAccessorTest)
ADD_TEST(mapSDElementTest ${MODULE_TESTS} mapSDElementTest)
ADD_TEST(mapSDXMLStrReaderTest ${MODULE_TESTS} mapSDXMLStrReaderTest)
ADD_TEST(mapSDXMLFileReaderTest ${MODULE_TESTS} mapSDXMLFileReaderTest ${TEST_DATA_ROOT}/Core)
ADD_TEST(mapSDXMLStrWriterTest ${MODULE_TESTS} mapSDXMLStrWriterTest)

IF(NOT UNIX)
	ADD_TEST(mapSDXMLFileWriterTest ${MODULE_TESTS} mapSDXMLFileWriterTest ${TEMP} ${TEST_DATA_ROOT}/Core/XMLFileWriteReference.xml ${TEST_DATA_ROOT}/Core/XMLFileWriteReference_withXSLT.xml)
ENDIF(NOT UNIX)
ADD_TEST(mapModificationTimeValidatorTest ${MODULE_TESTS} mapModificationTimeValidatorTest)
