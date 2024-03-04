#pragma once

typedef struct
{
	char* type;
	char* address;
	int surface;
	int price;
} Estate;

Estate* createEstate(const char* type, const char* address, int surface, int price);
void destroyEstate(Estate* estate);

Estate* copyEstate(Estate* estate);// copy constructor
char* getType(Estate* estate);// getter
char* getAddress(Estate* estate);// getter
int getSurface(Estate* estate);// getter
int getPrice(Estate* estate);// getter
void setAddress(Estate* estate, const char* newtype);// setter
void setSurface(Estate* estate, int newSurface);// setter
void setPrice(Estate* estate, int newPrice);// setter
void setType(Estate* estate, const char* newType);// setter
void toString(Estate* estate, char str[]);// convert to string
void TestEstate();// test
