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


#ifndef __MAP_REGISTRATION_FILE_READER_H
#define __MAP_REGISTRATION_FILE_READER_H

#include "itkObject.h"

#include "mapStaticServiceStack.h"
#include "mapRegistrationKernelLoaderBase.h"
#include "mapRegistration.h"
#include "mapKernelLoaderLoadPolicy.h"
#include "mapMAPIOExports.h"

namespace map
{

	namespace io
	{
		/*! @class RegistrationFileReader
		* @brief Class loads a registration object stored in a file.
		*
		* This class is used to load registration from file(s).\n
		* To load the registrations the class uses a static service stack populated with
		* RegistrationKernelLoaders for the direct and the inverse mapping direction.
		* You can change the stack content by the static class methods of the member typedef KernelLoaderStackType.\n
		*
		* @ingroup RegOperation
		* @ingroup Registration
		*/
		class MAPIO_EXPORT RegistrationFileReader: public itk::Object
		{
		public:
			/*! Standard class typedefs. */
			using Self = RegistrationFileReader;
			using Superclass = itk::Object;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(RegistrationFileReader, itk::Object);
			itkNewMacro(Self);

			using KernelLoaderBaseType = RegistrationKernelLoaderBase;

			using LoadedRegistrationType = core::RegistrationBase;
			using LoadedRegistrationPointer = core::RegistrationBase::Pointer;

		protected:
			typedef core::services::ServiceStack<KernelLoaderBaseType, KernelLoaderLoadPolicy >
			ConcreteLoaderStackType;
		public:
			using LoaderStackType = core::services::StaticServiceStack<ConcreteLoaderStackType>;

			/*! Reads the registration from the file and returns the object.
			 * The method throws expceptions if the there is a registration kernel stored with no suitable kernel reader.
			 * @pre the file must exist from where to read.
			 * @pre the process must have the rights to open and read the file.
			 * @eguarantee strong
			 * @param [in] registrationFile string that specifies the location of the registration file.
			 * @return Smart pointer to the loaded registration.
			 */
			LoadedRegistrationPointer read(const  core::String& registrationFile) const;

			/*! gets _preferLazyLoading */
			bool getPreferLazyLoading() const;
			/*! Sets _preferLazzyLoading . */
			void setPreferLazyLoading(bool preferLazyLoading);

		protected:
			RegistrationFileReader();
			~RegistrationFileReader() override;

			/*! Indicicates if the KernelLoader should prefer lazzy loading when loading a kernel takes a lot resources.
			 * (e.g. loading a field kernel with a large vector field: preferring lazy loading would only keep the reference to the
			 * file. The field wouldn't be loaded until realy needed to save memory. If lazy loading isn't preferred it is directly
			 * loaded, thus it can be directly used, but maybe unnecessarily occupies memory space.
			 */
			bool _preferLazyLoading{true};

			/*! Methods invoked by itk::LightObject::Print().  */
			void PrintSelf(std::ostream& os, itk::Indent indent) const override;

		private:

			RegistrationFileReader(const Self&) = delete;  //purposely not implemented
			void operator=(const Self&) = delete;  //purposely not implemented
		};
	} // end namespace io
} // end namespace map

#endif
