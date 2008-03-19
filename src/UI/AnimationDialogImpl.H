
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include <QDialog>

#include "ui_AnimationDialog.h"

/** A Dialog to select settings concerning the writing of animated frames
 *  to disk
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class AnimationDialogImpl:
        public QDialog, public Ui::AnimationDialog {

    Q_OBJECT

    public:
        AnimationDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
        virtual ~AnimationDialogImpl() {}
        int getFrames() {
            return framesCheckBox->isChecked()?
                    framesSpinBox->value(): -1;
        }
        QString getDir() { return directoryEdit->text(); }
        QString getPrefix() { return prefixEdit->text(); }

    protected slots:
        void openFileDialog();
};
