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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapMappingPerformerRequestBase.h $
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
			typedef TRegistration RegistrationType;
			typedef typename RegistrationType::ConstPointer RegistrationConstPointer;

			typedef TInputData InputDataType;
			typedef typename InputDataType::ConstPointer InputDataConstPointer;

			typedef TResultData ResultDataType;
			typedef typename ResultDataType::ConstPointer ResultDataConstPointer;

			itkStaticConstMacro(MovingDimensions, unsigned int, RegistrationType::MovingDimensions);
			itkStaticConstMacro(TargetDimensions, unsigned int, RegistrationType::TargetDimensions);

			RegistrationConstPointer _spRegistration;
			InputDataConstPointer _spInputData;

		protected:
			MappingPerformerRequestBase(const RegistrationType &registration, const InputDataType &inputData);
			MappingPerformerRequestBase(const RegistrationType *pRegistration, const InputDataType *pInputData);
			virtual ~MappingPerformerRequestBase();

		private:
			// purposely not implemented
			MappingPerformerRequestBase(const MappingPerformerRequestBase &);
			// purposely not implemented
			void operator=(const MappingPerformerRequestBase &);
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapMappingPerformerRequestBase.tpp"
#endif

#endif
