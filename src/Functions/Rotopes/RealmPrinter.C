#include "Realm.h"

using std::vector;
using std::endl;

const std::string Realm::RealmPrinter::PRINT_DIMENSION_SPACER = "    ";
unsigned Realm::RealmPrinter::_max_dimension = 0;

void Realm::RealmPrinter::print(std::ostream &out) const {

    if (_realm->dimension() > _max_dimension) _max_dimension = _realm->dimension();

    if (_realm->dimension() == 0) printPoint(out);
    else printSubrealms(out);

    indentNextLine(out);
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
    out << (unsigned)(*_realm) << " ";
}

void Realm::RealmPrinter::printSubrealms(std::ostream &out) const {
    if (_realm->dimension() > 2) out << endl;
    for (vector<Realm>::const_iterator i = _realm->_subrealm.begin();
         i != _realm->_subrealm.end(); ++i) {
        if (i->dimension()) out << "( ";
        out <<i->toString();
        if (i->dimension()) out << " ) ";
    }
}

void Realm::RealmPrinter::indentNextLine(std::ostream &out) const {
    if (_realm->dimension() > 2) {
        for (unsigned space = _realm->dimension(); space < _max_dimension; ++space) {
            out << PRINT_DIMENSION_SPACER;
        }
    }
}
