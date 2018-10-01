#include "Player.h"
#include "GraphicsSystem.h"

Player::Player()
{

}

Player::Player(Sprite sprite, Vector2D loc)
{
	mSprite = sprite;
	mLoc = loc;
	mDirection = RIGHT;
}

Player::~Player()
{

}

void Player::draw()
{
	GraphicsSystem::draw(mLoc, mSprite, 1.0f);
}