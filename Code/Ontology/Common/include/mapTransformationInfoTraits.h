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




#ifndef __IRO_TRANSFORMATION_INFO_TRAITS_H
#define __IRO_TRANSFORMATION_INFO_TRAITS_H

#include "mapIProblemStatementAssociated.h"
#include "mapIProblemComplianceDefinition.h"
#include "mapIInformationSpaceConnector.h"

namespace iro
{
    /*! @struct TransformationInfoTraits
    * @brief Template for the transformation info traits.
    * A Transformation info instance specifies a way to map information
    * from one information space to an other.
    * It may contain, if available, the transformation info for discrete data
    * (e.g. pixel images; inverse mapping; getDiscreteTransformation)
    * and continuous data (e.g. point sets; direct mapping, getContinousTransformation).\n\n
    * The concrete transformation info type and its traits are defined
    * in the application scenarios. Each scenario has a template specialization
    * of this template.
    * @tparam TTIType Type that represents the transformation info entity.
    * @tparam TIETraits traits of information entities.
    * @tparam TISTraits traits of information spaces.
    * @tparam TPSTraits traits of problem statements.
    * @tparam TTIPointer Pointer to the transformation info.
    * @tparam TTIConstPointer Const pointer to the transformation info.
    * @tparam TInferencePointer Type used as pointer when type is returned in an inference call/method.
    * @tparam TUIDType Type used to represent UIDs.
    */
  template <typename TTIType,
    typename TIETraits,
    typename TISTraits,
    typename TPSTraits,
    typename TTIPointer = typename TTIType::Pointer,
    typename TTIConstPointer = typename TTIType::ConstPointer,
    typename TInferencePointer = TTIConstPointer,
    typename TUIDType = typename TTIType::UIDType>
    struct TransformationInfoTraits
    {
      using Type = TTIType;
      using Pointer = TTIPointer;
      using ConstPointer = TTIConstPointer;
      using InferencePointer = TInferencePointer;

      using UIDType = TUIDType;

      using InformationEntityTraitsType = TIETraits;
      using InformationSpaceTraitsType = TISTraits;
      using ProblemStatementTraitsType = TPSTraits;

      using ConnectorInterface = IInformationSpaceConnector<InformationSpaceTraitsType>;
      using ConstISPointer = typename InformationSpaceTraitsType::ConstPointer;
      using ProblemAssociatedInterface = IProblemStatementAssociated< ProblemStatementTraitsType >;
      using ProblemComplianceInterface = IProblemComplianceDefinition<typename ProblemStatementTraitsType::Type>;
      using ConstProblemPointer = typename ProblemStatementTraitsType::ConstPointer;
    };

} // end namespace iro

#endif
