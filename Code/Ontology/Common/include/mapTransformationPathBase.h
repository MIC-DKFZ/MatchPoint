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




#ifndef __IRO_TRANSFORMATION_PATH_BASE_H
#define __IRO_TRANSFORMATION_PATH_BASE_H

#include "mapISConnectorPathBase.h"
#include "mapOntologyExceptions.h"

namespace iro
{

		/*! @class TransformationPathBase
    * @brief Base class for all transformation paths.
    *
    * A Transformation path defines a sequence of transformations (TransformationInfo instances)
    * that lead from the moving information space of the path to the target information space.
    * Because the ontology supports the fact that an entity may be mapped by using interim
    * registration spaces (Moving IS -> Interim IS -> Target IS) all evaluations of
    * "mappablility" result in paths and not plain Transformation-/RegistrationInfo.
    * Although most of the paths should be of size 1, because long paths will introduce more
    * error risks.\n
    * Because a TransformationPath is compiled of TransformationInfo instances it is only valid
    * for one data representation type. Therefore a TransformationPath has more precondition
    * regarding elements that should be added than ISConnectorPathBase.\n\n
    * 
    */
    template <typename TTransformationInfoTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
    class TransformationPathBase : public ISConnectorPathBase< TTransformationInfoTraits, TInformationSpaceTraits, TProblemStatementTraits >
		{
    public:
      typedef TransformationPathBase< TTransformationInfoTraits, TInformationSpaceTraits, TProblemStatementTraits > Self;
      typedef ISConnectorPathBase< TTransformationInfoTraits, TInformationSpaceTraits, TProblemStatementTraits > Superclass;
      typedef ::std::shared_ptr<Self> Pointer;
      typedef ::std::shared_ptr<const Self> ConstPointer;

      typedef typename Superclass::ConstISPointer  ConstISPointer;

      typedef typename Superclass::ConstISPointer  ProblemComplianceInterface;

      typedef typename Superclass::ProblemStatementType   ProblemStatementType;
      typedef typename Superclass::ProblemPointer         ProblemPointer;
      typedef typename Superclass::ConstProblemPointer    ConstProblemPointer;

      typedef typename Superclass::ConstPathElementPointer  ConstPathElementPointer;

      typedef typename Superclass::PathElementIterator      PathElementIterator;
      typedef typename Superclass::ConstPathElementIterator ConstPathElementIterator;
      typedef typename Superclass::PathSizeType             PathSizeType;

			virtual ~TransformationPathBase();
			TransformationPathBase();
    protected:
      /*! In addition to the base implementation it also checks if the elment has the same data support.
       * @pre The data representation support of the new element must equal the support of the path elements.
       * @param [in] pos Iterator indicating the postion of the element where the element should be inserted.
       * @param [in] newElement The new element that should be inserted.
       * @return Iterator that points to the position of the inserted element in the path.
       * @exception ::iro::exceptions::InvalidDataRepresentation: the precondition is violated*/
      virtual PathElementIterator doInsertElement(PathElementIterator pos, ConstPathElementPointer newElement);

      /*! Adds the passed newElement at the end of the path.
       * @pre The moving IS of the new element must equal the target IS of the preceeding element (if the path is not empty)
       * @param [in] newElement The new element that should be inserted.
       * @exception ::iro::exceptions::InvalidDataRepresentation: the preconditions is violated*/
      virtual void doAppend(ConstPathElementPointer newElement);

    private:
			TransformationPathBase(const Self&); //not implemented by purpose
			Self& operator=(const Self&); //not implemented by purpose
		};
} // end namespace iro

#ifndef IRO_MANUAL_TPP
#include "mapTransformationPathBase.tpp"
#endif

#endif
