#include "app.h"

bool init_sdl(Appstate *app) {
    if (!SDL_SetAppMetadata("Count In", "1", "io.github.vilhola2.countin")) return false;
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) return false;
    app->window = SDL_CreateWindow("Count In", 800, 600, 0);
    MIX_Init();
    app->mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    app->track1 = MIX_CreateTrack(app->mixer);
    return true;
}

inline bool init_metronome(
    Appstate *app,
    Metronome *m,
    const char *tick_path,
    const char *tock_path,
    double bpm
) {
    if (!(m->tick = MIX_LoadAudio(app->mixer, tick_path, false))) return false;
    if (!(m->tock = MIX_LoadAudio(app->mixer, tock_path, false))) return false;
    m->bpm = bpm;
    return true;
}

bool init_globals(Appstate *app) {
    if (!init_metronome(
        app,
        &g_default_metronome,
        "resources/tick.wav",
        "resources/tock.wav",
        120.0
    )) return false;
    return true;
}
