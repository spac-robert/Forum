#pragma once
#include <string>
#include <istream>

class Account {

private:
	std::string name, password,type,id;

public:
	Account() {
		this->id = "";
		this->name = "";
		this->password = "";
		this->type = "";
	}
	Account(std::string id,std::string name, std::string password, std::string type) {
		this->id = id;
		this->name = name;
		this->password = password;
		this->type = type;
	}
	Account(const Account& account) {

		this->id = account.id;
		this->name = account.name;
		this->password = account.password;
		this->type = account.type;
	}
	~Account() {
		this->id = "";
		this->name = "";
		this->password = "";
		this->type = "";
	}

	//Getters
	std::string get_id() {
		return this->id;
	}

	std::string get_name() {
		return this->name;
	}

	std::string get_pass() {
		return this->password;
	}

	std::string get_type() {
		return this->type;
	}
	//Setters

	void set_id(std::string new_id) {
		this->id = new_id;
	}

	void set_name(std::string new_id) {
		this->name = new_id;
	}
	
	void set_pass(std::string new_pass) {
		this->password = new_pass;
	}

	void set_type(std::string new_type) {
		this->type = new_type;
	}

	//Overloading oprators

	bool operator ==(const Account& account) {

		return account.name == name and account.password == password and account.id==id and account.type==type;
	}

	/*friend std::istream& operator >>(std::istream& is, Account& account) {
		is >> account.id >> account.password;
		return is;
	}
	*/
	friend std::ostream& operator <<(std::ostream& os, Account account) {
		os << "User: " << account.get_name() << " | " << "Type: " << account.get_type() << "\n"<<"\n";
		return os;
	}

};