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

    const SimpleInformationSpace::UIDType&
      SimpleInformationSpace::
      getUID() const
    {
      return _uid;
    };

    void
      SimpleInformationSpace::
      setUID(const UIDType& uid)
    {
      _uid = uid;
    };

    bool
      SimpleInformationSpace::
      operator==(const Self& is) const
    {
      return is.getUID()==_uid;
    };

    SimpleInformationSpace::
      ~SimpleInformationSpace()
    = default;


    SimpleInformationSpace::
      SimpleInformationSpace() : _uid("")
    {
    };

    SimpleInformationSpace::Pointer
      SimpleInformationSpace::
      clone() const
    {
      Pointer spClone(new Self());

      spClone->_uid=_uid;

      return spClone;
    };

  } // end namespace scenario
} // end namespace iro
