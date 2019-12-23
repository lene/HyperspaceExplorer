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

#ifndef PLUGIN_CREATOR_H
#define PLUGIN_CREATOR_H

namespace UI {
    namespace Dialogs {
        /// Abstract base class for all Dialogs which allow entering a custom function
        /** The user can enter a mathematical function in C++ syntax in almost
        *  symbolic notation and get the function compiled and loaded and displayed.
        *
        *  This class contains all the variables and functions common to the four
        *  different function types, the differences being encapsulated in a template
        *  class with auxiliary functions.
        *
        *  This class is abstract. The inheriting classes must implement the members
        *  loadFunction(), functionPresent() and writeSource().
        *  \todo set the function name to symbolic() in the descendants' constructors
        *  \ingroup UIGroup
        *  @author Lene Preuss <lene.preuss@gmail.com>                         */
        class PluginCreator {

            public:
                /// Class template with a static function to simulate a function template.
                /** The function \em functionPresent() tries to load a dynamic library
                *  containing a function \em f() with a variable signature.
                *  @tparam F the type of function to be loaded                            */
                template <class F> class LoadFunctionHelper {
                    public:
                        static bool functionPresent(const QString &, QDialog *);
                };

                virtual ~PluginCreator() { }    ///< Empty destructor

                /// Get the name of the selected dynamic library containing a function.
                /** @return the name of the selected DLL */
                QString libraryName () { return LibraryName; }

            protected:

                const QString vector_include_file = "Vector.h";
              
                bool loadFunction(const QString &, QDialog *);
                bool checkValidity(const QString &, const QString &, QDialog *);

                bool compile (const QString &);
                bool link (const QString &);

            private:

                /// Display  and load the selected DLL into current address space
                virtual bool loadFunction() = 0;
                /// Loads the dynamic library given by libName, if it exists and can be loaded.
                virtual bool functionPresent(const QString &) = 0;
                /// Write a C++ source file containing the given function
                virtual void writeSource() = 0;

                void setupPluginDirectoryStructure(const QString & type);
                QString findVectorHPath(const QString &start_path = "");
                bool copyVectorIncludeFile();                
                bool generatePluginFromSource(const QString &name);
                
                QString LibraryName;    ///< Filename of the DLL to be loaded
        };
    }
}

#include "FunctionDLL.h"
#include <dlfcn.h>
#include <iostream>
#include <QFile>
#include <QMessageBox>

namespace UI {
  namespace Dialogs {
    /// Loads the dynamic library given by libName, if it exists and can be loaded.
    /** Then it checks whether a function named \c f() is present.
     *
     *  If so, returns true. Else, gives an error message.
     *
     *  \tparam F The type of Function to be created.
     *  \param libName filename for the selected DLL
     *  \param parent the Dialog which calls this function
     *  \return success                                                           
     */
    template <class F>
    bool PluginCreator::LoadFunctionHelper<F>::functionPresent(const QString &libName, QDialog *parent) {

      FunctionDLL dll(libName.toStdString());
      if (!dll.isValid()) {
        QMessageBox::warning(parent, "Error opening library", dll.getError().c_str());
        return false;
      }
      
      F* f = (F *)dll.getSymbol("f");
      if (f == NULL) {
          QMessageBox::warning (parent, "Error finding function", dll.getError().c_str());
          return false;
        }

      return true;
    }
  }
}

#endif
