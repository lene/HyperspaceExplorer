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

#include "Test_ChangeDir.h"

#include "GlobalFunctions.h"

#include <QTemporaryDir>

using namespace UnitTests;

void Test_ChangeDir::dirIsChanged() {
    QTemporaryDir temp_dir;
    test(temp_dir.isValid(), "temporary directory created");
    test(QDir::currentPath() != temp_dir.path(), "whut? we already changed to the temp dir?");
    ChangeDir path_change(temp_dir.path());
    test(QDir::currentPath() == temp_dir.path(), "path changed");
}

void Test_ChangeDir::changeBackOnExit() {
    QTemporaryDir temp_dir;
    test(temp_dir.isValid(), "temporary directory created");
    QString old_path = QDir::currentPath();
    test(old_path != temp_dir.path(), "whut? we already changed to the temp dir?");
    {
        ChangeDir path_change(temp_dir.path());
        test(QDir::currentPath() == temp_dir.path(), "path changed");
    }
    test(QDir::currentPath() == old_path, "path changed back when objet went out of scope");
}