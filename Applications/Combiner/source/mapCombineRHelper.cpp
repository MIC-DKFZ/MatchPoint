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


#include "mapCombineRHelper.h"
#include "mapExceptionObjectMacros.h"
#include "mapRegistrationCombinator.h"
#include "mapRegistrationFileWriter.h"

template <unsigned int IIDim, unsigned int IODim>
map::core::RegistrationBase::Pointer
  doInversion(map::core::RegistrationBase* reg)
{
  map::core::RegistrationBase::Pointer result;
  typedef map::core::Registration<IIDim,IODim> CastedInputType;
  typedef map::core::Registration<IODim,IIDim> CastedResultType;

  typename CastedInputType::Pointer castedReg = dynamic_cast<CastedInputType*>(reg);

  if (castedReg.IsNotNull())
  {
    typename CastedResultType::Pointer castedResult = CastedResultType::New();
    map::core::RegistrationManipulator<CastedResultType> manipulator(castedResult);
    manipulator.setDirectMapping(const_cast<typename CastedResultType::DirectMappingType*>(&(castedReg->getInverseMapping())));
    manipulator.setInverseMapping(const_cast<typename CastedResultType::InverseMappingType*>(&(castedReg->getDirectMapping())));
    result = castedResult;
  }

  return result;
}

map::core::RegistrationBase::Pointer
  map::apps::combineR::invertRegistration(map::core::RegistrationBase* reg)
{
  map::core::RegistrationBase::Pointer result;

  if (reg != nullptr)
  {
    result = doInversion<2,2>(reg);
    if (result.IsNull()) { result = doInversion<3,3>(reg);
}
    if (result.IsNull()) { result = doInversion<2,3>(reg);
}
    if (result.IsNull()) { result = doInversion<3,2>(reg);
}
  }

  return result;
};


template <unsigned int IIDim, unsigned int IInterimDim, unsigned int IODim>
map::core::RegistrationBase::Pointer
  doCombination(map::core::RegistrationBase* reg1, map::core::RegistrationBase* reg2)
{
  map::core::RegistrationBase::Pointer result;
  typedef map::core::Registration<IIDim,IInterimDim> CastedReg1Type;
  typedef map::core::Registration<IInterimDim,IODim> CastedReg2Type;
  typedef map::core::Registration<IIDim,IODim> CastedResultType;

  typename CastedReg1Type::Pointer castedReg1 = dynamic_cast<CastedReg1Type*>(reg1);
  typename CastedReg2Type::Pointer castedReg2 = dynamic_cast<CastedReg2Type*>(reg2);

  if (castedReg1.IsNotNull() && castedReg2.IsNotNull())
  {
    typename map::core::RegistrationCombinator<CastedReg1Type,CastedReg2Type>::Pointer combinator = map::core::RegistrationCombinator<CastedReg1Type,CastedReg2Type>::New();
    typename map::core::RegistrationCombinator<CastedReg1Type,CastedReg2Type>::CombinedRegistrationPointer castedResult;

    castedResult = combinator->process(*(castedReg1.GetPointer()),*(castedReg2.GetPointer()));

    result = castedResult;
  }

  return result;
}

map::core::RegistrationBase::Pointer
  map::apps::combineR::combineRegistration(map::core::RegistrationBase* reg1, map::core::RegistrationBase* reg2)
{
  map::core::RegistrationBase::Pointer result;

  if(reg1->getTargetDimensions() != reg2->getMovingDimensions())
  {
    mapDefaultExceptionStaticMacro(<<"Cannot combine registration. Target dimension of reg 1 does not equal moving dimension of reg 2. Target dim reg 1: "<<reg1->getTargetDimensions()<<"; moving dim reg 2: "<<reg2->getMovingDimensions());
  }

  result = doCombination<2,2,2>(reg1,reg2);
  if (result.IsNull()) { result = doCombination<3,3,3>(reg1,reg2);
}
  if (result.IsNull()) { result = doCombination<2,3,2>(reg1,reg2);
}
  if (result.IsNull()) { result = doCombination<2,2,3>(reg1,reg2);
}
  if (result.IsNull()) { result = doCombination<3,2,2>(reg1,reg2);
}
  if (result.IsNull()) { result = doCombination<2,3,3>(reg1,reg2);
}
  if (result.IsNull()) { result = doCombination<3,3,2>(reg1,reg2);
}
  if (result.IsNull()) { result = doCombination<3,2,3>(reg1,reg2);
}

  return result;
};


template <unsigned int IIDim, unsigned int IODim>
bool
  doWriting(map::core::RegistrationBase* reg, const map::core::String& fileName)
{
  bool result = false;
  typedef map::core::Registration<IIDim,IODim> CastedInputType;

  typename CastedInputType::Pointer castedReg = dynamic_cast<CastedInputType*>(reg);

  if (castedReg.IsNotNull())
  {
    typename map::io::RegistrationFileWriter<IIDim,IODim>::Pointer writer = map::io::RegistrationFileWriter<IIDim,IODim>::New();
    writer->write(castedReg,fileName);
    result = true;
  }

  return result;
}

bool map::apps::combineR::writeRegistration(map::core::RegistrationBase* reg, const map::core::String& fileName)
{
  if(reg == nullptr)
  {
    mapDefaultExceptionStaticMacro(<<"Cannot write registration. Passed pointer is invalid");
  }

  bool result = doWriting<2,2>(reg,fileName);
  if (!result) { result = doWriting<3,3>(reg,fileName);
}
  if (!result) { result = doWriting<2,3>(reg,fileName);
}
  if (!result) { result = doWriting<3,2>(reg,fileName);
}

  return result;
};
