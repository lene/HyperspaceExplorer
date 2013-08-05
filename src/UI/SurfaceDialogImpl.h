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

#include "ui_SurfaceDialog.h"
#include "PluginCreator.h"

namespace UI {
    namespace Dialogs {
        /// A Dialog to enter a function from \f$ R^2 \rightarrow R^4 \f$
        /** The function will then be compiled into a dynamic library and loaded to be
        *  displayed on screen
        *  \ingroup UIGroup
        *  @author Helge Preuss <lene.preuss@gmail.com>                         */
        class SurfaceDialogImpl:
                public QDialog, public Ui::SurfaceDialog, public PluginCreator {
            Q_OBJECT

            public:
                SurfaceDialogImpl (QWidget *parent = 0);
                virtual ~SurfaceDialogImpl() {}

            private slots:
                virtual bool checkValidity();
                virtual bool loadFunction();

            private:
                virtual bool functionPresent(const QString &);
                virtual void writeSource ();
        };
    }
}
