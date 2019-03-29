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





#ifndef __MAP_PROBLEM_STATEMENT_ASSOCIATED_INTERFACE_H
#define __MAP_PROBLEM_STATEMENT_ASSOCIATED_INTERFACE_H

#include "mapIProblemComplianceChecker.h"

namespace iro
{
  /** This interface is realized by any class that
  * has an association with a problem statement.*/
  template <typename TProblemStatementTraits>
  class IProblemStatementAssociated : public IProblemComplianceChecker<TProblemStatementTraits>
  {
  public:
    using ConstProblemPointer = typename TProblemStatementTraits::ConstPointer;
    using Self = IProblemStatementAssociated<TProblemStatementTraits>;

    /** Returns the const pointer to the associated problem statement.
    * Pointer may be null, if no statement is defined.*/
    virtual ConstProblemPointer getAssociatedProblemStatement() const = 0;

    /**Checks if this and the passed instance are associated with the same
    * problem statement.
    * @param [in] nullEquals Indicates if it counts as equal if both
    * associates have no problem statement (NULL).
    * @return Indicates if they have the same problem statement.
    * @pre pAssociate must point to a valid instance
    * @exception: ::iro::exceptions::InvalidArgument: pAssociate is not valid*/
    bool hasSameProblemStatement( const Self* pAssociate, bool nullEquals = true) const
    {
      if (!pAssociate) { throw ::iro::exceptions::InvalidArgument("Error. Cannot equality of problem statements. pAssociate is a NULL pointer.");
}

      bool result = false;

      if (pAssociate->getAssociatedProblemStatement())
      {
        if (this->getAssociatedProblemStatement())
        {
          result = pAssociate->getAssociatedProblemStatement()->getUID() == this->getAssociatedProblemStatement()->getUID();
        }
      }
      else
      { //first one is null
        if (!(this->getAssociatedProblemStatement()))
        { //second one is also null
          result = nullEquals;
        }
      }
      return result;
    };

  protected:
    ~IProblemStatementAssociated() override = default;
    IProblemStatementAssociated() = default;
  private:
    IProblemStatementAssociated(const Self&) = delete; //not implemented by purpose
    IProblemStatementAssociated& operator=(const Self&) = delete; //not implemented by purpose
  };


} // end namespace iro

#endif
