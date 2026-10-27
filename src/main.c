#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} AppState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){
	if(!SDL_Init(SDL_INIT_VIDEO)){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	AppState *state = SDL_calloc(1, sizeof(AppState));
	if(!state) return SDL_APP_FAILURE;

	if(!SDL_CreateWindowAndRenderer(
				"SDL Rectangle",
				WIDTH, HEIGHT,
				0,
				&state->window,
				&state->renderer
				)){
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "SDL_CreateWindowAndRenderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	*appstate = state;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
	switch(event->type){
		case SDL_EVENT_QUIT:
			return SDL_APP_SUCCESS;
		break;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){
	AppState *state = appstate;
	SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
	SDL_RenderClear(state->renderer);

	SDL_FRect rect = { (WIDTH/2)-64, (HEIGHT/2)-64, 128, 128 };
	SDL_SetRenderDrawColor(state->renderer, 255, 0, 255, 255);
	SDL_RenderFillRect(state->renderer, &rect);

	SDL_RenderPresent(state->renderer);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){
	SDL_free(appstate);
}
