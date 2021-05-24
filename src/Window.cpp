#include "Window.h"

//Initialize Variables
Window::Window()
	:window(nullptr), renderer(nullptr), font(nullptr), wHeight(0), wWidth(0), wMinimized(false) { }

void Window::free() {
	if (window != nullptr) {

		TTF_CloseFont(font);
		font = NULL;

		SDL_DestroyRenderer(renderer);
		renderer = nullptr;

		SDL_DestroyWindow(window);
		window = nullptr;

		wHeight = 0;
		wWidth = 0;
		wMinimized = false;
	}
}

void Window::init() {

	try {
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
			throw (std::string("Enable to initialize SDL, SDL_ERROR : ") + std::string(SDL_GetError()));

		else {

			//Create window
			window = SDL_CreateWindow("TIC TAC TOE", SDL_WINDOWPOS_UNDEFINED, SCREEN_Y_POS,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

			//Throw error if window not created
			if (window == nullptr)
				throw (std::string("Enable to create window, SDL_ERROR : ") + std::string(SDL_GetError()));
			
			else {

				//Initialize h & w variables
				wHeight = SCREEN_HEIGHT;
				wWidth = SCREEN_WIDTH;

				//Create renderer for our window
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

				//Throw error if renderer not created
				if (renderer == nullptr)
					throw (std::string("Enable to create renderer, SDL_ERROR : ") + std::string(SDL_GetError()));
				
				else {

					//Set color of renderer
					SDL_SetRenderDrawColor(renderer, 15, 78, 99, 255);

					//Initilaize png flag
					int imgFlag = 2;

					//Initialize SDL Image
					if (!(IMG_Init(imgFlag) & imgFlag)) 
						throw (std::string("Failed to initialize IMG : ") + std::string(IMG_GetError()));

					//Initilaize SDL Font
					if (TTF_Init() == -1)
						throw (std::string("SDL_ttf could not initialize! SDL_ttf Error: ") + std::string(TTF_GetError()));

					//Initialize SDL_mixer
					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
						throw (std::string("SDL_mixer could not initialize! SDL_mixer Error: ") + std::string(Mix_GetError()));
	
				}
			}

		}
	}

	catch (std::string& ex) {
		std::cerr << ex << std::endl;
	}
}

void Window::handle_event(SDL_Event* e) {

	if (e->type == SDL_WINDOWEVENT) {

		switch (e->window.event) {

			//Window size is changed
		case SDL_WINDOWEVENT_RESIZED:
			wWidth = e->window.data1;
			wHeight = e->window.data2;
			SDL_RenderPresent(renderer);
			break;

			//Render after window size is changed
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(renderer);
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			wMinimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			wMinimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			wMinimized = false;
			break;
		}
	}
}


