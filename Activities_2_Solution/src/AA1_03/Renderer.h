#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <unordered_map>
#include "Utils.h"
//SDL
class Renderer {

private:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Window* m_window = nullptr;
	std::unordered_map<std::string, SDL_Texture*> m_textureData;
	std::unordered_map<std::string, TTF_Font*> m_fontData;
	std::unordered_map<std::string, SDL_Rect*> m_rects;

public:
	Renderer();
	~Renderer();
	void Clear();
	void Render();
	void LoadFont(const Font& font);
	void LoadTexture(const std::string& id, const std::string& path);
	void LoadRect(const std::string& idRect, const RECT& rect);
	//sobrecargar ... para que devuelva
	VEC2 LoadTextureText(const std::string& fontId, Text text);
	VEC2 GetTextureSize(const std::string& id);
	void PushImage(const std::string& id, const std::string& idRect);
	void PushSprite(const std::string& id, const std::string& idRectSprite, const std::string& idRectPos);
	void PushRotatedSprite(const std::string& id, const std::string& idRectSprite, const std::string& idRectPos, float angle);
	void SetRenderDrawColor(int r, int g, int b);
	void SetRenderDrawColor(const Color& c);
};

