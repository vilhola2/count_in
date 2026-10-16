#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <stdbool.h>

typedef struct {
    MIX_Mixer *mixer;
    MIX_Track *track1;
    SDL_Window *window;
    SDL_Renderer *renderer;
} Appstate;

typedef struct {
    MIX_Audio *tick, *tock;
    Uint64 next_beat;
    double bpm;
    bool is_running;
} Metronome;

extern Appstate g_appstate;
extern Metronome g_default_metronome;
extern Uint64 g_frequency;

bool init_sdl(Appstate *app);
bool init_metronome(
    Appstate *app,
    Metronome *m,
    const char *tick_path,
    const char *tock_path,
    double bpm
);
bool init_globals(Appstate *app);

void start_metronome(Metronome *m);
void stop_metronome(Metronome *m);
void update_metronome(Appstate *app, Metronome *m);

#endif
