#pragma once
#include <iostream>
#include "accountService.h"
#include <conio.h>

class UI {

private:
    AccountService service;
    void signInaccount(string, string,int&);
    Account logInaccount(string,string,Account);
public:
    ~UI() {}
    UI(AccountService& service) :service(service) {}
    Account logIn(string,string, Account);
    void signIn(string, string,int &);
    std::string user_name();
    std::string password();
    void printMessage(Response);
    Account start_login();
    void admin_menu();
    void user_menu();
    void run_admin(Account);//functionalitati admin
    void run_user(Account);//functionalitati user
    void findUser();
    void post(Account);
    void updateUser();
    void printPosts(vector<Post>);
    void display_accounts();
    void findUser(string );
    void run() {
        Account account;
        do {
            account = this->start_login();
            system("cls");
            if (account.get_type()=="admin") {
                run_admin(account);
            }
            else {
                run_user(account);
            }
        } while (true);
    }
};