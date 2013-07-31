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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapArbitraryTransformPolicy.tpp $
*/


#ifndef __ARBITRARY_TRANSFORM_POLICY_TPP
#define __ARBITRARY_TRANSFORM_POLICY_TPP

#include "mapAlgorithmEvents.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			unsigned long
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			GetMTime() const
			{
				unsigned long mt = _mTime.getMTime();
				return mt;
			};

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			setTransformModel(TransformType *pTransform)
			{
				if (pTransform != _spTransformModel.GetPointer())
				{
					//there is really the need to change
					if (this->_spOnChange.IsNotNull())
					{
						events::UnregisterAlgorithmComponentEvent unRegEvent(_spTransformModel.GetPointer(), "Unregister current transform model");
						this->_spOnChange->Execute((::itk::Object *)NULL, unRegEvent);
					}

					_spTransformModel  = pTransform;
					_mTime.setWatchedObject(pTransform);

					if (this->_spOnChange.IsNotNull())
					{
						events::RegisterAlgorithmComponentEvent regEvent(_spTransformModel.GetPointer(), "Register new transform model");
						this->_spOnChange->Execute((::itk::Object *)NULL, regEvent);
					}
				}
			};

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			ArbitraryTransformPolicy()
			{
			};

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			~ArbitraryTransformPolicy()
			{
			};

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::TransformType *
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			getTransformInternal()
			{
				return _spTransformModel;
			};

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			const typename ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::TransformType *
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			getTransformInternal() const
			{
				return _spTransformModel;
			};

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::TransformType *
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			getTransformModel()
			{
				return _spTransformModel;
			};

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			const typename ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::TransformType *
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			getTransformModel() const
			{
				return _spTransformModel;
			};

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			prepareTransform()
			{
				//default implementation does nothing;
			};

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::
			prepareTransformAfterAssembly()
			{
				//default implementation does nothing;
			};


		}
	} // end namespace algorithm
} // end namespace map

#endif
