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




#ifndef __IRO_SIMPLE_TRANSFORMATION_PATH_H
#define __IRO_SIMPLE_TRANSFORMATION_PATH_H

#include "mapTransformationPathBase.h"
#include "mapTransformationPathTraits.h"
#include "mapSimpleInformationSpace.h"
#include "mapSimpleTransformationInfo.h"

namespace iro
{
  namespace scenario
  {
    /*! @class SimpleTransformationPath
    * @brief Transformation path in the Simple scenario.
    * @ingroup Simple*/
    using SimpleTransformationPath = ::iro::TransformationPathBase<SimpleTransformationInfoTraits, SimpleInformationSpaceTraits, SimpleProblemStatementTraits>;

    using SimpleTransformationPathTraits = ::iro::TransformationPathTraits<SimpleTransformationPath, SimpleInformationEntityTraits, SimpleInformationSpaceTraits, SimpleProblemStatementTraits, SimpleTransformationInfoTraits>;
  
  } // end namespace scenario

} // end namespace iro

#endif
