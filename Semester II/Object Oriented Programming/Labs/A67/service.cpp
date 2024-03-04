#include "service.h"
#include "errors.h"

Service::Service(Repository& repo) : repo{ repo } {}

void Service::addCoatServ(std::string size, std::string colour, int price, int quantity, std::string photo)
{
	Coat c=Coat( size, colour, price, quantity, photo );
	try
	{
		this->repo.addCoatRepo(c);
	}
	catch (RepoError e)
	{
		throw e;
	}	
}

void Service::removeCoatServ(std::string size, std::string colour, std::string photo)
{
	try
	{
		this->repo.deleteCoatRepo(size, colour, photo);
	}
	catch (RepoError e)
	{
		throw e;
	}
}

void Service::updateCoatServ(std::string size, std::string colour, int price, int quantity, std::string photo)
{
	Coat c = Coat(size, colour, price, quantity, photo);
	try
	{
		this->repo.updateCoatRepo(photo, c);
	}
	catch (RepoError e)
	{
		throw e;
	}
}

std::vector<Coat> Service::getCoatList()
{
	return this->repo.getCoatList();
}
Service::~Service() = default;
