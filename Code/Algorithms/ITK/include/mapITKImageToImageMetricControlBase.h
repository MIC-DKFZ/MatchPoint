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




#ifndef __ITK_IMAGE_TO_IMAGE_METRIC_CONTROL_BASE_H
#define __ITK_IMAGE_TO_IMAGE_METRIC_CONTROL_BASE_H

#include "mapITKImageToImageMetricControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKImageToImageMetricControlBase
			This class serves as base class for all
			template specialization of itk::ImageToImageMetrics.
			It realizes some basic metric handling, to reduce the code in the control classes
			@remark ITKImageToImageMetricControlBase instantiates a concrete metric when constructed.
			You can set a new one, but ITKImageToImageMetricControlBase has always an optimizer under control.
			@template TConcreteMetric type of the concrete metric controlled by the class
			@ingroup ITK
			@ingroup MetricControl
			*/
			template<class TConcreteMetric>
			class ITKImageToImageMetricControlBase : public
				ITKImageToImageMetricControlInterface<typename TConcreteMetric::MovingImageType, typename TConcreteMetric::FixedImageType>
			{
			public:
				using Self = ITKImageToImageMetricControlBase<TConcreteMetric>;
				typedef ITKImageToImageMetricControlInterface<typename TConcreteMetric::MovingImageType, typename TConcreteMetric::FixedImageType>
				Superclass;
				using MovingImageType = typename TConcreteMetric::MovingImageType;
				using TargetImageType = typename TConcreteMetric::FixedImageType;

				using Pointer = ::itk::SmartPointer<Self>;
				using ConstPointer = ::itk::SmartPointer<const Self>;

				itkTypeMacro(ITKImageToImageMetricControlBase, ITKImageToImageMetricControlInterface);

				using ConcreteMetricType = TConcreteMetric;
				using ConcreteMetricPointer = typename ConcreteMetricType::Pointer;
				using MetricBaseType = typename Superclass::MetricBaseType;
				using SVMetricBaseType = typename Superclass::SVMetricBaseType;
				using ImageToImageMetricBaseType = typename Superclass::ImageToImageMetricBaseType;

				/*! setter for the optimizer
				@eguarantee no fail
				@param pMetric the ConcreteMetricType object that has to be set. Must not be NULL (otherwise an exception will be thrown).
				*/
				virtual void setMetric(ConcreteMetricType* pMetric);

				virtual MetricBaseType* getMetric();
				virtual const MetricBaseType* getMetric() const;

				virtual SVMetricBaseType* getSVMetric();
				virtual const SVMetricBaseType* getSVMetric() const;

				virtual ImageToImageMetricBaseType* getImageToImageMetric();
				virtual const ImageToImageMetricBaseType* getImageToImageMetric() const;

				virtual ConcreteMetricType* getConcreteMetric();
				virtual const ConcreteMetricType* getConcreteMetric() const;

				/*! The modification time (MT) of an metric controler is the the maximum of his MT
				 * and the MT of the controlled metric.  */
				virtual ::itk::ModifiedTimeType GetMTime() const;

			protected:
				virtual ~ITKImageToImageMetricControlBase();
				ITKImageToImageMetricControlBase();

				ConcreteMetricPointer _spMetric;

			private:
				//No copy constructor allowed
				ITKImageToImageMetricControlBase(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};
		}  // namespace itk
	}  // namespace algorithm
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKImageToImageMetricControlBase.tpp"
#endif

#endif
