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
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
// Subversion HeadURL: $HeadURL$
*/

#ifndef __REGISTRATION_MANIPULATOR_H
#define __REGISTRATION_MANIPULATOR_H

#include "mapRegistration.h"
#include "mapRegistrationBase.h"

namespace map
{
	namespace core
	{


		/*! @class RegistrationBaseManipulator
		    @brief Grants public write access to RegistrationBase.
		 */
		class RegistrationBaseManipulator
		{
		public:
			using TagMapType = RegistrationBase::TagMapType;

			/*! @brief sets the tags of a registration
			@eguarantee strong
			*/
			void setTagValues(const TagMapType& tags)
			{
				_pBase->setTagValues(tags);
			};

			/*! @brief allows non const access to the registration tags.
			@eguarantee no fail
			*/
			TagMapType& getTagValues()
			{
				return _pBase->getTagValues();
			};

			RegistrationBaseManipulator(RegistrationBase* pBase): _pBase(pBase)
			{
				assert(pBase);
			};

		protected:
			RegistrationBase* _pBase;

		private:
			//No copy constructor allowed
			RegistrationBaseManipulator(const RegistrationBaseManipulator& source) = delete;
			void operator=(const RegistrationBaseManipulator&) = delete;  //purposely not implemented
		};

		/*! @class RegistrationManipulator
		    @brief Grants public write access to Registration classes
		 */
		template<typename TRegistration>
		class RegistrationManipulator
		{
		public:
			using RegistrationType = TRegistration;

			/*! sets the DirectMapping kernel
			  @param pKernel the kernel for direct mapping
			  @eguarantee no fail
			 */
			virtual void setDirectMapping(typename RegistrationType::DirectMappingType* pKernel);

			/*! sets the InverseMapping kernel
			  @param pKernel the kernel for inverse mapping
			  @eguarantee no fail
			 */
			virtual void setInverseMapping(typename RegistrationType::InverseMappingType* pKernel);

			using TagMapType = typename RegistrationType::TagMapType;

			/*! @Sets the tags of a registration by replacing the existing tag map with the passed one.
			 * @remark If tags do not contain the tag "RegistrationUID" it will be added automatically.
			 * If it is present it stays untouched. If you define your own UID ensure that it is unique.
			@eguarantee strong
			*/
			virtual void setTagValues(const TagMapType& tags);

			/*! @brief allows non const access to the registration tags.
			@eguarantee no fail
			*/
			virtual TagMapType& getTagValues();

			RegistrationManipulator(RegistrationType* pI);

		protected:
			RegistrationType* _pInterface;

		private:
			//No copy constructor allowed
			RegistrationManipulator(const RegistrationManipulator& source) = delete;
			void operator=(const RegistrationManipulator&) = delete;  //purposely not implemented
		};

	}  // namespace core
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapRegistrationManipulator.tpp"
#endif

#endif
