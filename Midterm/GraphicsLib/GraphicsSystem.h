#include <allegro5/allegro.h>
#include "Trackable.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"
#pragma once
#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

class GraphicsSystem : public Trackable
{
private:
	ALLEGRO_DISPLAY* mDisplay;
	bool mIsInit;

public:
	GraphicsSystem();
	GraphicsSystem(int width, int height);
	
	~GraphicsSystem();

	void initGraphicsSystem(int width, int height);
	void cleanupGraphicsSystem();

	int getWidth();
	int getHeight();

	void flip();

	static void draw(Vector2D targetLoc, Sprite sprite, float scale = 1.0);
	static void draw(GraphicsBuffer &targetBuffer, Vector2D targetLoc, Sprite sprite, float scale = 1.0);
	static void drawAColor(GraphicsBuffer &targetBuffer, Color color);
	static void writeText(Vector2D targetLoc, Font& font, Color color, std::string text);
	static void writeText(GraphicsBuffer &targetBuffer, Vector2D targetLoc, Font &font, Color color, std::string text);
	void saveBuffer(GraphicsBuffer &saveBuffer, std::string fileName);

};

#endif // !GRAPHICS_SYSTEM_H
