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





#include "mapISemanticCorrelationType.h"
#include "mapOntologyExceptions.h"

namespace iro
{

    /** Checks if the type of this and pType are equal by comparing there names.*/
    bool ISemanticCorrelationType::
      equals(const ISemanticCorrelationType* pType) const
    {
      if (pType == nullptr) { throw exceptions::InvalidArgument("Passed correlation type pointer is NULL.");
}

      return this->getName() == pType->getName();
    };

    ISemanticCorrelationType::
      ~ISemanticCorrelationType() = default;

    ISemanticCorrelationType::
      ISemanticCorrelationType() = default;

} // end namespace iro

