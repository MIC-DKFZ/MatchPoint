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




#ifndef __MAP_IS_CACHE_KEY_TPP
#define __MAP_IS_CACHE_KEY_TPP

#include "mapISCacheKey.h"

namespace iro
{
  namespace core
  {

    template <class TISTraits>
      bool
        ISCacheKey<TISTraits>::
        operator == (const Self& source) const
      {
        return (this->_uid == source._uid) && (this->_dataRep == source._dataRep);
      };

    template <class TISTraits>
      bool
        ISCacheKey<TISTraits>::
        operator != (const Self& source) const
      {
        return !(*this == source);
      };

    template <class TISTraits>
      bool
        ISCacheKey<TISTraits>::
        operator < (const Self& source) const
      {
        if (_uid<source._uid) return true;
        if (this->_dataRep < source._dataRep) return true;
        return false;
      };

    template <class TISTraits>
      typename ISCacheKey<TISTraits>::Self&
        ISCacheKey<TISTraits>::
        operator = (const Self& source)
      {
        if (this != &source)
        {
          this->_uid = source._uid;
          this->_dataRep = source._dataRep;
        }

        return *this;
      };

     template <class TISTraits>
     ISCacheKey<TISTraits>::
           ISCacheKey(const UIDType& uid, DataRepresentationSupport::Type dataRep)
      {
        _uid = uid;
        _dataRep = dataRep;
      };


  } // end namespace core
} // end namespace iro

#endif
