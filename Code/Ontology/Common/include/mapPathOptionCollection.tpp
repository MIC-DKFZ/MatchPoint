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




#ifndef __MAP_PATH_OPTION_COLLECTION_TPP
#define __MAP_PATH_OPTION_COLLECTION_TPP

#include "mapTransformationPathBase.h"

namespace iro
{

  template <typename TPathOption>
  typename PathOptionCollection<TPathOption>::ConstIEPointer
    PathOptionCollection<TPathOption>::
    getMovingEntity() const
  {
    return _movingEntity;
  };

  template <typename TPathOption>
  void
    PathOptionCollection<TPathOption>::
    setMovingEntity(ConstIEPointer spMovingEntity)
  {
    if (_options.empty())
    { 
      _movingEntity = spMovingEntity;
    }
    else
    {
      exceptions::InvalidArgument("Cannot change moving entity of option collection. Collection contains options. Reset the collection before setting the moving entity.");
    }
  };

  template <typename TPathOption>
  typename PathOptionCollection<TPathOption>::OptionIterator
    PathOptionCollection<TPathOption>::
    getBegin()
  {
    return _options.begin();
  };

  template <typename TPathOption>
  typename PathOptionCollection<TPathOption>::ConstOptionIterator
    PathOptionCollection<TPathOption>::
    getBegin() const
  {
    return _options.begin();
  };
  
  template <typename TPathOption>
  typename PathOptionCollection<TPathOption>::OptionIterator
    PathOptionCollection<TPathOption>::
    getEnd()
  {
    return _options.end();
  };

  template <typename TPathOption>
  typename PathOptionCollection<TPathOption>::ConstOptionIterator
    PathOptionCollection<TPathOption>::
    getEnd() const
  {
    return _options.end();
  };

  template <typename TPathOption>
  typename PathOptionCollection<TPathOption>::SizeType
    PathOptionCollection<TPathOption>::
    getOptionCount() const
  {
    return _options.size();
  };

  template <typename TPathOption>
  void
    PathOptionCollection<TPathOption>::
    addOption(ConstOptionPointer option)
  {
    if (!option) { throw exceptions::InvalidArgument("Cannot add path option. Option pointer is null");
}

    if (this->getMovingEntity() && this->getMovingEntity()!=option->getMovingEntity())
    { 
      throw exceptions::InvalidDataRepresentation("Collection has a different moving entity than the option that should be added.");
    }

    if (!(this->getMovingEntity()) && _options.empty())
    { //define the moving entity
      _movingEntity = option->getMovingEntity();
    }

    _options.push_back(option);
    _cacheIsUpToDate = false;
  };

  template <typename TPathOption>
  typename PathOptionCollection<TPathOption>::OptionIterator
    PathOptionCollection<TPathOption>::
    removeOption(OptionIterator pos)
  { 
    typename PathOptionCollection<TPathOption>::OptionIterator result = _options.erase(pos);
    _cacheIsUpToDate = false;

    return result;
  };

  template <typename TPathOption>
  void
    PathOptionCollection<TPathOption>::
    resetOptions()
  { 
    _options.clear();
    _guranteeCache.clear();
    _cacheIsUpToDate = true;
  };

  template <typename TPathOption>
  typename PathOptionCollection<TPathOption>::MappingErrorType
    PathOptionCollection<TPathOption>::
    checkForFailureReason() const
  {
    if (_options.empty()) { throw exceptions::InvalidArgument("No option is set. Cannot ascertain failure risks.");
}

    if (!_cacheIsUpToDate)
    {
      MappingErrorType result = MappingError::NoPath;

      OptionCollectionType newCache;

      for ( auto pos = _options.begin(); pos!=_options.end(); ++pos)
      {
        MappingErrorType currentValue = (*pos)->checkForFailureReason();
        if (currentValue<result)
        { //the errors are ordered upwards by fatality, so smaller results are less fatal
          //and determin the new result
          result = currentValue;
        }
        if (currentValue == MappingError::NoFailure)
        {
          newCache.push_back(*pos);
        }
      }

      _guranteeCache.swap(newCache);
      _cacheIsUpToDate = true;
      _currentFailureReason = result;

    }

    return _currentFailureReason;
  };

  template <typename TPathOption>
  typename PathOptionCollection<TPathOption>::FullMappingOptionCollectionType
    PathOptionCollection<TPathOption>::
    getFullMappingGuaranteeOptions() const
  {
    if (!_cacheIsUpToDate)
    {
      checkForFailureReason();
    }

    return _guranteeCache;
  };

  template <typename TPathOption>
  PathOptionCollection<TPathOption>::
    ~PathOptionCollection()
  = default;

  template <typename TPathOption>
  PathOptionCollection<TPathOption>::
    PathOptionCollection()
  {
    _cacheIsUpToDate = true;
  };

} // end namespace iro

#endif
