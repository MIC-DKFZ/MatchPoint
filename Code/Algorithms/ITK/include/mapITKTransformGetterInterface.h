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




#ifndef __ITK_TRANSFORM_GETTER_INTERFACE_H
#define __ITK_TRANSFORM_GETTER_INTERFACE_H

#include "mapTransformModelBase.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ITKTransformGetterInterface
			 * Interface inherited by every algorithm that is able to get and change (by none const getter) an transform model
			 @ingroup AlgorithmFacets
			 */
			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			class ITKTransformGetterInterface
			{
			public:
				typedef ITKTransformGetterInterface<TScalar, VInputDimensions, VOutputDimensions> Self;

				typedef core::TransformModelBase<TScalar, VInputDimensions, VOutputDimensions> TransformType;

				/*! @brief gets the transform
				  @eguarantee no fail
				  @return pointer to a TransformBaseType object
				 */
				virtual TransformType* getTransformModel() = 0;

				/*! @brief gets the transform
				  @eguarantee no fail
				  @return pointer to a TransformBaseType object
				 */
				virtual const TransformType* getTransformModel() const = 0;

			protected:
				ITKTransformGetterInterface() {};
				virtual ~ITKTransformGetterInterface() {};

			private:
				//No copy constructor allowed
				ITKTransformGetterInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}

#endif
