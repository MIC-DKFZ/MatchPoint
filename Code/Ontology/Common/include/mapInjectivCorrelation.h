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


#ifndef __MAP_INJECTIV_CORRELATION_H
#define __MAP_INJECTIV_CORRELATION_H

#include "mapUnkownBijectivCorrelation.h"

#include "mapMAPOntologyExports.h"

namespace iro
{

  /** @class InjectivCorrelation
   * This class defines a semantic identity that is known but injective.
   * Thus you know the exact correspondence between the entities but it cover the entities only in parts
   * (e.g. the same set of intrinsic landmarks in different images and it is not guaranteed that all landmarks
   * are visible in all images. But the landmarks are uniquely identified, so when there is a landmark in to images
   * you are able to determin this).
   * @ingroup CorrelationType*/
  MAPOntology_EXPORT class InjectivCorrelation : public UnkownBijectivCorrelation
  {
  public:
    typedef InjectivCorrelation                           Self;
    typedef std::shared_ptr<InjectivCorrelation>        Pointer;
    typedef std::shared_ptr<const InjectivCorrelation>  ConstPointer;

    /** Returns the identifier name of the correlation type.*/
    virtual String getName() const;

    virtual ~InjectivCorrelation();
    InjectivCorrelation();

  private:
    InjectivCorrelation(const InjectivCorrelation&); //not implemented by purpose
    InjectivCorrelation& operator=(const InjectivCorrelation&); //not implemented by purpose
  };

} // end namespace iro

#endif
