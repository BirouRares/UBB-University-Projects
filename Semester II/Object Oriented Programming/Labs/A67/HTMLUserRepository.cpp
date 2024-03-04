#include "HTMLUserRepository.h"
#include <fstream>

HTMLUserRepository::HTMLUserRepository(std::string HTMLfileName)
{
	this->fileName = HTMLfileName;
}

void HTMLUserRepository::writeToFile()
{
	std::ofstream fileOut(fileName);
	fileOut << "<!DOCTYPE html>\n<html><head><title>Trench coats list</title></head><body>\n";
	fileOut << "<table border=\"1\">\n";
	fileOut << " <tr><td>Size</td><td>Color</td><td>Price</td><td>Quantity</td><td>Photo link</td></tr>\n";
	for (auto coat : coatList)
	{
		fileOut << "<tr><td>" << coat.GetSize() << "</td><td>" << coat.GetColour() << "</td><td>" << std::to_string(coat.GetPrice()) << "</td><td>" << std::to_string(coat.GetQuantity()) << "</td>" << "<td><a href = \"" << coat.GetPhoto() << "\">" << coat.GetPhoto() << "</a></td></tr>\n";
	}
	fileOut << "</table>\n</body>\n</html>";
	fileOut.close();
}

HTMLUserRepository::~HTMLUserRepository() = default;