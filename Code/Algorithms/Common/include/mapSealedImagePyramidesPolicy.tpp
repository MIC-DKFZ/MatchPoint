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


#ifndef __SEALED_IMAGE_PYRAMIDES_POLICY_TPP
#define __SEALED_IMAGE_PYRAMIDES_POLICY_TPP

namespace map
{
	namespace algorithm
	{

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		typename SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::ConcreteMovingImagePyramideType*

		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getConcreteMovingPyramide()
		{
			return _spMovingPyramide;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		const typename
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::ConcreteMovingImagePyramideType*

		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getConcreteMovingPyramide() const
		{
			return _spMovingPyramide;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		typename SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::ConcreteTargetImagePyramideType*

		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getConcreteTargetPyramide()
		{
			return _spTargetPyramide;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		const typename
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::ConcreteTargetImagePyramideType*

		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getConcreteTargetPyramide() const
		{
			return _spTargetPyramide;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		SealedImagePyramidesPolicy()
		{
			_spTargetPyramide =  ConcreteTargetImagePyramideType::New();
			_spMovingPyramide =  ConcreteMovingImagePyramideType::New();
			InitializationPolicy::initialize(_spTargetPyramide.GetPointer());
			InitializationPolicy::initialize(_spMovingPyramide.GetPointer());
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		~SealedImagePyramidesPolicy()
		{
		};


		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		typename SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::MovingImagePyramideBaseType*

		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getMovingPyramideInternal()
		{
			return _spMovingPyramide;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		const typename
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::MovingImagePyramideBaseType*

		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getMovingPyramideInternal() const
		{
			return _spMovingPyramide;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		typename SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::TargetImagePyramideBaseType*

		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getTargetPyramideInternal()
		{
			return _spTargetPyramide;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		const typename
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::TargetImagePyramideBaseType*

		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getTargetPyramideInternal() const
		{
			return _spTargetPyramide;
		};


		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		void
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		preparePyramides()
		{
			//default implementation does nothing;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		void
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		preparePyramidesAfterAssembly()
		{
			//default implementation does nothing;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		unsigned long
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getTargetPyramideMTime() const
		{
			unsigned long mt = _targetPyramideMTime.getMTime();
			return mt;
		};

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy>
		unsigned long
		SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>::
		getMovingPyramideMTime() const
		{
			unsigned long mt = _movingPyramideMTime.getMTime();
			return mt;
		};

	} // end namespace algorithm
} // end namespace map

#endif
