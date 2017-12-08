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




#ifndef __IRO_IS_CACHE_KEY_H
#define __IRO_IS_CACHE_KEY_H

#include "mapDataRepresentation.h"

namespace iro
{
  namespace core
  {

    /**
    Helper class used by ontologies as key in maps, where InformationSpaces should not just be distinguished
    by ther UID but also by the data representation type they are currently requested for.
    @tparam TISTraits traits of the used information space type.
    */
    template <typename TISTraits>
    struct ISCacheKey
    {
      typedef typename TISTraits::UIDType UIDType;
      typedef ISCacheKey<TISTraits> Self;

      UIDType _uid;
      DataRepresentationSupport::Type _dataRep;

      bool operator == (const Self& source) const;
      bool operator != (const Self& source) const;
      bool operator < (const Self& source) const;
      Self& operator = (const Self& source);
      
      ISCacheKey(const UIDType& uid, DataRepresentationSupport::Type dataRep);
    };

  } // end namespace core

} // end namespace iro

#ifndef IRO_MANUAL_TPP
#include "mapISCacheKey.tpp"
#endif

#endif
