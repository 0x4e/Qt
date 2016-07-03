#include "soundfile.h"
#include <stdlib.h>

#ifndef OLDCPP
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif

int main(int argc, char** argv) {
   Options options;
   options.process(argc, argv);
   SoundFileRead  insound;

   int i;
   for (i=1; i<=options.getArgCount(); i++) {
      insound.setFile(options.getArg(i));
      cout << "Filename:        " << insound.getFilename() << "\n";
      cout << insound << endl;

   }

   return 0;
}
