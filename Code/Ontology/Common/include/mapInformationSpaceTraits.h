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




#ifndef __MAP_INFORMATION_SPACE_TRAITS_H
#define __MAP_INFORMATION_SPACE_TRAITS_H

namespace iro
{

    /*! @struct InformationSpaceTraits
    * @brief Template for the information space traits.
    * 
    * The concrete information space type and its traits are defined
    * in the application scenarios. Each scenario has a specification based
    * on this template.
    * @tparam TISType Type that represents the information space
    * @tparam TISPointer Pointer to the information space type
    * @tparam TISConstPointer Const pointer to the information space type
    * @tparam TInferencePointer Type used as pointer when type is returned in an inference call/method.
    * @tparam TUIDType Type used to represent UIDs.

    */
  template <typename TISType, typename TISPointer = typename TISType::Pointer, typename TISConstPointer = typename TISType::ConstPointer,
    typename TInferencePointer = TISConstPointer, typename TUIDType = typename TISType::UIDType>
    struct InformationSpaceTraits
    {
      using Type = TISType;
      using Pointer = TISPointer;
      using ConstPointer = TISConstPointer;
      using InferencePointer = TInferencePointer;
      using UIDType = TUIDType;
    };

} // end namespace iro

#endif
