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




#ifndef __MAP_Simple_TRANSFORMATION_INFO_TPP
#define __MAP_Simple_TRANSFORMATION_INFO_TPP

#include "mapSimpleTransformationInfo.h"
#include "mapOntologyExceptions.h"
namespace iro
{
  namespace scenario
  {


    SimpleTransformationInfo::ConstISPointer
      SimpleTransformationInfo::
      getMovingIS() const
    {
      return _movingIS;
    };

    void
      SimpleTransformationInfo::
      setMovingIS(ConstISPointer movingIS)
    {
      _movingIS = movingIS;
    };

    SimpleTransformationInfo::ConstISPointer
      SimpleTransformationInfo::
      getTargetIS() const
    {
      return _targetIS;
    };

    void
      SimpleTransformationInfo::
      setTargetIS(ConstISPointer targetIS)
    {
      _targetIS = targetIS;
    };

    bool
      SimpleTransformationInfo::
      doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const
    {
      return pProblemCompliance->checkComplianceOfStatement(this->_associatedProblem.get());
    };


    SimpleTransformationInfo::ConstProblemPointer
      SimpleTransformationInfo::
      getAssociatedProblemStatement() const
    {
      return _associatedProblem;
    };

    void
      SimpleTransformationInfo::
      setAssociatedProblemStatement(ConstProblemPointer problem)
    {
      _associatedProblem = problem;
    };

    SimpleTransformationInfo::DataRepresentationType
      SimpleTransformationInfo::
      getSupportedDataRepresentation() const
    {
      return _dataRepresentation;
    };

    void
      SimpleTransformationInfo::
      setSupportedDataRepresentation(DataRepresentationType dr)
    {
      _dataRepresentation = dr;
    };

    const SimpleTransformationInfo::UIDType&
      SimpleTransformationInfo::
      getUID() const
    {
      return _uid;
    };

    void
      SimpleTransformationInfo::
      setUID(const UIDType& uid)
    {
      _uid = uid;
    };


    SimpleTransformationInfo::FOVScopeType
      SimpleTransformationInfo::
      getFOVScope() const
    {
      return _scope;
    };

    void
      SimpleTransformationInfo::
      setFOVScope(FOVScopeType scope)
    {
      _scope = scope;
    };


    SimpleTransformationInfo::
      ~SimpleTransformationInfo()
    = default;


    SimpleTransformationInfo::
      SimpleTransformationInfo():  _uid("")
    {
    };

    SimpleTransformationInfo::ExecutionInfoType::ConstPointer
      SimpleTransformationInfo::
      getAlgorithmExecutionInfo() const
    {
      return _execInfo;
    };
      
    void
      SimpleTransformationInfo::
      setAlgorithmExecutionInfo(ExecutionInfoType::Pointer execInfo)
    {
      _execInfo = execInfo;
    };

    SimpleTransformationInfo::Pointer
      SimpleTransformationInfo::
      clone() const
    {
      Pointer spClone(new Self());

      spClone->_movingIS = _movingIS;
      spClone->_targetIS = _targetIS;
      spClone->_associatedProblem = _associatedProblem;
      spClone->_dataRepresentation = _dataRepresentation;
      spClone->_scope = _scope;
      spClone->_uid = _uid;
      spClone->_execInfo = _execInfo;

      return spClone;
    };

  } // end namespace scenario
} // end namespace iro

#endif
