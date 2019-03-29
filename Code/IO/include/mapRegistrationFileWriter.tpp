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


#ifndef __MAP_REGISTRATION_FILE_WRITER_TPP
#define __MAP_REGISTRATION_FILE_WRITER_TPP

#include "mapRegistrationFileWriter.h"
#include "mapRegistrationManipulator.h"
#include "mapMissingProviderException.h"
#include "mapRegistrationFileTags.h"
#include "mapSDXMLFileWriter.h"
#include "mapFileDispatch.h"
#include "mapConvert.h"

namespace map
{
	namespace io
	{
		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		bool
		RegistrationFileWriter<VMovingDimensions, VTargetDimensions>::
		write(const RegistrationType* registration, const core::String& path) const
		{
			if (!registration)
			{
				mapDefaultExceptionMacro( << "Cannot serialize registration. Passed registration object is NULL.");
			}

			::map::core::String fileName = core::FileDispatch::getName(path);
			::map::core::String dir = core::FileDispatch::getPath(path);

			typename DirectKernelWriterBaseType::RequestType directRequest(registration->getDirectMapping(),
					dir, fileName + "_D", _expandLazyKernels, &(registration->getInverseMapping()));
			typename InverseKernelWriterBaseType::RequestType inverseRequest(registration->getInverseMapping(),
					dir, fileName + "_I", _expandLazyKernels, &(registration->getDirectMapping()));

			DirectKernelWriterBaseType* pDirectWriter = DirectKernelWriterStackType::getProvider(directRequest);
			InverseKernelWriterBaseType* pInverseWriter = InverseKernelWriterStackType::getProvider(
						inverseRequest);

			mapLogInfoMacro( << "Write registration. Registration: " << registration << std::endl);

			if (!pDirectWriter)
			{
				mapExceptionMacro(::map::core::MissingProviderException,
								  << "No responsible writer available for given direct request. Request:" << directRequest);
			}

			if (!pInverseWriter)
			{
				mapExceptionMacro(::map::core::MissingProviderException,
								  << "No responsible writer available for given inverse request. Request:" << inverseRequest);
			}

			structuredData::Element::Pointer spDirectKernelStream = pDirectWriter->storeKernel(directRequest);
			structuredData::Element::Pointer spInverseKernelStream = pInverseWriter->storeKernel(
						inverseRequest);

			assert(spDirectKernelStream.IsNotNull());
			assert(spInverseKernelStream.IsNotNull());

			structuredData::Element::Pointer spRegElement = structuredData::Element::New();

			spRegElement->setTag(tags::Registration);

			//add tags
			::map::core::RegistrationBase::TagMapType tagMap = registration->getTags();

			for (auto & pos : tagMap)
			{
				structuredData::Element::Pointer spTagElement = structuredData::Element::New();
				spTagElement->setTag(tags::RegistrationTag);
				spTagElement->setValue(pos.second);
				spTagElement->setAttribute(tags::RegistrationTagName, pos.first);

				spRegElement->addSubElement(spTagElement);
			}

			//add dimensions
			spRegElement->addSubElement(structuredData::Element::createElement(tags::MovingDimensions,
										::map::core::convert::toStr(registration->getMovingDimensions())));
			spRegElement->addSubElement(structuredData::Element::createElement(tags::TargetDimensions,
										::map::core::convert::toStr(registration->getTargetDimensions())));

			//add kernels
			spDirectKernelStream->setAttribute(tags::KernelID, tags::direct);
			spInverseKernelStream->setAttribute(tags::KernelID, tags::inverse);

			spRegElement->addSubElement(spDirectKernelStream);
			spRegElement->addSubElement(spInverseKernelStream);

			//store in file
			structuredData::XMLFileWriter::Pointer spWriter = structuredData::XMLFileWriter::New();
			spWriter->write(path, spRegElement);

			return true;
		}

		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationFileWriter<VMovingDimensions, VTargetDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			os << indent << "ExpandLazyKernels: " << _expandLazyKernels << std::endl;
		}

		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		RegistrationFileWriter<VMovingDimensions, VTargetDimensions>::
		RegistrationFileWriter() 
		{}

		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		RegistrationFileWriter<VMovingDimensions, VTargetDimensions>::
		~RegistrationFileWriter()
		= default;

		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		bool
		RegistrationFileWriter<VMovingDimensions, VTargetDimensions>::
		getExpandLazyKernels() const
		{
			return _expandLazyKernels;
		}

		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationFileWriter<VMovingDimensions, VTargetDimensions>::
		setExpandLazyKernels(bool expandLazyKernels)
		{
			_expandLazyKernels = expandLazyKernels;
		}

	} // end namespace io
} // end namespace map

#endif
