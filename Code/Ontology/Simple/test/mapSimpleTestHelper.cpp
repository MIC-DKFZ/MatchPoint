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


#include "mapSimpleTestHelper.h"
#include "mapSimpleOntologyCore.h"

#include "litCheckMacros.h"

#include <stdlib.h>

namespace iro
{
  namespace testing
  {

    OntologyTestFixture::
      OntologyTestFixture()
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
      spIEUnknown = generateEntity("unknown");
      spIENull = ::iro::scenario::SimpleInformationEntity::Pointer();

      //Information spaces
      spIS1 = generateIS("IS 1");
      spIS2 = generateIS("IS 2");
      spIS3 = generateIS("IS 3");
      spIS4 = generateIS("IS 4");
      spIS5 = generateIS("IS 5");
      spISUnknown = generateIS("IS unknown");
      spISNull = ::iro::scenario::SimpleInformationSpace::Pointer();
      
      //Problem statements
      spPS1 = generateStatement("PS 1");
      spPS2 = generateStatement("PS 2");
      spPS3 = generateStatement("PS 3");
      spPS4 = generateStatement("PS 4");
      spPS5 = generateStatement("PS 5");
      spPS6 = generateStatement("PS 6");
      spPSUnknown = generateStatement("PS unkown");
      spPSNull = ::iro::scenario::SimpleProblemStatement::Pointer();

      //Problem models
      spPM1 = generateModel("PM 1");
      spPM1->addStatement(spPS1);
      spPM1_small = spPM1->clone();
      spPM1->addStatement(spPS2);

      spPM2 = generateModel("PM 2");
      spPM2->addStatement(spPS1);
      spPM2->addStatement(spPS3);
      spPM2->addStatement(spPS4);

      spPM3 = generateModel("PM 3");
      spPM3->addStatement(spPS5);

      spPM4 = generateModel("PM 4");

      spPMUnkown = generateModel("PM unkown");
      spPMNull = ::iro::scenario::SimpleProblemModel::Pointer();

      //correlations
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

      spCor1_small = generateCorrelation(ieList1);
      spCor2 = generateCorrelation(ieList2);

      spCor1 = spCor1_small->clone();
      spCor1->addCorrelatedEntity(spIE5);
      spCor1_large = spCor1_small->clone();
      spCor1_large->addCorrelatedEntity(spIE5);
      spCor1_large->addCorrelatedEntity(spIE6);
      spCor1_large->addCorrelatedEntity(spIE7);

      spCor3 = generateCorrelation(ieList3);

      spCorNull = ::iro::scenario::SimpleSemanticCorrelation::Pointer();
      spCorUnknown = generateCorrelation(ieList3);

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
      spTransNull = ::iro::scenario::SimpleTransformationInfo::Pointer();

      //reference paths
      spRPath_1_2_5_3 = ::iro::scenario::SimpleRegistrationPath::Pointer(new ::iro::scenario::SimpleRegistrationPath);
      spRPath_1_2_3 = ::iro::scenario::SimpleRegistrationPath::Pointer(new ::iro::scenario::SimpleRegistrationPath);
      spRPath_1_3 = ::iro::scenario::SimpleRegistrationPath::Pointer(new ::iro::scenario::SimpleRegistrationPath);
      spRPath_1_2_5_3_4 = ::iro::scenario::SimpleRegistrationPath::Pointer(new ::iro::scenario::SimpleRegistrationPath);
      spRPath_1_2_3_4 = ::iro::scenario::SimpleRegistrationPath::Pointer(new ::iro::scenario::SimpleRegistrationPath);
      spRPath_1_3_4 = ::iro::scenario::SimpleRegistrationPath::Pointer(new ::iro::scenario::SimpleRegistrationPath);
      spRPath_4_3 = ::iro::scenario::SimpleRegistrationPath::Pointer(new ::iro::scenario::SimpleRegistrationPath);

      spRPath_1_2_5_3->appendElement(generateRegInfo(spTrans1_2,spTrans1_2d));
      spRPath_1_2_5_3->appendElement(generateRegInfo(spTrans2_5,spTrans2_5d));
      spRPath_1_2_5_3->appendElement(generateRegInfo(spTrans5_3,spTrans5_3d));

      spRPath_1_2_3->appendElement(generateRegInfo(spTrans1_2,spTrans1_2d));
      spRPath_1_2_3->appendElement(generateRegInfo(spTrans2_3,spTransNull));

      spRPath_1_3->appendElement(generateRegInfo(spTransNull,spTrans1_3d));

      spRPath_1_2_5_3_4->appendElement(generateRegInfo(spTrans1_2,spTrans1_2d));
      spRPath_1_2_5_3_4->appendElement(generateRegInfo(spTrans2_5,spTrans2_5d));
      spRPath_1_2_5_3_4->appendElement(generateRegInfo(spTrans5_3,spTrans5_3d));
      spRPath_1_2_5_3_4->appendElement(generateRegInfo(spTrans3_4,spTrans3_4d));

      spRPath_1_2_3_4->appendElement(generateRegInfo(spTrans1_2,spTrans1_2d));
      spRPath_1_2_3_4->appendElement(generateRegInfo(spTrans2_3,spTransNull));
      spRPath_1_2_3_4->appendElement(generateRegInfo(spTrans3_4,spTrans3_4d));

      spRPath_1_3_4->appendElement(generateRegInfo(spTransNull,spTrans1_3d));
      spRPath_1_3_4->appendElement(generateRegInfo(spTrans3_4,spTrans3_4d));

      spRPath_4_3->appendElement(generateRegInfo(spTrans4_3,spTransNull));

      //reference options
      //optimal path from IS1 to IS3 with both mappings
      spRegOptCol_opt_IS1_IS3_all = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS3_all->addOption(generateRegPathOption(spIENull,spRPath_1_2_5_3));
      //optimal path from IS1 to IS3 with continuous mapping
      spRegOptCol_opt_IS1_IS3_con = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS3_con->addOption(generateRegPathOption(spIENull,spRPath_1_2_3));
      //optimal path from IS1 to IS3 with discrete mapping
      spRegOptCol_opt_IS1_IS3_dis = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS3_dis->addOption(generateRegPathOption(spIENull,spRPath_1_3));
      //optimal path from IS1 to IS3 with arbitrary mapping
      spRegOptCol_opt_IS1_IS3_arbitrary = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS3_arbitrary->addOption(generateRegPathOption(spIENull,spRPath_1_3));
      //optimal path from IS1 to IS4 with both mappings
      spRegOptCol_opt_IS1_IS4_all = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS4_all->addOption(generateRegPathOption(spIENull,spRPath_1_2_5_3_4));
      //optimal path from IS1 to IS4 with discrete mapping
      spRegOptCol_opt_IS1_IS4_dis = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS4_dis->addOption(generateRegPathOption(spIENull,spRPath_1_3_4));

      //optimal path from IS1 to IS4 with discrete mapping unde PM2
      spRegOptCol_opt_IS1_IS4_dis_PM2 = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS4_dis_PM2->addOption(generateRegPathOption(spIENull,spRPath_1_3_4));
      //optimal path from IS1 to IS4 with discrete mapping unde PM1
      spRegOptCol_opt_IS1_IS4_dis_PM1 = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS4_dis_PM1->addOption(generateRegPathOption(spIENull,spRPath_1_2_5_3_4));

      //optimal path from IS1 to IS3 with continuous mapping under PM1
      spRegOptCol_opt_IS1_IS3_con_PM1 = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS3_con_PM1->addOption(generateRegPathOption(spIENull,spRPath_1_2_5_3));
      //optimal path from IS1 to IS3 with continuous mapping under PM2
      spRegOptCol_opt_IS1_IS3_con_PM2 = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_opt_IS1_IS3_con_PM2->addOption(generateRegPathOption(spIENull,spRPath_1_2_3));

      //all paths from IS1 to IS3
      spRegOptCol_IS1_IS3 = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_IS1_IS3->addOption(generateRegPathOption(spIENull,spRPath_1_2_5_3));
      spRegOptCol_IS1_IS3->addOption(generateRegPathOption(spIENull,spRPath_1_2_3));
      spRegOptCol_IS1_IS3->addOption(generateRegPathOption(spIENull,spRPath_1_3));
      //all paths from IS1 to IS3 under PM1
      spRegOptCol_IS1_IS3_PM1 = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_IS1_IS3_PM1->addOption(generateRegPathOption(spIENull,spRPath_1_2_5_3));
      //all paths from IS1 to IS3 under PM2
      spRegOptCol_IS1_IS3_PM2 = ::iro::scenario::SimpleRegPathOptionCollection::Pointer(new ::iro::scenario::SimpleRegPathOptionCollection);
      spRegOptCol_IS1_IS3_PM2->addOption(generateRegPathOption(spIENull,spRPath_1_2_3));
      spRegOptCol_IS1_IS3_PM2->addOption(generateRegPathOption(spIENull,spRPath_1_3));

    };


    ::iro::scenario::SimpleInformationSpace::Pointer generateIS(const String& id)
    {
      ::iro::scenario::SimpleInformationSpace::Pointer spIS(new ::iro::scenario::SimpleInformationSpace);
      spIS->setUID(id);

      return spIS;
    };

    ::iro::scenario::SimpleInformationEntity::Pointer generateEntity(const String& id, ::iro::scenario::SimpleTransformationInfo::DataRepresentationType dataRep)
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

    ::iro::scenario::SimpleRegistrationInfo::Pointer generateRegInfo(::iro::scenario::SimpleTransformationInfo::ConstPointer info1, ::iro::scenario::SimpleTransformationInfo::ConstPointer info2)
    {
      ::iro::scenario::SimpleRegistrationInfo::Pointer spInfo(new ::iro::scenario::SimpleRegistrationInfo);
      spInfo->setTransformations(info1,info2);

      return spInfo;
    };

    ::iro::scenario::SimpleRegPathOption::Pointer
      generateRegPathOption(::iro::scenario::SimpleInformationEntity::ConstPointer ie, ::iro::scenario::SimpleRegistrationPath::ConstPointer path)
    {
      ::iro::scenario::SimpleRegPathOption::Pointer spOpt(new ::iro::scenario::SimpleRegPathOption);
      spOpt->setMovingEntity(ie);
      spOpt->setPath(path);

      return spOpt;
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

    bool checkCorrelationEntryExists(::iro::scenario::SimpleInformationEntity::ConstPointer spE, ::iro::scenario::SimpleSemanticCorrelation::ConstPointer spC, const ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>& core)
    {
      bool result = false;
      typedef std::pair<::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::EntityCorrelationMapType::const_iterator, ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::EntityCorrelationMapType::const_iterator> PairType;

      PairType sourceFindings = core._entity2CorrelationMap.equal_range(spE->getUID());
      
      //got through all source entity correlations
      for (::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::EntityCorrelationMapType::const_iterator sourcePos = sourceFindings.first; sourcePos!= sourceFindings.second; ++sourcePos)
      {
          if (sourcePos->second == spC->getUID())
          { 
            result = true;
            break;
          }
      }

      return result;
    }

    bool checkStatementEntryExists(::iro::scenario::SimpleProblemStatement::ConstPointer spPS, ::iro::scenario::SimpleProblemModel::ConstPointer spPM, const ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>& core)
    {
      bool result = false;
      typedef std::pair<::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::StatementModelMapType::const_iterator, ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::StatementModelMapType::const_iterator> PairType;

      PairType sourceFindings = core._stat2ModelMap.equal_range(spPS->getUID());
      
      //got through all source entity correlations
      for (::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>::StatementModelMapType::const_iterator sourcePos = sourceFindings.first; sourcePos!= sourceFindings.second; ++sourcePos)
      {
          if (sourcePos->second == spPM->getUID())
          { 
            result = true;
            break;
          }
      }

      return result;
    }

    bool checkPath(::iro::scenario::SimpleRegistrationPath::ConstPointer spPath, ::iro::scenario::SimpleRegistrationPath::ConstPointer spRefPath)
    {
      bool result = false;

      if (spPath->size() != spRefPath->size()) return result;

      ::iro::scenario::SimpleRegistrationPath::ConstPathElementIterator pos = spPath->getBegin();
      ::iro::scenario::SimpleRegistrationPath::ConstPathElementIterator posRef = spRefPath->getBegin();
      
      while (pos != spPath->getEnd())
      {
        if ((*pos)->getContinuousTransformation() && (*posRef)->getContinuousTransformation())
        {
          if ((*pos)->getContinuousTransformation()->getUID() != (*posRef)->getContinuousTransformation()->getUID())
          {
            return result;
          }
        }
        else if (!((*pos)->getContinuousTransformation()) && !((*posRef)->getContinuousTransformation()))
        { //it is also fine but nothing to check
        }
        else return result;

        ++pos;
        ++posRef;
      }

      result = true;
      return result;
    };

    bool checkOption(::iro::scenario::SimpleRegPathOption::ConstPointer spOp, ::iro::scenario::SimpleRegPathOption::ConstPointer spRefOp)
    {
      if (spOp->getMovingEntity() != spRefOp->getMovingEntity())
      {
        return false;
      }

      return checkPath(spOp->getPath(), spRefOp->getPath());
    };

    bool checkOptionExists(::iro::scenario::SimpleRegPathOption::ConstPointer spOp, ::iro::scenario::SimpleRegPathOptionCollection::ConstPointer spCollection)
    {
      bool result = false;

      for (::iro::scenario::SimpleRegPathOptionCollection::ConstOptionIterator pos = spCollection->getBegin(); pos!=spCollection->getEnd(); ++pos)
      {
        if (checkOption(spOp,*pos))
        {
          result = true;
          break;
        }
      }

      return result;
    };

    //checks if both passed collections containing the same options.
    bool checkOptionCollection(::iro::scenario::SimpleRegPathOptionCollection::ConstPointer spColl, ::iro::scenario::SimpleRegPathOptionCollection::ConstPointer spColl2)
    {
      if (spColl->getOptionCount() != spColl2->getOptionCount()) return false;

      bool result = true;

      for (::iro::scenario::SimpleRegPathOptionCollection::ConstOptionIterator pos = spColl->getBegin(); pos!=spColl->getEnd(); ++pos)
      {
        if (!checkOptionExists(*pos,spColl2))
        {
          result = false;
          break;
        }
      }

      return result;
    };

  } //namespace testing
} //namespace iro
