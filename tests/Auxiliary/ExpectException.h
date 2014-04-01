/* 
 * File:   ExpectException.h
 * Author: lene
 *
 * Created on April 1, 2014, 6:44 PM
 */

#ifndef EXPECTEXCEPTION_H
#define	EXPECTEXCEPTION_H

#include "GlobalFunctions.h"

template <class Exception, typename Closure>
void expectException(Closure closure) {
        bool success = false;
        try {
            closure();
        } catch (const Exception &e) {
            success = true;
        } catch (...) { }
        UnitTests::test(success, std::string("Expected exception thrown"));
}
#endif	/* EXPECTEXCEPTION_H */

