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

#include "ui_ComplexDialog.h"
#include "PluginCreator.h"

namespace UI {
    namespace Dialogs {
        /// A Dialog to enter a user-defined complex function, \f$ f: C \rightarrow C \f$
        /** The function will then be compiled into a dynamic library and loaded to be
        *  displayed on screen.
        *  \ingroup UIGroup
        *  @author Lene Preuss <lene.preuss@gmail.com>                         */
        class ComplexDialogImpl:
                public QDialog, public Ui::ComplexDialog, public PluginCreator {
            Q_OBJECT

            public:
                ComplexDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
                virtual ~ComplexDialogImpl() {}

            private slots:
                virtual bool checkValidity();
                virtual bool loadFunction();

            private:
                virtual bool functionPresent(const QString &);
                virtual void writeSource ();
        };
    }
}
