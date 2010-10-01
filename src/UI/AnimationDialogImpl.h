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

#include <QDialog>

#include "ui_AnimationDialog.h"

namespace UI {
    namespace Dialogs {
        /// A Dialog to select settings concerning the writing of animated frames to disk
        /** \ingroup UIGroup
         *  @author Helge Preuss <lene.preuss@gmail.com>                         */
        class AnimationDialogImpl:
                public QDialog, public Ui::AnimationDialog {

            Q_OBJECT

            public:
                AnimationDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
                virtual ~AnimationDialogImpl() {}   ///< Empty destructor
                /// Read the maximum number of frames written to disk
                /** @return maximum number of frames written to disk                  */
                int getFrames() {
                    return framesCheckBox->isChecked()?
                            framesSpinBox->value(): -1;
                }
                /// Read the directory where the images are stored
                /** @return directory where the images are stored                     */
                QString getDir() { return directoryEdit->text(); }
                /// Read the prefix of the filenames of stored images
                /** @return prefix of the filenames of stored images                  */
                QString getPrefix() { return prefixEdit->text(); }

            protected slots:
                void openFileDialog();  ///< Open a QFileDialog to select save directory
        };
    }
}
