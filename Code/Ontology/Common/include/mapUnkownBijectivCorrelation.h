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


#ifndef __MAP_UNKOWN_BIJECTIV_CORRELATION_H
#define __MAP_UNKOWN_BIJECTIV_CORRELATION_H

#include "mapUnkownInjectivCorrelation.h"

#include "mapMAPOntologyExports.h"

namespace iro
{

  /** @class UnkownBijectivCorrelation
   * This class defines a semantic identity that is unkown but bijective.
   * Thus you know that to entities have exact correspondence (e.g. the same set of markers in different images)
   * but it is unknown how they match exactly (e.g. which marker is displayed in certain renderings in the image).
   * @ingroup CorrelationType*/
  MAPOntology_EXPORT class UnkownBijectivCorrelation : public UnkownInjectivCorrelation
  {
  public:
    typedef UnkownBijectivCorrelation                           Self;
    typedef std::shared_ptr<UnkownBijectivCorrelation>        Pointer;
    typedef std::shared_ptr<const UnkownBijectivCorrelation>  ConstPointer;

    /** Returns the identifier name of the correlation type.*/
    virtual String getName() const;

    virtual ~UnkownBijectivCorrelation();
    UnkownBijectivCorrelation();

  private:
    UnkownBijectivCorrelation(const UnkownBijectivCorrelation&); //not implemented by purpose
    UnkownBijectivCorrelation& operator=(const UnkownBijectivCorrelation&); //not implemented by purpose
  };
} // end namespace iro

#endif
