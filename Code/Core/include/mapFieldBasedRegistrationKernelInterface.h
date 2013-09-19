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
			FieldBasedRegistrationKernelInterface(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

	}
}

#endif
