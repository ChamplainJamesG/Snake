#include <allegro5\allegro.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <Trackable.h>
#pragma once
#ifndef FONT_H
#define FONT_H

class Font : public Trackable
{
private:
	//ALLEGRO_FONT * mFont;
	int mSize;
	std::string mFileName;

public:
	Font();
	Font(std::string fileName, int size);
	~Font();

	std::string getFont();
	int getSize();

};

#endif
