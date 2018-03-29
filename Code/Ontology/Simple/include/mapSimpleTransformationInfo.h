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




#ifndef __MAP_SIMPLE_TRANSFORMATION_INFO_H
#define __MAP_SIMPLE_TRANSFORMATION_INFO_H

#include "mapIInformationSpaceConnector.h"
#include "mapIProblemStatementAssociated.h"
#include "mapSimpleInformationSpace.h"
#include "mapSimpleInformationEntity.h"
#include "mapSimpleProblemStatement.h"
#include "mapDataRepresentation.h"
#include "mapFOVScope.h"
#include "mapAlgorithmExecutionInfo.h"
#include "mapTransformationInfoTraits.h"

#include <memory>

#include "mapMAPOntologySimpleExports.h"


namespace iro
{
  namespace scenario
  {

    /*! @class SimpleTransformationInfo
    * @brief Simple specific implementation for transformation infos.
    * @ingroup Simple
    */
    class MAPOntologySimple_EXPORT SimpleTransformationInfo : public IInformationSpaceConnector< SimpleInformationSpaceTraits >, public IProblemStatementAssociated< SimpleProblemStatementTraits >
    {
    public:
      typedef SimpleTransformationInfo Self;
      typedef ::std::shared_ptr<Self> Pointer;
      typedef ::std::shared_ptr<const Self> ConstPointer;

      typedef IInformationSpaceConnector< SimpleInformationSpaceTraits >	ConnectorInterface;
      typedef ConnectorInterface::ConstISPointer  ConstISPointer;

      typedef IProblemStatementAssociated< SimpleProblemStatementTraits >	ProblemAssociatedInterface;
      typedef ProblemAssociatedInterface::ProblemComplianceInterface  ProblemComplianceInterface;
      typedef ProblemAssociatedInterface::ConstProblemPointer         ConstProblemPointer;

      typedef DataRepresentation::Type          DataRepresentationType;
      typedef FOVScope::Type                    FOVScopeType;
      typedef ::iro::String                     UIDType;

      typedef AlgorithmExecutionInfo< SimpleInformationSpaceTraits, SimpleInformationEntityTraits > ExecutionInfoType;

      /*! Implementation of abstract member. See documentation in interface.
      * @see IInformationSpaceConnector*/
      virtual ConstISPointer getMovingIS() const;
      /*! Sets the moving information space */
      void setMovingIS(ConstISPointer movingIS);

      /*! Implementation of abstract member. See documentation in interface.
      * @see IInformationSpaceConnector*/
      virtual ConstISPointer getTargetIS() const;
      /*! Sets the target information space */
      void setTargetIS(ConstISPointer targetIS);

      /** Returns the const pointer to the associated problem statement.
      * Pointer may be null, if no statement is defined.*/
      virtual ConstProblemPointer getAssociatedProblemStatement() const override;
      /*! Sets the associated problem statement */
      void setAssociatedProblemStatement(ConstProblemPointer problem);

      DataRepresentationType getSupportedDataRepresentation() const;
      void setSupportedDataRepresentation(DataRepresentationType dr);

      const UIDType& getUID() const;
      void setUID(const UIDType& uid);

      FOVScopeType getFOVScope() const;
      void setFOVScope(FOVScopeType scope);

      virtual ~SimpleTransformationInfo();
      SimpleTransformationInfo();

      ExecutionInfoType::ConstPointer getAlgorithmExecutionInfo() const;
      void setAlgorithmExecutionInfo(ExecutionInfoType::Pointer execInfo);

      /* Clones the content of the info and returns it as
      * non const pointer. It can be used to alter the transformation info and
      * update the knowledge base of the ontology.
      */
      Pointer clone() const;

    protected:
      /*! Implementation of abstract member. This implementation checks the associated
      * problem statement for compliance. See also documentation in interface.
      * @see IProblemComplianceChecker*/
			virtual bool doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const;

      ConstISPointer _movingIS;
      ConstISPointer _targetIS;
      ConstProblemPointer _associatedProblem;

      DataRepresentationType _dataRepresentation;

      FOVScopeType _scope;

      UIDType _uid;

      ExecutionInfoType::Pointer _execInfo;

    private:
      SimpleTransformationInfo(const Self&); //not implemented by purpose
      Self& operator=(const Self&); //not implemented by purpose
    };

    using SimpleTransformationInfoTraits = TransformationInfoTraits<SimpleTransformationInfo, SimpleInformationEntityTraits, SimpleInformationSpaceTraits, SimpleProblemStatementTraits>;

  } // end namespace scenario

} // end namespace iro

#endif
