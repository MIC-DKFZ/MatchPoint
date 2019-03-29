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




#ifndef __MAP_PATH_OPTION_TPP
#define __MAP_PATH_OPTION_TPP

#include "mapTransformationPathBase.h"

namespace iro
{

  template <typename TPathTraits, typename TPathCheckPolicy>
  typename PathOption<TPathTraits, TPathCheckPolicy>::ConstIEPointer
    PathOption<TPathTraits, TPathCheckPolicy>::
    getMovingEntity() const
  {
    return _movingEntity;
  };

  template <typename TPathTraits, typename TPathCheckPolicy>
  void
    PathOption<TPathTraits, TPathCheckPolicy>::
    setMovingEntity(ConstIEPointer movingEntity)
  {
    if (_path && movingEntity && (movingEntity!=_movingEntity))
    { //check the support
      if (TPathCheckPolicy::checkForFailureReason(_path,movingEntity)>MappingError::NoMappingGuarantee)
      {
        throw exceptions::InvalidDataRepresentation("New moving entity is not supported by path option.");
      }
    }

    _movingEntity =  movingEntity;
  };

  template <typename TPathTraits, typename TPathCheckPolicy>
  typename PathOption<TPathTraits, TPathCheckPolicy>::ConstPathPointer
    PathOption<TPathTraits, TPathCheckPolicy>::
    getPath() const
  {
    return _path;
  };

  template <typename TPathTraits, typename TPathCheckPolicy>
  void
    PathOption<TPathTraits, TPathCheckPolicy>::
    setPath(ConstPathPointer path)
  {
    if (_movingEntity && path && (path.get()!=_path.get()))
    { //check the support
      if (TPathCheckPolicy::checkForFailureReason(path,_movingEntity)>MappingError::NoMappingGuarantee)
      {
        throw exceptions::InvalidDataRepresentation("New path does not support moving entity of the path option.");
      }
    }

    _path =  path;
  };

  template <typename TPathTraits, typename TPathCheckPolicy>
  typename PathOption<TPathTraits, TPathCheckPolicy>::ConstISPointer
    PathOption<TPathTraits, TPathCheckPolicy>::
    getTargetIS() const
  { 
    ConstISPointer spResult;

    if (_path)
    {
      spResult = _path->getTargetIS();
    }

    return spResult;
  };

  template <typename TPathTraits, typename TPathCheckPolicy>
  typename PathOption<TPathTraits, TPathCheckPolicy>::MappingErrorType
    PathOption<TPathTraits, TPathCheckPolicy>::
    checkForFailureReason() const
  {
    if (!_path) { throw exceptions::InvalidArgument("No path is set. Cannot ascertain failure risks.");
}
    if (!_movingEntity) { throw exceptions::InvalidArgument("No moving entity is set. Cannot ascertain failure risks.");
}
    return TPathCheckPolicy::checkForFailureReason(_path,_movingEntity);
  };

  template <typename TPathTraits, typename TPathCheckPolicy>
  bool
    PathOption<TPathTraits, TPathCheckPolicy>::
    hasFullMappingGuarantee() const
  {
    if (!_path) throw exceptions::InvalidArgument("No path is set. Cannot ascertain failure risks.");
    if (!_movingEntity) throw exceptions::InvalidArgument("No moving entity is set. Cannot ascertain failure risks.");
    return TPathCheckPolicy::checkForFailureReason(_path,_movingEntity)== MappingError::NoFailure;
  };

  template <typename TPathTraits, typename TPathCheckPolicy>
  bool
    PathOption<TPathTraits, TPathCheckPolicy>::
    doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const
  {
    bool result = true;

    if (_path)
    {
      result = _path->checkProblemCompliance(pProblemCompliance);
    }

    return result;
  };

  template <typename TPathTraits, typename TPathCheckPolicy>
  PathOption<TPathTraits, TPathCheckPolicy>::
    ~PathOption()
  = default;

  template <typename TPathTraits, typename TPathCheckPolicy>
  PathOption<TPathTraits, TPathCheckPolicy>::
    PathOption()
  = default;

} // end namespace iro

#endif
