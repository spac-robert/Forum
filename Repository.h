#pragma once
#include "Database.h"
#include <iostream>
#include <mysql.h>
#include "ErrorMessages.h"
#include "Post.h"

using namespace std; 

class Repo:public Database{

private:
    MYSQL* conn;

public:
    Repo(string nameDatabase){

        conn = mysql_init(NULL);
        mysql_real_connect(conn, "localhost", "root", "Spa306r*4834", nameDatabase.c_str(), 3306, NULL, 0);
		//mysql_real_connect(conn, "localhost", "root", "Spa306r*4834", "forumdatabase", 3306, NULL, 0);
        
    }
    ~Repo() {
    }

	vector<Account> displaydata() {
		MYSQL_RES* result;
		MYSQL_ROW row;
		int num_fields;
		int i;
		vector<Account>arr;
		//retrieve and display data
		mysql_query(conn, "SELECT * FROM users");
		result = mysql_store_result(conn);
		num_fields = mysql_num_fields(result);
		while ((row = mysql_fetch_row(result)))
		{
			Account account(row[0], row[1], row[2], row[3]);
			arr.push_back(account);
		}
		mysql_free_result(result);//clear result set from memory
		return arr;

	}

	void insertdata(string name,string pass,int id) {

		string qstr;
		qstr = "insert into users values('"+ to_string(id) + "' , '" + name + "' , '" + pass + "','user')";
		mysql_query(conn, qstr.c_str());
	}


	void deletedata(string name) {

		string qstr;
		qstr = "DELETE FROM users WHERE name= '"+name+"'";
		mysql_query(conn, qstr.c_str());
	}

	
	Account find_user(string name) {
		MYSQL_RES* result;
		MYSQL_ROW row;
		int num_fields;
		
		mysql_query(conn, "SELECT * FROM users");
		result = mysql_store_result(conn);
		num_fields = mysql_num_fields(result);
		while ((row = mysql_fetch_row(result)))
		{
			if (row[1] == name) {
				Account account_find(row[0], row[1], row[2], row[3]);
				mysql_free_result(result);
				return account_find;
			}	
		}
		mysql_free_result(result);
		return Account();
	}

	void updateuser(Account account) {
		MYSQL_RES* result;
		MYSQL_ROW row;
		string str;
		if (account.get_type() == "admin")
			str = "update users set type='user' where name='"+account.get_name()+"'";
		else
			str = "update users set type='admin' where name='" + account.get_name() + "'";
		mysql_query(conn, str.c_str());
	}

	/*void addPost(Post post) {
		MYSQL_RES* result;
		MYSQL_ROW row;
		string str;
		str = "insert into posts value(" + post.get_id() + ",'" + post.get_user_id() + "','" + post.get_title() + "','" + post.get_post() + "')";
		mysql_query(conn, str.c_str());
	}

	vector<Post> find_user_posts(Account account) {

		Response message;
		MYSQL_RES* result;
		MYSQL_ROW row;
		vector<Post>arr;

		string str = "SELECT * FROM posts where user_id='" + account.get_id() + "'";
		const char* c = str.c_str();
		mysql_query(conn, c);
		result = mysql_store_result(conn);
		
		while ((row = mysql_fetch_row(result)))
		{
			if (row[1] == account.get_id()) {
				Post post(row[0],string(row[1]),string(row[2]),string(row[3]));
				arr.push_back(post);
			}
		}
		mysql_free_result(result);
		return arr;
	}*/
	
};