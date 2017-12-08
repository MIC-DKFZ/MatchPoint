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



#ifndef __IRO_PROBLEM_MODEL_BASE_H
#define __IRO_PROBLEM_MODEL_BASE_H

#include "mapOntologyString.h"
#include "mapProblemStatementBase.h"

#include <vector>

#include <memory>

namespace iro
{
  namespace scenario
  {

    /*! @class ProblemModelBase
    * @brief  base for problem models.
    *
    * Problem models specify/represent a distinct abstracted view (the problem model) on a real world problem.
    * This is motivated by the assumption that a registration, as a model for a real world correlation,
    * might introduce abstraction errors. Thus solutions based on this registration are only simplified models
    * for the real world problem and its solution. ProblemStatements that are grouped in one ProblemModel are
    * assumed to be valid in the same abstracted view and thus registrations of these ProblemStatements may be
    * "used" together. Therefor an entity should not be mapped consecutively by registrations that are not
    * affiliated to the same ProblemModel via the according ProblemStatements because there is no accepted
    * "view" on the real world problem allowing there combination.\n
    * E.g.: Entities mapped prostate centric should not be displayed together
    * with entities that are mapped pelvis centric.\n\n
    *
    * Uses boost::uuid as ID and ior::String as name type. Both informations are stored as members.
    * the policiy offers public setters and initilizes name with an empty string and the UID with a new unique ID.
    */
    template <typename TProblemStatementTraits, typename TUIDPolicy>
    class ProblemModelBase : public IProblemComplianceDefinition<typename TProblemStatementTraits::Type>
    {
    public:
      typedef ProblemModelBase<TProblemStatementTraits, TUIDPolicy>   Self;

      typedef iro::String                       NameType;
      typedef typename TUIDPolicy::UIDType      UIDType;

      typedef std::shared_ptr< Self >         Pointer;
      typedef std::shared_ptr< const Self >   ConstPointer;

      using ProblemStatementTraitsType = TProblemStatementTraits;
      typedef typename ProblemStatementTraitsType::Type           ProblemStatementType;
      typedef typename ProblemStatementType::ConstPointer      ProblemStatementConstPointer;
      typedef std::vector<ProblemStatementConstPointer> StatementVectorType;

      typedef typename StatementVectorType::iterator		                  ProblemIterator;
      typedef typename StatementVectorType::const_iterator               ConstProblemIterator;

      typedef typename StatementVectorType::size_type                    SizeType;

      typedef typename ProblemStatementType::UIDType                  ProblemStatementUIDType;

      /*! returns the UID of the statement.*/
      const UIDType& getUID() const;
      void setUID(const UIDType& uid);

      /*! returns the name of the statement.*/
      const NameType& getName() const;
      void setName(const NameType& name);

      ProblemIterator getStatementBegin();
      ConstProblemIterator getStatementBegin() const;

      ProblemIterator getStatementEnd();
      ConstProblemIterator getStatementEnd() const;

      /*! Returns the number of statements assigned to the model */
      SizeType getStatementCount() const;

      ProblemIterator findStatement(const ProblemStatementUIDType& uid);
      ConstProblemIterator findStatement(const ProblemStatementUIDType& uid) const;

      /*! Adds the passed statement instance to the model.
      * @pre pStatement must point to a valid instance or an exception will be raised.
      * @pre pStatement must not have the same UID then an other statment already associated
      * with the modell or an exception will be thrown.*/
      void addStatement(ProblemStatementConstPointer pStatement);

      /*! removes the statement indecated by the passed iterator and returns the iterator the next statement.
      * if it is the last statement in the list the end iterator will be returned.*/
      ProblemIterator removeStatement(ProblemIterator pos);

      /*! removes all statements from the model.*/
      void resetStatements();

      /* Clones the content of the ProblemModel and returns it as
      * non const pointer. It can be used to alter the model and
      * update the knowledge base of the ontology.
      */
      Pointer clone() const;

      ~ProblemModelBase();
      ProblemModelBase();

    protected:

      virtual bool doCheckComplianceOfStatement(const ProblemStatementType* pProblem) const;

      StatementVectorType _associatedStatements;

      NameType _name;
      UIDType _uid;

    private:
      Self& operator=(const Self&); //not implemented by purpose
      ProblemModelBase(const Self&); //not implemented by purpose
    };

  } // end namespace scenario

} // end namespace iro

#ifndef IRO_MANUAL_TPP
#include "mapProblemModelBase.tpp"
#endif

#endif
