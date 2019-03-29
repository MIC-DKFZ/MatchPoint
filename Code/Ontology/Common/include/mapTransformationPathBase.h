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




#ifndef __MAP_TRANSFORMATION_PATH_BASE_H
#define __MAP_TRANSFORMATION_PATH_BASE_H

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
      using Pointer = ::std::shared_ptr<Self>;
      using ConstPointer = ::std::shared_ptr<const Self>;

      using ConstISPointer = typename Superclass::ConstISPointer;

      using ProblemComplianceInterface = typename Superclass::ConstISPointer;

      using ProblemStatementType = typename Superclass::ProblemStatementType;
      using ProblemPointer = typename Superclass::ProblemPointer;
      using ConstProblemPointer = typename Superclass::ConstProblemPointer;

      using ConstPathElementPointer = typename Superclass::ConstPathElementPointer;

      using PathElementIterator = typename Superclass::PathElementIterator;
      using ConstPathElementIterator = typename Superclass::ConstPathElementIterator;
      using PathSizeType = typename Superclass::PathSizeType;

			~TransformationPathBase() override;
			TransformationPathBase();
    protected:
      /*! In addition to the base implementation it also checks if the elment has the same data support.
       * @pre The data representation support of the new element must equal the support of the path elements.
       * @param [in] pos Iterator indicating the postion of the element where the element should be inserted.
       * @param [in] newElement The new element that should be inserted.
       * @return Iterator that points to the position of the inserted element in the path.
       * @exception ::iro::exceptions::InvalidDataRepresentation: the precondition is violated*/
      PathElementIterator doInsertElement(PathElementIterator pos, ConstPathElementPointer newElement) override;

      /*! Adds the passed newElement at the end of the path.
       * @pre The moving IS of the new element must equal the target IS of the preceeding element (if the path is not empty)
       * @param [in] newElement The new element that should be inserted.
       * @exception ::iro::exceptions::InvalidDataRepresentation: the preconditions is violated*/
      void doAppend(ConstPathElementPointer newElement) override;

    private:
			TransformationPathBase(const Self&) = delete; //not implemented by purpose
			Self& operator=(const Self&) = delete; //not implemented by purpose
		};
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapTransformationPathBase.tpp"
#endif

#endif
