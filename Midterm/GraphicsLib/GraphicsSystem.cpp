#include "GraphicsSystem.h"
#include <allegro5\allegro_primitives.h>
#include <Timer.h>

GraphicsSystem::GraphicsSystem()
{
	mDisplay = NULL;
	mIsInit = false;
}

GraphicsSystem::GraphicsSystem(int width, int height)
{
	//mDisplay = al_create_display(width, height);
	//assert(mDisplay);
	mDisplay = NULL;
	mIsInit = false;
}

GraphicsSystem::~GraphicsSystem()
{
	if(mIsInit)
		al_destroy_display(mDisplay);

	mIsInit = false;
}

void GraphicsSystem::initGraphicsSystem(int width, int height)
{
	if (!mIsInit)
	{
		al_init_font_addon();
		al_init_ttf_addon();
		al_init_primitives_addon();
		al_init_image_addon();
		mDisplay = al_create_display(width, height);
		assert(mDisplay);
		mIsInit = true;
	}

}

void GraphicsSystem::cleanupGraphicsSystem()
{
	if(mIsInit)
		al_destroy_display(mDisplay);

	mIsInit = false;
}

int GraphicsSystem::getWidth()
{
	return al_get_display_width(mDisplay);
}

int GraphicsSystem::getHeight()
{
	return al_get_display_height(mDisplay);
}

void GraphicsSystem::flip()
{
	al_flip_display();
	//Timer* pTimer = new Timer;
	//pTimer->start();
	//pTimer->sleepUntilElapsed(5*1000.0);
	//delete pTimer;
}

void GraphicsSystem::draw(Vector2D targetLoc, Sprite sprite, float scale)
{
	//assert sets a target bitmap
	//set target bitmap is a function. Cache current bitmap to get back to old bitmap
	//make sure targetbuffer is reference to avoid destructor shenanigans. 
	al_draw_scaled_bitmap(sprite.getGraphicsBuffer()->getBitmap(), sprite.getSourceLoc().getX(), sprite.getSourceLoc().getY(),
		sprite.getWidth(), sprite.getHeight(), targetLoc.getX(), targetLoc.getY(), sprite.getWidth() * scale, sprite.getHeight() * scale, 0);
}

void GraphicsSystem::draw(GraphicsBuffer &targetBuffer, Vector2D targetLoc, Sprite sprite, float scale)
{
	//How to draw to specific buffer?
	ALLEGRO_BITMAP* cacheBitmap = targetBuffer.getBitmap();
	assert(targetBuffer.getBitmap());
	//al_set_target_bitmap(targetBuffer.getBitmap());
	al_draw_scaled_bitmap(sprite.getGraphicsBuffer()->getBitmap(), sprite.getSourceLoc().getX(), sprite.getSourceLoc().getY(),
		sprite.getWidth(), sprite.getHeight(), targetLoc.getX(), targetLoc.getY(), sprite.getWidth() * scale, sprite.getHeight() * scale, 0);

	assert(cacheBitmap);
	//al_set_target_bitmap(cacheBitmap);

}

void GraphicsSystem::drawAColor(GraphicsBuffer &targetBuffer, Color color)
{
	//ALLEGRO_BITMAP* cacheBitmap = targetBuffer.getBitmap();
	//assert(targetBuffer.getBitmap());

	ALLEGRO_COLOR aColor = al_map_rgb(color.getRed(), color.getGreen(), color.getBlue());

	al_clear_to_color(aColor);

}

void GraphicsSystem::writeText(Vector2D targetLoc, Font& font, Color color, std::string text)
{
	ALLEGRO_COLOR aColor = al_map_rgb(color.getRed(), color.getGreen(), color.getBlue());
	ALLEGRO_FONT *aFont = al_load_ttf_font(font.getFont().c_str(), font.getSize(), 0);
	//al_draw_text(cour_font, WHITE, LOC1_X, LOC1_Y, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");
	al_draw_text(aFont, aColor, targetLoc.getX(), targetLoc.getY(), 0, text.c_str());
	al_destroy_font(aFont);
}

void GraphicsSystem::writeText(GraphicsBuffer &targetBuffer, Vector2D targetLoc, Font& font, Color color, std::string text)
{
	//same as 2nd Draw
	ALLEGRO_COLOR aColor = al_map_rgb(color.getRed(), color.getGreen(), color.getBlue());
	ALLEGRO_BITMAP* cacheBitmap = targetBuffer.getBitmap();
	ALLEGRO_FONT *aFont = al_load_ttf_font(font.getFont().c_str(), font.getSize(), 0);

	al_set_target_bitmap(targetBuffer.getBitmap());

	al_draw_text(aFont, aColor, targetLoc.getX(), targetLoc.getY(), 0, text.c_str());

	al_destroy_font(aFont);

	al_set_target_bitmap(cacheBitmap);


	//assert(cacheBitmap);
}

void GraphicsSystem::saveBuffer(GraphicsBuffer &saveBuffer, std::string fileName)
{
	al_save_bitmap(fileName.c_str(), al_get_backbuffer(mDisplay));
}