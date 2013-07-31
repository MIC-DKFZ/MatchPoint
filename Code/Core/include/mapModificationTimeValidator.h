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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapModificationTimeValidator.h $
*/


#ifndef __MAP_MODIFICATION_TIME_VALIDTOR_H
#define __MAP_MODIFICATION_TIME_VALIDTOR_H

#include "itkObject.h"
#include "itkTimeStamp.h"

#include <vector>
#include <iostream>

#include "mapMacros.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{
		/*! @class ModificationTimeValidator
		* @brief Helper class that allows to handles itk modification time consistency problems when using dll deployment for algoritms.
		*
		* When using a dll deployment strategy for algorithms (at least for windows systems)
		* the itk modification time (MTime) becomes inconsistent between the algorithms out of a dll
		* and data loaded by the host. (Reason is that dlls and host have different static variables
		* defining the current MTime). This leads inter alia to a false up to date conclusion
		* in dll deployed algorithms. This class serves as work around that helps to correctly detect
		* changes in modification time. Basic principle is that the MTime of an watched object is taged
		* by a MTime of the own context. And this "Tag" is changed, when the object or its MTime changes.
		* This may lead to false positives in modification detection. But it will allow to detect all
		* real changes.
		*/
		class MAPCore_EXPORT ModificationTimeValidator
		{
		public:
			/*! Standard class typedefs. */
			typedef ModificationTimeValidator  Self;
			typedef ::itk::Object	  WatchedObjectType;
			typedef unsigned long   MTimeType;

			/*! Constructor.
			* @eguarantee strong */
			ModificationTimeValidator(const WatchedObjectType *obj);

			/*! Constructor.
			* @eguarantee strong */
			ModificationTimeValidator();

			/*! Destructor.
			* @eguarantee none throw*/
			~ModificationTimeValidator();

			/*! Set the watched object and update the internal time stamp.
			* @eguarantee strong */
			void setWatchedObject(const WatchedObjectType *obj);

			/*! Get the point defining the origin of the volume.
			* @eguarantee strong */
			MTimeType getMTime() const;

		protected:
			WatchedObjectType::ConstPointer _spObj;
			mutable ::itk::TimeStamp _ownTimeStamp;
			mutable MTimeType _objTimeStamp;
		};

	} // end namespace core
} // end namespace map

#endif
