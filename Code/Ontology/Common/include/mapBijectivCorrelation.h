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





#ifndef __MAP_BIJECTIV_CORRELATION_H
#define __MAP_BIJECTIV_CORRELATION_H

#include "mapInjectivCorrelation.h"

#include "mapMAPOntologyExports.h"

namespace iro
{

  /** @class BijectivCorrelation
   * This class defines a semantic identity that is known and bijective.
   * Thus you know for the exact correspondence of one entity (element)
   * in the other information space.
   * @ingroup CorrelationType*/
  class MAPOntology_EXPORT BijectivCorrelation : public InjectivCorrelation
  {
  public:
    typedef BijectivCorrelation                           Self;
    typedef std::shared_ptr<BijectivCorrelation>        Pointer;
    typedef std::shared_ptr<const BijectivCorrelation>  ConstPointer;

    /** Returns the identifier name of the correlation type.*/
    virtual String getName() const;

    virtual ~BijectivCorrelation();
    BijectivCorrelation();

  private:
    BijectivCorrelation(const BijectivCorrelation&); //not implemented by purpose
    BijectivCorrelation& operator=(const BijectivCorrelation&); //not implemented by purpose
  };

} // end namespace iro

#endif
