#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "Trackable.h"
#include <string>
#include "Color.h"

#pragma once
#ifndef GRAPHICS_BUFFER_H
#define GRAPHICS_BUFFER_H

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;
	//or friend void GraphicsSystem::Draw(...);
private:
	ALLEGRO_BITMAP* mBitmap;
	ALLEGRO_BITMAP* getBitmap();

public:
	GraphicsBuffer();
	GraphicsBuffer(std::string fileName);
	~GraphicsBuffer();
	int getWidth();
	int getHeight();

	void setColor(Color color);
};

#endif // !GRAPHICS_BUFFER_H
