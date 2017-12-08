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




#ifndef __MAP_TRANSFORMATION_PATH_TRAITS_H
#define __MAP_TRANSFORMATION_PATH_TRAITS_H

namespace iro
{
    /*! @struct TransformationPathTraits
    * @brief Template for the transformation path traits.
    * @tparam TTPType Type that represents the transformation path.
    * @tparam TIETraits traits of information entities.
    * @tparam TISTraits traits of information spaces.
    * @tparam TPSTraits traits of problem statements.
    * @tparam TTITraits traits of transformation infos.
    * @tparam TTPPointer Pointer to a transformation path.
    * @tparam TTPConstPointer Const pointer to a transformation path.
    * @ingroup Traits
    */
  template <typename TTPType,
    typename TIETraits,
    typename TISTraits,
    typename TPSTraits,
    typename TTITraits,
    typename TTPPointer = typename TTPType::Pointer,
    typename TTPConstPointer = typename TTPType::ConstPointer>
    struct TransformationPathTraits
    {
      using Type = TTPType;
      using Pointer = TTPPointer;
      using ConstPointer = TTPConstPointer;

      using InformationEntityTraitsType = TIETraits;
      using InformationSpaceTraitsType = TISTraits;
      using ProblemStatementTraitsType = TPSTraits;
      using TransformationInfoTraitsType = TTITraits;
    };

} // end namespace iro

#endif
