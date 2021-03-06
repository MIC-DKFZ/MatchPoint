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





#include "mapInjectivCorrelation.h"

namespace iro
{

    String InjectivCorrelation::
      getName() const
    {
      return "InjectivCorrelation";
    };

    InjectivCorrelation::
      ~InjectivCorrelation() = default;

    InjectivCorrelation::
      InjectivCorrelation() = default;

} // end namespace iro
