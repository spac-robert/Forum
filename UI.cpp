#include "UI.h"

void UI::signInaccount(string name, string pass,int &id) {

   Account account = this->service.signIn(name, pass, id);
   Response message;
   if(account.get_name()==name){
       message.append("----------- Sign in successful -----------\n");
       message.setSuccess(true);
   }
   else {
       message.append("Username is taken\n");
       message.setSuccess(false);
   }
    printMessage(message);
    //return account;
}

Account UI::logInaccount(string name,string pass,Account account1){

    Account account = this->service.login(name, pass, account1);
    Response message;
    if (account.get_name() != "") {
        message.append("----------- Login successful -----------\n");
        message.setSuccess(true);
    }
    else {
        message.append("Login fail\n");
        message.setSuccess(false);
    }
    printMessage(message);
    return account;
}


std::string UI::user_name() {

    std::cout << "ID: ";
    std::string id;
    std::cin >> id;
    std::cout << std::endl;

    return id;
}

std::string UI::password() {

    std::cout << "Password: ";
    char* s = new char[10];
    int n = 0, x;
    int i;
    i = 0;
    while (i < 18) {
        x = _getch();
        if (x != 13 and x != 8) {
            s[n++] = x;
            _putch('*');
            i++;
        }
        else
            if (x == 8 and n > 0)
            {
                s[n--];
                _putch('\b');
                _putch(' ');
                _putch('\b');
                i--;
            }
            else
                if (x == 8 and i > 0)
                    i--;
                else
                    if (x == 13)
                        i = 18;

    }

    std::string str;
    str.resize(n);
    for (i = 0; i < n; i++)
        str[i] = s[i];
    return str;
}

void UI::printMessage(Response message) {

    std::vector<std::string> messages = message.getAll();

    for (int i = 0; i < int(messages.size()); i++) {
        std::cout << std::endl << messages[i] << ' ';
    }
}
Account UI::logIn(string name,string pass,Account account) {
    return this->logInaccount(name,pass,account);
}

void UI::signIn(string name, string pass,int & id) {
    this->signInaccount(name,pass,id);
}

Account UI::start_login() {
    Account account;
    int opt;
    vector<Account>arr = service.display_users();
    int id = stoi(arr[int(arr.size())-1].get_id());
    string type;
    std::cout << "----You need to loggin to have access----" << std::endl;
    do {
        std::cout << "  --Press 1 to have access to login" << std::endl << "  --Press 0 to sing in" << std::endl;
        cin >> opt;
        if (opt == 1) {
            system("cls");
            std::cout << std::endl << std::endl << "----------- Login -----------" << std::endl;
            std::string name = user_name();
            std::string pass = password();
            system("cls");
            account = this->logIn(name, pass,account);
            if (account.get_name()!="") {
                return account;
            }
            system("pause");
            system("cls");
        }
        else
            if (opt == 0) {
                system("cls");
                std::cout << std::endl << "----------- Sing in -----------" << std::endl;
                std::string name = user_name();
                std::string pass = password();
                system("cls");
                id = id + 1;
                this->signIn(name, pass,id);
                system("pause");
                system("cls");
            }
    } while (true);
}

void UI::admin_menu() {
    cout << "--------- Admin Menu ---------\n";
    cout << "0.Exit\n";
    cout << "1.Search users by id\n";
    cout << "2.Post\n";
    cout << "3.Delete user\n";
    cout << "4.Delete post\n";
    cout << "5.Update user type\n";
    cout << "6.Show all\n";
}

void UI::user_menu() {
    cout << "--------- User Menu ---------\n";
    cout << "0.Exit\n";
    cout << "1.Search users by id\n";
    cout << "2.Post\n";
    cout << "3.Delete post\n";
    cout << "4.Show all\n";
}

void UI::printPosts(vector<Post> arr) {

    int i = 0;
    for (i = 0; i<int(arr.size()); i++) {
        cout << arr[i]<<"\n";
    }
}

void UI::findUser() {
    string name;
    cout << "Name: ";
    cin >> name;
    Account account = service.find_user(name);
    if (account.get_name() == name)
        printPosts(service.find_user_post(account));
    else
        cout << "User does not exist\n";
}
void UI::findUser(string name) {
    
    Account account = service.find_user(name);
    if (account.get_name() == name)
        printPosts(service.find_user_post(account));
    else
        cout << "User does not exist\n";
}

void UI::post(Account account) {
    string title, posting;
    cout << "Title: \n";
    cin >> title;
    cout << "Post: \n";
    cin >> posting;
    this->service.toPost(title, posting,account);
}

void UI::display_accounts() {
    vector<Account>arr = service.display_users();
    for (int i = 0; i<int(arr.size()); i++) {
        cout << arr[i];
    }
}

void UI::updateUser() {

    this->display_accounts();
    string name;
    cout << "User: ";
    cin >> name;
    Account account = service.find_user(name);
    if (account.get_name() == name) {
        service.updateUser(account);
    }
    else
        cout << "User does not exist!";
}

void UI::run_admin(Account account) {
    int opt;
    do {
        this->admin_menu();
        cin >> opt;
        if (opt == 1) {
            this->findUser();
            system("pause");
            system("cls");
        }
        if (opt == 2) {
            this->post(account);
            system("pause");
            system("cls");
        }
        if (opt == 3) {
            string user;
            cout << "User: ";
            cin >> user;
            this->service.deleteUser(user);
            cout << "\nDone\n";
            system("pause");
            system("cls");
        }
        if (opt == 4) {
            this->display_accounts();
            this->findUser();
            cout << "Delete post with ID: ";
            string id;
            cin >> id;
            this->service.deletePost(id);
            cout << "\nDone\n";
            system("pause");
            system("cls");
        }
        if (opt == 5) {
            this->updateUser();
            system("pause");
            system("cls");
        }
        if (opt == 6) {
            this->display_accounts();
            system("pause");
            system("cls");
        }
    } while (opt);
    system("cls");
}

void UI::run_user(Account account) {
    int opt;
    do {
        this->user_menu();
        cin >> opt;
        if (opt == 1) {
            this->findUser();
            system("pause");
            system("cls");
        }
        if (opt == 2) {
            this->post(account);
            system("pause");
            system("cls");
        }
        if (opt == 3) {
            this->findUser(account.get_name());
            cout << "Delete post with ID: ";
            string id;
            cin >> id;
            this->service.deletePost(id);
            system("pause");
            system("cls");
        }
        if (opt == 4) {
            this->display_accounts();
            system("pause");
            system("cls");
        }
    } while (opt);
    system("cls");
}