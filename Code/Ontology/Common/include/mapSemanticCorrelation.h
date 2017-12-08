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




#ifndef __MAP_SEMANTIC_CORRELATION_H
#define __MAP_SEMANTIC_CORRELATION_H

#include "mapISemanticCorrelationType.h"
#include "mapOntologyExceptions.h"
#include "mapSemanticCorrelationTraits.h"

namespace iro
{

		/*! @class SemanticCorrelation
    * @brief Template class for semantic correlations.
    *
    * Class is used to gather information about certain semantic correlations.
    * It grants access to the type of the correlation and to the list of entities that are correlated.
    * @remark The default type of a correlation is UnkownInjectivCorrelation
    * @ingroup Correlation
    */
    template <typename TInformationEntityTraits, typename TUIDPolicy>
    class SemanticCorrelation
		{
    public:
      typedef SemanticCorrelation<TInformationEntityTraits, TUIDPolicy> Self;
      typedef ::std::shared_ptr<Self> Pointer;
      typedef ::std::shared_ptr<const Self> ConstPointer;

      typedef typename TInformationEntityTraits::ConstPointer  ConstIEPointer;
      typedef typename TInformationEntityTraits::Type          IEType;
      typedef typename TInformationEntityTraits::UIDType       IEUIDType;
      typedef ISemanticCorrelationType::ConstPointer           ConstTypePointer;

      typedef typename TUIDPolicy::UIDType                             UIDType;
      
    protected:
      typedef std::list<ConstIEPointer> EntityListType;
    
    public:

      typedef typename EntityListType::iterator        EntityIterator;
      typedef typename EntityListType::const_iterator  ConstEntityIterator;
      typedef typename EntityListType::size_type       SizeType;
 
      EntityIterator getCorrelatedEntitiesBegin();
      ConstEntityIterator getCorrelatedEntitiesBegin() const;

      EntityIterator getCorrelatedEntitiesEnd();
      ConstEntityIterator getCorrelatedEntitiesEnd() const;

      /*! Searches for the related entity that has the passed UID.
      * @param [in] id The ID of the entity that is searched
      * @return iterator pointing to the found entity. If no entity
      * was found the iterator equals getCorrelatedEntitiesEnd().
      */
      EntityIterator findCorrelatedEntity(const IEUIDType& id);
      /*!@overload
       * const overload
       * \see findCorrelatedEntity(const IEUIDType& id)
       */
      ConstEntityIterator findCorrelatedEntity(const IEUIDType& id) const;

      /*! Returns the number of statements assigned to the model */
      SizeType getCorrelatedEntitiesCount() const;

      /*! Adds the passed entity to the collection.
      * @pre enity must point to a valid instance or an exception will be raised.
      * @exception InvalidArgument: precondition is violated*/
      void addCorrelatedEntity(ConstIEPointer entity);

      /*! Removes the related entity indecated by the passed iterator and returns the iterator the next entity.
      * If it is the last entity in the list the end iterator will be returned.*/
      EntityIterator removeCorrelatedEntity(EntityIterator pos);

      /*! removes all options from the collection.*/
      void resetCorrelatedEntities();

      /*! Returns a shared_ptr to the type instance of the correlation.*/
      ConstTypePointer getType() const;

      /*! Sets the type of the correlation.
      * @pre corrType must point to a valid instance or an exception will be raised.
      * @exception InvalidArgument: precondition is violated*/
      void setType(ConstTypePointer corrType);

      const UIDType& getUID() const;
      
      Pointer clone() const;

      virtual ~SemanticCorrelation();
			SemanticCorrelation();
    protected:
      //Collection of the entities
      EntityListType _entities;

      ConstTypePointer _spType;

      UIDType _uid;

    private:
			SemanticCorrelation(const Self&); //not implemented by purpose
			Self& operator=(const Self&); //not implemented by purpose
		};
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapSemanticCorrelation.tpp"
#endif

#endif
