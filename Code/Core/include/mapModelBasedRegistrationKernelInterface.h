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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapModelBasedRegistrationKernelInterface.h $
*/

#ifndef __MODEL_BASED_REGISTRATION_KERNEL_INTERFACE_H
#define __MODEL_BASED_REGISTRATION_KERNEL_INTERFACE_H

#include "mapString.h"

#include "itkArray.h"
#include <string>

namespace map
{
	namespace core
	{

		/*! @class ModelBasedRegistrationKernelInterface
		    This class is the interface for model based registration kernel classes.
		    @ingroup RegKernel
		 */
		class ModelBasedRegistrationKernelInterface
		{
		public:
			typedef ModelBasedRegistrationKernelInterface Self;

			typedef itk::Array<double> ParametersType;

			/*! gets the name of the model
			  @eguarantee strong
			  @return an String containing the model name
			 */
			virtual String getModelName() const = 0;


			/*! gets the parameters
			  @eguarantee strong
			  @return a ParametersType containing the parameters
			 */
			virtual ParametersType getParameters() const = 0;



		protected:
			ModelBasedRegistrationKernelInterface() {};
			virtual ~ModelBasedRegistrationKernelInterface() {};

		private:
			//No copy constructor allowed
			ModelBasedRegistrationKernelInterface(const Self &);
			void operator=(const Self &); //purposely not implemented
		};

	}
}

#endif
