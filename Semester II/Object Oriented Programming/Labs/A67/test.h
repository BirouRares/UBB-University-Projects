#pragma once
#include "service.h"
#include "domain.h"
#include "repository.h"
#include "validation.h"
#include <vector>
#include <assert.h>
#include <iostream>

class Test
{
public:
	void TestAllDomain();
	void TestGetPhoto();
	void TestGetColour();
	void TestGetSize();
	void TestGetPrice();
	void TestGetQuantity();
	void TestSetPhoto();
	void TestSetColour();
	void TestSetSize();
	void TestSetPrice();
	void TestSetQuantity();

	void TestAllRepository();
	void TestAddCoatRepo();
	void TestUpdateCoatRepo();
	void TestGetCoatList();

	void TestAllService();
	void TestAddCoatService();
	void TestRemoveCoatService();
	void TestUpdateCoatService();
	void TestGetCoatListService();
	void TestGetShoppingBag();
	void TestAddCoatToShoppingBag();
	void TestGetTotalPrice();

	void test_validate_color_product();
	void test_validate_size_product();
	void test_validate_price_product();
	void test_validate_quantity_product();
	void test_validate_photograph_product();
	void TestAllValidation();

	void TestAll();
};