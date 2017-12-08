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





#ifndef __MAP_MAPPING_ERROR_H
#define __MAP_MAPPING_ERROR_H

namespace iro
{

/*! @struct MappingError
* Indication the supported scope of a mapping.
* The enumeration is ordered by there "fatality".
*
* Possible values:
* - No failure 
* - There is a fitting, but no Mapping guarantee
* - No TransformationPath for the needed data type (meaning: there are tranformation paths but not for the required data type support)
* - No TransformationPath available
*/
  struct MappingError
  {
    enum Type {
      NoFailure = 0, /*!< No failure. */
      NoMappingGuarantee = 1, /*!< No TransformationPath with sufficient FOV/Mapping guarantee available. */
      NoDataSupport = 2, /*!< No TransformationPath for the needed data type available. */
      NoPath = 4, /*!< No TransformationPath available. */
    };
  };

} // end namespace iro

#endif
