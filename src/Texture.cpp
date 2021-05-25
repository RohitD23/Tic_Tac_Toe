#include "Texture.h"

Texture::Texture()
	:texture(nullptr), tHeight(0), tWidth(0) { }

Texture::~Texture() {
	free();
}

//Free the texture
void Texture::free() {

	if (texture != nullptr) {
		SDL_DestroyTexture(texture);

		texture = nullptr;
		tHeight = 0;
		tWidth = 0;
	}
}

void Texture::load_media_from_file(std::string path) {
	//Get rid of preexisting texture
	free();

	//Load asset surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	try {

		//Check if surface loaded
		if (loadedSurface == nullptr) 
			throw ( std::string("Enable to load \"" + path + "\" surface SDL ERROR : ") + std::string(IMG_GetError()));

		else {

			//Create texture from surface
			texture = SDL_CreateTextureFromSurface(GameWindow.Get_Renderer(), loadedSurface);

			//Check if texture loaded
			if (texture == nullptr) 
				throw ( std::string("Enable to load \"" + path + "\" texture SDL ERROR : ") + std::string(SDL_GetError()));

			else {
				//Initialize H & W with H & W of surface
				tHeight = loadedSurface->h;
				tWidth = loadedSurface->w;
			}

			//Free Surface
			SDL_FreeSurface(loadedSurface);
		}
	}

	catch (std::string& ex) {
		std::cerr << ex << std::endl;
	}
}

void Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, int wrap)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(*(GameWindow.Get_Font()), textureText.c_str(), textColor, wrap);

	try {

		//Check if texture loaded
		if (textSurface == nullptr)
			throw (std::string("Unable to render text surface! \"" + textureText + "\" SDL_ttf Error: ") +
				std::string(TTF_GetError()));

		else
		{
			//Create texture from surface pixels
			texture = SDL_CreateTextureFromSurface(GameWindow.Get_Renderer(), textSurface);
			if (texture == nullptr)
			{
				throw (std::string("Unable to create texture from rendered text! \"" + textureText + "\" SDL Error: ") +
					std::string(SDL_GetError()));
			}
			else
			{
				//Get image dimensions
				tWidth = textSurface->w;
				tHeight = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}
	}

	catch (std::string& ex) {
		std::cerr << ex << std::endl;
	}
}

void Texture::renderTexture(SDL_Rect* clip, int x, int y) {

	if (this != nullptr) {
		//Rectangle to render asset at x and y on window with W & H of asset
		SDL_Rect destination{ x, y, tWidth, tHeight };

		//To change H & W to render part of asset of Clip H & W
		if (clip != nullptr) {
			destination.w = clip->w;
			destination.h = clip->h;
		}

		//Render Asset on window
		SDL_RenderCopy(GameWindow.Get_Renderer(), texture, clip, &destination);
	}

}

void Texture::setColor(const SDL_Color& color)
{
	//Modulate texture
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}
