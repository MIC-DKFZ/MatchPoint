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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapMetaPropertyBase.h $
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
			typedef MetaPropertyBase  Self;
			typedef ::itk::LightObject  Superclass;
			typedef ::itk::SmartPointer<Self>  Pointer;
			typedef ::itk::SmartPointer<const Self>  ConstPointer;


			/** Run-time type information (and related methods). */
			itkTypeMacro(MetaPropertyBase, LightObject);
			itkCloneMacro(Self);

			/**
			 * @brief Returns the unique type name of the value type that stores the property.
			 * @return A pointer to a const char array containing the unique type name.
			 * @eguarantee strong
			 * @ex
			 */
			virtual const char *getMetaPropertyTypeName() const = 0;

			/**
			 * @brief Returns the type_id of the value type that stores the property.
			 * @eguarantee strong
			 * @return A constant reference to a std::type_info object
			 */
			virtual const std::type_info &getMetaPropertyTypeInfo(void) const = 0;

		protected:
			virtual ~MetaPropertyBase();
			MetaPropertyBase();

			/**
			 * Defines the default behavior for printing out this element
			 * @eguarantee strong
			 * @param os An output stream
			 */
			virtual void PrintSelf(std::ostream &os, itk::Indent indent) const;

		private:
			MetaPropertyBase(const Self &);//purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};
	}
}

#endif
