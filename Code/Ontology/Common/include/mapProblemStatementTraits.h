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




#ifndef __MAP_PROBLEM_STATEMENT_TRAITS_H
#define __MAP_PROBLEM_STATEMENT_TRAITS_H

namespace iro
{
    /*! @struct ProblemStatementTraits
    * @brief Template for the problem statement traits.
    * ProblemStatements define certain registration problems. E.G.:
    * Pelvis centric rigid registration of reference MRI images of two given studies.\n\n
    *
    * The concrete problem statement type and its traits are defined
    * in the application scenarios. Each scenario has a template specialization
    * of this template.
    * @tparam TPSType Type that represents the problem statement.
    * @tparam TPSPointer Pointer to the problem statement instance.
    * @tparam TPSConstPointer Const pointer to a problem statement instance.
    * @tparam TPSInferencePointer Pointer used for inference resultes of problem statements.
    */
    template <typename TPSType, typename TPSPointer = typename TPSType::Pointer, typename TPSConstPointer = typename TPSType::ConstPointer, typename TPSInferencePointer = typename TPSType::ConstPointer>
    struct ProblemStatementTraits
    {
      using Type = TPSType;
      using Pointer = TPSPointer;
      using ConstPointer = TPSConstPointer;
      using InferencePointer = TPSInferencePointer;
    };

} // end namespace iro

#endif
