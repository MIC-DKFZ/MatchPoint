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




#ifndef __MAP_SIMPLE_PATH_SEARCH_H
#define __MAP_SIMPLE_PATH_SEARCH_H

#include "boost/graph/adjacency_list.hpp"

namespace iro
{
  namespace core
  {
    struct SearchColor
    {
      enum Type {
        White = 0,
        Gray = 1,
        Black = 2
      };
    };

    template <class TEdgeDescriptor, class TVertexDescriptor, class TGraph, class TProblemCompliance, class TEdgeValidator>
    void
      simplePathSearchStep(::std::vector< ::std::vector< TEdgeDescriptor> >& result,
      const TGraph& graph,
      TVertexDescriptor currentIS,
      TVertexDescriptor searchedIS,
      DataRepresentationSupport::Type dataRep,
      const TProblemCompliance* pProblemCompliance,
      ::std::vector<TEdgeDescriptor>& currentPath,
      ::std::map<TVertexDescriptor, SearchColor::Type>& colorMap,
      TEdgeValidator& validator,
      bool cTrail, bool dTrail)
    {
      if (searchedIS == currentIS)
      { //match -> current path is a valid result, so transfere it, and back in stack
        result.push_back(currentPath);
      }
      else
      { //normal search
        colorMap[currentIS] = SearchColor::Gray;

        typedef typename TGraph::out_edge_iterator EdgeIterator;
        std::pair<EdgeIterator, EdgeIterator> edgeRange = ::boost::out_edges(currentIS, graph);

        for (EdgeIterator pos = edgeRange.first; pos != edgeRange.second; ++pos)
        {
          TVertexDescriptor nextIS = ::boost::target(*pos,graph);
          if (colorMap[nextIS]== SearchColor::White)
          { //not touched in the current path search, thus go this way
            bool currentCTrail = cTrail;
            bool currentDTrail = dTrail;

              //check if the edge is valid
              if (validator.isValid(*pos, graph, dataRep, pProblemCompliance, currentCTrail, currentDTrail))
              { 
                currentPath.push_back(*pos);

                simplePathSearchStep(result,graph,nextIS,searchedIS,dataRep,pProblemCompliance,currentPath,colorMap,validator, currentCTrail, currentDTrail);

                currentPath.pop_back();
              }
          }
        }
        colorMap[currentIS] = SearchColor::White;
      }
    };

    /**Helper function that searches for an registration path represented by a boost graph.
    The strategy used is that the function searches for the shortest paths that a) support the needed data
    representation and b) have problem compliance (if a ProblemCompliance instance was passed). To validate the
    edge and check the requirements the passed edge validator "validator" is used.*/
    template <class TEdgeDescriptor, class TVertexDescriptor, class TGraph, class TProblemCompliance, class TEdgeValidator>
    void 
      simplePathSearch(::std::vector< ::std::vector< TEdgeDescriptor> >& result,
      const TGraph& graph,
      TVertexDescriptor startIS,
      TVertexDescriptor searchedIS,
      DataRepresentationSupport::Type dataRep,
      const TProblemCompliance* pProblemCompliance,
      TEdgeValidator validator)
    {
      ::std::vector<TEdgeDescriptor> currentPath;
      ::std::map<TVertexDescriptor, SearchColor::Type> colorMap;
      ::std::pair<typename TGraph::vertex_iterator, typename TGraph::vertex_iterator> range = ::boost::vertices(graph);
      bool currentCTrail = true;
      bool currentDTrail = true;

      for (typename TGraph::vertex_iterator pos = range.first; pos!=range.second; ++pos)
      {
        colorMap[*pos] = SearchColor::White;
      }

      simplePathSearchStep(result,graph,startIS,searchedIS,dataRep,pProblemCompliance,currentPath,colorMap,validator,currentCTrail,currentDTrail);
    }

  } // end namespace core

} // end namespace iro

#endif
