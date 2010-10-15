/*
    Hyperspace Explorer - vizualizing higher-dimensional geometry
    Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

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

#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>

template <class Parent> class Observer;

/// An object telling its state changes to all attached Observer s.
/** An Observer can register itself for updates on the Subject's state change by
 *  calling attach() and deregister with detach().
 *
 *  Whenever the implementing Subject wants to update the registered Observer s
 *  of its changed state, it must call the notify() method.
 *
 *  This class is meant to be used as a base class for making a Subject out of a
 *  arbitrary class, without intrusion to the original class. The final
 *  implementation must insert calls to notify() wherever appropriate.
 *
 *  Example:
 *  \code
 *  class Minx {
 *    void jinx();
 *  };
 *
 *  class MinxSubject: public Subject<Minx> {
 *    void jinx() {
 *      Minx::jinx();
 *      notify();
 *    }
 *  }
 *  \endcode
 */
template <class Parent>
class Subject: public Parent {

  public:

    Subject();
    virtual ~Subject();

    virtual void attach(std::shared_ptr< Observer<Parent> > observer);
    virtual void detach(std::shared_ptr< Observer<Parent> > observer);

  protected:

    virtual void notify();

  private:

    class Impl;
    std::shared_ptr<Impl> pImpl_;
};

/// An object that is notified by a Subject it is attached to.
/** After registering with a Subject, an object of this class is notified of any
 *  change of state via the update() method.
 *
 *  This class is an abstract class. The update() method must be implemented.
 *
 *  Any Observer must register with its Subject vi Subject::attach().
 *
 *  Example:
 *  \code
 *  class MinxObserver: public Observer<Minx> {
 *    virtual void update(const Subject<Minx> *changedSubject) {
 *      // do something
 *    }
 *  };
 *
 *  MinxSubject subject;
 *  shared_ptr< Observer<Minx> > observer(new MinxObserver);
 *  subject.attach(observer);
 *  subject.jinx(); // observer->update() is called
 *  \endcode
 */
template <class Parent>
class Observer {

  public:

    virtual ~Observer();

    virtual void update(std::shared_ptr< const Subject<Parent> > changedSubject) = 0;

};

#endif // OBSERVER_H
