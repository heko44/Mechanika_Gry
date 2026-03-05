#pragma once

#include <memory>
#include <vector>
#include "Item.hpp"
#include <fstream>
#include <iostream>
#include <string>

struct FileTextToSharedPtr {

	std::vector<std::shared_ptr<Item>> data;
	void SaveFromFile();
};