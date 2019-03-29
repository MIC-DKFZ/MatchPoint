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


#ifndef __MAP_MAPPING_PERFORMER_BASE_H
#define __MAP_MAPPING_PERFORMER_BASE_H

#include "mapServiceProvider.h"

namespace map
{
	namespace core
	{
		/*! @class MappingPerformerBase
		* @brief Base class for any instance in MatchPoint that provides the service of performing a registration on any kind of data.
		*
		* @ingroup MappingTask
		* @tparam TPerformerRequest the request class, used to perform the task.
		*/
		template <class TPerformerRequest>
		class MappingPerformerBase : public services::ServiceProvider< TPerformerRequest >
		{
		public:
			/*! Standard class typedefs. */
			using Self = MappingPerformerBase<TPerformerRequest>;
			using Superclass = services::ServiceProvider<TPerformerRequest>;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(MappingPerformerBase, ServiceProvider);

			using RequestType = typename Superclass::RequestType;

			using RegistrationType = typename RequestType::RegistrationType;
			using RegistrationConstPointer = typename RegistrationType::ConstPointer;
			using InputDataType = typename RequestType::InputDataType;
			using InputDataConstPointer = typename InputDataType::ConstPointer;
			using ResultDataType = typename RequestType::ResultDataType;
			using ResultDataPointer = typename ResultDataType::Pointer;

			/*! Registers the input data and returns the result data.
			 * @eguarantee strong
			 * @param [in] request Referenz to the request that contains the registration and the input data
			 * @return Smart pointer to the result image.
			 */
			virtual ResultDataPointer performMapping(const RequestType& request) const = 0;

		protected:

			MappingPerformerBase() = default;
			~MappingPerformerBase() override = default;

		private:
			MappingPerformerBase(const Self&) = delete;  //purposely not implemented
			void operator=(const Self&) = delete;  //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#endif
