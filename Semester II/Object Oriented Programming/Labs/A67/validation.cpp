#include "validation.h"

void Validator::validateCoat(const Coat& c)
{
    std::string size=c.GetSize();
    if(size != "XXS" and size != "XS" and size != "S" and size != "M" and size != "L" and size != "XL" and size != "XXL")
		throw std::invalid_argument("\nInvalid size!\n\n");
	std::string colour=c.GetColour();
	if(colour.empty())
        throw std::invalid_argument("\nInvalid colour!\n\n");
    std::string photo=c.GetPhoto();
    if(photo.empty())
		throw std::invalid_argument("\nInvalid photo!\n\n");
    int price=c.GetPrice();
    if(price < 0)
        throw std::invalid_argument("\nInvalid price!\n\n");
    int quantity=c.GetQuantity();
    if(quantity < 0)
		throw std::invalid_argument("\nInvalid quantity!\n\n");
}