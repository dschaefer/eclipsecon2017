#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define REC_SQRT2 0.7071067811865475
#define INTERVAL_US (1000000 / 60)

#define NOTHING_PRESSED 0
#define UP_PRESSED 1
#define DOWN_PRESSED (1 << 1)
#define LEFT_PRESSED (1 << 2)
#define RIGHT_PRESSED (1 << 3)

#ifdef __QNXNTO__
#define IMAGE_FILE "/root/assets/owl.png"
#elif __MINGW32__
#define IMAGE_FILE "C:\\Eclipse\\workspaces\\eclipsecon\\DCMakeDemo\\assets\\owl.png"
#elif __EMSCRIPTEN__
#define IMAGE_FILE "owl.png"
#include <emscripten.h>
#endif

struct context {
	SDL_Renderer *renderer;
	SDL_Rect dest;
	SDL_Texture *owl_tex;

	int active_state;

	int owl_vx;
	int owl_vy;
};

int get_owl_texture(struct context *ctx) {
	SDL_Surface *image = IMG_Load(IMAGE_FILE);
	if (!image) {
		fprintf(stderr, "IMG_LOAD: %s\n", IMG_GetError());
		return 0;
	}

	ctx->owl_tex = SDL_CreateTextureFromSurface(ctx->renderer, image);
	ctx->dest.w = image->w;
	ctx->dest.h = image->h;

	SDL_FreeSurface(image);

	return 1;
}

void process_input(struct context *ctx) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			SDL_Quit();
		}

		switch (event.key.keysym.sym) {
		case SDLK_UP:
			if (event.key.type == SDL_KEYDOWN) {
				ctx->active_state |= UP_PRESSED;
			} else if (event.key.type == SDL_KEYUP) {
				ctx->active_state &= ~UP_PRESSED;
			}
			break;
		case SDLK_DOWN:
			if (event.key.type == SDL_KEYDOWN) {
				ctx->active_state |= DOWN_PRESSED;
			} else if (event.key.type == SDL_KEYUP) {
				ctx->active_state &= ~DOWN_PRESSED;
			}
			break;
		case SDLK_LEFT:
			if (event.key.type == SDL_KEYDOWN) {
				ctx->active_state |= LEFT_PRESSED;
			} else if (event.key.type == SDL_KEYUP) {
				ctx->active_state &= ~LEFT_PRESSED;
			}
			break;
		case SDLK_RIGHT:
			if (event.key.type == SDL_KEYDOWN) {
				ctx->active_state |= RIGHT_PRESSED;
			} else if (event.key.type == SDL_KEYUP) {
				ctx->active_state &= ~RIGHT_PRESSED;
			}
			break;
		default:
			break;
		}
	}

	ctx->owl_vx = 0;
	ctx->owl_vy = 0;
	if (ctx->active_state & UP_PRESSED) {
		ctx->owl_vy = -5;
	}
	if (ctx->active_state & DOWN_PRESSED) {
		ctx->owl_vy = 5;
	}
	if (ctx->active_state & LEFT_PRESSED) {
		ctx->owl_vx = -5;
	}
	if (ctx->active_state & RIGHT_PRESSED) {
		ctx->owl_vx = 5;
	}

	if (ctx->owl_vx != 0 && ctx->owl_vy != 0) {
		ctx->owl_vx *= REC_SQRT2;
		ctx->owl_vy *= REC_SQRT2;
	}
}

void loop_handler(void *arg) {
	struct context *ctx = (struct context *) arg;

	int vx = 0;
	int vy = 0;

	process_input(ctx);

	ctx->dest.x += ctx->owl_vx;
	ctx->dest.y += ctx->owl_vy;

	SDL_RenderClear(ctx->renderer);
	SDL_RenderCopy(ctx->renderer, ctx->owl_tex, NULL, &ctx->dest);
	SDL_RenderPresent(ctx->renderer);
}

int main(int argc, char **argv) {
	SDL_Window *window;
	struct context ctx;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(600, 400, 0, &window, &ctx.renderer);
	SDL_SetRenderDrawColor(ctx.renderer, 255, 255, 255, 255);

	if (!get_owl_texture(&ctx)) {
		return 1;
	}

	ctx.active_state = NOTHING_PRESSED;
	ctx.dest.x = 200;
	ctx.dest.y = 100;
	ctx.owl_vx = 0;
	ctx.owl_vy = 0;

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(loop_handler, &ctx, -1, 1);
#else
	while (true) {
		loop_handler(&ctx);
		usleep(INTERVAL_US);
	}
#endif

	return 0;
}
