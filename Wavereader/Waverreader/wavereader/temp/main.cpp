#include "soundfile.h"
#include <stdlib.h>



#ifndef OLDCPP
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif

float * get_waveform(SoundFileRead &soundfile);

// function to generate and retrun random numbers.
float * get_waveform(SoundFileRead &soundfile)
{
    static float  wave[10000];
    int i, channel;
    channel = 0;

    //loop through file grabbing samples
    //only grab one channel to start with
    //for (i=0; i<soundfile.getSamples(); i++) {
    for (i=0; i<500; i++) {
        cout << soundfile.getCurrentSampleDouble(channel) << ")\t";
        wave[i] = soundfile.getCurrentSample16Bit(channel);
    //wave[i] = soundfile.getCurrentSampleDouble(channel);
        cout << "\n";
        soundfile.incrementSample();
    }
  return wave;
}






int main(int argc, char** argv) {
   float *point_to_array;
    int i;
    Options options;
  options.process(argc, argv);
  if (options.getArgCount() == 0) {
     cout << "Usage: " << options.getCommand()
          << " filename"
          << endl;
     exit(1);
  }

  SoundFileRead soundfile(options.getArg(1));

  cout << "; Sample count = " << soundfile.getSamples() << "\n";
  cout << "; Channels     = " << soundfile.getChannels() << "\n";
  cout << "; samp\t16-bit\tdouble\n";

  point_to_array = get_waveform(soundfile);
    for (i=0; i<500; i++) {
        cout << "*(Pointer + " << i << ") : ";
        cout << *(point_to_array + i) << endl;
    }
  cout << "; samp\t16-bit\tdouble\n";
   return 0;
}


