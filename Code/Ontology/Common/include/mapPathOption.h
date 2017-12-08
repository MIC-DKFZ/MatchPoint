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




#ifndef __IRO_PATH_OPTION_H
#define __IRO_PATH_OPTION_H

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
      typedef IProblemComplianceChecker<typename TPathTraits::ProblemStatementTraitsType> Superclass;
      typedef ::std::shared_ptr<Self> Pointer;
      typedef ::std::shared_ptr<const Self> ConstPointer;

      typedef TPathTraits        PathTraitsType;
      typedef TPathCheckPolicy   PathCheckPolicy;

      typedef typename PathTraitsType::InformationEntityTraitsType::ConstPointer  ConstIEPointer;
      typedef typename PathTraitsType::InformationSpaceTraitsType::ConstPointer   ConstISPointer;
      typedef typename PathTraitsType::ConstPointer                           ConstPathPointer;
      typedef MappingError::Type                                     MappingErrorType;

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
      
      virtual ~PathOption();
			PathOption();

    protected:
      /*! Implementation of abstract member. This implementation checks the associated
      * problem statement of all elements for compliance. See also documentation in interface.
      * @see IProblemComplianceChecker*/
			virtual bool doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const;

      ConstIEPointer _movingEntity;
      ConstPathPointer _path;

    private:
			PathOption(const Self&); //not implemented by purpose
			Self& operator=(const Self&); //not implemented by purpose
		};
} // end namespace iro

#ifndef IRO_MANUAL_TPP
#include "mapPathOption.tpp"
#endif

#endif
