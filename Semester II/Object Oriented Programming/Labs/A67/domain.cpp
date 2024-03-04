#include "domain.h"
#include <vector>
#include <sstream>

Coat::Coat():
	size{""}, colour{""}, price{0}, quantity{0}, photo{""}
{}

Coat::Coat(const std::string& size, const std::string& colour, const int& price, const int& quantity, const std::string& photo):
	size{size}, colour{colour}, price{price}, quantity{quantity}, photo{photo}
{}

Coat::Coat(const Coat& c)
{
	this->size=c.size;
	this->colour=c.colour;
	this->price=c.price;
	this->quantity=c.quantity;
	this->photo=c.photo;
}

std::string Coat::GetSize() const
{
	return this->size;
}
std::string Coat::GetColour() const
{
	return this->colour;
}
std::string Coat::GetPhoto() const
{
	return this->photo;
}
int Coat::GetPrice() const
{
	return this->price;
}
int Coat::GetQuantity() const
{
	return this->quantity;
}
void Coat::SetSize(std::string size)
{
	this->size = size;
}
void Coat::SetColour(std::string colour)
{
	this->colour = colour;
}
void Coat::SetPhoto(std::string photo)
{
	this->photo = photo;
}
void Coat::SetPrice(int price)
{
	this->price = price;
}
void Coat::SetQuantity(int quantity)
{
	this->quantity = quantity;
}

std::string Coat::toString() const
{
	return "Size: " + this->size + ", Colour: " + this->colour + ", Price: " + std::to_string(this->price) + ", Quantity: " + std::to_string(this->quantity) + ", Photo: " + this->photo;
}

Coat::~Coat()=default;

Coat& Coat::operator = (const Coat& c)
{
	if (this == &c)
		return *this;
	this->size = c.size;
	this->colour = c.colour;
	this->price = c.price;
	this->quantity = c.quantity;
	this->photo = c.photo;
	return *this;
}

bool Coat::operator == (const Coat& c) const
{
	return (this->size == c.size && this->colour == c.colour  && this->photo == c.photo);
}

std::ostream& operator << (std::ostream& os, const Coat& c)
{
	os << c.GetSize() << ",";
	os << c.GetColour() << ",";
	os << c.GetPrice() << ",";
	os << c.GetQuantity() << ",";
	os << c.GetPhoto();
	//os << "\n";
	return os;
}

std::istream& operator >> (std::istream& is, Coat& c)
{
	std::string line;
	getline(is, line);
	std::vector<std::string> tokens;
	std::stringstream ss(line);
	std::string token;
	while (getline(ss, token, ','))
		tokens.push_back(token);
	if (tokens.size() != 5)
		return is;
	c.size = tokens[0];
	c.colour = tokens[1];
	c.price = stoi(tokens[2]);
	c.quantity = stoi(tokens[3]);
	c.photo = tokens[4];
	return is;
}
/*std::istream& operator >> (std::istream& is, Coat& c)
{
	std::string line;
	std::getline(is, line);
	if (line.empty())
		return is;

	std::vector<std::string> tokens;
	tokens = tokenize(line, ',');

	if (tokens.size() != 5)
		return is;
	c.size = tokens[0];
	c.colour = tokens[1];
	c.price = std::stoi(tokens[2]);
	c.quantity = std::stoi(tokens[3]);
	c.photo = tokens[4];
	return is;
}*/