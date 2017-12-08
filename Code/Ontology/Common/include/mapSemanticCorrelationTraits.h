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




#ifndef __IRO_SEMANTIC_CORRELATION_TRAITS_H
#define __IRO_SEMANTIC_CORRELATION_TRAITS_H

namespace iro
{
    /*! @struct SemanticCorrelationTraits
    * @brief Template for the semantic correlation traits.
    * The concrete semantic correlation type and its traits are defined
    * in the application scenarios. Each scenario has a template specialization
    * of this template.
    * @tparam TSCType Type that represents a semantic correlation
    * @tparam TIETraits Traits of information entities
    * @tparam TSCPointer Pointer to a semantic correlation
    * @tparam TSCConstPointer Const pointer to a semantic correlation
    * @tparam TInferencePointer Type used as pointer when type is returned in an inference call/method.
    */
  template <typename TSCType, typename TIETraits, typename TSCPointer = typename TSCType::Pointer, typename TSCConstPointer = typename TSCType::ConstPointer,
    typename TInferencePointer = TSCConstPointer>
    struct SemanticCorrelationTraits
    {
      using Type = TSCType;
      using Pointer = TSCPointer;
      using ConstPointer = TSCConstPointer;
      using InferencePointer = TInferencePointer;

      using InformationEntityTraitsType = TIETraits;
    };

} // end namespace iro

#endif
