#pragma once
#include "Repository.h"

class Validator {

private:
    Database* repo{};
public:
    ~Validator() {}
    Validator(Database* repo) {
        this->repo = repo;
    }

    Account id_exist(std::string id) {
        return repo->find_user(id);
    }

};