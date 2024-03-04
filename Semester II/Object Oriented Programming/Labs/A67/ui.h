#pragma once
#include "service.h"
#include "userService.h"
#include "validation.h"

class UI
{
private:
	Service& adminService;
	UserService& userService;
	
	void handleAdd();
	void handleRemove();
	void handleUpdate();
	void printCoat();

	void printShoppingBag();
	void handleBuy();
	void openFile();

	void displayAdminMenu();
	void displayUserMenu();

	void AdminMode();
	void UserMode();
	
public:
	
	UI(Service& adminService, UserService& userService);
	void run();
	~UI();
};
