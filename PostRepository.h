#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <mysql.h>
#include "ErrorMessages.h"
#include "Account.h"
#include "Post.h"
#include <vector>

class PostRepo {
private:
    MYSQL* conn;

public:
    PostRepo() {
        conn = mysql_init(NULL);
        mysql_real_connect(conn, "localhost", "root", "Spa306r*4834", "forumdatabase", 3306, NULL, 0);

    }
    ~PostRepo() {
    }
	void addPost(Post post) {
		MYSQL_RES* result;
		MYSQL_ROW row;
		std::string str;
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
				Post post(row[0], string(row[1]), string(row[2]), string(row[3]));
				arr.push_back(post);
			}
		}
		mysql_free_result(result);
		return arr;
	}

	void deletePost(string id) {

		string qstr;
		qstr = "DELETE FROM posts WHERE id= '" + id + "'";
		mysql_query(conn, qstr.c_str());
	}
};