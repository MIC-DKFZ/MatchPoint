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



#ifndef __MAP_PROBLEM_STATEMENT_BASE_TPP
#define __MAP_PROBLEM_STATEMENT_BASE_TPP

#include "mapProblemStatementBase.h"

namespace iro
{
  namespace scenario
  {
    template <typename TUIDPolicy>
    const typename ProblemStatementBase<TUIDPolicy>::UIDType&
      ProblemStatementBase<TUIDPolicy>::
      getUID() const
    {
      return _uid;
    };

    template <typename TUIDPolicy>
    void
      ProblemStatementBase<TUIDPolicy>::
      setUID(const UIDType& uid)
    {
      _uid = uid;
    };

    template <typename TUIDPolicy>
    const typename ProblemStatementBase<TUIDPolicy>::NameType&
      ProblemStatementBase<TUIDPolicy>::
      getName() const
    {
      return _name;
    };

    template <typename TUIDPolicy>
    void
      ProblemStatementBase<TUIDPolicy>::
      setName(const NameType& name)
    {
      _name = name;
    };

    template <typename TUIDPolicy>
    ProblemStatementBase<TUIDPolicy>::
      ProblemStatementBase(): _name("")
    {
      _uid = TUIDPolicy::generateUID();
    };

    template <typename TUIDPolicy>
    ProblemStatementBase<TUIDPolicy>::
      ~ProblemStatementBase()
    {
    };

    template <typename TUIDPolicy>
    bool
      ProblemStatementBase<TUIDPolicy>::
      doCheckComplianceOfStatement(const Self* pProblem) const
    {
      return pProblem->getUID() == _uid;
    };

    template <typename TUIDPolicy>
    typename ProblemStatementBase<TUIDPolicy>::Pointer
      ProblemStatementBase<TUIDPolicy>::
      clone() const
    {
      Pointer spClone(new Self());

      spClone->setName(_name);
      spClone->setUID(_uid);

      return spClone;
    };

  } // end namespace scenario
} // end namespace iro

#endif
