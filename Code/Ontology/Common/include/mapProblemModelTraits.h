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




#ifndef __MAP_PROBLEM_MODEL_TRAITS_H
#define __MAP_PROBLEM_MODEL_TRAITS_H

namespace iro
{
    /*! @struct ProblemModelTraits
    * @brief Template for the problem model traits.
    * Problem models specify/represent a distinct abstracted view (the problem model) on a real world problem.
    * This is motivated by the assumption that a registration, as a model for a real world correlation,
    * might introduce abstraction errors. Thus solutions based on this registration are only simplified models
    * for the real world problem and its solution. ProblemStatements that are grouped in one ProblemModel are
    * assumed to be valid in the same abstracted view and thus registrations of these ProblemStatements may be
    * "used" together. Therefor an entity should not be mapped consecutively by registrations that are not
    * affiliated to the same ProblemModel via the according ProblemStatements because there is no accepted
    * "view" on the real world problem allowing there combination.\n
    * E.g.: Entities mapped prostate centric should not be displayed together
    * with entities that are mapped pelvis centric.\n\n
    *
    * The concrete problem model type and its traits are defined
    * in the application scenarios. Each scenario has a template specialization
    * of this template.
    * @tparam TPMType Type that represents the problem model.
    * @tparam TPMPointer Pointer to a problem model.
    * @tparam TPMConstPointer Const pointer to a problem model.
    * @tparam TInferencePointer Type used as pointer when type is returned in an inference call/method.

    */
  template <typename TPMType,
    typename TPMPointer = typename TPMType::Pointer,
    typename TPMConstPointer = typename TPMType::ConstPointer,
    typename TInferencePointer = TPMConstPointer>
    struct ProblemModelTraits
    {
      using Type = TPMType;
      using Pointer = TPMPointer;
      using ConstPointer = TPMConstPointer;
      using InferencePointer = TInferencePointer;

      using ProblemStatementTraitsType = typename Type::ProblemStatementTraitsType;
    };

} // end namespace iro

#endif
