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




#ifndef __MAP_REGISTRATION_INFO_TPP
#define __MAP_REGISTRATION_INFO_TPP

#include "mapRegistrationInfo.h"
#include "mapOntologyExceptions.h"
#include "mapDataRepresentation.h"

namespace iro
{

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
  typename RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::ConstISPointer
    RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
    getMovingIS() const
  {
    return _movingIS;
  };

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
  typename RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::ConstISPointer
    RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
    getTargetIS() const
  {
    return _targetIS;
  };

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
  bool
    RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
    doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const
  {
    return pProblemCompliance->checkComplianceOfStatement(this->_associatedProblem.get());
  };

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
  typename RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::ConstProblemPointer
    RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
    getAssociatedProblemStatement() const
  {
    return _associatedProblem;
  };

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
  typename RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::ConstTransformationInfoPointer
    RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
    getContinuousTransformation() const
  {
    return _continuous;
  };

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
  typename RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::ConstTransformationInfoPointer
    RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
    getDiscreteTransformation() const
  {
    return _discrete;
  };

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
  void
    RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
    setTransformations(ConstTransformationInfoPointer continuous, ConstTransformationInfoPointer discrete)
  {
    ConstISPointer tempMovingIS;
    ConstISPointer tempTargetIS;
    ConstProblemPointer tempAssociatedProblem;

    //check the data representation type
    if ( continuous && continuous->getSupportedDataRepresentation()!=::iro::DataRepresentation::Continuous)
    {
      throw ::iro::exceptions::InvalidArgument("Passed continuous transform has no continuous data representation type.");
    }
    if ( discrete && discrete->getSupportedDataRepresentation()!=::iro::DataRepresentation::Discrete)
    {
      throw ::iro::exceptions::InvalidArgument("Passed continuous transform has no continuous data representation type.");
    }

    //check the problem statement preconditon
    if ( continuous && discrete)
    { //both are defined -> conflict is possible
      if ( continuous->getAssociatedProblemStatement()->getUID() != discrete->getAssociatedProblemStatement()->getUID())
      {
        throw ::iro::exceptions::InvalidArgument("Associated problem statement of transformation info instances is not equal.");
      }
      tempAssociatedProblem =  continuous->getAssociatedProblemStatement();
    }
    else
    { //only one is defined -> no conflict -> determin associated problem statement
      if (continuous) 
      {
        tempAssociatedProblem = continuous->getAssociatedProblemStatement();
      }
      else
      {
        tempAssociatedProblem = discrete->getAssociatedProblemStatement();
      }
    }

    //check the moving IS preconditon
    if ( continuous && discrete)
    { //both are defined -> conflict is possible
      if (continuous->getMovingIS()->getUID() != discrete->getMovingIS()->getUID())
      {
        throw ::iro::exceptions::InvalidArgument("Moving IS of transformation info instances is not equal.");
      }
      tempMovingIS = continuous->getMovingIS();
    }
    else
    { //only one is defined -> no conflict -> determin IS
      if (continuous) 
      {
        tempMovingIS = continuous->getMovingIS();
      }
      else
      {
        tempMovingIS = discrete->getMovingIS();
      }
    }

    //check the target IS preconditon
    if ( continuous && discrete)
    { //both are defined -> conflict is possible
      if (continuous->getTargetIS()->getUID() != discrete->getTargetIS()->getUID())
      {
        throw ::iro::exceptions::InvalidArgument("Target IS of transformation info instances is not equal.");
      }
      tempTargetIS = continuous->getTargetIS();
    }
    else
    { //only one is defined -> no conflict -> determin IS
      if (continuous) 
      {
        tempTargetIS = continuous->getTargetIS();
      }
      else
      {
        tempTargetIS = discrete->getTargetIS();
      }
    }

    _movingIS = tempMovingIS;
    _targetIS = tempTargetIS;
    _associatedProblem = tempAssociatedProblem;
    _continuous = continuous;
    _discrete = discrete;
  };

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
    typename RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::Pointer
      RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
      clone() const
    {
      Pointer spClone(new Self());

      spClone->_movingIS = _movingIS;
      spClone->_targetIS = _targetIS;
      spClone->_associatedProblem = _associatedProblem;
      spClone->_continuous = _continuous;
      spClone->_discrete = _discrete;

      return spClone;
    };

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
  RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
    ~RegistrationInfo()
  {
  };

  template <typename TInformationSpaceTraits, typename TProblemStatementTraits, typename TTransformationInfoTraits>
  RegistrationInfo<TInformationSpaceTraits, TProblemStatementTraits, TTransformationInfoTraits>::
    RegistrationInfo()
  {
  };

} // end namespace iro

#endif
