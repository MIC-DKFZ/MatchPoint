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


#ifndef __MAP_FSL_HELPER_H
#define __MAP_FSL_HELPER_H

#include "vnl/vnl_matrix_fixed.h"
#include "vnl/vnl_diag_matrix.h"


#include "itkMatrix.h"

#include "mapString.h"
#include "mapExceptionObjectMacros.h"
#include "mapFieldRepresentationDescriptor.h"
#include "mapMAPAlgorithmsFSLExports.h"

namespace map
{
	namespace algorithm
	{
		namespace fsl
		{

			template <unsigned int VDimensions>
			::itk::Matrix < double, VDimensions + 1, VDimensions + 1 >
			convertVoxelSpaceToRASPhysicalSpaceMatrix(const core::FieldRepresentationDescriptor<VDimensions>*
					descriptor)
			{
				// Generate intermediate terms
				vnl_matrix<double> directions, rasMatrix;
				vnl_diag_matrix<double> scales, lps2rasMatrix;
				vnl_vector<double> origin, rasOffset;

				// Compute the matrix
				directions = descriptor->getDirection().GetVnlMatrix();
				scales.set(descriptor->getSpacing().GetVnlVector());
				lps2rasMatrix.set(vnl_vector<double>(VDimensions, 1.0));
				lps2rasMatrix[0] = -1;
				lps2rasMatrix[1] = -1;
				rasMatrix = lps2rasMatrix * directions * scales;

				// Compute the vector
				origin = descriptor->getOrigin().GetVnlVector();
				rasOffset = lps2rasMatrix * origin;

				// Create the larger matrix
				::itk::Matrix < double, VDimensions + 1, VDimensions + 1 > mat;
				vnl_vector<double> vcol(VDimensions, 1.0);
				vcol.update(rasOffset);
				mat.SetIdentity();
				mat.GetVnlMatrix().update(rasMatrix);
				mat.GetVnlMatrix().set_column(VDimensions, vcol);

				return mat;
			};

			template <unsigned int VDimensions>
			vnl_matrix_fixed < double, VDimensions + 1, VDimensions + 1 >
			readFSLMatrixFromFile(const map::core::String& fileName)
			{
				std::ifstream matFile;
				matFile.open(fileName.c_str());

				if (matFile.fail())
				{
					mapDefaultExceptionStaticMacro( << "Error cannot find or access determined matrix file. Path: " <<
													fileName);
				}

				typedef vnl_matrix_fixed < double, VDimensions + 1, VDimensions + 1 > MatrixType;

				typedef std::vector<double> ValueVectorType;

				ValueVectorType tempVals;
				double val = 0;

				matFile >> val;

				while (!matFile.fail())
				{
					tempVals.push_back(val);
					matFile >> val;
				}

				matFile.close();

				if (tempVals.size() != (VDimensions + 1) * (VDimensions + 1))
				{
					mapDefaultExceptionStaticMacro( <<
													"Error. Cannot determine final registration. Flirt matrix file has wrong value count. Expected value count: "
													<< (VDimensions + 1) * (VDimensions + 1) << "; recieved data size: " << tempVals.size());
				}

				//populate the matrix. Flirt stores all as (NOutputDimension+1 x NInputDimension+1)-matrix
				MatrixType result;

				for (unsigned int i = 0; i < VDimensions + 1; ++i)
				{
					for (unsigned int j = 0; j < VDimensions + 1; ++j)
					{
						{
							result.put(i, j, tempVals[i * (VDimensions + 1) + j]);
						}
					}
				}

				return result;
			}

			template <unsigned int VDimensions>
			::itk::Array<double>
			convertMatrixToAffineTransformParams(const vnl_matrix_fixed < double, VDimensions + 1,
												 VDimensions + 1 > & matrix)
			{

				::itk::Array<double> params(VDimensions * (VDimensions + 1));


				//populate params with correct values. The first (NOutputDimension x NInputDimension) parameters define the
				//matrix and the last NOutputDimension parameters. Flirt stores all as (NOutputDimension+1 x NInputDimension+1)-matrix
				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					for (unsigned int j = 0; j < VDimensions; ++j)
					{
						params[VDimensions * i + j] = -matrix(i, j);
					}
				}

				for (int i = 0; i < VDimensions; ++i)
				{
					params[(VDimensions * VDimensions) + i] = matrix(i, VDimensions);
				}

				return params;
			}


			template <unsigned int VDimensions>
			class MatrixConverter
			{
			public:
				typedef vnl_matrix_fixed < double, VDimensions + 1, VDimensions + 1 > MatrixType;
				typedef core::FieldRepresentationDescriptor<VDimensions> DescriptorType;

				//purposely not implemented. Currently only 2D and 3D is supported
				static MatrixType convertFSLToRAS(const MatrixType& fslMatrix, const DescriptorType* targetDesc,
												  const DescriptorType* movingDesc);
				static MatrixType convertRASToITKTrans(const MatrixType& rsaMatrix);

			private:
				~MatrixConverter();//purposely not implemented
				MatrixConverter();//purposely not implemented

				MatrixConverter(const MatrixConverter<VDimensions>&); //purposely not implemented
				void operator=(const MatrixConverter<VDimensions>&);  //purposely not implemented
			};

			template <>
			class MAPAlgorithmsFSL_EXPORT MatrixConverter<2>
			{
			public:
				typedef vnl_matrix_fixed<double, 3, 3> MatrixType;
				typedef core::FieldRepresentationDescriptor<2> DescriptorType;

				static MatrixType convertFSLToRAS(const MatrixType& fslMatrix, const DescriptorType* targetDesc,
												  const DescriptorType* movingDesc);
				static MatrixType convertRASToITKTrans(const MatrixType& rsaMatrix);

			private:
				~MatrixConverter();//purposely not implemented
				MatrixConverter();//purposely not implemented

				MatrixConverter(const MatrixConverter<2>&); //purposely not implemented
				void operator=(const MatrixConverter<2>&);  //purposely not implemented
			};

			template <>
			class MAPAlgorithmsFSL_EXPORT MatrixConverter<3>
			{
			public:
				typedef vnl_matrix_fixed<double, 4, 4> MatrixType;
				typedef core::FieldRepresentationDescriptor<3> DescriptorType;

				static MatrixType convertFSLToRAS(const MatrixType& fslMatrix, const DescriptorType* targetDesc,
												  const DescriptorType* movingDesc);
				static MatrixType convertRASToITKTrans(const MatrixType& rsaMatrix);

			private:
				~MatrixConverter();//purposely not implemented
				MatrixConverter();//purposely not implemented

				MatrixConverter(const MatrixConverter<2>&); //purposely not implemented
				void operator=(const MatrixConverter<2>&);  //purposely not implemented
			};


		}
	}
}

#endif
