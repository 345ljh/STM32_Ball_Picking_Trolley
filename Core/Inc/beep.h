#ifndef BEEP_H
#define BEEP_H

#include "tim.h"

typedef struct song_t
{
    int size;
    int buf[100];
}song;

extern song music_ready;
extern song music_thank;

void Beep_Play(song music);

#endif