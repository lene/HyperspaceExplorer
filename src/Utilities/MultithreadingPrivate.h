/* 
 * File:   PartitionedMultithreadedMapPrivate.h
 * Author: lene
 *
 * Created on April 9, 2012, 2:18 PM
 */

#ifndef PARTITIONEDMULTITHREADEDMAPPRIVATE_H
#define	PARTITIONEDMULTITHREADEDMAPPRIVATE_H

#include <QThread>

namespace Multithreading {

    /// Implementation details for multithreading.
    namespace Private {
                
        /// Does the work of running a function concurrently on a random access container
        /** 
         *  \tparam RandomAccessContainer Type of the \p container on which the operation
         *          is run. Must support \c operator[]().
         *  \tparam Function Type of the operation that is run on every element of the 
         *          \p container. Either a function with the signature 
         *          \code T function(const T &argument) \endcode or a functor class whose
         *          \c operator()() has that signature.
         *  \todo Adapt to the "correct" version of using QThread; see http://labs.qt.nokia.com/2010/06/17/youre-doing-it-wrong/
         *        and http://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/
         *  \todo possibility to transparently use different backends (QThread and std::thread)
         */
        template <class RandomAccessContainer, typename Function> 
        class Kernel: public QThread {

        public:
            
            static std::vector<Kernel *> generateKernels(
                const RandomAccessContainer & container, RandomAccessContainer &output, Function function, unsigned tasks_per_processor
            ) {

                const unsigned num_partitions = QThread::idealThreadCount()*tasks_per_processor;
                const unsigned elements_per_partition = container.size()/num_partitions;
                std::vector<Kernel*> tasks(num_partitions);

                if (output.size() < container.size()) {
                    output.resize(container.size());
                }
                
                for (unsigned index_start = 0, i = 0; index_start < container.size(); index_start += elements_per_partition, ++i) {
                    unsigned index_end = index_start+elements_per_partition;
                    if (index_end > container.size()) index_end = container.size();
                    tasks[i] = new Kernel(container, index_start, index_end, function, output);
                }

                return tasks;
            }

            static void startTasks(const std::vector<Kernel *> &tasks) {
                for (auto k: tasks) {
                     k->start();
                }
            }
            
            static void waitForTasks(const std::vector<Kernel *> &tasks) {
                for (auto k: tasks) {
                     k->wait();
                }
            }

        protected:
            
            void run() {
                for (unsigned i = index_start_; i < index_end_; ++i) {
                    output_[i] = function_(container_[i]);
                }
            }

        private:

            Kernel(
                const RandomAccessContainer & container, unsigned index_start, unsigned index_end, 
                Function function, RandomAccessContainer & output
            ):
                container_(container), index_start_(index_start), index_end_(index_end), 
                function_(function), output_(output) { }

            const RandomAccessContainer & container_;
            unsigned index_start_;
            unsigned index_end_;
            Function function_;
            RandomAccessContainer & output_;

        };
        
    }
    
}

#endif	/* PARTITIONEDMULTITHREADEDMAPPRIVATE_H */
