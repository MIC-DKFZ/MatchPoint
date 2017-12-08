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





#ifndef __MAP_I_MAPPING_INTEGRATION_H
#define __MAP_I_MAPPING_INTEGRATION_H

#include "mapIEntityInference.h"
#include "mapIProblemInference.h"

namespace iro
{
  namespace core
  {
    /*! @class IMappingIntegration
    * @brief Interface of the registration ontology decorator used for integration queries in the context of transformations or mapping
    * related information.
    *
    * As integration interface it is analog to a pure setter interface.
    * Getting will be done be inference interfaces (IMappingInference).
    * This interface is implemented regarding the NVI paradigm.
    *
    * @tparam TTITraits type that define the traits of transformation info.
    * @tparam TPInference type of the problem inference interface that should be used.
    * @tparam TIEInference type of the information entity inference interface that should be used.
    * @tparam TTDReturnType type that is returned by transformation/registration delete operations.
    * @sa IProblemIntegration
    * @sa IEntityIntegration
    * @sa IMappingInference
    * @ingroup Integration
    */
    template <typename TTITraits, typename TIEInference, typename TPInference, typename TTDReturnType = bool>
    class IMappingIntegration
    {
    public:
      typedef typename TTITraits::Type                  TransformationInfoType;
      typedef typename TTITraits::ConstPointer          ConstTransformationInfoPointer;
      typedef typename TTITraits::InferencePointer      TransInfoInferencePointer;

      using InformationSpaceTraitsType = typename TTITraits::InformationSpaceTraitsType;
      using InformationEntityTraitsType = typename TTITraits::InformationEntityTraitsType;
      using ProblemStatementTraitsType = typename TTITraits::ProblemStatementTraitsType;

      typedef TTDReturnType  TransformationDeleteReturnType;

      /*! Defines and stores the copy of the passed transformation information
      * after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleExistenceOnTransInfoDef
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @param [in] newTransformation Pointer to the transformation info that should be added as definition to the ontology.
      * @return Returns the transformation info after the insertion of the definition into the ontology.
      * @pre newTransformation must point to a valid instance.
      * @pre newTransformation must reference information spaces that are defined in the ontology.
      * @pre If newTransformation is associated to a problem statement this statement must be defined in the ontology.
      * @exception ::iro::exceptions::InvalidArgument : newTransformation pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : the information spaces or problem statement of the new transformation info are not defined in the ontology.
      */
      Result<ConstTransformationInfoPointer> defineTransformation(TransInfoInferencePointer newTransformation);

      /*! Stores the copy of the passed transformation and commits the changes between the passed version of the entity and the
      * one stored in the ontology after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnTransInfoStore
      * - handleExistenceOnTransInfoStore
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] pEntity Pointer to the entity whose changes should be commited to the ontology.
      * @return Returns the entity after the changes are commited to the ontology.
      * @pre pEntity must point to a valid instance.
      * @pre transformation must point to a valid instance.
      * @pre transformation must reference information spaces that are defined in the ontology.
      * @pre If transformation is associated to a problem statement this statement must be defined in the ontology.
      * @exception ::iro::exceptions::InvalidArgument : transformation pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : the information spaces or problem statement of the transformation info are not defined in the ontology.
      */
      Result<ConstTransformationInfoPointer> storeTransformation(TransInfoInferencePointer transformation);

      /*! Deletes the passed transformation info after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnTransInfoDel
      * - handleDependentsOnTransInfoDel
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] transformation Pointer to the transformation info that should be deleted.
      * @return The return type depends on the used scenario the the scenario and its interface realization for more information.
      * @pre transformation must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : transformation pointer is null.
      */
      TransformationDeleteReturnType deleteTransformation(TransInfoInferencePointer transformation);

    protected:
      virtual ~IMappingIntegration() {};
      IMappingIntegration() {};

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineTransformation*/
      virtual Result<ConstTransformationInfoPointer> doDefineTransformation(TransInfoInferencePointer newTransformation) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeTransformation*/
      virtual Result<ConstTransformationInfoPointer> doStoreTransformation(TransInfoInferencePointer transformation) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteTransformation*/
      virtual TransformationDeleteReturnType doDeleteTransformation(TransInfoInferencePointer transformation) = 0;

      using EntityInferenceInterface = TIEInference;

      using ProblemInferenceInterface = TPInference;

      /*!Sets the pointer to the interface that should be used to actualize inference elements
       * (e.g. entities or information spaces)*/
      void setEntityInferenceInterface(const EntityInferenceInterface* pInterface);

      /*!Sets the pointer to the interface that should be used to actualize inference elements
       * (e.g. problem statements)*/
      void setProblemInferenceInterface(const ProblemInferenceInterface* pInterface);

      /*!Used to actualize the passed inference elements (e.g. entities or information spaces)*/
      const EntityInferenceInterface* _pEntityInferenceInterface;

      /*!Used to actualize the passed inference elements (e.g. problem statements)*/
      const ProblemInferenceInterface* _pProblemInferenceInterface;

    private:
      IMappingIntegration(const IMappingIntegration&); //not implemented by purpose
      IMappingIntegration& operator=(const IMappingIntegration&); //not implemented by purpose
    };
  } // end namespace core
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapIMappingIntegration.tpp"
#endif

#endif
