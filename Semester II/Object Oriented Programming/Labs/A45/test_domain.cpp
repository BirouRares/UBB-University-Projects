#include "domain.h"
#include "test_domain.h"
#include <assert.h>

void Test_Domain::TestAllDomain()
{
	TestGetPhoto();
	TestGetColour();
	TestGetSize();
	TestGetPrice();
	TestGetQuantity();
	TestSetPhoto();
	TestSetColour();
	TestSetSize();
	TestSetPrice();
	TestSetQuantity();
}

void Test_Domain::TestSetQuantity()
{
	Coat c("XL", "Pink", 100, 10, "https://github.com/cs-ubbcluj-ro/a45-BirouRares");
	c.SetQuantity(999);
	assert(c.GetQuantity() == 999);
}

void Test_Domain::TestSetPrice()
{
	Coat c("XL", "Pink", 100, 10, "https://asgh.jpg/asgh");
	c.SetPrice(999);
	assert(c.GetPrice() == 999);
}

void Test_Domain::TestSetSize()
{
	Coat c("XL", "Pink", 100, 10, "https://github.com/cs-ubbcluj-ro/a45-BirouRares");
	c.SetSize("M");
	assert(c.GetSize() == "M");
}

void Test_Domain::TestSetColour()
{
	Coat c("XL", "Pink", 100, 10, "https://github.com/cs-ubbcluj-ro/a45-BirouRares");
	c.SetColour("Blue");
	assert(c.GetColour() == "Blue");
}

void Test_Domain::TestSetPhoto()
{
	Coat c("XL", "Pink", 100, 10, "https://github.com/cs-ubbcluj-ro/a45-BirouRares");
	c.SetPhoto("https://www.youtube.com/watch?v=4U9exgbJ9Q4");
	assert(c.GetPhoto() == "https://www.youtube.com/watch?v=4U9exgbJ9Q4");
}

void Test_Domain::TestGetQuantity()
{
	Coat c("XL", "Pink", 100, 10, "https://www.youtube.com");
	assert(c.GetQuantity() == 10);
}

void Test_Domain::TestGetColour()
{
	Coat c("XL", "Pink", 100, 10, "https://asgh.jpg/asgh");
	assert(c.GetColour() == "Pink");
}

void Test_Domain::TestGetPhoto()
{
	Coat c("XL", "Pink", 100, 10, "https://asgh.jpg/asgh");
	assert(c.GetPhoto() == "https://asgh.jpg/asgh");
}

void Test_Domain::TestGetSize()
{
	Coat c("XL", "Pink", 100, 10, "https://asgh.jpg/asgh");
	assert(c.GetSize() == "XL");
}

void Test_Domain::TestGetPrice()
{
	Coat c("XL", "Pink", 100, 10, "https://asgh.jpg/asgh");
	assert(c.GetPrice() == 100);
}