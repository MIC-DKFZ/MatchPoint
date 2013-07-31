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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapLogbookMacros.h $
*/


#ifndef __MAP_LOGBOOK_MACROS_H
#define __MAP_LOGBOOK_MACROS_H

#include "mapLogbook.h"
#include "mapMacros.h"
#include "mapConfigure.h"
#include "mapString.h"

#include "itkMacro.h"

/*! @def mapLogDebugMacro
 * This macro is used to print debug information.
 * It should be used within methods of objects, that are derivered from
 * itk::LightObject or have the same interface (GetNameOfClass() and GetDebug()).
 * Use mapLogDebugObjMacro() for other methods of objects that do not meet the requirement.
 * @sa mapLogDebugObjMacro
 * Example usage looks like:
 * mapLogDebugMacro(<< "this is debug info" << this->SomeVariable);
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogDebugMacro(x)
#else
#define mapLogDebugMacro(x) \
	{ if (this->GetDebug())   \
		{ ::map::core::OStringStream mapMsg; \
			mapMsg << "In " __FILE__ ", line " << __LINE__ << "\n" \
			       << this->GetNameOfClass() << " (" << this << "): " x  \
			       << "\n"; \
			::map::core::Logbook::debug(mapMsg.str());\
		} \
	}
#endif

/*! @def mapLogDebugStaticMacro
 * This macro is used to print debug information.
 * It should be used within static methods and global functions.
 * Example usage looks like:
 * mapLogDebugStaticMacro(<< "this is debug info");
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogDebugStaticMacro(x)
#else
#define mapLogDebugStaticMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "In " __FILE__ ", line " << __LINE__ << "\n" \
		       x << "\n"; \
		::map::core::Logbook::debug(mapMsg.str());\
	}
#endif

/*! @def mapLogDebugObjMacro
 * This macro is used to print debug information.
 * It should be used within methods of objects, where mapLogDebugMacro cannot
 * be used (e.g. not derivered from itk::LightObject).
 * @sa mapLogDebugMacro
 * Example usage looks like:
 * mapLogDebugObjMacro(<< "this is debug info" << this->SomeVariable);
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogDebugObjMacro(x)
#else
#define mapLogDebugObjMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "In " __FILE__ ", line " << __LINE__ << ", sig "\
		       << MAP_FUNCTION_SIGNATURE << "\n" << " (& " << this << "): " x  \
		       << "\n"; \
		::map::core::Logbook::debug(mapMsg.str());\
	}
#endif

/*! @def mapLogInfoMacro
 * This macro is used to print any information.
 * It should be used within methods of objects, that are derivered from
 * itk::LightObject or have the same interface (GetNameOfClass() and GetDebug()).
 * Use mapLogInfoObjMacro() for other methods of objects that do not meet the requirement.
 * @sa mapLogInfoObjMacro
 * Example usage looks like:
 * mapLogInfoMacro(<< "this is an info" << this->SomeVariable);
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogInfoMacro(x)
#else
#define mapLogInfoMacro(x) \
	{ if (this->GetDebug())   \
		{ ::map::core::OStringStream mapMsg; \
			mapMsg << "In " __FILE__ ", line " << __LINE__ << "\n" \
			       << this->GetNameOfClass() << " (" << this << "): " x  \
			       << "\n"; \
			::map::core::Logbook::info(mapMsg.str());\
		} \
	}
#endif

/*! @def mapLogInfoStaticMacro
 * This macro is used to print any information.
 * It should be used within static methods and global functions.
 * Example usage looks like:
 * mapLogInfoStaticMacro(<< "this is debug info");
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogInfoStaticMacro(x)
#else
#define mapLogInfoStaticMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "In " __FILE__ ", line " << __LINE__ << "\n" \
		       x << "\n"; \
		::map::core::Logbook::info(mapMsg.str());\
	}
#endif

/*! @def mapLogInfoObjMacro
 * This macro is used to print any information.
 * It should be used within methods of objects, where mapLogInfoMacro cannot
 * be used (e.g. not derivered from itk::LightObject).
 * @sa mapLogInfoMacro
 * Example usage looks like:
 * mapLogInfoObjMacro(<< "this is debug info" << this->SomeVariable);
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogInfoObjMacro(x)
#else
#define mapLogInfoObjMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "In " __FILE__ ", line " << __LINE__ << ", sig "\
		       << MAP_FUNCTION_SIGNATURE << "\n" << " (& " << this << "): " x  \
		       << "\n"; \
		::map::core::Logbook::info(mapMsg.str());\
	}
#endif

/*! @def mapLogWarningMacro
 * This macro is used to print a warning.
 * It should be used within methods of objects, that are derivered from
 * itk::LightObject or have the same interface (GetNameOfClass() and GetDebug()).
 * Use mapLogWarningObjMacro() for other methods of objects that do not meet the requirement.
 * @sa mapLogWarningObjMacro
 * Example usage looks like:
 * mapLogWarningMacro(<< "this is an info" << this->SomeVariable);
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogWarningMacro(x)
#else
#define mapLogWarningMacro(x) \
	{ if (this->GetDebug())   \
		{ ::map::core::OStringStream mapMsg; \
			mapMsg << "In " __FILE__ ", line " << __LINE__ << "\n" \
			       << this->GetNameOfClass() << " (" << this << "): " x  \
			       << "\n"; \
			::map::core::Logbook::warning(mapMsg.str());\
		} \
	}
#endif

/*! @def mapLogWarningStaticMacro
 * This macro is used to print a warning.
 * It should be used within static methods and global functions.
 * Example usage looks like:
 * mapLogWarningStaticMacro(<< "this is debug info");
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogWarningStaticMacro(x)
#else
#define mapLogWarningStaticMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "In " __FILE__ ", line " << __LINE__ << "\n" \
		       x << "\n"; \
		::map::core::Logbook::warning(mapMsg.str());\
	}
#endif

/*! @def mapLogWarningObjMacro
 * This macro is used to print a warning.
 * It should be used within methods of objects, where mapLogWarningMacro cannot
 * be used (e.g. not derivered from itk::LightObject).
 * @sa mapLogWarningMacro
 * Example usage looks like:
 * mapLogWarningObjMacro(<< "this is debug info" << this->SomeVariable);
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogWarningObjMacro(x)
#else
#define mapLogWarningObjMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "In " __FILE__ ", line " << __LINE__ << ", sig "\
		       << MAP_FUNCTION_SIGNATURE << "\n" << " (& " << this << "): " x  \
		       << "\n"; \
		::map::core::Logbook::warning(mapMsg.str());\
	}
#endif

/*! @def mapLogErrorMacro
 * This macro is used to print an error.
 * It should be used within methods of objects, that are derivered from
 * itk::LightObject or have the same interface (GetNameOfClass() and GetDebug()).
 * Use mapLogErrorObjMacro() for other methods of objects that do not meet the requirement.
 * @sa mapLogErrorObjMacro
 * Example usage looks like:
 * mapLogErrorMacro(<< "this is an info" << this->SomeVariable);
 * @ingroup Logging
 */
#define mapLogErrorMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "In " __FILE__ ", line " << __LINE__ << "\n" \
		       << this->GetNameOfClass() << " (" << this << "): " x  \
		       << "\n"; \
		::map::core::Logbook::error(mapMsg.str());\
	}

/*! @def mapLogErrorStaticMacro
 * This macro is used to print an error.
 * It should be used within static methods and global functions.
 * Example usage looks like:
 * mapLogErrorStaticMacro(<< "this is debug info");
 * @ingroup Logging
 */
#define mapLogErrorStaticMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "Debug: In " __FILE__ ", line " << __LINE__ << "\n" \
		       x << "\n"; \
		::map::core::Logbook::error(mapMsg.str());\
	}

/*! @def mapLogErrorObjMacro
 * This macro is used to print an error.
 * It should be used within methods of objects, where mapLogErrorMacro cannot
 * be used (e.g. not derivered from itk::LightObject).
 * @sa mapLogErrorMacro
 * Example usage looks like:
 * mapLogErrorObjMacro(<< "this is debug info" << this->SomeVariable);
 * @ingroup Logging
 */
#define mapLogErrorObjMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "In " __FILE__ ", line " << __LINE__ << ", sig "\
		       << MAP_FUNCTION_SIGNATURE << "\n" << " (& " << this << "): " x  \
		       << "\n"; \
		::map::core::Logbook::error(mapMsg.str());\
	}


/*! @def mapLogObjectStateMacro
 * This macro is used to print the state of "this" (current object scope)
 * as information in the logbook. Macro assumes that "this" is streamable
 * (e.g. derivered from itk::LightObject).
 * @sa mapLogCommentedObjectStateMacro
 * Example usage looks like:
 * mapLogErrorObjMacro();
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogObjectStateMacro()
#else
#define mapLogObjectStateMacro() \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "Object state in " __FILE__ ", line " << __LINE__ << ", sig "\
		       << MAP_FUNCTION_SIGNATURE << "\n\n" << &this << "\n";  \
		::map::core::Logbook::info(mapMsg.str());\
	}
#endif

/*! @def mapLogCommentedObjectStateMacro
 * This macro is used to print the state of "this" (current object scope)
 * along with a comment as information in the logbook. Macro assumes that
 * "this" is streamable (e.g. derivered from itk::LightObject).
 * @sa mapLogObjectStateMacro
 * Example usage looks like:
 * mapLogErrorObjMacro(<< "comment on the state");
 * @ingroup Logging
 */
#if defined(MAP_LEAN_AND_MEAN)
#define mapLogCommentedObjectStateMacro(x)
#else
#define mapLogCommentedObjectStateMacro(x) \
	{ ::map::core::OStringStream mapMsg; \
		mapMsg << "Object state in " __FILE__ ", line " << __LINE__ << ", sig "\
		       << MAP_FUNCTION_SIGNATURE << "\n\n" << &this << "\n\n"  \
		       << "Comment: " x; \
		::map::core::Logbook::info(mapMsg.str());\
	}
#endif

#endif
