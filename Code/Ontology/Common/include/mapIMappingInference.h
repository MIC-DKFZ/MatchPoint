// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright c German Cancer Research Center DKFZ,
// Software development for Integrated Diagnostics and Therapy SIDT.
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------





#ifndef __MAP_I_MAPPING_INFERENCE_H
#define __MAP_I_MAPPING_INFERENCE_H

#include "mapOntologyResult.h"
#include "mapDataRepresentation.h"
#include "mapMappingError.h"
#include "mapIProblemComplianceDefinition.h"
#include "mapIProblemStatementAssociated.h"
#include "mapIPathMetric.h"
#include "mapIEntityInference.h"

namespace iro
{
  namespace core
  {
    /*! @class IMappingInference
    * @brief Interface of the registration ontology decorator used for inference queries in the context of mapping and registration/transformation.
    *
    * As inference interface it is analog to a pure getter interface.
    * Setting and writing will be done be integration interfaces (IMappingIntegration).
    * This interface is implemented regarding the NVI paradigm.
    *
    * @tparam TRPTraits type that define the traits of registration paths.
    * @tparam TRPOCTraits type that define the traits of registration path option collections.
    * @tparam TTPOCTraits type that define the traits of transformation path option collections.
    * @tparam TIEInference type of the information entity inference interface that should be used.
    * @sa IProblemInference
    * @sa IViewingInference
    * @sa IEntityInference
    * @sa IMappingIntegration
    * @ingroup Inference
    */
    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    class IMappingInference
    {
    public:
      typedef typename TRPTraits::InformationEntityTraitsType   InformationEntityTraitsType;
      typedef typename TRPTraits::InformationSpaceTraitsType    InformationSpaceTraitsType;
      typedef typename TRPTraits::ProblemStatementTraitsType    ProblemStatementTraitsType;
      typedef typename TRPTraits::RegistrationInfoTraitsType    RegistrationInfoTraitsType;
      typedef typename TRPTraits::TransformationInfoTraitsType  TransformationInfoTraitsType;
      typedef typename TRPTraits::TransformationPathTraitsType  TransformationPathTraitsType;

      typedef typename InformationEntityTraitsType::Type                  InfEntityType;
      typedef typename InformationSpaceTraitsType::Type                   InfSpaceType;
      typedef typename ProblemStatementTraitsType::Type                   ProblemStatementType;
      typedef IProblemComplianceDefinition<ProblemStatementType>          ProblemComplianceInterface;
      typedef typename InformationEntityTraitsType::InferencePointer      InfEntityInferencePointer;
      typedef typename InformationSpaceTraitsType::InferencePointer       InfSpaceInferencePointer;

      typedef typename InfEntityType::ConstPointer           ConstInfEntityPointer;  
      typedef typename InfSpaceType::ConstPointer            ConstInfSpacePointer;  
      typedef typename std::vector<ConstInfEntityPointer>    ConstInfEntityVectorType;
      typedef typename std::vector<ConstInfSpacePointer>     ConstInfSpaceVectorType;

      typedef typename RegistrationInfoTraitsType::Type                                RegistrationInfoType;
      typedef typename RegistrationInfoType::Pointer                                   RegistrationInfoPointer;
      typedef typename RegistrationInfoType::ConstPointer                              ConstRegistrationInfoPointer;
      typedef typename RegistrationInfoTraitsType::InferencePointer                    RegistrationInfoInferencePointer;

      typedef typename TransformationInfoTraitsType::Type                              TransformationInfoType;
      typedef typename TransformationInfoType::Pointer                                 TransformationInfoPointer;
      typedef typename TransformationInfoType::ConstPointer                            ConstTransformationInfoPointer;
      typedef typename TransformationInfoTraitsType::InferencePointer                    TransformationInfoInferencePointer;

      typedef IPathMetric<RegistrationInfoTraitsType>                         RegPathMetricInterface;
      typedef IPathMetric<TransformationInfoTraitsType>                       TransPathMetricInterface;

      typedef typename TRPTraits::Type                    RegistrationPathType;
      typedef typename TRPTraits::ConstPointer            ConstRegistrationPathPointer;

      typedef typename TransformationPathTraitsType::Type                  TransformationPathType;
      typedef typename TransformationPathTraitsType::ConstPointer          ConstTransformationPathPointer;

      typedef typename TRPOCTraits::Type                RegPathOptCollectionType;
      typedef typename TRPOCTraits::ConstPointer        ConstRegPathOptColPointer;
      typedef std::vector<ConstRegPathOptColPointer>    ConstRegPathOptColVectorType;

      typedef typename TTPOCTraits::Type                TransPathOptCollectionType;
      typedef typename TTPOCTraits::ConstPointer        ConstTransPathOptColPointer;
      typedef std::vector<ConstTransPathOptColPointer>  ConstTransPathOptColVectorType;

      typedef MappingError::Type    MappingErrorType;
      
      /*! Queries for all registration paths that are (potentially) able to map between the passed
      * moving and fixed information space.
      * @remark It is only guaranteed that every found registration path by default connects both information spaces.
      * But a returned path may be unable to map a specific entity of the information space (e.g. wrong field of view,
      * wrong data representation support). To get registration paths that care about mapping support for certain entities,
      * use the overloaded version with movingEntities parameter.
      * @param [in] pMovingIS Pointer to the moving information space of the searched paths.
      * @param [in] pFixedIS Pointer to the target information space of the searched paths.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return A collection containing pointers to all registration path found.
      * @pre pMovingIS must point to a valid instance.
      * @pre pFixedIS must point to a valid instance.
      * @pre pMovingIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pMovingIS or pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : at least one of th entities is not defined in the ontology.
      */
      Result<ConstRegPathOptColPointer> getRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

      /*! For each passed entity all registration paths that are able to map the entity into the fixed information space are compiled.
      * Each RegistrationPathOptionCollections instance contains all valid registration paths for a specific entity to map it into the fixed
      * information space.
      * @param [in] movingEntities Collection with all entities for which valid path options should be found.
      * @param [in] pFixedIS Pointer to the target information space of the searched paths where the entities should be mapped to.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return A vector to collections for all entities with their RegistrationPathOptions found.
      * A collection may contain no options. meaning that there are no possibilities for a certain entity
      * to be mapped.
      * @remark The passed moving entity vector and the collection vector are sorted in the same way.
      * thus you can use the same index to adress the entity and its collection. 
      * @pre pFixedIS must point to a valid instance.
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre movingEntities must contain elements that are defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : at least one of the entities or the information space is not defined in the ontology.
      */
      Result<ConstRegPathOptColVectorType> getRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

      /*! Queries for all transformation paths that are (potentially) able to map between
      * the passed moving and fixed information space.
      * @remark It is only guaranteed that every found transformation path by default connects
      * both information spaces. But each path is only able to map one type of representation
      * data and may be unable to map a specific entity of the information space
      * (e.g. wrong field of view, wrong data representation support).
      * To get transformation paths that care about mapping support for certain entities,
      * use one of the overloaded entity specific versions.
      * @param [in] pMovingIS Pointer to the moving information space of the searched paths.
      * @param [in] pFixedIS Pointer to the target information space of the searched paths.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return A collection containing pointers to all transformation path found.
      * @pre pMovingIS must point to a valid instance.
      * @pre pFixedIS must point to a valid instance.
      * @pre pMovingIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pMovingIS or pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : at least one of the information spaces is not defined in the ontology.
      */
      Result<ConstTransPathOptColPointer> getTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

      /*! For each passed entity all transformation paths that are able to map the entity into the fixed information space are compiled.
      Each TransPathOptionCollections instance contains all valid transformation paths for a specific entity to map it into the fixed
      information space.
      * @param [in] movingEntities Collection with all entities for which valid path options should be found.
      * @param [in] pFixedIS Pointer to the target information space of the searched paths where the entities should be mapped to.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return A vector to collections for all entities with their TransformationPathOptions found.
      * A collection may contain no options. meaning that there are no possibilities for a certain entity
      * to be mapped.
      * @remark The passed moving entity vector and the collection vector are sorted in the same way.
      * thus you can use the same index to adress the entity and its collection. 
      * @pre pFixedIS must point to a valid instance.
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre movingEntities must contain elements that are defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : at least one of the entities or the information space is not defined in the ontology.
      */
      Result<ConstTransPathOptColVectorType> getTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

      /*! Queries for the optimal registration path that is (potentially) able to map between the passed
      * moving and fixed information space. How a path is evaluated as optimal can be defined via passing an
      * instance implementing a RegPathMetricInterface. This metric will be used to calculate the "costs" of each
      * path step in order to find an optimal path.
      * @remark It is only guaranteed that every found transformation path by default connects both information spaces.
      * But a returned path may be unable to map a specific entity of the information space (e.g. wrong field of view,
      * wrong data representation support). To get registration paths that care about mapping support for certain entities,
      * use the overloaded version with movingEntities parameter.
      * @remark Normaly the returned collection should contain only one path. But it is possible that several paths have the same
      * optimal rating. In this case all will be returned in the collection. If this is the case, you should either readjust the criterias
      * and redo the search, or just pick the path you like because regarding the given criteria all options are fine.
      * @remark If no metric is passed via pMetric, the definition of "optimum" depends on the application scenerio and is defined by its
      * implementation. Please see the documentation of the scenario for more information.
      * @param [in] pMovingIS Pointer to the moving information space of the searched paths.
      * @param [in] pFixedIS Pointer to the target information space of the searched paths.
      * @param [in] pMetric Pointer to the metric that is used to evaluate every path element. If NULL is passed the default optimum criteria will be used.
      * @param [in] requiredDataSupport Specifies the data representation support that should be regarded.
      * The sum of all path element measures is the rating for the complete graph.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return A collection containing pointers to all optimal registration path options found.
      * @pre pMovingIS must point to a valid instance.
      * @pre pFixedIS must point to a valid instance.
      * @pre pMovingIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pMovingIS or pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : at least one of the information spaces is not defined in the ontology.
      */
      Result<ConstRegPathOptColPointer> getOptimalRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL) const;

      /*! For each passed entity all optimal registration paths, that are able to map the entity into the fixed information
      * space, are compiled. How a path is evaluated as optimal can be defined via passing an
      * instance implementing a RegPathMetricInterface. This metric will be used to calculate the "costs" of each
      * path step in order to find an optimal path.
      * @remark Normaly the returned collection should contain only one optimal path. But it is possible that several paths have the same
      * optimal rating. In this case all will be returned in the collection. If this is the case, you should either readjust the criterias
      * and redo the search, or just pick the path you like because regarding the given criteria all options are fine.
      * @remark If no metric is passed via pMetric, the definition of "optimum" depends on the application scenerio and is defined by its
      * implementation. Please see the documentation of the scenario for more information.
      * @param [in] movingEntities Collection with all entities for which valid path options should be found.
      * @param [in] pFixedIS Pointer to the target information space of the searched paths.
      * @param [in] pMetric Pointer to the metric that is used to evaluate every path element. If NULL is passed the default optimum criteria will be used.
      * The sum of all path element measures is the rating for the complete graph.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return A vector to collections for all entities with their optimal RegistrationPathOptions found.
      * A collection may contain no options. meaning that there are no possibilities for a certain entity
      * to be mapped.
      * @remark The passed moving entity vector and the collection vector are sorted in the same way.
      * thus you can use the same index to adress the entity and its collection. 
      * @pre pFixedIS must point to a valid instance.
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre movingEntities must contain elements that are defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : at least one of the entities or the information space is not defined in the ontology.
      */
      Result<ConstRegPathOptColVectorType> getOptimalRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL) const;

      /*! Queries for the optimal transformation path that is (potentially) able to map between the passed
      * moving and fixed information space. How a path is evaluated as optimal can be defined via passing an
      * instance implementing a TransPathMetricInterface. This metric will be used to calculate the "costs" of each
      * path step in order to find an optimal path.
      * @remark It is only guaranteed that every found transformation path by default connects both information spaces.
      * But a returned path may be unable to map a specific entity of the information space (e.g. wrong field of view,
      * wrong data representation support). To get registration paths that care about mapping support for certain entities,
      * use the overloaded version with movingEntities parameter.
      * @remark Normaly the returned collection should contain only one path. But it is possible that several paths have the same
      * optimal rating. In this case all will be returned in the collection. If this is the case, you should either readjust the criterias
      * and redo the search, or just pick the path you like because regarding the given criteria all options are fine.
      * @remark If no metric is passed via pMetric, the definition of "optimum" depends on the application scenerio and is defined by its
      * implementation. Please see the documentation of the scenario for more information.
      * @param [in] pMovingIS Pointer to the moving information space of the searched paths.
      * @param [in] pFixedIS Pointer to the target information space of the searched paths.
      * @param [in] pMetric Pointer to the metric that is used to evaluate every path element. If NULL is passed the default optimum criteria will be used.
      * The sum of all path element measures is the rating for the complete graph.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return A collection containing pointers to all optimal transformation path found.
      * @pre pMovingIS must point to a valid instance.
      * @pre pFixedIS must point to a valid instance.
      * @pre pMovingIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pMovingIS or pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : at least one of the information spaces is not defined in the ontology.
      */
      Result<ConstTransPathOptColPointer> getOptimalTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL, const TransPathMetricInterface* pMetric = NULL) const;

      /*! For each passed entity all optimal transformation paths that are able to map the entity into the fixed information
      * space are compiled. How a path is evaluated as optimal can be defined via passing an
      * instance implementing a TransPathMetricInterface. This metric will be used to calculate the "costs" of each
      * path step in order to find an optimal path.
      * @remark It is only guaranteed that every found transformation path by default connects both information spaces.
      * But a returned path may be unable to map a specific entity of the information space (e.g. wrong field of view,
      * wrong data representation support). To get registration paths that care about mapping support for certain entities,
      * use the overloaded version with movingEntities parameter.
      * @remark Normaly the returned collection should contain only one path. But it is possible that several paths have the same
      * optimal rating. In this case all will be returned in the collection. If this is the case, you should either readjust the criterias
      * and redo the search, or just pick the path you like because regarding the given criteria all options are fine.
      * @remark If no metric is passed via pMetric, the definition of "optimum" depends on the application scenerio and is defined by its
      * implementation. Please see the documentation of the scenario for more information.
      * @param [in] movingEntities Collection with all entities for which valid path options should be found.
      * @param [in] pFixedIS Pointer to the target information space of the searched paths.
      * @param [in] pMetric Pointer to the metric that is used to evaluate every path element. If NULL is passed the default optimum criteria will be used.
      * The sum of all path element measures is the rating for the complete graph.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return A vector to collections for all entities with their optimal TransformationPathOptions found.
      * A collection may contain no options. meaning that there are no possibilities for a certain entity
      * to be mapped.
      * @remark The passed moving entity vector and the collection vector are sorted in the same way.
      * thus you can use the same index to adress the entity and its collection. 
      * @pre pFixedIS must point to a valid instance.
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : the information spaces is not defined in the ontology.
      */
      Result<ConstTransPathOptColVectorType> getOptimalTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL, const TransPathMetricInterface* pMetric = NULL) const;

      /*! Queries for all information spaces that can be mapped into a given information space
      * How a path is evaluated as optimal can be defined via passing an
      * instance implementing a RegPathMetricInterface. This metric will be used to calculate the "costs" of each
      * path step in order to find an optimal path.
      * @remark It is only guaranteed that every found IS is connected.
      * But there may be no existing path that is able to map a specific entity of the information space (e.g. wrong field of view,
      * wrong data representation support). To get registration paths that care about mapping support for certain entities,
      * use getOptimalTransformationPath() for entities.
      * @remark Normally the returned collection should contain only one path. But it is possible that several paths have the same
      * optimal rating. In this case all will be returned in the collection. If this is the case, you should either readjust the criterias
      * and redo the search, or just pick the path you like because regarding the given criteria all options are fine.
      * @remark If no metric is passed via pMetric, the definition of "optimum" depends on the application scenerio and is defined by its
      * implementation. Please see the documentation of the scenario for more information.
      * @param [in] pFixedIS Pointer to the target information space of the searched paths.
      * @param [in] pMetric Pointer to the metric that is used to evaluate every path element. If NULL is passed the default optimum criteria will be used.
      * @param [in] requiredDataSupport Specifies the data representation support that should be regarded.
      * The sum of all path element measures is the rating for the complete graph.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return A collection of information spaces that can be mapped.
      * @pre pFixedIS must point to a valid instance.
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : the information spaces is not defined in the ontology.
      */
      Result<ConstInfSpaceVectorType> getMappableInformationSpaces(InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL) const;

      /*! Checks if there are any valid transformation paths for enitity pMovingEntity to get mapped into pFixedIS. If not, it will be ascertained why
       * there is no suitable transformation path. The most precise reason will be returned:
      * - No failure (at least one valid path is available): MappingError::NoFailure
      * - No TransformationPath available : MappingError::NoPath
      * - No TransformationPath for the needed data type (meaning: there are tranformation paths but not for the required data type support) : MappingError::NoDataSupport
      * - No TransformationPath with sufficient FOV/Mapping guarantee : MappingError::NoMappingGuarantee
      * .
      * @param [in] pMovingEntity Pointer to the entity that should be checked for mapping failures.
      * @param [in] pFixedIS Pointer to the target information space of the paths that should be validated.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return The mapping error reason.
      * @pre pFixedIS must point to a valid instance.
      * @pre pMovingEntity must point to a valid instance.
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre pMovingEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pMovingEntity or pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : the entity or the information spaces is not defined in the ontology.
      */
      Result<MappingErrorType> checkForMappingFailureReason(InfEntityInferencePointer pMovingEntity, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

      /*! Checks if there are any valid transformation paths that maps between the given information spaces regarding the defined data
      * representation support. If not, it will be ascertained why there is no suitable transformation path. The most precise reason
      * will be returned:
      * - No failure (at least one valid path is available, but mapping is not guaranteed): MappingError::NoFailure
      * - No TransformationPath available : MappingError::NoPath
      * - No TransformationPath for the needed data type (meaning: there are tranformation paths but not for the required data type support) : MappingError::NoDataSupport
      * .
      * @Remark This function cannot guarantee full mapping. If it returns with no error it only indicates that
      * at least a part of the information could be mapped. If you also want to check vor mapping guarantee, use
      * the overloaded member and pass a concrete entity that should be checked. 
      * @param [in] pMovingIS Pointer to the moving information space of the paths that should be validated.
      * @param [in] pFixedIS Pointer to the target information space of the paths that should be validated.
      * @param [in] requiredDataSupport Specifies the data representation support that should be regarded.
      * @param [in] pProblemCompliance Pointer to a ProblemComplianceInterface (normaly implemented by a ProblemStatement or ProblemModel). If an instance is
      * given every element will be checked for compliance (e.g. same ProblemStamtement or within same ProblemModel). If a null pointer is
      * passed the problem compliance is not regarded -> any path will be returned.
      * @return The mapping error reason.
      * @pre pFixedIS must point to a valid instance.
      * @pre pMovingIS must point to a valid instance.
      * @pre pFixedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre pMovingIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pMovingIS or pFixedIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : at least one of the information spaces is not defined in the ontology.
      */
      Result<MappingErrorType> checkForMappingFailureReason(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

      /*! Checks if the passed registration path is able to map the given movingEntity.
      * If not, it will be acertained why there is no suitable registration path. The most precise reason will be returned:
      * - No failure (at least one valid path is available): MappingError::NoFailure
      * - No TransformationPath available : MappingError::NoPath
      * - No TransformationPath for the needed data type (meaning: there are tranformation paths but not for the required data type support) : MappingError::NoDataSupport
      * - No TransformationPath with sufficient FOV/Mapping guarantee : MappingError::NoMappingGuarantee
      * .
      * @param [in] pMovingEntity Pointer to the entity that should be checked for mapping failures.
      * @param [in] pPath Pointer to the path that should be checked for failure.
      * @return The mapping error reason.
      * @pre pPath must point to a valid instance.
      * @pre pMovingEntity must point to a valid instance.
      * @pre pMovingEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre Moving and fixed IS of pPath must be defined in the ontology.
      * @exception ::iro::exceptions::InvalidArgument : pMovingEntity or pPath pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : the entity or the ISs of the path are not defined in the ontology.
      */
      Result<MappingErrorType> checkForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstRegistrationPathPointer pPath) const;

      /*! Checks if the passed transformation path is able to map the given movingEntity.
      * If not, it will be acertained why there is no suitable transformation path. The most precise reason will be returned:
      * - No failure (at least one valid path is available): MappingError::NoFailure
      * - No TransformationPath available (the passed path has not the same moving information space): MappingError::NoPath
      * - No TransformationPath for the needed data type (meaning: there are tranformation paths but not for the required data type support) : MappingError::NoDataSupport
      * - No TransformationPath with sufficient FOV/Mapping guarantee : MappingError::NoMappingGuarantee
      * .
      * @param [in] pMovingEntity Pointer to the entity that should be checked for mapping failures.
      * @param [in] pPath Pointer to the path that should be checked for failure.
      * @return The mapping error reason.
      * @pre pPath must point to a valid instance.
      * @pre pMovingEntity must point to a valid instance.
      * @pre pMovingEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre Moving and target IS of pPath must be defined in the ontology.
      * @exception ::iro::exceptions::InvalidArgument : pMovingEntity or pPath pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : the entity or the ISs of the path are not defined in the ontology.
      */
      Result<MappingErrorType> checkForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstTransformationPathPointer pPath) const;

      /*! This function converts a given transformation path into a registration path.
      * This is done by searching the fitting complement TransformationInfo (if it exists)
      * for each TransformationInfo in the path and compiling them into a RegistrationInfo.
      * If no complement transformation info exists the RegistrationInfo will stay undefined
      * for the affected data representation type.
      * @remark A transformation info B is complement to info A if A and B have the same moving and fixed
      * information spaces and the same problem statement but different data representations (one
      * is discrete, the other is continuous).
      * @param [in] pPath Pointer to the path that should be converted.
      * @return The pointer to the instance of the registration path.
      * @pre pPath must point to a valid instance.
      * @pre Moving and target IS of pPath must be defined in the ontology.
      * @exception ::iro::exceptions::UndefinedElement : The ISs of the path are not defined in the ontology.
      * @exception ::iro::exceptions::InvalidArgument : pPath pointer is null.*/
      Result<ConstRegistrationPathPointer> convertTransformationToRegistrationPath(ConstTransformationPathPointer pPath) const;

			/*!Takes the passed transformation information and returns the current version (UID equals)
      * that represents the current state of the ontology.
      * @param [in] pTI Pointer to the transformation info that should be actualized.
      * @return Smart pointer to the current version of the element. If the information space
      * does not exist (any more) in the ontology, a NULL pointer will be returned.
      * @pre pTI must point to valid instances.
      * @overload
      * @exception ::iro::exceptions::InvalidArgument : pIS is not a valid pointer.*/
			Result<ConstTransformationInfoPointer> actualize(TransformationInfoInferencePointer pTI) const;

    protected:
      virtual ~IMappingInference() {};
      IMappingInference() {};

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getRegistrationPaths*/
      virtual Result<ConstRegPathOptColPointer> doGetRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getRegistrationPaths*/
      virtual Result<ConstRegPathOptColVectorType> doGetRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getTransformationPaths*/
      virtual Result<ConstTransPathOptColPointer> doGetTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getTransformationPaths*/
      virtual Result<ConstTransPathOptColVectorType> doGetTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalRegistrationPaths*/
      virtual Result<ConstRegPathOptColPointer> doGetOptimalRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalRegistrationPaths*/
      virtual Result<ConstRegPathOptColVectorType> doGetOptimalRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL) const = 0;

      /*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalTransformationPaths*/
      virtual Result<ConstTransPathOptColPointer> doGetOptimalTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL, const TransPathMetricInterface* pMetric = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalTransformationPaths*/
      virtual Result<ConstTransPathOptColVectorType> doGetOptimalTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL, const TransPathMetricInterface* pMetric = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getMappableInformationSpaces*/
      virtual Result<ConstInfSpaceVectorType> doGetMappableInformationSpaces(InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      virtual Result<MappingErrorType> doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      virtual Result<MappingErrorType> doCheckForMappingFailureReason(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = NULL) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      virtual Result<MappingErrorType> doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstRegistrationPathPointer pPath) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      virtual Result<MappingErrorType> doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstTransformationPathPointer pPath) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see convertTransformationToRegistrationPath*/
      virtual Result<ConstRegistrationPathPointer> doConvertTransformationToRegistrationPath(ConstTransformationPathPointer pPath) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
      virtual Result<ConstTransformationInfoPointer> doActualize(TransformationInfoInferencePointer pTI) const = 0;

      /*! Helper function that checks the entities in the vector if they are part of the ontology
       * and returns the vector containing the actualized entites. If at least one entity in the
       * vector is an invalid pointer or not defined in the ontology an exception will be thrown.
      * @exception ::iro::exceptions::InvalidArgument : at least one entity is not valid.
      * @exception ::iro::exceptions::UndefinedElement : at least one entity is not defined in the ontology.*/
      ConstInfEntityVectorType actualizeVector(const ConstInfEntityVectorType& oldV) const;

      typedef TIEInference EntityInferenceInterface;
      
      /*!Sets the pointer to the interface that should be used to actualze inference elements
       * (e.g. entities or information spaces)*/
      void setEntityInferenceInterface(const EntityInferenceInterface* pInterface);

      /*!Used to actualize the passed inference elements (e.g. entities or information spaces)*/
      const EntityInferenceInterface* _pEntityInferenceInterface;

    private:
      IMappingInference(const IMappingInference&); //not implemented by purpose
      IMappingInference& operator=(const IMappingInference&); //not implemented by purpose
    };
  } // end namespace core
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapIMappingInference.tpp"
#endif

#endif
