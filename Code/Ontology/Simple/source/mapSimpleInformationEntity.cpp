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




#include "mapSimpleTransformationInfo.h"

namespace iro
{
  namespace scenario
  {

    const SimpleInformationEntity::UIDType&
      SimpleInformationEntity::
      getUID() const
    {
      return _uid;
    };

    void
      SimpleInformationEntity::
      setUID(const UIDType& uid)
    {
      _uid = uid;
    };

    const SimpleInformationEntity::DataRepresentationType&
      SimpleInformationEntity::
      getDataRepresentation() const
    {
      return _dataRep;
    };

    void
      SimpleInformationEntity::
      setDataRepresentation(const DataRepresentationType& rep)
    {
      _dataRep = rep;
    };

    bool
      SimpleInformationEntity::
      operator==(const Self& is) const
    {
      return is.getUID()==_uid;
    };

    SimpleInformationEntity::Pointer
      SimpleInformationEntity::
      clone() const
    {
      Pointer spClone(new Self());

      spClone->_dataRep=_dataRep;
      spClone->_uid=_uid;

      return spClone;
    };

    SimpleInformationEntity::
      ~SimpleInformationEntity()
    {
    };


    SimpleInformationEntity::
      SimpleInformationEntity() : _uid(""), _dataRep(DataRepresentation::Discrete)
    {
    };


  } // end namespace scenario
} // end namespace iro
