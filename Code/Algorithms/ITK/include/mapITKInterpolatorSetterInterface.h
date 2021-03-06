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




#ifndef __ITK_INTERPOLATOR_SETTER_INTERFACE_H
#define __ITK_INTERPOLATOR_SETTER_INTERFACE_H

#include "itkInterpolateImageFunction.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ITKInterpolatorSetterInterface
			* Interface inherited by every algorithm that is able to set and change (by none const getter) an interpolator
			@ingroup AlgorithmFacets
			*/

			template<class TInputImage, class TCoordRep>
			class ITKInterpolatorSetterInterface
			{
			public:
				typedef ITKInterpolatorSetterInterface<TInputImage, TCoordRep> Self;

				typedef ::itk::InterpolateImageFunction<TInputImage, TCoordRep> InterpolatorType;
				using CoordRepType = TCoordRep;

				/*! sets the interpolator
				@eguarantee strong
				@param pInterpolator the interpolator
				*/
				virtual void setInterpolator(InterpolatorType* pInterpolator) = 0;

			protected:
				ITKInterpolatorSetterInterface() {};
				virtual ~ITKInterpolatorSetterInterface() {};

			private:
				//No copy constructor allowed
				ITKInterpolatorSetterInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};
		}  // namespace facet
	}  // namespace algorithm
}  // namespace map

#endif
