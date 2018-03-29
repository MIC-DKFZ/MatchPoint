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


#ifndef __MAP_UNKOWN_INJECTIV_CORRELATION_H
#define __MAP_UNKOWN_INJECTIV_CORRELATION_H

#include "mapISemanticCorrelationType.h"

#include "mapMAPOntologyExports.h"

namespace iro
{

  /** @class UnkownInjectivCorrelation
   * This class defines a semantic identity that is unknown but injective.
   * Thus you know that the entities are partly correspondent
   * (e.g. the same set of markers in different images but it is not guaranteed
   * that all landmarks are visible in all images), but you don't know which parts
   * correspond. The weakest of all correlations.
   * @ingroup CorrelationType*/
  class MAPOntology_EXPORT UnkownInjectivCorrelation : public ISemanticCorrelationType
  {
  public:
    typedef UnkownInjectivCorrelation                           Self;
    typedef std::shared_ptr<UnkownInjectivCorrelation>        Pointer;
    typedef std::shared_ptr<const UnkownInjectivCorrelation>  ConstPointer;

    /** Returns the identifier name of the correlation type.*/
    virtual String getName() const;

    virtual ~UnkownInjectivCorrelation();
    UnkownInjectivCorrelation();

  private:
    UnkownInjectivCorrelation(const UnkownInjectivCorrelation&); //not implemented by purpose
    UnkownInjectivCorrelation& operator=(const UnkownInjectivCorrelation&); //not implemented by purpose
  };
} // end namespace iro

#endif
