#include "app.h"

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    (void) argc; (void) argv;

    // Set SDL's appstate pointer
    *appstate = &g_appstate;

    // From now on we use SDL's pointer
    Appstate *app = *appstate;

    if (!init_sdl(app)) return SDL_APP_FAILURE;
    if (!init_globals(app)) return SDL_APP_FAILURE;
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
                case SDLK_M:
                    start_metronome(&g_default_metronome);
                    break;
                case SDLK_S:
                    stop_metronome(&g_default_metronome);
                    break;
            }
            break;
        case SDL_EVENT_FINGER_DOWN:
            MIX_SetTrackAudio(app->track1, g_default_metronome.tick);
            MIX_PlayTrack(app->track1, 0);
            break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    Appstate *app = appstate;
    update_metronome(app, &g_default_metronome);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    Appstate *app = appstate;
    if (result == SDL_APP_FAILURE) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
    }
    SDL_DestroyWindow(app->window);
    MIX_Quit();
    SDL_Quit();
}

