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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapUID.h $
*/




#ifndef __MAP_UID_H
#define __MAP_UID_H

#include <typeinfo>

#include "itkLightObject.h"

#include "mapMacros.h"
#include "mapString.h"
#include "mapMAPAlgorithmsExports.h"

namespace map
{
	namespace algorithm
	{

		/*! @class UID
		@brief This class is used to represent unique identification for algorithms.

		The UID of a MatchPoint algorithm consists of 4 parts:\n
		- Namespace: Namespace (e.g. organisation, work group) of the algorithm
		- Name: The Name of an algorithm. It also implicitly identifies the intended use
		and problem statements inteded to be solved respectivly. If the intended use of
		an algorithm diverges, a new algorithm UID with an other name should be used.
		- Version: Indicates a change in an algorithm (without touching its
		intended use). E.g. if Parameters are tweaked, computations are refined or new
		properties are added without changing the tackled problem statement, this would be
		a version change.
		- Build number: Just indicates when the binary of an algorithm was build. The changing
		of the build number is no indication for a changing of algorithm or its intended use.
		.
		@sa AlgorithmIdentificationInterface
		@ingroup UID
		*/
		class MAPAlgorithms_EXPORT UID : public ::itk::LightObject
		{
		public:
			/** Smart pointer typedef support. */
			typedef UID  Self;
			typedef ::itk::LightObject  Superclass;
			typedef ::itk::SmartPointer<Self>  Pointer;
			typedef ::itk::SmartPointer<const Self>  ConstPointer;

			/** Run-time type information (and related methods). */
			itkTypeMacro(UID, LightObject);

			typedef core::String NamespaceType;
			typedef core::String NameType;
			typedef core::String VersionType;
			typedef core::String BuildTagType;

			/**
			* @brief Creates a MetaProperty instance, initializes it and returns it via smartpointer.
			* @return A pointer to the MetaProperty.
			* @param name The name of the associated MetaProperty
			* @param type_info The type info of the value type used for the MetaProperty
			* @param isReadable Indicates if the property is readable
			* @param isWritable Indicates if the property is writable
			* @eguarantee strong
			*/
			static Pointer New(const NamespaceType &ns, const NameType &name, const VersionType &version, const BuildTagType &buildTag);

			/**
			* @brief Returns the namespace of the algorithm.
			* @eguarantee strong
			* @return A constant reference to the namespace
			*/
			const NamespaceType &getNamespace() const;

			/**
			* @brief Returns the name of the algorithm.
			* @eguarantee strong
			* @return A constant reference to the name
			*/
			const NameType &getName() const;

			/**
			* @brief Returns the version of the algorithm.
			* @eguarantee strong
			* @return A constant reference to the version
			*/
			const VersionType &getVersion() const;

			/**
			* @brief Returns the build number of the algorithm.
			* @eguarantee strong
			* @return A constant reference to the build number
			*/
			const BuildTagType &getBuildTag() const;

			/**
			* @brief Converts the UID into a display string containing all informations.
			* @eguarantee strong
			* @return A constant string representing the whole UID.
			*/
			const core::String toStr() const;

		protected:
			NamespaceType _namespace;
			NameType _name;
			VersionType _version;
			BuildTagType _buildTag;

			/**
			* Defines the default behavior for printing out this element
			* @eguarantee strong
			* @param os An output stream
			*/
			virtual void PrintSelf(std::ostream &os, ::itk::Indent indent) const;

			~UID();
			UID(const NamespaceType &ns, const NameType &name, const VersionType &version, const BuildTagType &buildTag);
		private:
			UID(const Self &);//purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

		/** Helper function that allows to compare uids directly or with wild cards,
		 * thus ignoring parts of the uid.
		 * @remark If at least one of the uids points to NULL
		 * the result is always false;
		 * @param [in] uid1 The first uid.
		 * @param [in] uid2 The second uid.
		 * @param [in] wcNamespace Indicates if the namespace is wild carded. (True: ignore).
		 * @param [in] wcName Indicates if the name is wild carded. (True: ignore).
		 * @param [in] wcVersion Indicates if the version is wild carded. (True: ignore).
		 * @param [in] wcBuild Indicates if the build is wild carded. (True: ignore).
		 * @return True, if the uids match (regarding the wildcard settings).
		 * @eguarantee strong
		 * @TODO add to unit test*/
		MAPAlgorithms_EXPORT bool compareUIDs(const UID *uid1, const UID *uid2, bool wcNamespace = false, bool wcName = false, bool wcVersion = false, bool wcBuild = false);

		/** Helper function that allows to compare uids directly or with wild cards,
		 * thus ignoring parts of the uid.
		 * @param [in] uid1 The first uid.
		 * @param [in] uid2 The second uid.
		 * @param [in] wcNamespace Indicates if the namespace is wild carded. (True: ignore).
		 * @param [in] wcName Indicates if the name is wild carded. (True: ignore).
		 * @param [in] wcVersion Indicates if the version is wild carded. (True: ignore).
		 * @param [in] wcBuild Indicates if the build is wild carded. (True: ignore).
		 * @return True, if the uids match (regarding the wildcard settings).
		 * @eguarantee strong
		 * @TODO add to unit test*/
		MAPAlgorithms_EXPORT bool compareUIDs(const UID &uid1, const UID &uid2, bool wcNamespace = false, bool wcName = false, bool wcVersion = false, bool wcBuild = false);


	}
}

#endif
