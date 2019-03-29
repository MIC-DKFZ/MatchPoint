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




#ifndef __MAP_ALGORITHM_EXECUTION_INFO_H
#define __MAP_ALGORITHM_EXECUTION_INFO_H

#include "mapOntologyString.h"

#include <memory>
#include <chrono>

#include <list>
#include <map>

namespace iro
{

		/** This class is used to collect and store an relevant information about
     * an algorithm execution. The gathered information can be compiled by
     * different sources (e.g. User, clients using the ontology).
     * @tparam TInformationSpaceTraits The traits of the information space, depending on the application scenario.
     * @tparam TInformationEntityTraits The traits of the information entity, depending on the application scenario.*/
    template <typename TInformationSpaceTraits, typename TInformationEntityTraits>
    class AlgorithmExecutionInfo
		{
    public:
      typedef AlgorithmExecutionInfo<TInformationSpaceTraits,TInformationEntityTraits> Self;
      using Pointer = ::std::shared_ptr<Self>;
      using ConstPointer = ::std::shared_ptr<const Self>;


      using RelevantEntityLabelType = String;
      using RelevantEntityPointer = typename TInformationEntityTraits::ConstPointer;

      using AdaptedParameterNameType = String;
      using AdaptedParameterValueType = String;

      using QualityMeasureNameType = String;
      using QualityMeasureValueType = String;

      using TagLabelType = String;
      using TagType = String;

      using DurationType = std::chrono::milliseconds;
      using AlgorithmIDType = String;

    protected:
      typedef typename std::multimap<RelevantEntityLabelType,RelevantEntityPointer> RelevantEntityMapType;
      typedef typename std::map<AdaptedParameterNameType,AdaptedParameterValueType> AdaptedParameterMapType;
      typedef typename std::map<QualityMeasureNameType,QualityMeasureValueType> QualityMeasureMapType;
      typedef typename std::multimap<TagLabelType,TagType> TagMapType;

    public:
      using RelevantEntityIterator = typename RelevantEntityMapType::iterator;
      using ConstRelevantEntityIterator = typename RelevantEntityMapType::const_iterator;
      using RelevantEntityCountType = typename RelevantEntityMapType::size_type;
      typedef std::pair<RelevantEntityIterator,RelevantEntityIterator> RelevantEntityRangeType;
      typedef std::pair<ConstRelevantEntityIterator,ConstRelevantEntityIterator> ConstRelevantEntityRangeType;

      using AdaptedParameterIterator = typename AdaptedParameterMapType::iterator;
      using ConstAdaptedParameterIterator = typename AdaptedParameterMapType::const_iterator;
      using AdaptedParameterCountType = typename AdaptedParameterMapType::size_type;

      using QualityMeasureIterator = typename QualityMeasureMapType::iterator;
      using ConstQualityMeasureIterator = typename QualityMeasureMapType::const_iterator;
      using QualityMeasureCountType = typename QualityMeasureMapType::size_type;

      using TagIterator = typename TagMapType::iterator;
      using ConstTagIterator = typename TagMapType::const_iterator;
      using TagCountType = typename TagMapType::size_type;
      typedef std::pair<TagIterator,TagIterator>  TagRangeType;
      typedef std::pair<ConstTagIterator,ConstTagIterator> ConstTagRangeType;

      //////////////////////////////////////////////////////
      // Relevant entities

      /*! Returns the iterator to the begin of the relevant entity map.*/
      RelevantEntityIterator getRelevantEntitiesBegin();
      /*! Returns the const iterator to the begin of th relevant entity map.*/
      ConstRelevantEntityIterator getRelevantEntitiesBegin() const;

      /*! Returns a iterator pair the first iterator points at the first entity
      * that is associated with the passed label, the second iterator points to the first
      * entity whose label is greater then the searched label. If the label does not exist
      * both iterators point to getRelevantEntitiesEnd(). The second iterator may also point
      * to getRelevantEntitiesEnd() if it is the last label in the map.*/
      RelevantEntityRangeType getRelevantEntities(const RelevantEntityLabelType& label);
      ConstRelevantEntityRangeType getRelevantEntities(const RelevantEntityLabelType& label) const;

      /*! Returns the iterator to the end of the relevant entity map.*/
      RelevantEntityIterator getRelevantEntitiesEnd();
      /*! Returns the const iterator to the end of the relevant entity map.*/
      ConstRelevantEntityIterator getRelevantEntitiesEnd() const;

      /*! Returns the size of the relevant entity map (number of elements).*/
      RelevantEntityCountType getRelevantEntitiesCount() const;

      /*! adds the passed newEntity under the label and returns its position.
       * @param [in] label Label of the entity.
       * @param [in] newEntity The new entity that should be added.
       * @pre newEntity must point to a valid instance.
       * @exception ::iro::exceptions::InvalidArgument: newEntity is no valid instance.
       * @return Iterator that points to the position of the inserted element.*/
      RelevantEntityIterator addRelevantEntity(const RelevantEntityLabelType& label, RelevantEntityPointer newEntity);
      /*! removes the element at the passed position.
       * @param [in] pos Iterator indicating the postion of the element that should be removed.
       * @return Iterator that points to the position behind the removed element. If it was the last element it points to getRelevantEntitiesEnd().*/
      RelevantEntityIterator removeRelevantEntity(RelevantEntityIterator pos);
      /*! removes all elements with the passed label.
       * @param [in] label Label that indicates all elements that should be removed.
       * @return Number of elements that have been removed with this function call.*/
      RelevantEntityCountType removeRelevantEntities(const RelevantEntityLabelType& label);


      //////////////////////////////////////////////////////
      // adapted parameters

      /*! Returns the iterator to the begin of the adapted parameter map.*/
      AdaptedParameterIterator getAdaptedParametersBegin();
      /*! Returns the const iterator to the begin of the adapted parameter map.*/
      ConstAdaptedParameterIterator getAdaptedParametersBegin() const;

      /*! Returns the iterator to the end of the adapted parameter map.*/
      AdaptedParameterIterator getAdaptedParametersEnd();
      /*! Returns the const iterator to the end of the adapted parameter map.*/
      ConstAdaptedParameterIterator getAdaptedParametersEnd() const;

      AdaptedParameterIterator getAdaptedParameter(const AdaptedParameterNameType& name);
      ConstAdaptedParameterIterator getAdaptedParameter(const AdaptedParameterNameType& name) const;

      /*! Returns the size of the adapted parameter map (number of elements).*/
      AdaptedParameterCountType getAdaptedParametersCount() const;

      /*! adds the passed name/value and returns its position.
       * @param [in] name Name of the parameter that should be added.
       * @param [in] value Value of the parameter that should be added.
       * @return Iterator that points to the position of the inserted value.*/
      AdaptedParameterIterator addAdaptedParameter(const AdaptedParameterNameType& name, const AdaptedParameterValueType& value);
      /*! removes the name/value at the passed position.
       * @param [in] pos Iterator indicating the postion of the element that should be removed.
       * @return Iterator that points to the position behind the removed element. If it was the last element it points to getAdaptedParametersEnd().*/
      AdaptedParameterIterator removeAdaptedParameter(AdaptedParameterIterator pos);

      //////////////////////////////////////////////////////
      // quality measures

      /*! Returns the iterator to the begin of the quality measures map.*/
      QualityMeasureIterator getQualityMeasuresBegin();
      /*! Returns the const iterator to the begin of the quality measures map.*/
      ConstQualityMeasureIterator getQualityMeasuresBegin() const;

      /*! Returns the iterator to the end of the quality measures map.*/
      QualityMeasureIterator getQualityMeasuresEnd();
      /*! Returns the const iterator to the end of the quality measures map.*/
      ConstQualityMeasureIterator getQualityMeasuresEnd() const;

      QualityMeasureIterator getQualityMeasure(const QualityMeasureNameType& name);
      ConstQualityMeasureIterator getQualityMeasure(const QualityMeasureNameType& name) const;

      /*! Returns the size of the quality measures map (number of elements).*/
      QualityMeasureCountType getQualityMeasuresCount() const;

      /*! adds the passed name/value and returns its position.
       * @param [in] name Name of the parameter that should be added.
       * @param [in] value Value of the parameter that should be added.
       * @return Iterator that points to the position of the inserted value.*/
      QualityMeasureIterator addQualityMeasure(const QualityMeasureNameType& name, const QualityMeasureValueType& value);
      /*! removes the name/value at the passed position.
       * @param [in] pos Iterator indicating the postion of the element that should be removed.
       * @return Iterator that points to the position behind the removed element. If it was the last element it points to getQualityMeasuresEnd().*/
      QualityMeasureIterator removeQualityMeasure(QualityMeasureIterator pos);

      //////////////////////////////////////////////////////
      // tags

      /*! Returns the iterator to the begin of the tags map.*/
      TagIterator getTagsBegin();
      /*! Returns the const iterator to the begin of the tags map.*/
      ConstTagIterator getTagsBegin() const;

      /*! Returns the iterator to the end of the tags map.*/
      TagIterator getTagsEnd();
      /*! Returns the const iterator to the end of the tags map.*/
      ConstTagIterator getTagsEnd() const;

            /*! Returns a iterator pair the first iterator points at the first entity
      * that is associated with the passed label, the second iterator points to the first
      * entity whose label is greater then the searched label. If the label does not exist
      * both iterators point to getRelevantEntitiesEnd(). The second iterator may also point
      * to getRelevantEntitiesEnd() if it is the last label in the map.*/
      TagRangeType getTags(const TagLabelType& label);
      ConstTagRangeType getTags(const TagLabelType& label) const;

      /*! Returns the size of the tags map (number of elements).*/
      TagCountType getTagsCount() const;

      /*! adds the passed newEntity under the label and returns its position.
       * @param [in] label Label of the entity.
       * @param [in] tag The new tag that should be added.
       * @return Iterator that points to the position of the inserted element.*/
      TagIterator addTag(const TagLabelType& label, const TagType& tag);
      /*! removes the element at the passed position.
       * @param [in] pos Iterator indicating the postion of the element that should be removed.
       * @return Iterator that points to the position behind the removed element. If it was the last element it points to getRelevantEntitiesEnd().*/
      TagIterator removeTag(TagIterator pos);
      /*! removes all elements with the passed label.
       * @param [in] label Label that indicates all elements that should be removed.
       * @return Number of elements that have been removed with this function call.*/
      TagCountType removeTags(const TagLabelType& label);

      //////////////////////////////////////////////////////
      // others

      const AlgorithmIDType& getAlgorithmID() const;
      void setAlgorithmID(const AlgorithmIDType& id);

      /** Returns the duration of the execution (in milliseconds).*/
      const DurationType& getDuration() const;
      /** Sets the duration of the execution (in milliseconds).*/
      void setDuration(const DurationType& duration);

      /* Clones the content of the execution info and returns it as
      * non const pointer. It can be used to alter the execution info and
      * update the knowledge base of the ontology.
      */
      Pointer clone() const;

			virtual ~AlgorithmExecutionInfo();
			AlgorithmExecutionInfo();

    protected:

      DurationType _duration;
      AlgorithmIDType _id;

      RelevantEntityMapType _relevantEntities;
      AdaptedParameterMapType _parameters;
      QualityMeasureMapType _measures;
      TagMapType _tags;

    private:
			AlgorithmExecutionInfo(const Self&); //not implemented by purpose
			Self& operator=(const Self&); //not implemented by purpose
		};
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapAlgorithmExecutionInfo.tpp"
#endif

#endif
