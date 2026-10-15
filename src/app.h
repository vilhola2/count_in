#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <stdbool.h>

typedef struct {
    MIX_Mixer *mixer;
    MIX_Track *track1;
    SDL_Window *window;
} Appstate;

typedef struct {
    MIX_Audio *tick, *tock;
    double bpm;
} Metronome;

extern Appstate g_appstate;
extern Metronome g_default_metronome;

bool init_sdl(Appstate *app);
bool init_metronome(
    Appstate *app,
    Metronome *m,
    const char *tick_path,
    const char *tock_path,
    double bpm
);
bool init_globals(Appstate *app);

#endif
