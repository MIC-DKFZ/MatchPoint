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

#ifndef __MAP_POINT_VECTOR_COMBINATION_POLICY_H
#define __MAP_POINT_VECTOR_COMBINATION_POLICY_H

#include "mapFieldRepresentationDescriptor.h"
#include "mapRegistrationTopology.h"

#include "itkObject.h"

namespace map
{
	namespace core
	{
		/*! @class PointVectorCombinationPolicy
		* @brief Class defines the rule for combining points and vectors of any dimensionality.
		*
		* This helper class is used by MatchPoint for mapping purposes of arbitrary dimensionality.
		* It handles the mapping of points by vectors of arbitrary dimensionality. Missing dimensions
		* will be substituted with 0. Surplus dimensions will be skipped. Vectors and points will be
		* aligned at the first dimension.
		*
		* @ingroup Registration
		* @tparam VInDimensions Dimension count of the first operand type.
		* @tparam VOutDimensions Dimension count of the output type.
		*/
		template <unsigned int VInDimensions, unsigned int VOutDimensions>
		class PointVectorCombinationPolicy
		{
		public:
			using PointType = typename continuous::Elements<VInDimensions>::PointType;
			using VectorType = typename continuous::Elements<VInDimensions>::VectorType;
			using OutputPointType = typename continuous::Elements<VOutDimensions>::PointType;
			using OutputVectorType = typename continuous::Elements<VOutDimensions>::VectorType;

			static inline void mapPoint(const PointType& inPoint, const OutputVectorType& mappingVector,
										OutputPointType& outPoint)
			{
				doAdd(inPoint, mappingVector, outPoint);
			};

			/*!mapping as an direct conversion (mapping vector is zero)*/
			static inline void mapPoint(const PointType& inPoint, OutputPointType& outPoint)
			{
				OutputVectorType mappingVector;
				mappingVector.Fill(itk::NumericTraits<typename OutputVectorType::ValueType>::Zero);

				doAdd(inPoint, mappingVector, outPoint);
			};

			static inline void combineVectors(const VectorType& vector1, const OutputVectorType& vector2,
											  OutputVectorType& outVector)
			{
				doAdd(vector1, vector2, outVector);
			};

			static inline void computeVector(const PointType& fromPoint, const OutputPointType& toPoint,
											 OutputVectorType& outVector)
			{
				doSubtract(toPoint, fromPoint, outVector);
			};

			static inline bool isDefaultImplementation()
			{
				return true;
			};

		private:

			template < typename T1stOp, typename T2ndOp, typename TResultType>
			static inline void doAdd(const T1stOp& op1, const T2ndOp& op2, TResultType& result)
			{
				for (unsigned int i = 0; i < TResultType::Dimension; ++i)
				{
					typename T1stOp::ValueType v1 = (i < T1stOp::Dimension ? op1[i] :
													 itk::NumericTraits<typename T1stOp::ValueType>::Zero);
					typename T2ndOp::ValueType v2 = (i < T2ndOp::Dimension ? op2[i] :
													 itk::NumericTraits<typename T2ndOp::ValueType>::Zero);
					result[i] = v1 + v2;
				}
			};

			template < typename T1stOp, typename T2ndOp, typename TResultType>
			static inline void doSubtract(const T1stOp& op1, const T2ndOp& op2, TResultType& result)
			{
				for (unsigned int i = 0; i < TResultType::Dimension; ++i)
				{
					typename T1stOp::ValueType v1 = (i < T1stOp::Dimension ? op1[i] :
													 itk::NumericTraits<typename T1stOp::ValueType>::Zero);
					typename T2ndOp::ValueType v2 = (i < T2ndOp::Dimension ? op2[i] :
													 itk::NumericTraits<typename T2ndOp::ValueType>::Zero);
					result[i] = v1 - v2;
				}
			};

			typedef PointVectorCombinationPolicy<VInDimensions, VOutDimensions> Self;
			PointVectorCombinationPolicy(); //purposely not implemented
			virtual ~PointVectorCombinationPolicy();  //purposely not implemented
			PointVectorCombinationPolicy(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

		/*! @class PointVectorCombinationPolicy<VDimensions, VDimensions, VDimensions>
		* @brief Template specialication for the case that input point and mapping vector are of the same dimensionality.
		*
		* @ingroup Registration
		* @tparam VDimensions Dimensionality of the operands.
		*/
		template <unsigned int VDimensions>
		class PointVectorCombinationPolicy<VDimensions, VDimensions>
		{
		public:
			using PointType = typename continuous::Elements<VDimensions>::PointType;
			using VectorType = typename continuous::Elements<VDimensions>::VectorType;
			using OutputPointType = typename continuous::Elements<VDimensions>::PointType;
			using OutputVectorType = typename continuous::Elements<VDimensions>::VectorType;

			static inline void mapPoint(const PointType& inPoint, const OutputVectorType& mappingVector,
										OutputPointType& outPoint)
			{
				outPoint = inPoint + mappingVector;
			};

			/*!mapping as an direct conversion (mapping vector is zero)*/
			static inline void mapPoint(const PointType& inPoint, OutputPointType& outPoint)
			{
				outPoint = inPoint;
			};

			static inline void combineVectors(const VectorType& vector1, const OutputVectorType& vector2,
											  OutputVectorType& outVector)
			{
				outVector = vector1 + vector2;
			};

			static inline void computeVector(const PointType& fromPoint, const OutputPointType& toPoint,
											 OutputVectorType& outVector)
			{
				outVector = toPoint - fromPoint;
			};

			static inline bool isDefaultImplementation()
			{
				return false;
			};

		private:
			typedef PointVectorCombinationPolicy<VDimensions, VDimensions> Self;
			PointVectorCombinationPolicy(); //purposely not implemented
			virtual ~PointVectorCombinationPolicy();  //purposely not implemented
			PointVectorCombinationPolicy(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented

		};
	} // end namespace core
} // end namespace map

#endif
