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





#ifndef __IRO_I_PATH_METRIC_H
#define __IRO_I_PATH_METRIC_H

#include "mapOntologyExceptions.h"

#include <memory>

namespace iro
{
  /** This interface is realized by any class that
  * implements a path element metric. 
  * @ingroup Interface
  * */
  template <typename TPathElementTraits>
  class IPathMetric
  {
  public:
    typedef IPathMetric<TPathElementTraits> Self;
    typedef std::shared_ptr<Self>         Pointer;
    typedef std::shared_ptr<const Self>    ConstPointer;

    typedef typename TPathElementTraits::Type   PathElementType;
    typedef double                              MeasureType;

    /** evaluates the passe Element and returns the measure.
     * @pre pElement must not be NULL
     * @exception exceptions::InvalidArgument: precondition is violated.*/
    MeasureType evaluatePathElement(const PathElementType* pElement) const
    {
      if (!pElement) throw exceptions::InvalidArgument("Passed path element pointer is NULL. Cannot evaluate Element");
      return doEvaluatePathElement(pElement);
    };

  protected:

    virtual MeasureType doEvaluatePathElement(const PathElementType* pElement) const = 0;

    virtual ~IPathMetric() {};
    IPathMetric() {};
  private:
    IPathMetric(const Self&); //not implemented by purpose
    Self& operator=(const Self&); //not implemented by purpose
  };

} // end namespace iro

#endif
