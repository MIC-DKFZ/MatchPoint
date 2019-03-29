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




#ifndef __MAP_REGISTRATON_PATH_BASE_H
#define __MAP_REGISTRATON_PATH_BASE_H

#include "mapISConnectorPathBase.h"

namespace iro
{

		/*! @class RegistrationPathBase
    * @brief Base class for all registration paths.
    *
    * A Registration path defines a sequence of registrations that lead from
    * the moving information space of the path to the target information space.
    * Because the ontology supports the fact that an entity may be mapped by
    * using interim registration spaces (Moving IS -> Interim IS -> Target IS)
    * all evaluations of "mappablility" result in paths and not plain
    * RegistrationInfo. Although most of the paths should be of size 1,
    * because long paths will introduce more error risks.\n
    * A RegistrationPath may "contain" up to two TransformationPaths,
    * one for each data representation type.
    */
    template <typename TRegistrationInfoTraits, typename TTransformationPathTraits>
    class RegistrationPathBase : public ISConnectorPathBase< TRegistrationInfoTraits, typename TTransformationPathTraits::InformationSpaceTraitsType, typename TTransformationPathTraits::ProblemStatementTraitsType >
		{
    public:
      typedef RegistrationPathBase<TRegistrationInfoTraits, TTransformationPathTraits> Self;
      typedef ISConnectorPathBase<TRegistrationInfoTraits, typename TTransformationPathTraits::InformationSpaceTraitsType, typename TTransformationPathTraits::ProblemStatementTraitsType> Superclass;
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

      using ConstTransformationPathPointer = typename TTransformationPathTraits::ConstPointer;
      using TransformationPathPointer = typename TTransformationPathTraits::Pointer;
      using TransformationPathType = typename TTransformationPathTraits::Type;

      /*! Returns the transformation path formed by the continuous transformations stored in each path element.
       * @remark If not every element of the path has a continuous transformation the transformation path cannot
       * be established and a null pointer will be returned, indicating that for this data representation type there
       * is no valid pathway.*/
      ConstTransformationPathPointer getContinuousTransformationPath() const;
      /*! Returns the transformation path formed by the discrete transformations stored in each path element.
       * @remark If not every element of the path has a discrete transformation the transformation path cannot
       * be established and a null pointer will be returned, indicating that for this data representation type there
       * is no valid pathway.*/
      ConstTransformationPathPointer getDiscreteTransformationPath() const;

			~RegistrationPathBase() override;
			RegistrationPathBase();

    private:
			RegistrationPathBase(const Self&); //not implemented by purpose
			Self& operator=(const Self&); //not implemented by purpose
		};
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapRegistrationPathBase.tpp"
#endif

#endif
