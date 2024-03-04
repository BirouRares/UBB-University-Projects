#include "UI.h"
#include "validation.h"
#include <crtdbg.h>

int main()
{
	std::string fileName = "coat.txt";
	Repository repo = Repository(fileName);
	repo.loadEntitiesFromFile();
	Service serv = Service(repo);
	UserService userServ = UserService();
	Validator* validator = new Validator();
	UI ui = UI(serv, userServ);
	ui.run();
	
    return 0;
}