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




#ifndef __IRO_REG_PATH_OPTION_TRAITS_H
#define __IRO_REG_PATH_OPTION_TRAITS_H

namespace iro
{
    /*! @struct PathOptionTraits
    * @brief Template for path option traits.
    *
    * The concrete registration path option type and its traits are defined
    * in the application scenarios. Each scenario has a template specialization
    * of this template.
    * @tparam TPOType Type that represents the path option.
    * @tparam TPOPointer Pointer to a path option.
    * @tparam TPOConstPointer Const pointer to a path option.
    */
  template <typename TPOType,
    typename TPOPointer = typename TPOType::Pointer,
    typename TPOConstPointer = typename TPOType::ConstPointer>
    struct PathOptionTraits
    {
      using Type = TPOType;
      using Pointer = TPOPointer;
      using ConstPointer = TPOConstPointer;

      using PathTraitsType = typename Type::PathTraitsType;
    };

} // end namespace iro

#endif
