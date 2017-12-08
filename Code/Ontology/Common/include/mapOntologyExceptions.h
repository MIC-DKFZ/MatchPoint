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

    typedef ::std::invalid_argument InvalidArgument;
      
    /** @class InvalidIS
    * Exception class that is thrown when an problem correlated with
    * information spaces occures
    * @ingroup Exception*/
    MAPOntology_EXPORT class InvalidIS : public InvalidArgument
    {
    public:
      explicit InvalidIS (const String& what_arg);
    };

    /** @class InvalidMovingIS
    * Exception class that is thrown when an problem correlated with
    * moving information spaces occures
    * @ingroup Exception*/
    MAPOntology_EXPORT class InvalidMovingIS : public InvalidIS
    {
    public:
      explicit InvalidMovingIS (const String& what_arg);
    };

    /** @class InvalidTargetIS
    * Exception class that is thrown when an problem correlated with
    * target information spaces occures
    * @ingroup Exception*/
    MAPOntology_EXPORT class InvalidTargetIS : public InvalidIS
    {
    public:
      explicit InvalidTargetIS (const String& what_arg);
    };

   /** @class InvalidDataRepresentation
    * Exception class that is thrown when an problem correlated with
    * invalid data representation support occures
    * @ingroup Exception*/
    MAPOntology_EXPORT class InvalidDataRepresentation : public InvalidArgument
    {
    public:
      explicit InvalidDataRepresentation (const String& what_arg);
    };

    /** @class UndefinedElement
    * Exception class that is thrown when an element is used for
    * inference or integration that is not part of the ontology
    * @ingroup Exceptions*/
    MAPOntology_EXPORT class UndefinedElement : public InvalidArgument
    {
    public:
      explicit UndefinedElement (const String& what_arg);
    };

  } // end namespace exceptions
} // end namespace iro

#endif
