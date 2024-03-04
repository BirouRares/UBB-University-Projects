#include "domain.h"
#include <cstring>

Coat::Coat()
{}

Coat::Coat(string size, string colour, int price, int quantity, string photo):
	size{size}, colour{colour}, price{price}, quantity{quantity}, photo{photo}
{}

string Coat::GetSize()
{
	return this->size;
}
string Coat::GetColour()
{
	return this->colour;
}
string Coat::GetPhoto()
{
	return this->photo;
}
int Coat::GetPrice()
{
	return this->price;
}
int Coat::GetQuantity()
{
	return this->quantity;
}
void Coat::SetSize(string size)
{
	this->size = size;
}
void Coat::SetColour(string colour)
{
	this->colour = colour;
}
void Coat::SetPhoto(string photo)
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