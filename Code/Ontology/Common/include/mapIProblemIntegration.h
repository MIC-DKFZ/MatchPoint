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





#ifndef __MAP_I_PROBLEM_INTEGRATION_H
#define __MAP_I_PROBLEM_INTEGRATION_H

#include "mapOntologyResult.h"

namespace iro
{
  namespace core
  {
    /*! @class IProblemIntegration
    * @brief Interface of the registration ontology decorator used for integration queries in the context of entities or entity
    * related information that is independent from registration/transformation.
    *
    * As integration interface it is analog to a pure setter interface.
    * Getting will be done be inference interfaces (IProblemInference).
    * This interface is implemented regarding the NVI paradigm.
    *
    * @tparam TIETraits type that define the traits of problem models.
    * @tparam TPInference type of the problem inference interface that should be used.
    * @tparam TPSDReturnType type that is returned by problem statement delete operations.
    * @tparam TPMDReturnType type that is returned by problem model delete operations.
    * @sa IProblemIntegration
    * @sa IMappingIntegration
    * @sa IProblemInference
    * @ingroup Integration
    */
    template <typename TPMTraits, typename TPInference, typename TPSDReturnType = bool, typename TPMDReturnType = bool>
    class IProblemIntegration
    {
    public:
      typedef typename TPMTraits::Type                 ProblemModelType;
      typedef typename TPMTraits::ConstPointer         ConstProblemModelPointer;
      typedef typename TPMTraits::InferencePointer     ProblemModelInferencePointer;

      using ProblemStatementTraitsType = typename TPMTraits::ProblemStatementTraitsType;

      typedef typename ProblemStatementTraitsType::Type             ProblemStatementType;
      typedef typename ProblemStatementTraitsType::ConstPointer     ConstProblemStatementPointer;
      typedef typename ProblemStatementTraitsType::InferencePointer ProblemStatementInferencePointer;

      typedef typename std::vector<ConstProblemStatementPointer>    ConstProblemStatementVectorType;    

      typedef TPSDReturnType   StatementDeleteReturnType;
      typedef TPMDReturnType    ModelDeleteReturnType;

      /*! Defines and stores the copy of the passed statement after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleExistenceOnStatementDef
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @param [in] pNewStatement Pointer to the problem statement that should be added as definition to the ontology.
      * @return Returns the entity after the insertion of the definition into the ontology.
      * @pre pNewStatement must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pNewStatement pointer is null.
      */
      Result<ConstProblemStatementPointer> defineProblemStatement(ProblemStatementInferencePointer pNewStatement);

      /*! Stores the copy of the passed statement or commits the changes between the passed version of the statement and the
      * one stored in the ontology after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnStatementStore
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] pStatement Pointer to the statement whose changes should be commited to the ontology.
      * @return Returns the statement after the changes are commited to the ontology.
      * @pre pStatement must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pStatement is null.
      */
      Result<ConstProblemStatementPointer> storeProblemStatement(ProblemStatementInferencePointer pStatement);

      /*! Deletes the passed statement after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnStatementDel
      * - handleDependentsOnStatementDel
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] pStatement Pointer to the statement that should be deleted.
      * @return The return type depends on the used scenario the the scenario and its interface realization for more information.
      * @pre pStatement must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pStatement pointer is null.
      */
      StatementDeleteReturnType deleteProblemStatement(ProblemStatementInferencePointer pStatement);

      /*! Defines and stores the copy of the passed model after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleExistenceOnModelDef
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @param [in] pNewModel Pointer to the problem model that should be added as definition to the ontology.
      * @return Returns the entity after the insertion of the definition into the ontology.
      * @pre pNewModel must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pNewModel pointer is null.
      */
      Result<ConstProblemModelPointer> defineProblemModel(ProblemModelInferencePointer pNewModel);

      /*! Stores the copy of the passed model or commits the changes between the passed version of the model and the
      * one stored in the ontology after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnModelStore
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] pModel Pointer to the model whose changes should be committed to the ontology.
      * @return Returns the model after the changes are committed to the ontology.
      * @pre pModel must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pModel is null.
      */
      Result<ConstProblemModelPointer> storeProblemModel(ProblemModelInferencePointer pModel);

      /*! Deletes the passed model after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnModelDel
      * - handleDependentsOnModelDel
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] pModel Pointer to the model that should be deleted.
      * @return The return type depends on the used scenario the the scenario and its interface realization for more information.
      * @pre pModel must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pModel pointer is null.
      */
      ModelDeleteReturnType deleteProblemModel(ProblemModelInferencePointer pModel);


    protected:
      virtual ~IProblemIntegration() {};
      IProblemIntegration() {};

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineProblemStatement*/
      virtual Result<ConstProblemStatementPointer> doDefineProblemStatement(ProblemStatementInferencePointer pNewStatement) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeProblemStatement*/
      virtual Result<ConstProblemStatementPointer> doStoreProblemStatement(ProblemStatementInferencePointer pStatement) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteProblemStatement*/
      virtual StatementDeleteReturnType doDeleteProblemStatement(ProblemStatementInferencePointer pStatement) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineProblemModel*/
      virtual Result<ConstProblemModelPointer> doDefineProblemModel(ProblemModelInferencePointer pNewModel) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeProblemModel*/
      virtual Result<ConstProblemModelPointer> doStoreProblemModel(ProblemModelInferencePointer pModel) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteProblemModel*/
      virtual ModelDeleteReturnType doDeleteProblemModel(ProblemModelInferencePointer pModel) = 0;

      using ProblemInferenceInterface = TPInference;
      
      /*!Sets the pointer to the interface that should be used to actualze inference elements
       * (e.g. entities or information spaces)*/
      void setProblemInferenceInterface(const ProblemInferenceInterface* pInterface);

      /*!Used to actualize the passed inference elements (e.g. entities or information spaces)*/
      const ProblemInferenceInterface* _pProblemInferenceInterface;

    private:
      IProblemIntegration(const IProblemIntegration&); //not implemented by purpose
      IProblemIntegration& operator=(const IProblemIntegration&); //not implemented by purpose
    };
  } // end namespace core
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapIProblemIntegration.tpp"
#endif

#endif
