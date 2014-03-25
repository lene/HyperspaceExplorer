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

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

#include "Globals.h"
#include "PluginCreator.h"

namespace UI {
    
  namespace Dialogs {
        
    /// Display  and load the selected DLL into current address space
    /** Loads a dynamic library, which can be selected by the user on a QFileDialog.
     *
     *  Calls functionPresent() below. see there.
     *  @param type the plugin's function type: real, polar, surface or complex
     *  @param parent the QDialog calling this function
     *  @return success                                                           
     */
    bool PluginCreator::loadFunction(const QString &type, QDialog *parent) {
            QString libName;
            //  iterate through resource directories until plugin subdirectory found
            for (auto dir: Globals::Instance().rcdirs()) {
                QDir current(dir);
                if (current.exists ("plugins/"+type)) {  //  plugin subdir present?
                    libName = QFileDialog::getOpenFileName(
                            parent,
                            QObject::tr("Open a function"),
                                current.absolutePath ()+"/plugins/"+type,
                            "Libraries (*.so*)");
                    if (!libName.isNull ()) break;      //  "Cancel" pressed
                }
            }

            if (libName.isNull ()) return false;        //  nothing found or selected

            if (functionPresent(libName)) {
                LibraryName = libName;
                parent->accept();
            }

            return false;
    }

        /// Called when the user clicks the OK button in the Function Dialog
        /** Checks whether all fields are filled in, whether the given function
        *  is valid C++ syntax, ie. whether it compiles, and whether the compiled code
        *  links into a dynamic library.
        *
        *  As a side effect, it generates this library.
        *
        *  Finally, it checks whether the library can be loaded. if so, it accepts the
        *  input.
        *
        *  Also, this function creates a directory structure "plugins/real" under the
        *  resource directory and changes the CWD to that folder for the duration of
        *  checkValidity ().
        *
        *  The name for this function is chosen rather unfortunately, i admit.
        *
        *  @param type the plugin's function type: real, polar, surface or complex
        *  @param name the name of the plugin
        *  @param parent the QDialog calling this function
        *  @return success                                                           */
        bool PluginCreator::checkValidity(const QString &type, const QString &name,
                                        QDialog *parent) {
            QString currentPath = QDir::currentPath();
            QDir::setCurrent(*(Globals::Instance().rcdirs().begin()));

            if (!QDir::current().exists ("plugins")) QDir::current().mkdir ("plugins");
            if (!QDir::current().exists ("plugins/"+type)) QDir::current().mkdir ("plugins/"+type);

            if (!QDir::current().exists(vector_include_file)) {
              for (QString rcdir: Globals::Instance().rcdirs()) {
                QString vector_h_path = findVectorHPath(rcdir);
                if (!vector_h_path.isEmpty()) {
                  QFile::copy(vector_h_path+"/"+vector_include_file, QDir::current().absolutePath()+"/"+vector_include_file);
                  std::cerr << vector_include_file.toStdString() << " found in " << rcdir.toStdString() << ": " << vector_h_path.toStdString() << std::endl;
                  break;
                }
                std::cerr << "no " << vector_include_file.toStdString() << " in " << rcdir.toStdString() << std::endl;
              }
            }
            QDir::setCurrent ("plugins/"+type);
            //  we are now in the subdirectory plugins/type under the first entry of
            //  the rcdirs list

            writeSource();                          //  generate C++ source code

            if (!compile(name)) {                   //  try to compile
                QDir::setCurrent (currentPath);
                return false;
            }

            if (!link (name)) {                     //  try to link
                QDir::setCurrent (currentPath);
                return false;
            }
            //  try to open the resulting dynamic library
            //  the name of the dynamic library must be given absolutely, because
            //  dlopen () only checks LD_LIBRARY_PATH, which usually doesn't contain "."
            if (functionPresent(QDir::currentPath ()+"/"+name+".so")) {
                LibraryName = QDir::currentPath ()+"/"+name+".so";
                parent->accept();
            }

            QDir::setCurrent (currentPath);

            return true;
        }

        /// Compile the C++ source code written by writeSource()
        /** Display errors and warnings, if they come up.
        *
        *  Needs "Vector.H" in the current directory or in the C++ include path.
        *  \todo Might tweak the compilation flags a little, or make them variable
        *  @param name the name of the plugin
        *  @return success                                                           */
        bool PluginCreator::compile (QString name) {
            QString compileCommand = "g++ -I.. -I../.. -I"
                    +Globals::Instance().rcdirs().join("/plugins -I")+"/plugins"
                    +(findVectorHPath("../..").isEmpty()? "": "-I "+findVectorHPath("../.."))
                    +" -g -c -Wall -fPIC \""
                    +name
                    +".C\" > /tmp/HyperspaceExplorer.compile.errors 2>&1";
            bool Success = !system(compileCommand.toStdString().c_str());

            if (!Success) {
                QFile Errs ("/tmp/HyperspaceExplorer.compile.errors");
                Errs.open (QIODevice::ReadOnly);
                QString ErrString (Errs.readAll ());
                QMessageBox::warning (NULL, "Compilation Errors",
                                    compileCommand+":\n"+ErrString);
            }

            return Success;
        }


        /// link the object file generated by compile() into a dynamic library.
        /** @param name the name of the plugin
        *  @return success                                                           */
        bool PluginCreator::link (QString name) {
            QString linkCommand = "g++ -shared -Wl,-export-dynamic -Wl,-soname,\""
                    +name+".so\" -o \""
                    +name+".so\" \""
                    +name+".o\""
                    +"> /tmp/HyperspaceExplorer.link.errors 2>&1";
            bool Success = !system (linkCommand.toStdString().c_str());

            if (!Success) {
                QFile Errs ("/tmp/HyperspaceExplorer.link.errors");
                Errs.open (QIODevice::ReadOnly);
                QString ErrString (Errs.readAll ());
                QMessageBox::warning (NULL, "Link Errors", linkCommand+":\n"+ErrString);
            }

            return Success;
        }
        
        QString PluginCreator::findVectorHPath(QString start_path) {
          QDir current;
          if (start_path.isEmpty()) current = QDir::current();
          else current = QDir(start_path);
          std::cerr << current.absolutePath().toStdString() << std::endl;
          
          if (current.exists(vector_include_file)) return current.absolutePath();
          
          for (QString dir: current.entryList(QDir::Dirs|QDir::NoDotAndDotDot)) {
//            std::cerr << (current.absolutePath()+"/"+dir).toStdString() << std::endl;
            if (!findVectorHPath(current.absolutePath()+"/"+dir).isEmpty()) return findVectorHPath(current.absolutePath()+"/"+dir);
          }
          return "";
        }

    }
}
