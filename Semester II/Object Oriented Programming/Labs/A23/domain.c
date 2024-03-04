#define _CRT_SECURE_NO_WARNINGS
#include "domain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Estate* createEstate(const char type[], const char address[], int surface, int price)
{
    Estate* estate = (Estate*)malloc(sizeof(Estate));// we allocate memory for the estate
    if (estate == NULL) {//if the allocation fails, we return null
        return NULL;
    }
    estate->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));//we allocate memory for the type of the estate
    if (estate->type != NULL) {
        memcpy(estate->type, type, strlen(type) + 1);// we copy the type of the estate
    }
    estate->address = (char*)malloc(sizeof(char) * (strlen(address) + 1));
    if (estate->address != NULL) {
        memcpy(estate->address, address, strlen(address) + 1);// we copy the address of the estate
    }
    estate->surface = surface;
    estate->price = price;

    return estate;
}

void destroyEstate(Estate* estate)//this function is used to free the memory allocated for an estate
{
    if (estate == NULL)//if the estate is null, we don't have to free anything
        return;
    free(estate->address);

    free(estate);
    estate = NULL;
}
char* getType(Estate* estate)// this function is used to get the type of an estate
{
    if (estate == NULL) 
        return NULL;
    return estate->type;// return the type of the estate
}

Estate* copyEstate(Estate* estate)//this function is used to copy an estate
{
    if (estate == NULL) {//if the estate is null, we don't have to copy anything
        return NULL;
    }
    Estate* estate1 = createEstate(estate->type, estate->address, estate->surface, estate->price);//create a new estate
    return estate1;//return the copy of the estate
}


char* getAddress(Estate* estate)// this function is used to get the address of an estate
{
    if (estate == NULL) {
        return NULL;
    }
    return estate->address;// return the address of the estate
}

int getSurface(Estate* estate)// this function is used to get the surface of an estate
{
    if (estate == NULL) {
        return -1;
    }
    return  estate->surface;// return the surface of the estate
}

int getPrice(Estate* estate)// this function is used to get the price of an estate
{
    if (estate == NULL) {
        return -1;
    }
    return estate->price;// return the price of the estate
}

void setAddress(Estate* estate, const char* newAddress)
{
    estate->address = newAddress; // set the address of the estate
}

void setSurface(Estate* estate, int newSurface)
{
    estate->surface = newSurface;// set the surface of the estate
}

void setPrice(Estate* estate, int newPrice)
{
    estate->price = newPrice;// set the price of the estate
}

void setType(Estate* estate, const char* newType)
{
    strcpy(estate->type, newType);// set the type of the estate
}

void toString(Estate* estate, char str[])// this function is used to print the information of an estate
{                                          // in a string
    if (estate == NULL) {
        return;
    }
    printf_s(str, "Type: %s; Address: %s; Surface: %d; Price: %d", estate->type,estate->address, estate->surface, estate->price);
}

void TestEstate()// this function is used to test the functions from the domain
{
    Estate* estate = createEstate("House", "Oncea", 321, 100);
    assert(strcmp(getType(estate), "House") == 0);
    assert(strcmp(getAddress(estate), "Oncea") == 0);
    assert(getSurface(estate) == 321);
    assert(getPrice(estate) == 100);
    setAddress(estate, "Oradea");
    assert(strcmp(getAddress(estate), "Oradea") == 0);
    setSurface(estate, 100);
    assert(getSurface(estate) == 100);
    setPrice(estate, 15);
    assert(getPrice(estate) == 15);
}

