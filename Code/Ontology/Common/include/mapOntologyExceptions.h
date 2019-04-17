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


#ifndef __MAP_EXCEPTIONS_H
#define __MAP_EXCEPTIONS_H

#include <stdexcept>
#include "mapOntologyString.h"

#include "mapMAPOntologyExports.h"

namespace iro
{
  namespace exceptions
  {

    using InvalidArgument = ::std::invalid_argument;
      
    /** @class InvalidIS
    * Exception class that is thrown when an problem correlated with
    * information spaces occures
    * @ingroup Exception*/
    class MAPOntology_EXPORT InvalidIS : public InvalidArgument
    {
    public:
      explicit InvalidIS (const String& what_arg);
    };

    /** @class InvalidMovingIS
    * Exception class that is thrown when an problem correlated with
    * moving information spaces occures
    * @ingroup Exception*/
    class MAPOntology_EXPORT InvalidMovingIS : public InvalidIS
    {
    public:
      explicit InvalidMovingIS (const String& what_arg);
    };

    /** @class InvalidTargetIS
    * Exception class that is thrown when an problem correlated with
    * target information spaces occures
    * @ingroup Exception*/
    class MAPOntology_EXPORT InvalidTargetIS : public InvalidIS
    {
    public:
      explicit InvalidTargetIS (const String& what_arg);
    };

   /** @class InvalidDataRepresentation
    * Exception class that is thrown when an problem correlated with
    * invalid data representation support occures
    * @ingroup Exception*/
    class MAPOntology_EXPORT InvalidDataRepresentation : public InvalidArgument
    {
    public:
      explicit InvalidDataRepresentation (const String& what_arg);
    };

    /** @class UndefinedElement
    * Exception class that is thrown when an element is used for
    * inference or integration that is not part of the ontology
    * @ingroup Exceptions*/
    class MAPOntology_EXPORT UndefinedElement : public InvalidArgument
    {
    public:
      explicit UndefinedElement (const String& what_arg);
    };

  } // end namespace exceptions
} // end namespace iro

#endif
