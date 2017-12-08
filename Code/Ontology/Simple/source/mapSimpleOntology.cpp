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
#include "mapISCacheKey.h"


namespace iro
{
  namespace scenario
  {

    SimpleOntology::
      ~SimpleOntology()
    {

    };

    SimpleOntology::
      SimpleOntology()
    {
      _spCore = std::shared_ptr<OntologyCoreType>(new OntologyCoreType);
    };

    void 
      SimpleOntology::
      reset()
    {
      OntologyRevisionTag revision = _spCore->_revision;

      _spCore = std::shared_ptr<OntologyCoreType>(new OntologyCoreType);
      _spCore->_revision = ++revision;
    };

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    // Entity Inference
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////

    Result<SimpleOntology::ConstInfSpacePointer>
      SimpleOntology::
      doGetContainingIS(InfEntityInferencePointer pEntity) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstInfSpacePointer result;

      /*INTERNAL-TODO Consistency rule should be added: Entity seems to have no IS*/
      OntologyCoreType::EntityISMapType::const_iterator pos = _spCore->_entity2ISMap.find(pEntity->getUID());
      if (pos !=  _spCore->_entity2ISMap.end())
      { //there is an entry in the look up map
        OntologyCoreType::ISMapType::const_iterator posIS = _spCore->_ISMap.find(pos->second);

        /*INTERNAL-TODO Consistency rule should be added: look up map is inconsistent*/
        if (posIS !=  _spCore->_ISMap.end())
        { //there is the fitting IS
          result = posIS->second;
        }
      }

      return Result<ConstInfSpacePointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstInfEntityVectorType>
      SimpleOntology::
      doGetEntitiesInIS(InfSpaceInferencePointer pIS) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstInfEntityVectorType result;

      for (OntologyCoreType::EntityISMapType::const_iterator pos = _spCore->_entity2ISMap.begin(); pos !=  _spCore->_entity2ISMap.end(); ++pos)
      { //search the look up map
        if (pos->second == pIS->getUID())
        { //it is an entity in the IS -> get entity
          OntologyCoreType::EntityMapType::const_iterator posEntity = _spCore->_entityMap.find(pos->first);

          /*INTERNAL-TODO Consistency rule should be added: look up map is inconsistent*/
          if (posEntity !=  _spCore->_entityMap.end())
          { //the entity realy exists so add it.
            result.push_back(posEntity->second);
          }
        }
      }

      return Result<ConstInfEntityVectorType>(result, _spCore->_revision);
    };

    Result<bool>
      SimpleOntology::
      doCheckForSameIS(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      bool result = false;

      /*INTERNAL-TODO Consistency rule should be added: Entity seems to have no IS*/
      OntologyCoreType::EntityISMapType::const_iterator pos1 = _spCore->_entity2ISMap.find(pEntity1->getUID());
      OntologyCoreType::EntityISMapType::const_iterator pos2 = _spCore->_entity2ISMap.find(pEntity2->getUID());

      if ((pos1 !=  _spCore->_entity2ISMap.end()) &&
        (pos2 !=  _spCore->_entity2ISMap.end()))
      { 
        result = pos1->second == pos2->second;
      }

      return Result<bool>(result, _spCore->_revision);
    };

    Result<bool>
      SimpleOntology::
      doCheckForSameIS(const ConstInfEntityVectorType& entities) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      bool result = true;

      if (!entities.empty())
      {

        ConstInfEntityVectorType::const_iterator firstPos = entities.begin();
        OntologyCoreType::EntityISMapType::const_iterator posLook1 = _spCore->_entity2ISMap.find((*firstPos)->getUID());

        if (posLook1 != _spCore->_entity2ISMap.end())
        { // first element exists in an kown IS

          ConstInfEntityVectorType::const_iterator pos = entities.begin()+1;

          while( pos !=  entities.end())
          {
            OntologyCoreType::EntityISMapType::const_iterator posLook2 = _spCore->_entity2ISMap.find((*pos)->getUID());

            if (posLook1 !=  _spCore->_entity2ISMap.end())
            { // second element exists in an kown IS
              result = posLook2->second == posLook1->second;

              if (!result) break; //at least one element doesn't match, we can stop
            }

            ++pos;
          }
        }
        else
        {
          result = false;
        }
      }

      return Result<bool>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstInfEntityVectorType> SimpleOntology::doGetEntitiesWithSemanticCorrelations(InfEntityInferencePointer pEntity) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstInfEntityVectorType result;

      //get the correlation
      OntologyCoreType::ConstCorrelationMapType corrMap;
      _spCore->getCorrelations(corrMap, pEntity->getUID());

      //get the entities
      OntologyCoreType::EntityUIDSetType uids;
      uids.insert(pEntity->getUID());
      OntologyCoreType::ConstEntityMapType entityMap = OntologyCoreType::getEntitiesByCorrelations(corrMap,uids);

      //convert entity map into result
      OntologyCoreType::extracValuesFromMap(entityMap, result);

      return Result<SimpleOntology::ConstInfEntityVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstInfEntityVectorType> SimpleOntology::doGetSemanticallyCorrelatedEntities(InfSpaceInferencePointer pSourceIS, InfSpaceInferencePointer pCorrelatedIS) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstInfEntityVectorType result;

      //get entities
      ConstInfEntityVectorType entitiesInIS1 = getEntitiesInIS(pSourceIS);
      ConstInfEntityVectorType entitiesInIS2 = getEntitiesInIS(pCorrelatedIS);

      //get their UIDs
      OntologyCoreType::EntityUIDSetType uidsInIS1;
      OntologyCoreType::extractUIDs(entitiesInIS1,uidsInIS1);

      OntologyCoreType::EntityUIDSetType uidsInIS2;
      OntologyCoreType::extractUIDs(entitiesInIS2,uidsInIS2);

      //get the correlation
      OntologyCoreType::ConstCorrelationMapType corrMap;
      _spCore->getCorrelations(corrMap, uidsInIS1, uidsInIS2);

      //get the entities
      OntologyCoreType::ConstEntityMapType entityMap = OntologyCoreType::getEntitiesByCorrelations(corrMap,uidsInIS1,false);

      //convert entity map into result
      OntologyCoreType::extracValuesFromMap(entityMap, result);

      return Result<SimpleOntology::ConstInfEntityVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstCorrelationVectorType> SimpleOntology::doGetSemanticCorrelations(InfSpaceInferencePointer pIS1, InfSpaceInferencePointer pIS2) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstCorrelationVectorType result;

      //get entities
      ConstInfEntityVectorType entitiesInIS1 = getEntitiesInIS(pIS1);
      ConstInfEntityVectorType entitiesInIS2 = getEntitiesInIS(pIS2);

      //get their UIDs
      OntologyCoreType::EntityUIDSetType uidsInIS1;
      OntologyCoreType::extractUIDs(entitiesInIS1,uidsInIS1);

      OntologyCoreType::EntityUIDSetType uidsInIS2;
      OntologyCoreType::extractUIDs(entitiesInIS2,uidsInIS2);

      //get the correlation
      OntologyCoreType::ConstCorrelationMapType corrMap;
      _spCore->getCorrelations(corrMap, uidsInIS1,uidsInIS2);

      //convert corr map into result
      OntologyCoreType::extracValuesFromMap(corrMap, result);

      return Result<SimpleOntology::ConstCorrelationVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstCorrelationVectorType> SimpleOntology::doGetSemanticCorrelations(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pIS) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstCorrelationVectorType result;

      //get entities
      ConstInfEntityVectorType entitiesInIS = getEntitiesInIS(pIS);

      //get their UIDs
      OntologyCoreType::EntityUIDSetType uidsInIS1;
      uidsInIS1.insert(pEntity->getUID());

      OntologyCoreType::EntityUIDSetType uidsInIS2;
      OntologyCoreType::extractUIDs(entitiesInIS,uidsInIS2);

      //get the correlation
      OntologyCoreType::ConstCorrelationMapType corrMap;
      _spCore->getCorrelations(corrMap, uidsInIS1,uidsInIS2);

      //convert corr map into result
      OntologyCoreType::extracValuesFromMap(corrMap, result);

      return Result<SimpleOntology::ConstCorrelationVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstCorrelationVectorType> SimpleOntology::doGetSemanticCorrelations(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstCorrelationVectorType result;

      //get the correlation
      OntologyCoreType::ConstCorrelationMapType corrMap;
      _spCore->getCorrelations(corrMap, pEntity1->getUID(),pEntity2->getUID());

      //convert corr map into result
      OntologyCoreType::extracValuesFromMap(corrMap, result);

      return Result<SimpleOntology::ConstCorrelationVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::DataRepresentationType> SimpleOntology::doGetDataRepresentationType(InfEntityInferencePointer pEntity) const
    {
      assert(_spCore);

      return Result<SimpleOntology::DataRepresentationType>(pEntity->getDataRepresentation(), _spCore->_revision);
    };

    Result<bool> SimpleOntology::doHasDiscreteDataRepresentation(InfEntityInferencePointer pEntity) const
    {
      assert(_spCore);

      return Result<bool>(pEntity->getDataRepresentation()==DataRepresentation::Discrete, _spCore->_revision);
    };

    Result<bool>
      SimpleOntology::
      doHasContinuousDataRepresentation(InfEntityInferencePointer pEntity) const
    {
      assert(_spCore);

      return Result<bool>(pEntity->getDataRepresentation()==DataRepresentation::Continuous, _spCore->_revision);
    };

    Result<SimpleOntology::ConstInfEntityVectorType>
      SimpleOntology::
      doGetEntities() const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstInfEntityVectorType result;

      //convert entity map into result
      OntologyCoreType::extracValuesFromMap(_spCore->_entityMap, result);

      return Result<SimpleOntology::ConstInfEntityVectorType>(result, _spCore->_revision);

    };

    Result<SimpleOntology::ConstInfSpaceVectorType>
      SimpleOntology::
      doGetInformationSpaces() const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstInfSpaceVectorType result;

      //convert is map into result
      OntologyCoreType::extracValuesFromMap(_spCore->_ISMap, result);

      return Result<SimpleOntology::ConstInfSpaceVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstCorrelationVectorType>
      SimpleOntology::
      doGetSemanticCorrelations() const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstCorrelationVectorType result;

      //convert corr map into result
      OntologyCoreType::extracValuesFromMap(_spCore->_correlationMap, result);

      return Result<SimpleOntology::ConstCorrelationVectorType>(result, _spCore->_revision);
    };


    Result<SimpleOntology::ConstInfEntityPointer>
      SimpleOntology::
      doActualize(InfEntityInferencePointer pEntity) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstInfEntityPointer result;

      OntologyCoreType::EntityMapType::const_iterator pos = _spCore->_entityMap.find(pEntity->getUID());
      if (pos !=  _spCore->_entityMap.end())
      { 
        result = pos->second;
      }

      return Result<SimpleOntology::ConstInfEntityPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstInfSpacePointer>
      SimpleOntology::
      doActualize(InfSpaceInferencePointer pIS) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstInfSpacePointer result;

      OntologyCoreType::ISMapType::const_iterator pos = _spCore->_ISMap.find(pIS->getUID());
      if (pos !=  _spCore->_ISMap.end())
      { 
        result = pos->second;
      }

      return Result<SimpleOntology::ConstInfSpacePointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstCorrelationPointer>
      SimpleOntology::
      doActualize(CorrelationInferencePointer corr) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstCorrelationPointer result;

      OntologyCoreType::CorrelationMapType::const_iterator pos = _spCore->_correlationMap.find(corr->getUID());
      if (pos !=  _spCore->_correlationMap.end())
      { 
        result = pos->second;
      }

      return Result<SimpleOntology::ConstCorrelationPointer>(result, _spCore->_revision);
    };

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    // Entity Integration
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////

    Result<SimpleOntology::ConstInfEntityPointer>
      SimpleOntology::
      doDefineEntity(InfEntityInferencePointer pNewEntity, InfSpaceInferencePointer pContainingIS)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstInfEntityPointer result;

      /*INTERNAL-TODO Consistency rule should be added: Entity already exists*/
      OntologyCoreType::EntityMapType::const_iterator pos = _spCore->_entityMap.find(pNewEntity->getUID());
      if (pos !=  _spCore->_entityMap.end())
      { //the entity is already there, silent drop in Simple implementierung
        result = pos->second;
      }
      else
      { // add the clone
        InfEntityType::Pointer spNew = pNewEntity->clone();
        _spCore->_entityMap[spNew->getUID()] = spNew;
        result = spNew;
        _spCore->_entity2ISMap[spNew->getUID()] = pContainingIS->getUID();
        _spCore->notifyChange();
      }

      return Result<SimpleOntology::ConstInfEntityPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstInfEntityPointer>
      SimpleOntology::
      doStoreEntity(InfEntityInferencePointer pEntity)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstInfEntityPointer result;

      /*INTERNAL-TODO Consistency rule should be added: Entity does not exist*/
      OntologyCoreType::EntityMapType::const_iterator pos = _spCore->_entityMap.find(pEntity->getUID());
      if (pos !=  _spCore->_entityMap.end())
      { //update entity
        pos->second->setDataRepresentation(pEntity->getDataRepresentation());
        result =  pos->second;
        //TODO check: ist eigentlich nicht n�tig, da hier nur werte ge�ndert
        //werden und referenzen g�ltig bleiben. Des Weiteren wird bei der correlation
        //ja validateForCommit aufgerufen um sicher zustellen, dass wenn sie abgespeichert oder
        //ge�ndert wird, alles auf diese referenz umgebogen wird.
        //_spCore->actualizeEntityInCorrelations(result->getUID());
      }
      else
      { // Simple implementation: silent add
        InfEntityType::Pointer spNew = pEntity->clone();
        _spCore->_entityMap[spNew->getUID()] = spNew;
        result = spNew;
      }
      _spCore->notifyChange();

      return Result<SimpleOntology::ConstInfEntityPointer>(result, _spCore->_revision);
    };

    SimpleOntology::EntityDeleteReturnType
      SimpleOntology::
      doDeleteEntity(InfEntityInferencePointer pEntity)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      EntityDeleteReturnType result = true;

      //remove from correlations
      _spCore->removeEntityFromCorrelations(pEntity->getUID());

      //remove from lookups
      _spCore->_entity2ISMap.erase(pEntity->getUID());
      _spCore->_entity2CorrelationMap.erase(pEntity->getUID());

      //remove entity
      if (_spCore->_entityMap.erase(pEntity->getUID()) > 0)
      {
        _spCore->notifyChange();
      }

      return result;
    };

    Result<SimpleOntology::ConstInfSpacePointer>
      SimpleOntology::
      doDefineInformationSpace(InfSpaceInferencePointer pNewIS)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstInfSpacePointer result;

      /*INTERNAL-TODO Consistency rule should be added: is already exists*/
      OntologyCoreType::ISMapType::const_iterator pos = _spCore->_ISMap.find(pNewIS->getUID());
      if (pos !=  _spCore->_ISMap.end())
      { //the is is already there, silent drop in Simple implementierung
        result = pos->second;
      }
      else
      { // add the clone
        InfSpaceType::Pointer spNew = pNewIS->clone();
        _spCore->_ISMap[spNew->getUID()] = spNew;
        _spCore->addVertex(spNew);
        result = spNew;
        _spCore->notifyChange();
      }

      return Result<SimpleOntology::ConstInfSpacePointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstInfSpacePointer>
      SimpleOntology::
      doStoreInformationSpace(InfSpaceInferencePointer pIS)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstInfSpacePointer result;

      /*INTERNAL-TODO Consistency rule should be added: IS does not exist*/
      OntologyCoreType::ISMapType::const_iterator pos = _spCore->_ISMap.find(pIS->getUID());
      if (pos !=  _spCore->_ISMap.end())
      { //update entity
        //no real update because in Simple only has UID
        result =  pos->second;
      }
      else
      { // Simple implementation: silent add
        InfSpaceType::Pointer spNew = pIS->clone();
        _spCore->_ISMap[spNew->getUID()] = spNew;
        _spCore->addVertex(spNew);
        result = spNew;
        _spCore->notifyChange();
      }

      return Result<SimpleOntology::ConstInfSpacePointer>(result, _spCore->_revision);
    };

    SimpleOntology::ISDeleteReturnType
      SimpleOntology::
      doDeleteInformationSpace(InfSpaceInferencePointer pIS)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ISDeleteReturnType result = true;

      //remark: the removel from _entity2ISMap is missing.
      //The Simple implementation was wished to keep simple.
      //the using host will take care to explicitly delete all contained
      //enitities, so no cascading delete is needed

      //remove IS
      if (_spCore->_ISMap.erase(pIS->getUID()) > 0)
      {
        _spCore->deleteVertex(pIS);
        _spCore->notifyChange();
      }

      return result;
    };

    void
      SimpleOntology::
      doSwitchInformationSpace(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pNewIS)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      /*INTERNAL-TODO Consistency rule should be added: entity is relevant*/

      //Simple just wants simple swith. no dependency analyses
      _spCore->_entity2ISMap[pEntity->getUID()] = pNewIS->getUID();

      _spCore->notifyChange();
    };

    Result<SimpleOntology::ConstCorrelationPointer>
      SimpleOntology::
      doDefineSemanticCorrelation(CorrelationInferencePointer pNewCorr)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstCorrelationPointer result;

      /*INTERNAL-TODO Consistency rule should be added: corr already exists*/
      OntologyCoreType::CorrelationMapType::const_iterator pos = _spCore->_correlationMap.find(pNewCorr->getUID());
      if (pos !=  _spCore->_correlationMap.end())
      { //the corr is already there, silent drop in Simple implementierung
        result = pos->second;
      }
      else
      { // add the clone
        CorrelationType::Pointer spNew = pNewCorr->clone();
        if (_spCore->validateForCommit(spNew))
        {
          _spCore->_correlationMap[spNew->getUID()] = spNew;
          result = spNew;
          _spCore->updateEntity2CorrelationMap(spNew);
          _spCore->notifyChange();
        }
        else throw exceptions::UndefinedElement("Cannot define semantic correlation, related entities are not defined in the ontology.");
      }

      return Result<SimpleOntology::ConstCorrelationPointer>(result, _spCore->_revision);
    };


    Result<SimpleOntology::ConstCorrelationPointer>
      SimpleOntology::
      doStoreSemanticCorrelation(CorrelationInferencePointer corr)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstCorrelationPointer result;

      /*INTERNAL-TODO Consistency rule should be added: corr does not exist*/
      CorrelationType::Pointer spNew = corr->clone();
      if (_spCore->validateForCommit(spNew))
      {
        _spCore->_correlationMap[spNew->getUID()] = spNew;
        _spCore->updateEntity2CorrelationMap(spNew);
        result = spNew;
        _spCore->notifyChange();
      }
      else throw exceptions::UndefinedElement("Cannot store semantic correlation, related entities are not defined in the ontology.");


      return Result<SimpleOntology::ConstCorrelationPointer>(result, _spCore->_revision);
    };

    SimpleOntology::CorrelationDeleteReturnType
      SimpleOntology::
      doDeleteSemanticCorrelation(CorrelationInferencePointer corr)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      CorrelationDeleteReturnType result = true;

      bool change = false;

      //remove from lookup
      OntologyCoreType::EntityCorrelationMapType::iterator pos = _spCore->_entity2CorrelationMap.begin();

      while( pos !=  _spCore->_entity2CorrelationMap.end())
      {
        if (pos->second == corr->getUID())
        {
          pos = _spCore->_entity2CorrelationMap.erase(pos);
          change = true;
        }
        else
        {
          ++pos;
        }
      }

      //remove corr
      if (_spCore->_correlationMap.erase(corr->getUID()))
      {
        change = true;
      };

      if (change)
      {
        _spCore->notifyChange();
      }

      return result;
    };

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    // Mapping inference
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////

    Result<SimpleOntology::ConstRegPathOptColPointer>
      SimpleOntology::
      doGetRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      OntologyCoreType::RegistrationGraphType::vertex_descriptor movingV = _spCore->getVertex(pMovingIS);
      OntologyCoreType::RegistrationGraphType::vertex_descriptor targetV = _spCore->getVertex(pFixedIS);

      OntologyCoreType::SimpleSearchMapType searchResult;
      core::simplePathSearch(searchResult, _spCore->_graph, targetV, movingV, DataRepresentationSupport::Arbitrary, pProblemCompliance, OntologyCoreType::EdgeValidatorType());

      ConstRegPathOptColPointer result = _spCore->generateRegCollection(searchResult, ConstInfEntityPointer());

      return Result<ConstRegPathOptColPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstRegPathOptColVectorType>
      SimpleOntology::
      doGetRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstRegPathOptColVectorType result;

      typedef std::map<core::ISCacheKey<SimpleInformationSpaceTraits>, OntologyCoreType::SimpleSearchMapType> SearchCacheType;

      SearchCacheType cache;

      for (ConstInfEntityVectorType::const_iterator pos = movingEntities.begin(); pos != movingEntities.end(); ++pos)
      {
        ConstInfSpacePointer spMIS = getContainingIS(*pos);

        core::ISCacheKey<SimpleInformationSpaceTraits> key(spMIS->getUID(), convertToSupport((*pos)->getDataRepresentation()));
        SearchCacheType::iterator cachePos = cache.find(key);

        if (cachePos == cache.end())
        { //results are missing so generate them;
          OntologyCoreType::RegistrationGraphType::vertex_descriptor movingV = _spCore->getVertex(spMIS);
          OntologyCoreType::RegistrationGraphType::vertex_descriptor targetV = _spCore->getVertex(pFixedIS);

          OntologyCoreType::SimpleSearchMapType searchResult;
          core::simplePathSearch(searchResult, _spCore->_graph, targetV, movingV, convertToSupport((*pos)->getDataRepresentation()),pProblemCompliance , OntologyCoreType::EdgeValidatorType());
          //store results;
          cachePos = cache.insert(::std::make_pair(key,searchResult)).first;
        }

        ConstRegPathOptColPointer spCollection = _spCore->generateRegCollection(cachePos->second, *pos);
        result.push_back(spCollection);
      }

      return Result<ConstRegPathOptColVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstTransPathOptColPointer>
      SimpleOntology::doGetTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      OntologyCoreType::RegistrationGraphType::vertex_descriptor movingV = _spCore->getVertex(pMovingIS);
      OntologyCoreType::RegistrationGraphType::vertex_descriptor targetV = _spCore->getVertex(pFixedIS);

      OntologyCoreType::SimpleSearchMapType searchResult;
      core::simplePathSearch(searchResult, _spCore->_graph, targetV, movingV, DataRepresentationSupport::Arbitrary, pProblemCompliance, OntologyCoreType::EdgeValidatorType());

      ConstTransPathOptColPointer result = _spCore->generateTransCollection(searchResult, ConstInfEntityPointer());

      return Result<ConstTransPathOptColPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstTransPathOptColVectorType>
      SimpleOntology::doGetTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstTransPathOptColVectorType result;

      typedef std::map<core::ISCacheKey<SimpleInformationSpaceTraits>, OntologyCoreType::SimpleSearchMapType> SearchCacheType;

      SearchCacheType cache;

      for (ConstInfEntityVectorType::const_iterator pos = movingEntities.begin(); pos != movingEntities.end(); ++pos)
      {
        ConstInfSpacePointer spMIS = getContainingIS(*pos);

        core::ISCacheKey<SimpleInformationSpaceTraits> key(spMIS->getUID(), convertToSupport((*pos)->getDataRepresentation()));
        SearchCacheType::iterator cachePos = cache.find(key);

        if (cachePos == cache.end())
        { //results are missing so generate them;
          OntologyCoreType::RegistrationGraphType::vertex_descriptor movingV = _spCore->getVertex(spMIS);
          OntologyCoreType::RegistrationGraphType::vertex_descriptor targetV = _spCore->getVertex(pFixedIS);

          OntologyCoreType::SimpleSearchMapType searchResult;
          core::simplePathSearch(searchResult, _spCore->_graph, targetV, movingV, convertToSupport((*pos)->getDataRepresentation()), pProblemCompliance, OntologyCoreType::EdgeValidatorType());
          //store results;
          cachePos = cache.insert(::std::make_pair(key,searchResult)).first;
        }

        ConstTransPathOptColPointer spCollection = _spCore->generateTransCollection(cachePos->second, *pos);
        result.push_back(spCollection);
      }

      return Result<ConstTransPathOptColVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstRegPathOptColPointer>
      SimpleOntology::
      doGetOptimalRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance, const RegPathMetricInterface* pMetric) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      RegPathOptCollectionType::Pointer result(new RegPathOptCollectionType);

      OntologyCoreType::WeightMapType weights = _spCore->generateWeightMap_reg(requiredDataSupport, pProblemCompliance, pMetric);
      OntologyCoreType::PredecessorMapType predecessors;
      OntologyCoreType::EdgeMapType edges;
      _spCore->generateMinimalPathPredecessors(pFixedIS, weights, predecessors, edges);

      RegistrationPathType::Pointer spPath = _spCore->generateRegPath(pMovingIS, pFixedIS, weights, predecessors, edges);

      if (spPath)
      { //there is a path -> so generate an option and add it
        RegPathOptionType::Pointer spOption(new RegPathOptionType);
        spOption->setPath(spPath);
        result->addOption(spOption);
      }

      return Result<ConstRegPathOptColPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstRegPathOptColVectorType>
      SimpleOntology::
      doGetOptimalRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance, const RegPathMetricInterface* pMetric) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstRegPathOptColVectorType result;

      ConstInfEntityVectorType continuousEntities;
      ConstInfEntityVectorType discreteEntities;

      OntologyCoreType::spliteEntitiesByData(movingEntities, continuousEntities, discreteEntities);

      OntologyCoreType::WeightMapType cWeights, dWeights;
      OntologyCoreType::PredecessorMapType cPredecessors, dPredecessors;
      OntologyCoreType::EdgeMapType cEdges, dEdges;

      if (!continuousEntities.empty())
      {
        //get minaml spanning tree for continuous data
        cWeights = _spCore->generateWeightMap_reg(DataRepresentationSupport::Continuous, pProblemCompliance, pMetric);
        _spCore->generateMinimalPathPredecessors(pFixedIS, cWeights, cPredecessors, cEdges);
      }

      if (!discreteEntities.empty())
      {
        //get minaml spanning tree for discrete data
        dWeights = _spCore->generateWeightMap_reg(DataRepresentationSupport::Discrete, pProblemCompliance, pMetric);
        _spCore->generateMinimalPathPredecessors(pFixedIS, dWeights, dPredecessors, dEdges);
      }

      //go throug all entities and get there options
      for (ConstInfEntityVectorType::const_iterator pos = movingEntities.begin(); pos!= movingEntities.end(); ++pos)
      {
        RegPathOptCollectionType::Pointer spOptCol(new RegPathOptCollectionType);
        spOptCol->setMovingEntity(*pos);

        RegistrationPathType::Pointer spPath;

        if ((*pos)->getDataRepresentation()==DataRepresentation::Continuous)
        {
          spPath = _spCore->generateRegPath(getContainingIS(*pos), pFixedIS, cWeights, cPredecessors, cEdges);
        }
        else
        {
          spPath = _spCore->generateRegPath(getContainingIS(*pos), pFixedIS, dWeights, dPredecessors, dEdges);
        }

        if (spPath)
        { //there is a path -> so generate an option and add it
          RegPathOptionType::Pointer spOption(new RegPathOptionType);
          spOption->setPath(spPath);
          spOption->setMovingEntity(*pos);
          spOptCol->addOption(spOption);
        }

        result.push_back(spOptCol);
      }

      return Result<ConstRegPathOptColVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstTransPathOptColPointer>
      SimpleOntology::
      doGetOptimalTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance, const TransPathMetricInterface* pMetric) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      TransPathOptCollectionType::Pointer result(new TransPathOptCollectionType);

      OntologyCoreType::WeightMapType weights = _spCore->generateWeightMap_trans(DataRepresentationSupport::Arbitrary, pProblemCompliance, pMetric);
      OntologyCoreType::PredecessorMapType predecessors;
      OntologyCoreType::EdgeMapType edges;
      _spCore->generateMinimalPathPredecessors(pFixedIS, weights, predecessors, edges);

      TransformationPathType::Pointer spPath = _spCore->generateTransPath(pMovingIS, pFixedIS, DataRepresentation::Continuous, weights, predecessors, edges);
      if (spPath)
      { //there is a path -> so generate an option and add it
        TransPathOptionType::Pointer spOption(new TransPathOptionType);
        spOption->setPath(spPath);
        result->addOption(spOption);
      }

      spPath = _spCore->generateTransPath(pMovingIS, pFixedIS, DataRepresentation::Discrete, weights, predecessors, edges);
      if (spPath)
      { //there is a path -> so generate an option and add it
        TransPathOptionType::Pointer spOption(new TransPathOptionType);
        spOption->setPath(spPath);
        result->addOption(spOption);
      }

      return Result<ConstTransPathOptColPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstTransPathOptColVectorType>
      SimpleOntology::
      doGetOptimalTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance, const TransPathMetricInterface* pMetric) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstTransPathOptColVectorType result;

      ConstInfEntityVectorType continuousEntities;
      ConstInfEntityVectorType discreteEntities;

      OntologyCoreType::spliteEntitiesByData(movingEntities, continuousEntities, discreteEntities);

      OntologyCoreType::WeightMapType cWeights, dWeights;
      OntologyCoreType::PredecessorMapType cPredecessors, dPredecessors;
      OntologyCoreType::EdgeMapType cEdges, dEdges;

      if (!continuousEntities.empty())
      {
        //get minaml spanning tree for continuous data
        cWeights = _spCore->generateWeightMap_trans(DataRepresentationSupport::Continuous, pProblemCompliance, pMetric);
        _spCore->generateMinimalPathPredecessors(pFixedIS, cWeights, cPredecessors, cEdges);
      }

      if (!discreteEntities.empty())
      {
        //get minaml spanning tree for discrete data
        dWeights = _spCore->generateWeightMap_trans(DataRepresentationSupport::Discrete, pProblemCompliance, pMetric);
        _spCore->generateMinimalPathPredecessors(pFixedIS, dWeights, dPredecessors, dEdges);
      }

      //go throug all entities and get there options
      for (ConstInfEntityVectorType::const_iterator pos = movingEntities.begin(); pos!= movingEntities.end(); ++pos)
      {
        TransPathOptCollectionType::Pointer spOptCol(new TransPathOptCollectionType);
        spOptCol->setMovingEntity(*pos);

        TransformationPathType::Pointer spPath;

        if ((*pos)->getDataRepresentation()==DataRepresentation::Continuous)
        {
          spPath = _spCore->generateTransPath(getContainingIS(*pos), pFixedIS, DataRepresentation::Continuous, cWeights, cPredecessors, cEdges);
        }
        else
        {
          spPath = _spCore->generateTransPath(getContainingIS(*pos), pFixedIS, DataRepresentation::Discrete, dWeights, dPredecessors, dEdges);
        }

        if (spPath)
        { //there is a path -> so generate an option and add it
          TransPathOptionType::Pointer spOption(new TransPathOptionType);
          spOption->setPath(spPath);
          spOption->setMovingEntity(*pos);
          spOptCol->addOption(spOption);
        }

        result.push_back(spOptCol);
      }

      return Result<ConstTransPathOptColVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstInfSpaceVectorType>
      SimpleOntology::
      doGetMappableInformationSpaces(InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance, const RegPathMetricInterface* pMetric) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstInfSpaceVectorType result;

      OntologyCoreType::WeightMapType weights = _spCore->generateWeightMap_reg(requiredDataSupport, pProblemCompliance, pMetric);
      OntologyCoreType::PredecessorMapType predecessors;
      OntologyCoreType::EdgeMapType edges;
      _spCore->generateMinimalPathPredecessors(pFixedIS, weights, predecessors, edges);

      result = _spCore->generateMapableIS(pFixedIS, weights, predecessors, edges);

      return Result<ConstInfSpaceVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::MappingErrorType>
      SimpleOntology::
      doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      //get path option collection for the passed entity
      ConstInfEntityVectorType movingIEs;
      movingIEs.push_back(pMovingEntity);
      ConstTransPathOptColVectorType cols = getTransformationPaths(movingIEs, pFixedIS, pProblemCompliance);

      assert(cols.size()>0);

      return Result<MappingErrorType>(cols[0]->checkForFailureReason(), _spCore->_revision);
    };

    Result<SimpleOntology::MappingErrorType>
      SimpleOntology::
      doCheckForMappingFailureReason(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      OntologyCoreType::RegistrationGraphType::vertex_descriptor movingV = _spCore->getVertex(pMovingIS);
      OntologyCoreType::RegistrationGraphType::vertex_descriptor targetV = _spCore->getVertex(pFixedIS);

      OntologyCoreType::SimpleSearchMapType searchResult;
      core::simplePathSearch(searchResult, _spCore->_graph, targetV, movingV, requiredDataSupport, pProblemCompliance, OntologyCoreType::EdgeValidatorType());

      ConstRegPathOptColPointer col = _spCore->generateRegCollection(searchResult, ConstInfEntityPointer());
      
      MappingErrorType result =_spCore->checkOptionCollectionSupport(col, requiredDataSupport);

      return Result<MappingErrorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::MappingErrorType>
      SimpleOntology::
      doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstRegistrationPathPointer pPath) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      MappingErrorType result = RegPathOptionType::PathCheckPolicy::checkForFailureReason(pPath,pMovingEntity);

      return Result<MappingErrorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::MappingErrorType>
      SimpleOntology::
      doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstTransformationPathPointer pPath) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      MappingErrorType result = TransPathOptionType::PathCheckPolicy::checkForFailureReason(pPath,pMovingEntity);

      return Result<MappingErrorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstRegistrationPathPointer>
      SimpleOntology::
      doConvertTransformationToRegistrationPath(ConstTransformationPathPointer pPath) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      RegistrationPathType::Pointer result(new RegistrationPathType());

      for (TransformationPathType::ConstPathElementIterator pos = pPath->getBegin(); pos != pPath->getEnd(); ++pos)
      {
        OntologyCoreType::RegistrationGraphType::edge_descriptor edge = _spCore->getAssociatedEdge(*pos);

        SimpleRegistrationInfo::Pointer spRegInfo(new SimpleRegistrationInfo());
        spRegInfo->setTransformations(_spCore->_graph[edge].direct,_spCore->_graph[edge].inverse);
        result->appendElement(spRegInfo);
      }

      return Result<ConstRegistrationPathPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstTransformationInfoPointer>
      SimpleOntology::doActualize(TransformationInfoInferencePointer pTI) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstTransformationInfoPointer result;

      OntologyCoreType::TransformationMapType::const_iterator pos = _spCore->_transformationMap.find(pTI->getUID());
      if (pos !=  _spCore->_transformationMap.end())
      {
        result = pos->second;
      }

      return Result<SimpleOntology::ConstTransformationInfoPointer>(result, _spCore->_revision);
    };

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    // Mapping Integration
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////

    Result<SimpleOntology::ConstTransformationInfoPointer>
      SimpleOntology::
      doDefineTransformation(TransInfoInferencePointer newTransformation)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstTransformationInfoPointer result;

      MappingInferenceInterface::TransformationInfoType::Pointer spNew = newTransformation->clone();
      if (_spCore->validateForCommit(spNew))
      {
        /*INTERNAL-TODO Consistency rule should be added: transformation already exists*/
        OntologyCoreType::TransformationMapType::const_iterator pos = _spCore->_transformationMap.find(spNew->getUID());
        if (pos !=  _spCore->_transformationMap.end())
        { //the info is already there, silent delete of old version in Simple implementation.
          _spCore->deleteTransformationInfo(spNew);
        }
  
        // add the clone
        _spCore->storeTransformationInfo(spNew);     
        result = spNew;
      }
      else throw exceptions::UndefinedElement("Cannot define transformation info, associated information spaces or statement are not defined in the ontology.");

      return Result<SimpleOntology::ConstTransformationInfoPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstTransformationInfoPointer>
      SimpleOntology::
      doStoreTransformation(TransInfoInferencePointer transformation)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstTransformationInfoPointer result;

      /*INTERNAL-TODO Consistency rule should be added: transformation info does not exist*/
      // Simple implementation //silent add
      MappingInferenceInterface::TransformationInfoType::Pointer spNew = transformation->clone();
      if (_spCore->validateForCommit(spNew))
      {
        _spCore->storeTransformationInfo(spNew);     
        result = spNew;
      }
      else throw exceptions::UndefinedElement("Cannot store transformation info, associated information spaces or statement are not defined in the ontology.");

      return Result<SimpleOntology::ConstTransformationInfoPointer>(result, _spCore->_revision);
    };

    SimpleOntology::TransformationDeleteReturnType
      SimpleOntology::
      doDeleteTransformation(TransInfoInferencePointer transformation)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      TransformationDeleteReturnType result = true;

      _spCore->deleteTransformationInfo(transformation);

      return result;
    };

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    // Problem Inference
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////

    Result<SimpleOntology::ConstProblemModelVectorType>
      SimpleOntology::
      doGetAssociatedProblemModels(ProblemStatementInferencePointer ps) const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstProblemModelVectorType result;

      //get the correlation
      OntologyCoreType::ConstModelMapType modelMap;
      _spCore->getProblemModels(modelMap, ps->getUID());

      //convert entity map into result
      OntologyCoreType::extracValuesFromMap(modelMap, result);

      return Result<ConstProblemModelVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstProblemModelVectorType>
      SimpleOntology::
      doGetProblemModels() const
    { 
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstProblemModelVectorType result;

      //convert corr map into result
      OntologyCoreType::extracValuesFromMap(_spCore->_modelMap, result);

      return Result<ConstProblemModelVectorType>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstProblemStatementVectorType>
      SimpleOntology::
      doGetProblemStatements() const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstProblemStatementVectorType result;

      //convert corr map into result
      OntologyCoreType::extracValuesFromMap(_spCore->_statementMap, result);

      return Result<ConstProblemStatementVectorType>(result, _spCore->_revision);
    };


    Result<SimpleOntology::ConstProblemStatementPointer>
      SimpleOntology::
      doActualize(ProblemStatementInferencePointer ps) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstProblemStatementPointer result;

      OntologyCoreType::StatementMapType::const_iterator pos = _spCore->_statementMap.find(ps->getUID());
      if (pos !=  _spCore->_statementMap.end())
      { 
        result = pos->second;
      }

      return Result<ConstProblemStatementPointer>(result, _spCore->_revision);
    };


    Result<SimpleOntology::ConstProblemModelPointer>
      SimpleOntology::
      doActualize(ProblemModelInferencePointer pm) const
    {
      assert(_spCore);

      OntologyCoreType::SharableLockType lock(_spCore->_mutex);

      ConstProblemModelPointer result;

      OntologyCoreType::ModelMapType::const_iterator pos = _spCore->_modelMap.find(pm->getUID());
      if (pos !=  _spCore->_modelMap.end())
      { 
        result = pos->second;
      }

      return Result<ConstProblemModelPointer>(result, _spCore->_revision);
    };

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    // Problem Integration
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////

    Result<SimpleOntology::ConstProblemStatementPointer>
      SimpleOntology::
      doDefineProblemStatement(ProblemStatementInferencePointer pNewStatement)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstProblemStatementPointer result;

      /*INTERNAL-TODO Consistency rule should be added: problem statement already exists*/
      OntologyCoreType::StatementMapType::const_iterator pos = _spCore->_statementMap.find(pNewStatement->getUID());
      if (pos !=  _spCore->_statementMap.end())
      { //the statement is already there, silent drop in Simple implementierung
        result = pos->second;
      }
      else
      { // add the clone
        ProblemStatementType::Pointer spNew = pNewStatement->clone();
        _spCore->_statementMap[spNew->getUID()] = spNew;
        result = spNew;
        _spCore->notifyChange();
      }

      return Result<SimpleOntology::ConstProblemStatementPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstProblemStatementPointer>
      SimpleOntology::
      doStoreProblemStatement(ProblemStatementInferencePointer pStatement)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstProblemStatementPointer result;

      /*INTERNAL-TODO Consistency rule should be added: Entity does not exist*/
      OntologyCoreType::StatementMapType::const_iterator pos = _spCore->_statementMap.find(pStatement->getUID());
      if (pos !=  _spCore->_statementMap.end())
      { //update entity
        pos->second->setName(pStatement->getName());
        result =  pos->second;
      }
      else
      { // Simple implementation: silent add
        ProblemStatementType::Pointer spNew = pStatement->clone();
        _spCore->_statementMap[spNew->getUID()] = spNew;
        result = spNew;
      }
      _spCore->notifyChange();

      return Result<SimpleOntology::ConstProblemStatementPointer>(result, _spCore->_revision);
    };

    SimpleOntology::StatementDeleteReturnType
      SimpleOntology::
      doDeleteProblemStatement(ProblemStatementInferencePointer pStatement)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      StatementDeleteReturnType result = true;

      //remove from correlations
      _spCore->removeStatementFromModels(pStatement->getUID());

      //remove from lookups
      _spCore->_stat2ModelMap.erase(pStatement->getUID());

      //remove statement
      if (_spCore->_statementMap.erase(pStatement->getUID()) > 0)
      {
        _spCore->notifyChange();
      }

      return result;
    };

    Result<SimpleOntology::ConstProblemModelPointer>
      SimpleOntology::
      doDefineProblemModel(ProblemModelInferencePointer pNewModel)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstProblemModelPointer result;

      /*INTERNAL-TODO Consistency rule should be added: problem model already exists*/
      OntologyCoreType::ModelMapType::const_iterator pos = _spCore->_modelMap.find(pNewModel->getUID());
      if (pos !=  _spCore->_modelMap.end())
      { //the model is already there, silent drop in Simple implementierung
        result = pos->second;
      }
      else
      { // add the clone
        ProblemModelType::Pointer spNew = pNewModel->clone();
        if (_spCore->validateForCommit(spNew))
        {
          _spCore->_modelMap[spNew->getUID()] = spNew;
          result = spNew;
          _spCore->updateStatement2ModelMap(spNew);
          _spCore->notifyChange();
        }
        else throw exceptions::UndefinedElement("Cannot define problem model, associated statements are not defined in the ontology.");
      }

      return Result<SimpleOntology::ConstProblemModelPointer>(result, _spCore->_revision);
    };

    Result<SimpleOntology::ConstProblemModelPointer>
      SimpleOntology::
      doStoreProblemModel(ProblemModelInferencePointer pModel)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ConstProblemModelPointer result;

      /*INTERNAL-TODO Consistency rule should be added: model does not exist*/
      // Simple implementation
      ProblemModelType::Pointer spNew = pModel->clone();
      if (_spCore->validateForCommit(spNew))
      {
        _spCore->_modelMap[spNew->getUID()] = spNew;
        _spCore->updateStatement2ModelMap(spNew);
        result = spNew;
        _spCore->notifyChange();
      }
      else throw exceptions::UndefinedElement("Cannot store problem model, associated statements are not defined in the ontology.");

      return Result<SimpleOntology::ConstProblemModelPointer>(result, _spCore->_revision);
    };

    SimpleOntology::ModelDeleteReturnType
      SimpleOntology::
      doDeleteProblemModel(ProblemModelInferencePointer pModel)
    {
      assert(_spCore);

      OntologyCoreType::LockType lock(_spCore->_mutex);

      ModelDeleteReturnType result = true;

      bool change = false;

      //remove from lookup
      OntologyCoreType::StatementModelMapType::iterator pos = _spCore->_stat2ModelMap.begin();

      while( pos !=  _spCore->_stat2ModelMap.end())
      {
        if (pos->second == pModel->getUID())
        {
          pos = _spCore->_stat2ModelMap.erase(pos);
          change = true;
        }
        else
        {
          ++pos;
        }
      }

      //remove model
      if (_spCore->_modelMap.erase(pModel->getUID()))
      {
        change = true;
      };

      if (change)
      {
        _spCore->notifyChange();
      }

      return result;
    };


  } // end namespace scenario
} // end namespace iro
