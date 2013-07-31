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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapRegistration.h $
*/


#ifndef __REGISTRATION_H
#define __REGISTRATION_H

#include "mapDefaultRegistrationTopologyPolicy.h"
#include "mapRegistrationBase.h"

namespace map
{
	namespace core
	{

		/* forward declaration (see mapRegistrationManipulator.h)*/
		template <typename TRegistration> class RegistrationManipulator;


		/*! @class Registration
		@brief class for registration.
		@ingroup Registration

		This class is the class for the registration.
		*/
		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
		         template <unsigned int, unsigned int> class TRegistrationTopologyPolicy = DefaultRegistrationTopologyPolicy >
		class Registration: public RegistrationBase,
			public TRegistrationTopologyPolicy<VMovingDimensions, VTargetDimensions>
		{
		public:
			typedef Registration Self;
			typedef RegistrationBase Superclass;
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;

			typedef TRegistrationTopologyPolicy<VMovingDimensions, VTargetDimensions> TopologyPolicyType;

			typedef typename TopologyPolicyType::DirectMappingType    DirectMappingType;
			typedef typename TopologyPolicyType::InverseMappingType   InverseMappingType;

			typedef typename TopologyPolicyType::MovingPointType			MovingPointType;
			typedef typename TopologyPolicyType::TargetPointType		  TargetPointType;

			typedef typename DirectMappingType::RepresentationDescriptorType  DirectFieldRepresentationType;
			typedef typename InverseMappingType::RepresentationDescriptorType InverseFieldRepresentationType;
			typedef typename DirectFieldRepresentationType::ConstPointer      DirectFieldRepresentationConstPointer;
			typedef typename InverseFieldRepresentationType::ConstPointer     InverseFieldRepresentationConstPointer;

			itkStaticConstMacro(MovingDimensions, unsigned int, VMovingDimensions);
			itkStaticConstMacro(TargetDimensions, unsigned int, VTargetDimensions);

			itkTypeMacro(Registration, RegistrationBase);
			itkNewMacro(Self);

			/*! maps a point from moving space to target space
			@eguarantee strong
			@todo der LazyFieldBasedRegistrationKernel muss dann die stong guarantee erfüllen beim erzeugen des feldes ansonsten
			ist die garantie dieser methode nicht erfüllbar. noch überprüfen
			@param inPoint pointer to a MovingPointType
			@param outPoint pointer to a TargetPointType
			@return success of operation
			@pre direct mapping kerne must be defined
			*/
			virtual bool mapPoint(const MovingPointType &inPoint, TargetPointType &outPoint) const;

			/*! maps a point from target space to moving space
			@eguarantee strong
			@todo der LazyFieldBasedRegistrationKernel muss dann die stong guarantee erfüllen beim erzeugen des feldes ansonsten
			ist die garantie dieser methode nicht erfüllbar. noch überprüfen
			@param inPoint pointer to a TargetPointType
			@param outPoint pointer to a MovingPointType
			@return success of operation
			*/
			virtual bool mapPointInverse(const TargetPointType &inPoint, MovingPointType &outPoint) const;

			/*! returns the InverseMappingType of this registration
			@eguarantee no fail
			@return a const InverseMappingType
			*/
			const InverseMappingType &getInverseMapping() const;

			/*! returns the DirectMappingType of this registration
			@eguarantee no fail
			@return a const DirectMappingType
			*/
			const DirectMappingType &getDirectMapping() const;

			/*! returns the direct FieldRepresentationDescriptor which defines the part
			of the moving space that is guaranteed to be mapped by the direct mapping kernel.
			@eguarantee strong
			@return smart pointer to a FieldRepresentationDescriptor for the supported registration space in the moving domain.
			May be null if the direct registration kernel is global and thus not limited.
			If there is a limitation, the retun value is not NULL.
			@retval NULL no field representation set/requested by the creating registration algorithm.
			*/
			DirectFieldRepresentationConstPointer getDirectFieldRepresentation() const;

			/*! returns the inverse FieldRepresentationDescriptor which defines the part
			of the target space that is guaranteed to be mapped by the inverse mapping kernel.
			@eguarantee strong
			@return a const FieldRepresentationDescriptor for the supported registration space in the target domain.
			May be null if the inverse registration kernel is global and thus not limited.
			If there is a limitation, the retun value is not NULL.
			@retval NULL no field representation set/requested by the creating registration algorithm.
			*/
			InverseFieldRepresentationConstPointer getInverseFieldRepresentation() const;

			/*! forces kernel to precompute, even if it is a LazyFieldKernel
			@eguarantee strong
			@todo der LazyFieldBasedRegistrationKernel muss dann die stong guarantee erfüllen beim erzeugen des feldes ansonsten
			ist die garantie dieser methode nicht erfüllbar. noch überprüfen
			*/
			void precomputeDirectMapping();

			/*! forces kernel to precompute, even if it is a LazyFieldKernel
			@eguarantee strong
			@todo der LazyFieldBasedRegistrationKernel muss dann die stong guarantee erfüllen beim erzeugen des feldes ansonsten
			ist die garantie dieser methode nicht erfüllbar. noch überprüfen
			*/
			void precomputeInverseMapping();

			/*! @brief Gets the number of moving dimensions
			@eguarantee no fail
			@return a SmartPointer to the ModelDescriptor
			*/
			virtual unsigned int getMovingDimensions() const;

			/*! @brief Gets the number of target dimensions
			@eguarantee no fail
			@return a SmartPointer to the ModelDescriptor
			*/
			virtual unsigned int getTargetDimensions() const;

			/*!
			@eguarantee no fail
			@return is the target representation limited
			@retval true if target representation is limited
			@retval false if target representation is not limited
			*/
			virtual bool hasLimitedTargetRepresentation() const;

			/*!
			@eguarantee no fail
			@return is the moving representation limited
			@retval true if moving representation is limited
			@retval false if moving representation is not limited
			*/
			virtual bool hasLimitedMovingRepresentation() const;

			friend class RegistrationManipulator<Self>;

		protected:
			Registration();
			~Registration();

			typename DirectMappingType::Pointer _spDirectMapping;
			typename InverseMappingType::Pointer _spInverseMapping;

			virtual void setDirectMapping(DirectMappingType *pKernel);

			virtual void setInverseMapping(InverseMappingType *pKernel);

		private:

			//No copy constructor allowed
			Registration(const Self &source);
			void operator=(const Self &); //purposely not implemented

		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		std::ostream &operator<<(std::ostream &os, const Registration<VMovingDimensions, VTargetDimensions> &registration)
		{
			registration.Print(os);
			return os;
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapRegistration.tpp"
#endif

#endif
