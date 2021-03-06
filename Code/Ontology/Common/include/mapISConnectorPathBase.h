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




#ifndef __MAP_CONNECTOR_PATH_BASE_H
#define __MAP_CONNECTOR_PATH_BASE_H

#include "mapIInformationSpaceConnector.h"
#include "mapIProblemComplianceChecker.h"

#include <memory>
#include <list>

namespace iro
{

		/** Base class for all class that defines sequential
		* connection between information spaces. Most relevant realizations
		* are TransformationPath and RegistrationPath. This interface combines
		* the interfaces IInformationSpaceConnector and IProblemModelAssociated*/
    template <typename TPathElementTraits, typename TInformationSpaceTraits, typename TProblemStatementTraits>
    class ISConnectorPathBase: public IInformationSpaceConnector<TInformationSpaceTraits>, public IProblemComplianceChecker<TProblemStatementTraits>
		{
    public:
      typedef ISConnectorPathBase<TPathElementTraits, TInformationSpaceTraits, TProblemStatementTraits> Self;
      using Pointer = ::std::shared_ptr<Self>;
      using ConstPointer = ::std::shared_ptr<const Self>;

      using ConnectorInterface = IInformationSpaceConnector<TInformationSpaceTraits>;
      using ConstISPointer = typename ConnectorInterface::ConstISPointer;

      using ComplianceCheckerInterface = IProblemComplianceChecker<TProblemStatementTraits>;
      using ProblemComplianceInterface = typename ComplianceCheckerInterface::ProblemComplianceInterface;

      using ProblemStatementType = typename TProblemStatementTraits::Type;
			using ProblemPointer = typename TProblemStatementTraits::Pointer;
			using ConstProblemPointer = typename TProblemStatementTraits::ConstPointer;

      using PathElementType = typename TPathElementTraits::Type;
			using ConstPathElementPointer = typename TPathElementTraits::ConstPointer;

    protected:
      using PathElementListType = typename std::list<ConstPathElementPointer>;

    public:
      using PathElementIterator = typename PathElementListType::iterator;
      using ConstPathElementIterator = typename PathElementListType::const_iterator;
      using PathSizeType = typename PathElementListType::size_type;

      /*! Implementation of abstract member. See documentation in interface.
      * @see IInformationSpaceConnector*/
      ConstISPointer getMovingIS() const override;

      /*! Implementation of abstract member. See documentation in interface.
      * @see IInformationSpaceConnector*/
      ConstISPointer getTargetIS() const override;

      /*! Returns the iterator to the begin of th path.*/
      PathElementIterator getBegin();
      /*! Returns the const iterator to the begin of th path.*/
      ConstPathElementIterator getBegin() const;

      /*! Returns the iterator to the end of the path.*/
      PathElementIterator getEnd();
      /*! Returns the const iterator to the end of the path.*/
      ConstPathElementIterator getEnd() const;

      /*! Returns the size of the path (number of elements).*/
      PathSizeType size() const;

      /*! Inserts the passed newElement at the postion in the path indicated by pos.
       * Calls doInsertElement() after the preconditions are checked.
       * @remark Derivated classes may introducs further preconditions. E.g. see TransformationPath
       * @pre The moving IS of the new element must equal the target IS of the preceeding element (if new element is not inserted at the beginning)
       * @pre The target IS of the new element must equal the moving IS of the succeeding element (if new element is not inserted at the end)
       * @param [in] pos Iterator indicating the postion of the element where the element should be inserted.
       * @param [in] newElement The new element that should be inserted.
       * @return Iterator that points to the position of the inserted element in the path.
       * @exception ::iro::exceptions::InvalidMovingIS: the preconditions are violated
       * @exception ::iro::exceptions::InvalidTargetIS: the preconditions are violated*/
      PathElementIterator insertElement(PathElementIterator pos, ConstPathElementPointer newElement);

      /*! Adds the passed newElement at the end of the path.
       * Calls doAppend() after the preconditions are checked.
       * @remark Derivated classes may introducs further preconditions. E.g. see TransformationPath
       * @pre The moving IS of the new element must equal the target IS of the preceeding element (if the path is not empty)
       * @param [in] newElement The new element that should be inserted.
       * @exception ::iro::exceptions::InvalidMovingIS: the preconditions are violated*/
      void appendElement(ConstPathElementPointer newElement);

      /*! removes the element at the passed position from the path.
       * @param [in] pos Iterator indicating the postion of the element that should be removed.
       * @return Iterator that points to the position behind the removed element in the path. If it was the last element it points to getEnd().*/
      PathElementIterator removeElement(PathElementIterator pos);

      /*! Removes all elements of the path*/
      void resetElements();

			~ISConnectorPathBase() override;
			ISConnectorPathBase();

    protected:
      /*! Is called by InsertElement() after the preconditions are checked.
       * Base implementation just adds the element.
       * @param [in] pos Iterator indicating the postion of the element where the element should be inserted.
       * @param [in] newElement The new element that should be inserted.
       * @return Iterator that points to the position of the inserted element in the path.
       */
      virtual PathElementIterator doInsertElement(PathElementIterator pos, ConstPathElementPointer newElement);

      /*! Is called by appendElement() after the preconditions are checked.
       * Base implementation just appends the element.
       * @param [in] newElement The new element that should be inserted.
       */
      virtual void doAppend(ConstPathElementPointer newElement);

      /*! Implementation of abstract member. This implementation checks the associated
      * problem statement of all elements for compliance. See also documentation in interface.
      * @see IProblemComplianceChecker*/
			bool doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const override;

      PathElementListType _pathElements;

    private:
			ISConnectorPathBase(const Self&); //not implemented by purpose
			Self& operator=(const Self&); //not implemented by purpose
		};
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapISConnectorPathBase.tpp"
#endif

#endif
