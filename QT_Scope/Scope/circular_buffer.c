#include "circular_buffer.h"


#define BUFFERSIZE 4096*4

static BufferParameters BufferParametersSamples[BUFFERSIZE];
static CircularBuffer cb={.size=BUFFERSIZE + 1, .bp=BufferParametersSamples, .bufferDisabled=0};


void cb_update(u_int16_t  Ch1, u_int16_t Ch2){

    if (cb.bufferDisabled){
        return;
    }

    BufferParametersSamples[cb.end].voltage = Ch1;
    BufferParametersSamples[cb.end].current = Ch2;
    BufferParametersSamples[cb.end].count =cb.end;

    cb.end = (cb.end + 1) % cb.size;
    if (cb.end == cb.start)
        cb.start = (cb.start + 1) % cb.size; /* full, overwrite */
}

//This function will send the caller a pointer to a bufferParameter
CircularBuffer * get_bufferPointer(){
    cb.bufferDisabled = true;
    return &cb;
}

void cb_disable(){
    cb.bufferDisabled = 1;
}
void cb_enable(){
    cb.bufferDisabled = 0;
}


void cb_init() {
    cb.size  = BUFFERSIZE + 1; /* include empty elem */
    cb.start = 0;
    cb.end   = 0;
}

int cb_isfull() {
    return (cb.end + 1) % cb.size == cb.start;
}

int cb_isempty() {
    return cb.end == cb.start;
}
