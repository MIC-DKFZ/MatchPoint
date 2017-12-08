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


#include "mapSimpleDemoInstancer.h"

#include "litCheckMacros.h"

#include <stdlib.h>

namespace iro
{
  namespace scenario
  {

    ::iro::scenario::SimpleInformationSpace::Pointer generateIS(const String& id)
    {
      ::iro::scenario::SimpleInformationSpace::Pointer spIS(new ::iro::scenario::SimpleInformationSpace);
      spIS->setUID(id);

      return spIS;
    };

    ::iro::scenario::SimpleInformationEntity::Pointer generateEntity(const String& id, ::iro::scenario::SimpleTransformationInfo::DataRepresentationType dataRep = ::iro::DataRepresentation::Discrete)
    {
      ::iro::scenario::SimpleInformationEntity::Pointer spEntity(new ::iro::scenario::SimpleInformationEntity);
      spEntity->setUID(id);
      spEntity->setDataRepresentation(dataRep);

      return spEntity;
    };

    ::iro::scenario::SimpleSemanticCorrelation::Pointer generateCorrelation(const std::list<::iro::scenario::SimpleInformationEntity::ConstPointer>& relatedEntities)
    {
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCorr(new ::iro::scenario::SimpleSemanticCorrelation);

      for (std::list<::iro::scenario::SimpleInformationEntity::ConstPointer>::const_iterator pos = relatedEntities.begin(); pos!=relatedEntities.end(); ++pos)
      {
        spCorr->addCorrelatedEntity(*pos);
      }

      return spCorr;
    };

    ::iro::scenario::SimpleTransformationInfo::Pointer generateTransInfo(const ::iro::String& id, ::iro::scenario::SimpleInformationSpace::ConstPointer movingIS, ::iro::scenario::SimpleInformationSpace::ConstPointer targetIS,::iro::scenario::SimpleProblemStatement::Pointer statement, ::iro::scenario::SimpleTransformationInfo::DataRepresentationType dataRep)
    {
      ::iro::scenario::SimpleTransformationInfo::Pointer spInfo(new ::iro::scenario::SimpleTransformationInfo);
      spInfo->setUID(id);
      spInfo->setMovingIS(movingIS);
      spInfo->setTargetIS(targetIS);
      spInfo->setAssociatedProblemStatement(statement);
      spInfo->setSupportedDataRepresentation(dataRep);

      return spInfo;
    };

    ::iro::scenario::SimpleProblemStatement::Pointer generateStatement(const String& name)
    {
      ::iro::scenario::SimpleProblemStatement::Pointer spStat(new ::iro::scenario::SimpleProblemStatement);
      spStat->setName(name);

      return spStat;
    };

    ::iro::scenario::SimpleProblemModel::Pointer generateModel(const String& name)
    {
      ::iro::scenario::SimpleProblemModel::Pointer spModel(new ::iro::scenario::SimpleProblemModel);
      spModel->setName(name);

      return spModel;
    };

    struct OntologyFixture
    {
      //entities
      ::iro::scenario::SimpleInformationEntity::Pointer spIE1;
      ::iro::scenario::SimpleInformationEntity::Pointer spIE2;
      ::iro::scenario::SimpleInformationEntity::Pointer spIE3;
      ::iro::scenario::SimpleInformationEntity::Pointer spIE4;
      ::iro::scenario::SimpleInformationEntity::Pointer spIE5;
      ::iro::scenario::SimpleInformationEntity::Pointer spIE6;
      ::iro::scenario::SimpleInformationEntity::Pointer spIE7;
      ::iro::scenario::SimpleInformationEntity::Pointer spIE8;

      //Information spaces
      ::iro::scenario::SimpleInformationSpace::Pointer spIS1;
      ::iro::scenario::SimpleInformationSpace::Pointer spIS2;
      ::iro::scenario::SimpleInformationSpace::Pointer spIS3;
      ::iro::scenario::SimpleInformationSpace::Pointer spIS4;
      ::iro::scenario::SimpleInformationSpace::Pointer spIS5;
      
      //Problem statements
      ::iro::scenario::SimpleProblemStatement::Pointer spPS1;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS2;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS3;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS4;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS5;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS6;

      //Problem models
      ::iro::scenario::SimpleProblemModel::Pointer spPM1;
      ::iro::scenario::SimpleProblemModel::Pointer spPM2;
      ::iro::scenario::SimpleProblemModel::Pointer spPM3;
      ::iro::scenario::SimpleProblemModel::Pointer spPM4;

      //correlations
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor1;
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor2;
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor3;

      //transformations

      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans1_2;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans2_3;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans3_4;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans4_3;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans1_2d;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans3_4d;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans1_3d;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans2_5;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans2_5d;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans5_3;
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans5_3d;

      OntologyFixture();
    };


    OntologyFixture::
      OntologyFixture()
    {
      //entities
      spIE1 = generateEntity("e1");
      spIE2 = generateEntity("e2");
      spIE3 = generateEntity("e3");
      spIE4 = generateEntity("e4");
      spIE5 = generateEntity("e5");
      spIE6 = generateEntity("e6");
      spIE7 = generateEntity("e7");
      spIE8 = generateEntity("e8",DataRepresentation::Continuous);

      //Information spaces
      spIS1 = generateIS("IS 1");
      spIS2 = generateIS("IS 2");
      spIS3 = generateIS("IS 3");
      spIS4 = generateIS("IS 4");
      spIS5 = generateIS("IS 5");
      
      //Problem statements
      spPS1 = generateStatement("PS 1");
      spPS2 = generateStatement("PS 2");
      spPS3 = generateStatement("PS 3");
      spPS4 = generateStatement("PS 4");
      spPS5 = generateStatement("PS 5");
      spPS6 = generateStatement("PS 6");

      //Problem models
      spPM1 = generateModel("PM 1");
      spPM1->addStatement(spPS1);
      spPM1->addStatement(spPS2);

      spPM2 = generateModel("PM 2");
      spPM2->addStatement(spPS1);
      spPM2->addStatement(spPS3);
      spPM2->addStatement(spPS4);

      spPM3 = generateModel("PM 3");
      spPM3->addStatement(spPS5);

      spPM4 = generateModel("PM 4");

      //correlations
      typedef std::list<::iro::scenario::SimpleInformationEntity::ConstPointer> IEListType;

      IEListType ieList1;
      ieList1.push_back(spIE1);
      ieList1.push_back(spIE2);
      ieList1.push_back(spIE3);
      ieList1.push_back(spIE5);
      IEListType ieList2;
      ieList2.push_back(spIE3);
      ieList2.push_back(spIE4);
      ieList2.push_back(spIE5);
      IEListType ieList3;
      ieList3.push_back(spIE2);
      ieList3.push_back(spIE7);

      spCor1 = generateCorrelation(ieList1);
      spCor2 = generateCorrelation(ieList2);
      spCor3 = generateCorrelation(ieList3);

      //transformations

      spTrans1_2 = generateTransInfo("1->2",spIS1,spIS2,spPS1, ::iro::DataRepresentation::Continuous);
      spTrans2_3 = generateTransInfo("2->3",spIS2,spIS3,spPS3, ::iro::DataRepresentation::Continuous);
      spTrans3_4 = generateTransInfo("3->4",spIS3,spIS4,spPS4, ::iro::DataRepresentation::Continuous);
      spTrans4_3 = generateTransInfo("4->3",spIS4,spIS3,spPS2, ::iro::DataRepresentation::Continuous);
      spTrans1_2d = generateTransInfo("1->d2",spIS1,spIS2,spPS1, ::iro::DataRepresentation::Discrete);
      spTrans3_4d = generateTransInfo("3->d4",spIS3,spIS4,spPS4, ::iro::DataRepresentation::Discrete);
      spTrans1_3d = generateTransInfo("1->d3",spIS1,spIS3,spPS3, ::iro::DataRepresentation::Discrete);
      spTrans2_5 = generateTransInfo("2->5",spIS2,spIS5,spPS2, ::iro::DataRepresentation::Continuous);
      spTrans2_5d = generateTransInfo("2->d5",spIS2,spIS5,spPS2, ::iro::DataRepresentation::Discrete);
      spTrans5_3 = generateTransInfo("5->3",spIS5,spIS3,spPS1, ::iro::DataRepresentation::Continuous);
      spTrans5_3d = generateTransInfo("5->d3",spIS5,spIS3,spPS1, ::iro::DataRepresentation::Discrete);
      spTrans3_4->setFOVScope(::iro::FOVScope::Global);
      spTrans3_4d->setFOVScope(::iro::FOVScope::Global);
      spTrans1_3d->setFOVScope(::iro::FOVScope::Global);
    };

    void setupSimpleDemoOntoloty(SimpleOntology::Pointer ontology)
    {
      OntologyFixture fixture;
      ontology->reset();

      ontology->defineInformationSpace(fixture.spIS1);
      ontology->defineInformationSpace(fixture.spIS2);
      ontology->defineInformationSpace(fixture.spIS3);
      ontology->defineInformationSpace(fixture.spIS4);
      ontology->defineInformationSpace(fixture.spIS5);

      ontology->defineEntity(fixture.spIE1, fixture.spIS1);
      ontology->defineEntity(fixture.spIE2, fixture.spIS2);
      ontology->defineEntity(fixture.spIE3, fixture.spIS3);
      ontology->defineEntity(fixture.spIE4, fixture.spIS1);
      ontology->defineEntity(fixture.spIE5, fixture.spIS2);
      ontology->defineEntity(fixture.spIE6, fixture.spIS4);
      ontology->defineEntity(fixture.spIE7, fixture.spIS3);
      ontology->defineEntity(fixture.spIE8, fixture.spIS2);

      ontology->defineSemanticCorrelation(fixture.spCor1);
      ontology->defineSemanticCorrelation(fixture.spCor2);
      ontology->defineSemanticCorrelation(fixture.spCor3);

      ontology->defineProblemStatement(fixture.spPS1);
      ontology->defineProblemStatement(fixture.spPS2);
      ontology->defineProblemStatement(fixture.spPS3);
      ontology->defineProblemStatement(fixture.spPS4);
      ontology->defineProblemStatement(fixture.spPS5);
      ontology->defineProblemStatement(fixture.spPS6);

      ontology->defineProblemModel(fixture.spPM1);
      ontology->defineProblemModel(fixture.spPM2);
      ontology->defineProblemModel(fixture.spPM3);
      ontology->defineProblemModel(fixture.spPM4);

      ontology->defineTransformation(fixture.spTrans1_2);
      ontology->defineTransformation(fixture.spTrans2_3);
      ontology->defineTransformation(fixture.spTrans3_4);
      ontology->defineTransformation(fixture.spTrans4_3);
      ontology->defineTransformation(fixture.spTrans1_2d);
      ontology->defineTransformation(fixture.spTrans3_4d);
      ontology->defineTransformation(fixture.spTrans2_5);
      ontology->defineTransformation(fixture.spTrans1_3d);
      ontology->defineTransformation(fixture.spTrans2_5d);
      ontology->defineTransformation(fixture.spTrans5_3);
      ontology->defineTransformation(fixture.spTrans5_3d);
    };

    struct SimpleInstantiationHelper
    {

    };



  } //namespace scenario
} //namespace iro
