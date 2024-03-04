#pragma once
#include <string>
using namespace std;
class Coat {
	private:
		string size;
		string colour;
		int price;
		int quantity;
		string photo;
	public:
		Coat();
		Coat(string size, string colour, int price, int quantity, string photo);
		string GetSize();// return the size of the coat
		string GetColour();// return the colour of the coat
		string GetPhoto();// return the photo of the coat
		int GetPrice();// return the price of the coat
		int GetQuantity();// return the quantity of the coat

		void SetSize(string size);// set the size of the coat
		void SetColour(string colour);// set the colour of the coat
		void SetPhoto(string photo);// set the photo of the coat
		void SetPrice(int price);// set the price of the coat
		void SetQuantity(int quantity);// set the quantity of the coat
};