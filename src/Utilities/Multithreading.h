/*
    Hyperspace Explorer - visualizing higher-dimensional geometry
    Copyright (C) 2012  Lene Preuss <lene.preuss@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef PARTITIONEDMULTITHREADEDMAP_H
#define	PARTITIONEDMULTITHREADEDMAP_H

#include "MultithreadingPrivate.h"

#if QT_VERSION < 050000
# include <QtConcurrent/QtConcurrentMap>
#else
# include <QtConcurrentMap>
#endif

/// Functions for multithreaded manipulation of data containers.
/**
 *  The namespace \c Multithreading contains functions that run concurrently on 
 *  a random access container using the minimum necessary number of threads 
 *  (usually the number of processors available in the system).
 * 
 *  \todo Also provide an abstraction layer for the threading model that is used
 *      to execute threads (currently only \c QThread and \c QtConcurrent, but 
 *      C++11's \c std::thread is also feasible).
 */
namespace Multithreading {

    template <class RandomAccessContainer, typename Function> 
    RandomAccessContainer mapped(const RandomAccessContainer &container, Function function) {
        return QtConcurrent::blockingMapped<RandomAccessContainer>(container, function);
    }
    
    /// Run a function concurrently on every element of a random access container, 
    /// writing every modified element of the container to another container.
    /** 
     *  The number of threads started is controlled by the parameter \p tasks_per_processor.
     *  The container is partitioned so that every thread works on as many elements are 
     *  necessary so that \p tasks_per_processor threads are started per available
     *  processor.
     * 
     *  \tparam RandomAccessContainer Type of the \p container on which the operation
     *          is run. Must support \c operator[]().
     *  \tparam Function Type of the operation that is run on every element of the 
     *          \p container. Either a function with the signature 
     *          \code T function(const T &argument) \endcode or a functor class whose
     *          \c operator()() has that signature.
     *  \param container The container on whose elements the Function is run.
     *  \param output The result of the operation run on \p container.
     *  \param function The Function that is called on every element of \p container.
     *  \param tasks_per_processor number of tasks that is started for every available
     *          processor or core.
     */
    template <class RandomAccessContainer, typename Function> 
    void partitionedMap(
        const RandomAccessContainer &container, RandomAccessContainer &output, Function function, 
        unsigned tasks_per_processor = 1
    ) {
        auto tasks = Private::Kernel<RandomAccessContainer, Function>::generateKernels(container, output, function, tasks_per_processor);

        Private::Kernel<RandomAccessContainer, Function>::startTasks(tasks);
        
        Private::Kernel<RandomAccessContainer, Function>::waitForTasks(tasks);
    }

    /// Run a function concurrently on every element of a random access container, 
    /// modifying every element of the container in place.
    /** 
     *  The number of threads started is controlled by the parameter \p tasks_per_processor.
     *  The container is partitioned so that every thread works on as many elements are 
     *  necessary so that \p tasks_per_processor threads are started per available
     *  processor.
     * 
     *  \tparam RandomAccessContainer Type of the \p container on which the operation
     *          is run. Must support \c operator[]().
     *  \tparam Function Type of the operation that is run on every element of the 
     *          \p container. Either a function with the signature 
     *          \code T function(const T &argument) \endcode or a functor class whose
     *          \c operator()() has that signature.
     *  \param container The container on whose elements the Function is run.
     *  \param function The Function that is called on every element of \p container.
     *  \param tasks_per_processor number of tasks that is started for every available
     *          processor or core.
     */
    template <class RandomAccessContainer, typename Function> 
    void partitionedMap(
        RandomAccessContainer &container, Function function, unsigned tasks_per_processor = 1
    ) {
        partitionedMap(container, container, function, tasks_per_processor);
    }

    /// Run a function concurrently on every element of a random access container, 
    /// collecting the results of each operation in another container and returning them.
    /** 
     *  The number of threads started is controlled by the parameter \p tasks_per_processor.
     *  The container is partitioned so that every thread works on as many elements are 
     *  necessary so that \p tasks_per_processor threads are started per available
     *  processor.
     * 
     *  \tparam RandomAccessContainer Type of the \p container on which the operation
     *          is run. Must support \c operator[]().
     *  \tparam Function Type of the operation that is run on every element of the 
     *          \p container. Either a function with the signature 
     *          \code T function(const T &argument) \endcode or a functor class whose
     *          \c operator()() has that signature.
     *  \param container The container on whose elements the Function is run.
     *  \param function The Function that is called on every element of \p container.
     *  \param tasks_per_processor number of tasks that is started for every available
     *          processor or core.
     *  \return The result of the operation run on \p container.
     */
    template <class RandomAccessContainer, typename Function> 
    RandomAccessContainer partitionedMapped(
        const RandomAccessContainer &container, Function function, unsigned tasks_per_processor = 1
    ) {
        RandomAccessContainer output(container.size());
        
        partitionedMap(container, output, function, tasks_per_processor);

        return output;
    }
    
}

#endif	/* PARTITIONEDMULTITHREADEDMAP_H */
