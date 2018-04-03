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




#ifndef __MAP_CONNECTOR_PATH_BASE_TPP
#define __MAP_CONNECTOR_PATH_BASE_TPP

#include "mapISConnectorPathBase.h"

namespace iro
{

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::ConstISPointer
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    getMovingIS() const
  {
    ConstISPointer spIS;

    if (!_pathElements.empty())
    {
      spIS = _pathElements.front()->getMovingIS();
    }

    return spIS;
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::ConstISPointer
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    getTargetIS() const
  {
    ConstISPointer spIS;

    if (!_pathElements.empty())
    {
      spIS = _pathElements.back()->getTargetIS();
    }

    return spIS;
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  bool
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const
  {
    bool result = true;

    ConstPathElementIterator pos = _pathElements.begin();

    while (result && pos!=_pathElements.end())
    { //we haven't reched the end of the path and till now all elements were compliant -> check the next element
      result = (*pos)->checkProblemCompliance(pProblemCompliance);
      ++pos;
    }

    return result;
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::PathElementIterator
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    getBegin()
  {
    return _pathElements.begin();
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::ConstPathElementIterator
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    getBegin() const
  {
    return _pathElements.begin();
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::PathElementIterator
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    getEnd()
  {
    return _pathElements.end();
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::ConstPathElementIterator
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    getEnd() const
  {
    return _pathElements.end();
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::PathSizeType
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    size() const
  {
    return _pathElements.size();
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::PathElementIterator
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    insertElement(PathElementIterator pos, ConstPathElementPointer newElement)
  {
    //check the connection correctness precondition
    if (pos!=_pathElements.begin() && !_pathElements.empty())
    { //there will be an element bevor the newElement -> check IS compliance
      PathElementIterator predecessor = pos;
      --predecessor;
      if ((*predecessor)->getTargetIS() != newElement->getMovingIS())
      {
        throw exceptions::InvalidMovingIS("The insert element would violated the IS connection correctness.");
      }
    }

    if (pos!=_pathElements.end() && !_pathElements.empty())
    { //there will be an element after (pos itself) the newElement -> check IS compliance
      if ((*pos)->getMovingIS() != newElement->getTargetIS())
      {
        throw exceptions::InvalidTargetIS("The insert element would violated the IS connection correctness.");
      }
    }

    return doInsertElement(pos,newElement);
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  void
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    appendElement(ConstPathElementPointer newElement)
  {
    //check the connection correctness precondition
    if (!_pathElements.empty())
    { //there will be an element bevor the newElement -> check IS compliance
      if (_pathElements.back()->getTargetIS() != newElement->getMovingIS())
      {
        throw exceptions::InvalidMovingIS("The insert element would violated the IS connection correctness.");
      }
    }

    doAppend(newElement);
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::PathElementIterator
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    doInsertElement(PathElementIterator pos, ConstPathElementPointer newElement)
  {
    return _pathElements.insert(pos,newElement);
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  void
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    doAppend(ConstPathElementPointer newElement)
  {
    _pathElements.push_back(newElement);
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::PathElementIterator
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    removeElement(PathElementIterator pos)
  {
    return _pathElements.erase(pos);
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  void
    ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    resetElements()
  {
    _pathElements.clear();
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    ~ISConnectorPathBase()
  {
  };

  template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    ISConnectorPathBase()
  {
  };

} // end namespace iro

#endif
