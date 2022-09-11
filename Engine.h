#ifndef ENGINE_H
#define ENGINE_H

#define INITIAL_GEMS 10

// Keys
#define KEY_SPACE 32
#define KEY_ESCAPE 27

// Color pair ids
#define CLR_REGULAR 1
#define CLR_TRAAL 2
#define CLR_GNOME 3
#define CLR_GEMS 4
#define CLR_BORDERS 5
#define CLR_PAPYROS 6
#define CLR_SAVE 7

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "curses.h"

#include "Moving.h"
#include "HiScore.h"
#include "Potter.h"
#include "Traal.h"
#include "Gnome.h"

using namespace std;

class Engine {
private:

	WINDOW* Gm;
	WINDOW* Wd;
	WINDOW* fn;
	WINDOW* Pn;

	HiScore scoreSystem;

	vector<Moving*> movingObjects;

	int gemsTakenCount;
	int papyrosTaken;
	int mapSizeX, mapSizeY;
	char** fileMap;
	char** auxMap; // The auxiliary matrix is used to find the shortest route to a target position.

	int gemsX[INITIAL_GEMS];
	int gemsY[INITIAL_GEMS];
	int papyrosX, papyrosY;

	void loadMapFromFile(ifstream&);
	
	void printWelcome();
	void printMenu();
	void InitScreen();
	void ShowBoard();

	void createPapyros();
	void showPapyros();

	void createGems();
	void showGems();

	void createObjects();
	void showObjects();
	void hideObjects();

	void GetRandomPosition(int*, int*);
	int getInput();

	void saveScore();

	void UpdateDataScore();

	void resetState();

public:

	void CreateAuxMatrix(int, int);
	void startGame();

	Engine(const string&, const string&);
	Engine(const Engine&);
	~Engine();

	Engine& operator=(const Engine&);
};

#endif
