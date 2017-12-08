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





#include "mapOntologyExceptions.h"
namespace iro
{
  namespace exceptions
  {

    InvalidIS::
      InvalidIS (const String& what_arg) : InvalidArgument (what_arg)
    {
    };

    InvalidMovingIS::
      InvalidMovingIS (const String& what_arg) : InvalidIS (what_arg)
    {
    };

    InvalidTargetIS::
      InvalidTargetIS (const String& what_arg) : InvalidIS (what_arg)
    {
    };

    InvalidDataRepresentation::
      InvalidDataRepresentation (const String& what_arg) : InvalidArgument (what_arg)
    {
    };

    UndefinedElement::
      UndefinedElement (const String& what_arg) : InvalidArgument (what_arg)
    {
    };


  } // end namespace exceptions
} // end namespace iro

