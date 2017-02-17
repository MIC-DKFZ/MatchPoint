// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/Common/include/mapPointSetRegistrationAlgorithmInterface.h $
*/

#ifndef __POINT_SET_REGISTRATION_ALGORITHM_INTERFACE_V2_H
#define __POINT_SET_REGISTRATION_ALGORITHM_INTERFACE_V2_H

#include "mapPointSetRegistrationAlgorithmInterface.h"

/*! @namespace
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class PointSetRegistrationAlgorithmInterfaceV2
			@brief This is the interface for point set based registration algorithms (Version 2)
      This version extents the first version by:
      1. Allow define multiple inputs for the roles (moving / target)
      2. posibility to query if the input slots are mandatory or just optional.

      The inputs are indexed (like itk filters) and the interface implies that all mandatory
      input slots of a role have lower indeces then optional slots of the same role. So e.g.
      given 4 mandatory moving input slots, by definition they will have the indeces 0..3. Optional
      slots will start with 4.
      An additional assumption is that PointSetRegistrationAlgorithmInterface accesses the first slots
      (slot index 0). According to this assumptions the methods of PointSetRegistrationAlgorithmInterface
      have a default implementation.
      @sa PointSetRegistrationAlgorithmInterface
			@ingroup AlgorithmFacets
			@template TMovingPointSet Type of the moving point set
			@template TTargetPointSet Type of the target point set
			*/
			template<class TMovingPointSet, class TTargetPointSet>
      class PointSetRegistrationAlgorithmInterfaceV2 : public PointSetRegistrationAlgorithmInterface<TMovingPointSet, TTargetPointSet>
			{
			public:
        typedef PointSetRegistrationAlgorithmInterfaceV2<TMovingPointSet, TTargetPointSet> Self;
        typedef PointSetRegistrationAlgorithmInterface<TMovingPointSet, TTargetPointSet> Superclass;

        typedef typename Superclass::MovingPointSetType MovingPointSetType;
        typedef typename Superclass::TargetPointSetType TargetPointSetType;

        typedef typename Superclass::MovingPointSetConstPointer MovingPointSetConstPointer;
        typedef typename Superclass::TargetPointSetConstPointer TargetPointSetConstPointer;
        typedef unsigned int SlotIndexType;

        itkTypeMacro(PointSetRegistrationAlgorithmInterfaceV2, PointSetRegistrationAlgorithmInterface);

        /*! @brief gets a const pointer to the moving point set for the specified index
        @eguarantee strong
        @param index Index of the requested slot.
        @return a const pointer to the moving point set
        @pre If index is out of bound an exception will be thrown.
        */
        MovingPointSetConstPointer getNthMovingPointSet(SlotIndexType index) const
        {
          if (index >= this->getMovingPointSetCount())
          {
            mapDefaultExceptionMacro(<< "Error. Index of requested moving point set is out of bounds. Requested index: " << index << "; number of point sets: " << getMovingPointSetCount());
          }
          return doGetNthMovingPointSet(index);
        };

        /*! @brief gets a const pointer to the target point set for the specified index
        @eguarantee strong
        @param index Index of the requested slot.
        @return a const pointer to the target point set. If no data has been set for the index
        null ptr will be returned.
        @pre If index is out of bound an exception will be thrown.
        */
        TargetPointSetConstPointer getNthTargetPointSet(SlotIndexType index) const
        {
          if (index >= this->getTargetPointSetCount())
          {
            mapDefaultExceptionMacro(<< "Error. Index of requested target point set is out of bounds. Requested index: " << index << "; number of point sets: " << getTargetPointSetCount());
          }
          return doGetNthTargetPointSet(index);
        };
        
        /*! @brief sets the moving point set for a specified slot index 
        @eguarantee strong
        @param pMovingPointSet a pointer to the moving point set
        @param index Index of the slot.
        @pre If index is out of bound an exception will be thrown.
        */
        void setNthMovingPointSet(SlotIndexType index, const MovingPointSetType* pMovingPointSet)
        {
          if (index >= this->getMovingPointSetCount())
          {
            mapDefaultExceptionMacro(<< "Error. Setter index of moving point set is out of bounds. Specified index: " << index << "; number of point set slots: " << getMovingPointSetCount());
          }
          return doSetNthMovingPointSet(index, pMovingPointSet);
        };
        
        /*! @brief sets the target point set for a specified slot index 
        @eguarantee strong
        @param pTargetPointSet a pointer to the moving point set
        @param index Index of the slot.
        @pre If index is out of bound an exception will be thrown.
        */
        void setNthTargetPointSet(SlotIndexType index, const TargetPointSetType* pTargetPointSet)
        {
          if (index >= this->getTargetPointSetCount())
          {
            mapDefaultExceptionMacro(<< "Error. Setter index of target point set is out of bounds. Specified index: " << index << "; number of point set slots: " << getTargetPointSetCount());
          }
          return doSetNthTargetPointSet(index, pTargetPointSet);
        };
        
        /*! Indicates if the target and input data of one index are coupled or not. Coupled means
          that if the index for one role (target or moving) is set, the other role at this index
          must also be set.
          @return True if coupled. False if not.
          @eguarantee strong*/
        virtual bool hasCoupledPointSetInputs() const { return true; };

        /*! Indicates if the passed index indicates a mandatory (false) or an optional (true) input.*/
        virtual bool isOptionalTargetPointSet(SlotIndexType index) const { return false; };

        /*! Indicates if the passed index indicates a mandatory (false) or an optional (true) input.*/
        virtual bool isOptionalMovingPointSet(SlotIndexType index) const { return false; };

        /*! Gets the number of target inputs (in total: onlyMandatory == false)
        @eguarantee strong
        */
        virtual SlotIndexType getTargetPointSetCount(bool onlyMandatory = false) const { return 1; };

        /*! Gets the number of moving inputs (in total: onlyMandatory == false)
        @eguarantee strong
        */
        virtual SlotIndexType getMovingPointSetCount(bool onlyMandatory = false) const { return 1; };

        /*! returns the modification time of the target point set.
        */
        virtual unsigned long getNthTargetPointSetMTime(SlotIndexType index) const = 0;

        /*! returns the modification time of the moving point set.
        */
        virtual unsigned long getNthMovingPointSetMTime(SlotIndexType index) const = 0;

        virtual MovingPointSetConstPointer getMovingPointSet() const override
        {
          return getNthMovingPointSet(0);
        };

        virtual TargetPointSetConstPointer getTargetPointSet() const override
        {
          return getNthTargetPointSet(0);
        }

        virtual void setMovingPointSet(const MovingPointSetType* pMovingPointSet) override
        {
          setNthMovingPointSet(0, pMovingPointSet);
        };

        virtual void setTargetPointSet(const TargetPointSetType* pTargetPointSet) override
        {
          setNthTargetPointSet(0, pTargetPointSet);
        };

        virtual unsigned long getTargetPointSetMTime() const override
        {
          return getNthTargetPointSetMTime(0);
        };

        virtual unsigned long getMovingPointSetMTime() const override
        {
          return getNthMovingPointSetMTime(0);
        };

			protected:
				/*! @brief virtual destructor
				*/
				virtual ~PointSetRegistrationAlgorithmInterfaceV2() {};

				PointSetRegistrationAlgorithmInterfaceV2() {};

        virtual MovingPointSetConstPointer doGetNthMovingPointSet(SlotIndexType index) const = 0;

        virtual TargetPointSetConstPointer doGetNthTargetPointSet(SlotIndexType index) const = 0;

        virtual void doSetNthMovingPointSet(SlotIndexType index, const MovingPointSetType* pMovingPointSet) = 0;

        virtual void doSetNthTargetPointSet(SlotIndexType index, const TargetPointSetType* pTargetPointSet) = 0;

      private:

				//No copy constructor allowed
				PointSetRegistrationAlgorithmInterfaceV2(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#endif
