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





#ifndef __MAP_I_MAPPING_INFERENCE_TPP
#define __MAP_I_MAPPING_INFERENCE_TPP

#include <assert.h>
#include "mapIMappingInference.h"

namespace iro
{
  namespace core
  {

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstRegPathOptColPointer>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    getRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    {
      assert(_pEntityInferenceInterface);

      if (!pMovingIS)
      {
        throw exceptions::InvalidArgument("Cannot get registration paths. Passed moving IS pointer is NULL.");
      }
      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot get registration paths. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentMIS = _pEntityInferenceInterface->actualize(pMovingIS);

      if (!spCurrentMIS)
      {
        throw exceptions::UndefinedElement("Cannot get registration paths. Passed moving IS is not defined in the ontology.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot get registration paths. Passed fixed IS is not defined in the ontology.");
      }

      return doGetRegistrationPaths(spCurrentMIS, spCurrentFIS, pProblemCompliance);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstRegPathOptColVectorType>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    getRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    {
      assert(_pEntityInferenceInterface);

      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot get registration paths. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot get registration paths. Passed fixed IS is not defined in the ontology.");
      }

      //check validity of moving entities
      ConstInfEntityVectorType currentEntities = actualizeVector(movingEntities);

      return doGetRegistrationPaths(currentEntities, spCurrentFIS, pProblemCompliance);
    };
    
    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstTransPathOptColPointer>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    getTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    {
      assert(_pEntityInferenceInterface);

      if (!pMovingIS)
      {
        throw exceptions::InvalidArgument("Cannot get transformation paths. Passed moving IS pointer is NULL.");
      }
      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot get transformation paths. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentMIS = _pEntityInferenceInterface->actualize(pMovingIS);

      if (!spCurrentMIS)
      {
        throw exceptions::UndefinedElement("Cannot get transformation paths. Passed moving IS is not defined in the ontology.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot get transformation paths. Passed fixed IS is not defined in the ontology.");
      }

      return doGetTransformationPaths(spCurrentMIS, spCurrentFIS, pProblemCompliance);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstTransPathOptColVectorType>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    getTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    {
      assert(_pEntityInferenceInterface);

      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot get transformation paths. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot get transformation paths. Passed fixed IS is not defined in the ontology.");
      }

      //check validity of moving entities
      ConstInfEntityVectorType currentEntities = actualizeVector(movingEntities);

      return doGetTransformationPaths(currentEntities, spCurrentFIS, pProblemCompliance);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstRegPathOptColPointer>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    getOptimalRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance, const RegPathMetricInterface* pMetric) const
    {
      assert(_pEntityInferenceInterface);

      if (!pMovingIS)
      {
        throw exceptions::InvalidArgument("Cannot get optimal registration paths. Passed moving IS pointer is NULL.");
      }
      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot get optimal registration paths. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentMIS = _pEntityInferenceInterface->actualize(pMovingIS);

      if (!spCurrentMIS)
      {
        throw exceptions::UndefinedElement("Cannot get optimal registration paths. Passed moving IS is not defined in the ontology.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot get optimal registration paths. Passed fixed IS is not defined in the ontology.");
      }

      return doGetOptimalRegistrationPaths(spCurrentMIS, spCurrentFIS, requiredDataSupport, pProblemCompliance, pMetric);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstRegPathOptColVectorType>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    getOptimalRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance, const RegPathMetricInterface* pMetric) const
    {
      assert(_pEntityInferenceInterface);

      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot get optimal registration paths. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot get optimal registration paths. Passed fixed IS is not defined in the ontology.");
      }

      //check validity of moving entities
      ConstInfEntityVectorType currentEntities = actualizeVector(movingEntities);

      return doGetOptimalRegistrationPaths(currentEntities, spCurrentFIS, pProblemCompliance, pMetric);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstTransPathOptColPointer>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    getOptimalTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance, const TransPathMetricInterface* pMetric) const
    {
      assert(_pEntityInferenceInterface);

      if (!pMovingIS)
      {
        throw exceptions::InvalidArgument("Cannot get optimal transformation paths. Passed moving IS pointer is NULL.");
      }
      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot get optimal transformation paths. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentMIS = _pEntityInferenceInterface->actualize(pMovingIS);

      if (!spCurrentMIS)
      {
        throw exceptions::UndefinedElement("Cannot get optimal transformation paths. Passed moving IS is not defined in the ontology.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot get optimal transformation paths. Passed fixed IS is not defined in the ontology.");
      }

      return doGetOptimalTransformationPaths(spCurrentMIS, spCurrentFIS, pProblemCompliance, pMetric);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstTransPathOptColVectorType>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    getOptimalTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance, const TransPathMetricInterface* pMetric) const
    {
      assert(_pEntityInferenceInterface);

      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot get optimal transformation paths. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot get optimal transformation paths. Passed fixed IS is not defined in the ontology.");
      }

      //check validity of moving entities
      ConstInfEntityVectorType currentEntities = actualizeVector(movingEntities);

      return doGetOptimalTransformationPaths(currentEntities, spCurrentFIS, pProblemCompliance, pMetric);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstInfSpaceVectorType>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    getMappableInformationSpaces(InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance, const RegPathMetricInterface* pMetric) const
    {
      assert(_pEntityInferenceInterface);

      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot get optimal registration paths. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot get optimal registration paths. Passed fixed IS is not defined in the ontology.");
      }

      return doGetMappableInformationSpaces(spCurrentFIS, requiredDataSupport, pProblemCompliance, pMetric);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::MappingErrorType>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    checkForMappingFailureReason(InfEntityInferencePointer pMovingEntity, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    {
      assert(_pEntityInferenceInterface);

      if (!pMovingEntity)
      {
        throw exceptions::InvalidArgument("Cannot check failure resaons. Passed moving entity pointer is NULL.");
      }
      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot check failure resaons. Passed fixed IS pointer is NULL.");
      }

      typename InfEntityType::ConstPointer spCurrentEntity = _pEntityInferenceInterface->actualize(pMovingEntity);

      if (!spCurrentEntity)
      {
        throw exceptions::UndefinedElement("Cannot check failure resaons. Passed moving IS is not defined in the ontology.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot check failure resaons. Passed fixed IS is not defined in the ontology.");
      }

      return doCheckForMappingFailureReason(spCurrentEntity, spCurrentFIS, pProblemCompliance);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::MappingErrorType>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    checkForMappingFailureReason(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance) const
    {
      assert(_pEntityInferenceInterface);

      if (!pMovingIS)
      {
        throw exceptions::InvalidArgument("Cannot check failure resaons. Passed moving IS pointer is NULL.");
      }
      if (!pFixedIS)
      {
        throw exceptions::InvalidArgument("Cannot check failure resaons. Passed fixed IS pointer is NULL.");
      }

      typename InfSpaceType::ConstPointer spCurrentMIS = _pEntityInferenceInterface->actualize(pMovingIS);

      if (!spCurrentMIS)
      {
        throw exceptions::UndefinedElement("Cannot check failure resaons. Passed moving IS is not defined in the ontology.");
      }

      typename InfSpaceType::ConstPointer spCurrentFIS = _pEntityInferenceInterface->actualize(pFixedIS);

      if (!spCurrentFIS)
      {
        throw exceptions::UndefinedElement("Cannot check failure resaons. Passed fixed IS is not defined in the ontology.");
      }

      return doCheckForMappingFailureReason(spCurrentMIS, spCurrentFIS, requiredDataSupport, pProblemCompliance);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::MappingErrorType>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    checkForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstRegistrationPathPointer pPath) const
    {
      assert(_pEntityInferenceInterface);

      if (!pMovingEntity)
      {
        throw exceptions::InvalidArgument("Cannot check failure resaons. Passed moving entity pointer is NULL.");
      }
      if (!pPath)
      {
        throw exceptions::InvalidArgument("Cannot check failure resaons. Passed path pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentMIE = _pEntityInferenceInterface->actualize(pMovingEntity);

      if (!spCurrentMIE)
      {
        throw exceptions::UndefinedElement("Cannot check for failure reason. Passed moving entitiy is not defined in the ontology.");
      }

      ConstInfSpacePointer spCurrentMIS = pPath->getMovingIS();

      if (!spCurrentMIS)
      {
        throw exceptions::UndefinedElement("Cannot check for failure reason. Moving space of passed path is not defined in the ontology.");
      }

      ConstInfSpacePointer spCurrentTIS = pPath->getTargetIS();

      if (!spCurrentTIS)
      {
        throw exceptions::UndefinedElement("Cannot check for failure reason. Target space of passed path is not defined in the ontology.");
      }

      return doCheckForMappingFailureReason(spCurrentMIE, pPath);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::MappingErrorType>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    checkForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstTransformationPathPointer pPath) const
    {
      assert(_pEntityInferenceInterface);

      if (!pMovingEntity)
      {
        throw exceptions::InvalidArgument("Cannot check failure resaons. Passed moving entity pointer is NULL.");
      }
      if (!pPath)
      {
        throw exceptions::InvalidArgument("Cannot check failure resaons. Passed path pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentMIE = _pEntityInferenceInterface->actualize(pMovingEntity);
      if (!spCurrentMIE)
      {
        throw exceptions::UndefinedElement("Cannot check for failure reason. Passed moving entitiy is not defined in the ontology.");
      }

      ConstInfSpacePointer spCurrentMIS = _pEntityInferenceInterface->actualize(pPath->getMovingIS());
      if (!spCurrentMIS)
      {
        throw exceptions::UndefinedElement("Cannot check for failure reason. Moving space of passed path is not defined in the ontology.");
      }

      ConstInfSpacePointer spCurrentTIS = _pEntityInferenceInterface->actualize(pPath->getTargetIS());
      if (!spCurrentTIS)
      {
        throw exceptions::UndefinedElement("Cannot check for failure reason. Target space of passed path is not defined in the ontology.");
      }

      return doCheckForMappingFailureReason(spCurrentMIE, pPath);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstRegistrationPathPointer>
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    convertTransformationToRegistrationPath(ConstTransformationPathPointer pPath) const
    {
      if (!pPath)
      {
        throw exceptions::InvalidArgument("Cannot convert path resaons. Passed path pointer is NULL.");
      }

      ConstInfSpacePointer spCurrentMIS = _pEntityInferenceInterface->actualize(pPath->getMovingIS());
      if (!spCurrentMIS)
      {
        throw exceptions::UndefinedElement("Cannot check for failure reason. Moving space of passed path is not defined in the ontology.");
      }

      ConstInfSpacePointer spCurrentTIS = _pEntityInferenceInterface->actualize(pPath->getTargetIS());
      if (!spCurrentTIS)
      {
        throw exceptions::UndefinedElement("Cannot check for failure reason. Target space of passed path is not defined in the ontology.");
      }

      return doConvertTransformationToRegistrationPath(pPath);
    };


		template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    Result<typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstTransformationInfoPointer>
      IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
      actualize(TransformationInfoInferencePointer pTI) const
    {
      if (!pTI)
      {
        throw exceptions::InvalidArgument("Cannot actualize transformation info. Passed entity pointer is NULL.");
      }

      return doActualize(pTI);
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    typename IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::ConstInfEntityVectorType
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    actualizeVector(const ConstInfEntityVectorType& oldV) const
    {
      assert(_pEntityInferenceInterface);

      ConstInfEntityVectorType newEntities;

      for (typename ConstInfEntityVectorType::const_iterator pos = oldV.begin(); pos!=oldV.end(); ++pos)
      {
        if (!(*pos))
        {
          throw exceptions::InvalidArgument("Cannot actualize entity vector. At least one entity pointer is NULL.");
        }
        ConstInfEntityPointer spCurrentIE = _pEntityInferenceInterface->actualize(*pos);

        if (!spCurrentIE)
        {
          throw exceptions::UndefinedElement("Cannot actualize entity vector. At least one moving entitiy is not defined in the ontology.");
        }
        newEntities.push_back(spCurrentIE);
      }

      return newEntities;
    };

    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits, typename TIEInference>
    void
    IMappingInference<TRPTraits, TRPOCTraits, TTPOCTraits, TIEInference>::
    setEntityInferenceInterface(const EntityInferenceInterface* pInterface)
    {
      _pEntityInferenceInterface = pInterface;
    };


  } // end namespace core
} // end namespace iro

#endif
