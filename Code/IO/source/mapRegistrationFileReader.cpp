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


#include "mapRegistrationFileReader.h"
#include "mapSDXMLFileReader.h"
#include "mapMissingProviderException.h"
#include "mapSDElement.h"
#include "mapRegistrationFileTags.h"
#include "mapRegistrationManipulator.h"

namespace map
{
	namespace io
	{

		RegistrationFileReader::LoadedRegistrationPointer
		RegistrationFileReader::
		read(const  core::String& registrationFile) const
		{
			structuredData::XMLFileReader::Pointer spReader = structuredData::XMLFileReader::New();

			mapLogInfoMacro( << "Read registration file. File: " << registrationFile);

			structuredData::Element::Pointer spFileData = spReader->read(registrationFile);

			if (spFileData->getSubElementsCount() < 1)
			{
				mapDefaultExceptionMacro( << "Illegal registration file. No registration stored.");
			}

			//don't need the root, but the first sub element.
			spFileData = spFileData->getSubElement(0);

			structuredData::Element::SubElementIteratorType directKernelPos =
				structuredData::findNextSubElement(spFileData->getSubElementBegin(), spFileData->getSubElementEnd(),
												   tags::Kernel, tags::KernelID, tags::direct);

			if (directKernelPos == spFileData->getSubElementEnd())
			{
				mapDefaultExceptionMacro( << "Illegal registration file. No direct kernel entry found");
			}

			structuredData::Element::SubElementIteratorType inverseKernelPos =
				structuredData::findNextSubElement(spFileData->getSubElementBegin(), spFileData->getSubElementEnd(),
												   tags::Kernel, tags::KernelID, tags::inverse);

			if (inverseKernelPos == spFileData->getSubElementEnd())
			{
				mapDefaultExceptionMacro( << "Illegal registration file. No inverse kernel entry found");
			}

			KernelLoaderBaseType::RequestType directRequest(*directKernelPos, _preferLazyLoading);
			KernelLoaderBaseType::RequestType inverseRequest(*inverseKernelPos, _preferLazyLoading);

			KernelLoaderBaseType* pDirectLoader = LoaderStackType::getProvider(directRequest);
			KernelLoaderBaseType::GenericKernelPointer spDirectKernel;

			if (!pDirectLoader)
			{
				mapLogDebugMacro( <<
								  "No responsible loader available for given direct request. Try to load inverse request first and retry with additional complementary kernel.");
			}
			else
			{
				spDirectKernel = pDirectLoader->loadKernel(directRequest);
				inverseRequest._spComplementaryKernel = dynamic_cast< ::map::core::DimensionlessRegistrationKernelBase*>
														(spDirectKernel.GetPointer());
			}

			KernelLoaderBaseType* pInverseLoader = LoaderStackType::getProvider(inverseRequest);
			KernelLoaderBaseType::GenericKernelPointer spInverseKernel;

			if (!pInverseLoader)
			{
				mapExceptionMacro(::map::core::MissingProviderException,
								  << "No responsible loader available for given inverse request. Request:" << inverseRequest);
			}
			else
			{
				spInverseKernel = pInverseLoader->loadKernel(inverseRequest);
			}

			if (spDirectKernel.IsNull())
			{
				//retry direct kernel loading with additional complimentary kernel information
				directRequest._spComplementaryKernel = dynamic_cast< ::map::core::DimensionlessRegistrationKernelBase*>
													   (spInverseKernel.GetPointer());
				pDirectLoader = LoaderStackType::getProvider(directRequest);

				if (!pDirectLoader)
				{
					mapExceptionMacro(::map::core::MissingProviderException,
									  << "No responsible loader available for given direct request. Request:" << directRequest);
				}

				spDirectKernel = pDirectLoader->loadKernel(directRequest);
			}

			LoadedRegistrationPointer spRegistration;

			pDirectLoader->addAsDirectKernel(spDirectKernel, spRegistration);
			pInverseLoader->addAsInverseKernel(spInverseKernel, spRegistration);

			//read registration tags
			::map::core::RegistrationBaseManipulator manip(spRegistration);
			::map::core::RegistrationBaseManipulator::TagMapType tagMap;
			structuredData::Element::SubElementIteratorType pos = structuredData::findNextSubElement(
						spFileData->getSubElementBegin(), spFileData->getSubElementEnd(), tags::RegistrationTag);

			while (pos != spFileData->getSubElementEnd())
			{
				if (!(*pos)->attributeExists(tags::RegistrationTagName))
				{
					mapLogInfoMacro( << "Error when reading registration. Tag is invalid, no tag name. Tag value: " <<
									 (*pos)->getValue());
				}
				else
				{
					tagMap.insert(std::make_pair((*pos)->getAttribute(tags::RegistrationTagName), (*pos)->getValue()));
				}

				++pos;
			}

			manip.setTagValues(tagMap);

			return spRegistration;
		}


		bool
		RegistrationFileReader::
		getPreferLazyLoading() const
		{
			return _preferLazyLoading;
		}

		void
		RegistrationFileReader::
		setPreferLazyLoading(bool preferLazyLoading)
		{
			_preferLazyLoading = preferLazyLoading;
		}

		void
		RegistrationFileReader::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			os << indent << "Prefere lazy loading :" << _preferLazyLoading << std::endl;
		}

		RegistrationFileReader::
		RegistrationFileReader(): _preferLazyLoading(true)
		{}

		RegistrationFileReader::
		~RegistrationFileReader()
		{}



	} // end namespace io
} // end namespace map
