
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)

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
