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


#ifndef __MAP_DATA_REPRESENTATION_H
#define __MAP_DATA_REPRESENTATION_H

#include "mapMAPOntologyExports.h"

namespace iro
{

/*! @struct DataRepresentation
* Struct defining the enum that indicates if an entity can be regarded as
* continuous or discrete. This information is important to select proper
* transformations in order to map the entity.
*
* Possible values:
* - Discrete (e.g. voxel images)
* - Continuous (e.g. points)
*/
  struct MAPOntology_EXPORT DataRepresentation
  {
    enum Type {
      Discrete = 1,
      Continuous = 2
    };
  };

/*! @struct DataRepresentationSupport
Enum indicates the wanted or given support of continuous or discrete data

Possible values:
- Arbitrary
- Discrete
- Continuous
- All
*/
  struct MAPOntology_EXPORT DataRepresentationSupport
  {
    enum Type {
      Arbitrary = 0,
      Discrete = 1,
      Continuous = 2,
      All = 3
    };
  };

  /** Conversion function for data representation type to data
  * representation support type.*/
  MAPOntology_EXPORT DataRepresentationSupport::Type convertToSupport(DataRepresentation::Type data);

} // end namespace iro

#endif
