#pragma once
#include <vector>
#include <string>
#include "Account.h"

class Database {

public:

	Database() {
	};
	~Database() {
	};
	virtual std::vector<Account> displaydata() = 0;

	virtual void insertdata(std::string name, std::string pass, int id) = 0;


	virtual void deletedata(std::string name) = 0;


	virtual Account find_user(std::string name) = 0;

	virtual void updateuser(Account account) = 0;
};