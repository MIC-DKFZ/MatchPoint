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




#ifndef __MAP_SIMPLE_ONTOLOGY_CORE_H
#define __MAP_SIMPLE_ONTOLOGY_CORE_H

#include <set>

#include "mapValidityIndicator.h"
#include "mapProblemBasedEdgeValidator.h"
#include "mapDataRepresentation.h"
#include "mapIPathMetric.h"
#include "mapMappingError.h"

#include "mapGraphProperties.h"
#include "mapSimplePathSearch.h"

#include "boost/graph/adjacency_list.hpp"

#define BOOST_DATE_TIME_NO_LIB
#include "boost/interprocess/sync/interprocess_upgradable_mutex.hpp"
#include "boost/interprocess/sync/sharable_lock.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"


namespace iro
{
  namespace scenario
  {

    /*! @class SimpleOntologyCore
     * @brief Simple specific implementation of the ontology core
     * @ingroup Simple*/
    template <typename TOATraits>
    class SimpleOntologyCore
    {
    public:
      typedef SimpleOntologyCore Self;

      typedef ::boost::interprocess::interprocess_upgradable_mutex  MutexType;
      typedef ::boost::interprocess::sharable_lock<MutexType>       SharableLockType;
      typedef ::boost::interprocess::scoped_lock<MutexType>         LockType;

      using InfEntityType = typename TOATraits::InformationEntityTraitsType::Type;
      using InfEntityUIDType = typename TOATraits::InformationEntityTraitsType::UIDType;
      using InfSpaceType = typename TOATraits::InformationSpaceTraitsType::Type;
      using InfSpaceUIDType = typename TOATraits::InformationSpaceTraitsType::UIDType;
      using CorrelationType = typename TOATraits::SemanticCorrelationTraitsType::Type;
      using CorrelationUIDType = typename CorrelationType::UIDType;
      using ConstInfEntityPointer = typename TOATraits::InformationEntityTraitsType::ConstPointer;
      using ConstInfSpacePointer = typename TOATraits::InformationSpaceTraitsType::ConstPointer;
      using ConstCorrelationPointer = typename TOATraits::SemanticCorrelationTraitsType::ConstPointer;
      using InfEntityPointer = typename TOATraits::InformationEntityTraitsType::Pointer;
      using InfSpacePointer = typename TOATraits::InformationSpaceTraitsType::Pointer;
      using CorrelationPointer = typename TOATraits::SemanticCorrelationTraitsType::Pointer;
      using ProblemStatementType = typename TOATraits::ProblemStatementTraitsType::Type;
      using ProblemStatementUIDType = typename ProblemStatementType::UIDType;
      using ProblemStatementPointer = typename TOATraits::ProblemStatementTraitsType::Pointer;
      using ProblemModelType = typename TOATraits::ProblemModelTraitsType::Type;
      using ProblemModelUIDType = typename ProblemModelType::UIDType;
      using ProblemModelPointer = typename TOATraits::ProblemModelTraitsType::Pointer;
      using ConstProblemModelPointer = typename TOATraits::ProblemModelTraitsType::ConstPointer;
      using TransformationInfoType = typename TOATraits::TransformationInfoTraitsType::Type;
      using TransformationInfoPointer = typename TOATraits::TransformationInfoTraitsType::Pointer;
      using ConstTransformationInfoPointer = typename TOATraits::TransformationInfoTraitsType::ConstPointer;
      using TransformationInfoUIDType = typename TOATraits::TransformationInfoTraitsType::UIDType;
      typedef typename TOATraits::RegistrationInfoTraitsType::Type                     RegistrationInfoType;
      typedef typename TOATraits::RegistrationInfoTraitsType::Pointer                  RegistrationInfoPointer;
      typedef IProblemComplianceDefinition<ProblemStatementType>          ProblemComplianceInterface;
      typedef IPathMetric<typename TOATraits::RegistrationInfoTraitsType >             RegPathMetricInterface;
      typedef IPathMetric<typename TOATraits::TransformationInfoTraitsType >           TransPathMetricInterface;
      typedef typename TOATraits::TransformationPathTraitsType::Type                   TransformationPathType;
      typedef typename TOATraits::TransformationPathTraitsType::Pointer                TransformationPathPointer;
      typedef typename TOATraits::RegistrationPathTraitsType::Type                     RegistrationPathType;
      using RegistrationPathPointer = typename TOATraits::RegistrationPathTraitsType::Pointer;
      typedef typename TOATraits::RegPathOptionCollectionTraitsType::Type              RegPathOptColType;
      typedef typename TOATraits::RegPathOptionCollectionTraitsType::Pointer           RegPathOptColPointer;
      typedef typename TOATraits::RegPathOptionCollectionTraitsType::ConstPointer      ConstRegPathOptColPointer;
      typedef typename TOATraits::TransPathOptionCollectionTraitsType::Type            TransPathOptColType;
      typedef typename TOATraits::TransPathOptionCollectionTraitsType::Pointer         TransPathOptColPointer;

      //Basic entity maps
      typedef std::map<InfEntityUIDType, InfEntityPointer> EntityMapType;
      typedef std::map<InfEntityUIDType, ConstInfEntityPointer> ConstEntityMapType;
      typedef std::map<InfSpaceUIDType, InfSpacePointer> ISMapType;
      typedef std::map<CorrelationUIDType, CorrelationPointer> CorrelationMapType;
      typedef std::map<ProblemModelUIDType, ProblemModelPointer> ModelMapType;
      typedef std::map<ProblemStatementUIDType, ProblemStatementPointer> StatementMapType;
      typedef std::map<TransformationInfoUIDType, TransformationInfoPointer> TransformationMapType;

      //look up maps
      typedef std::multimap<ProblemStatementUIDType, ProblemModelUIDType> StatementModelMapType;
      typedef std::map<InfEntityUIDType, InfSpaceUIDType> EntityISMapType;
      typedef std::multimap<InfEntityUIDType, CorrelationUIDType> EntityCorrelationMapType;
      typedef ::boost::adjacency_list<::boost::vecS,::boost::vecS,::boost::directedS,core::ISGraphInfo<typename TOATraits::InformationSpaceTraitsType>, core::RegistrationISGraphInfo<typename TOATraits::TransformationInfoTraitsType> > RegistrationGraphType;

      //utility maps/collections
      typedef std::map<CorrelationUIDType, ConstCorrelationPointer> ConstCorrelationMapType;
      typedef std::map<ProblemModelUIDType, ConstProblemModelPointer> ConstModelMapType;
      typedef std::set<InfEntityUIDType> EntityUIDSetType;
      typedef std::map<typename RegistrationGraphType::edge_descriptor, double> WeightMapType;
      typedef std::map<typename RegistrationGraphType::vertex_descriptor, typename RegistrationGraphType::vertex_descriptor> PredecessorMapType;
      typedef std::map<typename RegistrationGraphType::vertex_descriptor, typename RegistrationGraphType::edge_descriptor> EdgeMapType;
      typedef std::vector<ConstInfEntityPointer> ConstInfEntityVectorType;
      typedef ::std::vector< ::std::vector< typename RegistrationGraphType::edge_descriptor> > SimpleSearchMapType;
      typedef std::vector<ConstInfSpacePointer> ConstInfSpaceEntityVectorType;

      using EdgeValidatorType = ProblemBasedEdgeValidator<RegistrationGraphType, IProblemComplianceDefinition<ProblemStatementType> >;

      MutexType _mutex;

      EntityMapType _entityMap;
      ISMapType _ISMap;
      CorrelationMapType _correlationMap;
      StatementMapType _statementMap;
      ModelMapType _modelMap;
      TransformationMapType _transformationMap;
      RegistrationGraphType _graph;

      EntityISMapType _entity2ISMap;
      EntityCorrelationMapType _entity2CorrelationMap;
      StatementModelMapType _stat2ModelMap;

      mutable OntologyRevisionTag _revision;

      /**changes the revision*/
      void notifyChange() const;

			/**! Get all correlations between source entities and target entities.
       @remark the passed variable corrs is not reseted only "updated". If you want a "clean" result clear the map before adding.*/
			void getCorrelations(ConstCorrelationMapType& corrs, const EntityUIDSetType& sourceEntities, const EntityUIDSetType& targetEntities) const;
			/**! Get all correlations between source entities and target entities.
       @remark the passed variable corrs is not reseted only "updated". If you want a "clean" result clear the map before adding.*/
			void getCorrelations(ConstCorrelationMapType& corrs, const InfEntityUIDType& sourceEntity, const InfEntityUIDType& targetEntity) const;
			/**! Get all correlations of passed entity.
       @remark the passed variable corrs is not reseted only "updated". If you want a "clean" result clear the map before adding.*/
			void getCorrelations(ConstCorrelationMapType& corrs, const InfEntityUIDType& entity) const;

			/**! Get all models that are associated with the passed statement.
       @remark the passed variable models is not reseted only "updated". If you want a "clean" result clear the map before adding.*/
      void getProblemModels(ConstModelMapType& models, const ProblemStatementUIDType& ps) const;

      /**! stores (new or updated) transformation infos to the core. handles the update of reference and of the graph*/
      void storeTransformationInfo(TransformationInfoPointer trans);
      /**! deletes transformation infos to the core. handles the update of reference and of the graph*/
      void deleteTransformationInfo(ConstTransformationInfoPointer trans);
      /**checks if the transformation info only relates to entities defined in the ontology.
      * if not it returns false. All referenced entities will be updated/exchange with the current
      * instances of the ontology.*/
      bool validateForCommit(TransformationInfoPointer trans);
      /** searches for the edge containing the transformation. throws an exception if not found*/
      typename RegistrationGraphType::edge_descriptor getAssociatedEdge(ConstTransformationInfoPointer trans);
      /** searches for an edge that has the right IS connection and problem statement association and
       returns it via edge. If no edge has been found it returns false.*/
      bool getFittingEdge(ConstTransformationInfoPointer trans, typename RegistrationGraphType::edge_descriptor& edge);
      /** adds an edge connecting the passed spaces*/
      typename RegistrationGraphType::edge_descriptor addEdge(ConstInfSpacePointer movingIS, ConstInfSpacePointer targetIS);
      /** inserts the transformation into the edge. If there is already an transformation it will be removed from the
       * edge and ontology.*/
      void updateEdge(typename RegistrationGraphType::edge_descriptor, TransformationInfoPointer trans);

      typename RegistrationGraphType::vertex_descriptor getVertex(ConstInfSpacePointer is) const;
      void addVertex(ConstInfSpacePointer is);
      void deleteVertex(ConstInfSpacePointer is);

      /**generates a weight map on registration info level for all edges regarding the passed requirements.*/
      WeightMapType generateWeightMap_reg(DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL);
      /**generates a weight map on transformation info level for all edges regarding the passed requirements.*/
      WeightMapType generateWeightMap_trans(DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance = NULL, const TransPathMetricInterface* pMetric = NULL);

      void generateMinimalPathPredecessors(ConstInfSpacePointer targetIS, WeightMapType& map, PredecessorMapType& predecessors, EdgeMapType& edges);

      RegistrationPathPointer generateRegPath(ConstInfSpacePointer movingIS, ConstInfSpacePointer targetIS, const WeightMapType& weights, const PredecessorMapType& predecessors, const EdgeMapType& edges);
      TransformationPathPointer generateTransPath(ConstInfSpacePointer movingIS, ConstInfSpacePointer targetIS, DataRepresentation::Type requiredDataSupport, const WeightMapType& weights, const PredecessorMapType& predecessors, const EdgeMapType& edges);

      /*generates path options out of the simple search results and sets the entity of the option if passed*/
      RegPathOptColPointer generateRegCollection(const SimpleSearchMapType& searchResult, ConstInfEntityPointer ie) const;
      /**generates path options out of the simple search results and sets the entity of the option if passed
       * if no entity is passed all types of paths will be generated, otherwise only the fitting paths.*/
      TransPathOptColPointer generateTransCollection(const SimpleSearchMapType& searchResult, ConstInfEntityPointer ie) const;

      /** Generates a vector with all information spaces that can be mapped into the target IS.*/
      ConstInfSpaceEntityVectorType generateMapableIS(ConstInfSpacePointer targetIS, const WeightMapType& weights, const PredecessorMapType& predecessors, const EdgeMapType& edges);

      /**deletes look ups of entities that aren't related to corr any more and add all entities that are related to corr*/
      void updateEntity2CorrelationMap(ConstCorrelationPointer corr);
      /**goes through all correlations and removes the passed entity if related.*/
			void removeEntityFromCorrelations(const InfEntityUIDType& entity);
      /**goes through all correlations and updates the entity specified by the UID if it is related to the correlation
      * @remark the updated entity must already be in _entityMap;*/
			void actualizeEntityInCorrelations(const InfEntityUIDType& entity);
      /**checks if the correlation only relates to entities defined in the ontology.
      * if not it returns false. All referenced entities will be updated/exchange with the current
      * instances of the ontology.*/
      bool validateForCommit(CorrelationPointer corr);

      /**deletes look ups of statements that aren't related to pModell any more and add all statements that are related to pModell*/
      void updateStatement2ModelMap(ConstProblemModelPointer pModell);
      /**goes through all models and removes the passed statement if associated.*/
			void removeStatementFromModels(const ProblemStatementUIDType& stat);
      /**goes through all models and updates the statement specified by the UID if it is related to the model
      * @remark the updated statement must already be in _statementMap;*/
			void actualizeStatementInModels(const ProblemStatementUIDType& stat);
      /**checks if the model only relates to statements defined in the ontology.
      * if not it returns false. All referenced statements will be updated/exchange with the current
      * instances of the ontology.*/
      bool validateForCommit(ProblemModelPointer model);

			//*! Get all entities correlations relate to. You can specify an entity UID set and exclude all entities that match to this set or only include entities that match with this set.
      static ConstEntityMapType getEntitiesByCorrelations(const ConstCorrelationMapType& correlations, const EntityUIDSetType& entities, bool excludeEntities = true);

      static void spliteEntitiesByData(const ConstInfEntityVectorType& movingEntities, ConstInfEntityVectorType&  continuousEntities, ConstInfEntityVectorType& discreteEntities);


      template <typename TMap, typename TList>  
      static void extracValuesFromMap( const  TMap & m, TList & v )
      { 
          for( typename TMap::const_iterator it = m.begin(); it != m.end(); ++it )
          { 
              v.push_back( it->second ); 
          } 
      } 

      template <typename TVector, typename TUIDVector>  
      static void extractUIDs( const  TVector & v, TUIDVector & uids )
      { 
        uids.clear();
          for( typename TVector::const_iterator it = v.begin(); it != v.end(); ++it )
          { 
              uids.insert( (*it)->getUID() ); 
          } 
      } 

      MappingError::Type checkOptionCollectionSupport( ConstRegPathOptColPointer col, DataRepresentationSupport::Type requiredDataSupport ) const;

      virtual ~SimpleOntologyCore();
      SimpleOntologyCore();

    protected:
      const static double fatalPenaltyCost;
      const static double baseCost;

    private:
      SimpleOntologyCore(const Self&); //not implemented by purpose
      Self& operator=(const Self&); //not implemented by purpose
    };

  } // end namespace scenario

} // end namespace iro

#include "mapSimpleOntologyCore.tpp"

#endif
