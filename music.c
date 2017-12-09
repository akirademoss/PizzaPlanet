/**
 * @file music.c
 * @brief Open Interface Load song
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#include "open_interface.h"
#include "music.h"

/**
 * Song for reaching goal
 */
void load_songs(){
    unsigned char numNotes = 13;
    unsigned char notes[13] = {74,77,86,74,77,86,88,89,88,89,88,85,81};
    unsigned char duration[13] = {12,12,18,12,12,18,10,8,8,8,8,8,15};
    oi_loadSong(SONG_OF_STORMS, numNotes, notes, duration);
}


