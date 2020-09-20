#pragma once
#include "Repository.h"
#include "Validator.h"
#include "ErrorMessages.h"
#include "PostRepository.h"

class AccountService {

private:
    Database* repo;
    PostRepo postrepo;
    Validator validator;

public:
    
    ~AccountService() {}
    AccountService(Database* repo,PostRepo& postrepo) :validator(repo),postrepo(postrepo) {
        this->repo = repo;
       // this->repo = new Repo();
       ///* this->repo = repo;
       // this->postrepo = postrepo;*/
    }

    Account login(std::string name, std::string pass,Account account) {

        Response message;
        account = this->validator.id_exist(name);
        if (name == account.get_name() and pass == account.get_pass()) {
            return account;
        }
        return Account();

    }

    Account signIn(std::string id, std::string pass,int& nr) {

        Response message;

        Account account = this->validator.id_exist(id);
        if (account.get_name()=="") {
            message.append("----------- Sign in successful -----------\n");
            repo->insertdata(id, pass,nr);
            return Account(to_string(nr),id,pass,"user");
           /* message.setSuccess(true);
            message.append("--Press 1 to have access to login\n ");
            message.append("--Press 0 to sing in \n ");
            return message;*/
        }
        else {
            /*message.append("----------------------");
            message.append("ID already exist ");
            message.append("----------------------");
            message.append("Try again (1) or sign in (0) \n");
            message.setSuccess(false);*/
            return Account();
        }
    }

    Account find_user(string name) {
        Response message;
        vector<Post>arr;
        Account account = repo->find_user(name);
        return account;
    }

    vector<Post> find_user_post(Account account) {
        return postrepo.find_user_posts(account);
    }

    void toPost(string title,string posting,Account account) {
        Post post("", account.get_id(), title, posting);
        this->postrepo.addPost(post);
    }

    void deleteUser(string user) {
        repo->deletedata(user);
    }

    void updateUser(Account account) {

        repo->updateuser(account);
    }

    vector<Account> display_users(){
        return repo->displaydata();
    }

    void deletePost(string id) {
        this->postrepo.deletePost(id);
    }
};