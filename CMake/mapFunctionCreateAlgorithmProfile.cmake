###################################################################
#
# MAP_CREATE_ALGORITHM_PROFILE 
# 
# This macro is used to generate resources for the algorithm
#
##################################################################
MACRO(MAP_CREATE_XML_ELEMENT XML_TAG XML_CONTENT)
	MESSAGE("Create XML element: ${${XML_CONTENT}}")	
	IF(DEFINED ${XML_CONTENT})
	MESSAGE("defed XML element: ${${XML_CONTENT}}")	
		FOREACH(XML_ELEMENT IN ITEMS ${${XML_CONTENT}})
	MESSAGE("XML element: ${XML_ELEMENT}")	
		
			LIST(APPEND ALGORITHM_PROFILE_XML_Content "<${XML_TAG}>${XML_ELEMENT}</${XML_TAG}>")
		ENDFOREACH(XML_ELEMENT)
	ENDIF(DEFINED ${XML_CONTENT})
ENDMACRO(MAP_CREATE_XML_ELEMENT)

FUNCTION(CREATE_ALGORITHM_PROFILE ALG_NAME_IN PROFILE_FILE_IN)
	INCLUDE(${PROFILE_FILE_IN})

	SET(ALGORITHM_NAME ${ALG_NAME_IN})
	SET(ALGORITHM_PROFILE_UID "${ALGORITHM_PROFILE_UID_Namespace}::${ALGORITHM_PROFILE_UID_Name}::${ALGORITHM_PROFILE_UID_Version}" PARENT_SCOPE)
	SET(ALGORITHM_PROFILE_UID "${ALGORITHM_PROFILE_UID_Namespace}::${ALGORITHM_PROFILE_UID_Name}::${ALGORITHM_PROFILE_UID_Version}")
	SET(ALGORITHM_PROFILE_FILE "${CMAKE_CURRENT_BINARY_DIR}/${ALG_NAME_IN}_ProfileResource.h" PARENT_SCOPE)
	SET(ALGORITHM_PROFILE_FILE "${CMAKE_CURRENT_BINARY_DIR}/${ALG_NAME_IN}_ProfileResource.h")
	SET(ALGORITHM_PROFILE_XML_FILE "${CMAKE_CURRENT_BINARY_DIR}/${ALG_NAME_IN}.profile.xml" PARENT_SCOPE)
	SET(ALGORITHM_PROFILE_XML_FILE "${CMAKE_CURRENT_BINARY_DIR}/${ALG_NAME_IN}.profile.xml")
	MESSAGE("XML Profile Debug: ${ALGORITHM_PROFILE_XML_FILE}")

	SET(ALGORITHM_PROFILE_XML_Content "<Profile>")
	LIST(APPEND ALGORITHM_PROFILE_XML_Content "<UID>")
	LIST(APPEND ALGORITHM_PROFILE_XML_Content "<Namespace>${ALGORITHM_PROFILE_UID_Namespace}</Namespace>")
	LIST(APPEND ALGORITHM_PROFILE_XML_Content "<Name>${ALGORITHM_PROFILE_UID_Name}</Namespace>")
	LIST(APPEND ALGORITHM_PROFILE_XML_Content "<Version>${ALGORITHM_PROFILE_UID_Version}</Version>")
	LIST(APPEND ALGORITHM_PROFILE_XML_Content "</UID>")
	
	MAP_CREATE_XML_ELEMENT("Description" ALGORITHM_PROFILE_Description)
	MAP_CREATE_XML_ELEMENT("Contact" ALGORITHM_PROFILE_Contact)
	MAP_CREATE_XML_ELEMENT("Terms" ALGORITHM_PROFILE_Terms)
	MAP_CREATE_XML_ELEMENT("Citation" ALGORITHM_PROFILE_Citation)
	LIST(APPEND ALGORITHM_PROFILE_XML_Content "<Characteristics>")
	MAP_CREATE_XML_ELEMENT("DataType" ALGORITHM_PROFILE_DataType)
	MAP_CREATE_XML_ELEMENT("ComputationStyle" ALGORITHM_PROFILE_ComputationStyle)
	IF(DEFINED ALGORITHM_PROFILE_Deterministic)
		LIST(APPEND ALGORITHM_PROFILE_XML_Content "<${Deterministic}/>")
	ENDIF(DEFINED ALGORITHM_PROFILE_Deterministic)
	
	MAP_CREATE_XML_ELEMENT("ResolutionStyle" ALGORITHM_PROFILE_ResolutionStyle)
	MAP_CREATE_XML_ELEMENT("DimMoving" ALGORITHM_PROFILE_DimMoving)
	MAP_CREATE_XML_ELEMENT("ModalityMoving" ALGORITHM_PROFILE_ModalityMoving)
	MAP_CREATE_XML_ELEMENT("DimTarget" ALGORITHM_PROFILE_DimTarget)
	MAP_CREATE_XML_ELEMENT("ModalityTarget" ALGORITHM_PROFILE_ModalityTarget)
	MAP_CREATE_XML_ELEMENT("Subject" ALGORITHM_PROFILE_Subject)
	MAP_CREATE_XML_ELEMENT("Object" ALGORITHM_PROFILE_Object)
	MAP_CREATE_XML_ELEMENT("TransformModel" ALGORITHM_PROFILE_TransformModel)
	MAP_CREATE_XML_ELEMENT("TransformDomain" ALGORITHM_PROFILE_TransformDomain)
	MAP_CREATE_XML_ELEMENT("Metric" ALGORITHM_PROFILE_Metric)
	MAP_CREATE_XML_ELEMENT("Optimization" ALGORITHM_PROFILE_Optimization)
	MAP_CREATE_XML_ELEMENT("Interaction" ALGORITHM_PROFILE_Interaction)
	MAP_CREATE_XML_ELEMENT("Interaction" ALGORITHM_PROFILE_Interaction)
	LIST(APPEND ALGORITHM_PROFILE_XML_Content "</Characteristics>")
	
    CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/CMake/mapAlgorithmProfile.h.in ${ALGORITHM_PROFILE_FILE} @ONLY)
	MESSAGE("XML Debug: ${ALGORITHM_PROFILE_XML_FILE}")

	FILE(WRITE ${ALGORITHM_PROFILE_XML_FILE} ${ALGORITHM_PROFILE_XML_Content})
	
	MESSAGE("XML Debug: ${ALGORITHM_PROFILE_XML_Content}")
ENDFUNCTION()
