//
// C++ Interface: PluginCreator
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PLUGIN_CREATOR_H
#define PLUGIN_CREATOR_H

/** Base class for all Dialogs which allow entering a custom function in
 *  symbolic notation and get the function compiled and loaded and displayed. \n
 *  This class contains all the variables and functions common to the four
 *  different function types, the differences being encapsulated in a template
 *  class with auxiliary functions.
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class PluginCreator {
    /** a class template with a static function to simulate a function
     *  template.
     *  @param F the type of function to be loaded                            */
    template <class F> class LoadFunctionHelper {
        public:
            static bool functionPresent(const QString &, QDialog *);
    };

    public:
        virtual ~PluginCreator() { }
        /** @return the name of the selected DLL */
        QString libraryName () { return LibraryName; }

    protected:
        virtual bool loadFunction() = 0;
        virtual bool functionPresent(const QString &) = 0;
        virtual void writeSource () = 0;

        bool loadFunction(const QString &, QDialog *);
        bool checkValidity(const QString &, const QString &, QDialog *);

        bool compile (QString);
        bool link (QString);

        QString LibraryName;
};

#include <dlfcn.h>
#include <iostream>
#include <QFile>
#include <QMessageBox>

/** loads the dynamic library given by libName, if it exists and can be loaded.
 *  then it checks whether a function named f () is present. if so, returns
 *  true. else, gives an error message.
 *
 *  @param F the type of the function to be checked for
 *  @param libName filename for the selected DLL
 *  @return success                                                           */
template <class F>
        bool PluginCreator::LoadFunctionHelper<F>::functionPresent(
            const QString &libName, QDialog *parent) {
    void *handle;
    F *f;
    char *error;

    if (!QFile::exists (libName)) {
        QMessageBox::warning (parent, "Error opening library",
                              "Library does not exist: "+libName);
        std::cerr << "Library does not exist: "+libName.toStdString()
                  << std::endl;
        return false;
    }

    handle = dlopen (libName.toStdString().c_str(), RTLD_LAZY);
    if (!handle) {
        QMessageBox::warning (parent, "Error opening library", dlerror());
        return false;
    }

    f = (F *)dlsym(handle, "f");

    if (f == NULL) {
        if ((error = dlerror()) != NULL)  {
            QMessageBox::warning (parent, "Error finding function", error);
            abort ();
            return false;
        }
    }

    dlclose(handle);

    return true;
}

#endif
