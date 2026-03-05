#include <random>
#include <iostream>
#include <sstream>
#include <Windows.h>

#include "Map.hpp"

#undef near

void Map::create_map() {

	std::random_device rand;
	std::uniform_int_distribution<> distr(0,1);
	int random = distr(rand);

	for (auto& row : map) {
		for (auto &square: row){
			random = distr(rand);
			switch (random)
			{
			case 0: square = bush;
				break;
			case 1: square = field;
				break;
			//case 2: square = tree;
				//break;
			//case 3: square = '^';
				//break;
			default:
				break;
			}
		}
	}
}

int Map::near(int x, int y) {
	int count{};

	for (int h = y-1; h < 2+y; h++)
		for (int w = x - 1; w < 2 + x; w++)
			if (!(w == x && h == y))
				count += map[h][w];

	return count;
}

void Map::transform() {
		for (int h = 2; h < HEIGHT - 1; h++){
			for (int w = 2; w < WIDTH - 1; w++) {
				int count = near(w, h);

				if (map[h][w] == bush && count >= 6) map[h][w] = field;
				if (map[h][w] == field && count <= 3)  map[h][w] = bush;
				if ((map[h][w] == bush || map[h][w] == field) && count == 4) map[h][w] = tree;
			}
		}
}

void  Map::spawn_mobs() {

	std::random_device rand;
	std::uniform_int_distribution<> distr(0, 100);
	int random = distr(rand);

	//<=
	for (int i = 1; i < HEIGHT; i++)
		for (int j = 1; j < WIDTH; j++) {
			if (map[i][j] == field) {
				random = distr(rand);

				if (random <= 20)
					mobs.at(i).at(j) = std::make_unique<Goblin>(i,j);

				else
					mobs.at(i).at(j) = nullptr;
			}

			else
				mobs.at(i).at(j) = nullptr;
		}

}

void Map::display(const Player& p) const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {

			if (i == 0 && j == 0)
				std::cout << ' ';

			else if (i == 0 && j != 0) {
				if (j % 2 == 0)
					SetConsoleTextAttribute(hConsole, 1);

				else
					SetConsoleTextAttribute(hConsole, 7);

				if (j < 10)
					std::cout << j << ' ';

				else 
					std::cout << j;
			}

			else if (j == 0 && i != 0){
				if (i < 10)
					std::cout << i << ' ';

				else
					std::cout << i;
			}

			else if (p.get_x() == j && p.get_y() == i)
				std::cout << '@' << ' ';
			
			else
			{
				switch (map[i][j]) {
				case bush: std::cout << c_bush << ' ';
					break;

				case field: std::cout << c_field << ' ' ;
					break;

				case tree: std::cout << c_tree << ' ';
					break;
				}
			}
		}
		std::cout << '\n';
	}
}

void Map::display2() const {

	for (auto& row : map)
	{
		for (auto& column : row)
			std::cout << column;
		std::cout << std::endl;
	}
	std::cout << "\n";
}

void Map::display_mobs() const {
	for (int i = 1; i < HEIGHT; i++) {
		for (int j = 1; j < WIDTH; j++) {

			if (mobs[i][j] == nullptr)
				std::cout << '_';
			else
				std::cout << 'M';
		}
		std::cout << std::endl;
	}
}

//getters
std::unique_ptr<Entity>& Map::mobs_cord(int xPos, int yPos) {
	return mobs[yPos][xPos];
}

int Map::get_map_X_max() const {
	return WIDTH;
}

int Map::get_map_Y_max() const {
	return HEIGHT;
}

int Map::get_map_at_cord(int x, int y) const {
	return map[x][y];
}

std::unique_ptr<Entity>& Map::get_mob_from_cord(int x, int y) {
	return mobs[x][y];
}

std::stringstream Map::get_mob_stringstream() const {
	std::stringstream ss;
	ss << "Mobs: {\n";

	for (auto& row : mobs) {
		for (auto& mob : row) {
			if (mob != nullptr) {
				ss << mob->get_entity_stream().str();
			}
		}
	}
	ss << "};\n";

	return ss;
}

std::stringstream Map::get_map_stringstream() const {
	std::stringstream ss;
	ss << "Map: {\n";

	for (auto& row : map) {
		for (auto& cord : row) {
			ss << cord;
		}
		ss << '\n';
	}
	ss << "}\n";

	return ss;
}

//setters
void Map::set_map_at_cord(int x, int y, int Tex) {
	map[x][y] = Tex;
}


//Mobs enum
enum Mob {
	OptionInvalid,
	goblin
};

Mob resolveOption(std::string input) {
	if (input == "Goblin") return goblin;

	return OptionInvalid;
}

void Map::set_mob_at_cord(std::string name_tmp, int level_tmp, int x_tmp, int y_tmp) {
	std::unique_ptr<Entity> ptr;

	switch (resolveOption(name_tmp))
	{
	case goblin: {
		ptr = std::make_unique<Goblin>(x_tmp, y_tmp);
		ptr->set_level(level_tmp);
		break;
	}
	default:
		break;
	}

	mobs[x_tmp][y_tmp] = std::move(ptr);
}