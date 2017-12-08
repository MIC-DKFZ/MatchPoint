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




#ifndef __IRO_INFORMATION_ENTITY_TRAITS_H
#define __IRO_INFORMATION_ENTITY_TRAITS_H

namespace iro
{
    /*! @struct InformationEntityTraits
    * @brief Template for the information entity traits.
    * 
    * The concrete information entity type and its traits are defined
    * in the application scenarios. Each scenario has a specification based
    * on this template.
    * @tparam TIEType Type that represents the information entity.
    * @tparam TEntityIdentificationPolicy Policy that implements an method that check if an entity has a specified UID.
    * The method must regard the following signature: static bool identifyEntity(const Type& pEntity, const UIDType& uid);
    * @tparam TIEPointer Pointer to the information entity type.
    * @tparam TIEConstPointer Const pointer to the information entity type.
    * @tparam TUIDType Type used as UID for the information entity.
    * @tparam TInferencePointer Type used as pointer when type is returned in an inference call/method.
    */
    template <typename TIEType,
      typename TEntityIdentificationPolicy,
      typename TIEPointer = typename TIEType::Pointer,
      typename TIEConstPointer = typename TIEType::ConstPointer,
      typename TInferencePointer = TIEConstPointer>
    struct InformationEntityTraits : TEntityIdentificationPolicy
    {
      using Type = TIEType;
      using Pointer = TIEPointer;
      using ConstPointer = TIEConstPointer;
      using TEntityIdentificationPolicy::UIDType;
      using InferencePointer = TInferencePointer;

      // implemented by TEntityIdentificationPolicy
      // static bool identifyEntity(const Type& pEntity, const UIDType& uid);
    };

} // end namespace iro

#endif
