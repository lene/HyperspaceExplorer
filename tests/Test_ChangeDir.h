/*
 * Hyperspace Explorer - visualizing higher-dimensional geometry
 * Copyright (C) 2011  Lene Preuss <lene.preuss@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef TEST_CHANGEDIR_H
#define	TEST_CHANGEDIR_H

#include "ChangeDir.h"

#include <QtTest/QtTest>

class Test_ChangeDir: public QObject {
  
  Q_OBJECT
  
private slots:  
  void dirIsChanged();
  void changeBackOnExit();
  
private:
  QString temp_dir;    

};

#endif	/* TEST_CHANGEDIR_H */

