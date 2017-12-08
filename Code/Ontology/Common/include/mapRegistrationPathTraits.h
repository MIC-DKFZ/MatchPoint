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




#ifndef __MAP_REGISTRATION_PATH_TRAITS_H
#define __MAP_REGISTRATION_PATH_TRAITS_H

namespace iro
{
    /*! @struct RegistrationPathTraits
    * @brief Base template for the registration path traits.
    *
    * The concrete registration path type and its traits are defined
    * in the application scenarios. Each scenario has a template specialization
    * of this template.
    * @tparam TRPType Type that represents the registration path option collection.
    * @tparam TRITraits traits of registration infos.
    * @tparam TTPTraits traits of transformation paths.
    * @tparam TRPPointer Pointer to a registration path option collection.
    * @tparam TRPConstPointer Const pointer to a registration path option collection.
    * @ingroup Traits
    */
  template <typename TRPType,
    typename TRITraits,
    typename TTPTraits,
    typename TRPPointer = typename TRPType::Pointer,
    typename TRPConstPointer = typename TRPType::ConstPointer>
    struct RegistrationPathTraits
    {
      using Type = TRPType;
      using Pointer = TRPPointer;
      using ConstPointer = TRPConstPointer;

      using TransformationPathTraitsType = TTPTraits;
      using InformationEntityTraitsType = typename TTPTraits::InformationEntityTraitsType;
      using InformationSpaceTraitsType = typename TTPTraits::InformationSpaceTraitsType;
      using ProblemStatementTraitsType = typename TTPTraits::ProblemStatementTraitsType;
      using TransformationInfoTraitsType = typename TTPTraits::TransformationInfoTraitsType;
      using RegistrationInfoTraitsType = TRITraits;
    };

} // end namespace iro

#endif
