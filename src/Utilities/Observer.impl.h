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

#include "Observer.h"

#include <list>
#include <algorithm>
#include <functional>

using std::shared_ptr;
using std::list;
using std::binary_function;
using std::for_each;

template <class Parent>
struct Subject<Parent>::Impl {
  list< shared_ptr< Observer<Parent> > > observers_;
};

template <class Parent>
Subject<Parent>::Subject(): pImpl_(new Impl) { }

template <class Parent>
Subject<Parent>::~Subject() { }

template <class Parent>
void Subject<Parent>::attach(shared_ptr< Observer<Parent> > observer) {
  pImpl_->observers_.push_back(observer);
}

template <class Parent>
void Subject<Parent>::detach(shared_ptr< Observer<Parent> > observer) {
  pImpl_->observers_.remove(observer);
}

template <class Parent>
struct Update: public binary_function< shared_ptr< Observer<Parent> >, shared_ptr< const Subject<Parent> >, void > {
  void operator()(shared_ptr< Observer<Parent> > observer, shared_ptr< const Subject<Parent> > subject) const {
    observer->update(subject);
  }
};

template <class Parent>
void Subject<Parent>::notify() {
  static Update<Parent> update;
  for_each(pImpl_->observers_.begin(), pImpl_->observers_.end(),
           std::bind2nd(update, this));
}

template <class Parent>
Observer<Parent>::~Observer() { }
