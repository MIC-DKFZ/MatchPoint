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




#ifndef __MAP_SIMPLE_INFORMATION_SPACE_H
#define __MAP_SIMPLE_INFORMATION_SPACE_H

#include <memory>
#include "mapInformationSpaceTraits.h"
#include "mapOntologyString.h"

#include "mapMAPOntologySimpleExports.h"

namespace iro
{
  namespace scenario
  {

    /*! @class SimpleInformationSpace
     * @brief Simple specific implementation of an information space
     * Uses a string type to store the UID.
     * @ingroup Simple*/
    class MAPOntologySimple_EXPORT SimpleInformationSpace
    {
    public:
      typedef SimpleInformationSpace Self;
      typedef ::iro::String        UIDType;

      typedef std::shared_ptr< Self >         Pointer;
      typedef std::shared_ptr< const Self >   ConstPointer;

       /*! returns the UID of the statement.*/
      const UIDType& getUID() const;
      void setUID(const UIDType& uid);

      virtual ~SimpleInformationSpace();
      SimpleInformationSpace();

      bool operator == (const Self& is) const;

      /** Clones the content of the information space and returns it as
      * non const pointer. It can be used to alter the entity and
      * update the knowledge base of the ontology.
      */
      Pointer clone() const;

    protected:
      UIDType _uid;

    private:
      SimpleInformationSpace(const Self&); //not implemented by purpose
      Self& operator=(const Self&); //not implemented by purpose
    };

    using SimpleInformationSpaceTraits = InformationSpaceTraits<::iro::scenario::SimpleInformationSpace>;

  } // end namespace scenario

} // end namespace iro

#endif
