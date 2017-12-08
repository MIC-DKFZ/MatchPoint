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




#ifndef __MAP_ALGORITHM_EXECUTION_INFO_TRAITS_H
#define __MAP_ALGORITHM_EXECUTION_INFO_TRAITS_H

namespace iro
{

    /*! @struct InformationEntityTraits
    * @brief Template for the execution info traits.
    * 
    * The concrete algorithm execution info type and its traits are defined
    * in the application scenarios. Each scenario has a template specialization
    * of this template.
    * @tparam TAEIType Type that represents the algorithm execution info.
    * @tparam TAEIPointer Pointer to the algorithm execution info instance.
    * @tparam TAEIConstPointer Const pointer to a algorithm execution info instance.
    */
  template <typename TAEIType, typename TAEIPointer = typename TAEIType::Pointer, typename TAEIConstPointer = typename TAEIType::ConstPointer>
    struct AlgorithmExecutionInfoTraits
    {
      using Type = TAEIType;
      using Pointer = TAEIPointer;
      using ConstPointer = TAEIConstPointer;
    };

} // end namespace iro


#endif
