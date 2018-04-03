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




#ifndef __AFFINE_MATRIX_DECOMPOSER_TPP
#define __AFFINE_MATRIX_DECOMPOSER_TPP

#include "mapAffineMatrixDecomposer.h"
#include "mapRegistrationKernel.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		AffineMatrixDecomposer<VInputDimensions, VOutputDimensions>::
		decomposeKernel(const KernelType* pKernel, MatrixType& matrix, OffsetType& offset)
		{
			bool result = false;

			if (!pKernel)
			{
				mapDefaultExceptionStaticMacro( <<
												"Error decomposing affine matrix of kernel. Passed kernel pointer is NULL.");
			};

      const RegistrationKernel<VInputDimensions, VOutputDimensions>* castedKernel = dynamic_cast<const RegistrationKernel<VInputDimensions, VOutputDimensions>*>(pKernel);

      if (castedKernel)
      {
          result = castedKernel->getAffineMatrixDecomposition(matrix, offset);
      }
      return result;
		};

	}
}

#endif
