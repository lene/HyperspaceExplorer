////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author or Addison-Wesley Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////
#ifndef LOKI_FUNCTOR_INC_
#define LOKI_FUNCTOR_INC_

// $Id: Functor.h 750 2006-10-17 19:50:02Z syntheticpp $


#include "Typelist.h"
//#include "Sequence.h"
#include "EmptyType.h"
#include "TypeTraits.h"
#include <typeinfo>
#include <memory>

///  \defgroup FunctorGroup Function objects

/// \namespace Loki
/// All classes of Loki are in the Loki namespace
namespace Loki
{
////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl (internal)
////////////////////////////////////////////////////////////////////////////////

    namespace Private
    {
        template <typename R>
        struct FunctorImplBase 
        {
            typedef R ResultType;
            typedef FunctorImplBase<R> FunctorImplBaseType;

            typedef EmptyType Parm1;
            typedef EmptyType Parm2;
            typedef EmptyType Parm3;
            typedef EmptyType Parm4;

            virtual ~FunctorImplBase()
            {}

            virtual FunctorImplBase* DoClone() const = 0;

            template <class U>
            static U* Clone(U* pObj)
            {
                if (!pObj) return 0;
                U* pClone = static_cast<U*>(pObj->DoClone());
                assert(typeid(*pClone) == typeid(*pObj));
                return pClone;
            }


        };
    }
    
////////////////////////////////////////////////////////////////////////////////
// macro LOKI_DEFINE_CLONE_FUNCTORIMPL
// Implements the DoClone function for a functor implementation
////////////////////////////////////////////////////////////////////////////////

#define LOKI_DEFINE_CLONE_FUNCTORIMPL(Cls) \
    virtual Cls* DoClone() const { return new Cls(*this); }

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// The base class for a hierarchy of functors. The FunctorImpl class is not used
//     directly; rather, the Functor class manages and forwards to a pointer to
//     FunctorImpl
// You may want to derive your own functors from FunctorImpl.
// Specializations of FunctorImpl for up to 15 parameters follow
////////////////////////////////////////////////////////////////////////////////

    template <typename R, class TList>
    class FunctorImpl;

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 0 (zero) parameters
////////////////////////////////////////////////////////////////////////////////

    template <typename R>
    class FunctorImpl<R, NullType>
        : public Private::FunctorImplBase<R>
    {
    public:
        typedef R ResultType;
        virtual R operator()() = 0;
    };

    ////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 1 parameter
////////////////////////////////////////////////////////////////////////////////

    template <typename R, typename P1>
        class FunctorImpl<R, Seq<P1> >
        : public Private::FunctorImplBase<R>
    {
    public:
        typedef R ResultType;
        typedef typename TypeTraits<P1>::ParameterType Parm1;
        virtual R operator()(Parm1) = 0;
    };

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 2 parameters
////////////////////////////////////////////////////////////////////////////////

    template <typename R, typename P1, typename P2>
    class FunctorImpl<R, Seq<P1, P2> >
        : public Private::FunctorImplBase<R>
    {
    public:
        typedef R ResultType;
        typedef typename TypeTraits<P1>::ParameterType Parm1;
        typedef typename TypeTraits<P2>::ParameterType Parm2;
        virtual R operator()(Parm1, Parm2) = 0;
    };

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 3 parameters
////////////////////////////////////////////////////////////////////////////////

    template <typename R, typename P1, typename P2, typename P3>
    class FunctorImpl<R, Seq<P1, P2, P3> >
        : public Private::FunctorImplBase<R>
    {
    public:
        typedef R ResultType;
        typedef typename TypeTraits<P1>::ParameterType Parm1;
        typedef typename TypeTraits<P2>::ParameterType Parm2;
        typedef typename TypeTraits<P3>::ParameterType Parm3;
        virtual R operator()(Parm1, Parm2, Parm3) = 0;
    };

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 4 parameters
////////////////////////////////////////////////////////////////////////////////

    template <typename R, typename P1, typename P2, typename P3, typename P4>
    class FunctorImpl<R, Seq<P1, P2, P3, P4> >
        : public Private::FunctorImplBase<R>
    {
    public:
        typedef R ResultType;
        typedef typename TypeTraits<P1>::ParameterType Parm1;
        typedef typename TypeTraits<P2>::ParameterType Parm2;
        typedef typename TypeTraits<P3>::ParameterType Parm3;
        typedef typename TypeTraits<P4>::ParameterType Parm4;
        virtual R operator()(Parm1, Parm2, Parm3, Parm4) = 0;
    };

#ifndef LOKI_DISABLE_TYPELIST_MACROS

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 1 parameter
////////////////////////////////////////////////////////////////////////////////

    template <typename R, typename P1>
    class FunctorImpl<R, LOKI_TYPELIST_1(P1)>
        : public Private::FunctorImplBase<R>
    {
    public:
        typedef R ResultType;
        typedef typename TypeTraits<P1>::ParameterType Parm1;
        virtual R operator()(Parm1) = 0;
    };

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 2 parameters
////////////////////////////////////////////////////////////////////////////////

    template <typename R, typename P1, typename P2>
    class FunctorImpl<R, LOKI_TYPELIST_2(P1, P2)>
        : public Private::FunctorImplBase<R>
    {
    public:
        typedef R ResultType;
        typedef typename TypeTraits<P1>::ParameterType Parm1;
        typedef typename TypeTraits<P2>::ParameterType Parm2;
        virtual R operator()(Parm1, Parm2) = 0;
    };

/** class template FunctorImpl
 *  Specialization for 3 parameters */
    template <typename R, typename P1, typename P2, typename P3>
    class FunctorImpl<R, LOKI_TYPELIST_3(P1, P2, P3)>
        : public Private::FunctorImplBase<R>
    {
    public:
        typedef R ResultType;
        typedef typename TypeTraits<P1>::ParameterType Parm1;
        typedef typename TypeTraits<P2>::ParameterType Parm2;
        typedef typename TypeTraits<P3>::ParameterType Parm3;
        virtual R operator()(Parm1, Parm2, Parm3) = 0;
    };

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for 4 parameters
////////////////////////////////////////////////////////////////////////////////

    template <typename R, typename P1, typename P2, typename P3, typename P4>
    class FunctorImpl<R, LOKI_TYPELIST_4(P1, P2, P3, P4)>
        : public Private::FunctorImplBase<R>
    {
    public:
        typedef R ResultType;
        typedef typename TypeTraits<P1>::ParameterType Parm1;
        typedef typename TypeTraits<P2>::ParameterType Parm2;
        typedef typename TypeTraits<P3>::ParameterType Parm3;
        typedef typename TypeTraits<P4>::ParameterType Parm4;
        virtual R operator()(Parm1, Parm2, Parm3, Parm4) = 0;
    };


#endif //LOKI_DISABLE_TYPELIST_MACROS

////////////////////////////////////////////////////////////////////////////////
// class template FunctorHandler
// Wraps functors and pointers to functions
////////////////////////////////////////////////////////////////////////////////

    template <class ParentFunctor, typename Fun>
    class FunctorHandler
        : public ParentFunctor::Impl
    {
        typedef typename ParentFunctor::Impl Base;

    public:
        typedef typename Base::ResultType ResultType;
        typedef typename Base::Parm1 Parm1;
        typedef typename Base::Parm2 Parm2;
        typedef typename Base::Parm3 Parm3;
        typedef typename Base::Parm4 Parm4;
        
        FunctorHandler(const Fun& fun) : f_(fun) {}
        
        LOKI_DEFINE_CLONE_FUNCTORIMPL(FunctorHandler)


        // operator() implementations for up to 4 arguments
                
        ResultType operator()()
        { return f_(); }

        ResultType operator()(Parm1 p1)
        { return f_(p1); }
        
        ResultType operator()(Parm1 p1, Parm2 p2)
        { return f_(p1, p2); }
        
        ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3)
        { return f_(p1, p2, p3); }
        
        ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4)
        { return f_(p1, p2, p3, p4); }
    private:
        Fun f_;
    };
        
////////////////////////////////////////////////////////////////////////////////
// class template FunctorHandler
// Wraps pointers to member functions
////////////////////////////////////////////////////////////////////////////////

    template <class ParentFunctor, typename PointerToObj,
        typename PointerToMemFn>
    class MemFunHandler : public ParentFunctor::Impl
    {
        typedef typename ParentFunctor::Impl Base;

    public:
        typedef typename Base::ResultType ResultType;
        typedef typename Base::Parm1 Parm1;
        typedef typename Base::Parm2 Parm2;
        typedef typename Base::Parm3 Parm3;
        typedef typename Base::Parm4 Parm4;

        MemFunHandler(const PointerToObj& pObj, PointerToMemFn pMemFn) 
        : pObj_(pObj), pMemFn_(pMemFn)
        {}
        
        LOKI_DEFINE_CLONE_FUNCTORIMPL(MemFunHandler)

        ResultType operator()()
        { return ((*pObj_).*pMemFn_)(); }

        ResultType operator()(Parm1 p1)
        { return ((*pObj_).*pMemFn_)(p1); }
        
        ResultType operator()(Parm1 p1, Parm2 p2)
        { return ((*pObj_).*pMemFn_)(p1, p2); }
        
        ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3)
        { return ((*pObj_).*pMemFn_)(p1, p2, p3); }
        
        ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4)
        { return ((*pObj_).*pMemFn_)(p1, p2, p3, p4); }
        
    private:
        PointerToObj pObj_;
        PointerToMemFn pMemFn_;
    };
        
////////////////////////////////////////////////////////////////////////////////
// TR1 exception
//////////////////////////////////////////////////////////////////////////////////

#ifdef LOKI_ENABLE_FUNCTION

    class bad_function_call : public std::runtime_error
    {
    public:
        bad_function_call() : std::runtime_error("bad_function_call in Loki::Functor")
        {}
    };

#define LOKI_FUNCTION_THROW_BAD_FUNCTION_CALL if(empty()) throw bad_function_call();

#else

#define LOKI_FUNCTION_THROW_BAD_FUNCTION_CALL 

#endif

////////////////////////////////////////////////////////////////////////////////
///  \class Functor
///
///  \ingroup FunctorGroup
///  A generalized functor implementation with value semantics
///
/// \par Macro: LOKI_FUNCTOR_IS_NOT_A_SMALLOBJECT
/// Define 
/// \code LOKI_FUNCTOR_IS_NOT_A_SMALLOBJECT \endcode
/// to avoid static instantiation/delete 
/// order problems.
/// It often helps against crashes when using static Functors and multi threading.
/// Defining also removes problems when unloading Dlls which hosts
/// static Functor objects.
///
/// \par Macro: LOKI_FUNCTORS_ARE_COMPARABLE
/// To enable the operator== define the macro
/// \code LOKI_FUNCTORS_ARE_COMPARABLE \endcode
/// The macro is disabled by default, because it breaks compiling functor 
/// objects  which have no operator== implemented, keep in mind when you enable
/// operator==.
////////////////////////////////////////////////////////////////////////////////
    template <typename R = void, class TList = NullType>
    class Functor
    {
    public:
        // Handy type definitions for the body type
        typedef FunctorImpl<R, TList> Impl;
        typedef R ResultType;
        typedef TList ParmList;
        typedef typename Impl::Parm1 Parm1;
        typedef typename Impl::Parm2 Parm2;
        typedef typename Impl::Parm3 Parm3;
        typedef typename Impl::Parm4 Parm4;

        // Member functions

        Functor() : spImpl_(0)
        {}
        
        Functor(const Functor& rhs) : spImpl_(Impl::Clone(rhs.spImpl_.get()))
        {}
        
        Functor(std::auto_ptr<Impl> spImpl) : spImpl_(spImpl)
        {}
        
        template <typename Fun>
        Functor(Fun fun)
        : spImpl_(new FunctorHandler<Functor, Fun>(fun))
        {}

        template <class PtrObj, typename MemFn>
        Functor(const PtrObj& p, MemFn memFn)
        : spImpl_(new MemFunHandler<Functor, PtrObj, MemFn>(p, memFn))
        {}

        typedef Impl * (std::auto_ptr<Impl>::*unspecified_bool_type)() const;

        operator unspecified_bool_type() const
        {
            return spImpl_.get() ? &std::auto_ptr<Impl>::get : 0;
        }

        Functor& operator=(const Functor& rhs)
        {
            Functor copy(rhs);
            // swap auto_ptrs by hand
            Impl* p = spImpl_.release();
            spImpl_.reset(copy.spImpl_.release());
            copy.spImpl_.reset(p);
            return *this;
        }

#ifdef LOKI_ENABLE_FUNCTION

        bool empty() const
        {
            return spImpl_.get() == 0;
        }

        void clear()
        {
            spImpl_.reset(0);
        }
#endif

        // operator() implementations for up to 15 arguments

        ResultType operator()() const
        {
            LOKI_FUNCTION_THROW_BAD_FUNCTION_CALL
            return (*spImpl_)(); 
        }

        ResultType operator()(Parm1 p1) const
        { 
            LOKI_FUNCTION_THROW_BAD_FUNCTION_CALL
            return (*spImpl_)(p1); 
        }
        
        ResultType operator()(Parm1 p1, Parm2 p2) const
        {    
            LOKI_FUNCTION_THROW_BAD_FUNCTION_CALL
            return (*spImpl_)(p1, p2); 
        }
        
        ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3) const
        {    
            LOKI_FUNCTION_THROW_BAD_FUNCTION_CALL
            return (*spImpl_)(p1, p2, p3); 
        }
        
        ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4) const
        { 
            LOKI_FUNCTION_THROW_BAD_FUNCTION_CALL
            return (*spImpl_)(p1, p2, p3, p4); 
        }
        
    private:
        std::auto_ptr<Impl> spImpl_;
    };
    
} // namespace Loki


#endif // end file guardian

