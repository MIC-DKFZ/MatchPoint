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




#include "mapSimpleOntologyCore.h"

#include <boost/graph/dijkstra_shortest_paths.hpp>

namespace iro
{
  namespace scenario
  {

    template <typename TOATraits>
    const double SimpleOntologyCore<TOATraits>::fatalPenaltyCost = 1e9;
    template <typename TOATraits>
    const double SimpleOntologyCore<TOATraits>::baseCost = 0.0;

    template <typename TOATraits>
    SimpleOntologyCore<TOATraits>::
      ~SimpleOntologyCore()
    = default;

    template <typename TOATraits>
    SimpleOntologyCore<TOATraits>::
      SimpleOntologyCore()
    {
      _revision = 0;
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      notifyChange() const
    {
      ++_revision;
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      getCorrelations(ConstCorrelationMapType& corrs, const EntityUIDSetType& sourceEntities, const EntityUIDSetType& targetEntities) const
    {
      for (auto sourcePos = sourceEntities.begin(); sourcePos!= sourceEntities.end(); ++sourcePos)
      {
        for (auto targetPos = targetEntities.begin(); targetPos!= targetEntities.end(); ++targetPos)
        {
          getCorrelations(corrs, *sourcePos,*targetPos);
        }
      }
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      getCorrelations(ConstCorrelationMapType& corrs, const InfEntityUIDType& sourceEntity, const InfEntityUIDType& targetEntity) const
    {

      typedef std::pair<typename EntityCorrelationMapType::const_iterator,typename EntityCorrelationMapType::const_iterator> PairType;

      PairType sourceFindings = _entity2CorrelationMap.equal_range(sourceEntity);
      PairType targetFindings = _entity2CorrelationMap.equal_range(targetEntity);

      //got through all source entity correlations
      for (auto sourcePos = sourceFindings.first; sourcePos!= sourceFindings.second; ++sourcePos)
      {

        for (auto targetPos = targetFindings.first; targetPos!= targetFindings.second; ++targetPos)
        {
          if (sourcePos->second == targetPos->second)
          { //source and target are related to the same correlation
            //get Correlation
            auto posCorr = _correlationMap.find(sourcePos->second);

            if (posCorr !=  _correlationMap.end())
            {
              corrs[posCorr->second->getUID()] = posCorr->second;
              break;
            }
          }
        }
      }
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      getCorrelations(ConstCorrelationMapType& corrs, const InfEntityUIDType& entity) const
    {
      typedef std::pair<typename EntityCorrelationMapType::const_iterator,typename EntityCorrelationMapType::const_iterator> PairType;

      PairType sourceFindings = _entity2CorrelationMap.equal_range(entity);

      //got through all source entity correlations
      for (auto sourcePos = sourceFindings.first; sourcePos!= sourceFindings.second; ++sourcePos)
      {
        auto posCorr = _correlationMap.find(sourcePos->second);

        if (posCorr !=  _correlationMap.end())
        {
          corrs[posCorr->second->getUID()] = posCorr->second;
        }
      }
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      storeTransformationInfo(TransformationInfoPointer trans)
    {
      auto trPos = _transformationMap.find(trans->getUID());

      if (trPos!=_transformationMap.end())
      { //existing transformation -> check if edges must be refined or even deleted
        bool changedIS = (trPos->second->getTargetIS()->getUID() != trans->getTargetIS()->getUID()) || (trPos->second->getMovingIS()->getUID() != trans->getMovingIS()->getUID());
        bool changedPS = !(trPos->second->hasSameProblemStatement(trans.get()));

        if (changedIS || changedPS)
        {//check if existant edge would be empty
          bool willBeEmpty = false;
          typename RegistrationGraphType::edge_descriptor oldEdge = getAssociatedEdge(trPos->second);
          if (trans->getSupportedDataRepresentation()==DataRepresentation::Continuous)
          {
            willBeEmpty = !(_graph[oldEdge].inverse);
          }
          else
          {
            willBeEmpty = !(_graph[oldEdge].direct);
          }

          if (willBeEmpty)
          { // delete the old edge
            ::boost::remove_edge(oldEdge,_graph);
          }
        }
      }

      typename RegistrationGraphType::edge_descriptor newEdge;

      if (!getFittingEdge(trans,newEdge))
      { //need new edge
        newEdge = addEdge(trans->getMovingIS(),trans->getTargetIS()); 
      };

      updateEdge(newEdge,trans);
      _transformationMap[trans->getUID()] = trans;

      notifyChange();
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      deleteTransformationInfo(ConstTransformationInfoPointer trans)
    {
      typename RegistrationGraphType::edge_descriptor oldEdge = getAssociatedEdge(trans);
      ::boost::remove_edge(oldEdge,_graph);
      _transformationMap.erase(trans->getUID());
      notifyChange();
    };

    template <typename TOATraits>
    bool
      SimpleOntologyCore<TOATraits>::
      validateForCommit(TransformationInfoPointer trans)
    {
      bool result = true;

      if (trans->getMovingIS())
      {
        typename ISMapType::const_iterator isPos = _ISMap.find(trans->getMovingIS()->getUID());
        if (isPos==_ISMap.end())
        {
          result = false;
        }
        else
        {
          trans->setMovingIS(isPos->second);
        }
      }
      else
      {
        result = false;
      }

      if (trans->getTargetIS())
      {
        typename ISMapType::const_iterator isPos = _ISMap.find(trans->getTargetIS()->getUID());
        if (isPos==_ISMap.end())
        {
          result = false;
        }
        else
        {
          trans->setTargetIS(isPos->second);
        }
      }
      else
      {
        result = false;
      }

      if (trans->getAssociatedProblemStatement())
      {
        typename StatementMapType::const_iterator statPos = _statementMap.find(trans->getAssociatedProblemStatement()->getUID());
        if (statPos==_statementMap.end())
        {
          result = false;
        }
        else
        {
          trans->setAssociatedProblemStatement(statPos->second);
        }
      }

      return result;
    };

    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::RegistrationGraphType::edge_descriptor
      SimpleOntologyCore<TOATraits>::
      getAssociatedEdge(ConstTransformationInfoPointer trans)
    {
      typename RegistrationGraphType::edge_descriptor result;
      std::pair<typename RegistrationGraphType::edge_iterator, typename RegistrationGraphType::edge_iterator> range = boost::edges(_graph);

      for (typename RegistrationGraphType::edge_iterator pos = range.first; pos != range.second; ++pos)
      {
        if (trans->getSupportedDataRepresentation()==DataRepresentation::Continuous)
        {
          if(_graph[*pos].direct && _graph[*pos].direct->getUID() == trans->getUID())
          {
            return *pos;
          }
        }
        else
        {
          if (_graph[*pos].inverse && _graph[*pos].inverse->getUID() == trans->getUID())
          {
            return *pos;
          }
        }
      }

      throw exceptions::InvalidArgument("Error, cannot find transformation in registration graph. Should be there. Check graph initialization.");
    };

    template <typename TOATraits>
    bool
      SimpleOntologyCore<TOATraits>::
      getFittingEdge(ConstTransformationInfoPointer trans, typename RegistrationGraphType::edge_descriptor& edge)
    {
      bool result = false;
      std::pair<typename RegistrationGraphType::edge_iterator, typename RegistrationGraphType::edge_iterator> range = boost::edges(_graph);

      for (typename RegistrationGraphType::edge_iterator pos = range.first; pos != range.second; ++pos)
      {
        //check IS
        //target vertex == moving IS : for explanation see addEdge();
        typename RegistrationGraphType::vertex_descriptor movingV = ::boost::target(*pos,_graph);
        if (_graph[movingV].infSpace->getUID() != trans->getMovingIS()->getUID())
        {
          continue;
        }
        //source vertex == moving IS : for explanation see addEdge();
        typename RegistrationGraphType::vertex_descriptor targetV = ::boost::source(*pos,_graph);
        if (_graph[targetV].infSpace->getUID() != trans->getTargetIS()->getUID())
        {
          continue;
        }
        //check PS
        if (_graph[*pos].direct)
        {
          if (_graph[*pos].direct->hasSameProblemStatement(trans.get()))
          {
            edge = *pos;
            result = true; //ok IS is correct and PS also
            break;
          };
        }
        else if (_graph[*pos].inverse)
        {
          if (_graph[*pos].inverse->hasSameProblemStatement(trans.get()))
          {
            edge = *pos;
            result = true; //ok IS is correct and PS also
            break;
          };
        }
      }

      return result;
    };

    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::RegistrationGraphType::edge_descriptor
      SimpleOntologyCore<TOATraits>::
      addEdge(ConstInfSpacePointer movingIS, ConstInfSpacePointer targetIS)
    {
      typename RegistrationGraphType::edge_descriptor result;

      typename RegistrationGraphType::vertex_descriptor movingV = getVertex(movingIS);
      typename RegistrationGraphType::vertex_descriptor targetV = getVertex(targetIS);

      //we add the edge as "target -> moving" because it is more efficient when
      //searching in the registration graph via dijkstra_shortest_path etc.
      ::std::pair<typename RegistrationGraphType::edge_descriptor, bool> addResult = ::boost::add_edge(targetV, movingV,_graph);

      result = addResult.first;

      if (!(addResult.second)) { throw exceptions::InvalidArgument("Unable to add an edge.");
}

      return result;
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      updateEdge(typename RegistrationGraphType::edge_descriptor edge, TransformationInfoPointer trans)
    {
      bool hasRemovedEdge = false;
      TransformationInfoPointer oldTrans;

      if (trans->getSupportedDataRepresentation()==DataRepresentation::Continuous)
      {
        if (_graph[edge].direct)
        {
          hasRemovedEdge=true;
          oldTrans = _graph[edge].direct;
        }
        _graph[edge].direct = trans;
      } 
      else
      {
        if (_graph[edge].inverse)
        {
          hasRemovedEdge=true;
          oldTrans = _graph[edge].inverse;
        }
        _graph[edge].inverse = trans;
      }

      if (hasRemovedEdge)
      {
        _transformationMap.erase(oldTrans->getUID());
      }

    };

    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::RegistrationGraphType::vertex_descriptor
      SimpleOntologyCore<TOATraits>::
      getVertex(ConstInfSpacePointer is) const
    {
      std::pair<typename RegistrationGraphType::vertex_iterator, typename RegistrationGraphType::vertex_iterator> range = boost::vertices(_graph);

      for (typename RegistrationGraphType::vertex_iterator pos = range.first; pos != range.second; ++pos)
      {
        if (_graph[*pos].infSpace->getUID() == is->getUID())
        {
          return *pos;
        }
      }

      throw exceptions::InvalidArgument("Error, cannot find IS in registration graph. Should be there. Check graph initialization.");
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      addVertex(ConstInfSpacePointer is)
    {
      typename RegistrationGraphType::vertex_descriptor v = ::boost::add_vertex(_graph);

      _graph[v].infSpace = is;

    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      deleteVertex(ConstInfSpacePointer is)
    {
      typename RegistrationGraphType::vertex_descriptor v = getVertex(is);

      ::boost::remove_vertex(v,_graph);
    };

    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::WeightMapType
      SimpleOntologyCore<TOATraits>::
      generateWeightMap_reg(DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance, const RegPathMetricInterface* pMetric)
    {
      WeightMapType result;

      std::pair<typename RegistrationGraphType::edge_iterator, typename RegistrationGraphType::edge_iterator> range = boost::edges(_graph);

      for (typename RegistrationGraphType::edge_iterator pos = range.first; pos != range.second; ++pos)
      {
        double weight = baseCost;

        if ((requiredDataSupport == DataRepresentationSupport::All|| requiredDataSupport == DataRepresentationSupport::Discrete)&&
          (!_graph[*pos].inverse))
        {
          weight += fatalPenaltyCost;
        }

        if ((requiredDataSupport == DataRepresentationSupport::All|| requiredDataSupport == DataRepresentationSupport::Continuous)&&
          (!_graph[*pos].direct))
        {
          weight += fatalPenaltyCost;
        }

        RegistrationInfoPointer spRegInfo(new RegistrationInfoType);
        spRegInfo->setTransformations(_graph[*pos].direct,_graph[*pos].inverse);

        if (pProblemCompliance)
        {
          if (!pProblemCompliance->checkComplianceOfStatement(spRegInfo->getAssociatedProblemStatement().get()))
          {
            weight += fatalPenaltyCost;
          }
        }

        if (pMetric)
        {
          weight += pMetric->evaluatePathElement(spRegInfo.get());
        } 

        result[*pos] = weight;
      }

      return result;
    };

    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::WeightMapType
      SimpleOntologyCore<TOATraits>::
      generateWeightMap_trans(DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance, const TransPathMetricInterface* pMetric)
    {
      WeightMapType result;

      std::pair<typename RegistrationGraphType::edge_iterator, typename RegistrationGraphType::edge_iterator> range = boost::edges(_graph);

      for (typename RegistrationGraphType::edge_iterator pos = range.first; pos != range.second; ++pos)
      {
        double weight = baseCost;

        if ((requiredDataSupport == DataRepresentationSupport::All|| requiredDataSupport == DataRepresentationSupport::Discrete)&&
          (!_graph[*pos].inverse))
        {
          weight += fatalPenaltyCost;
        }

        if ((requiredDataSupport == DataRepresentationSupport::All|| requiredDataSupport == DataRepresentationSupport::Continuous)&&
          (!_graph[*pos].direct))
        {
          weight += fatalPenaltyCost;
        }

        if (pProblemCompliance)
        {
          RegistrationInfoPointer spRegInfo(new RegistrationInfoType);
          spRegInfo->setTransformations(_graph[*pos].direct,_graph[*pos].inverse);

          if (!pProblemCompliance->checkComplianceOfStatement(spRegInfo->getAssociatedProblemStatement().get()))
          {
            weight += fatalPenaltyCost;
          }
        }

        if (pMetric)
        {
          double weightD = fatalPenaltyCost;
          if (_graph[*pos].direct) { weightD = pMetric->evaluatePathElement(_graph[*pos].direct.get());
}
          double weightI = fatalPenaltyCost;
          if (_graph[*pos].direct) { weightI = pMetric->evaluatePathElement(_graph[*pos].inverse.get());
}

          if (requiredDataSupport == DataRepresentationSupport::Discrete)
          {
            weight += weightI;
          }
          else if (requiredDataSupport == DataRepresentationSupport::Continuous)
          {
            weight += weightD;
          }
          else if (requiredDataSupport == DataRepresentationSupport::All)
          {
            weight += weightI>weightD ? weightI : weightD;
          }
          else
          {
            weight += weightI<weightD ? weightI : weightD;
          }
        } 

        result[*pos] = weight;
      }

      return result;
    };


    template <class TEdgeMap>
    class record_edges : public ::boost::dijkstra_visitor<>
    {
    public:
      record_edges(TEdgeMap& e)
        : m_edges(e) { }

      template <class Edge, class Graph>
      void edge_relaxed(Edge e, Graph& g) {
        // set the parent of the target(e) to source(e)
        m_edges[::boost::target(e, g)] = e;
      }
    protected:
      TEdgeMap& m_edges;
    };


    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      generateMinimalPathPredecessors(ConstInfSpacePointer targetIS, WeightMapType& map, PredecessorMapType& predecessors, EdgeMapType& edges)
    {
      typename RegistrationGraphType::vertex_descriptor v = getVertex(targetIS);

      PredecessorMapType result;
      record_edges<EdgeMapType> recorder(edges);


      ::boost::associative_property_map<WeightMapType>      pmWeigth(map); 
      ::boost::associative_property_map<PredecessorMapType> pmPredecessor(predecessors); 

      ::boost::dijkstra_shortest_paths(_graph,v,::boost::weight_map(pmWeigth).predecessor_map(pmPredecessor).visitor(recorder));
    };

    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::RegistrationPathPointer
      SimpleOntologyCore<TOATraits>::
      generateRegPath(ConstInfSpacePointer movingIS, ConstInfSpacePointer targetIS, const WeightMapType& weights, const PredecessorMapType& predecessors, const EdgeMapType& edges)
    {
      RegistrationPathPointer result;
      RegistrationPathPointer temp(new RegistrationPathType);

      bool reachedTarget = false;
      typename RegistrationGraphType::vertex_descriptor currentV = getVertex(movingIS);
      typename RegistrationGraphType::vertex_descriptor targetV = getVertex(targetIS);

      while (!reachedTarget)
      {
        auto posV = predecessors.find(currentV);
        assert(posV!=predecessors.end());
        if (posV->second == currentV)
        {
          if (posV->second == targetV)
          {
            reachedTarget = true;
          }
          else
          { //this moving IS has no connection
            break;
          }
        }
        else
        {
          auto posEdge = edges.find(currentV);
          assert(posEdge!=edges.end());
          auto posWeigth = weights.find(posEdge->second);

          if (posWeigth->second<fatalPenaltyCost)
          { //it is a legal path
            RegistrationInfoPointer spInfo(new RegistrationInfoType);
            spInfo->setTransformations(_graph[posEdge->second].direct,_graph[posEdge->second].inverse);
            temp->appendElement(spInfo);
          }
          else
          { //even the shortest path is not valid -> breake generation.
            break;
          }
          currentV = posV->second;
        }
      }

      if (reachedTarget) { result = temp;
}

      return result;
    };

    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::TransformationPathPointer
      SimpleOntologyCore<TOATraits>::
      generateTransPath(ConstInfSpacePointer movingIS, ConstInfSpacePointer targetIS, DataRepresentation::Type requiredDataSupport, const WeightMapType& weights, const PredecessorMapType& predecessors, const EdgeMapType& edges)
    {
      TransformationPathPointer result;
      TransformationPathPointer temp(new TransformationPathType);

      bool reachedTarget = false;
      typename RegistrationGraphType::vertex_descriptor currentV = getVertex(movingIS);
      typename RegistrationGraphType::vertex_descriptor targetV = getVertex(targetIS);
      while (!reachedTarget)
      {
        auto posV = predecessors.find(currentV);
        assert(posV!=predecessors.end());
        if (posV->second == currentV)
        {
          if (posV->second == targetV)
          {
            reachedTarget = true;
          }
          else
          { //this moving IS has no connection
            break;
          }
        }
        else
        {
          auto posEdge = edges.find(currentV);
          assert(posEdge!=edges.end());

          auto posWeigth = weights.find(posEdge->second);

          if (posWeigth->second<fatalPenaltyCost)
          { //it is a legal path
            if (requiredDataSupport == DataRepresentation::Continuous)
            {
              if (_graph[posEdge->second].direct)
              {
                temp->appendElement(_graph[posEdge->second].direct);
              }
              else
              {
                break; //shortest path isn't valid for this data representation
              }
            }
            else
            {
              if (_graph[posEdge->second].inverse)
              {
                temp->appendElement(_graph[posEdge->second].inverse);
              }
              else
              {
                break; //shortest path isn't valid for this data representation
              }
            }
          }
          else
          { //even the shortest path is not valid -> breake generation.
            break;
          }
          currentV = posV->second;
        }
      }
      if (reachedTarget) { result = temp;
}

      return result;
    };

    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::RegPathOptColPointer
      SimpleOntologyCore<TOATraits>::
      generateRegCollection(const SimpleSearchMapType& searchResult, ConstInfEntityPointer ie) const
    {
      RegPathOptColPointer result(new RegPathOptColType);

      if (ie)
      {
        result->setMovingEntity(ie);
      }

      for (auto pos = searchResult.begin(); pos != searchResult.end(); ++pos)
      {
        typename RegPathOptColType::OptionType::Pointer spOption (new typename RegPathOptColType::OptionType);
        spOption->setMovingEntity(ie);
        RegistrationPathPointer spPath(new RegistrationPathType);

        //must iterate reverse because of inverse graph layout
        for (auto posPath = pos->rbegin(); posPath!=pos->rend(); ++posPath)
        {
          RegistrationInfoPointer spInfo(new RegistrationInfoType);
          spInfo->setTransformations(_graph[*posPath].direct,_graph[*posPath].inverse);
          spPath->appendElement(spInfo);
        }

        spOption->setPath(spPath);
        result->addOption(spOption);
      }
      return result;
    };

    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::TransPathOptColPointer
      SimpleOntologyCore<TOATraits>::
      generateTransCollection(const SimpleSearchMapType& searchResult, ConstInfEntityPointer ie) const
    {
      TransPathOptColPointer result(new TransPathOptColType);
      DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::Arbitrary;
      if (ie)
      {
        requiredDataSupport = convertToSupport(ie->getDataRepresentation());
        result->setMovingEntity(ie);
      }

      for (auto pos = searchResult.begin(); pos != searchResult.end(); ++pos)
      {
        TransformationPathPointer spCPath(new TransformationPathType);
        TransformationPathPointer spDPath(new TransformationPathType);

        //must iterate reverse because of inverse graph layout
        for (auto posPath = pos->rbegin(); posPath!=pos->rend(); ++posPath)
        {
          if (requiredDataSupport != DataRepresentationSupport::Discrete)
          {
            spCPath->appendElement(_graph[*posPath].direct);
          }
          if (requiredDataSupport != DataRepresentationSupport::Continuous)
          {
            spDPath->appendElement(_graph[*posPath].inverse);
          }
        }

        if (requiredDataSupport != DataRepresentationSupport::Discrete)
        {
          typename TransPathOptColType::OptionType::Pointer spOption (new typename TransPathOptColType::OptionType());
          spOption->setMovingEntity(ie);
          spOption->setPath(spCPath);
          result->addOption(spOption);
        }
        if (requiredDataSupport != DataRepresentationSupport::Continuous)
        {
          typename TransPathOptColType::OptionType::Pointer spOption (new typename TransPathOptColType::OptionType());
          spOption->setMovingEntity(ie);
          spOption->setPath(spDPath);
          result->addOption(spOption);
        }
      }
      return result;
    };


    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::ConstInfSpaceEntityVectorType
      SimpleOntologyCore<TOATraits>::
      generateMapableIS( ConstInfSpacePointer targetIS, const WeightMapType& weights, const PredecessorMapType& predecessors, const EdgeMapType& edges )
    {
      ConstInfSpaceEntityVectorType result;

      typename RegistrationGraphType::vertex_descriptor targetV = getVertex(targetIS);
      std::pair<typename RegistrationGraphType::vertex_iterator, typename RegistrationGraphType::vertex_iterator> range = boost::vertices(_graph);
      //go through all vertices
      for (typename RegistrationGraphType::vertex_iterator pos = range.first; pos != range.second; ++pos)
      {
        bool reachedTarget = false;
        typename RegistrationGraphType::vertex_descriptor currentV = *pos;
        if (currentV != targetV)
        { //don't check self reference, only other information spaces.
          while (!reachedTarget)
          {
            auto posV = predecessors.find(currentV);
            assert(posV!=predecessors.end());
            if (posV->second == currentV)
            {
              if (posV->second == targetV)
              {
                reachedTarget = true;
              }
              else
              {
                break;
              }
            }
            else
            {
              auto posEdge = edges.find(currentV);
              assert(posEdge!=edges.end());
              auto posWeigth = weights.find(posEdge->second);

              if (posWeigth->second>=fatalPenaltyCost)
              { //even the shortest path is not valid -> breake generation.
                break;
              }
              currentV = posV->second;
            }
          }
        }
        if (reachedTarget) { result.push_back(_graph[*pos].infSpace);
}
      }

      return result;
    }

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      updateEntity2CorrelationMap(ConstCorrelationPointer corr)
    {
      typedef std::pair<typename EntityCorrelationMapType::iterator,typename EntityCorrelationMapType::iterator> PairType;

      //1st remove all old look ups for this correlation
      auto pos = _entity2CorrelationMap.begin();

      while (pos!=  _entity2CorrelationMap.end())
      {
        if (pos->second == corr->getUID())
        {
          pos = _entity2CorrelationMap.erase(pos);
        }
        else
        {
          ++pos;
        }
      }

      //2nd add current relations
      for (auto relatedPos = corr->getCorrelatedEntitiesBegin(); relatedPos!=corr->getCorrelatedEntitiesEnd(); ++relatedPos)
      {
        _entity2CorrelationMap.insert(std::make_pair((*relatedPos)->getUID(),corr->getUID()));
      }
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      removeEntityFromCorrelations(const InfEntityUIDType& entity)
    {
      typedef std::pair<typename EntityCorrelationMapType::iterator, typename EntityCorrelationMapType::iterator> PairType;

      PairType sourceFindings = _entity2CorrelationMap.equal_range(entity);

      //got through all source entity correlations
      for (auto pos = sourceFindings.first; pos!= sourceFindings.second; ++pos)
      {
        auto posCorr = _correlationMap.find(pos->second);

        if (posCorr !=  _correlationMap.end())
        {
          auto relatedPos = posCorr->second->getCorrelatedEntitiesBegin();

          while(relatedPos!=posCorr->second->getCorrelatedEntitiesEnd())
          {
            if ((*relatedPos)->getUID()==entity)
            {
              relatedPos = posCorr->second->removeCorrelatedEntity(relatedPos);
            }
            else
            {
              ++relatedPos;
            }
          }
        }
      }
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      actualizeEntityInCorrelations(const InfEntityUIDType& entity)
    {
      typename EntityMapType::const_iterator entityPos = _entityMap.find(entity);
      if (entityPos==_entityMap.end()) throw exceptions::InvalidArgument("Cannot actualize entity. It does not exist");

      typedef std::pair<typename EntityCorrelationMapType::iterator, typename EntityCorrelationMapType::iterator> PairType;

      PairType sourceFindings = _entity2CorrelationMap.equal_range(entity);

      //got through all source entity correlations
      for (typename EntityCorrelationMapType::iterator pos = sourceFindings.first; pos!= sourceFindings.second; ++pos)
      {
        typename CorrelationMapType::iterator posCorr = _correlationMap.find(pos->second);

        if (posCorr !=  _correlationMap.end())
        {
          typename CorrelationType::EntityIterator relatedPos = posCorr->second->findCorrelatedEntity(entity);

          if (relatedPos!=posCorr->second->getCorrelatedEntitiesEnd())
          {
            *relatedPos == entityPos->second;
          }
        }
      }
    };


    template <typename TOATraits>
    bool
      SimpleOntologyCore<TOATraits>::
      validateForCommit(CorrelationPointer corr)
    {
      bool result = true;

      for(auto relatedPos = corr->getCorrelatedEntitiesBegin(); relatedPos!=corr->getCorrelatedEntitiesEnd(); ++relatedPos)
      {
        typename EntityMapType::const_iterator entityPos = _entityMap.find((*relatedPos)->getUID());
        if (entityPos==_entityMap.end())
        {
          result = false;
          break;
        }
        *relatedPos = entityPos->second;
      };

      return result;
    };


    template <typename TOATraits>
    typename SimpleOntologyCore<TOATraits>::ConstEntityMapType
      SimpleOntologyCore<TOATraits>::
      getEntitiesByCorrelations(const ConstCorrelationMapType& correlations, const EntityUIDSetType& entities, bool excludeEntities)
    {
      ConstEntityMapType result;

      //got through all correlations
      for (auto pos = correlations.begin(); pos!= correlations.end(); ++pos)
      { //go through there entities
        for (auto relatedPos = pos->second->getCorrelatedEntitiesBegin(); relatedPos!=pos->second->getCorrelatedEntitiesEnd(); ++relatedPos)
        {
          if ((entities.find((*relatedPos)->getUID())!=entities.end()) != excludeEntities)
          { // the entity exists in the passed list and but its include mode or it is not in the list and it is exclude mode
            // -> transfer entity
            result[(*relatedPos)->getUID()] = *relatedPos;
          }
        }
      }
      return result;
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      getProblemModels(ConstModelMapType& models, const ProblemStatementUIDType& ps) const
    {
      typedef std::pair<typename StatementModelMapType::const_iterator,typename StatementModelMapType::const_iterator> PairType;

      PairType sourceFindings = _stat2ModelMap.equal_range(ps);

      //got through all source entity correlations
      for (auto sourcePos = sourceFindings.first; sourcePos!= sourceFindings.second; ++sourcePos)
      {
        auto posModel = _modelMap.find(sourcePos->second);

        if (posModel !=  _modelMap.end())
        {
          models[posModel->second->getUID()] = posModel->second;
        }
      }
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      updateStatement2ModelMap(ConstProblemModelPointer pModell)
    {
      typedef std::pair<typename StatementModelMapType::iterator, typename StatementModelMapType::iterator> PairType;

      //1st remove all old look ups for this correlation
      auto pos = _stat2ModelMap.begin();

      while (pos!=  _stat2ModelMap.end())
      {
        if (pos->second == pModell->getUID())
        {
          pos = _stat2ModelMap.erase(pos);
        }
        else
        {
          ++pos;
        }
      }

      //2nd add current relations
      for (auto relatedPos = pModell->getStatementBegin(); relatedPos!=pModell->getStatementEnd(); ++relatedPos)
      {
        _stat2ModelMap.insert(std::make_pair((*relatedPos)->getUID(),pModell->getUID()));
      }
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      removeStatementFromModels(const ProblemStatementUIDType& stat)
    {
      typedef std::pair<typename StatementModelMapType::iterator, typename StatementModelMapType::iterator> PairType;

      PairType sourceFindings = _stat2ModelMap.equal_range(stat);

      //got through all source entity correlations
      for (auto pos = sourceFindings.first; pos!= sourceFindings.second; ++pos)
      {
        auto posModel = _modelMap.find(pos->second);

        if (posModel !=  _modelMap.end())
        {
          auto relatedPos = posModel->second->getStatementBegin();

          while(relatedPos!=posModel->second->getStatementEnd())
          {
            if ((*relatedPos)->getUID()==stat)
            {
              relatedPos = posModel->second->removeStatement(relatedPos);
            }
            else
            {
              ++relatedPos;
            }
          }
        }
      }
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      actualizeStatementInModels(const ProblemStatementUIDType& stat)
    {
      typename StatementMapType::const_iterator statPos = _statementMap.find(stat);
      if (statPos==_statementMap.end()) throw exceptions::InvalidArgument("Cannot actualize statement. It is not defined in the ontology.");

      typedef std::pair<typename StatementModelMapType::iterator, typename StatementModelMapType::iterator> PairType;

      PairType sourceFindings = _stat2ModelMap.equal_range(stat);

      //got through all source entity correlations
      for (typename StatementModelMapType::iterator pos = sourceFindings.first; pos!= sourceFindings.second; ++pos)
      {
        typename ModelMapType::iterator posModel = _modelMap.find(pos->second);

        if (posModel !=  _modelMap.end())
        {
          typename ProblemModelType::ProblemIterator relatedPos = posModel->second->findStatement(stat);

          if (relatedPos!=posModel->second->getStatementEnd())
          {
            *relatedPos == statPos->second;
          }
        }
      }
    };

    template <typename TOATraits>
    bool
      SimpleOntologyCore<TOATraits>::
      validateForCommit(ProblemModelPointer model)
    {
      bool result = true;

      for(auto relatedPos = model->getStatementBegin(); relatedPos!=model->getStatementEnd(); ++relatedPos)
      {
        typename StatementMapType::const_iterator statPos = _statementMap.find((*relatedPos)->getUID());
        if (statPos==_statementMap.end())
        {
          result = false;
          break;
        }
        *relatedPos = statPos->second;
      };

      return result;
    };

    template <typename TOATraits>
    void
      SimpleOntologyCore<TOATraits>::
      spliteEntitiesByData(const ConstInfEntityVectorType& movingEntities, ConstInfEntityVectorType&  continuousEntities, ConstInfEntityVectorType& discreteEntities)
    {
      continuousEntities.clear();
      discreteEntities.clear();

      for (auto pos = movingEntities.begin(); pos != movingEntities.end(); ++pos)
      {
        if ((*pos)->getDataRepresentation()==DataRepresentation::Continuous)
        {
          continuousEntities.push_back(*pos);
        }
        else
        {
          discreteEntities.push_back(*pos);
        }
      }
    };

    template <typename TOATraits>
    MappingError::Type
      SimpleOntologyCore<TOATraits>::checkOptionCollectionSupport(ConstRegPathOptColPointer col, DataRepresentationSupport::Type requiredDataSupport) const
    {
      MappingError::Type result = MappingError::NoFailure;

      if (col->getOptionCount()>0)
      {
        MappingError::Type cResult = MappingError::NoFailure;
        MappingError::Type dResult = MappingError::NoFailure;
        using PolicyType = typename TOATraits::RegPathOptionTraitsType::Type::PathCheckPolicy;

        if (requiredDataSupport!=DataRepresentationSupport::Discrete)
        {
          InfEntityPointer spDummy(new InfEntityType());
          spDummy->setDataRepresentation(DataRepresentation::Continuous);

          for (auto pos = col->getBegin(); pos != col->getEnd(); ++pos)
          {
            MappingError::Type temp = PolicyType::checkForFailureReason((*pos)->getPath(),spDummy);
            if (temp>cResult)
            {
              cResult = temp;
            }
          }
        }

        if (requiredDataSupport!=DataRepresentationSupport::Continuous)
        {
          InfEntityPointer spDummy(new InfEntityType());
          spDummy->setDataRepresentation(DataRepresentation::Discrete);

          for (auto pos = col->getBegin(); pos != col->getEnd(); ++pos)
          {
            MappingError::Type temp = PolicyType::checkForFailureReason((*pos)->getPath(),spDummy);
            if (temp>dResult)
            {
              dResult = temp;
            }
          }
        }

        if (requiredDataSupport == DataRepresentationSupport::Continuous)
        {
          result = cResult;
        }
        else if (requiredDataSupport == DataRepresentationSupport::Discrete)
        {
          result = dResult;
        }
        else if (requiredDataSupport == DataRepresentationSupport::All)
        {
          result = (cResult<dResult)? dResult : cResult;
        }
        else /*requiredDataSupport == DataRepresentationSupport::Arbitrary*/
        {
          result = (cResult<dResult)? cResult : dResult;
        }
      }
      else
      {
        result = MappingError::NoPath;
      }

      return result;
    }

  } // end namespace scenario
} // end namespace iro
