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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldBasedRegistrationKernelInterface.h $
*/

#ifndef __FIELD_BASED_REGISTRATION_KERNEL_INTERFACE_H
#define __FIELD_BASED_REGISTRATION_KERNEL_INTERFACE_H


namespace map
{
	namespace core
	{

		/*! @class FieldBasedRegistrationKernelInterface
		    This class is the interface for field based registration kernel classes.
		    @ingroup RegKernel
		 */
		class FieldBasedRegistrationKernelInterface
		{
		public:
			typedef FieldBasedRegistrationKernelInterface Self;


		protected:
			FieldBasedRegistrationKernelInterface() {};
			virtual ~FieldBasedRegistrationKernelInterface() {};

		private:
			//No copy constructor allowed
			FieldBasedRegistrationKernelInterface(const Self &source);
			void operator=(const Self &); //purposely not implemented

		};

	}
}

#endif
