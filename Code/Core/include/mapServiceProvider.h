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

#ifndef __MAP_SERVICE_PROVIDER_H
#define __MAP_SERVICE_PROVIDER_H

#include "mapString.h"

#include "itkObject.h"

namespace map
{
	namespace core
	{
		namespace services
		{

			/*! @class ServiceProvider
			* @brief Base class for any instance in MatchPoint that provides services
			*
			* In different parts of the code MatchPoint uses a dynamic dispatch mechanism
			* to get a proper provider for a needed type of service (e.g. the inversion of
			* registration kernels). To allow dynamic selection of the right code and integration
			* in the service fascility, you can deriver from ServiceProvider the base class of a
			* special service provider type.
			*
			* @sa ServiceStack
			* @ingroup Services
			*/
			template <class TRequestType>
			class ServiceProvider : public itk::Object
			{
			public:
				/*! Standard class typedefs. */
				using Self = ServiceProvider<TRequestType>;
				using Superclass = itk::Object;
				using Pointer = itk::SmartPointer<Self>;
				using ConstPointer = itk::SmartPointer<const Self>;

				itkTypeMacro(ServiceProvider, itk::Object);

				using RequestType = TRequestType;

				/*! Uses the passed request data to check if the provider is able to provide the service for
				 * this request.
				 * @return Indicates if the provider offers the right solution.
				 * @retval true Provider can handle the request.
				 * @retval false Provider is not able to handle the request.*/
				virtual bool canHandleRequest(const RequestType& request) const = 0;

				/*! Returns an ID of the provider as string. May be equal to GetClassName(), but it may differ.
				 * @return Service provider ID.*/
				virtual String getProviderName() const = 0;

				/*! Returns an ID of the provider as string. May be equal to GetClassName(), but it may differ.
				 * @return Service provider ID.
				 * @remark It is a return by value, becaus it might be possible that the description is generated on line
				 * when calling this method.*/
				virtual String getDescription() const = 0;

			protected:
				ServiceProvider() = default;
				~ServiceProvider() override = default;

			private:
				ServiceProvider(const Self&) = delete;  //purposely not implemented
				void operator=(const Self&) = delete;  //purposely not implemented
			};


		} // end namespace services
	} // end namespace core
} // end namespace map

#endif
