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





#ifndef __MAP_I_PROBLEM_INFERENCE_H
#define __MAP_I_PROBLEM_INFERENCE_H

#include "mapOntologyResult.h"
#include "mapIProblemStatementAssociated.h"

#include <vector>

namespace iro
{
	namespace core
	{
		/*! @class IProblemInference
     * @brief Interface of the registration ontology used for inference queries in the context of entities or entity related questions that can be handled without caring about registration.
     *
     * Interface of the registration ontology decorator used for inference queries in the
     * context of problem models and statements. As inference interface it is analog to a
     * pure getter interface. Setting and writing will be done be integration interfaces (IProblemIntegration).
     * This interface is implemented regarding the NVI paradigm.
     *
     * @tparam TPMTraits type that represents the problem model traits.
     * @sa IEntityInference
     * @sa IViewingInference
     * @sa IMappingInference
     * @sa IProblemIntegration
     * @ingroup Inference
     */
		template <typename TPMTraits>
		class IProblemInference
		{
		public:
      using ProblemModelType = typename TPMTraits::Type;
      using ConstProblemModelPointer = typename TPMTraits::ConstPointer;
      using ProblemModelInferencePointer = typename TPMTraits::InferencePointer;

      using ConstProblemModelVectorType = typename std::vector<ConstProblemModelPointer>;

      using ProblemStatementTraitsType = typename TPMTraits::ProblemStatementTraitsType;

      using ProblemStatementType = typename ProblemStatementTraitsType::Type;
      using ConstProblemStatementPointer = typename ProblemStatementTraitsType::ConstPointer;
      using ProblemStatementInferencePointer = typename ProblemStatementTraitsType::InferencePointer;

      using ConstProblemStatementVectorType = typename std::vector<ConstProblemStatementPointer>;
      

      using ProblemAssociatedInterface = IProblemStatementAssociated<ProblemStatementTraitsType>;

      /*! Queries for all ProblemModels that are associated with the given instance
      * (more precise with its associated problem statement) and returns result set.
      * This method is a convenience overload of getAssociatedProblemModels(...).
      *@param [in] pAssociated Const pointer to the entity that is associated with an problem statement.
      *@return a collection containing pointers to all problem models that contain the problem statement
      * and therefor are associated with the passed instance.
      *@pre pAssociated must point to a valid instance.
      *@pre pAssociated must be associated to a problem statement that is defined in the ontology.
      *@exception ::iro::exceptions::InvalidArgument : entity pointer is null.
      *@exception ::iro::exceptions::UndefinedElement : associated problem statement is not defined in the ontology.
      */
			Result<ConstProblemModelVectorType> getAssociatedProblemModels(const ProblemAssociatedInterface* pAssociated) const;

      /*! Queries for all ProblemModels that are associated with the given ProblemStatement and returns the filtered result set.
      *@param [in] ps problem statement whose associated problem models should be returned.
      *@return a collection containing pointers to all problem models that are associated to the passed problem statement
      * If the problem statement is unknown.
      *@pre ps must point to a valid instance.
      *@pre ps must be defined in the ontology (use actualize() in order to check
      * this in before).
      *@exception ::iro::exceptions::InvalidArgument : problem statement pointer is null.
      *@exception ::iro::exceptions::UndefinedElement : problem statement is not defined in the ontology.
      */
			Result<ConstProblemModelVectorType> getAssociatedProblemModels(ProblemStatementInferencePointer ps) const;

			/*! Returns a vector that contains all problem models that are defined in the ontology.
      * @remark Depending on the ontology the returning vector can be very large and thus the function call
      * can be of low performance.
      */
			Result<ConstProblemModelVectorType> getProblemModels() const;

			/*! Returns a vector that contains all problem statements that are defined in the ontology.
      * @remark Depending on the ontology the returning vector can be very large and thus the function call
      * can be of low performance.
      */
			Result<ConstProblemStatementVectorType> getProblemStatements() const;

			/*!Takes the passed problem statement and returns the version of the problem statement (UID equals)
      * that represents the current state of the ontology.
      * @param [in] ps Pointer to the problem statement that should be actualized.
      * @return Smart pointer to the current version of the element. If the problem statement
      * does not exist (any more) in the ontology, a NULL pointer will be returned.
      * @pre ps must point to valid instances.
      * @overload
      * @exception ::iro::exceptions::InvalidArgument : ps is not a valid pointer.*/
			Result<ConstProblemStatementPointer> actualize(ProblemStatementInferencePointer ps) const;

			/*!Takes the passed problem model and returns the version of the problem model (UID equals)
      * that represents the current state of the ontology.
      * @param [in] pm Pointer to the problem model that should be actualized.
      * @return Smart pointer to the current version of the element. If the problem model
      * does not exist (any more) in the ontology, a NULL pointer will be returned.
      * @pre ps must point to valid instances.
      * @overload
      * @exception ::iro::exceptions::InvalidArgument : pm is not a valid pointer.*/
			Result<ConstProblemModelPointer> actualize(ProblemModelInferencePointer pm) const;

    protected:

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getAssociatedProblemModels*/
			virtual Result<ConstProblemModelVectorType> doGetAssociatedProblemModels(ProblemStatementInferencePointer ps) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see geProblemModels*/
			virtual Result<ConstProblemModelVectorType> doGetProblemModels() const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getProblemStatements*/
			virtual Result<ConstProblemStatementVectorType> doGetProblemStatements() const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstProblemStatementPointer> doActualize(ProblemStatementInferencePointer ps) const = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstProblemModelPointer> doActualize(ProblemModelInferencePointer pm) const = 0;

      virtual ~IProblemInference() = default;
			IProblemInference() = default;

		private:
			IProblemInference(const IProblemInference&); //not implemented by purpose
			IProblemInference& operator=(const IProblemInference&); //not implemented by purpose
		};
	} // end namespace core
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapIProblemInference.tpp"
#endif

#endif
