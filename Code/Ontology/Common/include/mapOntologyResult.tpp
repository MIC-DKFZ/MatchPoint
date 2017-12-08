// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright c German Cancer Research Center DKFZ,
// Software development for Integrated Diagnostics and Therapy SIDT.
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------





#ifndef __MAP_RESULT_TPP
#define __MAP_RESULT_TPP

namespace iro
{

    template <typename TResultType>
    typename Result<TResultType>::ResultType&
      Result<TResultType>::
      operator*()
    {
      return this->_result;
    };

    template <typename TResultType>
    const typename Result<TResultType>::ResultType&
      Result<TResultType>::
      operator*() const
    {
      return this->_result;
    };

    template <typename TResultType>
    const typename Result<TResultType>::ResultType*
      Result<TResultType>::
      operator->() const
    {
      return &(this->_result);
    };

    template <typename TResultType>
    typename Result<TResultType>::ResultType*
      Result<TResultType>::
      operator->()
    {
      return &(this->_result);
    };

    template <typename TResultType>
      Result<TResultType>::
      operator ResultType() const
    {
      return this->_result;
    };

    template <typename TResultType>
    typename Result<TResultType>::ResultType&
      Result<TResultType>::
      getValue()
    {
      return this->_result;
    };

    template <typename TResultType>
    const typename Result<TResultType>::ResultType&
      Result<TResultType>::
      getValue() const
    {
      return this->_result;
    };

    template <typename TResultType>
    const typename Result<TResultType>::OntologyRevisionTag&
      Result<TResultType>::
      getRevision() const
    {
      return _revision;
    };

    template <typename TResultType>
      Result<TResultType>::
      ~Result()
    {
    };

    template <typename TResultType>
      Result<TResultType>::
        Result(ResultType resultValue, const OntologyRevisionTag& tag) : _result(resultValue), _revision(tag)
      {};

    template <typename TResultType>
      Result<TResultType>::
      Result(const Result<TResultType>& result) : _result(result._result), _revision(result._revision)
    {
    };

    template <typename TResultType>
    Result<TResultType>&
      Result<TResultType>::
      operator=(const Result<TResultType>& result)
    {
      if (&result != this)
      {
        _result = result._result;
        _revision = result._revision;        
      }

      return *this;
    };




    template <typename TResultType>
    typename Result< std::shared_ptr<TResultType> >::PlainResultType&
      Result< std::shared_ptr<TResultType> >::
      operator*()
    {
      return *(this->_result.get());
    };

    template <typename TResultType>
    const typename Result< std::shared_ptr<TResultType> >::PlainResultType&
      Result< std::shared_ptr<TResultType> >::
      operator*() const
    {
      return *(this->_result.get());
    };

    template <typename TResultType>
    const typename Result< std::shared_ptr<TResultType> >::PlainResultType*
      Result< std::shared_ptr<TResultType> >::
      operator->() const
    {
      return this->_result.get();
    };

    template <typename TResultType>
    typename Result< std::shared_ptr<TResultType> >::PlainResultType*
      Result< std::shared_ptr<TResultType> >::
      operator->()
    {
      return this->_result.get();
    };

    template <typename TResultType>
      Result< std::shared_ptr<TResultType> >::
      operator ResultType() const
    {
      return this->_result;
    };

    template <typename TResultType>
    typename Result< std::shared_ptr<TResultType> >::ResultType&
      Result< std::shared_ptr<TResultType> >::
      getValue()
    {
      return this->_result;
    };

    template <typename TResultType>
    const typename Result< std::shared_ptr<TResultType> >::ResultType&
      Result< std::shared_ptr<TResultType> >::
      getValue() const
    {
      return this->_result;
    };

    template <typename TResultType>
    const typename Result< std::shared_ptr<TResultType> >::OntologyRevisionTag&
      Result< std::shared_ptr<TResultType> >::
      getRevision() const
    {
      return _revision;
    };

    template <typename TResultType>
      Result< std::shared_ptr<TResultType> >::
      ~Result()
    {
    };

    template <typename TResultType>
      Result< std::shared_ptr<TResultType> >::
        Result(ResultType resultValue, const OntologyRevisionTag& tag) : _result(resultValue), _revision(tag)
      {};

    template <typename TResultType>
      Result< std::shared_ptr<TResultType> >::
      Result(const Result< std::shared_ptr<TResultType> >& result) : _result(result._result), _revision(result._revision)
    {
    };

    template <typename TResultType>
    Result< std::shared_ptr<TResultType> >&
      Result< std::shared_ptr<TResultType> >::
      operator=(const Result< std::shared_ptr<TResultType> >& result)
    {
      if (&result != this)
      {
        _result = result._result;
        _revision = result._revision;        
      }

      return *this;
    };


} // end namespace iro

#endif
