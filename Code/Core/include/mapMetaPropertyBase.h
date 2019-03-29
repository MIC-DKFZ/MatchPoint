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



#ifndef __MAP_META_PROPERTY_BASE_H
#define __MAP_META_PROPERTY_BASE_H

#include <typeinfo>
#include <iostream>

#include "itkLightObject.h"

#include "mapMacros.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{
		/*! @class MetaPropertyBase
		* @brief Base class designed as common interface for MetaProperties.
		*
		* MetaProperties are inter alia used to realize a generic streaming of algorithm
		* properties like parameter settings.
		*
		* @ingroup Core
		*/

		class MAPCore_EXPORT MetaPropertyBase : public ::itk::LightObject
		{
		public:
			/** Smart pointer typedef support. */
			using Self = MetaPropertyBase;
			using Superclass = ::itk::LightObject;
			using Pointer = ::itk::SmartPointer<Self>;
			using ConstPointer = ::itk::SmartPointer<const Self>;


			/** Run-time type information (and related methods). */
			itkTypeMacro(MetaPropertyBase, LightObject);
			itkCloneMacro(Self);

			/**
			 * @brief Returns the unique type name of the value type that stores the property.
			 * @return A pointer to a const char array containing the unique type name.
			 * @eguarantee strong
			 * @ex
			 */
			virtual const char* getMetaPropertyTypeName() const = 0;

			/**
			 * @brief Returns the type_id of the value type that stores the property.
			 * @eguarantee strong
			 * @return A constant reference to a std::type_info object
			 */
			virtual const std::type_info& getMetaPropertyTypeInfo() const = 0;

		protected:
			~MetaPropertyBase() override;
			MetaPropertyBase();

			/**
			 * Defines the default behavior for printing out this element
			 * @eguarantee strong
			 * @param os An output stream
			 */
			void PrintSelf(std::ostream& os, itk::Indent indent) const override;

		private:
			MetaPropertyBase(const Self&) = delete; //purposely not implemented
			void operator=(const Self&) = delete;  //purposely not implemented
		};
	}  // namespace core
}  // namespace map

#endif
