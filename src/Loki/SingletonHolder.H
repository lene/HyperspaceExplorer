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
#ifndef LOKI_SINGLETON_INC_
#define LOKI_SINGLETON_INC_

// $Id$

#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <cstdlib>
#include <new>
#include <vector>
#include <list>
#include <memory>

///  \defgroup  SingletonGroup Singleton
///  \defgroup  CreationGroup Creation policies
///  \ingroup   SingletonGroup
///  \defgroup  LifetimeGroup Lifetime policies
///  \ingroup   SingletonGroup
///  The lifetimes of the singleton.
///  \par Special lifetime for SmallObjects
///  When the holded object is a Small(Value)Object or the holded object
///  uses objects which are or inherit from Small(Value)Object
///  then you can't use the default lifetime: you must use the lifetime
///  \code Loki::LongevityLifetime::DieAsSmallObjectChild \endcode
///  Be aware of this when you use Loki::Factory, Loki::Functor, or Loki::Function.


/// The Loki library by Andrei Alexandrescu
/** Copyright (c) 2001 by Andrei Alexandrescu
 *
 *  This code accompanies the book:
 *
 *  Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
 *     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
 *
 *  Permission to use, copy, modify, distribute and sell this software for any
 *      purpose is hereby granted without fee, provided that the above copyright
 *      notice appear in all copies and that both that copyright notice and this
 *      permission notice appear in supporting documentation.
 *
 *  The author or Addison-Wesley Longman make no representations about the
 *      suitability of this software for any purpose. It is provided "as is"
 *      without express or implied warranty.
 **/
namespace Loki
{

    ////////////////////////////////////////////////////////////////////////////////
    ///  \struct CreateUsingNew
    ///
    ///  \ingroup CreationGroup
    ///  Implementation of the CreationPolicy used by SingletonHolder
    ///  Creates objects using a straight call to the new operator
    ////////////////////////////////////////////////////////////////////////////////
    template <class T> struct CreateUsingNew
    {
        /// create managed object
        static T* Create()
        { return new T; }

        /// destroy managed object
        static void Destroy(T* p)
        { delete p; }
    };

    ////////////////////////////////////////////////////////////////////////////////
    ///  \struct CreateUsing
    ///
    ///  \ingroup CreationGroup
    ///  Implementation of the CreationPolicy used by SingletonHolder
    ///  Creates objects using a custom allocater.
    ///  Usage: e.g. CreateUsing<std::allocator>::Allocator
    ////////////////////////////////////////////////////////////////////////////////
    template<template<class> class Alloc>
    struct CreateUsing
    {
        template <class T>
        struct Allocator
        {
            static Alloc<T> allocator;

            static T* Create()
            {
                return new (allocator.allocate(1)) T;
            }

            static void Destroy(T* p)
            {
                //allocator.destroy(p);
                p->~T();
                allocator.deallocate(p,1);
            }
        };
    };

    ////////////////////////////////////////////////////////////////////////////////
    ///  \struct CreateUsingMalloc
    ///
    ///  \ingroup CreationGroup
    ///  Implementation of the CreationPolicy used by SingletonHolder
    ///  Creates objects using a call to std::malloc, followed by a call to the
    ///  placement new operator
    ////////////////////////////////////////////////////////////////////////////////
    template <class T> struct CreateUsingMalloc
    {
        /// create managed object
        static T* Create()
        {
            void* p = std::malloc(sizeof(T));
            if (!p) return 0;
            return new(p) T;
        }

        /// destroy managed object
        static void Destroy(T* p)
        {
            p->~T();
            std::free(p);
        }
    };


    ////////////////////////////////////////////////////////////////////////////////
    ///  \struct CreateStatic
    ///
    ///  \ingroup CreationGroup
    ///  Implementation of the CreationPolicy used by SingletonHolder
    ///  Creates an object in static memory
    ///  Implementation is slightly nonportable because it uses the MaxAlign trick
    ///  (an union of all types to ensure proper memory alignment). This trick is
    ///  nonportable in theory but highly portable in practice.
    ////////////////////////////////////////////////////////////////////////////////
    template <class T> struct CreateStatic
    {
        union MaxAlign
        {
            char t_[sizeof(T)];
            short int shortInt_;
            int int_;
            long int longInt_;
            float float_;
            double double_;
            long double longDouble_;
            struct Test;
            int Test::* pMember_;
            int (Test::*pMemberFn_)(int);
        };

        /// create managed object
        static T* Create()
        {
            static MaxAlign staticMemory_;
            return new(&staticMemory_) T;
        }

        /// destroy managed object
        static void Destroy(T* p)
        {
            p->~T();
        }
    };



    ////////////////////////////////////////////////////////////////////////////////
    ///  \class  SingletonHolder
    ///
    ///  \ingroup SingletonGroup
    ///
    ///  Provides Singleton amenities for a type T
    ///  To protect that type from spurious instantiations,
    ///  you have to protect it yourself.
    ///
    ///  \param CreationPolicy Creation policy, default: CreateUsingNew
    ///  \param LifetimePolicy Lifetime policy, default: DefaultLifetime,
    ///  \param ThreadingModel Threading policy,
    ///                         default: LOKI_DEFAULT_THREADING_NO_OBJ_LEVEL
    ////////////////////////////////////////////////////////////////////////////////
    template
    <
        typename T,
        template <class> class CreationPolicy = CreateUsingNew
    >
    class SingletonHolder
    {
    public:

        ///  Type of the singleton object
        typedef T ObjectType;

        ///  Returns a reference to singleton object
        static T& Instance();

    private:
        // Helpers
        static void MakeInstance();         ///< create singleton object
        static void DestroySingleton();     ///< destroy singleton object

        // Protection
        SingletonHolder();

        // Data
        typedef T* PtrInstanceType;         ///< pointer to singleton object
        static PtrInstanceType pInstance_;  ///< pointer to singleton object
        static bool destroyed_;             ///< is singleton object destroyed?
    };

    ////////////////////////////////////////////////////////////////////////////////
    // SingletonHolder's data
    ////////////////////////////////////////////////////////////////////////////////

    template
    <
        class T,
        template <class> class C
    >
    typename SingletonHolder<T, C>::PtrInstanceType
        SingletonHolder<T, C>::pInstance_ = 0;

    template
    <
        class T,
        template <class> class C
    >
    bool SingletonHolder<T, C>::destroyed_ = false;

    ////////////////////////////////////////////////////////////////////////////////
    // SingletonHolder::Instance
    ////////////////////////////////////////////////////////////////////////////////

    template
    <
        class T,
        template <class> class CreationPolicy
    >
    inline T& SingletonHolder<T, CreationPolicy>::Instance()
    {
        if (!pInstance_)
        {
            MakeInstance();
        }
        return *pInstance_;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // SingletonHolder::MakeInstance (helper for Instance)
    ////////////////////////////////////////////////////////////////////////////////

    template
    <
        class T,
        template <class> class CreationPolicy
    >
    void SingletonHolder<T, CreationPolicy>::MakeInstance()
    {
        if (!pInstance_)
        {
            if (destroyed_)
            {
                destroyed_ = false;
            }
            pInstance_ = CreationPolicy<T>::Create();
        }
    }

    template
    <
        class T,
        template <class> class CreationPolicy
    >
    void
    SingletonHolder<T, CreationPolicy>::DestroySingleton()
    {
        assert(!destroyed_);
        CreationPolicy<T>::Destroy(pInstance_);
        pInstance_ = 0;
        destroyed_ = true;
    }


    ////////////////////////////////////////////////////////////////////////////////
    ///  \class  Singleton
    ///
    ///  \ingroup SingletonGroup
    ///
    ///  Convenience template to implement a getter function for a singleton object.
    ///  Often needed in a shared library which hosts singletons.
    ///
    ///  \par Usage
    ///
    ///  see test/SingletonDll
    ///
    ////////////////////////////////////////////////////////////////////////////////

#ifndef LOKI_SINGLETON_EXPORT
#define LOKI_SINGLETON_EXPORT
#endif

    template<class T>
    class LOKI_SINGLETON_EXPORT Singleton
    {
    public:
        static T& Instance();   ///< returns the single T object
    };

} // namespace Loki


/// \def LOKI_SINGLETON_INSTANCE_DEFINITION(SHOLDER)
/// Convenience macro for the definition of the static Instance member function
/// Put this macro called with a SingletonHolder typedef into your cpp file.

#define LOKI_SINGLETON_INSTANCE_DEFINITION(SHOLDER)                     \
namespace Loki                                                          \
{                                                                        \
    template<>                                                          \
    SHOLDER::ObjectType&  Singleton<SHOLDER::ObjectType>::Instance()    \
    {                                                                   \
        return SHOLDER::Instance();                                     \
    }                                                                    \
}


#endif // end file guardian
