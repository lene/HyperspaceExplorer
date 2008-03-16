
#include <iostream>
#include <string>

#include "Log.H"
#include "Globals.H"

using std::cerr;
using std::endl;
using std::string;

Log::Log() {
}


Log::~Log(){
}

void Log::log(string message) {
# ifdef DEBUG
    cerr << message << endl;
#endif
}

Log &Log::operator<<(const string &message) {
# ifdef DEBUG
    cerr << message;
#endif
    return *this;
}

Log &Log::operator<<(long x) {
    return operator<<(Globals::Instance().itoa(x));
}

Log &Log::operator<<(unsigned long x) {
    return operator<<(Globals::Instance().itoa(x));
}

Log &Log::operator<<(double x) {
    return operator<<(Globals::Instance().ftoa(x));
}

