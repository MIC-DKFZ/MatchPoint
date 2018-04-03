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


#include "mapAlgorithmEvents.h"

#ifndef __ARBITRARY_IMAGE_PYRAMIDE_POLICY_TPP
#define __ARBITRARY_IMAGE_PYRAMIDE_POLICY_TPP

namespace map
{
	namespace algorithm
	{

		template<class TMovingImage, class TTargetImage>
		unsigned long
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>::
		getTargetPyramideMTime() const
		{
			unsigned long mt = _targetPyramideMTime.getMTime();
			return mt;
		};

		template<class TMovingImage, class TTargetImage>
		unsigned long
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>::
		getMovingPyramideMTime() const
		{
			unsigned long mt = _movingPyramideMTime.getMTime();
			return mt;
		};

		template<class TMovingImage, class TTargetImage>
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		ArbitraryImagePyramidesPolicy()
		{
		}

		template<class TMovingImage, class TTargetImage>
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		~ArbitraryImagePyramidesPolicy()
		{
		}

		template<class TMovingImage, class TTargetImage>
		typename ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::MovingImagePyramideBaseType*
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		getMovingPyramideInternal()
		{
			return _spMovingPyramide;
		}

		template<class TMovingImage, class TTargetImage>
		const typename ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>
		::MovingImagePyramideBaseType*
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		getMovingPyramideInternal() const
		{
			return _spMovingPyramide;
		}

		template<class TMovingImage, class TTargetImage>
		typename ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::TargetImagePyramideBaseType*
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		getTargetPyramideInternal()
		{
			return _spTargetPyramide;
		}

		template<class TMovingImage, class TTargetImage>
		const typename ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>
		::TargetImagePyramideBaseType*
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		getTargetPyramideInternal() const
		{
			return _spTargetPyramide;
		}

		template<class TMovingImage, class TTargetImage>
		typename ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::MovingImagePyramideBaseType*
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		getMovingImagePyramide()
		{
			return _spMovingPyramide;
		}

		template<class TMovingImage, class TTargetImage>
		const typename ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>
		::MovingImagePyramideBaseType*
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		getMovingImagePyramide() const
		{
			return _spMovingPyramide;
		}

		template<class TMovingImage, class TTargetImage>
		typename ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::TargetImagePyramideBaseType*
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		getTargetImagePyramide()
		{
			return _spTargetPyramide;
		}

		template<class TMovingImage, class TTargetImage>
		const typename ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>
		::TargetImagePyramideBaseType*
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		getTargetImagePyramide() const
		{
			return _spTargetPyramide;
		}

		template<class TMovingImage, class TTargetImage>
		void
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		setMovingImagePyramide(MovingImagePyramideBaseType* pMovingPyramide)
		{
			if (pMovingPyramide != _spMovingPyramide.GetPointer())
			{
				//there is really the need to change
				if (this->_spOnChangeMoving.IsNotNull())
				{
					::map::events::UnregisterAlgorithmComponentEvent unRegEvent(_spMovingPyramide.GetPointer(),
							"Unregister current moving image pyramide");
					this->_spOnChangeMoving->Execute((::itk::Object*)NULL, unRegEvent);
				}

				_movingPyramideMTime.setWatchedObject(pMovingPyramide);
				_spMovingPyramide  = pMovingPyramide;

				if (this->_spOnChangeMoving.IsNotNull())
				{
					::map::events::RegisterAlgorithmComponentEvent regEvent(_spMovingPyramide.GetPointer(),
							"Register new moving image pyramide");
					this->_spOnChangeMoving->Execute((::itk::Object*)NULL, regEvent);
				}
			}
		}

		template<class TMovingImage, class TTargetImage>
		void
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		setTargetImagePyramide(TargetImagePyramideBaseType* pTargetPyramide)
		{
			if (pTargetPyramide != _spTargetPyramide.GetPointer())
			{
				//there is really the need to change
				if (this->_spOnChangeTarget.IsNotNull())
				{
					::map::events::UnregisterAlgorithmComponentEvent unRegEvent(_spTargetPyramide.GetPointer(),
							"Unregister current target image pyramide");
					this->_spOnChangeTarget->Execute((::itk::Object*)NULL, unRegEvent);
				}

				_targetPyramideMTime.setWatchedObject(pTargetPyramide);
				_spTargetPyramide  = pTargetPyramide;

				if (this->_spOnChangeTarget.IsNotNull())
				{
					::map::events::RegisterAlgorithmComponentEvent regEvent(_spTargetPyramide.GetPointer(),
							"Register new target image pyramide");
					this->_spOnChangeTarget->Execute((::itk::Object*)NULL, regEvent);
				}
			}
		}

		template<class TMovingImage, class TTargetImage>
		void
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		preparePyramides()
		{
			//default implementation does nothing;
		}

		template<class TMovingImage, class TTargetImage>
		void
		ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> ::
		preparePyramidesAfterAssembly()
		{
			//default implementation does nothing;
		}

	}
}

#endif
