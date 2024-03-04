#pragma once
#include <string>
using namespace std;
class Validator
{
public:
    //validate the color of the product
    bool validate_color_product(string color);
    //validate the size of the product
    bool validate_size_product(string size);

    //validate the price of the product
    int validate_price_product(string price);

    //validate the quantity of the product
    int validate_quantity_product(string quantity);

    //validate the link of the photograph
    bool validate_photograph_product(string photograph);
};