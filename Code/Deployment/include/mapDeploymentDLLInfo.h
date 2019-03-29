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


#ifndef __MAP_DEPLOYMENT_DLL_INFO_H
#define __MAP_DEPLOYMENT_DLL_INFO_H

#include "mapUID.h"
#include "mapMAPDeploymentExports.h"

namespace map
{
	namespace deployment
	{

		/** @class DLLInfo
		* @brief Basis information of deployment DLLs that contain MatchPoint algorithms.
		*
		* Structur contains the UID of an algorithm and the file path to the DLL that
		* contains that algorithm.
		* @ingroup DeployHost
		*/
		class MAPDeployment_EXPORT DLLInfo: public itk::LightObject
		{
		public:
			/** Smart pointer typedef support. */
			using Self = DLLInfo;
			using Superclass = ::itk::LightObject;
			using Pointer = ::itk::SmartPointer<Self>;
			using ConstPointer = ::itk::SmartPointer<const Self>;

			/** Run-time type information (and related methods). */
			itkTypeMacro(DLLInfo, ::itk::LightObject);

			/**
			* @brief Creates a DeploymentDLLInfo instance, initializes it and returns it via smartpointer.
			* @return A pointer to the MetaProperty.
			* @pre pUID must not be NULL.
			* @param pUID pointer to the UID of the algorithm offered by the DLL.
			* @param libraryFilePath File path of the DLL containing the algorithm
			* @eguarantee strong
			*/
			static Pointer New(const map::algorithm::UID* pUID,
							   const core::String& libraryFilePath,
							   const core::String& profileStr);

			const map::algorithm::UID& getAlgorithmUID() const;
			const core::String& getAlgorithmProfileStr() const;

			const core::String& getLibraryFilePath() const;

		protected:
			DLLInfo(const map::algorithm::UID* pUID,
					const core::String& libraryFilePath,
					core::String  profileStr);

			~DLLInfo() override;

			map::algorithm::UID::ConstPointer _spAlgorithmUID;
			::map::core::String _libraryFilePath;
			/** Profile string (xml structured) associated with the algorithm*/
			::map::core::String _profileStr;
			/** Description string associated with the algorithm*/
			::map::core::String _description;

		private:
			DLLInfo(const Self&) = delete; //purposely not implemented
			void operator=(const Self&) = delete;  //purposely not implemented

		};


	} // end namespace deployment
} // end namespace map

#endif
