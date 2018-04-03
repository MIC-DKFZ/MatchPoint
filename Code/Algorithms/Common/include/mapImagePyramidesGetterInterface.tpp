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


#ifndef __IMAGE_PYRAMIDES_GETTER_INTERFACE_TPP
#define __IMAGE_PYRAMIDES_GETTER_INTERFACE_TPP

namespace map
{
	namespace algorithm
	{

		template<class TMovingImage, class TTargetImage>
		ImagePyramidesGetterInterface<TMovingImage, TTargetImage>::
		ImagePyramidesGetterInterface()
		{};

		template<class TMovingImage, class TTargetImage>
		ImagePyramidesGetterInterface<TMovingImage, TTargetImage>::
		~ImagePyramidesGetterInterface()
		{};

	} // end namespace algorithm
} // end namespace map

#endif
