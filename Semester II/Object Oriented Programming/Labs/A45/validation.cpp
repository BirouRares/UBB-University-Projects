#include "validation.h"
#include <ctype.h>
#include <string>
using namespace std;
bool Validator::validate_color_product(string color)// validate the color 
{
    return true;
}// \params a string 

bool Validator::validate_size_product(string size) {// validate the size
    if (size != "XXS" && size != "XS" && size != "S" && size != "M" && size != "L" && size != "XL" && size != "XXL")
        return false;
    else
        return true;
}// \params a string for the size

int Validator::validate_price_product(string price) // validate the price
{
    for (char i : price)
        if (isalpha(i))
            return -1;
    int new_price;
    new_price = stoi(price);// convert the string to int
    if (new_price < 0)
		return -1;
    return new_price;
}// \params a string for the price

bool Validator::validate_photograph_product(string photograph) // validate the photo link
{
    /*if (photograph.length() < 13)
        return false;
    if (photograph[0] != 'h' || photograph[1] != 't' || photograph[2] != 't' || photograph[3] != 'p' ||photograph[4] != 's' || photograph[5] != ':' || photograph[6] != '/' || photograph[7] != '/')
        return false;
    if (photograph.find(".com") == std::string::npos && photograph.find(".jpg") == std::string::npos)
        return false;*/
    return true;
}// \params a string for the photo link

int Validator::validate_quantity_product(string quantity) // validate the quantity string
{
    for (char i : quantity)
        if (isalpha(i))
            return -1;
    int new_quantity;
    new_quantity = stoi(quantity);
    if (new_quantity < 0)
        return -1;
    return new_quantity;
}// \params a string for the quantity