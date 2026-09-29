#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

typedef struct {
    MIX_Mixer *mixer;
    MIX_Track *track1;
    SDL_Window *window;
} Appstate;
Appstate g_appstate;

typedef struct {
    MIX_Audio *tick, *tock;
} Metronome;

Metronome g_default_metronome;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    *appstate = &g_appstate; (void) argc; (void) argv;
    Appstate *app = *appstate;
    if (!SDL_SetAppMetadata("Count In", "1", "io.github.vilhola2.countin")) return SDL_APP_FAILURE;
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) return SDL_APP_FAILURE;
    app->window = SDL_CreateWindow("Count In", 800, 600, 0);
    MIX_Init();
    app->mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    g_default_metronome.tick = MIX_LoadAudio(app->mixer, "resources/tick.wav", false);
    g_default_metronome.tock = MIX_LoadAudio(app->mixer, "resources/tock.wav", false);
    app->track1 = MIX_CreateTrack(app->mixer);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    Appstate *app = appstate;
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
                case SDLK_ESCAPE:
                    return SDL_APP_SUCCESS;
                case SDLK_A:
                    MIX_SetTrackAudio(app->track1, g_default_metronome.tick);
                    MIX_PlayTrack(app->track1, 0);
                    break;
                case SDLK_B:
                    MIX_SetTrackAudio(app->track1, g_default_metronome.tock);
                    MIX_PlayTrack(app->track1, 0);
                    break;
            }
            break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    (void) appstate;
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    Appstate *app = appstate;
    if (result == SDL_APP_FAILURE) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
    }
    (void) appstate;
    (void) result;
    SDL_DestroyWindow(app->window);
    SDL_Quit();
    MIX_Quit();
}

