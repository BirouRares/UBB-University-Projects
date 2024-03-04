#pragma once
#include "service.h"
#include "validation.h"

class Console
{
private:
	Service* service;
	Validator* validator;
public:
	Console();
	~Console();
	Console(Service* service, Validator* validator);
	void start();
	void AdminMode();
	void UserMode();
	void DisplayShoppingBag();
	void MenuAdminMode();
	void UpdateProductsPriceAdmin();
	void UpdateProductsQuantityAdmin();
	void DeleteEntireProductAdmin();
	int DisplayProductsUser();
	void DeleteSoldOutProductAdmin();
	void MenuDisplayProductsUser();
	void DisplayProductsAdmin();
	void AddAdminConsole();
	void DisplayTotalPrice();
};
