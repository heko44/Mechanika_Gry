#include "Tools.hpp"
#include <sstream>

void FileTextToSharedPtr::SaveFromFile(){
	
	std::ifstream input;
	std::ofstream output;

	input.open("data.txt");
	output.open("output_data.txt");

	if (!input)
		std::cerr << "Could not open file to read";

	if (!output)
		std::cerr << "Could not open file to write";

	std::string line;
	std::string firstArg, secondArg, thirdArg, fourthArg;

	while (std::getline(input,line)) {
		//std::cout << line << std::endl;

		size_t found = line.find('\t');
		firstArg = line.substr(0, found);
		thirdArg = line.substr(found + 1, line.find('\t', found + 1) - found - 1); found = line.find('\t', found + 1);
		fourthArg = line.substr(found + 1, line.find('\t', found + 1) - found - 1); found = line.find('\t', found + 1); found = line.find('\t', found + 1);
		secondArg = line.substr(found + 1, line.find('\t', found + 1) - found - 1);

		//Weapon(std::string name, int price, int damage_points, int required_level);
		//std::make_shared<Weapon>("Rusty sword", 10, 5, 1),

		output << "std::make_shared<Weapon>('" << firstArg << "', " << secondArg << ", " << thirdArg << ", "
			<< fourthArg << ")," << std::endl;
	}

	input.close();
	output.close();
}