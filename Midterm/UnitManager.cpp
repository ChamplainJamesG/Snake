#include "UnitManager.h"

UnitManager::UnitManager()
{

}

UnitManager::~UnitManager()
{
	mUnitList.clear();
}

void UnitManager::addUnit(Unit unit)
{
	mUnitList.push_back(unit);
}

void UnitManager::deleteUnit(int loc)
{
	mUnitList.erase(mUnitList.begin() + loc);
}

Unit& UnitManager::getUnit(int loc)
{
	return mUnitList[loc];
}

void UnitManager::setAnim()
{
	getUnit(mUnitList.size() - 1).setAnimation();
}

void UnitManager::setDoAnim()
{
	if(checkAllFrozen())
		for (int i = 0; i < mUnitList.size(); i++)
		{
			mUnitList[i].setDoAnim(!mUnitList[i].getDoAnim());
		}
	else
	{
		for (int i = 0; i < mUnitList.size(); i++)
		{
			mUnitList[i].setDoAnim(false);
		}
	}
}

bool UnitManager::checkAllFrozen()
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		if (mUnitList[i].getDoAnim())
			return false;
	}

	return true;
}

void UnitManager::clear()
{
	mUnitList.clear();
}

void UnitManager::update(float dt)
{
	for (int i = 0; i < mUnitList.size(); i++)
		mUnitList[i].update(dt);
}

void UnitManager::draw(GraphicsBuffer& graphicsBuffer, bool anim)
{
	for (int i = 0; i < mUnitList.size(); i++)
		mUnitList[i].draw(graphicsBuffer);
}