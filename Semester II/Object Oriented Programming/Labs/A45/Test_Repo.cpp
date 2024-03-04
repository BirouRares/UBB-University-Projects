#include "Test_Repo.h"
#include "repository.h"
#include "dynamic_array.h"
#include <assert.h>

void Test_Repository::Test_init_repository() {
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);
    Repository* repo = new Repository(DA);
    repo->init_repo();
    assert((*repo)[0].GetSize() == "S");
    assert((*repo)[0].GetColour() == "red");
    assert((*repo)[0].GetPrice() == 100);
    assert((*repo)[0].GetQuantity() == 2);
    assert((*repo)[0].GetPhoto() == "https://www.google.com/imgres?imgurl");

    delete repo;
}

void Test_Repository::TestGetSize() {
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);
    Repository* repo = new Repository(DA);
    repo->init_repo();
    assert(repo->GetSize() == 10);
    delete repo;
}

void Test_Repository::TestGetDynArr() {
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);
    Repository* repo = new Repository(DA);
    assert(DA == repo->GetDArray());
    delete repo;
}

void Test_Repository::TestAddRepo() {
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);
    Repository* repo = new Repository(DA);
    assert(repo->AddRepo("M", "Blue", 100, 10, "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg") == 0);
    assert((*repo)[0].GetSize() == "M");
    assert((*repo)[0].GetColour() == "Blue");
    assert((*repo)[0].GetPrice() == 100);
    assert((*repo)[0].GetQuantity() == 10);
    assert((*repo)[0].GetPhoto() == "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg");
    assert(repo->AddRepo("M", "Blue", 100, 10, "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg") == 1);

    delete repo;
}

void Test_Repository::TestCheckExistenceCoat() {
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);
    Repository* repo = new Repository(DA);
    repo->AddRepo("M", "Blue", 100, 10, "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg");
    assert(repo->CheckExistence("M", "Blue", "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg") == 0);
    assert(repo->CheckExistence("S", "Pink", "https://sagsahj.jpg/saghsa") == -1);
    delete repo;
}
void Test_Repository::TestDeleteEntireProductRepo() {
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);
    Repository* repo = new Repository(DA);
    repo->AddRepo("M", "Blue", 100, 10, "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg");
    assert(repo->DeleteEntireProductRepo("M", "Blue", "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg") == 0);
    assert(repo->DeleteEntireProductRepo("s", "Purple", "https://safghsajk.jpg") == 1);
    delete repo;
}
void Test_Repository::TestDeleteSoldOutProductRepo() {
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);
    Repository* repo = new Repository(DA);
    repo->AddRepo("M", "Blue", 100, 10, "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg");
    repo->AddRepo("M", "Pink", 100, 0, "https://abcdef.jpg");
    assert(repo->DeleteSoldOutRepo("M", "Blue", "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg") == 1);
    assert(repo->DeleteSoldOutRepo("M", "Pink", "https://abcdef.jpg") == 0);
    delete repo;
}

void Test_Repository::TestUpdatePriceRepo() {
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);
    Repository* repo = new Repository(DA);
    repo->AddRepo("M", "Pink", 100, 0, "https://abcdef.jpg");
    assert(repo->UpdatePriceRepo("M", "Pink", "https://abcdef.jpg", 999) == 0);
    assert((*repo)[0].GetPrice() == 999);
    assert(repo->UpdatePriceRepo("S", "Blue", "https://abcdesaff.jpg", 999) == 1);
    delete repo;
}

void Test_Repository::TestUpdateQuantityRepo() {
    DynamicArray<Coat>* DA = new DynamicArray<Coat>(100);
    Repository* repo = new Repository(DA);
    repo->AddRepo("M", "Pink", 100, 0, "https://abcdef.jpg");
    assert(repo->UpdateQuantityRepo("M", "Pink", "https://abcdef.jpg", 999) == 0);
    assert((*repo)[0].GetQuantity() == 999);
    assert(repo->UpdateQuantityRepo("S", "Blue", "https://abcdesaff.jpg", 999) == 1);

    delete repo;
}

void Test_Repository::TestAllRepository() {
    Test_init_repository();
    TestGetSize();
    TestGetDynArr();
    TestAddRepo();
    TestCheckExistenceCoat();
    TestDeleteEntireProductRepo();
    TestDeleteSoldOutProductRepo();
    TestUpdatePriceRepo();
    TestUpdateQuantityRepo();

}