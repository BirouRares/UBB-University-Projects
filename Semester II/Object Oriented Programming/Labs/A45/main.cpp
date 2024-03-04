#include <iostream>
#include "repository.h"
#include "dynamic_array.h"
#include "domain.h"
#include "validation.h"
#include "service.h"
#include "ui.h"
#include "test_domain.h"
#include "Test_DynamicArray.h"
#include "Test_Repo.h"
#include "Test_Service.h"
#include "Test_Validation.h"
#include <crtdbg.h>
#include <windows.h>
using namespace std;

int main(int argc, char* argv[])
{
    DynamicArray<Coat>* UserDA = new DynamicArray<Coat>(100);// create a dynamic array for the user repository
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);// create a dynamic array for the repository
    Repository* UserRepo = new Repository(UserDA);// create a repository for the user repository
    Repository* repo = new Repository(DA);// create a repository for the repository
    repo->init_repo();// initialize the repository
    Service* service = new Service(repo, UserRepo);// create a service
    Validator* validator = new Validator();// create a validator
    Console* console = new Console(service, validator);// create a console

    Test_Domain test1;
    test1.TestAllDomain();
    Test_DynamicArray test2;
    test2.TestAllDynamicArray();
    Test_Repository test3;
    test3.TestAllRepository();
    Test_Service test4;
    test4.TestAllService();
    Test_Validation test5;
    test5.TestAllValidation();

    console->start();// start the console
    delete console;// delete the console


    _CrtDumpMemoryLeaks();

    return 0;
}