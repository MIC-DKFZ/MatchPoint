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




#ifndef __MAP_PATH_OPTION_H
#define __MAP_PATH_OPTION_H

#include "mapOntologyString.h"
#include "mapMappingError.h"
#include "mapOntologyExceptions.h"
#include "mapIProblemComplianceChecker.h"
#include <memory>

namespace iro
{

		/*! @class PathOption
    * @brief Template class that is used for path options.
    *
    * A path option correlates a certain entity with a mapping path and can
    * be used to quickly access the validity check for the path
    * regarding the moving entity. 
    * 
    */
    template <typename TPathTraits, typename TPathCheckPolicy>
    class PathOption: public IProblemComplianceChecker<typename TPathTraits::ProblemStatementTraitsType>
		{
    public:
      typedef PathOption<TPathTraits, TPathCheckPolicy> Self;
      using Superclass = IProblemComplianceChecker<typename TPathTraits::ProblemStatementTraitsType>;
      using Pointer = ::std::shared_ptr<Self>;
      using ConstPointer = ::std::shared_ptr<const Self>;

      using PathTraitsType = TPathTraits;
      using PathCheckPolicy = TPathCheckPolicy;

      using ConstIEPointer = typename PathTraitsType::InformationEntityTraitsType::ConstPointer;
      using ConstISPointer = typename PathTraitsType::InformationSpaceTraitsType::ConstPointer;
      using ConstPathPointer = typename PathTraitsType::ConstPointer;
      using MappingErrorType = MappingError::Type;

      using ProblemComplianceInterface = typename Superclass::ProblemComplianceInterface;

      /*! Returns the entity this path option was compiled for.*/
      ConstIEPointer getMovingEntity() const;
      /*! Sets the moving entity of this path option.
       * @pre If a path is set it must support the entity according to the PathCheckPolicy
       * of this option.
       * @exception InvalidDataRepresentation: precondition is violated*/
      void setMovingEntity(ConstIEPointer movingEntity);

      /*! Returns the pointer to the path of this option.*/
      ConstPathPointer getPath() const;
      /*! Sets the path of this option.
       * @pre If a entity is set it must have a data representation supported by the new path
       * according to the PathCheckPolicy of this option.
       * @exception InvalidDataRepresentation: precondition is violated*/
      void setPath(ConstPathPointer path);

      /*! Returns the target information space of the path. If no path is set it returns a NULL pointer.*/
      ConstISPointer getTargetIS() const;

      /*! Checks if the path is able to map the moving entity or if there are any
      * possible reasons for a mapping failure.
      * @pre path and moving entity must be defined
      * @exception InvalidArgument: precondition is violated*/
      MappingErrorType checkForFailureReason() const;

      /*! Checks if the mapping of the moving entity is guaranteed by the path
      * it is the same like checkForFailureReason()==MappinError::NoFailure.
      * @pre path and moving entity must be defined
      * @exception InvalidArgument: precondition is violated*/
      bool hasFullMappingGuarantee() const;
      
      ~PathOption() override;
			PathOption();

    protected:
      /*! Implementation of abstract member. This implementation checks the associated
      * problem statement of all elements for compliance. See also documentation in interface.
      * @see IProblemComplianceChecker*/
			bool doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const override;

      ConstIEPointer _movingEntity;
      ConstPathPointer _path;

    private:
			PathOption(const Self&); //not implemented by purpose
			Self& operator=(const Self&); //not implemented by purpose
		};
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapPathOption.tpp"
#endif

#endif
