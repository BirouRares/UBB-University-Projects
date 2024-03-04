#include "test.h"
#include <assert.h>
#include <iostream>
#include "domain.h"
#include "repository.h"
#include "validation.h"
#include "service.h"

void Test::TestAllDomain()
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

void Test::TestGetPhoto()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	assert(coat.GetPhoto() == "photo");
}

void Test::TestGetColour()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	assert(coat.GetColour() == "colour");
}

void Test::TestGetSize()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	assert(coat.GetSize() == "photo");
}

void Test::TestGetPrice()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	assert(coat.GetPrice() == 1);
}

void Test::TestGetQuantity()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	assert(coat.GetQuantity() == 1);
}

void Test::TestSetPhoto()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	coat.SetPhoto("photo2");
	assert(coat.GetPhoto() == "photo2");
}

void Test::TestSetColour()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	coat.SetColour("colour2");
	assert(coat.GetColour() == "colour2");
}

void Test::TestSetSize()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	coat.SetSize("photo2");
	assert(coat.GetSize() == "photo2");
}

void Test::TestSetPrice()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	coat.SetPrice(2);
	assert(coat.GetPrice() == 2);
}

void Test::TestSetQuantity()
{
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	coat.SetQuantity(2);
	assert(coat.GetQuantity() == 2);
}

void Test::TestAllRepository()
{
	TestAddCoatRepo();
	TestUpdateCoatRepo();
	TestGetCoatList();
}

void Test::TestAddCoatRepo()
{
	std::string filename = "test.txt";
	Repository repo=Repository(filename);
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	repo.addCoatRepo(coat);
	assert(repo.getCoatList().size() == 1);
}

void Test::TestUpdateCoatRepo()
{
	std::string filename = "test.txt";
	Repository repo = Repository(filename);
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	repo.addCoatRepo(coat);
	Coat coat2 = Coat("photo2", "colour2", 2, 2, "photo2");
	repo.updateCoatRepo("photo", coat2);
	assert(repo.getCoatList()[0].GetPhoto() == "photo2");
}

void Test::TestGetCoatList()
{
	std::string filename = "test.txt";
	Repository repo = Repository(filename);
	Coat coat = Coat("photo", "colour", 1, 1, "photo");
	repo.addCoatRepo(coat);
	assert(repo.getCoatList().size() == 1);
}

void Test::TestAllService()
{
	TestAddCoatService();
	TestRemoveCoatService();
	TestUpdateCoatService();
	TestGetCoatListService();
	TestGetShoppingBag();
	TestAddCoatToShoppingBag();
	TestGetTotalPrice();
}

void Test::TestAddCoatService()
{
	std::string filename = "test.txt";
	Repository repo = Repository(filename);
	Service service = Service(repo);
	service.addCoatServ("XXL","red",1,1,"rerer");
	assert(service.getCoatList().size() == 1);
}

void Test::TestRemoveCoatService()
{
	std::string filename = "test.txt";
	Repository repo = Repository(filename);
	Service service = Service(repo);
	service.addCoatServ("XXL", "red", 1, 1, "rerer");
	service.removeCoatServ("XXL","red","rerer");
	assert(service.getCoatList().size() == 0);
}

void Test::TestUpdateCoatService()
{
	std::string filename = "test.txt";
	Repository repo = Repository(filename);
	Service service = Service(repo);
	service.addCoatServ("XXL", "red", 1, 1, "rerer");
	service.updateCoatServ("XXL", "red", 2, 2, "rerer");
	assert(service.getCoatList()[0].GetColour() == "red");
}

void Test::TestGetCoatListService()
{
	std::string filename = "test.txt";
	Repository repo = Repository(filename);
	Service service = Service(repo);
	service.addCoatServ("XXL", "red", 1, 1, "rerer");
	assert(service.getCoatList().size() == 1);
}

void Test::TestGetShoppingBag()
{
	std::string filename = "test.txt";
	Repository repo = Repository(filename);
	Service service = Service(repo);
	service.addCoatServ("XXL", "red", 1, 1, "rerer");
}

void Test::TestAddCoatToShoppingBag()
{
	std::string filename = "test.txt";
	Repository repo = Repository(filename);
	Service service = Service(repo);
	service.addCoatServ("XXL", "red", 1, 1, "rerer");

}

void Test::TestGetTotalPrice()
{
	std::string filename = "test.txt";
	Repository repo = Repository(filename);
	Service service = Service(repo);
	service.addCoatServ("XXL", "red", 1, 1, "rerer");
}

void Test::TestAll()
{
	Test::TestAllDomain();
	Test::TestAllRepository();
	Test::TestAllService();
}




