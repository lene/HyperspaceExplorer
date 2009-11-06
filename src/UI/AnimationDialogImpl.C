
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

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
