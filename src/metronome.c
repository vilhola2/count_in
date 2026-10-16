#include "app.h"

inline void start_metronome(Metronome *m) {
    m->is_running = true;
    m->next_beat = SDL_GetPerformanceCounter();
}

inline void stop_metronome(Metronome *m) {
    m->is_running = false;
}

void update_metronome(Appstate *app, Metronome *m) {
    if (!m->is_running) return;
    Uint64 interval = (Uint64)(g_frequency * 60 / m->bpm);
    if (SDL_GetPerformanceCounter() >= m->next_beat) {
        MIX_SetTrackAudio(app->track1, m->tick);
        MIX_PlayTrack(app->track1, 0);
        m->next_beat += interval;
    }
}
