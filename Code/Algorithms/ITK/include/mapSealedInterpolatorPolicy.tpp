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


#ifndef __SEALED_INTERPOLATOR_POLICY_TPP
#define __SEALED_INTERPOLATOR_POLICY_TPP

namespace map
{
	namespace algorithm
	{

		namespace itk
		{

			template<class TConcreteInterpolator>
			typename SealedInterpolatorPolicy<TConcreteInterpolator>::ConcreteInterpolatorType*
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			getConcreteInterpolator()
			{
				return _spInterpolator;
			};

			template<class TConcreteInterpolator>
			const typename SealedInterpolatorPolicy<TConcreteInterpolator>::ConcreteInterpolatorType*
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			getConcreteInterpolator() const
			{
				return _spInterpolator;
			};


			template<class TConcreteInterpolator>
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			SealedInterpolatorPolicy()
			{
				_spInterpolator =  ConcreteInterpolatorType::New();
			};

			template<class TConcreteInterpolator>
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			~SealedInterpolatorPolicy()
			{
			};


			template<class TConcreteInterpolator>
			typename SealedInterpolatorPolicy<TConcreteInterpolator>::InterpolatorType*
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			getInterpolatorInternal()
			{
				return _spInterpolator;
			};

			template<class TConcreteInterpolator>
			const typename SealedInterpolatorPolicy<TConcreteInterpolator>::InterpolatorType*
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			getInterpolatorInternal() const
			{
				return _spInterpolator;
			};

			template<class TConcreteInterpolator>
			void
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			prepareInterpolator()
			{
				//default implementation does nothing;
			};

			template<class TConcreteInterpolator>
			void
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			prepareInterpolatorAfterAssembly()
			{
				//default implementation does nothing;
			};

			template<class TConcreteInterpolator>
			unsigned long
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			GetMTime() const
			{
				unsigned long mt = _mTime.GetMTime();

				if (mt < _spInterpolator->GetMTime())
				{
					mt = _spInterpolator->GetMTime();
				}

				return mt;
			};


			template<class TConcreteInterpolator>
			void
			SealedInterpolatorPolicy<TConcreteInterpolator>::
			indicateModification() const
			{
				_mTime.Modified();
			};

		}
	} // end namespace algorithm
} // end namespace map

#endif
