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

#include <iostream>

#include <QFileDialog>
#include <QString>

#include "AnimationDialogImpl.h"

namespace UI {
    namespace Dialogs {
        /** AnimationDialogImpl c'tor taking parameters for the parent AnimationDialog,
        *  which in turn inherited them from QDialog
        *  displays the dialog
        *  @param parent parent widget (NULL)
        *  @param f window flags                                                     */
        AnimationDialogImpl::AnimationDialogImpl (QWidget *parent, Qt::WFlags f) :
                QDialog (parent, f) {
        setupUi(this);
        connect (fileDialogButton, SIGNAL(clicked()), this, SLOT(openFileDialog()));
        show ();
        }

        void AnimationDialogImpl::openFileDialog() {
            QString dirName = QFileDialog::getExistingDirectory(
                this,
                QObject::tr("Select a directory to save the animation frames"),
                QDir::currentPath(), QFileDialog::ShowDirsOnly);
            if (!dirName.isEmpty()) directoryEdit->setText(dirName);
        }
    }
}
