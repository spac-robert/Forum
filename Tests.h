#pragma once
#include "accountService.h"
#include <cassert>

class Tests {

public:
	void testAccount() {
		Account account;

		assert(account.get_id() == "");
		assert(account.get_name() == "");
		assert(account.get_pass() == "");
		assert(account.get_type() == "");

		account.set_id("4");
		account.set_name("Ana");
		account.set_pass("parola");
		account.set_type("user");

		assert(account.get_id()=="4");
		assert(account.get_name() == "Ana");
		assert(account.get_pass() == "parola");
		assert(account.get_type() == "user");

		Account account1("4","Ana","parola","user");
		assert(account == acount1);
	}

	void testRepository() {
		//de facut un testDatabase in mysql plus conectarea aceteia cu una pentru postari
		Database* database = new Repo("TestDatabase");
		Account account("1", "Robert", "Spac", "admin"), account1("2", "asd", "asd", "user");
		database->insertdata("asd","asd",2);
		vector<Account>arr, auxArr;
		auxArr.push_back(account);
		auxArr.push_back(account1);
		arr = database->displaydata();
		
		assert(arr[0] == account);                                      // nu merge pt ca nu vede account si account 1
		assert(arr[1] == account1);

		database->deletedata("asd");
		auxArr.erase(auxArr.begin() + 1);
		arr = database->displaydata();

		for (int i = 0; i<int(arr.size()); i++) {
			assert(arr[i] != auxArr[i]);
		}

		assert(database->find_user("Robert")== account);

		database->updateuser(account);
		account.set_type("user");
		auxArr.erase(auxArr.begin() + 1);
		arr = database->displaydata();
		auxArr.push_back(account);

		for (int i = 0; i<int(arr.size()); i++) {
			assert(arr[i] == auxArr[i]);
		}
		database->updateuser(account);
		account.set_type("Admin");
		arr = database->displaydata();
		auxArr.push_back(account);

		for (int i = 0; i<int(arr.size()); i++) {
			assert(arr[i] == auxArr[i]);
		}
	}

	void runTests() {
		testAccount();
		testRepository();
	}
};