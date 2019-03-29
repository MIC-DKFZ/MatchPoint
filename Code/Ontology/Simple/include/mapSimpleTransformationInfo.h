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
      using Self = SimpleTransformationInfo;
      using Pointer = ::std::shared_ptr<Self>;
      using ConstPointer = ::std::shared_ptr<const Self>;

      using ConnectorInterface = IInformationSpaceConnector<SimpleInformationSpaceTraits>;
      using ConstISPointer = ConnectorInterface::ConstISPointer;

      using ProblemAssociatedInterface = IProblemStatementAssociated<SimpleProblemStatementTraits>;
      using ProblemComplianceInterface = ProblemAssociatedInterface::ProblemComplianceInterface;
      using ConstProblemPointer = ProblemAssociatedInterface::ConstProblemPointer;

      using DataRepresentationType = DataRepresentation::Type;
      using FOVScopeType = FOVScope::Type;
      using UIDType = ::iro::String;

      typedef AlgorithmExecutionInfo< SimpleInformationSpaceTraits, SimpleInformationEntityTraits > ExecutionInfoType;

      /*! Implementation of abstract member. See documentation in interface.
      * @see IInformationSpaceConnector*/
      ConstISPointer getMovingIS() const override;
      /*! Sets the moving information space */
      void setMovingIS(ConstISPointer movingIS);

      /*! Implementation of abstract member. See documentation in interface.
      * @see IInformationSpaceConnector*/
      ConstISPointer getTargetIS() const override;
      /*! Sets the target information space */
      void setTargetIS(ConstISPointer targetIS);

      /** Returns the const pointer to the associated problem statement.
      * Pointer may be null, if no statement is defined.*/
      ConstProblemPointer getAssociatedProblemStatement() const override;
      /*! Sets the associated problem statement */
      void setAssociatedProblemStatement(ConstProblemPointer problem);

      DataRepresentationType getSupportedDataRepresentation() const;
      void setSupportedDataRepresentation(DataRepresentationType dr);

      const UIDType& getUID() const;
      void setUID(const UIDType& uid);

      FOVScopeType getFOVScope() const;
      void setFOVScope(FOVScopeType scope);

      ~SimpleTransformationInfo() override;
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
      bool doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const override;

      ConstISPointer _movingIS;
      ConstISPointer _targetIS;
      ConstProblemPointer _associatedProblem;

      DataRepresentationType _dataRepresentation{::iro::DataRepresentation::Discrete};

      FOVScopeType _scope{::iro::FOVScope::Local};

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
