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
// @version $Revision: 1316 $ (last changed revision)
// @date    $Date: 2016-04-13 14:50:09 +0200 (Mi, 13 Apr 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Core/include/mapGenericFieldGeneratingCombinationFunctor.tpp $
*/


#ifndef __MAP_GENERIC_KERNEL_COMBINATION_FIELD_SOURCE_H
#define __MAP_GENERIC_KERNEL_COMBINATION_FIELD_SOURCE_H

#include "itkGenerateImageSource.h"

#include "mapRegistrationKernelBase.h"
#include "mapDefaultRegistrationTopologyPolicy.h"

namespace map
{
    namespace core
    {
        /** \class GenericKernelCombinationFieldSource
         * \brief Generate an Vector field by combining the givin to source kernels.
         *
         * \ingroup DataSources
         * \ingroup ITKImageSources
         */
        template< unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions, typename TScalarType >
        class GenericKernelCombinationFieldSource
            : public ::itk::GenerateImageSource < typename ::map::core::RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectFieldType >
        {
        public:
            typedef typename ::map::core::RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectFieldType OutputImageType;

            typedef GenericKernelCombinationFieldSource   Self;
            typedef ::itk::GenerateImageSource< OutputImageType > Superclass;
            typedef ::itk::SmartPointer< Self >                Pointer;
            typedef ::itk::SmartPointer< const Self>           ConstPointer;

            /** Output image typedefs */
            typedef typename OutputImageType::PixelType     PixelType;
            typedef typename OutputImageType::RegionType    RegionType;
            typedef typename OutputImageType::SpacingType   SpacingType;
            typedef typename OutputImageType::PointType     PointType;
            typedef typename OutputImageType::DirectionType DirectionType;

            typedef typename RegionType::SizeType SizeType;

            typedef RegistrationKernelBase<VInputDimensions, VInterimDimensions> SourceKernel1BaseType;
            typedef RegistrationKernelBase<VInterimDimensions, VOutputDimensions> SourceKernel2BaseType;

            typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::TargetPointType
                NullPointType;

            /** Run-time type information (and related methods). */
            itkTypeMacro(GenericKernelCombinationFieldSource, GenerateImageSource);

            /** Method for creation through the object factory. */
            itkNewMacro(Self);

            itkSetConstObjectMacro(SourceKernel1, SourceKernel1BaseType);
            itkSetConstObjectMacro(SourceKernel2, SourceKernel2BaseType);

            itkGetConstObjectMacro(SourceKernel1, SourceKernel1BaseType);
            itkGetConstObjectMacro(SourceKernel2, SourceKernel2BaseType);

            itkSetMacro(UseNullPoint, bool);
            itkGetMacro(UseNullPoint, bool);

            itkSetMacro(NullPoint, NullPointType);
            itkGetMacro(NullPoint, NullPointType);

        protected:
            GenericKernelCombinationFieldSource() : m_UseNullPoint(false)
            {
              m_NullPoint.Fill(itk::NumericTraits<map::core::continuous::ScalarType>::NonpositiveMin());
            };
            // virtual ~GenericKernelCombinationFieldSource() default implementation ok

            virtual void ThreadedGenerateData(const RegionType &outputRegionForThread, ::itk::ThreadIdType threadId);
            virtual void GenerateOutputInformation();

            typename SourceKernel1BaseType::ConstPointer m_SourceKernel1;
            typename SourceKernel2BaseType::ConstPointer m_SourceKernel2;

            NullPointType m_NullPoint;
            bool m_UseNullPoint;

        private:
            GenericKernelCombinationFieldSource(const GenericKernelCombinationFieldSource &); //purposely not implemented
            void operator=(const GenericKernelCombinationFieldSource &);  //purposely not implemented
        };

    }
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapGenericKernelCombinationFieldSource.tpp"
#endif


#endif
