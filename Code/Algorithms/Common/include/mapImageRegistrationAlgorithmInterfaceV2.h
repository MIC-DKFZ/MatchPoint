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
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/Common/include/mapImageRegistrationAlgorithmInterface.h $
*/

#ifndef __IMAGE_REGISTRATION_ALGORITHM_INTERFACE_V2_H
#define __IMAGE_REGISTRATION_ALGORITHM_INTERFACE_V2_H

#include "mapImageRegistrationAlgorithmInterface.h"

/*! @namespace
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ImageRegistrationAlgorithmInterfaceV2
      @brief This is the interface for image based registration algorithms (Version 2)
      This version extents the first version by:
      1. Allow define multiple inputs for the roles (moving / target)
      2. posibility to query if the input slots are mandatory or just optional.

      The inputs are indexed (like itk filters) and the interface implies that all mandatory
      input slots of a role (moving or target) have lower indeces then optional slots of the same role. So e.g.
      given 4 mandatory moving input slots, by definition they will have the indeces 0..3. Optional
      slots will start with 4.
      An additional assumption is that ImageRegistrationAlgorithmInterface accesses the first slots
      (slot index 0). According to this assumptions the methods of ImageRegistrationAlgorithmInterface
      have a default implementation.
      @sa ImageRegistrationAlgorithmInterface
			@ingroup AlgorithmFacets
			@template TMovingImage Type of the moving image
			@template TTargetImage Type of the target image
			*/
			template<class TMovingImage, class TTargetImage>
      class ImageRegistrationAlgorithmInterfaceV2 : public ImageRegistrationAlgorithmInterface<TMovingImage, TTargetImage>

			{
			public:
        typedef ImageRegistrationAlgorithmInterfaceV2<TMovingImage, TTargetImage> Self;
        typedef ImageRegistrationAlgorithmInterface<TMovingImage, TTargetImage> Superclass;

        typedef typename Superclass::MovingImageType MovingImageType;
        typedef typename Superclass::TargetImageType TargetImageType;
        typedef typename Superclass::MovingImageConstPointer MovingImageConstPointer;
        typedef typename Superclass::TargetImageConstPointer TargetImageConstPointer;
        typedef unsigned int SlotIndexType;

        itkTypeMacroNoParent(ImageRegistrationAlgorithmInterfaceV2);

        /*! @brief gets a const pointer to the moving image for the specified index
        @eguarantee strong
        @param index Index of the requested slot.
        @return a const pointer to the moving image
        @pre If index is out of bound an exception will be thrown.
        */
        MovingImageConstPointer getNthMovingImage(SlotIndexType index) const
        {
          if (index >= this->getMovingImageCount())
          {
            mapDefaultExceptionMacro(<< "Error. Index of requested moving image is out of bounds. Requested index: " << index << "; number of images: " << getMovingImageCount());
          }
          return doGetNthMovingImage(index);
        };

        /*! @brief gets a const pointer to the target image for the specified index
        @eguarantee strong
        @param index Index of the requested slot.
        @return a const pointer to the target image. If no data has been set for the index
        null ptr will be returned.
        @pre If index is out of bound an exception will be thrown.
        */
        TargetImageConstPointer getNthTargetImage(SlotIndexType index) const
        {
          if (index >= this->getTargetImageCount())
          {
            mapDefaultExceptionMacro(<< "Error. Index of requested target image is out of bounds. Requested index: " << index << "; number of images: " << getNthTargetImage());
          }
          return doGetNthTargetImage(index);
        };

        /*! @brief sets the moving image for a specified slot index
        @eguarantee strong
        @param pMovingImage a pointer to the moving image
        @param index Index of the slot.
        @pre If index is out of bound an exception will be thrown.
        */
        void setNthMovingImage(SlotIndexType index, const MovingImageType* pMovingImage)
        {
          if (index >= this->getMovingImageCount())
          {
            mapDefaultExceptionMacro(<< "Error. Setter index of moving image is out of bounds. Specified index: " << index << "; number of image slots: " << getMovingImageCount());
          }
          return doSetNthMovingImage(index, pMovingImage);
        };

        /*! @brief sets the target image for a specified slot index
        @eguarantee strong
        @param pTargetImage a pointer to the moving image
        @param index Index of the slot.
        @pre If index is out of bound an exception will be thrown.
        */
        void setNthTargetImage(SlotIndexType index, const TargetImageType* pTargetImage)
        {
          if (index >= this->getTargetImageCount())
          {
            mapDefaultExceptionMacro(<< "Error. Setter index of target image is out of bounds. Specified index: " << index << "; number of image slots: " << getMovingImageCount());
          }
          return doSetNthTargetImage(index, pTargetImage);
        };

        /*! Indicates if the target and input data of one index are coupled or not. Coupled means
        that if the index for one role (target or moving) is set, the other role at this index
        must also be set.
        @return True if coupled. False if not.
        @eguarantee strong*/
        virtual bool hasCoupledImageInputs() const { return true; };

        /*! Indicates if the passed index indicates a mandatory (false) or an optional (true) input.*/
        virtual bool isOptionalTargetImage(SlotIndexType index) const { return false; };

        /*! Indicates if the passed index indicates a mandatory (false) or an optional (true) input.*/
        virtual bool isOptionalMovingImage(SlotIndexType index) const { return false; };

        /*! Gets the number of target inputs (in total: onlyMandatory == false)
        @eguarantee strong
        */
        virtual SlotIndexType getTargetImageCount(bool onlyMandatory = false) const { return 1; };

        /*! Gets the number of moving inputs (in total: onlyMandatory == false)
        @eguarantee strong
        */
        virtual SlotIndexType getMovingImageCount(bool onlyMandatory = false) const { return 1; };

        /*! returns the modification time of the target image.
        */
        virtual unsigned long getNthTargetImageMTime(SlotIndexType index) const = 0;

        /*! returns the modification time of the moving image.
        */
        virtual unsigned long getNthMovingImageMTime(SlotIndexType index) const = 0;

        virtual MovingImageConstPointer getMovingImage() const override
        {
          return getNthMovingImage(0);
        };

        virtual TargetImageConstPointer getTargetImage() const override
        {
          return getNthTargetImage(0);
        }

        virtual void setMovingImage(const MovingImageType* pMovingImage) override
        {
          setNthMovingImage(0, pMovingImage);
        };

        virtual void setTargetImage(const TargetImageType* pTargetImage) override
        {
          setNthTargetImage(0, pTargetImage);
        };

        virtual unsigned long getTargetImageMTime() const override
        {
          return getNthTargetImageMTime(0);
        };

        virtual unsigned long getMovingImageMTime() const override
        {
          return getNthMovingImageMTime(0);
        };

			protected:
				/*! @brief virtual destructor
				*/
        virtual ~ImageRegistrationAlgorithmInterfaceV2() {};

        ImageRegistrationAlgorithmInterfaceV2() {};

        virtual MovingImageConstPointer doGetNthMovingImage(SlotIndexType index) const = 0;

        virtual TargetImageConstPointer doGetNthTargetImage(SlotIndexType index) const = 0;

        virtual void doSetNthMovingImage(SlotIndexType index, const MovingImageType* pMovingImage) = 0;

        virtual void doSetNthTargetImage(SlotIndexType index, const TargetImageType* pTargetImage) = 0;

			private:
				//No copy constructor allowed
        ImageRegistrationAlgorithmInterfaceV2(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};
		}
	}
}

#endif
