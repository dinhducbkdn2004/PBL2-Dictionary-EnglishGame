#ifndef LOGIN_H
#define LOGIN_H
#include <iostream>

class Login {
public:
    std::string username;
    std::string userpw;
    std::string full_name;
    int age;
    std::string email;

    void registeruser();
    void edit_User();
    void loginuser();
    void loginadmin();

    static void searchUser(const std::string& searchTerm);
    static void addUserToFile(const Login& newUser);
    static void editUser(const std::string& username, Login& updatedUser);
    static void deleteUser(const std::string& usernameToDelete);
    static void displayUserInfo(const Login& user);
    static void listUsers();

    bool is_empty(std::ifstream& pFile);
};

void startAct();
#endif // !LOGIN_H
