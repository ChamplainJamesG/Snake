#include "Game.h"
#include "Timer.h"
#include <fstream>

Game::Game(EventSystem *pSystem)
	:EventListener(pSystem)
{
	mSystem = NULL;
	//mUnit = new Unit();
}

Game::~Game()
{
	if (mInitG)
	{
		//mUnit->~Unit();
		//mSystem = NULL;
		//mUnit = NULL;
		//delete mUnit;
		delete mSystem;
		mInitG = false;
		delete mTranslator;
		//delete mGraphicsBuffer1;
		//delete mGraphicsBuffer2;
		//delete mGraphicsBuffer3;
		//delete mUnit;
	}
}

void Game::init(float width, float height, ifstream& in)
{
	if (!mInitG)
	{
		//int inInt;
		//in.open("INIT.init");
		EventSystem::initInstance();
		Sprite smurfSpriteArray[16];
		Sprite deanSpriteArray[16];
		int loc = 0;
		float startSpeed;
		in >> startSpeed;
		mPlayerManager = PlayerManager(startSpeed);

		in >> mPUSpawnRate;

		//GraphicsBuffer* gBuffer = new GraphicsBuffer((FILE_PATH + WOODS_NAME).c_str());

		//in.ignore('\n');
		in.clear();
		mInitG = true;
		mSystem = new System();
		mSystem->init(width, height);

		mTranslator = new InputTranslator(EventSystem::getInstance());

		//GraphicsBuffer mGraphicsBuffer1((FILE_PATH + WOODS_NAME).c_str());



		//mGBManager.addGraphicsBuffer("Woods", new GraphicsBuffer((FILE_PATH + WOODS_NAME).c_str()));
		//mGBManager.addGraphicsBuffer("SmurfSprite", new GraphicsBuffer((FILE_PATH + SMURF_SPRITES).c_str()));
		//mGBManager.addGraphicsBuffer("DeanSprite", new GraphicsBuffer((FILE_PATH + DEAN_SPRITES).c_str()));
		mGBManager.addGraphicsBuffer("SquareSprite", new GraphicsBuffer(SQUARE_NAME.c_str()));
		string imgString;
		getline(in, imgString, '\n');
		getline(in, imgString, '\n');
		mGBManager.addGraphicsBuffer("PlayerSprite", new GraphicsBuffer(imgString));
		getline(in, imgString, '\n');
		mGBManager.addGraphicsBuffer("Player2Sprite", new GraphicsBuffer(imgString));
		getline(in, imgString, '\n');
		mGBManager.addGraphicsBuffer("BadSquare", new GraphicsBuffer(imgString));
		getline(in, imgString, '\n');
		mGBManager.addGraphicsBuffer("Food", new GraphicsBuffer(imgString));
		//mGBManager.addGraphicsBuffer("Player2Sprite", new GraphicsBuffer(imgString));

		//mGBManager.addGraphicsBuffer("Player2Sprite", new GraphicsBuffer(imgString));
		getline(in, imgString, '\n');
		mGBManager.addGraphicsBuffer("FoodPU", new GraphicsBuffer(imgString));
		getline(in, imgString, '\n');
		mGBManager.addGraphicsBuffer("PointPU", new GraphicsBuffer(imgString));
		getline(in, imgString, '\n');
		mGBManager.addGraphicsBuffer("ShrinkPU", new GraphicsBuffer(imgString));

		//float smurfWOffset = mGBManager.getGraphicsBuffer("SmurfSprite")->getWidth() / 4;
		//float smurfHOffset = mGBManager.getGraphicsBuffer("SmurfSprite")->getHeight() / 4;

		//Sprite newSprite = Sprite(*mGBManager.getGraphicsBuffer("SquareSprite"), 0, 0);
		Sprite newSprite = Sprite(*mGBManager.getGraphicsBuffer("SquareSprite"), Vector2D(0, 0), mGBManager.getGraphicsBuffer("SquareSprite")->getWidth(), mGBManager.getGraphicsBuffer("SquareSprite")->getHeight());
		Sprite playerSprite = Sprite(*mGBManager.getGraphicsBuffer("PlayerSprite"), Vector2D(0, 0), mGBManager.getGraphicsBuffer("PlayerSprite")->getWidth(), mGBManager.getGraphicsBuffer("PlayerSprite")->getHeight());
		Sprite badSquareSprite = Sprite(*mGBManager.getGraphicsBuffer("BadSquare"), Vector2D(0, 0), mGBManager.getGraphicsBuffer("BadSquare")->getWidth(), mGBManager.getGraphicsBuffer("BadSquare")->getHeight());
		Sprite foodSprite = Sprite(*mGBManager.getGraphicsBuffer("Food"), Vector2D(0, 0), mGBManager.getGraphicsBuffer("Food")->getWidth(), mGBManager.getGraphicsBuffer("Food")->getHeight());
		Sprite player2Sprite = Sprite(*mGBManager.getGraphicsBuffer("Player2Sprite"), Vector2D(0, 0), mGBManager.getGraphicsBuffer("PlayerSprite")->getWidth(), mGBManager.getGraphicsBuffer("PlayerSprite")->getHeight());
		Sprite foodPUSprite = Sprite(*mGBManager.getGraphicsBuffer("FoodPU"), Vector2D(0, 0), mGBManager.getGraphicsBuffer("FoodPU")->getWidth(), mGBManager.getGraphicsBuffer("FoodPU")->getHeight());
		Sprite pointPUSprite = Sprite(*mGBManager.getGraphicsBuffer("PointPU"), Vector2D(0, 0), mGBManager.getGraphicsBuffer("PointPU")->getWidth(), mGBManager.getGraphicsBuffer("PointPU")->getHeight());
		Sprite shrinkPUSprite = Sprite(*mGBManager.getGraphicsBuffer("ShrinkPU"), Vector2D(0, 0), mGBManager.getGraphicsBuffer("ShrinkPU")->getWidth(), mGBManager.getGraphicsBuffer("ShrinkPU")->getHeight());

		Animation foodAnim;
		Animation pointAnim;
		Animation bigFoodAnim;
		Animation shrinkAnim;

		for (int i = 0; i < 3; i++)
		{
			foodAnim.addSprite(Sprite(*mGBManager.getGraphicsBuffer("Food"), Vector2D((mGBManager.getGraphicsBuffer("Food")->getWidth() / 3) * i, 0), mGBManager.getGraphicsBuffer("Food")->getWidth() / 3, mGBManager.getGraphicsBuffer("Food")->getHeight()));
		}

		for (int i = 0; i < 3; i++)
		{
			pointAnim.addSprite(Sprite(*mGBManager.getGraphicsBuffer("PointPU"), Vector2D((mGBManager.getGraphicsBuffer("PointPU")->getWidth() / 3) * i, 0), mGBManager.getGraphicsBuffer("PointPU")->getWidth() / 3, mGBManager.getGraphicsBuffer("PointPU")->getHeight()));
		}		
		
		for (int i = 0; i < 3; i++)
		{
			bigFoodAnim.addSprite(Sprite(*mGBManager.getGraphicsBuffer("FoodPU"), Vector2D((mGBManager.getGraphicsBuffer("FoodPU")->getWidth() / 3) * i, 0), mGBManager.getGraphicsBuffer("FoodPU")->getWidth() / 3, mGBManager.getGraphicsBuffer("FoodPU")->getHeight()));
		}		
		
		for (int i = 0; i < 3; i++)
		{
			shrinkAnim.addSprite(Sprite(*mGBManager.getGraphicsBuffer("ShrinkPU"), Vector2D((mGBManager.getGraphicsBuffer("ShrinkPU")->getWidth() / 3) * i, 0), mGBManager.getGraphicsBuffer("ShrinkPU")->getWidth() / 3, mGBManager.getGraphicsBuffer("ShrinkPU")->getHeight()));
		}

		//mLevel = Level(8, 6, newSprite, badSquareSprite, foodSprite);

		//Player newPlayer = Player(mPlayerTemplate, mLevel.getSquare(1, 1).getPos());
		mPlayerTemplate = Player(playerSprite, /*mLevel.getSquare(0, 0).getPos()*/ Vector2D(1000, 1000));
		mPlayerTemplate.setX(0);
		mPlayerTemplate.setY(0);
		mPlayerManager.addPlayer(mPlayerTemplate);
		mPlayerManager.getPlayer(0).setX(1);
		mPlayerManager.getPlayer(0).setY(1);
		mPlayerTemplate.setSprite(player2Sprite);

		/*
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				smurfSpriteArray[loc] = Sprite(*mGBManager.getGraphicsBuffer("SmurfSprite"), Vector2D(smurfWOffset * j, smurfHOffset * i), smurfWOffset, smurfHOffset);
				loc++;
			}
		}

		loc = 0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				deanSpriteArray[loc] = Sprite(*mGBManager.getGraphicsBuffer("DeanSprite"), Vector2D(smurfWOffset * j, smurfHOffset * i), smurfWOffset, smurfHOffset);
				loc++;
			}
		}

		addSprites(smurfSpriteArray, 16, true);
		addSprites(deanSpriteArray, 16, false);
		*/
		//EventSystem::getInstance().addListener(ADD_EVENT, this);
		EventSystem::getInstance()->addListener(ADD_EVENT, this);
		EventSystem::getInstance()->addListener(DELETE_EVENT, this);
		EventSystem::getInstance()->addListener(FREEZE_EVENT, this);
		EventSystem::getInstance()->addListener(CHANGE_EVENT, this);
		EventSystem::getInstance()->addListener(QUIT_EVENT, this);
		EventSystem::getInstance()->addListener(MOVE_UP, this);
		EventSystem::getInstance()->addListener(MOVE_LEFT, this);
		EventSystem::getInstance()->addListener(MOVE_DOWN, this);
		EventSystem::getInstance()->addListener(MOVE_RIGHT, this);
		EventSystem::getInstance()->addListener(TEST_MAKE_PLAYER, this);
		EventSystem::getInstance()->addListener(RESET, this);
		EventSystem::getInstance()->addListener(START_LEVEL, this);
		EventSystem::getInstance()->addListener(START_GAME, this);
		EventSystem::getInstance()->addListener(EXIT, this);
		EventSystem::getInstance()->addListener(FOOD_PU, this);
		EventSystem::getInstance()->addListener(POINT_PU, this);
		EventSystem::getInstance()->addListener(SHRINK_PU, this);


		assert(this);

		EventSystem::getInstance()->addListener(AL_ADD_EVENT, mTranslator);
		EventSystem::getInstance()->addListener(AL_DELETE_EVENT, mTranslator);
		EventSystem::getInstance()->addListener(AL_FREEZE_EVENT, mTranslator);
		EventSystem::getInstance()->addListener(AL_CHANGE_EVENT, mTranslator);
		EventSystem::getInstance()->addListener(AL_QUIT_EVENT, mTranslator);

		Level initLevel = Level(8, 6, newSprite, badSquareSprite, foodSprite, foodPUSprite, pointPUSprite, shrinkPUSprite, foodAnim, bigFoodAnim, pointAnim, shrinkAnim);
		in >> initLevel;
		mLevelManager.addLevel(initLevel);
		in >> initLevel;
		mLevelManager.addLevel(initLevel);
		in >> initLevel;
		mLevelManager.addLevel(initLevel);

		mCurLevel = 0;
		mLevel = mLevelManager.getLevel(mCurLevel);

		mLevel.spawnFood(mPlayerManager);

		in.close();
	}

}

void Game::initBuffers(std::string fileName1, std::string fileName2, std::string fileName3)
{
	//mGraphicsBuffer1 = new GraphicsBuffer(fileName1);
	//mGraphicsBuffer2 = new GraphicsBuffer(fileName2);
	//mGraphicsBuffer3 = new GraphicsBuffer(fileName3);
}

void Game::addSprites(Sprite sprite[], int count, bool anim)
{
	//Sprite *ptr = sprite;
	for (int i = 0; i < count; i++)
	{
		if (anim)
			mUnit.addAnim(sprite[i], anim);
		else
			mUnit.addAnim(sprite[i], anim);
	}
}

void Game::createUnit(Unit unit)
{
	mUnitManager.addUnit(unit);
}

void Game::makeUnit()
{
	Unit unit = mUnit;
	mUnit.setSourceLoc(Vector2D(mSystem->getMouseLoc().getX() - mGBManager.getGraphicsBuffer("SmurfSprite")->getWidth() / 8, mSystem->getMouseLoc().getY() - mGBManager.getGraphicsBuffer("SmurfSprite")->getHeight() / 8));
	createUnit(unit);
}

void Game::removeUnit()
{
	for (int i = 0; i < mUnitManager.getSize(); i++)
	{
		if (compareLoc(mUnitManager.getUnit(i)))
		{
			mUnitManager.deleteUnit(i);
		}
	}
}

bool Game::compareLoc(Unit unit)
{
	if (mSystem->getMouseLoc().getX() > unit.getLocation().getX() && mSystem->getMouseLoc().getX() < unit.getLocation().getX() + mGBManager.getGraphicsBuffer("SmurfSprite")->getWidth() / 4
		&& mSystem->getMouseLoc().getY() > unit.getLocation().getY() && mSystem->getMouseLoc().getY() < unit.getLocation().getY() + mGBManager.getGraphicsBuffer("SmurfSprite")->getHeight() / 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::cleanup()
{
	if (mInitG)
	{
		//mUnit->~Unit();
		//mSystem = NULL;
		//mUnit = NULL;
		//delete mUnit;
		delete mSystem;
		mGBManager.clear();
		mInitG = false;
		delete mGBManager.getGraphicsBuffer("Woods");
		delete mGBManager.getGraphicsBuffer("SmurfSprites");
		delete mGBManager.getGraphicsBuffer("DeanSprites");
		delete mGBManager.getGraphicsBuffer("PlayerSprite");
		delete mGBManager.getGraphicsBuffer("Player2Sprite");
		delete mGBManager.getGraphicsBuffer("BadSquare");
		delete mGBManager.getGraphicsBuffer("Food");
		delete mGBManager.getGraphicsBuffer("FoodPU");
		delete mGBManager.getGraphicsBuffer("PointPU");
		delete mGBManager.getGraphicsBuffer("ShrinkPU");
		delete mGBManager.getGraphicsBuffer("SquareSprite");

		delete mTranslator;
		EventSystem::cleanupInstance();

		//delete mGraphicsBuffer1;
		//delete mGraphicsBuffer2;
		//delete mGraphicsBuffer3;
		//delete mUnit;
	}
}

void Game::doLoop()
{
	Timer timer;
	//worry about timing inside here. 
	//Sprite stepsSprite(mGraphicsBuffer1, 0, 0);
	//Sprite stepsSprite(*mGBManager.getGraphicsBuffer("Woods"), 0, 0);
	bool anim = true;
	//bool done = false;
	bool leftClick = false;
	bool rightClick = false;
	//bool doAnim = true;
	//bool firstFlip = false;
	mPlayerManager.setMaxTime(mPlayerManager.getMaxTime() - mLevel.getSubFactor());
	while (!mStartGame)
	{
		timer.start();
		GraphicsSystem::drawAColor(*mGBManager.getGraphicsBuffer("SquareSprite"), Color(255, 255, 255));
		GraphicsSystem::writeText(Vector2D(200, 200), mSystem->getFont(), Color(255, 70, 100), "A day in the life of Gary Oldmyer");
		GraphicsSystem::writeText(Vector2D(200, 250), mSystem->getFont(), Color(255, 70, 100), "Press SPACE to start");
		mSystem->update();
		mSystem->flip();
		timer.sleepUntilElapsed(16.67);
	}
	mPlayerManager.getPlayer(0).setDir(RIGHT);
	while (!mDoneLoop)
	{
		timer.start();
		mSystem->update();

		if (mStartLevel)
		{
			timer.start();
			//input

			checkEnd();


			//update
			//render
			//mUnit.setSourceLoc(mSystem->getMouseState(mUnit.getOrigLoc()));
			//mSystem->getMouseState(Vector2D(0, 0), leftClick, rightClick);
			/*
			if (leftClick)
			{
			makeUnit();
			leftClick = false;
			}

			if (rightClick)
			{
			removeUnit();
			rightClick = false;
			}
			*/

			//mUnit.update(timer.getElapsedTime(), anim);

			mUnitManager.update(timer.getElapsedTime());
			mPlayerManager.update(timer.getElapsedTime(), mLevel);

			mLevel.update(timer.getElapsedTime());
			//GraphicsSystem::draw(*mGBManager.getGraphicsBuffer("Woods"), Vector2D(0, 0), stepsSprite, .5);
			
			//mUnitManager.draw(*mGBManager.getGraphicsBuffer("SmurfSprite"), anim);


			//firstFlip = true;


			checkLevel();
			if (rollSpawn())
				mPowerUpSpawn = true;

		}

		mLevel.drawLevel(mGBManager.getGraphicsBuffer("SquareSprite"));

		//mUnit.draw(*mGBManager.getGraphicsBuffer("SmurfSprite"), anim);
		mPlayerManager.draw();
		
		if (!mStartLevel)
		{
			GraphicsSystem::writeText(Vector2D(200, 450), mSystem->getFont(), Color(50, 20, 255), "Press SPACE to start");
		}

		timer.sleepUntilElapsed(16.67);
		std::cout << timer.getElapsedTime() << std::endl;
		updateHUD(timer.getElapsedTime());

		mSystem->flip();

		//std::cout << timer.getElapsedTime() << std::endl;

	}

	if(!mWinGame)
		while (!mEndGame)
		{
			timer.start();
			GraphicsSystem::writeText(Vector2D(100, 350), mSystem->getFont(), Color(50, 20, 255), "Gary Oldmyer has died.");
			GraphicsSystem::writeText(Vector2D(100, 400), mSystem->getFont(), Color(50, 20, 255), "It was inevitable.");
			GraphicsSystem::writeText(Vector2D(100, 450), mSystem->getFont(), Color(50, 20, 255), "Press ESC to exit");
			mSystem->update();
			mSystem->flip();
			timer.sleepUntilElapsed(16.67);
		}

	else
		while (!mEndGame)
		{
			timer.start();
			GraphicsSystem::writeText(Vector2D(100, 350), mSystem->getFont(), Color(50, 20, 255), "Gary Oldmyer has won.");
			GraphicsSystem::writeText(Vector2D(100, 400), mSystem->getFont(), Color(50, 20, 255), "Good job.");
			GraphicsSystem::writeText(Vector2D(100, 450), mSystem->getFont(), Color(50, 20, 255), "Press ESC to exit.");
			mSystem->update();
			mSystem->flip();
			timer.sleepUntilElapsed(16.67);
		}

	mSystem->cleanup();

}

void Game::changePlayerDir(DIRECTION dir)
{
	mPlayerManager.getPlayer(0).setDir(dir);
}

void Game::handleEvent(const Event &theEvent)
{
	//cout << endl << "ExampleListener#" << mID << endl;
	//cout << "\t" << theEvent.getEventName() << " Received";
	std::cout << "Firing game event" << std::endl;
	if (theEvent.getType() == ADD_EVENT)
	{
		//const MoveEvent& moveEvent = static_cast<const MoveEvent&>(theEvent);
		//add a sprite
		makeUnit();
	}

	if (theEvent.getType() == DELETE_EVENT)
	{
		//delete a sprite
		removeUnit();
	}

	if (theEvent.getType() == FREEZE_EVENT)
	{
		mUnitManager.setDoAnim();
	}

	if (theEvent.getType() == QUIT_EVENT)
	{
		mDoneLoop = !mDoneLoop;
	}

	if (theEvent.getType() == CHANGE_EVENT)
	{
		mUnitManager.setAnim();
	}

	if (theEvent.getType() == MOVE_UP)
	{
		changePlayerDir(UP);
	}

	if (theEvent.getType() == MOVE_LEFT)
	{
		changePlayerDir(LEFT);
	}

	if (theEvent.getType() == MOVE_DOWN)
	{
		changePlayerDir(DOWN);
	}

	if (theEvent.getType() == MOVE_RIGHT)
	{
		changePlayerDir(RIGHT);
	}

	if (theEvent.getType() == TEST_MAKE_PLAYER)
	{
		addPlayer();
		mLevel.getSquare(mPlayerManager.getPlayer(0).getX(), mPlayerManager.getPlayer(0).getY()).setHasFood(false);
		mLevel.spawnFood(mPlayerManager);
		mScore += 1;
	}

	if (theEvent.getType() == FOOD_PU)
	{
		mLevel.getSquare(mPlayerManager.getPlayer(0).getX(), mPlayerManager.getPlayer(0).getY()).setHasFoodPU(false);
		addPlayer();
		addPlayer();
		mScore += 2;
		mPowerUpSpawn = false;

	}

	if (theEvent.getType() == POINT_PU)
	{
		mLevel.getSquare(mPlayerManager.getPlayer(0).getX(), mPlayerManager.getPlayer(0).getY()).setHasPointPU(false);
		mScore += 1;
		mPowerUpSpawn = false;

	}

	if (theEvent.getType() == SHRINK_PU)
	{
		mLevel.getSquare(mPlayerManager.getPlayer(0).getX(), mPlayerManager.getPlayer(0).getY()).setShrinkPU(false);
		mPowerUpSpawn = false;
		if (mPlayerManager.getNumPlayer() > 3)
		{
			mPlayerManager.removeOnePlayer();
		}

	}

	if (theEvent.getType() == RESET)
	{
		mCurLevel++;
		loadNextLevel(mCurLevel);
	}

	if (theEvent.getType() == START_LEVEL)
	{
		if(mStartGame)
			mStartLevel = true;
	}

	if (theEvent.getType() == START_GAME)
	{
		mStartGame = true;
	}

	if (theEvent.getType() == EXIT)
	{
		mEndGame = true;
	}
}

void Game::addPlayer()
{
	Player newPlayer = mPlayerTemplate;
	mPlayerManager.addPlayer(newPlayer);
}

void Game::checkEnd()
{
	if (mPlayerManager.getDead())
		EventSystem::getInstance()->fireEvent(QUIT_EVENT);
}

void Game::checkLevel()
{
	if (mScore > mLevelManager.getLevel(mCurLevel).getScoreToWin())
	{
		EventSystem::getInstance()->fireEvent(RESET);
	}
}

void Game::updateHUD(float dt)
{
	float fps = dt * 3.59;
	roundf(fps);

	mSystem->doHud(fps, mScore);
}

void Game::loadNextLevel(int level)
{
	if (mCurLevel > 2)
	{
		mWinGame = true;
		mDoneLoop = true;
		return;
	}
	mLevel = mLevelManager.getLevel(level);
	mPlayerManager.resetPlayer();
	mLevel.spawnFood(mPlayerManager);
	mPlayerManager.setMaxTime(mPlayerManager.getMaxTime() - mLevel.getSubFactor());
	EventSystem::getInstance()->fireEvent(MOVE_RIGHT);
	mStartLevel = false;


}

bool Game::rollSpawn()
{
	int random = rand() % mPUSpawnRate;
	if (random <= 1)
	{
		mLevel.spawnPowerup(mPlayerManager);
		return true;
	}

	return false;
}
/*
input system does interface events
i.e mouse moves, return new vector2d

add game as a listener to event system

example event flow
input system fires event for onclick()
event system deals handles that event, which goes into inputtranslator
input translator recieves that input, which then fires a new event, to create a unit that goes back to event system
EventSystem calls handleEvent based on that create unit event, which then calls handleevent again,
which then goes into game, and creates a new unit
*/