#include "GraphicsBuffer.h"

GraphicsBuffer::GraphicsBuffer()
{
	al_init_image_addon();
	mBitmap = NULL;
	//assert(mBitmap);
}

GraphicsBuffer::GraphicsBuffer(std::string fileName)
{
	al_init_image_addon();
	mBitmap = al_load_bitmap(fileName.c_str());
	assert(mBitmap);
}

GraphicsBuffer::~GraphicsBuffer()
{
	//delete mBitmap;
	al_destroy_bitmap(mBitmap);
}

ALLEGRO_BITMAP* GraphicsBuffer::getBitmap()
{
	return mBitmap;
}

int GraphicsBuffer::getWidth()
{
	return al_get_bitmap_width(mBitmap);
}

int GraphicsBuffer::getHeight()
{
	return al_get_bitmap_height(mBitmap);
}

/*
void GraphicsBuffer::setColor(Color color)
{
al_clear_to_color(color.getColor());
}
*/
