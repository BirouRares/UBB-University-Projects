#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <string.h>
#include <time.h>

UI* createUI(Service* service)
{
    UI* ui = (UI*)malloc(sizeof(UI));
    if (ui == NULL) {
        return NULL;
    }
    ui->service = service;
    return ui;
}

void destoryUI(UI* ui)
{
    if (ui == NULL) {
        return;
    }
    destroyService(ui->service);
    free(ui);
}

void printMenu()
{

    printf("0.Exit\n");
    printf("1.Add an estate\n");
    printf("2.Delete an estate\n");
    printf("3.Update an estate\n");
    printf("4.Display estates by address\n");
    printf("5.See all estates of a given type,\n");
    printf("6.Undo\n");
    printf("7.Redo\n");

}

int readIntegerNumber(const char* message)
{
    char string[16] = { 0 };
    int result;
    int flag = 0;
    int read;

    while (flag == 0) {
        printf(message);
        scanf("%s", string);
        read = sscanf_s(string, "%d", &result);
        flag = (read == 1);

        if (flag == 0) {
            printf("Invalid option! Try again\n");
        }
    }
    return result;
}

int addEstateUI(UI* ui)
{
    char type[50];
    char address[50];
    int price = 0;
    int surface = 0;

    printf("Type of the estate(House, Apartment or Penthouse): ");

    scanf("%s", type);

    //check if the type is valid
    if (strcmp(type, "House") != 0 && strcmp(type, "Apartment") != 0 && strcmp(type, "Penthouse") != 0)
    {
		printf("Invalid type!\n");
		return 0;
	}

    printf("Address: ");

    //scanf("%s", address);
    gets(address);
    gets(address);

    printf("Surface: ");
    if (1 != scanf_s("%d", &surface))
    {
        while (getchar() != '\n');
        return 0;
    }

    printf("Price: ");
    if (1 != scanf_s("%d", &price))
    {
        while (getchar() != '\n');
        return 0;
    }

    return add(ui->service, type, address, surface, price);
}

int deleteEstateUI(UI* ui)
{
    char type[50];
    char address[50];
    int price = 0;


    printf("Address of the estate you want to delete: ");
    //scanf("%s", address);
    gets(address);
    gets(address);
    return deleteServ(ui->service, address);
}

int updateEstateUI(UI* ui)
{
    char type[50];
    char address[50];
    int price = 0;
    int new_surface = 0;

    printf("Type of the estate(House, Apartment or Penthouse): ");

    scanf("%s", type);

    //check if the type is valid
    if (strcmp(type, "House") != 0 && strcmp(type, "Apartment") != 0 && strcmp(type, "Penthouse") != 0)
    {
        printf("Invalid type!\n");
        return 0;
    }
    printf("Address of the estate you want to update: ");
    //scanf("%s", address);
    gets(address);
    gets(address);
    printf("Price of the estate you want to update: ");
    scanf_s("%d", &price);
    printf("Surface of the estate you want to update: ");
    scanf_s("%d", &new_surface);

    return update(ui->service, type, address, price, new_surface);
}

void printVector(DynamicArray* v)
{
    if (v == NULL)
        return;

    int count = getArrayLength(v);
    for (int i = 0; i < count; i++)
    {
        Estate* estate = (Estate*)getElementAtIndex(v, i);
        if (estate != NULL)
        {
            char* type = getType(estate);
            char* address = getAddress(estate);
            int surface = getSurface(estate);
            int price = getPrice(estate);
            printf("Type:%s  |||  Address:%s  |||  Surface:%d  |||  Price:%d\n", type, address, surface, price);
        }
    }
    printf("\n");
}



void printEstatesByName(UI* ui)
{
    const char* type[50];
    printf("Address to search for: ");
    gets(type);
    gets(type);
    if (type == NULL)
    {
        DynamicArray* estateData = getEstates(ui->service);
        sortEstatesVectorAscendingByPrice(estateData);
        printVector(estateData);
    }
    else
    {
        DynamicArray* estates = getEstatesByName(ui->service, type);
        sortEstatesVectorAscendingByPrice(estates);
        printVector(estates);
        destroyDynamicArray(estates);
    }
}
void print_vector(UI* ui)
{
    DynamicArray* estateData = getEstates(ui->service);
    printVector(estateData);
}


void printEstatesBySomething(UI* ui)
{
    int surface;
    const char* type[50];
    printf("Type of the estate(House, Apartment or Penthouse): ");

    scanf("%s", type);

    if (strcmp(type, "House") != 0 && strcmp(type, "Apartment") != 0 && strcmp(type, "Penthouse") != 0)
    {
        printf("Invalid type!\n");
        return 0;
    }
    printf("Please input the surface to search for: ");
    scanf("%d", &surface);
    DynamicArray* estates = getEstatesBySurface(ui->service, surface, type);

    printVector(estates);
}

int undoUI(UI* ui)
{
    return undo(ui->service);
}

int redoUI(UI* ui)
{
    return redo(ui->service);
}

void start(UI* ui)
{
    while (1) {
        printMenu();
        int option = readIntegerNumber("Option :  ");
        if (option == 0)
            return;
        else if (option == 1)
        {
            int addResult = addEstateUI(ui);
            if (addResult == 1)
                printf("Estate added!\n");
            else
                printf("Estate cannot be added!\n");
        }
        else if (option == 2)
        {
            int deleteResult = deleteEstateUI(ui);
            if (deleteResult == 1)
                printf("Estate deleted!\n");
            else
                printf("Estate cannot be deleted!\n");
        }
        else if (option == 3)
        {
            int t = updateEstateUI(ui);
            if (t == 1)
                printf("Estate successfully updated!\n");
            else
                printf("Estate cannot be updated!\n");
        }
        else if (option == 4)
            printEstatesByName(ui);
        else if (option == 5)
            printEstatesBySomething(ui);
        else if (option == 6)
        {
            int undoResult = undoUI(ui);
            if (undoResult == 1)
                printf("Undo Complete ! \n");
            else
                printf("No more undo!\n");
        }
        else if (option == 7)
        {
            int redoResult = redoUI(ui);
            if (redoResult == 1)
                printf("Redo complete!\n");
            else
                printf("No more redo! \n");
        }
        else if (option < 0 || option > 7)
        {
            printf("Invalid option ! Please type a valid input\n");
        }
    }
}

void tests()
{
    TestEstate();
    testEstateRepo();
    testService();
    testDynamicArray();
}

int start_app() {
    Repository* Repo = createRepository(30);
    Service* service = createService(Repo);
    UI* ui = createUI(service);
    start(ui);
    destoryUI(ui);

    tests();
}