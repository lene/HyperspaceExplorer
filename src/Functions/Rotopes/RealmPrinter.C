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

#include "Realm.h"

#include <QtDebug>

using std::vector;
using std::endl;

const std::string Realm::RealmPrinter::PRINT_DIMENSION_SPACER = "    ";
unsigned Realm::RealmPrinter::_max_dimension = 0;

void Realm::RealmPrinter::print(std::ostream &out) const {

    if (_realm->dimension() > _max_dimension) _max_dimension = _realm->dimension();

    printHeader(out);
    if (_realm->dimension() == 0) printPoint(out);
    else printSubrealms(out);
    indentNextLine(out);
    printFooter(out);
}

void Realm::RealmPrinter::printHeader(std::ostream &out) const {
    if (_realm->dimension()) {
        for (unsigned space = _realm->dimension(); space < _max_dimension; ++space) {
            out << PRINT_DIMENSION_SPACER;
        }
        out << "[" << _realm->dimension() << "] ";
        out << "(";
    }
}

void Realm::RealmPrinter::printFooter(std::ostream &out) const {
    if (_realm->dimension()) out << ")" << endl;
}

void Realm::RealmPrinter::printPoint(std::ostream &out) const {
    out << _realm->toIndex() << " ";
}

void Realm::RealmPrinter::printSubrealms(std::ostream &out) const {
    if (_realm->dimension() > 2) out << endl;
    for (realm_container_type::const_iterator i = _realm->_subrealm.begin();
         i != _realm->_subrealm.end(); ++i) {
        out <<i->toString();
    }
}

void Realm::RealmPrinter::indentNextLine(std::ostream &out) const {
    if (_realm->dimension() > 2) {
        for (unsigned space = _realm->dimension(); space < _max_dimension; ++space) {
            out << PRINT_DIMENSION_SPACER;
        }
    }
}
