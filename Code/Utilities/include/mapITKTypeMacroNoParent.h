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
// @version $Revision: 1088 $ (last changed revision)
// @date    $Date: 2015-09-09 10:28:23 +0200 (Mi, 09 Sep 2015) $ (last change date)
// @author  $Author: debusc $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/ITK/include/mapArbitrarySVNLOptimizerPolicy.h $
*/




#ifndef __ITK_TYPE_MACRO_NO_PARENT_H
#define __ITK_TYPE_MACRO_NO_PARENT_H

#include "itkConfigure.h"

/** This is a helper workaround to keep MatchPoint backwards compatible to ITK <4.7.
* In order to do so a macro is defined (introduced in ITK 4.7) when MatchPoint is
* used with earlier itk versions. */

#if ITK_VERSION_MAJOR <4
#define MAP_MISSING_ITK_TYPE_MACRO_NO_PARENT
#elif ITK_VERSION_MAJOR == 4 && ITK_VERSION_MINOR < 7
#define MAP_MISSING_ITK_TYPE_MACRO_NO_PARENT
#endif

#ifdef MAP_MISSING_ITK_TYPE_MACRO_NO_PARENT
#define itkTypeMacroNoParent(thisClass)      \
  virtual const char *GetNameOfClass() const \
  {                                          \
    return #thisClass;                       \
  }
#endif

#endif