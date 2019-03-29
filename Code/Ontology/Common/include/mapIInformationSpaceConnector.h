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





#ifndef __MAP_I_INFORMATION_SPACE_CONNECTOR_H
#define __MAP_I_INFORMATION_SPACE_CONNECTOR_H

namespace iro
{

  /** Interface for any class that realizes a connection between two information spaces.
  Most relevant realizations are TransformationInfo and RegistrationInfo.*/
  template <typename TInformationSpaceTraits>
  class IInformationSpaceConnector
  {
  public:
    using ConstISPointer = typename TInformationSpaceTraits::ConstPointer;

    /** Returns the pointer to the associated moving information space. If the connector has no IS defined the return
    * can be a NULL pointer.*/
    virtual ConstISPointer getMovingIS() const = 0 ;

    /** Returns the pointer to the associated moving information space. If the connector has no IS defined the return
    * can be a NULL pointer.*/
    virtual ConstISPointer getTargetIS() const = 0 ;

  protected:

    virtual ~IInformationSpaceConnector() = default;
    IInformationSpaceConnector() = default;
  private:
    IInformationSpaceConnector(const IInformationSpaceConnector&) = delete; //not implemented by purpose
    IInformationSpaceConnector& operator=(const IInformationSpaceConnector&) = delete; //not implemented by purpose
  };
} // end namespace iro

#endif
