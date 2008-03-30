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

/// Abstract base class for all Dialogs which allow entering a custom function
/** The user can enter a mathematical function in C++ syntax in almost
 *  symbolic notation and get the function compiled and loaded and displayed. \n
 *  This class contains all the variables and functions common to the four
 *  different function types, the differences being encapsulated in a template
 *  class with auxiliary functions. \n
 *  This class is abstract. The inheriting classes must implement the members
 *  loadFunction(), functionPresent() and writeSource().
 *  \todo set the function name to symbolic() in the descendants' constructors
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class PluginCreator {
    /// Class template with a static function to simulate a function template.
    /** The function \em functionPresent() tries to load a dynamic library
     *  containing a function \em f() with a variable signature.
     *  @param F the type of function to be loaded                            */
    template <class F> class LoadFunctionHelper {
        public:
            static bool functionPresent(const QString &, QDialog *);
    };

    public:

        virtual ~PluginCreator() { }    ///< Empty destructor

        /// Get the name of the selected dynamic library containing a function.
        /** @return the name of the selected DLL */
        QString libraryName () { return LibraryName; }

    protected:

        /// Display  and load the selected DLL into current address space
        virtual bool loadFunction() = 0;
        /// Loads the dynamic library given by libName, if it exists and can be loaded.
        virtual bool functionPresent(const QString &) = 0;
        /// Write a C++ source file containing the given function
        virtual void writeSource() = 0;

        bool loadFunction(const QString &, QDialog *);
        bool checkValidity(const QString &, const QString &, QDialog *);

        bool compile (QString);
        bool link (QString);

        QString LibraryName;    ///< Filename of the DLL to be loaded
};

#include <dlfcn.h>
#include <iostream>
#include <QFile>
#include <QMessageBox>

/// Loads the dynamic library given by libName, if it exists and can be loaded.
/** Then it checks whether a function named \em f() is present. \n
 *  If so, returns true. Else, gives an error message.
 *
 *  @param F the type of the function to be checked for
 *  @param libName filename for the selected DLL
 *  @return success                                                           */
template <class F>
        bool PluginCreator::LoadFunctionHelper<F>::functionPresent(
            const QString &libName, QDialog *parent) {
    void *handle;
    F *f;
    const char *error;

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
