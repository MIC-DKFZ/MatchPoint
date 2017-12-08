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




#ifndef __IRO_ALGORITHM_EXECUTION_INFO_TPP
#define __IRO_ALGORITHM_EXECUTION_INFO_TPP

#include "mapAlgorithmExecutionInfo.h"
#include "mapOntologyExceptions.h"

namespace iro
{

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::RelevantEntityIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getRelevantEntitiesBegin()
    {
      return _relevantEntities.begin();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstRelevantEntityIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getRelevantEntitiesBegin() const
    {
      return _relevantEntities.begin();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::RelevantEntityRangeType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getRelevantEntities(const RelevantEntityLabelType& label)
    {
      RelevantEntityIterator lower = _relevantEntities.lower_bound();
      RelevantEntityIterator upper = _relevantEntities.upper_bound();

      return RelevantEntityRangeType(lower,upper);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstRelevantEntityRangeType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
    getRelevantEntities(const RelevantEntityLabelType& label) const
    {
      ConstRelevantEntityIterator lower = _relevantEntities.lower_bound();
      ConstRelevantEntityIterator upper = _relevantEntities.upper_bound();

      return ConstRelevantEntityRangeType(lower,upper);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::RelevantEntityIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
      getRelevantEntitiesEnd()
    {
      return _relevantEntities.end();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstRelevantEntityIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
      getRelevantEntitiesEnd() const
    {
      return _relevantEntities.end();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::RelevantEntityCountType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getRelevantEntitiesCount() const
    {
      return _relevantEntities.size();
    };

          template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::RelevantEntityIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
      addRelevantEntity(const RelevantEntityLabelType& label, RelevantEntityPointer newEntity)
    {
      if (!newEntity) throw ::iro::exceptions::InvalidArgument("Cannot add new relevant entity. Passed entity pointer is NULL.");

      return _relevantEntities.insert(std::make_pair(label,newEntity));
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::RelevantEntityIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       removeRelevantEntity(RelevantEntityIterator pos)
    {
      return _relevantEntities.erase(pos);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::RelevantEntityCountType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       removeRelevantEntities(const RelevantEntityLabelType& label)
    {
      return _relevantEntities.erase(label);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::AdaptedParameterIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getAdaptedParametersBegin()
    {
      return _parameters.begin();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstAdaptedParameterIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getAdaptedParametersBegin() const
    {
      return _parameters.begin();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::AdaptedParameterIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getAdaptedParametersEnd()
    {
      return _parameters.end();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstAdaptedParameterIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getAdaptedParametersEnd() const
    {
      return _parameters.end();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::AdaptedParameterIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
      getAdaptedParameter(const AdaptedParameterNameType& name)
    {
      return _parameters.find(name);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstAdaptedParameterIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
     getAdaptedParameter(const AdaptedParameterNameType& name) const
    {
      return _parameters.find(name);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::AdaptedParameterCountType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getAdaptedParametersCount() const
    {
      return _parameters.size();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::AdaptedParameterIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       addAdaptedParameter(const AdaptedParameterNameType& name, const AdaptedParameterValueType& value)
    {
      std::pair<AdaptedParameterMapType::iterator,bool> result = _parameters.insert(std::make_pair(name,value));

      if (!result.second)
      { //name was already present. replace
        result.first->second = value;
      }

      return result.first;
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::AdaptedParameterIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       removeAdaptedParameter(AdaptedParameterIterator pos)
    {
      return _parameters.erase(pos);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::QualityMeasureIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getQualityMeasuresBegin()
    {
      return _measures.begin();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstQualityMeasureIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getQualityMeasuresBegin() const
    {
      return _measures.begin();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::QualityMeasureIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getQualityMeasuresEnd()
    {
      return _measures.end();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstQualityMeasureIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getQualityMeasuresEnd() const
    {
      return _measures.end();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::QualityMeasureIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getQualityMeasure(const QualityMeasureNameType& name)
    {
      return _measures.find(name);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstQualityMeasureIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
     getQualityMeasure(const QualityMeasureNameType& name) const
    {
      return _measures.find(name);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::QualityMeasureCountType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getQualityMeasuresCount() const
    {
      return _measures.size();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::QualityMeasureIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       addQualityMeasure(const QualityMeasureNameType& name, const QualityMeasureValueType& value)
    {
      std::pair<QualityMeasureMapType::iterator,bool> result = _measures.insert(std::make_pair(name,value));

      if (!result.second)
      { //name was already present. replace
        result.first->second = value;
      }

      return result.first;
    };

      /*! removes the name/value at the passed position.
       * @param [in] pos Iterator indicating the postion of the element that should be removed.
       * @return Iterator that points to the position behind the removed element. If it was the last element it points to getQualityMeasuresEnd().*/
    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::QualityMeasureIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       removeQualityMeasure(QualityMeasureIterator pos)
    {
      return _measures.erase(pos);
    };

      /*! Returns the iterator to the begin of the tags map.*/
    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::TagIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getTagsBegin()
    {
      return _tags.begin();
    };

      /*! Returns the const iterator to the begin of the tags map.*/
    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstTagIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getTagsBegin() const
    {
      return _tags.begin();
    };


      /*! Returns the iterator to the end of the tags map.*/
    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::TagIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getTagsEnd()
    {
      return _tags.end();
    };

      /*! Returns the const iterator to the end of the tags map.*/
    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstTagIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getTagsEnd() const
    {
      return _tags.end();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::TagRangeType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
      getTags(const TagLabelType& label)
    {
      TagIterator lower = _tags.lower_bound(label);
      TagIterator upper = _tags.upper_bound(label);

      return TagRangeType(lower,upper);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::ConstTagRangeType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
     getTags(const TagLabelType& label) const
    {
      ConstTagIterator lower = _tags.lower_bound(label);
      ConstTagIterator upper = _tags.upper_bound(label);

      return ConstTagRangeType(lower,upper);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::TagCountType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getTagsCount() const
    {
      return _tags.size();
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::TagIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       addTag(const TagLabelType& label, const TagType& tag)
    {
      return _tags.insert(std::make_pair(label,tag));
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::TagIterator
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       removeTag(TagIterator pos)
    {
      return _tags.erase(pos);
    };
      /*! removes all elements with the passed label.
       * @param [in] label Label that indicates all elements that should be removed.
       * @return Number of elements that have been removed with this function call.*/
    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::TagCountType
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       removeTags(const TagLabelType& label)
    {
      return _tags.erase(label);
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    const typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::AlgorithmIDType&
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       getAlgorithmID() const
    {
      return _id;
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    void
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
    setAlgorithmID(const AlgorithmIDType& id)
    {
      _id = id;
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    const typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::DurationType&
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
      getDuration() const
    {
      return _duration;
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    void
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
    setDuration(const DurationType& duration)
    {
      _duration = duration;
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    typename AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::Pointer
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
       clone() const
    {
      Pointer spClone(new Self());
      spClone->_duration = _duration;
      spClone->_id = _id;
      spClone->_relevantEntities = _relevantEntities;
      spClone->_parameters = _parameters;
      spClone->_measures = _measures;
      spClone->_tags = _tags;

      return spClone;
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
			~AlgorithmExecutionInfo()
    {
    };

    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
      AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits>::
        AlgorithmExecutionInfo() : _duration(0)
      {
      };


} // end namespace iro

#endif
