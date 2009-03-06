///
/// C++ Implementation: Realm
///
/// Description:
///
///
/// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2009
///
/// Copyright: See COPYING file that comes with this distribution
///
///
#include "Realm.H"

#include "Rotope.H"

using std::cout;
using std::endl;
using std::vector;

void Realm::print() const {
    if (_dimension) cout << "[" << _dimension << "] ";
    cout << "(";
    if (_dimension == 0) cout << _index;
    else {
        for (vector<Realm>::const_iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            i->print();
            cout << " ";
        }
    }
    cout << ")";
}

void Realm::add(unsigned delta) {
    if (_dimension == 0) _index += delta;
    else {
        for (vector<Realm>::iterator i = _subrealm.begin();
             i != _subrealm.end(); ++i) {
            i->add(delta);
        }
    }
}

Realm Realm::extrude(unsigned delta) {
    vector<Realm> new_subrealms;
    cout << "Realm::extrude(" << delta << ")" << endl <<"    size = " << _subrealm.size() << ", dimension = " << _dimension << endl;
    print(); cout << endl;
    if (_dimension == 0) {
        new_subrealms.push_back(_index);
        new_subrealms.push_back(_index+delta);
    } else if (_dimension == 1) {
        // special case: make surfaces so OpenGL can draw them
        // _subrealm.size() should be 2
        new_subrealms.push_back(_subrealm[0]._index);
        new_subrealms.push_back(_subrealm[1]._index);
        new_subrealms.push_back(_subrealm[1]._index+delta);
        new_subrealms.push_back(_subrealm[0]._index+delta);
//        for (unsigned i = 0; i < _subrealm.size(); ++i) {
//            new_subrealms.push_back(_subrealm[i].extrude(delta));
//        }
        Realm new_realm(new_subrealms);
        new_realm._dimension++;
        cout << "new realm: " << endl;
        new_realm.print(); cout << endl;
        return new_realm;
    } else {
        Realm copy(*this);
        new_subrealms.push_back(copy);
        for (unsigned i = 0; i < _subrealm.size(); ++i) {
            new_subrealms.push_back(_subrealm[i].extrude(delta));
        }
        copy.add(delta);
        new_subrealms.push_back(copy);
    }
    Realm new_realm(new_subrealms);
    cout << "new realm: " << endl;
    new_realm.print(); cout << endl;
    return new_realm;
}

/** Draw the Realm using OpenGL. Draws all subrealms recursively. */
void Realm::draw(Rotope *f) const {
#   if 0
        print();
        cout << endl;
#   endif
    switch (_dimension) {
        case 0:
            /** Dimension 0 is a point. Easy to draw ;-) */
            glBegin(GL_POINTS);
                f->Function::setVertex(f->X[_index], f->Xscr[_index]);
            glEnd();
            break;
        case 1:
            glBegin(GL_LINES);
                for (vector<Realm>::const_iterator i = _subrealm.begin();
                     i != _subrealm.end(); ++i) {
                    f->setVertex(f->X[i->_index], f->Xscr[i->_index]);
                }
            glEnd();
            break;
        case 2:
            /** In two dimensions, draw a surface. Current implementation simply
             *  recurses to draw the lines bordering the surface because of the 
             *  following problem.
             *
             *  What we have: 4 (or even \p N ) lines, e.g.
             *  \code (0, 1) (0, 2) (1, 3) (2, 3) \endcode
             * 
             *  what we need: 1 surface
             *  \code (0, 1, 3, 2) \endcode
             *
             *  \todo find an algorithm for this.
             */
            glBegin(GL_POLYGON);
                for (vector<Realm>::const_iterator i = _subrealm.begin();
                     i != _subrealm.end(); ++i) {
                    f->setVertex(f->X[i->_index], f->Xscr[i->_index]);
                }
            glEnd();
            break;
        default:
            /** OpenGL does not allow to draw anything above the dimension of a
             *  surface. Recurse to draw the lower order realms, until we find 
             *  surfaces.
             */
            for (vector<Realm>::const_iterator i = _subrealm.begin();
                 i != _subrealm.end(); ++i) {
                i->draw(f);
            }
            break;
    }
}

