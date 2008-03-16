//
// C++ Implementation: PluginCreator
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "Globals.H"
#include "PluginCreator.H"

/** display  and load the selected DLL into current address space
 *  loads a dynamic library, which can be selected by the user on a QFileDialog.
 *  calls functionPresent() below. see there.
 *  @param type the plugin's function type: real, polar, surface or complex
 *  @param parent the QDialog calling this function
 *  @return success                                                           */
bool PluginCreator::loadFunction(const QString &type, QDialog *parent) {
    QString libName;
    //  iterate through resource directories until plugin subdirectory found
    for (QStringList::Iterator it = Globals::Instance().rcdirs.begin();
         it != Globals::Instance().rcdirs.end();
         ++it ) {
        QDir current (*it);
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

/** this function is called when the user clicks the OK button in the Function
 *  Dialog. Checks whether all fields are filled in, whether the given function
 *  is valid C++ syntax, ie. whether it compiles, and whether the compiled code
 *  links into a dynamic library.
 *  as a side effect, it generates this library.
 *  finally, it checks whether the library can be loaded. if so, it accepts the
 *  input.
 *  also, this function creates a directory structure "plugins/real" under the
 *  resource directory and changes the CWD to that folder for the duration of
 *  checkValidity ().
 *  the name for this function is chosen rather unfortunately, i guess.
 *
 *  @param type the plugin's function type: real, polar, surface or complex
 *  @param name the name of the plugin
 *  @param parent the QDialog calling this function
 *  @return success                                                           */
bool PluginCreator::checkValidity(const QString &type, const QString &name,
                                  QDialog *parent) {
    QString currentPath = QDir::currentPath();
    QDir::setCurrent (*(Globals::Instance().rcdirs.begin()));

    if (!QDir::current ().exists ("plugins"))
        QDir::current ().mkdir ("plugins");
    if (!QDir::current ().exists ("plugins/"+type))
        QDir::current ().mkdir ("plugins/"+type);

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

/** compile the C++ source code written by writeSource (), displaying errors and
 *  warnings, if they come up.
 *  needs "Vector.H" in the current directory or in the C++ include path.
 *  TODO: might tweak the compilation flags a little, or make them variable
 *  @param name the name of the plugin
 *  @return success                                                           */
bool PluginCreator::compile (QString name) {
    QString compileCommand = "g++ -I.. -I../.. -I"
            +Globals::Instance().rcdirs.join("/plugins -I")+"/plugins"
            +" -g -c -Wall -fPIC \""
            +name
            +".C\" > /tmp/HyperspaceExplorer.compile.errors 2>&1";
    bool Success = !system (compileCommand.toStdString().c_str());

    if (!Success) {
        QFile Errs ("/tmp/HyperspaceExplorer.compile.errors");
        Errs.open (QIODevice::ReadOnly);
        QString ErrString (Errs.readAll ());
        QMessageBox::warning (NULL, "Compilation Errors",
                              compileCommand+":\n"+ErrString);
    }

    return Success;
}


/** link the object file generated by compile () into a dynamic library.
 *  @param name the name of the plugin
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
