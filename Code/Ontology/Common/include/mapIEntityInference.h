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





#ifndef __MAP_I_ENTITY_INFERENCE_H
#define __MAP_I_ENTITY_INFERENCE_H

#include "mapOntologyResult.h"
#include "mapDataRepresentation.h"

#include <vector>

namespace iro
{
	namespace core
	{
		/*! @class IEntityInference
     * @brief Interface of the registration ontology used for inference queries in the context of entities or entity related questions that can be handled without caring about registration.
     *
     * As inference interface it is analog to a pure getter interface.
     * Setting and writing will be done be integration interfaces (IProblemIntegration).
     * This interface is implemented regarding the NVI paradigm.
     *
     * @tparam TIETraits type that define the traits of information entities.
     * @tparam TISTraits type that define the traits of information spaces.
     * @tparam TSCTraits type that define the traits of semantic correlations.
     * @sa IProblemInference
     * @sa IViewingInference
     * @sa IMappingInference
     * @sa IProblemIntegration
     * @ingroup Inference
     */
    template <typename TIETraits, typename TISTraits, typename TSCTraits>
		class IEntityInference
		{
		public:
      typedef typename TIETraits::Type                   InfEntityType;
      typedef typename TISTraits::Type                    InfSpaceType;
      typedef typename TSCTraits::Type                 CorrelationType;
      typedef typename TIETraits::ConstPointer           ConstInfEntityPointer;
      typedef typename TISTraits::ConstPointer            ConstInfSpacePointer;
      typedef typename TSCTraits::ConstPointer         ConstCorrelationPointer;
      typedef typename TIETraits::InferencePointer       InfEntityInferencePointer;
      typedef typename TISTraits::InferencePointer        InfSpaceInferencePointer;
      typedef typename TSCTraits::InferencePointer     CorrelationInferencePointer;

      typedef typename std::vector<ConstInfEntityPointer>   ConstInfEntityVectorType;
      typedef typename std::vector<ConstInfSpacePointer>   ConstInfSpaceVectorType;
      typedef typename std::vector<ConstCorrelationPointer>   ConstCorrelationVectorType;

      typedef DataRepresentation::Type DataRepresentationType;

      /*! Returns the information space of the passed entity.
      *@param [in] pEntity Const pointer to the entity whose information space should be detected.
      *@return Pointer to the correlated information space. If the passed entity is unkown,
      * a null pointer will be returned.
      *@pre pEntity must point to a valid instance.
      *@pre pEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : entity pointer is null.
      *@exception ::iro::exceptions::UndefinedElement : entity is not defined in the ontology.
      */
			Result<ConstInfSpacePointer> getContainingIS(InfEntityInferencePointer pEntity) const;

			/*! Queries for all entities that are contained by the passed information space.
      *@param [in] pIS Pointer to the information space that contains the wanted entities.
      *@return a collection containing pointers to all entities associated with the passed information space.
      * If the space is unkown, an empty collection will be returned.
      *@pre Information space must point to a valid instance.
      *@pre pIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : information space pointer is null.
      *@exception ::iro::exceptions::UndefinedElement : information space is not defined in the ontology.
      */
			Result<ConstInfEntityVectorType> getEntitiesInIS(InfSpaceInferencePointer pIS) const;

			/*! Function checks if two entities are located in the same information space.
      *@param [in] pEntity1 Pointer to the first entity.
      *@param [in] pEntity2 Pointer to the second entity.
      *@return True if the passed entities are locates in the same information space.
      *@pre pEntity1 must point to a valid instance.
      *@pre pEntity2 must point to a valid instance.
      *@pre pEntity1 must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@pre pEntity2 must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : entity pointer is null.
      *@exception ::iro::exceptions::UndefinedElement : at least on entity is not defined in the ontology.
      */
			Result<bool> checkForSameIS(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const;

			/*! Function checks if the passed entities are located in the same information space.
      *@param [in] entities collection with pointers to entities that should be checked.
      *@return True if the passed entities are locates in the same information space.
      *@pre entities must contain pointer to valid instances.
      *@pre entities must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : collection containes invalid entity pointers.
      *@exception ::iro::exceptions::UndefinedElement : at least on entity is not defined in the ontology.*/
			Result<bool> checkForSameIS(const ConstInfEntityVectorType& entities) const;

			/*! Queries for all entities that have a semantic correlation to the passed entity.
      *@param [in] pEntity Pointer to the entity that should be checked for correlations.
      *@return A collection containing pointers to all entities correlated with the passed
      * entity.
      *@pre pEntity must point to valid instances.
      *@pre pEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : pEntity is not valid.
      *@exception ::iro::exceptions::UndefinedElement : entity is not defined in the ontology.
      */
			Result<ConstInfEntityVectorType> getEntitiesWithSemanticCorrelations(InfEntityInferencePointer pEntity) const;

			/*! Returns all entities of "pSourceIS" that have a semantic correlation into "pCorrelatedIS".
      *@param [in] pSourceIS Pointer to the information spaces whose entities will be queried for the fact if they have correlations with entities in pCorrelatedIS.
      *@param [in] pCorrelatedIS Pointer to the information space the entities from pSourceIS should have correlations into.
      *@return A collection containing pointers to all entities in pSourceIS that are correlated with
      * at least one entity in pCorrelatedIS.
      *@pre pSourceIS must point to valid instances.
      *@pre pCorrelatedIS must point to valid instances.
      *@pre pSourceIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@pre pCorrelatedIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : pSourceIS or pCorrelatedIS is not valid.
      *@exception ::iro::exceptions::UndefinedElement : at least on of the information spaces is not defined in the ontology.
      */
			Result<ConstInfEntityVectorType> getSemanticallyCorrelatedEntities(InfSpaceInferencePointer pSourceIS, InfSpaceInferencePointer pCorrelatedIS) const;

			/*! Queries for all semantic correlations that exist between the passed information spaces.
      *@param [in] pIS1 Pointer to the first information spaces.
      *@param [in] pIS2 Pointer to the second information space.
      *@return A collection containing semantic correlations between entities of the passed information spaces.
      *@pre is1 must point to valid instances.
      *@pre is2 must point to valid instances.
      *@pre pIS1 must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@pre pIS2 must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : is1 or is2 is not valid.
      *@exception ::iro::exceptions::UndefinedElement : at least on of the information spaces is not defined in the ontology.
      */
			Result<ConstCorrelationVectorType> getSemanticCorrelations(InfSpaceInferencePointer pIS1, InfSpaceInferencePointer pIS2) const;

			/*! Queries for all semantic correlations that exist between the passed entity and entities of the passed information space.
      *@param [in] pEntity Pointer to the entity.
      *@param [in] pIs Pointer to the information space.
      *@return A collection containing found semantic correlations.
      *@pre pEntity must point to valid instances.
      *@pre pIS must point to valid instances.
      *@pre pEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@pre pIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : pEntity or pIS is not valid.
      *@exception ::iro::exceptions::UndefinedElement : entity or information space is not defined in the ontology.
      */
			Result<ConstCorrelationVectorType> getSemanticCorrelations(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pIS) const;

			/*! Queries for all semantic correlations that exist between the passed entities.
      *@param [in] pEntity1 Pointer to the first entity.
      *@param [in] pEntity2 Pointer to the second entity.
      *@return A collection containing found semantic correlations.
      *@pre pEntity1 must point to valid instances.
      *@pre pEntity2 must point to valid instances.
      *@pre pEntity1 must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@pre pEntity2 must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : pEntity1 or pEntity2 is not valid.
      *@exception ::iro::exceptions::UndefinedElement : at least on entity is not defined in the ontology.
      */
			Result<ConstCorrelationVectorType> getSemanticCorrelations(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const;

			/*!Returns the data representation type of the passed entity.
      *@param [in] pEntity Pointer to the entity whose representation type should be queried.
      *@pre pEntity must point to valid instances.
      *@pre pEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : pEntity is not valid.
      *@exception ::iro::exceptions::UndefinedElement : entity is not defined in the ontology.
      */
			Result<DataRepresentationType> getDataRepresentationType(InfEntityInferencePointer pEntity) const;

			/*!Indicates if the passed entity is represented by discrete data.
      *@param [in] pEntity Pointer to the entity whose representation type should be checked.
      *@pre pEntity must point to valid instances.
      *@pre pEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : pEntity is not valid.
      *@exception ::iro::exceptions::UndefinedElement : entity is not defined in the ontology.
      */
			Result<bool> hasDiscreteDataRepresentation(InfEntityInferencePointer pEntity) const;

			/*!Indicates if the passed entity is represented by continuous data.
      *@param [in] pEntity Pointer to the entity whose representation type should be checked.
      *@pre pEntity must point to valid instances.
      *@pre pEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : pEntity is not valid.
      *@exception ::iro::exceptions::UndefinedElement : entity is not defined in the ontology.
      */
			Result<bool> hasContinuousDataRepresentation(InfEntityInferencePointer pEntity) const;

			/*! Returns a vector that containes all entities that are defined in the ontology.
      * @remark Depending on the ontology the returning vector can be very large and thus the function call
      * can be of low performance.
      */
			Result<ConstInfEntityVectorType> getEntities() const;

			/*! Returns a vector that containes all information spaces that are defined in the ontology.
      * @remark Depending on the ontology the returning vector can be very large and thus the function call
      * can be of low performance.
      */
			Result<ConstInfSpaceVectorType> getInformationSpaces() const;

			/*! Returns a vector that containes all semantic correlations that are defined in the ontology.
      * @remark Depending on the ontology the returning vector can be very large and thus the function call
      * can be of low performance.
      */
			Result<ConstCorrelationVectorType> getSemanticCorrelations() const;

			/*!Takes the passed entity and returns the version of the entity (UID equals)
      * that represents the current state of the ontology.
      * @param [in] pEntity Pointer to the entity that should be actualized.
      * @return Smart pointer to the current version of the element. If the entity
      * does not exist (any more) in the ontology, a NULL pointer will be returned.
      * @pre pEntity must point to valid instances.
      * @overload
      * @exception ::iro::exceptions::InvalidArgument : pEntity is not a valid pointer.*/
			Result<ConstInfEntityPointer> actualize(InfEntityInferencePointer pEntity) const;

			/*!Takes the passed information space and returns the version of the IS (UID equals)
      * that represents the current state of the ontology.
      * @param [in] pIS Pointer to the IS that should be actualized.
      * @return Smart pointer to the current version of the element. If the information space
      * does not exist (any more) in the ontology, a NULL pointer will be returned.
      * @pre pIS must point to valid instances.
      * @overload
      * @exception ::iro::exceptions::InvalidArgument : pIS is not a valid pointer.*/
			Result<ConstInfSpacePointer> actualize(InfSpaceInferencePointer pIS) const;

			/*!Takes the passed correlation and returns the version of the correlation (UID equals)
      * that represents the current state of the ontology.
      * @param [in] corr Pointer to the information space that should be actualized.
      * @return Smart pointer to the current version of the element. If the correlation
      * does not exist (any more) in the ontology, a NULL pointer will be returned.
      * @pre corr must point to valid instances.
      * @overload
      * @exception ::iro::exceptions::InvalidArgument : corr is not a valid pointer.*/
			Result<ConstCorrelationPointer> actualize(CorrelationInferencePointer corr) const;

    protected:
			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getContainingIS*/
			virtual Result<ConstInfSpacePointer> doGetContainingIS(InfEntityInferencePointer pEntity) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getEntitiesInIS*/
			virtual Result<ConstInfEntityVectorType> doGetEntitiesInIS(InfSpaceInferencePointer pIS) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForSameIS*/
			virtual Result<bool> doCheckForSameIS(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForSameIS*/
			virtual Result<bool> doCheckForSameIS(const ConstInfEntityVectorType& entities) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getEntitiesWithSemanticCorrelations*/
			virtual Result<ConstInfEntityVectorType> doGetEntitiesWithSemanticCorrelations(InfEntityInferencePointer pEntity) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticallyCorrelatedEntities*/
			virtual Result<ConstInfEntityVectorType> doGetSemanticallyCorrelatedEntities(InfSpaceInferencePointer pSourceIS, InfSpaceInferencePointer pCorrelatedIS) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			virtual Result<ConstCorrelationVectorType> doGetSemanticCorrelations(InfSpaceInferencePointer pIS1, InfSpaceInferencePointer pIS2) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			virtual Result<ConstCorrelationVectorType> doGetSemanticCorrelations(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pIs) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			virtual Result<ConstCorrelationVectorType> doGetSemanticCorrelations(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getDataRepresentationType*/
			virtual Result<DataRepresentationType> doGetDataRepresentationType(InfEntityInferencePointer pEntity) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see hasDiscreteDataRepresentation*/
			virtual Result<bool> doHasDiscreteDataRepresentation(InfEntityInferencePointer pEntity) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see hasContinuousDataRepresentation*/
			virtual Result<bool> doHasContinuousDataRepresentation(InfEntityInferencePointer pEntity) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getEntities*/
			virtual Result<ConstInfEntityVectorType> doGetEntities() const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getInformationSpaces*/
			virtual Result<ConstInfSpaceVectorType> doGetInformationSpaces() const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			virtual Result<ConstCorrelationVectorType> doGetSemanticCorrelations() const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstInfEntityPointer> doActualize(InfEntityInferencePointer pEntity) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstInfSpacePointer> doActualize(InfSpaceInferencePointer pIS) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstCorrelationPointer> doActualize(CorrelationInferencePointer corr) const = 0;


      virtual ~IEntityInference() {};
			IEntityInference() {};

		private:
			IEntityInference(const IEntityInference&); //not implemented by purpose
			IEntityInference& operator=(const IEntityInference&); //not implemented by purpose
		};
	} // end namespace core
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapIEntityInference.tpp"
#endif

#endif
