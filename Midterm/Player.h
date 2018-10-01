#include "Trackable.h"
#include <vector>
#include "Sprite.h"
#include "Vector2D.h"
#pragma once
#ifndef PLAYER_H
#define PLAYER_H

const enum DIRECTION { UP = 0, LEFT, RIGHT, DOWN, NUM_DIRECTION };

class Player : public Trackable
{
public:
	Player();
	Player(Sprite sprite, Vector2D loc);
	~Player();

	Vector2D getPlayerLocation() { return mLoc; };
	Sprite getPlayerSprite() { return mSprite; };
	DIRECTION getDirection() { return mDirection; };
	int getX() { return mX; };
	int getY() { return mY; };

	void setLoc(Vector2D loc) { mLoc = loc; };
	void setDir(DIRECTION dir) { mDirection = dir; };
	void setX(int x) { mX = x; };
	void setY(int y) { mY = y; };
	void setSprite(Sprite sprite) { mSprite = sprite; };

	void draw();
private:
	DIRECTION mDirection;
	Sprite mSprite;
	Vector2D mLoc;
	int mX,  mY;
};

#endif // !PLAYER_H
