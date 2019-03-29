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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/Common/boxed/mapDummyRegistrationAlgorithm.h $
*/




#ifndef __DUMMY_REGISTRATION_ALGORITHM_H
#define __DUMMY_REGISTRATION_ALGORITHM_H

#include "mapContinuous.h"

#include "mapAnalyticAlgorithmInterface.h"
#include "mapRegistrationAlgorithm.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
    mark code as components of this project
 */
namespace map
{
  namespace algorithm
  {

    namespace boxed
    {
      mapGenerateAlgorithmUIDPolicyMacro(DummyRegIDPolicy,
                                         "de.dkfz.matchpoint", "Identity", "1.0.0", "");
    }

    /*! @class DummyRegistrationAlgorithm
        @brief This is a simple registration algorithm that does nothing (and does not even have data input slots).
        The algorithm determines a registration that has an identity transform.
    	You may see this algorithm as a generation functor for identity registrations.
    	This class can be used for testing purposes.
        @ingroup Boxed
     */
    template < unsigned int VDimension, class TIdentificationPolicy = boxed::DummyRegIDPolicy >
    class DummyRegistrationAlgorithm : public facet::AnalyticAlgorithmInterface,
      public RegistrationAlgorithm<VDimension, VDimension>,
      public TIdentificationPolicy
    {
    public:
      typedef DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy> Self;
      typedef RegistrationAlgorithm<VDimension, VDimension>	Superclass;

      using Pointer = ::itk::SmartPointer<Self>;
      using ConstPointer = ::itk::SmartPointer<const Self>;
      itkTypeMacro(DummyRegistrationAlgorithm, RegistrationAlgorithm);
      mapNewAlgorithmMacro(Self);

      using IdentificationPolicyType = TIdentificationPolicy;
      using FieldRepRequirement = typename Superclass::FieldRepRequirement;
      using UIDPointer = typename Superclass::UIDPointer;
      using AlgorithmType = typename Superclass::AlgorithmType;
      using RegistrationType = typename Superclass::RegistrationType;
      using RegistrationPointer = typename Superclass::RegistrationPointer;

      mapDefineAlgorithmIdentificationByPolicyMacro;

      /*! @brief Returns the algorithm type for this registration algorithm
        @eguarantee strong
        @return The algorithm type
       */
      AlgorithmType getAlgorithmType() const override;

      typename FieldRepRequirement::Type isMovingRepresentationRequired() const override;

      typename FieldRepRequirement::Type isTargetRepresentationRequired() const override;

      bool isReusable() const override;

    protected:
      DummyRegistrationAlgorithm();
      ~DummyRegistrationAlgorithm() override;

      void configureAlgorithm() override;

      /*! @brief starts the computation of the registration
        @eguarantee strong
        @return Indicates if the registration was successfully determined (e.g. could be
        false if an iterative algorithm was stopped prematurely by the user).
       */
      bool doDetermineRegistration() override;

      /*!
       * Returns the final registration
        @eguarantee strong
       */
      RegistrationPointer doGetRegistration() const override;

      /*! Returns if the registration should be computed. The registration is outdated if doGetRegistration returns null
       * or the modification times of at least one policy is newer then the modification time of the registration.
        @eguarantee strong
        @return true if the registration should be (re)computed. False if the registration is uptodate.
       */
      bool registrationIsOutdated() const override;

      /*! Methods invoked by derived classes.  */
      void PrintSelf(std::ostream& os, ::itk::Indent indent) const override;

    private:

      RegistrationPointer _spFinalizedRegistration;

      DummyRegistrationAlgorithm(const Self& source) = delete;
      void operator=(const Self&) = delete;  //purposely not implemented
    };

  }  // namespace algorithm
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
#include "mapDummyRegistrationAlgorithm.tpp"
#endif

#endif
