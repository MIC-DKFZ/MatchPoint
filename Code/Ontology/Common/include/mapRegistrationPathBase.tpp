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




#ifndef __MAP_REGISTRATON_PATH_BASE_TPP
#define __MAP_REGISTRATON_PATH_BASE_TPP

#include "mapRegistrationPathBase.h"

namespace iro
{

  template <typename TRegistrationInfoTraits, typename TTransformationPathTraits>
  typename RegistrationPathBase<TRegistrationInfoTraits, TTransformationPathTraits>::ConstTransformationPathPointer
    RegistrationPathBase<TRegistrationInfoTraits, TTransformationPathTraits>::
    getContinuousTransformationPath() const
  {
    TransformationPathPointer spNewPath(new TransformationPathType);

    ConstPathElementIterator pos = this->_pathElements.begin();
    bool valid = true;

    while (valid && pos!=this->_pathElements.end())
    { //we haven't reched the end of the path and till now all elements were valid -> go on

      typename TransformationPathType::ConstPathElementPointer spTransElement = (*pos)->getContinuousTransformation();

      if (spTransElement)
      { //there is an element, so add it
        spNewPath->appendElement(spTransElement);
      }
      else
      { //path is broken
        valid = false;
      }
      ++pos;
    }

    ConstTransformationPathPointer spResult;
    if (valid)
    {
      spResult = spNewPath;
    }

    return spResult;
  };

  template <typename TRegistrationInfoTraits, typename TTransformationPathTraits>
  typename RegistrationPathBase<TRegistrationInfoTraits, TTransformationPathTraits>::ConstTransformationPathPointer
    RegistrationPathBase<TRegistrationInfoTraits, TTransformationPathTraits>::
    getDiscreteTransformationPath() const
  {
    TransformationPathPointer spNewPath(new TransformationPathType);

    ConstPathElementIterator pos = this->_pathElements.begin();
    bool valid = true;

    while (valid && pos!= this->pathElements.end())
    { //we haven't reched the end of the path and till now all elements were valid -> go on

      typename TransformationPathType::ConstPathElementPointer spTransElement = (*pos)->getDiscreteTransformation();

      if (spTransElement)
      { //there is an element, so add it
        spNewPath->appendElement(spTransElement);
      }
      else
      { //path is broken
        valid = false;
      }
      ++pos;
    }

    ConstTransformationPathPointer spResult;
    if (valid)
    {
      spResult = spNewPath;
    }

    return spResult;
  };

  template <typename TRegistrationInfoTraits, typename TTransformationPathTraits>
  RegistrationPathBase<TRegistrationInfoTraits, TTransformationPathTraits>::
    ~RegistrationPathBase()
  {
  };

  template <typename TRegistrationInfoTraits, typename TTransformationPathTraits>
  RegistrationPathBase<TRegistrationInfoTraits, TTransformationPathTraits>::
    RegistrationPathBase()
  {
  };

} // end namespace iro

#endif
