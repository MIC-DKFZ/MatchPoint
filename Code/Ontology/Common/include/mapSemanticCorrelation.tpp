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




#ifndef __MAP_SEMANTIC_CORRELATION_TPP
#define __MAP_SEMANTIC_CORRELATION_TPP

#include "mapUnkownInjectivCorrelation.h"
#include "mapSemanticCorrelation.h"

namespace iro
{

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::EntityIterator
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    getCorrelatedEntitiesBegin()
  {
    return _entities.begin();
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::ConstEntityIterator
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    getCorrelatedEntitiesBegin() const
  {
    return _entities.begin();
  };
  
  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::EntityIterator
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    getCorrelatedEntitiesEnd()
  {
    return _entities.end();
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::ConstEntityIterator
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    getCorrelatedEntitiesEnd() const
  {
    return _entities.end();
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::SizeType
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    getCorrelatedEntitiesCount() const
  {
    return _entities.size();
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::EntityIterator
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
     findCorrelatedEntity(const IEUIDType& id)
  {
    EntityIterator result = _entities.begin();

    while (result != _entities.end())
    {
      if (TInformationEntityTraits::identifyEntity(*((*result).get()),id))
      { //it is the search entity
        break;
      }
      ++result;
    }
    return result;
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::ConstEntityIterator
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
     findCorrelatedEntity(const IEUIDType& id) const
  {
    ConstEntityIterator result = _entities.begin();

    while (result != _entities.end())
    {
      if (TInformationEntityTraits::identifyEntity(*((*result).get()),id))
      { //it is the search entity
        break;
      }
      ++result;
    }
    return result;
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  void
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    addCorrelatedEntity(ConstIEPointer entity)
  {
    if (!entity) throw exceptions::InvalidArgument("Cannot add entity. Entity pointer is null");

    _entities.push_back(entity);
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::EntityIterator
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    removeCorrelatedEntity(EntityIterator pos)
  { 
    EntityIterator result = _entities.erase(pos);

    return result;
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  void
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    resetCorrelatedEntities()
  { 
    _entities.clear();
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::ConstTypePointer
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    getType() const
  {
    return _spType;
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  void
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    setType(ConstTypePointer corrType)
  {
    if (!corrType) throw exceptions::InvalidArgument("Cannot add NULL pointer as type.");

    _spType = corrType;
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  const typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::UIDType&
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
      getUID() const
    {
      return _uid;
    };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  typename SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::Pointer
    SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
      clone() const
    {
      Pointer spClone(new Self());

      spClone->_entities = _entities;
      spClone->_spType = _spType;
      spClone->_uid = _uid;

      return spClone;
    };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    ~SemanticCorrelation()
  {
  };

  template <typename TInformationEntityTraits, typename TUIDPolicy>
  SemanticCorrelation<TInformationEntityTraits, TUIDPolicy>::
    SemanticCorrelation()
  {
    _uid = TUIDPolicy::generateUID();
    _spType = ConstTypePointer(new UnkownInjectivCorrelation);
  };

} // end namespace iro

#endif
