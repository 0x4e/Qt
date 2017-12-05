#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include "sys/types.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint16_t voltage;
    uint16_t current;
    uint16_t count;
} BufferParameters;


/* Circular buffer object */
typedef struct {
    int         size;   /* maximum number of elements           */
    int         start;  /* index of oldest element              */
    int         end;    /* index at which to write new element  */
    BufferParameters *bp;
    bool bufferDisabled;
} CircularBuffer;


void cb_update(u_int16_t  Ch1, u_int16_t Ch2);
void cb_disable(void);
void cb_enable(void);
void cb_init(void);
int cb_isfull(void);
int cb_isempty(void);

CircularBuffer *get_bufferPointer(void);


#ifdef __cplusplus
}
#endif


#endif // CIRCULAR_BUFFER_H
