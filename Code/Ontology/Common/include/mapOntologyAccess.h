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





#ifndef __MAP_ONTOLOGY_ACCESS_H
#define __MAP_ONTOLOGY_ACCESS_H

#include "mapIEntityInference.h"
#include "mapIMappingInference.h"
#include "mapIProblemInference.h"
#include "mapIEntityIntegration.h"
#include "mapIProblemIntegration.h"
#include "mapIMappingIntegration.h"

namespace iro
{
  namespace core
  {
    /**
    *@tparam TRPTraits type that define the traits of registration paths.
      * @tparam TRPOCTraits type that define the traits of registration path option collections.
      * @tparam TTPOCTraits type that define the traits of transformation path option collections.
      * @tparam TSCTraits type that define the traits of semantic correlations.
      * @tparam TPMTraits type that represents the problem model traits.
      * @tparam TEDReturnType type that is returned by entity delete operations.
      * @tparam TISDReturnType type that is returned by information space delete operations.
      * @tparam TCDReturnType type that is returned by correlation delete operations.
      * @tparam TPSDReturnType type that is returned by problem statement delete operations.
      * @tparam TPMDReturnType type that is returned by problem model delete operations.
      * @tparam TTDReturnType type that is returned by transformation / registration delete operations.
      */
    template <typename TRPTraits, typename TRPOCTraits, typename TTPOCTraits,
      typename TSCTraits, typename TPMTraits, typename TEDReturnType = bool,
      typename TISDReturnType = bool, typename TCDReturnType = bool,
      typename TPSDReturnType = bool, typename TPMDReturnType = bool,
      typename TTDReturnType = bool>
    struct OntologyAccessTraits
    {
      using SemanticCorrelationTraitsType = TSCTraits;
      using ProblemModelTraitsType = TPMTraits;
      using ProblemStatementTraitsType = typename TPMTraits::ProblemStatementTraitsType;

      using InformationEntityTraitsType = typename TRPTraits::InformationEntityTraitsType;
      using InformationSpaceTraitsType = typename TRPTraits::InformationSpaceTraitsType;

      using TransformationInfoTraitsType = typename TRPTraits::TransformationInfoTraitsType;
      using TransformationPathTraitsType = typename TRPTraits::TransformationPathTraitsType;
      using TransPathOptionCollectionTraitsType = TTPOCTraits;
      using TransPathOptionTraitsType = typename TTPOCTraits::OptionTraitsType;

      using RegistrationInfoTraitsType = typename TRPTraits::RegistrationInfoTraitsType;
      using RegistrationPathTraitsType = TRPTraits;
      using RegPathOptionCollectionTraitsType = TRPOCTraits;
      using RegPathOptionTraitsType = typename TRPOCTraits::OptionTraitsType;

      using EDReturnType = TEDReturnType;
      using ISDReturnType = TISDReturnType;
      using CDReturnType = TCDReturnType;
      using PSDReturnType = TPSDReturnType;
      using PMDReturnType = TPMDReturnType;
      using TDReturnType = TTDReturnType;
    };

    /*! @class OntologyAccess
    * Base class for classes that implement a complete ontology with all interfaces.

    * @tparam TRPTraits type that define the traits of registration paths.
    * @tparam TRPOCTraits type that define the traits of registration path option collections.
    * @tparam TTPOCTraits type that define the traits of transformation path option collections.
    * @tparam TSCTraits type that define the traits of semantic correlations.
    * @tparam TPMTraits type that represents the problem model traits.
    * @tparam TEDReturnType type that is returned by entity delete operations.
    * @tparam TISDReturnType type that is returned by information space delete operations.
    * @tparam TCDReturnType type that is returned by correlation delete operations.
    * @tparam TPSDReturnType type that is returned by problem statement delete operations.
    * @tparam TPMDReturnType type that is returned by problem model delete operations.
    * @tparam TTDReturnType type that is returned by transformation/registration delete operations.
    */
    template <typename TOATraits>
    class OntologyAccess : public IEntityInference<typename TOATraits::InformationEntityTraitsType, typename TOATraits::InformationSpaceTraitsType, typename TOATraits::SemanticCorrelationTraitsType>,
      public IProblemInference<typename TOATraits::ProblemModelTraitsType>,
      public IMappingInference<typename TOATraits::RegistrationPathTraitsType, typename TOATraits::RegPathOptionCollectionTraitsType, typename TOATraits::TransPathOptionCollectionTraitsType, IEntityInference<typename TOATraits::InformationEntityTraitsType, typename TOATraits::InformationSpaceTraitsType, typename TOATraits::SemanticCorrelationTraitsType> >,
      public IEntityIntegration<typename TOATraits::InformationEntityTraitsType, typename TOATraits::InformationSpaceTraitsType, typename TOATraits::SemanticCorrelationTraitsType, IEntityInference<typename TOATraits::InformationEntityTraitsType, typename TOATraits::InformationSpaceTraitsType, typename TOATraits::SemanticCorrelationTraitsType>, typename TOATraits::EDReturnType, typename TOATraits::ISDReturnType, typename TOATraits::CDReturnType>,
      public IProblemIntegration<typename TOATraits::ProblemModelTraitsType, IProblemInference<typename TOATraits::ProblemModelTraitsType>, typename TOATraits::PSDReturnType, typename TOATraits::PMDReturnType>,
      public IMappingIntegration<typename TOATraits::TransformationInfoTraitsType, IEntityInference<typename TOATraits::InformationEntityTraitsType, typename TOATraits::InformationSpaceTraitsType, typename TOATraits::SemanticCorrelationTraitsType>, IProblemInference<typename TOATraits::ProblemModelTraitsType>, typename TOATraits::TDReturnType>
    {
    public:

      using EntityInferenceInterface = IEntityInference<typename TOATraits::InformationEntityTraitsType, typename TOATraits::InformationSpaceTraitsType, typename TOATraits::SemanticCorrelationTraitsType>;
      using MappingInferenceInterface = IMappingInference<typename TOATraits::RegistrationPathTraitsType, typename TOATraits::RegPathOptionCollectionTraitsType, typename TOATraits::TransPathOptionCollectionTraitsType, EntityInferenceInterface >;
      using ProblemInferenceInterface = IProblemInference<typename TOATraits::ProblemModelTraitsType>;
      using EntityIntegrationInterface = IEntityIntegration<typename TOATraits::InformationEntityTraitsType, typename TOATraits::InformationSpaceTraitsType, typename TOATraits::SemanticCorrelationTraitsType, EntityInferenceInterface, typename TOATraits::EDReturnType, typename TOATraits::ISDReturnType, typename TOATraits::CDReturnType>;
      using MappingIntegrationInterface = IMappingIntegration<typename TOATraits::TransformationInfoTraitsType, EntityInferenceInterface, ProblemInferenceInterface, typename TOATraits::TDReturnType>;
      using ProblemIntegrationInterface = IProblemIntegration<typename TOATraits::ProblemModelTraitsType, ProblemInferenceInterface, typename TOATraits::PSDReturnType, typename TOATraits::PMDReturnType>;

      using EntityInferenceInterface::actualize;
      using ProblemInferenceInterface::actualize;
      using MappingInferenceInterface::actualize;

    protected:
      virtual ~OntologyAccess();
      OntologyAccess();

    private:
      OntologyAccess(const OntologyAccess&); //not implemented by purpose
      OntologyAccess& operator=(const OntologyAccess&); //not implemented by purpose
    };
  } // end namespace core
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapOntologyAccess.tpp"
#endif

#endif
