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




#ifndef __REGISTRATION_KERNEL_INTERFACE_H
#define __REGISTRATION_KERNEL_INTERFACE_H

namespace map
{
	namespace core
	{

		/*! @class RegistrationKernelInterface
		    This class is the base class for the registration kernels.
				@ingroup RegKernel
		 */
		class RegistrationKernelInterface
		{
		public:
			typedef RegistrationKernelInterface Self;

			/*! @brief Gets the number of input dimensions
			@eguarantee no fail
			*/
			virtual unsigned int getInputDimensions() const = 0;

			/*! @brief Gets the number of output dimensions
			@eguarantee no fail
			*/
			virtual unsigned int getOutputDimensions() const = 0;

		protected:

			RegistrationKernelInterface() {};
			virtual ~RegistrationKernelInterface() {};

		private:
			//No copy constructor allowed
			RegistrationKernelInterface(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

	}
}

#endif
