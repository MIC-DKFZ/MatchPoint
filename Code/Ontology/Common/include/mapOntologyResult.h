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





#ifndef __IRO_RESULT_H
#define __IRO_RESULT_H

#include "mapValidityIndicator.h"
#include <memory>

namespace iro
{
    /*! @class Result
    * @brief Helper class that is used by inference interfaces to return the query results and to bind them to a validity indicator.
    *
    * This class is used by the ontology to bind a validity indicator to inference query results and therefore offers the possibility
    * to check the validity of conclusions later on. This helper class is implemented like a pointer. Offering the possibility to
    * access directly the actual result value by operator * and ->.
    * @remark There is a template specialication for shared_ptr result types. In these cases * and -> will directly access
    * the pointer value (pointer becomes transparent). To access the shared_pointer itself use getValue().
    * @tparam TResultType The type of the result value that is passed back by a inference or integration interface.*/
    template <typename TResultType>
    class Result
    {
    public:
      typedef TResultType ResultType;

      using OntologyRevisionTag	= ::iro::OntologyRevisionTag;

      ResultType& operator*();
      const ResultType& operator*() const;

      ResultType* operator->();
      const ResultType* operator->() const;

      operator ResultType() const;

      ResultType& getValue();
      const ResultType& getValue() const;

      const OntologyRevisionTag& getRevision() const;

      ~Result();
      Result(ResultType resultValue, const OntologyRevisionTag& tag);

      Result(const Result<TResultType>& result);
      Result<TResultType>& operator=(const Result<TResultType>& result);

    protected:
      ResultType _result;
      OntologyRevisionTag _revision;
    };

       
    /*! Template specialication for shared pointer. Operator * and -> will directly access
    * the pointer value (pointer becomes transparent). To access the shared_pointer itself use getValue().
    * @tparam TResultType The type of the result value that is passed back by a inference or integration interface.*/
    template <typename TResultType>
    class Result< std::shared_ptr<TResultType> >
    {
    public:
      typedef typename std::shared_ptr<TResultType> ResultType;
      typedef TResultType PlainResultType;
      typedef Result< std::shared_ptr<TResultType> > Self;

      using OntologyRevisionTag	= ::iro::OntologyRevisionTag;

      PlainResultType& operator*();
      const PlainResultType& operator*() const;

      PlainResultType* operator->();
      const PlainResultType* operator->() const;

      operator ResultType() const;

      ResultType& getValue();
      const ResultType& getValue() const;

      const OntologyRevisionTag& getRevision() const;

      ~Result();
      Result(ResultType resultValue, const OntologyRevisionTag& tag);

      Result(const Self& result);
      Self& operator=(const Self& result);

    protected:
      ResultType _result;
      OntologyRevisionTag _revision;
    };

} // end namespace iro

#ifndef IRO_MANUAL_TPP
#include "mapOntologyResult.tpp"
#endif

#endif
