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




#ifndef __MAP_REG_PATH_OPTION_COLLECTION_TRAITS_H
#define __MAP_REG_PATH_OPTION_COLLECTION_TRAITS_H

namespace iro
{
    /*! @struct PathOptionCollectionTraits
    * @brief Template for path option traits.
    *
    * The concrete path option collection type and its traits are defined
    * in the application scenarios. Each scenario has a template specialization
    * of this template.
    * @tparam TPOCType Type that represents the path option collection.
    * @tparam TPOTraits traits of path options entities.
    * @tparam TPOCPointer Pointer to a path option collection.
    * @tparam TPOCConstPointer Const pointer to a path option collection.
    */
  template <typename TPOCType,
    typename TPOTraits,
    typename TPOCPointer = typename TPOCType::Pointer,
    typename TPOCConstPointer = typename TPOCType::ConstPointer>
    struct PathOptionCollectionTraits
    {
      using Type = TPOCType;
      using Pointer = TPOCPointer;
      using ConstPointer = TPOCConstPointer;

      using OptionTraitsType = TPOTraits;
      using OptionType = typename OptionTraitsType::Type;
    };

} // end namespace iro

#endif
