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


#include "mapSimpleOntologyCore.h"
#include "mapSimpleOntology.h"
#include "mapSimpleTestHelper.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace iro
{
  namespace testing
  {

    int mapSimpleOntologyCoreTest(int, char* [] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;
      using OntologyCoreType = ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>;
      //establish test elements
      OntologyCoreType core;

      ::iro::scenario::SimpleInformationEntity::Pointer spIE1 = generateEntity("e1");
      ::iro::scenario::SimpleInformationEntity::Pointer spIE2 = generateEntity("e2");
      ::iro::scenario::SimpleInformationEntity::Pointer spIE3 = generateEntity("e3");
      ::iro::scenario::SimpleInformationEntity::Pointer spIE4 = generateEntity("e4");
      ::iro::scenario::SimpleInformationEntity::Pointer spIE5 = generateEntity("e5");
      ::iro::scenario::SimpleInformationEntity::Pointer spIE6 = generateEntity("e6");
      ::iro::scenario::SimpleInformationEntity::Pointer spIE7 = generateEntity("e7");
      ::iro::scenario::SimpleInformationEntity::Pointer spIE8 = generateEntity("e8");

      typedef std::list<::iro::scenario::SimpleInformationEntity::ConstPointer> IEListType;

      IEListType ieList1;
      ieList1.push_back(spIE1);
      ieList1.push_back(spIE2);
      ieList1.push_back(spIE3);
      IEListType ieList2;
      ieList2.push_back(spIE3);
      ieList2.push_back(spIE4);
      ieList2.push_back(spIE5);
      IEListType ieList3;
      ieList3.push_back(spIE2);
      ieList3.push_back(spIE7);

      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor1_small = generateCorrelation(ieList1);
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor2 = generateCorrelation(ieList2);

      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor1 = spCor1_small->clone();
      spCor1->addCorrelatedEntity(spIE5);
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor1_large = spCor1_small->clone();
      spCor1_large->addCorrelatedEntity(spIE5);
      spCor1_large->addCorrelatedEntity(spIE6);
      spCor1_large->addCorrelatedEntity(spIE7);

      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor3 = generateCorrelation(ieList3);

      core._correlationMap[spCor1->getUID()] = spCor1;
      core._correlationMap[spCor2->getUID()] = spCor2;
      core._correlationMap[spCor3->getUID()] = spCor3;

      core._entityMap[spIE1->getUID()] = spIE1;
      core._entityMap[spIE2->getUID()] = spIE2;
      core._entityMap[spIE3->getUID()] = spIE3;
      core._entityMap[spIE4->getUID()] = spIE4;
      core._entityMap[spIE5->getUID()] = spIE5;
      core._entityMap[spIE6->getUID()] = spIE6;
      core._entityMap[spIE7->getUID()] = spIE7;
      core._entityMap[spIE8->getUID()] = spIE8;

      //check revision change
      CHECK_NO_THROW(core.notifyChange());
      CHECK(core._revision == 1);
      CHECK_NO_THROW(core.notifyChange());
      CHECK_NO_THROW(core.notifyChange());
      CHECK(core._revision == 3);

      //check update correlation map
      CHECK_NO_THROW(core.updateEntity2CorrelationMap(spCor1));
      CHECK(checkCorrelationEntryExists(spIE1,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE2,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE3,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE5,spCor1,core));
      CHECK(core._entity2CorrelationMap.size() == 4);

      CHECK_NO_THROW(core.updateEntity2CorrelationMap(spCor2));
      CHECK(checkCorrelationEntryExists(spIE1,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE2,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE3,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE5,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE3,spCor2,core));
      CHECK(checkCorrelationEntryExists(spIE4,spCor2,core));
      CHECK(checkCorrelationEntryExists(spIE5,spCor2,core));
      CHECK(core._entity2CorrelationMap.size() == 7);

      CHECK_NO_THROW(core.updateEntity2CorrelationMap(spCor1_small));
      CHECK(checkCorrelationEntryExists(spIE1,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE2,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE3,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE3,spCor2,core));
      CHECK(checkCorrelationEntryExists(spIE4,spCor2,core));
      CHECK(checkCorrelationEntryExists(spIE5,spCor2,core));
      CHECK(core._entity2CorrelationMap.size() == 6);

      CHECK_NO_THROW(core.updateEntity2CorrelationMap(spCor1_large));
      CHECK(checkCorrelationEntryExists(spIE1,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE2,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE3,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE5,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE6,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE7,spCor1,core));
      CHECK(checkCorrelationEntryExists(spIE3,spCor2,core));
      CHECK(checkCorrelationEntryExists(spIE4,spCor2,core));
      CHECK(checkCorrelationEntryExists(spIE5,spCor2,core));
      CHECK(core._entity2CorrelationMap.size() == 9);

      core.updateEntity2CorrelationMap(spCor1);
      core.updateEntity2CorrelationMap(spCor3);

      //////////////////////////////////////////////////
      //check update correlation map getCorrelations

      OntologyCoreType::ConstCorrelationMapType corrMap;
      OntologyCoreType::EntityUIDSetType uidSet1;
      OntologyCoreType::EntityUIDSetType uidSet2;
      OntologyCoreType::EntityUIDSetType uidSet3;
      OntologyCoreType::EntityUIDSetType uidSet4;
      OntologyCoreType::EntityUIDSetType uidSet5;
      OntologyCoreType::EntityUIDSetType emptyUIDSet;
      uidSet1.insert(spIE3->getUID());
      uidSet2.insert(spIE2->getUID());
      uidSet2.insert(spIE5->getUID());
      uidSet2.insert(spIE7->getUID());
      uidSet3.insert(spIE8->getUID());
      uidSet4.insert(spIE3->getUID());
      uidSet4.insert(spIE2->getUID());
      uidSet5.insert(spIE5->getUID());
      uidSet5.insert(spIE7->getUID());

      //check should get corr 1 (3-5 3-2), corr 2 (3-5), 3-7 is not available
      CHECK_NO_THROW(core.getCorrelations(corrMap, uidSet1, uidSet2));
      CHECK(corrMap.find(spCor1->getUID())!=corrMap.end());
      CHECK(corrMap.find(spCor2->getUID())!=corrMap.end());
      CHECK(corrMap.size()==2);

      //check should get corr 1 (2-5 3-5), corr 2 (3-5), corr 3 (2-7)
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, uidSet4, uidSet5));
      CHECK(corrMap.find(spCor1->getUID())!=corrMap.end());
      CHECK(corrMap.find(spCor2->getUID())!=corrMap.end());
      CHECK(corrMap.find(spCor3->getUID())!=corrMap.end());
      CHECK(corrMap.size()==3);

      //check should get no corr
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, uidSet3, uidSet2));
      CHECK(corrMap.size()==0);

      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, emptyUIDSet, uidSet2));
      CHECK(corrMap.size()==0);

      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, uidSet2, uidSet3));
      CHECK(corrMap.size()==0);

      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, uidSet2, emptyUIDSet));
      CHECK(corrMap.size()==0);

      //check should get corr 1  and corr 2
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, spIE3->getUID(), spIE5->getUID()));
      CHECK(corrMap.find(spCor1->getUID())!=corrMap.end());
      CHECK(corrMap.find(spCor2->getUID())!=corrMap.end());
      CHECK(corrMap.size()==2);

      //check should get corr 1  and corr 2
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, spIE5->getUID(), spIE3->getUID()));
      CHECK(corrMap.find(spCor1->getUID())!=corrMap.end());
      CHECK(corrMap.find(spCor2->getUID())!=corrMap.end());
      CHECK(corrMap.size()==2);

      //check should get corr 2
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, spIE3->getUID(), spIE4->getUID()));
      CHECK(corrMap.find(spCor2->getUID())!=corrMap.end());
      CHECK(corrMap.size()==1);

      //check should get corr 3
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, spIE2->getUID(), spIE7->getUID()));
      CHECK(corrMap.find(spCor3->getUID())!=corrMap.end());
      CHECK(corrMap.size()==1);

      //check should get nothing
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, spIE1->getUID(), spIE6->getUID()));
      CHECK(corrMap.size()==0);

      //check should get corr 1  and corr 3
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, spIE2->getUID()));
      CHECK(corrMap.find(spCor1->getUID())!=corrMap.end());
      CHECK(corrMap.find(spCor3->getUID())!=corrMap.end());
      CHECK(corrMap.size()==2);

      //check should get corr 2
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, spIE4->getUID()));
      CHECK(corrMap.find(spCor2->getUID())!=corrMap.end());
      CHECK(corrMap.size()==1);

      //check should get nothin
      corrMap.clear();
      CHECK_NO_THROW(core.getCorrelations(corrMap, spIE6->getUID()));
      CHECK(corrMap.size()==0);

      //check update correlation map getEntitiesByCorrelations
      corrMap.clear();
      core.getCorrelations(corrMap, uidSet1, uidSet2);
      OntologyCoreType::ConstEntityMapType entityMap;

      CHECK_NO_THROW(entityMap = core.getEntitiesByCorrelations(corrMap, uidSet2));
      CHECK(entityMap.find(spIE1->getUID())!=entityMap.end());
      CHECK(entityMap.find(spIE3->getUID())!=entityMap.end());
      CHECK(entityMap.find(spIE4->getUID())!=entityMap.end());
      CHECK(entityMap.size()==3);

      CHECK_NO_THROW(entityMap = core.getEntitiesByCorrelations(corrMap, uidSet2, true));
      CHECK(entityMap.find(spIE1->getUID())!=entityMap.end());
      CHECK(entityMap.find(spIE3->getUID())!=entityMap.end());
      CHECK(entityMap.find(spIE4->getUID())!=entityMap.end());
      CHECK(entityMap.size()==3);

      CHECK_NO_THROW(entityMap = core.getEntitiesByCorrelations(corrMap, uidSet5, false));
      CHECK(entityMap.find(spIE5->getUID())!=entityMap.end());
      CHECK(entityMap.size()==1);

      CHECK_NO_THROW(entityMap = core.getEntitiesByCorrelations(corrMap, uidSet2, false));
      CHECK(entityMap.find(spIE2->getUID())!=entityMap.end());
      CHECK(entityMap.find(spIE5->getUID())!=entityMap.end());
      CHECK(entityMap.size()==2);

      //check update correlation map removeEntityFromCorrelations
      CHECK_NO_THROW(core.removeEntityFromCorrelations(spIE8->getUID()));
      CHECK(spCor1->getCorrelatedEntitiesCount()==4);
      CHECK(spCor2->getCorrelatedEntitiesCount()==3);
      CHECK(spCor3->getCorrelatedEntitiesCount()==2);

      CHECK(spCor1->findCorrelatedEntity(spIE3->getUID())!=spCor1->getCorrelatedEntitiesEnd());
      CHECK(spCor2->findCorrelatedEntity(spIE3->getUID())!=spCor2->getCorrelatedEntitiesEnd());
      CHECK_NO_THROW(core.removeEntityFromCorrelations(spIE3->getUID()));
      CHECK(spCor1->getCorrelatedEntitiesCount()==3);
      CHECK(spCor1->findCorrelatedEntity(spIE3->getUID())==spCor1->getCorrelatedEntitiesEnd());
      CHECK(spCor2->getCorrelatedEntitiesCount()==2);
      CHECK(spCor2->findCorrelatedEntity(spIE3->getUID())==spCor2->getCorrelatedEntitiesEnd());
      CHECK(spCor3->getCorrelatedEntitiesCount()==2);

      CHECK(spCor1->findCorrelatedEntity(spIE1->getUID())!=spCor1->getCorrelatedEntitiesEnd());
      CHECK_NO_THROW(core.removeEntityFromCorrelations(spIE1->getUID()));
      CHECK(spCor1->getCorrelatedEntitiesCount()==2);
      CHECK(spCor1->findCorrelatedEntity(spIE1->getUID())==spCor1->getCorrelatedEntitiesEnd());
      CHECK(spCor2->getCorrelatedEntitiesCount()==2);
      CHECK(spCor3->getCorrelatedEntitiesCount()==2);

      //check update correlation map extracValuesFromMap
      std::vector<OntologyCoreType::ConstInfEntityPointer> entityVector;
      CHECK_NO_THROW(OntologyCoreType::extracValuesFromMap(entityMap,entityVector));
      CHECK(entityVector.size()==2);
      CHECK(entityVector[0] == spIE2);
      CHECK(entityVector[1] == spIE5);

      //check update correlation map extractUIDs
      CHECK(uidSet1.size()==1);
      CHECK_NO_THROW(OntologyCoreType::extractUIDs(entityVector,uidSet1));
      CHECK(uidSet1.size()==2);
      CHECK(uidSet1.find(spIE2->getUID())!=uidSet1.end());
      CHECK(uidSet1.find(spIE5->getUID())!=uidSet1.end());

      //**@TODO Test für die mapping inference methoden

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace iro
