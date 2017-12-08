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



#ifndef __MAP_SIMPLE_PROBLEM_MODEL_H
#define __MAP_SIMPLE_PROBLEM_MODEL_H

#include "mapOntologyString.h"
#include "mapSimpleProblemStatement.h"
#include "mapProblemModelTraits.h"
#include "mapProblemModelBase.h"
#include "mapBoostUIDPolicy.h"

namespace iro
{
  namespace scenario
  {

    /*! @class SimpleProblemModel
    * @brief Simple definition for problem models.
    * @ingroup Simple
    */
    using SimpleProblemModel = ProblemModelBase<SimpleProblemStatementTraits, BoostUIDPolicy>;
    using SimpleProblemModelTraits = ProblemModelTraits<SimpleProblemModel>;

  } // end namespace scenario

} // end namespace iro

#endif
