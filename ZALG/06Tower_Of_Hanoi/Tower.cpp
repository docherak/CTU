#include "Tower.h"
#include <iostream>

Tower::Tower() {
	std::cout << "__TOWER__" << std::endl;
}

Tower::Tower(int _discAmount) {
	discs.resize(_discAmount);
	std::cout << "Velikost: " << discs.size() << std::endl;
}

void Tower::nullify() {
	height = 0;
	for (int i = 0; i < discs.size(); i++)
		discs.at(i) = 0;
}

void Tower::init() {
	height = discs.size();
	for (int i = 0; i < height; i++)
		discs.at(i) = height - i;
}

void Tower::print(int maxHeight) {
	for (int i = 0; i < height; i++)
		std::cout << discs.at(i);
	for (int i = height; i <= maxHeight; i++)
		std::cout << '-';
}
