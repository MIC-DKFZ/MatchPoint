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


#ifndef __MAP_MAPPING_PERFORMER_REQUEST_BASE_H
#define __MAP_MAPPING_PERFORMER_REQUEST_BASE_H

#include "itkMacro.h"

namespace map
{
	namespace core
	{
		/*! @class MappingPerformerRequestBase
		* @brief Base class used by the MappingPerformerRequests.
		*
		* This class is used as request type for the provider stack of MappingPerformers
		* @ingroup MappingTask
		* @sa MappingPerformer
		* @tparam TRegistration the registration class, that should be used to perform the task.
		* @tparam TInputData Type of the input data.
			* @tparam TResultData Type of the data in the target space.
		*/
		template <class TRegistration, class TInputData, class TResultData>
		class MappingPerformerRequestBase
		{
		public:
			using RegistrationType = TRegistration;
			using RegistrationConstPointer = typename RegistrationType::ConstPointer;

			using InputDataType = TInputData;
			using InputDataConstPointer = typename InputDataType::ConstPointer;

			using ResultDataType = TResultData;
			using ResultDataConstPointer = typename ResultDataType::ConstPointer;

			itkStaticConstMacro(MovingDimensions, unsigned int, RegistrationType::MovingDimensions);
			itkStaticConstMacro(TargetDimensions, unsigned int, RegistrationType::TargetDimensions);

			RegistrationConstPointer _spRegistration;
			InputDataConstPointer _spInputData;

		protected:
			MappingPerformerRequestBase(const RegistrationType& registration, const InputDataType& inputData);
			MappingPerformerRequestBase(const RegistrationType* pRegistration, const InputDataType* pInputData);
			virtual ~MappingPerformerRequestBase();

		private:
			// purposely not implemented
			MappingPerformerRequestBase(const MappingPerformerRequestBase&);
			// purposely not implemented
			void operator=(const MappingPerformerRequestBase&);
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapMappingPerformerRequestBase.tpp"
#endif

#endif
