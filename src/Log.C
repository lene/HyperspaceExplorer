
#include <iostream>
#include <string>

#include "Log.H"

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

