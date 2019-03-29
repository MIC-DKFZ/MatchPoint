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





#ifndef __MAP_I_SEMANTIC_CORRELATION_TYPE_H
#define __MAP_I_SEMANTIC_CORRELATION_TYPE_H

#include "mapOntologyString.h"
#include <memory>

#include "mapMAPOntologyExports.h"

namespace iro
{

  /** @class ISemanticCorrelationType
   *Interface for all kind of correlation types.
   * @ingroup CorrelationType Interfaces
   */
  class MAPOntology_EXPORT ISemanticCorrelationType
  {
  public:
    using Self = ISemanticCorrelationType;
    using Pointer = std::shared_ptr<ISemanticCorrelationType>;
    using ConstPointer = std::shared_ptr<const ISemanticCorrelationType>;

    /** Checks if the type of this and pType are equal by comparing there names.*/
    bool equals(const ISemanticCorrelationType* pType) const;

    /** Returns the identifier name of the correlation type.*/
    virtual String getName() const = 0;

  protected:
    virtual ~ISemanticCorrelationType();
    ISemanticCorrelationType();
  private:
    ISemanticCorrelationType(const ISemanticCorrelationType&) = delete; //not implemented by purpose
    ISemanticCorrelationType& operator=(const ISemanticCorrelationType&) = delete; //not implemented by purpose
  };
} // end namespace iro

#endif
