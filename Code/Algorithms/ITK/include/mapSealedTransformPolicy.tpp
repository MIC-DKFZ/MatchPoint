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


#ifndef __SEALED_TRANSFORM_POLICY_TPP
#define __SEALED_TRANSFORM_POLICY_TPP

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TConcreteITKTransform>
			typename SealedTransformPolicy<TConcreteITKTransform>::ConcreteTransformType*
			SealedTransformPolicy<TConcreteITKTransform>::
			getConcreteTransformModel()
			{
				return _spTransformModel;
			}

			template<class TConcreteITKTransform>
			const typename SealedTransformPolicy<TConcreteITKTransform>::ConcreteTransformType*
			SealedTransformPolicy<TConcreteITKTransform>::
			getConcreteTransformModel() const
			{
				return _spTransformModel;
			}

			template<class TConcreteITKTransform>
			SealedTransformPolicy<TConcreteITKTransform>::
			SealedTransformPolicy()
			{
				_spTransformModel = ConcreteTransformType::New();
			};

			template<class TConcreteITKTransform>
			SealedTransformPolicy<TConcreteITKTransform>::
			~SealedTransformPolicy()
			{
			};

			template<class TConcreteITKTransform>
			typename SealedTransformPolicy<TConcreteITKTransform>::TransformType*
			SealedTransformPolicy<TConcreteITKTransform>::
			getTransformInternal()
			{
				return _spTransformModel;
			}

			template<class TConcreteITKTransform>
			const typename SealedTransformPolicy<TConcreteITKTransform>::TransformType*
			SealedTransformPolicy<TConcreteITKTransform>::
			getTransformInternal() const
			{
				return _spTransformModel;
			}

			template<class TConcreteITKTransform>
			void
			SealedTransformPolicy<TConcreteITKTransform>::
			prepareTransform()
			{
				//default implementation does nothing;
			};

			template<class TConcreteITKTransform>
			void
			SealedTransformPolicy<TConcreteITKTransform>::
			prepareTransformAfterAssembly()
			{
				//default implementation does nothing;
			};

			template<class TConcreteITKTransform>
			unsigned long
			SealedTransformPolicy<TConcreteITKTransform>::
			GetMTime() const
			{
				unsigned long mt = _mTime.GetMTime();

				if (mt < _spTransformModel->GetMTime())
				{
					mt = _spTransformModel->GetMTime();
				}

				return mt;
			};

			template<class TConcreteITKTransform>
			void
			SealedTransformPolicy<TConcreteITKTransform>::
			indicateModification() const
			{
				_mTime.Modified();
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
