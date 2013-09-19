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


#ifndef __MAP_REGISTRATION_FILE_WRITER_H
#define __MAP_REGISTRATION_FILE_WRITER_H

#include "mapStaticServiceStack.h"
#include "mapRegistrationKernelWriterBase.h"
#include "mapRegistration.h"
#include "mapKernelWriterLoadPolicy.h"
#include "mapString.h"

#include "itkObject.h"

namespace map
{

	namespace io
	{
		/*! @class RegistrationFileWriter
		* @brief Class stores a registration object in a file.
		*
		* This class is used to store registration to file(s).\n
		* To store the registrations the class uses a static service stack populated with
		* RegistrationKernelWriters.
		* You can change the stack content by the static class methods of the member typedef DirectKernelWriterStackType or InverseKernelWriterStackType.\n
		*
		* @ingroup RegOperation
		* @ingroup Registration
			* @tparam VMovingDimensions Dimensions of the moving space of the registration.
			* @tparam VTargetDimensions Dimensions of the target space of the registration.
		* @tparam TLoadPolicy the load policy that should be used for the provider stack of the recombinator.
		*/
		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		class RegistrationFileWriter: public itk::Object
		{
		public:
			/*! Standard class typedefs. */
			typedef RegistrationFileWriter<VMovingDimensions, VTargetDimensions>  Self;
			typedef itk::Object                    Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(RegistrationFileWriter, itk::Object);
			itkNewMacro(Self);

			typedef core::Registration<VMovingDimensions, VTargetDimensions>  RegistrationType;
			typedef typename RegistrationType::Pointer                 RegistrationPointer;

			itkStaticConstMacro(MovingDimensions, unsigned int, VMovingDimensions);
			itkStaticConstMacro(TargetDimensions, unsigned int, VTargetDimensions);

			typedef RegistrationKernelWriterBase<VMovingDimensions, VTargetDimensions>
			DirectKernelWriterBaseType;
			typedef RegistrationKernelWriterBase<VTargetDimensions, VMovingDimensions>
			InverseKernelWriterBaseType;

		protected:
			typedef core::services::ServiceStack<DirectKernelWriterBaseType, KernelWriterLoadPolicy<VMovingDimensions, VTargetDimensions> >
			ConcreteDirectKernelWriterStackType;
			typedef core::services::ServiceStack<InverseKernelWriterBaseType, KernelWriterLoadPolicy<VTargetDimensions, VMovingDimensions> >
			ConcreteInverseKernelWriterStackType;
		public:
			typedef core::services::StaticServiceStack<ConcreteDirectKernelWriterStackType>
			DirectKernelWriterStackType;
			typedef core::services::StaticServiceStack<ConcreteInverseKernelWriterStackType>
			InverseKernelWriterStackType;

			/*! Stores the passed registration in the specified path.
			 * @eguarantee strong
			 * @param [in] registration Pointer to the registration.
			 * @param [in] path Defines the file path were the registration should be stored. The write process
			 * may generate more then one file in the specified directory depending on the kernels to store.
			 * @pre registration must point to a valid instance.

			 */
			bool write(const RegistrationType* registration, const core::String& path) const;

			bool getExpandLazyKernels() const;
			void setExpandLazyKernels(bool expandLazyKernels);

		protected:
			RegistrationFileWriter();
			virtual ~RegistrationFileWriter();

			/*! Determines if lazy kernels that have not been processed should be stored with there generation functors (false)
			 * or should be generated and stored with the actual kernel data (true). Default is true.*/
			bool _expandLazyKernels;

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

		private:
			RegistrationFileWriter(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};
	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapRegistrationFileWriter.tpp"
#endif

#endif
