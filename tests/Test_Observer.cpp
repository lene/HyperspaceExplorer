/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "Test_Observer.h"

#include "Observer.impl.h"

using std::shared_ptr;

class ProjectionPolicyBase {
public:
  virtual void change() { }
};

class TestSubject: public Subject< ProjectionPolicyBase > {
public:
  virtual void change() {
    ProjectionPolicyBase::change();
    notify();
  }
};

class TestObserver: public Observer< ProjectionPolicyBase > {
public:
  TestObserver(): changed_(false) { }
  bool isChanged() { return changed_; }
  virtual void update(shared_ptr< const Subject<ProjectionPolicyBase> > changedSubject) {
    changed_ = true;
  }
private:
  bool changed_;
};

struct Test_Observer::Impl {
  TestSubject subject_;
  shared_ptr<TestObserver> observer_;
};

Test_Observer::Test_Observer(): pImpl_(new Impl) { }

void Test_Observer::init() {
  pImpl_->subject_ = TestSubject();
  pImpl_->observer_ = shared_ptr<TestObserver>(new TestObserver);
}

void Test_Observer::update() {
  pImpl_->subject_.attach(pImpl_->observer_);
  pImpl_->subject_.change();
  QVERIFY(pImpl_->observer_->isChanged());
}

