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


#ifndef __MAP_MACROS_H
#define __MAP_MACROS_H

#include "mapConfigure.h"
#include "mapWin32Header.h"



/*! @def MAP_FUNCTION_SIGNATURE
 * Returns the signature of function in wich scope this macro is used as a character literal.
 */
//Definition of the function name macro depends on different compilers
//checks which one is present and maps it to MAP_FUNCTION_SIGNATURE
#ifdef __FUNCSIG__
#define MAP_FUNCTION_SIGNATURE __FUNCSIG__
#else
#ifdef __PRETTY_FUNCTION__
#define MAP_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#else
#ifdef __FUNC__
#define MAP_FUNCTION_SIGNATURE __FUNC__
#else
#define MAP_FUNCTION_SIGNATURE "unkown"
#endif
#endif
#endif


#endif
