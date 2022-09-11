#include "Engine.h"

Engine::Engine(const string& mapFile, const string& scoreFile) : scoreSystem(scoreFile) {
	fileMap = NULL;
	auxMap = NULL;

	papyrosTaken = 0;
	papyrosX = papyrosY = -1;

	ifstream str(mapFile.c_str());
	loadMapFromFile(str);
}

Engine::Engine(const Engine& other) : scoreSystem(other.scoreSystem) {
	gemsTakenCount = other.gemsTakenCount;
	papyrosTaken = other.papyrosTaken;

	mapSizeX = other.mapSizeX;
	mapSizeY = other.mapSizeY;
	papyrosX = other.papyrosX;
	papyrosY = other.papyrosY;

	for (int i = 0; i < INITIAL_GEMS; i++) {
		gemsX[i] = other.gemsX[i];
		gemsY[i] = other.gemsY[i];
	}

	if (other.fileMap != NULL) {
		fileMap = new char* [mapSizeY];
		for (int i = 0; i < mapSizeY; i++) {
			fileMap[i] = new char[mapSizeX];
			for (int j = 0; j < mapSizeX; j++)
				fileMap[i][j] = other.fileMap[i][j];
		}
	}
	else {
		fileMap = NULL;
	}

	if (other.auxMap != NULL) {
		auxMap = new char* [mapSizeY];
		for (int i = 0; i < mapSizeY; i++) {
			auxMap[i] = new char[mapSizeX];
			for (int j = 0; j < mapSizeX; j++)
				auxMap[i][j] = other.auxMap[i][j];
		}
	}
	else {
		auxMap = NULL;
	}
}

Engine& Engine::operator=(const Engine& other) {
	if (this != &other) {

		if (fileMap != NULL) {
			for (int i = 0; i < mapSizeY; i++)
				delete[] fileMap[i];
			delete[] fileMap;
		}

		if (auxMap != NULL) {
			for (int i = 0; i < mapSizeY; i++)
				delete[] auxMap[i];
			delete[] auxMap;
		}

		gemsTakenCount = other.gemsTakenCount;
		papyrosTaken = other.papyrosTaken;

		mapSizeX = other.mapSizeX;
		mapSizeY = other.mapSizeY;
		papyrosX = other.papyrosX;
		papyrosY = other.papyrosY;

		for (int i = 0; i < INITIAL_GEMS; i++) {
			gemsX[i] = other.gemsX[i];
			gemsY[i] = other.gemsY[i];
		}

		if (other.fileMap != NULL) {
			fileMap = new char* [mapSizeY];
			for (int i = 0; i < mapSizeY; i++) {
				fileMap[i] = new char[mapSizeX];
				for (int j = 0; j < mapSizeX; j++)
					fileMap[i][j] = other.fileMap[i][j];
			}
		}
		else {
			fileMap = NULL;
		}

		if (other.auxMap != NULL) {
			auxMap = new char* [mapSizeY];
			for (int i = 0; i < mapSizeY; i++) {
				auxMap[i] = new char[mapSizeX];
				for (int j = 0; j < mapSizeX; j++)
					auxMap[i][j] = other.auxMap[i][j];
			}
		}
		else {
			auxMap = NULL;
		}
	}

	return *this;

}

Engine::~Engine() {
	if (fileMap != NULL) {
		for (int i = 0; i < mapSizeY; i++) {
			delete[] fileMap[i];
		}
		delete[] fileMap;
	}

	if (auxMap != NULL) {
		for (int i = 0; i < mapSizeY; i++) {
			delete[] auxMap[i];
		}
		delete[] auxMap;
	}

	vector<Moving*>::iterator it;
	for (it = movingObjects.begin(); it != movingObjects.end(); it++) {
		if (*it != NULL)
			delete* it;
	}
}

void Engine::loadMapFromFile(ifstream& file) {
	if (!file.is_open())
		throw ios_base::failure("Unable to load from map file");

	// Load vector.
	vector<string> lines;
	string temp;
	mapSizeX = mapSizeY = -1;
	while (getline(file, temp)) {
		lines.push_back(temp);

		// Check if map is square.
		if (mapSizeX == -1) {
			mapSizeX = temp.size();
		}
		else {
			if (mapSizeX != temp.size()) {
				throw invalid_argument("Map width is not consistent");
			}
		}
	}
	file.close();

	mapSizeY = lines.size();

	fileMap = new char* [mapSizeY];
	for (int i = 0; i < mapSizeY; i++) {
		fileMap[i] = new char[mapSizeX];
		for (int j = 0; j < mapSizeX; j++) {
			fileMap[i][j] = lines[i][j];
		}
	}

	auxMap = new char* [mapSizeY];
	for (int i = 0; i < mapSizeY; i++)
		auxMap[i] = new char[mapSizeX];
}
void Engine::printWelcome() {
	cout <<endl<<endl<< endl;
	cout << "     XXXX   XXXX  XXXXX  XXXXX  XXXX  XXXXX  " << endl;
	cout << "     X  X   X  X    X      X    X     X   X  " << endl;
	cout << "     XXXX   X  X    X      X    XXX   XXXXX  " << endl;
	cout << "     X      X  X    X      X    X     X X    " << endl;
	cout << "     X      XXXX    X      X    XXXX  X  X   " << endl;
	cout <<endl<<endl;
	cout << "       XXXXX   XXXXX   XX   XX    XXXXX    " << endl;
	cout << "       X       X   X   X X X X    X        " << endl;
	cout << "       X  XX   XXXXX   X  X  X    XXX      " << endl;
	cout << "       X   X   X   X   X     X    X        " << endl;
	cout << "       XXXXX   X   X   X     X    XXXX     " << endl;
	cout <<endl<<endl<< endl;
}
void Engine::printMenu() {
	cout << endl << "---------------------" << endl;
	cout << "   MENU:   " << endl;
	cout << "---------------------" << endl;
	cout << "1: Start the Game" << endl;
	cout << "2: High Scores" << endl;
	cout << "0: Exit" << endl;
	cout << "---------------------" << endl;
	cout << endl << "--GIVE A CHOISE--" << endl;
	cout << "->";
}
void Engine::ShowBoard() {
	int i, j;
	char wallChar = 219;
	for (i = 0; i < mapSizeY; i++)
		for (j = 0; j < mapSizeX; j++) {
			mvwaddch(Gm, i + 1, j + 1, (fileMap[i][j] == '*') ? wallChar : ' ');
		}
	wrefresh(Gm);
}
void Engine::showPapyros() {
	wcolor_set(Gm, CLR_PAPYROS, 0);

	int potterX = movingObjects[0]->getX();
	int potterY = movingObjects[0]->getY();

	mvwaddch(Gm, papyrosY + 1, papyrosX + 1, (papyrosX == potterX && papyrosY == potterY) ? '$' : '~');
	if (papyrosX == potterX && papyrosY == potterY) {
		papyrosX = -1;
		papyrosY = -1;
		this->papyrosTaken = 1;
	}
}

void Engine::createPapyros() {
	bool positionAccepted;
	srand(time(NULL));

	do {
		GetRandomPosition(&papyrosX, &papyrosY);
		positionAccepted = true;

		// Check distance with other objects
		vector<Moving*>::iterator it;
		for (it = movingObjects.begin(); it != movingObjects.end(); it++) {
			int x2 = (*it)->getX();
			int y2 = (*it)->getY();
			if (abs(papyrosX - x2) < 4 && abs(papyrosY - y2) < 4) {
				positionAccepted = false;
				break;
			}
		}
	} while (!positionAccepted);
}

void Engine::showGems() {

	int px = movingObjects[0]->getX();
	int py = movingObjects[0]->getY();

	for (int j = 0; j < INITIAL_GEMS; j++) {
		wcolor_set(Gm, CLR_GEMS, 0);
		if (gemsY[j] != -1 && gemsX[j] != -1)
			mvwaddch(Gm, gemsY[j] + 1, gemsX[j] + 1, (gemsX[j] == px && gemsY[j] == py) ? '$' : '@');
		if (gemsX[j] == px && gemsY[j] == py) {
			gemsX[j] = -1;
			gemsY[j] = -1;
		}
	}
	wrefresh(Gm);

}

void Engine::showObjects() {

	int px = movingObjects[0]->getX();
	int py = movingObjects[0]->getY();

	vector<Moving*>::iterator it;
	for (it = movingObjects.begin(); it != movingObjects.end(); it++) {
		int i = std::distance(movingObjects.begin(), it);
		int x = (*it)->getX();
		int y = (*it)->getY();
		char c = (*it)->getAppearance();

		wcolor_set(Gm, i + 1, 0);

		// If a monster hit the player, draw a '+'
		if (i > 0 && x == px && y == py)
			mvwaddch(Gm, y + 1, x + 1, '+');
		else
			mvwaddch(Gm, y + 1, x + 1, c);

	}
	wrefresh(Gm);
}
void Engine::hideObjects() {
	vector<Moving*>::iterator it;
	for (it = movingObjects.begin(); it != movingObjects.end(); it++) {

		// The character with which to replace the moving object.
		char replace = ' ';
		wcolor_set(Gm, CLR_REGULAR, 0);

		for (int i = 0; i < INITIAL_GEMS; i++) {
			if ((*it)->getX() == gemsX[i] && (*it)->getY() == gemsY[i]) {
				replace = '@';
				wcolor_set(Gm, CLR_GEMS, 0);
				break;
			}
		}

		if ((*it)->getX() == papyrosX && (*it)->getY() == papyrosY) {
			wcolor_set(Gm, CLR_PAPYROS, 0);
			replace = '~';
		}

		mvwaddch(Gm, (*it)->getY() + 1, (*it)->getX() + 1, replace);
	}
	wrefresh(Gm);
}

void Engine::CreateAuxMatrix(int x, int y) {
	int i, j;
	int flag;
	for (i = 0; i < mapSizeY; i++)
		for (j = 0; j < mapSizeX; j++)
			auxMap[i][j] = (fileMap[i][j] == '*') ? -1 : -2;
	auxMap[y][x] = 0;
	do {
		flag = 0;
		for (i = 1; i < mapSizeY; i++)
			for (j = 1; j < mapSizeX - 1; j++) {
				if (auxMap[i][j] == -2 && auxMap[i - 1][j] >= 0) {
					flag = 1;
					auxMap[i][j] = auxMap[i - 1][j] + 1;
				}
				if (auxMap[i][j] == -2 && auxMap[i + 1][j] >= 0) {
					flag = 1;
					auxMap[i][j] = auxMap[i + 1][j] + 1;
				}
				if (auxMap[i][j] == -2 && auxMap[i][j - 1] >= 0) {
					flag = 1;
					auxMap[i][j] = auxMap[i][j - 1] + 1;
				}
				if (auxMap[i][j] == -2 && auxMap[i][j + 1] >= 0) {
					flag = 1;
					auxMap[i][j] = auxMap[i][j + 1] + 1;
				}
			}
	} while (flag == 1);
}

void Engine::saveScore() {
	// calculate the score
	int score = 10 * gemsTakenCount + 100 * papyrosTaken;
	if (scoreSystem.isScoreGoodEnough(score)) {
		char name[NAME_SIZE + 1];
		mvaddstr(2, 1, "What is your name> ");
		refresh();
		mvgetnstr(2, 22, name, NAME_SIZE);
		mvwprintw(fn, 6, 2, "Name: %s Score: %d", name, score);
		scoreSystem << name << score;
	}
	else {
		mvwprintw(fn, 6, 2, "Score: %d", score);
	}
	refresh();
	mvwprintw(fn, 8, 2, "Press ENTER to quit.");
}

//this method creates windows
void Engine::InitScreen() {
	initscr();
	start_color();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	curs_set(0);

	init_pair(CLR_REGULAR, COLOR_WHITE, COLOR_BLACK);
	init_pair(CLR_TRAAL, COLOR_RED, COLOR_BLACK);
	init_pair(CLR_GNOME, COLOR_BLUE, COLOR_BLACK);
	init_pair(CLR_GEMS, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(CLR_BORDERS, COLOR_CYAN, COLOR_BLACK);
	init_pair(CLR_PAPYROS, COLOR_GREEN, COLOR_BLACK);
	init_pair(CLR_SAVE, COLOR_YELLOW, COLOR_BLACK);
	color_set(CLR_REGULAR, 0);
	mvprintw(1, 15, " POTTER  ESCAPE  GAME  ");

	resize_term(mapSizeY * 2, mapSizeX * 3);
	refresh();

	Gm = newwin(mapSizeY + 2, mapSizeX + 2, 3, 0);
	clearok(Gm, true);
	scrollok(Gm, false);
	wcolor_set(Gm, CLR_REGULAR, 0);
	keypad(Gm, TRUE);
	werase(Gm);
	wborder(Gm, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(Gm);

	Wd = newwin(25, 22, 3, mapSizeX + 5);
	clearok(Wd, 0);
	scrollok(Wd, false);
	wcolor_set(Wd, CLR_BORDERS, 0);
	werase(Wd);
	keypad(Wd, TRUE);
	wborder(Wd, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(Wd, 2, 2, "Total Gems : %3d", INITIAL_GEMS);
	mvwprintw(Wd, 6, 2, "Gems Left   : %3d", INITIAL_GEMS - gemsTakenCount);
	wrefresh(Wd);

	fn = newwin(12, 35, 3, mapSizeX + 20 + 10);
	clearok(fn, 0);
	scrollok(fn, false);
	wcolor_set(fn, CLR_BORDERS, 0);
	werase(fn);
	keypad(fn, TRUE);
	wborder(fn, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(fn);
	
	Pn = newwin(13, 35, 15, mapSizeX + 20 + 10);
	clearok(Pn, 0);
	scrollok(Pn, false);
	wcolor_set(Pn, CLR_BORDERS, 0);
	werase(Pn);
	keypad(Pn, TRUE);
	wborder(Pn, 0, 0, 0, 0, 0, 0, 0, 0);
	wattron(stdscr, A_BOLD | COLOR_PAIR(COLOR_RED));
	wattrset( Pn, COLOR_PAIR(1) );
	mvwprintw(Pn, 2, 3, "Potter: M -> Color: White");
	wattrset( Pn, COLOR_PAIR(3) );
	mvwprintw(Pn, 4, 3, "Gnome:  G -> Color: Blue");
	wattrset( Pn, COLOR_PAIR(2) );
	mvwprintw(Pn, 6, 3, "Traal: T -> Color: Red");
	wattrset( Pn, COLOR_PAIR(4) );
	mvwprintw(Pn, 8, 3, "Gems: @ -> Color: Purple");
	wattrset( Pn, COLOR_PAIR(6) );
	mvwprintw(Pn, 10, 3, "Papyros: ~ -> Color: Green");
	wrefresh(Pn);
}

void Engine::createObjects() {
	bool positionAccepted;
	srand(time(NULL));
	for (int i = 0; i < 3; i++) {

		// Get a valid position for the object.
		int x, y;
		do {
			GetRandomPosition(&x, &y);
			positionAccepted = true;

			// Check distance with other objects
			vector<Moving*>::iterator it;
			for (it = movingObjects.begin(); it != movingObjects.end(); it++) {
				int x2 = (*it)->getX();
				int y2 = (*it)->getY();
				if (abs(x - x2) < 4 && abs(y - y2) < 4) {
					positionAccepted = false;
					break;
				}
			}
		} while (!positionAccepted);

		// Add object to vector.
		Moving* obj = NULL;

		if (i == 0)
			obj = new Potter(auxMap, mapSizeX, mapSizeY, x, y);
		else if (i == 1)
			obj = new Traal(auxMap, mapSizeX, mapSizeY, x, y);
		else if (i == 2)
			obj = new Gnome(auxMap, mapSizeX, mapSizeY, x, y);

		if (obj != NULL)
			movingObjects.push_back(obj);


	}
}

void Engine::createGems() {
	bool positionAccepted;

	for (int i = 0; i < INITIAL_GEMS; i++) {
		do {
			GetRandomPosition(&gemsX[i], &gemsY[i]);
			positionAccepted = true;
			for (int j = 0; j < i; j++) {
				if (abs(gemsX[i] - gemsX[j]) < 4 && abs(gemsY[i] - gemsY[j]) < 4) {
					positionAccepted = false;
					break;
				}
			}
		} while (!positionAccepted);
	}
}
// is used to initialize game entities in random locations on the map
void Engine::GetRandomPosition(int* X, int* Y) {
	do {
		*X = rand() % mapSizeX;
		*Y = rand() % mapSizeY;
	} while (fileMap[*Y][*X] != ' ');
}

int Engine::getInput() {
	int ch;
	do {
		ch = getch();
	} while (ch != KEY_ESCAPE && ch != KEY_SPACE && ch != KEY_LEFT && ch != KEY_RIGHT && ch != KEY_UP && ch != KEY_DOWN);
	return ch;
}

void Engine::startGame() {
	printWelcome();
	system("PAUSE");
	system("cls");
	char selection[3];
	printMenu();
	std::cin.getline(selection, 3);

	while (strcmp(selection, "0") != 0) {
		clear();
		//e.printMenu();
		if (strcmp(selection, "1") == 0) {

			bool gameOver = false;
			bool escapePressed = false;
			bool papyrosSpawned = false;

			resetState();
			
			InitScreen();
			ShowBoard();

			createObjects();
			createGems();

			showObjects();
			showGems();

			while (papyrosTaken == 0 && !gameOver) {
				MoveDirection dir;
				int ch = getInput();
				int targetX, targetY;

				Potter* p = dynamic_cast<Potter*>(movingObjects[0]);
				if (ch == KEY_ESCAPE) {
					gameOver = true;
					escapePressed = true;
					break;
				}
				else if (ch == KEY_UP) {
					dir = UP;
					targetX = p->getX();
					targetY = p->getY() - 1;
				}
				else if (ch == KEY_DOWN) {
					dir = DOWN;
					targetX = p->getX();
					targetY = p->getY() + 1;
				}
				else if (ch == KEY_LEFT) {
					dir = LEFT;
					targetX = p->getX() - 1;
					targetY = p->getY();
				}
				else if (ch == KEY_RIGHT) {
					dir = RIGHT;
					targetX = p->getX() + 1;
					targetY = p->getY();
				}
				else {
					dir = NONE;
					targetX = p->getX();
					targetY = p->getY();
				}

				// Check if Potter will hit a wall.
				if (fileMap[targetY][targetX] == '*')
					continue;

				// Check if Potter will hit a monster.
				vector<Moving*>::iterator it;
				bool valid = true;
				for (it = movingObjects.begin() + 1; it != movingObjects.end(); it++) {
					if (targetX == (*it)->getX() && targetY == (*it)->getY()) {
						valid = false;
						break;
					}
				}
				if (!valid)
					continue;

				// Create the auxiliary map.
				CreateAuxMatrix(targetX, targetY);

				// Set the direction for Potter to move.
				p->setDirection(dir);

				hideObjects();

				// Move the characters.
				for (it = movingObjects.begin(); it != movingObjects.end(); it++) {
					(*it)->makeMove();

					// Check if a monster killed Potter
					if (it != movingObjects.begin()) {
						if (p->getX() == (*it)->getX() && p->getY() == (*it)->getY())
							gameOver = true;
					}
				}

				// Check for collision with the gems or the papyros.
				for (int j = 0; j < INITIAL_GEMS; j++) {
					if (p->getX() == gemsX[j] && p->getY() == gemsY[j]) {
						gemsTakenCount++;
						gemsX[j] = -1;
						gemsY[j] = -1;
					}
				}

				// Spawn papyros
				if (gemsTakenCount == INITIAL_GEMS && !papyrosSpawned) {
                    mvwprintw(Wd, 10, 2, " A Papyros ~ ");
                    mvwprintw(Wd, 12, 2, "has appeared!");
					papyrosSpawned = true;
					createPapyros();
					showPapyros();
				}

				// Papyros collision.
				if (p->getX() == papyrosX && p->getY() == papyrosY) {
					papyrosTaken = 1;
					papyrosX = -1;
					papyrosY = -1;
					gameOver = true;
				}

				showObjects();

				if (gemsTakenCount <= INITIAL_GEMS && !gameOver)
					UpdateDataScore();
			}

			if (gameOver) {
				char str[2];
				int score = 10 * gemsTakenCount + 100 * papyrosTaken;

				if (gemsTakenCount == INITIAL_GEMS && papyrosTaken == 1){
					wattrset(fn,COLOR_PAIR(6));
					mvwprintw(fn, 2, 2,"...YOU WIN...");
				}
				else{
					wattrset(fn,COLOR_PAIR(2) );
					mvwprintw(fn, 2, 2, "...YOU LOSE...");
				}
				wrefresh(fn);

				if (scoreSystem.isScoreGoodEnough(score)) {
					attrset(COLOR_PAIR(7) );
					mvaddstr(1, 1, "Do you want to save your Score [1:for YES/2: for NO]: ");
					echo();
					getnstr(str, 1);
					if (strcmp(str, "1") == 0) {
						wattrset(fn,COLOR_PAIR(5) );
						char name[NAME_SIZE + 1];
						mvaddstr(2, 1, "What is your name> ");
						refresh();
						mvgetnstr(2, 22, name, NAME_SIZE);
						mvwprintw(fn, 6, 2, "Name: %s Score: %d", name, score);
						scoreSystem << name << score;

						refresh();
						mvwprintw(fn, 8, 2, "Press any key to quit.");
					}
					else {
						wattrset(fn,COLOR_PAIR(5));
						mvwprintw(fn, 5, 2, "Score not Saved");
						mvwprintw(fn, 7, 2, "Press any key to quit.");
					}
					wrefresh(fn);
					
				}
				else {
					wattrset(fn,COLOR_PAIR(5) );
					mvwprintw(fn, 6, 2, "Score: %d", score);
					mvwprintw(fn, 8, 2, "Press any key to quit.");
					wrefresh(fn);
				}
				
			}
			wrefresh(Wd);
			if (!escapePressed)
				wgetch(Gm);
			clear();
			endwin();
			printMenu();
			cin.getline(selection, 3);
		}
		else if (strcmp(selection, "2") == 0) {
			cout << "Best Scores History:" << endl;
			cout << scoreSystem << endl;
			printMenu();
			cin.getline(selection, 3);
		}
		else if (strcmp(selection, "0") == 0) {
			//exit(0);
		}
		else {
			cout << "Please Follow Menu Choices" << endl;
			printMenu();
			cin.getline(selection, 3);
		}
	}
}

//update data Left Gems
void Engine::UpdateDataScore() {
	mvwprintw(Wd, 6, 2, "Gems Left   : %3d", INITIAL_GEMS - gemsTakenCount);
	wrefresh(Wd);
}

void Engine::resetState() {
	gemsTakenCount = 0;
	papyrosTaken = 0;

	// Delete moving objects
	vector<Moving*>::iterator it;
	for (it = movingObjects.begin(); it != movingObjects.end(); it++) {
		delete* it;
	}
	movingObjects.clear();
}
