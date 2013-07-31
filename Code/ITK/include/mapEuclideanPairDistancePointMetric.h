/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkEuclideanPairDistancePointMetric.h,v $
  Language:  C++
  Date:      $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $
  Version:   $Revision: 4912 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkEuclideanPairDistancePointMetric_h
#define __itkEuclideanPairDistancePointMetric_h

#include "itkPointSetToPointSetMetric.h"
#include "itkCovariantVector.h"
#include "itkPoint.h"
#include "itkPointSet.h"
#include "itkImage.h"

namespace itk
{
	/** \class EuclideanPairDistancePointMetric
	 * \brief Computes the minimum distance between a point pairs
	 *  of a moving point-set and a fixed point-set;
	 *  assuming that points with same index are point pairs.
	 *
	 * \ingroup RegistrationMetrics
	 */
	template < class TFixedPointSet, class TMovingPointSet,
	         class TDistanceMap = ::itk::Image<unsigned short, TMovingPointSet::PointDimension> >
	class ITK_EXPORT EuclideanPairDistancePointMetric :
		public PointSetToPointSetMetric< TFixedPointSet, TMovingPointSet>
	{
	public:

		/** Standard class typedefs. */
		typedef EuclideanPairDistancePointMetric                                Self;
		typedef PointSetToPointSetMetric<TFixedPointSet, TMovingPointSet >  Superclass;

		typedef SmartPointer<Self>         Pointer;
		typedef SmartPointer<const Self>   ConstPointer;

		/** Method for creation through the object factory. */
		itkNewMacro(Self);

		/** Run-time type information (and related methods). */
		itkTypeMacro(EuclideanPairDistancePointMetric, Object);

		/** Types transferred from the base class */
		typedef typename Superclass::TransformType              TransformType;
		typedef typename Superclass::TransformPointer           TransformPointer;
		typedef typename Superclass::TransformParametersType    TransformParametersType;
		typedef typename Superclass::TransformJacobianType      TransformJacobianType;

		typedef typename Superclass::MeasureType                MeasureType;
		typedef typename Superclass::DerivativeType             DerivativeType;
		typedef typename Superclass::FixedPointSetType          FixedPointSetType;
		typedef typename Superclass::MovingPointSetType         MovingPointSetType;
		typedef typename Superclass::FixedPointSetConstPointer  FixedPointSetConstPointer;
		typedef typename Superclass::MovingPointSetConstPointer MovingPointSetConstPointer;

		typedef typename Superclass::PointIterator              PointIterator;
		typedef typename Superclass::PointDataIterator          PointDataIterator;

		typedef TDistanceMap                                    DistanceMapType;
		typedef typename DistanceMapType::ConstPointer          DistanceMapPointer;


		/** Get the number of values */
		unsigned int GetNumberOfValues() const;

		/** Get the derivatives of the match measure. */
		void GetDerivative(const TransformParametersType &parameters,
		                   DerivativeType &Derivative) const;

		/**  Get the value for single valued optimizers. */
		MeasureType GetValue(const TransformParametersType &parameters) const;

		/**  Get value and derivatives for multiple valued optimizers. */
		void GetValueAndDerivative(const TransformParametersType &parameters,
		                           MeasureType &Value, DerivativeType &Derivative) const;

		/** Set/Get the distance map */
		itkSetConstObjectMacro(DistanceMap, DistanceMapType);
		itkGetConstObjectMacro(DistanceMap, DistanceMapType);

		/** Set/Get if the distance should be squared. Default is true for computation speed */
		itkSetMacro(ComputeSquaredDistance, bool);
		itkGetConstMacro(ComputeSquaredDistance, bool);
		itkBooleanMacro(ComputeSquaredDistance);

	protected:
		EuclideanPairDistancePointMetric();
		virtual ~EuclideanPairDistancePointMetric() {};

		/** PrintSelf funtion */
		void PrintSelf(std::ostream &os, Indent indent) const;

	private:
		EuclideanPairDistancePointMetric(const Self &); //purposely not implemented
		void operator=(const Self &); //purposely not implemented

		DistanceMapPointer m_DistanceMap;
		bool               m_ComputeSquaredDistance;

	};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "mapEuclideanPairDistancePointMetric.txx"
#endif

#endif
