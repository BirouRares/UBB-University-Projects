#pragma once
#include <string>
#include <iostream>
class Coat {
	private:
		std::string size;
		std::string colour;
		int price;
		int quantity;
		std::string photo;
	public:
		Coat();
		
		Coat(const std::string&, const std::string&, const int&, const int&, const std::string&);
		Coat(const Coat& c);
		~Coat();
		std::string GetSize() const;// return the size of the coat
		std::string GetColour() const;// return the colour of the coat
		std::string GetPhoto() const;// return the photo of the coat
		int GetPrice() const;// return the price of the coat
		int GetQuantity() const;// return the quantity of the coat

		void SetSize(std::string size);// set the size of the coat
		void SetColour(std::string colour);// set the colour of the coat
		void SetPhoto(std::string photo);// set the photo of the coat
		void SetPrice(int price);// set the price of the coat
		void SetQuantity(int quantity);// set the quantity of the coat

		std::string toString() const;

		Coat& operator = (const Coat& c);
		bool operator == (const Coat& c) const;

		friend std::ostream& operator << (std::ostream& os, const Coat& c);
		friend std::istream& operator >> (std::istream& is, Coat& c);
		
};