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


#include "mapSimpleOntology.h"
#include "mapSimpleOntologyCore.h"
#include "mapSimpleTestHelper.h"
#include "mapOntologyExceptions.h"

#include "litCheckMacros.h"

#include <stdlib.h>

namespace iro
{
  namespace testing
  {
    class SimpleTestOntology : public ::iro::scenario::SimpleOntology
    {
    public:
      OntologyCoreType& getCore() { return *(_spCore.get());}
    };

    int mapSimpleOntologyTest(int, char* [] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      SimpleTestOntology ontology;
      int revCheck = 0;

      /////////////////////////////////////////////////////////////////////////
      // establish test elements
      /////////////////////////////////////////////////////////////////////////
      OntologyTestFixture fixture;

      /////////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////
      // test entity inference / integration
      /////////////////////////////////////////////////////////////////////////

      /////////////////////////////////////////////////////////////////////////
      // information spaces

      //test invalid usage of IS integration
      CHECK_THROW_EXPLICIT(ontology.defineInformationSpace(fixture.spISNull),::iro::exceptions::InvalidArgument);

      //test correct define
      Result<SimpleTestOntology::ConstInfSpacePointer> resultIS = ontology.defineInformationSpace(fixture.spIS1);
      CHECK(resultIS.getRevision() == ++revCheck);
      CHECK(resultIS->getUID() == fixture.spIS1->getUID());
      ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::ISMapType::iterator posIS = ontology.getCore()._ISMap.find(fixture.spIS1->getUID());
      CHECK(posIS != ontology.getCore()._ISMap.end()); //is in list
      CHECK(posIS->second == resultIS.getValue()); //is right element

      //test re define ->must stay silent and unchanged
      CHECK_NO_THROW(resultIS = ontology.defineInformationSpace(fixture.spIS1));
      CHECK(resultIS.getRevision() == revCheck);
      CHECK(resultIS->getUID() == fixture.spIS1->getUID());
      CHECK(1 == ontology.getCore()._ISMap.size());

      //test invalid usage of IS store
      CHECK_THROW_EXPLICIT(ontology.storeInformationSpace(fixture.spISNull),::iro::exceptions::InvalidArgument);

      //test correct store
      resultIS = ontology.storeInformationSpace(fixture.spIS1);
      CHECK(resultIS.getRevision() == revCheck); // it stays untouched in this implementation.
      CHECK(resultIS->getUID() == fixture.spIS1->getUID());
      posIS = ontology.getCore()._ISMap.find(fixture.spIS1->getUID());
      CHECK(posIS != ontology.getCore()._ISMap.end()); //is in list
      CHECK(posIS->second == resultIS.getValue()); //is right element
      CHECK(1 == ontology.getCore()._ISMap.size()); //is in list

      //test store of unkown IS ->must do a silent define
      resultIS = ontology.storeInformationSpace(fixture.spIS2);
      CHECK(resultIS.getRevision() == ++revCheck);
      CHECK(resultIS->getUID() == fixture.spIS2->getUID());
      posIS = ontology.getCore()._ISMap.find(fixture.spIS2->getUID());
      CHECK(posIS != ontology.getCore()._ISMap.end()); //is in list
      CHECK(posIS->second == resultIS.getValue()); //is right element
      CHECK(2 == ontology.getCore()._ISMap.size()); //is in list

      resultIS = ontology.defineInformationSpace(fixture.spIS3);
      revCheck++;

      //test invalid usage of IS delete
      CHECK_THROW_EXPLICIT(ontology.deleteInformationSpace(fixture.spISNull),::iro::exceptions::InvalidArgument);

      //test correct delete
      CHECK(ontology.deleteInformationSpace(fixture.spIS1));
      CHECK(2 == ontology.getCore()._ISMap.size());
      posIS = ontology.getCore()._ISMap.find(fixture.spIS1->getUID());
      CHECK(posIS == ontology.getCore()._ISMap.end()); //is not in list
      CHECK(++revCheck == ontology.getCore()._revision); //is in list

      //test delete unkown element -> keep silent
      CHECK(ontology.deleteInformationSpace(fixture.spIS1));
      CHECK(2 == ontology.getCore()._ISMap.size());
      CHECK(revCheck == ontology.getCore()._revision); //is in list

      resultIS = ontology.defineInformationSpace(fixture.spIS1);

      //test IS inference
      Result<SimpleTestOntology::ConstInfSpaceVectorType> resultISs = ontology.getInformationSpaces();
      CHECK(resultISs.getRevision() == ++revCheck);
      CHECK(resultISs->size() == 3); //is in list
      CHECK(existsUIDInInferenceVector(resultISs, fixture.spIS1));
      CHECK(existsUIDInInferenceVector(resultISs, fixture.spIS2));
      CHECK(existsUIDInInferenceVector(resultISs, fixture.spIS3));

      /////////////////////////////////////////////////////////////////////////
      // information entities

      //test invalid usage of entity integration
      CHECK_THROW_EXPLICIT(ontology.defineEntity(fixture.spIENull,fixture.spIS1),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.defineEntity(fixture.spIENull,fixture.spISNull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.defineEntity(fixture.spIE1,fixture.spISNull),::iro::exceptions::InvalidArgument);

      //test correct define
      Result<SimpleTestOntology::ConstInfEntityPointer> resultIE = ontology.defineEntity(fixture.spIE1, fixture.spIS1);
      CHECK(resultIE.getRevision() == ++revCheck);
      CHECK(resultIE->getUID() == fixture.spIE1->getUID());
      ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::EntityMapType::iterator posIE = ontology.getCore()._entityMap.find(fixture.spIE1->getUID());
      CHECK(posIE != ontology.getCore()._entityMap.end()); //is in list
      CHECK(posIE->second == resultIE.getValue()); //is right element
      ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::EntityISMapType::iterator posIE2IS = ontology.getCore()._entity2ISMap.find(fixture.spIE1->getUID());
      CHECK(posIE2IS != ontology.getCore()._entity2ISMap.end()); //entity linked to IS
      CHECK(posIE2IS->second == fixture.spIS1->getUID()); //is linked to correct IS

      //test re define ->must stay silent and unchanged
      CHECK_NO_THROW(resultIE = ontology.defineEntity(fixture.spIE1,fixture.spIS1));
      CHECK(resultIE.getRevision() == revCheck);
      CHECK(resultIE->getUID() == fixture.spIE1->getUID());
      CHECK(1 == ontology.getCore()._entityMap.size());
      CHECK(1 == ontology.getCore()._entity2ISMap.size());

      //test invalid usage of entity store
      CHECK_THROW_EXPLICIT(ontology.storeEntity(fixture.spIENull),::iro::exceptions::InvalidArgument);

      //test correct store
      ::iro::scenario::SimpleInformationEntity::Pointer spIE1Clone = fixture.spIE1->clone();
      spIE1Clone->setDataRepresentation(DataRepresentation::Continuous);
      CHECK_NO_THROW(resultIE = ontology.storeEntity(spIE1Clone));
      CHECK(resultIE.getRevision() == ++revCheck);
      CHECK(resultIE->getDataRepresentation() == DataRepresentation::Continuous);
      posIE = ontology.getCore()._entityMap.find(fixture.spIE1->getUID());
      CHECK(posIE != ontology.getCore()._entityMap.end()); //is in list
      CHECK(posIE->second->getDataRepresentation() == DataRepresentation::Continuous); //has new representation type

      //test silent add with store
      CHECK_NO_THROW(resultIE = ontology.storeEntity(fixture.spIE2));
      CHECK(resultIE.getRevision() == ++revCheck);
      posIE = ontology.getCore()._entityMap.find(fixture.spIE2->getUID());
      CHECK(posIE != ontology.getCore()._entityMap.end()); //is in list

      //test invalid usage of entity delete
      CHECK_THROW_EXPLICIT(ontology.deleteEntity(fixture.spIENull),::iro::exceptions::InvalidArgument);

      //test entity inference
      Result<SimpleTestOntology::ConstInfEntityVectorType> resultIEs = ontology.getEntities();
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE1));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE2));
      CHECK(resultIEs->size() == 2); //is in list

      //test entity IS switch
      CHECK_THROW_EXPLICIT(ontology.switchInformationSpace(fixture.spIENull,fixture.spIS1),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.switchInformationSpace(fixture.spIE1,fixture.spISNull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.switchInformationSpace(fixture.spIE1,fixture.spIS5),::iro::exceptions::UndefinedElement); //fixture.spIS5 not yet defined in ontology
      CHECK_THROW_EXPLICIT(ontology.switchInformationSpace(fixture.spIE7,fixture.spIS1),::iro::exceptions::UndefinedElement); //fixture.spIE7 not yet defined in ontology

      CHECK_NO_THROW(ontology.switchInformationSpace(fixture.spIE2,fixture.spIS3));
      CHECK(ontology.getCore()._revision == ++revCheck);
      posIE2IS = ontology.getCore()._entity2ISMap.find(fixture.spIE2->getUID());
      CHECK(posIE2IS != ontology.getCore()._entity2ISMap.end()); //entity linked to IS
      CHECK(posIE2IS->second == fixture.spIS3->getUID()); //is linked to correct IS
      //test a changing switch
      CHECK_NO_THROW(ontology.switchInformationSpace(fixture.spIE2,fixture.spIS2));
      CHECK(ontology.getCore()._revision == ++revCheck);
      posIE2IS = ontology.getCore()._entity2ISMap.find(fixture.spIE2->getUID());
      CHECK(posIE2IS != ontology.getCore()._entity2ISMap.end()); //entity linked to IS
      CHECK(posIE2IS->second == fixture.spIS2->getUID()); //is linked to correct IS

      ///////////////////////////////////////////////////////////
      // define rest of ISs and entities

      ontology.defineInformationSpace(fixture.spIS4);
      ontology.defineInformationSpace(fixture.spIS5);

      ontology.defineEntity(fixture.spIE3,fixture.spIS3);
      ontology.defineEntity(fixture.spIE4,fixture.spIS1);
      ontology.defineEntity(fixture.spIE5,fixture.spIS2);
      ontology.defineEntity(fixture.spIE6,fixture.spIS4);
      ontology.defineEntity(fixture.spIE7,fixture.spIS3);
      ontology.defineEntity(fixture.spIE8,fixture.spIS2);
      
      revCheck = revCheck+8;


      ///////////////////////////////////////////////////////////
      // test entity-IS-inference

      //check getContainingIS
      CHECK_THROW_EXPLICIT(ontology.getContainingIS(fixture.spIENull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getContainingIS(fixture.spIEUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultIS = ontology.getContainingIS(fixture.spIE1));
      CHECK(resultIS.getRevision() == revCheck);
      CHECK(resultIS->getUID() == fixture.spIS1->getUID());

      CHECK_NO_THROW(resultIS = ontology.getContainingIS(fixture.spIE6));
      CHECK(resultIS.getRevision() == revCheck);
      CHECK(resultIS->getUID() == fixture.spIS4->getUID());

      CHECK_NO_THROW(resultIS = ontology.getContainingIS(fixture.spIE8));
      CHECK(resultIS.getRevision() == revCheck);
      CHECK(resultIS->getUID() == fixture.spIS2->getUID());

      //check getEntitiesInIS
      CHECK_THROW_EXPLICIT(ontology.getEntitiesInIS(fixture.spISNull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getEntitiesInIS(fixture.spISUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultIEs = ontology.getEntitiesInIS(fixture.spIS5));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(resultIEs->size() == 0);

      CHECK_NO_THROW(resultIEs = ontology.getEntitiesInIS(fixture.spIS4));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(resultIEs->size() == 1);
      CHECK(resultIEs->front()->getUID() == fixture.spIE6->getUID());

      CHECK_NO_THROW(resultIEs = ontology.getEntitiesInIS(fixture.spIS1));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE1));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE4));
      CHECK(resultIEs->size() == 2);

      CHECK_NO_THROW(resultIEs = ontology.getEntitiesInIS(fixture.spIS3));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE3));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE7));
      CHECK(resultIEs->size() == 2);

      CHECK_NO_THROW(resultIEs = ontology.getEntitiesInIS(fixture.spIS2));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE2));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE5));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE8));
      CHECK(resultIEs->size() == 3);

      //check checkForSameIS
      CHECK_THROW_EXPLICIT(ontology.checkForSameIS(fixture.spIENull,fixture.spIE2),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.checkForSameIS(fixture.spIEUnknown,fixture.spIE2),::iro::exceptions::UndefinedElement);
      CHECK_THROW_EXPLICIT(ontology.checkForSameIS(fixture.spIE1, fixture.spIENull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.checkForSameIS(fixture.spIE1, fixture.spIEUnknown),::iro::exceptions::UndefinedElement);

      Result<bool> resultBool = ontology.checkForSameIS(fixture.spIE1,fixture.spIE2);
      CHECK(resultBool.getRevision() == revCheck);
      CHECK(!(*resultBool));
      CHECK_NO_THROW(resultBool = ontology.checkForSameIS(fixture.spIE1,fixture.spIE4));
      CHECK(resultBool.getRevision() == revCheck);
      CHECK((*resultBool));
      CHECK_NO_THROW(resultBool = ontology.checkForSameIS(fixture.spIE3,fixture.spIE7));
      CHECK(resultBool.getRevision() == revCheck);
      CHECK((*resultBool));

      SimpleTestOntology::ConstInfEntityVectorType checkIEs;
      CHECK_NO_THROW(resultBool = ontology.checkForSameIS(checkIEs)); //empty vector is also true
      CHECK(resultBool.getRevision() == revCheck);
      CHECK((*resultBool));

      checkIEs.push_back(fixture.spIENull);
      CHECK_THROW_EXPLICIT(ontology.checkForSameIS(checkIEs),::iro::exceptions::InvalidArgument);

      checkIEs.clear(); checkIEs.push_back(fixture.spIEUnknown);
      CHECK_THROW_EXPLICIT(ontology.checkForSameIS(checkIEs),::iro::exceptions::UndefinedElement);

      checkIEs.clear();
      checkIEs.push_back(fixture.spIE2);
      checkIEs.push_back(fixture.spIE5);
      checkIEs.push_back(fixture.spIE8);
      CHECK_NO_THROW(resultBool = ontology.checkForSameIS(checkIEs));
      CHECK(resultBool.getRevision() == revCheck);
      CHECK((*resultBool));

      checkIEs.push_back(fixture.spIE1);
      CHECK_NO_THROW(resultBool = ontology.checkForSameIS(checkIEs));
      CHECK(resultBool.getRevision() == revCheck);
      CHECK(!(*resultBool));

      //check hasDiscreteDataRepresentation
      CHECK_THROW_EXPLICIT(ontology.getDataRepresentationType(fixture.spIENull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getDataRepresentationType(fixture.spIEUnknown),::iro::exceptions::UndefinedElement);

      Result<SimpleTestOntology::DataRepresentationType> resultDRep = ontology.getDataRepresentationType(fixture.spIE2);
      CHECK(resultDRep.getRevision() == revCheck);
      CHECK(*resultDRep ==DataRepresentation::Discrete);
      
      CHECK_NO_THROW(resultDRep = ontology.getDataRepresentationType(fixture.spIE8));
      CHECK(resultDRep.getRevision() == revCheck);
      CHECK(*resultDRep ==DataRepresentation::Continuous);

      //check hasDiscreteDataRepresentation
      CHECK_THROW_EXPLICIT(ontology.hasDiscreteDataRepresentation(fixture.spIENull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.hasDiscreteDataRepresentation(fixture.spIEUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultBool = ontology.hasDiscreteDataRepresentation(fixture.spIE2));
      CHECK(resultBool.getRevision() == revCheck);
      CHECK((*resultBool));
      
      CHECK_NO_THROW(resultBool = ontology.hasDiscreteDataRepresentation(fixture.spIE8));
      CHECK(resultBool.getRevision() == revCheck);
      CHECK(!(*resultBool));

      //check hasContinuousDataRepresentation
      CHECK_THROW_EXPLICIT(ontology.hasContinuousDataRepresentation(fixture.spIENull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.hasContinuousDataRepresentation(fixture.spIEUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultBool = ontology.hasContinuousDataRepresentation(fixture.spIE2));
      CHECK(resultBool.getRevision() == revCheck);
      CHECK(!(*resultBool));
      
      CHECK_NO_THROW(resultBool = ontology.hasContinuousDataRepresentation(fixture.spIE8));
      CHECK(resultBool.getRevision() == revCheck);
      CHECK((*resultBool));

      /////////////////////////////////////////////////////////////////////////
      // correlations

      //test invalid usage of correlation integration
      CHECK_THROW_EXPLICIT(ontology.defineSemanticCorrelation(fixture.spCorNull),::iro::exceptions::InvalidArgument);

      //test correct define
      Result<SimpleTestOntology::ConstCorrelationPointer> resultCor = ontology.defineSemanticCorrelation(fixture.spCor1);
      CHECK(resultCor.getRevision() == ++revCheck);
      CHECK(resultCor->getUID() == fixture.spCor1->getUID());
      ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::CorrelationMapType::iterator posCor = ontology.getCore()._correlationMap.find(fixture.spCor1->getUID());
      CHECK(posCor != ontology.getCore()._correlationMap.end()); //is in list
      CHECK(posCor->second == resultCor.getValue()); //is right element
      CHECK(ontology.getCore()._entity2CorrelationMap.size() == 4); //added correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE1,fixture.spCor1,ontology.getCore())); //check correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE2,fixture.spCor1,ontology.getCore())); //check correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE3,fixture.spCor1,ontology.getCore())); //check correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE5,fixture.spCor1,ontology.getCore())); //check correlation look ups

      //test re define ->must stay silent and unchanged
      CHECK_NO_THROW(resultCor = ontology.defineSemanticCorrelation(fixture.spCor1));
      CHECK(resultCor.getRevision() == revCheck);

      //test invalid usage of IS store
      CHECK_THROW_EXPLICIT(ontology.storeSemanticCorrelation(fixture.spCorNull),::iro::exceptions::InvalidArgument);

      //test correct store
      CHECK_NO_THROW(resultCor = ontology.storeSemanticCorrelation(fixture.spCor1_small));
      CHECK(resultCor.getRevision() == ++revCheck);
      CHECK(resultCor->getUID() == fixture.spCor1_small->getUID());
      posCor = ontology.getCore()._correlationMap.find(fixture.spCor1_small->getUID());
      CHECK(posCor != ontology.getCore()._correlationMap.end()); //is in list
      CHECK(posCor->second == resultCor.getValue()); //is right element
      CHECK(1 == ontology.getCore()._correlationMap.size()); //check number of correlations
      CHECK(ontology.getCore()._entity2CorrelationMap.size() == 3); //list of look ups should be reduced now
      CHECK(checkCorrelationEntryExists(fixture.spIE1,fixture.spCor1,ontology.getCore())); //check correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE2,fixture.spCor1,ontology.getCore())); //check correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE3,fixture.spCor1,ontology.getCore())); //check correlation look ups

      //test store of unkown correlation ->must do a silent define
      CHECK_NO_THROW(resultCor = ontology.storeSemanticCorrelation(fixture.spCor2));
      CHECK(resultCor.getRevision() == ++revCheck);
      CHECK(resultCor->getUID() == fixture.spCor2->getUID());
      posCor = ontology.getCore()._correlationMap.find(fixture.spCor2->getUID());
      CHECK(posCor != ontology.getCore()._correlationMap.end()); //is in list
      CHECK(posCor->second == resultCor.getValue()); //is right element
      CHECK(2 == ontology.getCore()._correlationMap.size()); //check number of correlations
      CHECK(ontology.getCore()._entity2CorrelationMap.size() == 6); //list of look ups 
      CHECK(checkCorrelationEntryExists(fixture.spIE3,fixture.spCor2,ontology.getCore())); //check correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE4,fixture.spCor2,ontology.getCore())); //check correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE5,fixture.spCor2,ontology.getCore())); //check correlation look ups

      //test invalid usage of IS delete
      CHECK_THROW_EXPLICIT(ontology.deleteSemanticCorrelation(fixture.spCorNull),::iro::exceptions::InvalidArgument);

      //test correct delete
      CHECK(ontology.deleteSemanticCorrelation(fixture.spCor1));
      CHECK(1 == ontology.getCore()._correlationMap.size());
      posCor = ontology.getCore()._correlationMap.find(fixture.spCor1->getUID());
      CHECK(posCor == ontology.getCore()._correlationMap.end()); //is not in list
      CHECK(++revCheck == ontology.getCore()._revision); //is in list
      CHECK(ontology.getCore()._entity2CorrelationMap.size() == 3); //list of look ups is reduced only cor2 left
      CHECK(checkCorrelationEntryExists(fixture.spIE3,fixture.spCor2,ontology.getCore())); //check correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE4,fixture.spCor2,ontology.getCore())); //check correlation look ups
      CHECK(checkCorrelationEntryExists(fixture.spIE5,fixture.spCor2,ontology.getCore())); //check correlation look ups

      //test delete unkown element -> keep silent
      CHECK(ontology.deleteSemanticCorrelation(fixture.spCor1));
      CHECK(1 == ontology.getCore()._correlationMap.size());
      CHECK(revCheck == ontology.getCore()._revision); //is in list

      //(re)define the rest of the correlations
      ontology.defineSemanticCorrelation(fixture.spCor1);
      revCheck++;
      ontology.defineSemanticCorrelation(fixture.spCor3);
      revCheck++;

      //test correlation infernce
      Result<SimpleTestOntology::ConstCorrelationVectorType> resultCors = ontology.getSemanticCorrelations();
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(resultCors->size() == 3); //is in list
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor1));
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor2));
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor3));

      ///////////////////////////////////////////////////////////
      // test entity-IS-correlation-inference

      //check getEntitiesWithSemanticCorrelations
      CHECK_THROW_EXPLICIT(ontology.getEntitiesWithSemanticCorrelations(fixture.spIENull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getEntitiesWithSemanticCorrelations(fixture.spIEUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultIEs = ontology.getEntitiesWithSemanticCorrelations(fixture.spIE1));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE2));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE3));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE5));
      CHECK(resultIEs->size() == 3);

      CHECK_NO_THROW(resultIEs = ontology.getEntitiesWithSemanticCorrelations(fixture.spIE6));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(resultIEs->size() == 0);

      CHECK_NO_THROW(resultIEs = ontology.getEntitiesWithSemanticCorrelations(fixture.spIE3));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE1));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE4));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE5));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE2));
      CHECK(resultIEs->size() == 4);

      //check getSemanticallyCorrelatedEntities
      CHECK_THROW_EXPLICIT(ontology.getSemanticallyCorrelatedEntities(fixture.spISNull, fixture.spIS2),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getSemanticallyCorrelatedEntities(fixture.spISUnknown, fixture.spIS2),::iro::exceptions::UndefinedElement);
      CHECK_THROW_EXPLICIT(ontology.getSemanticallyCorrelatedEntities(fixture.spIS1, fixture.spISNull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getSemanticallyCorrelatedEntities(fixture.spIS1, fixture.spISUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultIEs = ontology.getSemanticallyCorrelatedEntities(fixture.spIS1,fixture.spIS2));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE1));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE4));
      CHECK(resultIEs->size() == 2);

      CHECK_NO_THROW(resultIEs = ontology.getSemanticallyCorrelatedEntities(fixture.spIS2,fixture.spIS1));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE2));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE5));
      CHECK(resultIEs->size() == 2);

      CHECK_NO_THROW(resultIEs = ontology.getSemanticallyCorrelatedEntities(fixture.spIS1, fixture.spIS5));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(resultIEs->size() == 0);

      CHECK_NO_THROW(resultIEs = ontology.getSemanticallyCorrelatedEntities(fixture.spIS1,fixture.spIS3));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE1));
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE4));
      CHECK(resultIEs->size() == 2);

      CHECK_NO_THROW(resultIEs = ontology.getSemanticallyCorrelatedEntities(fixture.spIS3,fixture.spIS1));
      CHECK(resultIEs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultIEs, fixture.spIE3));
      CHECK(resultIEs->size() == 1);

      //check getSemanticCorrelations
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spISNull, fixture.spIS2),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spISUnknown, fixture.spIS2),::iro::exceptions::UndefinedElement);
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIS1, fixture.spISNull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIS1, fixture.spISUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIS1,fixture.spIS2));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor1));
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor2));
      CHECK(resultCors->size() == 2);

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIS1,fixture.spIS4));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(resultCors->size() == 0);

      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIENull, fixture.spIS2),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIEUnknown, fixture.spIS2),::iro::exceptions::UndefinedElement);
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIE1, fixture.spISNull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIE1, fixture.spISUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIE1,fixture.spIS2));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor1));
      CHECK(resultCors->size() == 1);

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIE3,fixture.spIS1));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor1));
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor2));
      CHECK(resultCors->size() == 2);

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIE7,fixture.spIS1));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(resultCors->size() == 0); //ISs are correlated but not IE7 with IS1

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIE6,fixture.spIS2));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(resultCors->size() == 0); //No correlation between ISs at all

      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIENull, fixture.spIE2),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIEUnknown, fixture.spIE2),::iro::exceptions::UndefinedElement);
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIE1, fixture.spIENull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getSemanticCorrelations(fixture.spIE1, fixture.spIEUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIE1,fixture.spIE5));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor1));
      CHECK(resultCors->size() == 1);

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIE3,fixture.spIE5));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor1));
      CHECK(existsUIDInInferenceVector(resultCors, fixture.spCor2));
      CHECK(resultCors->size() == 2);

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIE7,fixture.spIS5));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(resultCors->size() == 0); //ISs are correlated but not IE7 with IE5

      CHECK_NO_THROW(resultCors = ontology.getSemanticCorrelations(fixture.spIE6,fixture.spIE1));
      CHECK(resultCors.getRevision() == revCheck);
      CHECK(resultCors->size() == 0); //No correlation between IEs at all


      /////////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////
      // test problem inference / integration
      /////////////////////////////////////////////////////////////////////////

      /////////////////////////////////////////////////////////////////////////
      // test problem statement integration

      //test invalid usage of IS integration
      CHECK_THROW_EXPLICIT(ontology.defineProblemStatement(fixture.spPSNull),::iro::exceptions::InvalidArgument);

      //test correct define
      Result<SimpleTestOntology::ConstProblemStatementPointer> resultPS = ontology.defineProblemStatement(fixture.spPS1);
      CHECK(resultPS.getRevision() == ++revCheck);
      CHECK(resultPS->getUID() == fixture.spPS1->getUID());
      ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::StatementMapType::iterator posStat = ontology.getCore()._statementMap.find(fixture.spPS1->getUID());
      CHECK(posStat != ontology.getCore()._statementMap.end()); //is in list
      CHECK(posStat->second == resultPS.getValue()); //is right element
      CHECK(1 == ontology.getCore()._statementMap.size()); //check number of correlations

      //test re define ->must stay silent and unchanged
      CHECK_NO_THROW(resultPS = ontology.defineProblemStatement(fixture.spPS1));
      CHECK(resultPS.getRevision() == revCheck);

      //test invalid usage of IS store
      CHECK_THROW_EXPLICIT(ontology.storeProblemStatement(fixture.spPSNull),::iro::exceptions::InvalidArgument);

      //test correct store
      ::iro::scenario::SimpleProblemStatement::Pointer spPS1_clone = fixture.spPS1->clone();
      ::iro::scenario::SimpleProblemStatement::ConstPointer internalPS1 = resultPS.getValue();
      spPS1_clone->setName("PS 1 Clone");
      CHECK_NO_THROW(resultPS = ontology.storeProblemStatement(spPS1_clone));
      CHECK(resultPS.getRevision() == ++revCheck);
      CHECK(resultPS->getUID() == spPS1_clone->getUID());
      CHECK(internalPS1 == resultPS.getValue()); //is still the right element

      CHECK_NO_THROW(resultPS = ontology.storeProblemStatement(fixture.spPS1));
      ++revCheck;

      //test store of unkown correlation ->must do a silent define
      CHECK_NO_THROW(resultPS = ontology.storeProblemStatement(fixture.spPS2));
      CHECK(resultPS.getRevision() == ++revCheck);
      CHECK(resultPS->getUID() == fixture.spPS2->getUID());
      posStat = ontology.getCore()._statementMap.find(fixture.spPS2->getUID());
      CHECK(posStat != ontology.getCore()._statementMap.end()); //is in list
      CHECK(posStat->second == resultPS.getValue()); //is right element
      CHECK(2 == ontology.getCore()._statementMap.size()); //check number of correlations

      ////test invalid usage of IS delete
      CHECK_THROW_EXPLICIT(ontology.deleteProblemStatement(fixture.spPSNull),::iro::exceptions::InvalidArgument);

      //test correct delete
      CHECK(ontology.deleteProblemStatement(fixture.spPS1));
      CHECK(1 == ontology.getCore()._statementMap.size());
      posStat = ontology.getCore()._statementMap.find(fixture.spPS1->getUID());
      CHECK(posStat == ontology.getCore()._statementMap.end()); //is not in list
      CHECK(++revCheck == ontology.getCore()._revision); //is in list

      //test delete unkown element -> keep silent
      CHECK(ontology.deleteProblemStatement(fixture.spPS1));
      CHECK(1 == ontology.getCore()._statementMap.size());
      CHECK(revCheck == ontology.getCore()._revision); //is in list

      //(re)define the some of the correlations; rest will be defined after the first tests of problem model
      CHECK_NO_THROW(ontology.defineProblemStatement(fixture.spPS1));
      revCheck++;
      CHECK_NO_THROW(ontology.defineProblemStatement(fixture.spPS3));
      revCheck++;

      //test statement inference
      Result<SimpleTestOntology::ConstProblemStatementVectorType> resultPSs = ontology.getProblemStatements();
      CHECK(resultPSs.getRevision() == revCheck);
      CHECK(resultPSs->size() == 3); //is in list
      CHECK(existsUIDInInferenceVector(resultPSs, fixture.spPS1));
      CHECK(existsUIDInInferenceVector(resultPSs, fixture.spPS2));
      CHECK(existsUIDInInferenceVector(resultPSs, fixture.spPS3));

      /////////////////////////////////////////////////////////////////////////
      // test problem model integration

      //test invalid usage of correlation integration
      CHECK_THROW_EXPLICIT(ontology.defineProblemModel(fixture.spPMNull),::iro::exceptions::InvalidArgument);

      //test correct define
      Result<SimpleTestOntology::ConstProblemModelPointer> resultPM = ontology.defineProblemModel(fixture.spPM1);
      CHECK(resultPM.getRevision() == ++revCheck);
      CHECK(resultPM->getUID() == fixture.spPM1->getUID());
      ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::ModelMapType::iterator posPM = ontology.getCore()._modelMap.find(fixture.spPM1->getUID());
      CHECK(posPM != ontology.getCore()._modelMap.end()); //is in list
      CHECK(posPM->second == resultPM.getValue()); //is right element
      CHECK(ontology.getCore()._stat2ModelMap.size() == 2); //added statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS1,fixture.spPM1,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS2,fixture.spPM1,ontology.getCore())); //check statement look ups

      //test invalid usage (statements referenced are unknown)
      CHECK_THROW_EXPLICIT(ontology.defineProblemModel(fixture.spPM2),::iro::exceptions::InvalidArgument);
      CHECK(resultPM.getRevision() == revCheck);
      CHECK(ontology.getCore()._stat2ModelMap.size() == 2); //unchanged statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS1,fixture.spPM1,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS2,fixture.spPM1,ontology.getCore())); //check statement look ups
      //define missing statements
      CHECK_NO_THROW(ontology.defineProblemStatement(fixture.spPS4));
      ++revCheck;
      CHECK_NO_THROW(ontology.defineProblemStatement(fixture.spPS5));
      ++revCheck;
      CHECK_NO_THROW(ontology.defineProblemStatement(fixture.spPS6));
      revCheck++;
      //redo define of model -> now it should work
      CHECK_NO_THROW(resultPM = ontology.storeProblemModel(fixture.spPM2));
      CHECK(resultPM.getRevision() == ++revCheck);
      CHECK(resultPM->getUID() == fixture.spPM2->getUID());
      posPM = ontology.getCore()._modelMap.find(fixture.spPM2->getUID());
      CHECK(posPM != ontology.getCore()._modelMap.end()); //is in list
      CHECK(posPM->second == resultPM.getValue()); //is right element
      CHECK(2 == ontology.getCore()._modelMap.size()); //check number of models
      CHECK(ontology.getCore()._stat2ModelMap.size() == 5); //list of look ups should be reduced now
      CHECK(checkStatementEntryExists(fixture.spPS1,fixture.spPM1,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS2,fixture.spPM1,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS1,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS3,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS4,fixture.spPM2,ontology.getCore())); //check statement look ups

      //test re define ->must stay silent and unchanged
      CHECK_NO_THROW(resultPM = ontology.defineProblemModel(fixture.spPM1));
      CHECK(resultPM.getRevision() == revCheck);

      //test invalid usage of IS store
      CHECK_THROW_EXPLICIT(ontology.storeProblemModel(fixture.spPMNull),::iro::exceptions::InvalidArgument);

      //test correct store
      CHECK_NO_THROW(resultPM = ontology.storeProblemModel(fixture.spPM1_small));
      CHECK(resultPM.getRevision() == ++revCheck);
      CHECK(resultPM->getUID() == fixture.spPM1_small->getUID());
      posPM = ontology.getCore()._modelMap.find(fixture.spPM1_small->getUID());
      CHECK(posPM != ontology.getCore()._modelMap.end()); //is in list
      CHECK(posPM->second == resultPM.getValue()); //is right element
      CHECK(2 == ontology.getCore()._modelMap.size()); //check number of models
      CHECK(ontology.getCore()._stat2ModelMap.size() == 4); //list of look ups should be reduced now
      CHECK(checkStatementEntryExists(fixture.spPS1,fixture.spPM1,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS1,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS3,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS4,fixture.spPM2,ontology.getCore())); //check statement look ups

      //test store of unkown correlation ->must do a silent define
      CHECK_NO_THROW(resultPM = ontology.storeProblemModel(fixture.spPM3));
      CHECK(resultPM.getRevision() == ++revCheck);
      CHECK(resultPM->getUID() == fixture.spPM3->getUID());
      posPM = ontology.getCore()._modelMap.find(fixture.spPM3->getUID());
      CHECK(posPM != ontology.getCore()._modelMap.end()); //is in list
      CHECK(posPM->second == resultPM.getValue()); //is right element
      CHECK(3 == ontology.getCore()._modelMap.size()); //check number of correlations
      CHECK(ontology.getCore()._stat2ModelMap.size() == 5); //list of look ups 
      CHECK(checkStatementEntryExists(fixture.spPS1,fixture.spPM1,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS1,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS3,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS4,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS5,fixture.spPM3,ontology.getCore())); //check statement look ups

      //test invalid usage of IS delete
      CHECK_THROW_EXPLICIT(ontology.deleteProblemModel(fixture.spPMNull),::iro::exceptions::InvalidArgument);

      //test correct delete
      CHECK(ontology.deleteProblemModel(fixture.spPM1));
      CHECK(2 == ontology.getCore()._modelMap.size());
      posPM = ontology.getCore()._modelMap.find(fixture.spPM1->getUID());
      CHECK(posPM == ontology.getCore()._modelMap.end()); //is not in list
      CHECK(++revCheck == ontology.getCore()._revision); 
      CHECK(ontology.getCore()._stat2ModelMap.size() == 4); //list of look ups is reduced only cor2 left
      CHECK(checkStatementEntryExists(fixture.spPS1,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS3,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS4,fixture.spPM2,ontology.getCore())); //check statement look ups
      CHECK(checkStatementEntryExists(fixture.spPS5,fixture.spPM3,ontology.getCore())); //check statement look ups

      //test delete unkown element -> keep silent
      CHECK(ontology.deleteProblemModel(fixture.spPM1));
      CHECK(2 == ontology.getCore()._modelMap.size());
      CHECK(revCheck == ontology.getCore()._revision); //is not changed

      //(re)define the rest of the correlations
      ontology.defineProblemModel(fixture.spPM1);
      revCheck++;
      ontology.defineProblemModel(fixture.spPM4);
      revCheck++;

      //test correlation infernce
      Result<SimpleTestOntology::ConstProblemModelVectorType> resultPMs = ontology.getProblemModels();
      CHECK(resultPMs.getRevision() == revCheck);
      CHECK(resultPMs->size() == 4); //is in list
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM1));
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM2));
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM3));
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM4));

      ///////////////////////////////////////////////////////////
      // test statement-model-inference

      //check getAssociatedProblemModels
      CHECK_THROW_EXPLICIT(ontology.getAssociatedProblemModels(fixture.spPSNull),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getAssociatedProblemModels(fixture.spPSUnknown),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultPMs = ontology.getAssociatedProblemModels(fixture.spPS1));
      CHECK(resultPMs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM1));
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM2));
      CHECK(resultPMs->size() == 2);

      CHECK_NO_THROW(resultPMs = ontology.getAssociatedProblemModels(fixture.spPS2));
      CHECK(resultPMs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM1));
      CHECK(resultPMs->size() == 1);

      CHECK_NO_THROW(resultPMs = ontology.getAssociatedProblemModels(fixture.spPS5));
      CHECK(resultPMs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM3));
      CHECK(resultPMs->size() == 1);

      CHECK_NO_THROW(resultPMs = ontology.getAssociatedProblemModels(fixture.spPS6));
      CHECK(resultPMs.getRevision() == revCheck);
      CHECK(resultPMs->size() == 0);

      //check getAssociatedProblemModels für problem associated
      ::iro::scenario::SimpleTransformationInfo::Pointer spTestTrans = generateTransInfo("1->2",fixture.spIS1,fixture.spIS2,fixture.spPS1, DataRepresentation::Discrete);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTestTrans_unknown = generateTransInfo("unkown",fixture.spIS1,fixture.spIS2,fixture.spPSUnknown, DataRepresentation::Discrete);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTestTrans_null = generateTransInfo("null",fixture.spIS1,fixture.spIS2,fixture.spPSNull, DataRepresentation::Discrete);

      CHECK_THROW_EXPLICIT(ontology.getAssociatedProblemModels(NULL),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getAssociatedProblemModels(spTestTrans_null.get()),::iro::exceptions::InvalidArgument);
      CHECK_THROW_EXPLICIT(ontology.getAssociatedProblemModels(spTestTrans_unknown.get()),::iro::exceptions::UndefinedElement);

      CHECK_NO_THROW(resultPMs = ontology.getAssociatedProblemModels(spTestTrans.get()));
      CHECK(resultPMs.getRevision() == revCheck);
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM1));
      CHECK(existsUIDInInferenceVector(resultPMs, fixture.spPM2));
      CHECK(resultPMs->size() == 2);

      /////////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////
      // test mapping inference / integration
      /////////////////////////////////////////////////////////////////////////

      ontology.defineTransformation(fixture.spTrans1_2);
      ontology.defineTransformation(fixture.spTrans2_3);
      ontology.defineTransformation(fixture.spTrans3_4);
      ontology.defineTransformation(fixture.spTrans1_2d);
      ontology.defineTransformation(fixture.spTrans3_4d);
      ontology.defineTransformation(fixture.spTrans2_5);
      ontology.defineTransformation(fixture.spTrans1_3d);
      ontology.defineTransformation(fixture.spTrans2_5d);
      ontology.defineTransformation(fixture.spTrans5_3);
      ontology.defineTransformation(fixture.spTrans5_3d);
      ontology.defineTransformation(fixture.spTrans4_3);


      Result<SimpleTestOntology::ConstRegPathOptColPointer> resultRPOC = ontology.getOptimalRegistrationPaths(fixture.spIS1,fixture.spIS2);
      resultRPOC = ontology.getOptimalRegistrationPaths(fixture.spIS1,fixture.spIS3);
      resultRPOC = ontology.getOptimalRegistrationPaths(fixture.spIS1,fixture.spIS3,DataRepresentationSupport::Arbitrary);
      resultRPOC = ontology.getOptimalRegistrationPaths(fixture.spIS1,fixture.spIS3,DataRepresentationSupport::Continuous);
      resultRPOC = ontology.getOptimalRegistrationPaths(fixture.spIS1,fixture.spIS3,DataRepresentationSupport::Discrete);
      resultRPOC = ontology.getOptimalRegistrationPaths(fixture.spIS1,fixture.spIS4);

      resultRPOC = ontology.getRegistrationPaths(fixture.spIS1,fixture.spIS3);

      //**@TODO Test für die mapping inference methoden

      resultISs = ontology.getMappableInformationSpaces(fixture.spIS2,DataRepresentationSupport::Arbitrary);
      resultISs = ontology.getMappableInformationSpaces(fixture.spIS3,DataRepresentationSupport::Arbitrary);
      resultISs = ontology.getMappableInformationSpaces(fixture.spIS3,DataRepresentationSupport::All);
      resultISs = ontology.getMappableInformationSpaces(fixture.spIS1,DataRepresentationSupport::All);

      /////////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////
      // test rest
      /////////////////////////////////////////////////////////////////////////

      //delete test for entities 
      ////test correct delete
      //CHECK(ontology.deleteEntity(fixture.spIS1));
      //CHECK(2 == ontology.getCore()._ISMap.size());
      //posIS = ontology.getCore()._ISMap.find(fixture.spIS1->getUID());
      //CHECK(posIS == ontology.getCore()._ISMap.end()); //is not in list
      //CHECK(4 == ontology.getCore()._revision); //is in list

      ////test delete unkown element -> keep silent
      //CHECK(ontology.deleteInformationSpace(fixture.spIS1));
      //CHECK(2 == ontology.getCore()._ISMap.size());revCheck
      //CHECK(4 == ontology.getCore()._revision); //is in list

      //resultIS = ontology.defineInformationSpace(fixture.spIS1);

      //delete test for correlations wie bei PS

      //löschen von PS wenn modelle da sind um zu prüfen, ob die map sauber entfernt wird

      //test actualization

      //TODO teste ob sauber aktualisiert wird wenn z.B. eine korrelation gespeichert wird,
      //die auf eine alte variante einer entität oder den Klone verweist, muss sie nach dem
      //speichern, anlegen auf die Entitäten verweisen, die in der Ontology gespeichert sind
      //das gleiche gilt auch für Models udn Statements, sowie bei Transformations und
      //IS

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace iro
