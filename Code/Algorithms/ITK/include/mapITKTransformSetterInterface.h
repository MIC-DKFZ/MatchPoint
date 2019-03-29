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




#ifndef __ITK_TRANSFORM_SETTER_INTERFACE_H
#define __ITK_TRANSFORM_SETTER_INTERFACE_H

#include "itkTransform.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ITKTransformSetterInterface
			 * Interface inherited by every algorithm that is able to set and change (by none const getter) an transform model
			 @ingroup AlgorithmFacets
			 */
			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			class ITKTransformSetterInterface
			{
			public:
				typedef ITKTransformSetterInterface<TScalar, VInputDimensions, VOutputDimensions> Self;

				typedef ::itk::Transform<TScalar, VInputDimensions, VOutputDimensions> TransformType;

				/*! sets the transform
				  @eguarantee strong
				  @param pTransform the pTransform
				 */
				virtual void setTransformModel(TransformType* pTransform) = 0;

			protected:
				ITKTransformSetterInterface() {};
				virtual ~ITKTransformSetterInterface() {};

			private:
				//No copy constructor allowed
				ITKTransformSetterInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}  // namespace facet
	}  // namespace algorithm
}  // namespace map

#endif
