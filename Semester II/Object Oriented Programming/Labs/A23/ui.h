#pragma once
#include "service.h"
#include "domain.h"
#include "repository.h"

typedef struct {
	Service* service;
} UI;

UI* createUI(Service* service);
void destoryUI(UI* ui);
void printMenu();
int addEstateUI(UI* ui);
int deletEestateUI(UI* ui);
int updateEstateUI(UI* ui);
void start(UI* ui);
void tests();
int start_app();