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




#ifndef __ALGORITHM_PROFILE_HELPER_H
#define __ALGORITHM_PROFILE_HELPER_H

#include "mapSDElement.h"

#include "mapMAPAlgorithmsExports.h"

namespace map
{

	namespace tags
	{
		/** Top node of a algorithm profile.*/
		const char* const AlgorithmProfile = "Profile";
		const char* const AlgorithmDescription = "Description";
		const char* const AlgorithmContact = "Contact";
		const char* const AlgorithmTerms = "Terms";
		const char* const AlgorithmCitation = "Citation";
		const char* const AlgorithmCharacteristics = "Characteristics";
		const char* const AlgorithmDataType = "DataType";
		const char* const AlgorithmComputationStyle = "ComputationStyle";
		const char* const AlgorithmDeterministic = "Deterministic";
		const char* const AlgorithmResolutionStyle = "ResolutionStyle";
		const char* const AlgorithmDimMoving = "DimMoving";
		const char* const AlgorithmModalityMoving = "ModalityMoving";
		const char* const AlgorithmDimTarget = "DimTarget";
		const char* const AlgorithmModalityTarget = "ModalityTarget";
		const char* const AlgorithmSubject = "Subject";
		const char* const AlgorithmObject = "Object";
		const char* const AlgorithmTransformModel = "TransformModel";
		const char* const AlgorithmTransformDomain = "TransformDomain";
		const char* const AlgorithmMetric = "Metric";
		const char* const AlgorithmOptimization = "Optimization";
		const char* const AlgorithmInteraction = "Interaction";
		const char* const AlgorithmKeywords = "Keywords";
		const char* const AlgorithmKeyword = "Keyword";
	}

	namespace algorithm
	{
		namespace profile
		{
			typedef std::vector< ::map::core::String> ValueListType;

			/** Helper function that takes an algorithm profile string and converts it into structuredData
			 * elements.
			 * @return Pointer to the root element of the profile (Tag: Profile). If an invalid or empty string is passed,
			 * the result will be a NULL pointer.*/
			MAPAlgorithms_EXPORT structuredData::Element::Pointer parseProfileString(
				const core::String& profileStr);

			/** Helper function that extracts the description from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return Description string, may be empty if profileRoot is invalid or does not contain a description.*/
			MAPAlgorithms_EXPORT const ::map::core::String getDescription(const structuredData::Element*
					profileRoot);

			/** Helper function that extracts the description from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return Description string, may be empty if profileStr does not contain a description.*/
			MAPAlgorithms_EXPORT const ::map::core::String getDescription(const core::String& profileStr);

			/** Helper function that extracts the contact(s) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getContact(const structuredData::Element* profileRoot);

			/** Helper function that extracts the contact(s) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getContact(const core::String& profileStr);

			/** Helper function that extracts the terms from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @param terms String containing the information.
			 * @return Indicates if terms where found in the profile.*/
			MAPAlgorithms_EXPORT bool getTerms(const structuredData::Element* profileRoot,
											   map::core::String& terms);

			/** Helper function that extracts the terms from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @param terms String containing the information.
			 * @return Indicates if terms where found in the profile.*/
			MAPAlgorithms_EXPORT bool getTerms(const core::String& profileStr, map::core::String& terms);

			/** Helper function that extracts the citation(s) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getCitation(const structuredData::Element* profileRoot);

			/** Helper function that extracts the citation(s) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getCitation(const core::String& profileStr);

			/** Helper function that extracts the supported data type(s) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getDataType(const structuredData::Element* profileRoot);

			/** Helper function that extracts the supported data type(s) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getDataType(const core::String& profileStr);

			/** Helper function that extracts the computation style from a profile.
				 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
				 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getComputationStyle(const structuredData::Element* profileRoot);

			/** Helper function that extracts the computation style from a profile.
				 * @overload Convenience version where you can directly insert the profileStr.
				 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getComputationStyle(const core::String& profileStr);

			/** Helper function that extracts the (multi) resolution style/approach from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getResolutionStyle(const structuredData::Element* profileRoot);

			/** Helper function that extracts the (multi) resolution style/approach from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getResolutionStyle(const core::String& profileStr);

			/** Helper function that extracts the algorithm's moving dimensions from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @param dims parameter containing the information.
			 * @return Indicates if terms where found in the profile.*/
			MAPAlgorithms_EXPORT bool getMovingDimensions(const structuredData::Element* profileRoot,
					unsigned int& dims);

			/** Helper function that extracts the algorithm's moving dimensions from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @param dims parameter containing the information.
			 * @return Indicates if terms where found in the profile.*/
			MAPAlgorithms_EXPORT bool getMovingDimensions(const core::String& profileStr, unsigned int& dims);

			/** Helper function that extracts the moving modality/modalities from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getMovingModality(const structuredData::Element* profileRoot);

			/** Helper function that extracts the moving modality/modalities from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getMovingModality(const core::String& profileStr);

			/** Helper function that extracts the algorithm's moving dimensions from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @param dims parameter containing the information.
			 * @return Indicates if terms where found in the profile.*/
			MAPAlgorithms_EXPORT bool getTargetDimensions(const structuredData::Element* profileRoot,
					unsigned int& dims);

			/** Helper function that extracts the algorithm's target dimensions from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @param dims parameter containing the information.
			 * @return Indicates if terms where found in the profile.*/
			MAPAlgorithms_EXPORT bool getTargetDimensions(const core::String& profileStr, unsigned int& dims);

			/** Helper function that extracts the target modality/modalities from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getTargetModality(const structuredData::Element* profileRoot);

			/** Helper function that extracts the target modality/modalities from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getTargetModality(const core::String& profileStr);

			/** Helper function that extracts the algorithm's object(s) (e.g. lung) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getObject(const structuredData::Element* profileRoot);

			/** Helper function that extracts the  algorithm's object(s) (e.g. lung) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getObject(const core::String& profileStr);

			/** Helper function that extracts the algorithm's subject(s) (e.g. intra personal) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getSubject(const structuredData::Element* profileRoot);

			/** Helper function that extracts the  algorithm's subject(s) (e.g. intra personal) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getSubject(const core::String& profileStr);

			/** Helper function that extracts the algorithm's transform models(s) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getTransformModel(const structuredData::Element* profileRoot);

			/** Helper function that extracts the algorithm's transform models(s) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getTransformModel(const core::String& profileStr);

			/** Helper function that extracts the algorithm's transform domain (e.g. global; in different stages) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getTransformDomain(const structuredData::Element* profileRoot);

			/** Helper function that extracts the algorithm's transform domain (e.g. global; in different stages) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getTransformDomain(const core::String& profileStr);

			/** Helper function that extracts the algorithm's metrics(s) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getMetric(const structuredData::Element* profileRoot);

			/** Helper function that extracts the algorithm's metrics(s) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getMetric(const core::String& profileStr);

			/** Helper function that extracts the algorithm's optimization(s) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getOptimization(const structuredData::Element* profileRoot);

			/** Helper function that extracts the algorithm's optimization(s) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getOptimization(const core::String& profileStr);

			/** Helper function that extracts the algorithm's keyword(s) from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getKeywords(const structuredData::Element* profileRoot);

			/** Helper function that extracts the algorithm's keyword(s) from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getKeywords(const core::String& profileStr);

			/** Helper function that extracts the algorithm's interaction schema/schemes from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).
			 * @return List may be empty if profileRoot is invalid or does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getInteraction(const structuredData::Element* profileRoot);

			/** Helper function that extracts the algorithm's interaction schema/schemes from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.
			 * @return List may be empty if profileStr does not contain any information.*/
			MAPAlgorithms_EXPORT ValueListType getInteraction(const core::String& profileStr);

			/** Helper function that extracts if the algorithm is deterministic from a profile.
			 * @param profileRoot Pointer to the root element of the profile (e.g. generated by parseProfileString).*/
			MAPAlgorithms_EXPORT bool isDeterministic(const structuredData::Element* profileRoot);

			/** Helper function that extracts if the algorithm is deterministic from a profile.
			 * @overload Convenience version where you can directly insert the profileStr.*/
			MAPAlgorithms_EXPORT bool isDeterministic(const core::String& profileStr);

		}
	}
}

#endif
