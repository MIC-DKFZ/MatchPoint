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


#ifndef __IRO_SIMPLE_TEST_HELPER_H
#define __IRO_SIMPLE_TEST_HELPER_H

#include "mapSimpleOntology.h"

namespace iro
{
  namespace testing
  {

    ::iro::scenario::SimpleInformationSpace::Pointer
      generateIS(const String& id);

    ::iro::scenario::SimpleInformationEntity::Pointer
      generateEntity(const String& id, ::iro::scenario::SimpleTransformationInfo::DataRepresentationType dataRep = ::iro::DataRepresentation::Discrete);

    ::iro::scenario::SimpleSemanticCorrelation::Pointer
      generateCorrelation(const std::list<::iro::scenario::SimpleInformationEntity::ConstPointer>& relatedEntities);

    ::iro::scenario::SimpleTransformationInfo::Pointer
      generateTransInfo(const ::iro::String& id, ::iro::scenario::SimpleInformationSpace::ConstPointer movingIS, ::iro::scenario::SimpleInformationSpace::ConstPointer targetIS,::iro::scenario::SimpleProblemStatement::Pointer statement, ::iro::scenario::SimpleTransformationInfo::DataRepresentationType dataRep);

    ::iro::scenario::SimpleRegistrationInfo::Pointer
      generateRegInfo(::iro::scenario::SimpleTransformationInfo::ConstPointer info1, ::iro::scenario::SimpleTransformationInfo::ConstPointer info2);

    ::iro::scenario::SimpleRegPathOption::Pointer
      generateRegPathOption(::iro::scenario::SimpleInformationEntity::ConstPointer ie, ::iro::scenario::SimpleRegistrationPath::ConstPointer path);

    ::iro::scenario::SimpleProblemStatement::Pointer
      generateStatement(const String& name);

    ::iro::scenario::SimpleProblemModel::Pointer
      generateModel(const String& name);

    //checks if in the entity-correlation-look up of the core if a certain entry exists
    bool checkCorrelationEntryExists(::iro::scenario::SimpleInformationEntity::ConstPointer spE, ::iro::scenario::SimpleSemanticCorrelation::ConstPointer spC, const ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>& core);

    //checks if in the entity-correlation-look up of the core if a certain entry exists
    bool checkStatementEntryExists(::iro::scenario::SimpleProblemStatement::ConstPointer spPS, ::iro::scenario::SimpleProblemModel::ConstPointer spPM, const ::iro::scenario::SimpleOntologyCore<::iro::scenario::SimpleOntologyAccessTraits>& core);

    //checks if the both passed paths are equal
    bool checkPath(::iro::scenario::SimpleRegistrationPath::ConstPointer spPath, ::iro::scenario::SimpleRegistrationPath::ConstPointer spRefPath);

    //checks if the both passed options are equal
    bool checkOption(::iro::scenario::SimpleRegPathOption::ConstPointer spOp, ::iro::scenario::SimpleRegPathOption::ConstPointer spRefOp);

    //checks if a option exists in a collection
    bool checkOptionExists(::iro::scenario::SimpleRegPathOption::ConstPointer spOp, ::iro::scenario::SimpleRegPathOptionCollection::ConstPointer spCollection);

    //checks if both passed collections containing the same options.
    bool checkOptionCollection(::iro::scenario::SimpleRegPathOptionCollection::ConstPointer spColl, ::iro::scenario::SimpleRegPathOptionCollection::ConstPointer spColl2);

    /**
     Checks if in an inference result vector a smart pointer to an entity with a certain UID exists.
    */
    template<typename TVector>
    bool existsUIDInInferenceVector(const Result<TVector>& v, const typename TVector::value_type& val)
    {
      bool result = false;
      for(typename TVector::const_iterator pos = v->begin(); pos!=v->end(); ++pos)
      {
        if ((*pos)->getUID()==val->getUID())
        {
          result = true;
          break;
        }
      }
      return result;
    }

    struct OntologyTestFixture
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
      ::iro::scenario::SimpleInformationEntity::Pointer spIEUnknown;
      ::iro::scenario::SimpleInformationEntity::Pointer spIENull;

      //Information spaces
      ::iro::scenario::SimpleInformationSpace::Pointer spIS1;
      ::iro::scenario::SimpleInformationSpace::Pointer spIS2;
      ::iro::scenario::SimpleInformationSpace::Pointer spIS3;
      ::iro::scenario::SimpleInformationSpace::Pointer spIS4;
      ::iro::scenario::SimpleInformationSpace::Pointer spIS5;
      ::iro::scenario::SimpleInformationSpace::Pointer spISUnknown;
      ::iro::scenario::SimpleInformationSpace::Pointer spISNull;
      
      //Problem statements
      ::iro::scenario::SimpleProblemStatement::Pointer spPS1;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS2;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS3;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS4;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS5;
      ::iro::scenario::SimpleProblemStatement::Pointer spPS6;
      ::iro::scenario::SimpleProblemStatement::Pointer spPSUnknown;
      ::iro::scenario::SimpleProblemStatement::Pointer spPSNull;

      //Problem models
      ::iro::scenario::SimpleProblemModel::Pointer spPM1;
      ::iro::scenario::SimpleProblemModel::Pointer spPM1_small;
      ::iro::scenario::SimpleProblemModel::Pointer spPM2;

      ::iro::scenario::SimpleProblemModel::Pointer spPM3;
      ::iro::scenario::SimpleProblemModel::Pointer spPM4;
      ::iro::scenario::SimpleProblemModel::Pointer spPMUnkown;
      ::iro::scenario::SimpleProblemModel::Pointer spPMNull;

      //correlations
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor1_small;
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor1;
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor1_large;
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor2;
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCor3;

      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCorNull;
      ::iro::scenario::SimpleSemanticCorrelation::Pointer spCorUnknown;

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
      ::iro::scenario::SimpleTransformationInfo::Pointer spTransNull;

      //reference path
      ::iro::scenario::SimpleRegistrationPath::Pointer spRPath_1_2_5_3;
      ::iro::scenario::SimpleRegistrationPath::Pointer spRPath_1_2_3;
      ::iro::scenario::SimpleRegistrationPath::Pointer spRPath_1_3;
      ::iro::scenario::SimpleRegistrationPath::Pointer spRPath_1_2_5_3_4;
      ::iro::scenario::SimpleRegistrationPath::Pointer spRPath_1_2_3_4;
      ::iro::scenario::SimpleRegistrationPath::Pointer spRPath_1_3_4;
      ::iro::scenario::SimpleRegistrationPath::Pointer spRPath_4_3;

      //reference options
      //optimal path from IS1 to IS3 with both mappings
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS3_all;
      //optimal path from IS1 to IS3 with continuous mapping
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS3_con;
      //optimal path from IS1 to IS3 with discrete mapping
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS3_dis;
      //optimal path from IS1 to IS3 with arbitrary mapping
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS3_arbitrary;
      //optimal path from IS1 to IS4 with both mappings
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS4_all;
      //optimal path from IS1 to IS4 with discrete mapping
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS4_dis;

      //optimal path from IS1 to IS4 with discrete mapping unde PM2
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS4_dis_PM2;
      //optimal path from IS1 to IS4 with discrete mapping unde PM1
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS4_dis_PM1;

      //optimal path from IS1 to IS3 with continuous mapping under PM1
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS3_con_PM1;
      //optimal path from IS1 to IS3 with continuous mapping under PM2
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_opt_IS1_IS3_con_PM2;

      //all paths from IS1 to IS3
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_IS1_IS3;
      //all paths from IS1 to IS3 under PM1
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_IS1_IS3_PM1;
      //all paths from IS1 to IS3 under PM2
      ::iro::scenario::SimpleRegPathOptionCollection::Pointer spRegOptCol_IS1_IS3_PM2;

      OntologyTestFixture();
    };

  } //namespace testing
} //namespace iro

#endif