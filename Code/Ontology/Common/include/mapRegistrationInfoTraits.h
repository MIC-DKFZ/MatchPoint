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




#ifndef __IRO_REGISTRATION_INFO_TRAITS_H
#define __IRO_REGISTRATION_INFO_TRAITS_H

namespace iro
{

    /*! @struct RegistrationInfoTraits
    * @brief Template for the registration info traits.
    * @tparam TRIType Type that represents the registration info.
    * @tparam TISTraits traits of information spaces.
    * @tparam TPSTraits traits of problem statements.
    * @tparam TTITraits traits of transformation infos.
    * @tparam TRIPointer Pointer to a registration info.
    * @tparam TRIConstPointer Const pointer to a registration info.
    * @tparam TInferencePointer Type used as pointer when type is returned in an inference call/method.
    * @ingroup Traits
    */
  template <typename TRIType,
    typename TISTraits,
    typename TPSTraits,
    typename TTITraits,
    typename TRIPointer = typename TRIType::Pointer,
    typename TRIConstPointer = typename TRIType::ConstPointer,
    typename TInferencePointer = TRIConstPointer>
    struct RegistrationInfoTraits
    {
      using Type = TRIType;
      using Pointer = TRIPointer;
      using ConstPointer = TRIConstPointer;
      using InferencePointer = TInferencePointer;

      using InformationSpaceTraitsType = TISTraits;
      using ProblemStatementTraitsType = TPSTraits;

      using ConstISPointer = typename InformationSpaceTraitsType::ConstPointer;
      using ConstProblemPointer = typename ProblemStatementTraitsType::ConstPointer;

      using TransformationInfoTraitsType = TTITraits;
      using TransformationInfoType = typename TransformationInfoTraitsType::Type;
      using ConstTransformationInfoPointer = typename TransformationInfoTraitsType::ConstPointer;
      using TransformationInfoPointer = typename TransformationInfoTraitsType::Pointer;
    };

} // end namespace iro

#endif
