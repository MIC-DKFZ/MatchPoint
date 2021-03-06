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




#ifndef __MAP_PATH_OPTION_COLLECTION_H
#define __MAP_PATH_OPTION_COLLECTION_H

#include "mapPathOption.h"
#include "mapOntologyExceptions.h"

namespace iro
{

		/*! @class PathOptionCollection
    * @brief Template class that is used for path options.
    *
    * This template class is used to compile several path options
    * for the same entity. It is used by some inference queries if
    * the result must not be unambiguous.
    */
    template <typename TPathOption>
    class PathOptionCollection
		{
    public:
      using Self = PathOptionCollection<TPathOption>;
      using Pointer = ::std::shared_ptr<Self>;
      using ConstPointer = ::std::shared_ptr<const Self>;

      using PathTraitsType = typename TPathOption::PathTraitsType;

      using ConstIEPointer = typename PathTraitsType::InformationEntityTraitsType::ConstPointer;
      using ConstISPointer = typename PathTraitsType::InformationSpaceTraitsType::ConstPointer;
      using ConstPathPointer = typename PathTraitsType::ConstPointer;
      using MappingErrorType = MappingError::Type;

      using OptionType = TPathOption;
      using ConstOptionPointer = typename TPathOption::ConstPointer;

    protected:
      using OptionCollectionType = std::list<ConstOptionPointer>;
    
    public:

      using OptionIterator = typename OptionCollectionType::iterator;
      using ConstOptionIterator = typename OptionCollectionType::const_iterator;
      using SizeType = typename OptionCollectionType::size_type;
 
      using FullMappingOptionCollectionType = std::list<ConstOptionPointer>;

      /*! Returns the entity this path option collection was compiled for.
       * It  may return NULL if no option was added and moving entity was
       * not set*/
      ConstIEPointer getMovingEntity() const;

      /*! Sets the moving entity of the collection.
       * @pre the collection may not contain options with a moving entity != NULL
       * before the   * moving entity is changed. 
      .*/
      void setMovingEntity(ConstIEPointer spMovingEntity);

      OptionIterator getBegin();
      ConstOptionIterator getBegin() const;

      OptionIterator getEnd();
      ConstOptionIterator getEnd() const;

      /*! Returns the number of statements assigned to the model */
      SizeType getOptionCount() const;

      /*! Adds the passed option to the collection. If not defined yet, the moving entity
      * will be defined by the added option.
      * @pre option must point to a valid instance or an exception will be raised.
      * @pre If the collection has a defined moving entity (by user or other options), "option" must have the same enity.
      * @exception InvalidArgument: precondition is violated*/
      void addOption(ConstOptionPointer option);

      /*! Removes the option indecated by the passed iterator and returns the iterator the next option.
      * If it is the last option in the list the end iterator will be returned.*/
      OptionIterator removeOption(OptionIterator pos);

      /*! removes all options from the collection.*/
      void resetOptions();

      /*! Checks the options for the failure reason that is less fatal or for
      * at least on success.
      * @pre At least one path option must be defined.
      * @exception InvalidArgument: precondition is violated*/
      MappingErrorType checkForFailureReason() const;

      /*! returns a list with al options in this collection
       * that guarantee full mapping of the moving entity..*/
      FullMappingOptionCollectionType getFullMappingGuaranteeOptions() const;
      
      virtual ~PathOptionCollection();
			PathOptionCollection();
    protected:
      //*Collection of the options
      OptionCollectionType _options;

      //* Entity can be set directly or is set automatically when an option is added.
      ConstIEPointer _movingEntity;

      mutable MappingErrorType _currentFailureReason;
      //*cache for all options that guarantee mapping (no failure reason)
      mutable FullMappingOptionCollectionType _guranteeCache;
      //*indicates if the cache is still valid.
      mutable bool _cacheIsUpToDate;

    private:
			PathOptionCollection(const Self&); //not implemented by purpose
			Self& operator=(const Self&); //not implemented by purpose
		};
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapPathOptionCollection.tpp"
#endif

#endif
