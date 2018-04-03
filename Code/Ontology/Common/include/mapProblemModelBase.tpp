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



#ifndef __MAP_PROBLEM_MODEL_BASE_TPP
#define __MAP_PROBLEM_MODEL_BASE_TPP

#include "mapProblemModelBase.h"

namespace iro
{
  namespace scenario
  {
    template <typename TProblemStatementTraits, typename TUIDPolicy>
    const typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::UIDType&
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      getUID() const
    {
      return _uid;
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    void
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      setUID(const UIDType& uid)
    {
      _uid = uid;
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    const typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::NameType&
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      getName() const
    {
      return _name;
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    void
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      setName(const NameType& name)
    {
      _name = name;
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      ProblemModelBase():_name("")
    {
      _uid = TUIDPolicy::generateUID();
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      ~ProblemModelBase()
    {
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::ProblemIterator
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      getStatementBegin()
    {
      return _associatedStatements.begin();
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::ConstProblemIterator
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      getStatementBegin() const
    {
      return _associatedStatements.begin();
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::ProblemIterator
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      getStatementEnd()
    {
      return _associatedStatements.end();
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::ConstProblemIterator
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      getStatementEnd() const
    {
      return _associatedStatements.end();
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::SizeType
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      getStatementCount() const
    {
      return _associatedStatements.size();
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::ProblemIterator
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      findStatement(const ProblemStatementUIDType& uid)
    {
      ProblemIterator result = getStatementEnd();

      for ( typename StatementVectorType::iterator pos = _associatedStatements.begin(); pos!=_associatedStatements.end(); ++pos)
      {
        if ( (*pos)->getUID() == uid)
        {
          result = pos;
          break;
        }
      }

      return result;
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::ConstProblemIterator
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      findStatement(const ProblemStatementUIDType& uid) const
    {
      ConstProblemIterator result = getStatementEnd();

      for ( ConstProblemIterator pos = _associatedStatements.begin(); pos!=_associatedStatements.end(); ++pos)
      {
        if ( (*pos)->getUID() == uid)
        {
          result = pos;
          break;
        }
      }

      return result;
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    void
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      addStatement(ProblemStatementConstPointer pStatement)
    {
      if (!pStatement)
      {
        //@TODO add exception
      }
      if (findStatement(pStatement->getUID())!=_associatedStatements.end())
      {
        //it is not allowed that the same UID is allready included
        //@TODO add exception
      }

      _associatedStatements.push_back(pStatement);
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::ProblemIterator
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      removeStatement(ProblemIterator pos)
    {
      return _associatedStatements.erase(pos);
    };


    template <typename TProblemStatementTraits, typename TUIDPolicy>
    void
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
       resetStatements()
    {
      _associatedStatements.clear();
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    typename ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::Pointer
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      clone() const
    {
      Pointer spClone(new Self());

      spClone->setName(_name);
      spClone->setUID(_uid);
      spClone->_associatedStatements = _associatedStatements;

      return spClone;
    };

    template <typename TProblemStatementTraits, typename TUIDPolicy>
    bool
      ProblemModelBase<TProblemStatementTraits, TUIDPolicy>::
      doCheckComplianceOfStatement(const ProblemStatementType* pProblem) const
    {
      bool result = false;

      ConstProblemIterator pos = _associatedStatements.begin();

      while (!result && pos!=_associatedStatements.end())
      { //we haven't reached the end of the path and till now all elements were compliant -> check the next element
        result = (*pos)->checkComplianceOfStatement(pProblem);
        ++pos;
      }

      return result;
    };

  } // end namespace scenario
} // end namespace iro

#endif
