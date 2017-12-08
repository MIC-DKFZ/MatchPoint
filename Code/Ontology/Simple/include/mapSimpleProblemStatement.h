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




#ifndef __MAP_SIMPLE_PROBLEM_STATEMENT_H
#define __MAP_SIMPLE_PROBLEM_STATEMENT_H

#include "mapProblemStatementBase.h"
#include "mapProblemStatementTraits.h"
#include "mapBoostUIDPolicy.h"

namespace iro
{
  namespace scenario
  {
    /*! @class SimpleProblemStatement
    * @brief Simple definition for problem statements.
    * @ingroup Simple
    */
    typedef ProblemStatementBase<BoostUIDPolicy> SimpleProblemStatement;

    using SimpleProblemStatementTraits = ProblemStatementTraits<SimpleProblemStatement>;

  } // end namespace scenario

} // end namespace iro

#endif
