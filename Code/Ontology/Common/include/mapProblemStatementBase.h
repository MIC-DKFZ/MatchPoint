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



#ifndef __MAP_PROBLEM_STATEMENT_BASE_H
#define __MAP_PROBLEM_STATEMENT_BASE_H

#include "mapOntologyString.h"
#include "mapIProblemComplianceDefinition.h"

#include <memory>

namespace iro
{
  namespace scenario
  {

    /*! @class ProblemStatementBase
    * @brief  base for problem statements.
    *
    * A problem statement is for example: Pelvis centric rigid registration of the reference MRI images of two given studies.
    * This class is used to resolve ambiguities between translation if they would connect the same information spaces.\n\n
    *
    * @tparam TUIDPolicy specifies the type and who to handle UIDs (see for example BoostUIDPolicy which implements boost based UIDs.
    */
    template <typename TUIDPolicy>
    class ProblemStatementBase : public IProblemComplianceDefinition< ProblemStatementBase<TUIDPolicy> >
    {
    public:
      using Self = ProblemStatementBase<TUIDPolicy>;

      using NameType = iro::String;
      using UIDType = typename TUIDPolicy::UIDType;

      using Pointer = std::shared_ptr<Self>;
      using ConstPointer = std::shared_ptr<const Self>;

       /*! returns the UID of the statement.*/
      const UIDType& getUID() const;
      void setUID(const UIDType& uid);

      /*! returns the name of the statement.*/
      const NameType& getName() const;
      void setName(const NameType& name);

      ~ProblemStatementBase() override;
      ProblemStatementBase();

      /* Clones the content of the ProblemStatement and returns it as
      * non const pointer. It can be used to alter the statement and
      * update the knowledge base of the ontology.
      */
      Pointer clone() const;

    protected:
      bool doCheckComplianceOfStatement(const Self* pProblem) const override;

      NameType _name;
      UIDType _uid;

    private:
      ProblemStatementBase(const Self&) = delete; //not implemented by purpose
      ProblemStatementBase& operator=(const Self&) = delete; //not implemented by purpose

    };


  } // end namespace scenario

} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapProblemStatementBase.tpp"
#endif

#endif
