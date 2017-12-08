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




#ifndef __MAP_TRANSFORMATION_PATH_BASE_TPP
#define __MAP_TRANSFORMATION_PATH_BASE_TPP

#include "mapTransformationPathBase.h"

namespace iro
{

  template <typename TTransformationInfoTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  typename TransformationPathBase<TTransformationInfoTraits, TInformationSpaceTraits, TProblemStatementTraits>::PathElementIterator
    TransformationPathBase<TTransformationInfoTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    doInsertElement(PathElementIterator pos, ConstPathElementPointer newElement)
  {
    //check data representation
    if (!this->_pathElements.empty())
    { //there will be an element bevor the newElement -> check IS compliance
      if (this->_pathElements.front()->getSupportedDataRepresentation() != newElement->getSupportedDataRepresentation())
      {
        throw exceptions::InvalidDataRepresentation("The insert element has wrong data representation support.");
      }
    }

    return Superclass::doInsertElement(pos,newElement);
  };

  template <typename TTransformationInfoTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  void
    TransformationPathBase<TTransformationInfoTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    doAppend(ConstPathElementPointer newElement)
  {
    if (!this->_pathElements.empty())
    { //there will be an element bevor the newElement -> check IS compliance
      if (this->_pathElements.front()->getSupportedDataRepresentation() != newElement->getSupportedDataRepresentation())
      {
        throw exceptions::InvalidDataRepresentation("The insert element has wrong data representation support.");
      }
    }

    Superclass::doAppend(newElement);
  };

  template <typename TTransformationInfoTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  TransformationPathBase<TTransformationInfoTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    ~TransformationPathBase()
  {
  };

  template <typename TTransformationInfoTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
  TransformationPathBase<TTransformationInfoTraits, TInformationSpaceTraits, TProblemStatementTraits>::
    TransformationPathBase()
  {
  };

} // end namespace iro

#endif
