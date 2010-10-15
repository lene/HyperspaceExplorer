/*
Hyperspace Explorer - visualizing higher-dimensional geometry
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

#include "ScopedTimer.h"

#include <QTime>

struct ScopedTimer::Impl {
  Impl(const std::string& message, std::ostream& out):
    message_(message), out_(out), startTime_(QTime::currentTime()) { }

  std::string message_;
  std::ostream &out_;
  QTime startTime_;

};

ScopedTimer::ScopedTimer(const std::string& message, std::ostream& out): pImpl_(new Impl(message, out)) { }

ScopedTimer::~ScopedTimer() {
  QTime timeNow = QTime::currentTime();
  int msecsElapsed = pImpl_->startTime_.msecsTo(timeNow);
  double timeElapsed = (double)msecsElapsed/1000.;
  pImpl_->out_ << pImpl_->message_ << ": " << timeElapsed << "\n";
}
