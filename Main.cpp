#include <iostream>
#include"UI.h"
#include "Tests.h"
int main()
{
    Tests tests;
    tests.runTests();//imi sare peste assert

    PostRepo postrepo;
    /*Database* database= new Database;
    database = new Repo();
    Repo repo;*/
   
    AccountService serviceAccount(new Repo("forumdatabase"),postrepo);//in teste este Testdatabase
    UI ui(serviceAccount);
    ui.run();

    return 0;
}

