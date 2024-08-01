#include "Login.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "pageDisplayer.h"
#include "Game.h"
#include "Dictionary.h"

int state = 0;
// Function prototypes
void errorAct();
void registerAct();
void loginAct();
void exitAct();
void loginActAdm();
void aboutAct();

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int getConsoleWidth() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
#endif
}

std::string hideInput() {
    std::string str;

    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == 8) {
            if (!str.empty()) {
                str.pop_back();
                std::cout << "\b \b";
            }
        }
        else {
            str.push_back(ch);
            std::cout << '*';
        }
    }
    return str;
}

void Login::registeruser() {
    clrscr();
    fflush(stdin);
    set_Color(0, 3);
    registerAccount();
    gotoxy(74, 5); std::cin >> username;
    gotoxy(74, 8);
    std::cin.ignore(); // Clear newline character
    userpw = hideInput();
    gotoxy(75, 12);
    std::getline(std::cin, full_name);
    full_name.erase(std::remove_if(full_name.begin(), full_name.end(), ::isspace), full_name.end());
    gotoxy(69, 15); std::cin >> age;
    gotoxy(71, 18);
    std::cin.ignore(); // Clear newline character
    std::getline(std::cin, email);
}

void Login::edit_User() {
    clrscr();
    fflush(stdin);
    set_Color(0, 3);
    editAccount();

    gotoxy(74, 5);
    std::cin.ignore(); // Clear newline character
    userpw = hideInput();
    gotoxy(75, 9);
    std::getline(std::cin, full_name);
    full_name.erase(std::remove_if(full_name.begin(), full_name.end(), ::isspace), full_name.end());
    gotoxy(69, 12); std::cin >> age;
    gotoxy(71, 15);
    std::cin.ignore(); // Clear newline character
    std::getline(std::cin, email);
}

void Login::loginuser() {
    clrscr();
    fflush(stdin);
    set_Color(0, 3);
    loginAccount();
    gotoxy(85, 5); std::cin >> username;
    gotoxy(85, 8);
    std::cin.ignore(); // Clear newline character
    userpw = hideInput();
}

void Login::loginadmin() {
    clrscr();
    fflush(stdin);
    set_Color(0, 3);
    loginAdmin();
    gotoxy(85, 5); std::cin >> username;
    gotoxy(85, 8);
    std::cin.ignore(); // Clear newline character
    userpw = hideInput();
}

void Login::searchUser(const std::string& searchTerm) {
    std::ifstream fin("./data/logindata.txt");
    Login user;
    bool found = false;

    while (fin >> user.username >> user.userpw >> user.full_name >> user.age >> user.email) {
        if (user.username == searchTerm || user.email == searchTerm) {
            displayUserInfo(user);
            found = true;
        }
    }

    fin.close();

    if (!found) {
        set_Color(0, 4);
        set_Mode();
        std::wcout << std::endl << std::setw(94) << L"User not found!" << std::endl << std::endl;
        reset_Mode();
        set_Color(0, 7);
    }
}

void Login::addUserToFile(const Login& newUser) {
    std::ifstream fin("./data/logindata.txt");
    Login existingUser;

    // Kiểm tra xem tài khoản đã tồn tại chưa
    while (fin >> existingUser.username >> existingUser.userpw >> existingUser.full_name >> existingUser.age >> existingUser.email) {
        if (existingUser.username == newUser.username || existingUser.email == newUser.email) {
            fin.close();
            set_Color(0, 4);
            set_Mode();
            std::wcout << "\n";
            std::wcout << std::endl << std::setw(66) << L"Error:";
            std::wcout << std::endl << std::setw(117) << L"Username or email already exists. Please choose another!\n";
            reset_Mode();
            set_Color(0, 7);
            return; // Không thêm tài khoản nếu đã tồn tại
        }
    }

    fin.close();

    // Nếu không trùng, thì thêm tài khoản vào tệp
    std::ofstream fout("./data/logindata.txt", std::ios::app);
    fout << newUser.username << " " << newUser.userpw << " " << newUser.full_name << " " << newUser.age << " " << newUser.email << std::endl;
    fout.close();
    set_Color(0, 2);
    set_Mode();
    std::wcout << std::endl << std::endl << std::endl << std::setw(99) << L"User added successfully.\n";
    reset_Mode();
    set_Color(0, 7);
}

void Login::editUser(const std::string& username, Login& updatedUser) {
    std::ifstream fin("./data/logindata.txt");
    std::ofstream fout("./data/temp.txt");

    Login user;
    bool updated = false;

    while (fin >> user.username >> user.userpw >> user.full_name >> user.age >> user.email) {
        if (user.username == username) {
            // Nếu tài khoản tồn tại, thì thực hiện chỉnh sửa
            fflush(stdin);
            updatedUser.edit_User();
            fout << username << " " << updatedUser.userpw << " " << updatedUser.full_name << " " << updatedUser.age << " " << updatedUser.email << std::endl;
            updated = true;
        }
        else {
            fout << user.username << " " << user.userpw << " " << user.full_name << " " << user.age << " " << user.email << std::endl;
        }
    }

    fin.close();
    fout.close();

    if (updated) {
        std::remove("./data/logindata.txt");
        std::rename("./data/temp.txt", "./data/logindata.txt");
        set_Color(0, 2);
        set_Mode();
        std::wcout << L"\n" << L"\n";
        std::wcout << std::setw(110) << L"User information updated successfully.\n";
        reset_Mode();
        set_Color(0, 7);
    }
    else {
        set_Color(0, 4);
        set_Mode();
        std::wcout << std::endl << std::setw(97) << L"Error: User not found.\n";
        reset_Mode();
        set_Color(0, 7);
    }
}

void Login::deleteUser(const std::string& usernameToDelete) {
    std::ifstream fin("./data/logindata.txt");
    std::ofstream fout("./data/temp.txt");

    Login user;
    bool deleted = false;

    while (fin >> user.username >> user.userpw >> user.full_name >> user.age >> user.email) {
        if (user.username == usernameToDelete) {
            // Nếu tài khoản tồn tại, thì không sao chép nó vào tệp mới
            deleted = true;
        }
        else {
            fout << user.username << " " << user.userpw << " " << user.full_name << " " << user.age << " " << user.email << std::endl;
        }
    }

    fin.close();
    fout.close();

    if (deleted) {
        std::remove("./data/logindata.txt");
        std::rename("./data/temp.txt", "./data/logindata.txt");
        set_Color(0, 2);
        set_Mode();
        std::wcout << L"\n" << L"\n";
        std::wcout << std::setw(100) << L"User deleted successfully.\n";
        reset_Mode();
        set_Color(0, 7);
    }
    else {
        set_Color(0, 4);
        set_Mode();
        std::wcout << std::endl << std::setw(97) << L"Error: User not found.\n";
        reset_Mode();
        set_Color(0, 7);
    }
}

void Login::displayUserInfo(const Login& user) {
    const int fieldWidth = 20;
    const int separatorWidth = 5;

    // Lấy độ rộng của màn hình console
    int consoleWidth = getConsoleWidth();

    // Tính toán vị trí bắt đầu để canh giữa
    int startColumn = 66;

    // Hiển thị thông tin người dùng
    std::cout << std::setw(startColumn) << "" << std::setw(fieldWidth) << std::left << "       o-----------------------o \n";
    std::cout << std::setw(startColumn) << "" << std::setw(fieldWidth) << std::left << "       |  INFORMATION ACCOUNT  |\n";
    std::cout << std::setw(startColumn) << "" << std::setw(fieldWidth) << std::left << "       o-----------------------o \n\n";
    std::cout << std::setw(startColumn) << "" << std::setw(fieldWidth) << std::left << "Username:" << std::setw(separatorWidth) << "" << std::setw(fieldWidth * 2) << user.username << "\n";
    std::cout << std::setw(startColumn) << "" << std::setw(fieldWidth) << std::left << "Full Name:" << std::setw(separatorWidth) << "" << std::setw(fieldWidth * 2) << user.full_name << "\n";
    std::cout << std::setw(startColumn) << "" << std::setw(fieldWidth) << std::left << "Age:" << std::setw(separatorWidth) << "" << std::setw(fieldWidth * 2) << user.age << "\n";
    std::cout << std::setw(startColumn) << "" << std::setw(fieldWidth) << std::left << "Email:" << std::setw(separatorWidth) << "" << std::setw(fieldWidth * 2) << user.email << "\n";
}

void Login::listUsers() {
    system("cls");
    std::ifstream fin("./data/logindata.txt");

    Login user;
    int count = 0;

    // In header của bảng
    std::cout << std::setw(20) << std::left << "Username" << std::setw(25) << std::left << "Full Name" << std::setw(10) << std::left << "Age" << std::setw(30) << std::left << "Email";
    std::cout << std::setfill('-') << std::setw(85) << "\n" << std::setfill(' ') << "\n";

    // In thông tin người dùng
    while (fin >> user.username >> user.userpw >> user.full_name >> user.age >> user.email) {
        std::cout << std::setw(20) << std::left << user.username << std::setw(25) << std::left << user.full_name << std::setw(10) << std::left << user.age << std::setw(30) << std::left << user.email << "\n";
        count++;
    }

    fin.close();

    if (count == 0) {
        std::cout << "No users found.\n";
    }
    else {
        std::cout << "\nTotal users: " << count << "\n";
    }
}


// Function to check if a file is empty
bool Login::is_empty(std::ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}

// Exit the program
void exitAct() {
    set_Color(0, 3);
    exitScreen();
}

// Error handling for wrong option selected
void errorAct() {
    clrscr();
    int ch1;
    errorPage();
    ch1 = pickMenu1();
    if (ch1 == 1) {
        startAct();
    }
    else {
        exitAct();
    }
}

// Register new user
void registerAct() {
    Login l;
    std::fstream fout;

    //int ch;
    clrscr();
    //registerPage();
    //cin >> ch;
    //switch (ch) {
    //case 1:
    try {
        // Making an account
        fout.open("./data/logindata.txt", std::ios::app);
        clrscr();
        // Input new user data
        l.registeruser();

        // Check for existing username redundancy
        std::ifstream fin("./data/logindata.txt");
        if (fin) {
            Login existingUser;
            while (fin >> existingUser.username >> existingUser.userpw >> existingUser.full_name >> existingUser.age >> existingUser.email) {
                if (existingUser.username == l.username) {
                    fin.close();
                    std::cout << std::endl << std::endl;
                    set_Color(0, 4);
                    throw std::runtime_error("\n\t\t\t\t\t\t\t   Username already exists. Please choose another username.");
                    set_Color(0, 3);

                }
            }
            fin.close();
        }

        // Register the new user
        fout << l.username << " " << l.userpw << " " << l.full_name << " " << l.age << " " << l.email << " " << std::endl;
        fout.close();
        set_Color(0, 2);
        set_Mode();
        std::wcout << std::endl << std::endl << std::endl << std::setw(89) << L"User Registered Successfully!\n";
        reset_Mode();
        set_Color(0, 3);
    }
    catch (const std::exception& e) {
        // Handle the exception (existing username)
        std::cerr << std::endl << std::setw(66) << " Error: " << e.what() << std::endl;
    }
    set_Color(0, 3);
    set_Mode();
    std::wcout << std::endl << std::setw(86) << L"You may login to continue:\n";
    std::wcout << std::setw(85) << L"| Press 1: Register Again\n";
    std::wcout << std::setw(81) << L"| Press 2: Start Page\n";
    std::wcout << std::setw(81) << L"| Press 3: Login Page\n";
    reset_Mode();
    //std::cout << std::endl << std::setw(82) << "Please enter your choice : ";
    set_Color(0, 7);
    //std::cin >> ch;
    int a;
    a = pickMenu1();
    if (a == 1) {
        registerAct();
    }
    else if (a == 2) {
        startAct();
    }
    else if (a == 3) {
        loginAct();
    }
    else {
        errorAct();
    }
    /*switch (ch) {
    case 1:
        registerAct();
        break;
    case 2:
        startAct();
        break;
    case 3:
        loginAct();
        break;
    default:
        errorAct();
    }*/
    //break;
/*case 2:
    loginAct();
    break;

case 3:
    startAct();
    break;

default:
    errorAct();
}*/
}

// Login activity for user
void loginAct() {
    //Dictionary application;
    Game game;
    Dictionary application;
    std::ifstream fin;
    Login t;
    int check;

    clrscr();
    // Verify user and take to dashboard
    // Run a loop to verify but at eof() ask to make an ID
    Login l;
    t.loginuser();
    fin.open("./data/logindata.txt");

    while (fin >> l.username >> l.userpw >> l.full_name >> l.age >> l.email) {
        if (l.username == t.username) {
            if (l.userpw == t.userpw) {
                ::state = 1;
                gotoxy(56, 14);
                set_Color(0, 2);
                set_Mode();
                std::wcout << std::setw(38) << L"Verified user!";
                std::wcout << std::endl << std::setw(101) << L"Press any key to continue...";
                pause();
                reset_Mode();
                set_Color(0, 15);
                break;
            }
            else {
                ::state = 2;
                set_Color(0, 4);
                set_Mode();
                std::wcout << std::endl << std::endl << std::endl << std::setw(74) << L"Wrong password"; // Forgot password action can be added
                reset_Mode();
                set_Color(0, 3);
                break;
            }
        }
    }

    if (::state == 1) {
    ACCOUNT_USER:
        clrscr();
        fflush(stdin);
        userSelection_4();
        int userSelection = pickMenu1();
        if (userSelection == 1) {
        SEARCH_VOCAB:
            set_Mode();
            application.searchWordInDictionary();
            set_Color(0, 3);
            std::wcout << std::endl << std::endl << std::setw(89) << L"--++----------++--" << std::endl;
            std::wcout << std::setw(89) << std::endl << L"| Press 1 to continue." << std::endl;
            std::wcout << std::setw(93) << L"| Press 2 to back to menu." << std::endl;
            set_Color(0, 7);
            check = pickMenu1();
            if (check == 1)
                goto SEARCH_VOCAB;
            if (check == 2) {
                reset_Mode();
                goto ACCOUNT_USER;
            }

        }
        else if (userSelection == 2) {
            set_Mode();
            game.playGame(t.username);
            clrscr();
            //application.updateToFile();
            reset_Mode();
        }
        if (userSelection == 3) {
            fflush(stdin);
            reset_Mode();
            startAct();
        }

    }

    if (::state == 0 || ::state == 2) {
        if (::state == 0) {
            set_Color(0, 4);
            set_Mode();
            std::wcout << std::endl << std::endl << std::endl << std::setw(87) << L"No user found! Try again...";
            reset_Mode();
            set_Color(0, 3);
        }

        if (::state == 2) {
            set_Color(0, 4);
            set_Mode();
            std::wcout << std::endl <<  std::setw(80) << L"Please! Try again...";
            reset_Mode();
            set_Color(0, 3);
        }
        set_Mode();
        std::wcout << std::endl;
        std::wcout << std::endl << std::setw(83) << L"| Press 1: Login Again\n";
        std::wcout << std::setw(85) << L"| Press 2: Register Page\n";
        std::wcout << std::setw(82) << L"| Press 3: Start Page\n";
        std::wcout << std::setw(76) << L"| Press 4: Exit\n";
        reset_Mode();
        //std::cout << std::endl << std::setw(82) << "Please enter your choice : ";
        set_Color(0, 15);
        //std::cin >> ch;
        int a;
        a = pickMenu1();
        if (a == 1) {
            ::state = 0;
            loginAct();
        }
        else if (a == 2) {
            ::state = 0;
            registerAct();
        }
        else if (a == 3) {
            ::state = 0;
            startAct();
        }
        else if (a == 4) {
            ::state = 0;
            exitAct();
        }
        else {
            ::state = 0;
            errorAct();
        }
    }
}

// Admin management program
void loginActAdm() {
    int ch;
    Login l;
    clrscr();
    // Verify admin and take to admin dashboard (temporary method)
    l.loginadmin();
    if (l.username == "admin" && l.userpw == "12345") { // Temporary admin password
        set_Color(0, 2);
        std::wcout << std::endl << std::endl << std::endl << std::endl << std::setw(108) << L"Logged in! Redirecting to admin dashboard...\n";
        std::wcout << std::setw(91) << L"Press any key to continue...";
        pause();
        set_Color(0, 15);
        Word temp;
        int check;
        Dictionary application;

    MENU:
        system("cls");
        fflush(stdin);
        userSelection_1();
        int userSelection = pickMenu1();
        if (userSelection == 1) {
            set_Mode();
        DICTIONARY_SETTING:
            system("cls");
            fflush(stdin);
            userSelection_2();
            int userSelection1 = pickMenu1();
            if (userSelection1 == 1) {
            SEARCH:
                application.searchWordInDictionary();
                set_Color(0, 3);
                std::wcout << std::endl << std::endl << std::setw(89) << L"--++----------++--" << std::endl;
                std::wcout << std::setw(89) << std::endl << L"| Press 1 to continue." << std::endl;
                std::wcout << std::setw(93) << L"| Press 2 to back to menu." << std::endl;
                set_Color(0, 7);
                check = pickMenu1();
                if (check == 1)
                    goto SEARCH;
                if (check == 2) {

                    goto DICTIONARY_SETTING;
                }

            }
            else if (userSelection1 == 2) {
            ADD:
                application.addNewWordToDictionary();
                set_Color(0, 3);
                std::wcout << std::endl << std::endl << std::setw(89) << L"--++----------++--" << std::endl;
                std::wcout << std::setw(89) << std::endl << L"| Press 1 to continue." << std::endl;
                std::wcout << std::setw(93) << L"| Press 2 to back to menu." << std::endl;
                set_Color(0, 7);
                check = pickMenu1();
                if (check == 1)
                    goto ADD;
                if (check == 2) {

                    goto DICTIONARY_SETTING;
                }
            }
            else if (userSelection1 == 3) {
            DEL:
                application.delWordFromDictionary();
                set_Color(0, 3);
                std::wcout << std::endl << std::endl << std::setw(89) << L"--++----------++--" << std::endl;
                std::wcout << std::setw(89) << std::endl << L"| Press 1 to continue." << std::endl;
                std::wcout << std::setw(93) << L"| Press 2 to back to menu." << std::endl;
                set_Color(0, 7);
                check = pickMenu1();
                if (check == 1)
                    goto DEL;
                if (check == 2) {

                    goto DICTIONARY_SETTING;
                }
            }
            else if (userSelection1 == 4) {
            EDIT:
                application.editWordInDictionary();
                set_Color(0, 3);
                std::wcout << std::endl << std::endl << std::setw(89) << L"--++----------++--" << std::endl;
                std::wcout << std::setw(89) << std::endl << L"| Press 1 to continue." << std::endl;
                std::wcout << std::setw(93) << L"| Press 2 to back to menu." << std::endl;
                set_Color(0, 7);
                check = pickMenu1();
                if (check == 1)
                    goto EDIT;
                if (check == 2) {

                    goto DICTIONARY_SETTING;
                }
            }
            if (userSelection1 == 5) {
                fflush(stdin);
                reset_Mode();
                goto MENU;
            }
        }
        else if (userSelection == 2) {
            reset_Mode();
        ACCOUNT_SETTING:
            system("cls");
            fflush(stdin);
            userSelection_3();
            int userSelection2 = pickMenu1();
            if (userSelection2 == 1) {
            SEARCH_USER:
                system("cls");
                std::string searchTerm;
                set_Mode();
                std::wcout << std::setw(98) << std::endl << std::endl << L"<<===== SEARCHING =====>>" << std::endl;
                std::wcout << std::setw(100) << std::endl << L"Enter username or email to search: ";
                reset_Mode();
                std::cin >> searchTerm;
                Login::searchUser(searchTerm);
                frame();
                check = pickMenu1();
                if (check == 1)
                    goto SEARCH_USER;
                if (check == 2)
                {

                    goto ACCOUNT_SETTING;
                }
            }
            else if (userSelection2 == 2) {
            ADD_USER:
                system("cls");
                Login newUser;
                //std::wcout << "Enter new user details:\n";
                //cin.ignore();
                newUser.registeruser();
                Login::addUserToFile(newUser);
                frame();
                check = pickMenu1();
                if (check == 1)
                    goto ADD_USER;
                if (check == 2)
                {
                    goto ACCOUNT_SETTING;
                }
            }
            else if (userSelection2 == 3) {
            EDIT_USER:
                system("cls");
                std::string usernameToEdit;
                set_Mode();
                std::wcout << std::setw(96) << std::endl << std::endl << L"<<===== EDITING =====>>" << std::endl;
                std::wcout << std::setw(98) << std::endl << std::endl << L"Enter username to edit: ";
                reset_Mode();
                std::cin >> usernameToEdit;
                Login updatedUser;
                Login::editUser(usernameToEdit, updatedUser);
                frame();
                check = pickMenu1();
                if (check == 1)
                    goto EDIT_USER;
                if (check == 2)
                {
                    goto ACCOUNT_SETTING;
                }
            }
            else if (userSelection2 == 4) {
            DELETE_USER:
                system("cls");
                std::string usernameToDelete;
                set_Mode();
                std::wcout << std::setw(96) << std::endl << std::endl << L"<<===== DELETING =====>>" << std::endl;
                std::wcout << std::setw(98) << std::endl << std::endl << L"Enter username to delete: ";
                reset_Mode();
                std::cin >> usernameToDelete;
                Login::deleteUser(usernameToDelete);
                frame();
                check = pickMenu1();
                if (check == 1)
                    goto DELETE_USER;
                if (check == 2)
                {
                    goto ACCOUNT_SETTING;
                }

            }
            else if (userSelection2 == 5) {
            LIST_USER:
                system("cls");
                Login::listUsers();
                set_Color(0, 3);
                set_Mode();
                std::wcout << std::endl << std::endl << L"--++----------++--" << std::endl;
                std::wcout << L"| Press 1 to continue." << std::endl;
                std::wcout << L"| Press 2 to back to menu." << std::endl;
                reset_Mode();
                set_Color(0, 7);
                check = pickMenu1();
                if (check == 1)
                    goto LIST_USER;
                if (check == 2)
                {
                    goto ACCOUNT_SETTING;
                }
            }
            if (userSelection2 == 6) {
                fflush(stdin);
                reset_Mode();
                goto MENU;
            }
        }
        if (userSelection == 3) {
            /*set_Mode();
            application.updateToFile();
            reset_Mode();
            clrscr();
            set_Color(0, 2);
            set_Mode();
            std::wcout << std::endl << std::endl << std::endl << std::endl << std::setw(108) << L"Waiting for updating data...\n";
            std::wcout << std::setw(99) << L"Successfully saved!\n";
            reset_Mode();
            pause();
            set_Color(0, 3);
            exitAct();*/
            set_Mode();
            application.updateToFile();
            fflush(stdin);
            reset_Mode();
            startAct();
        }
    }
    else {
        set_Color(0, 4);
        set_Mode();
        std::wcout << std::endl << std::endl << std::endl << std::endl << std::setw(67) << "Error:";
        std::wcout << std::endl << std::setw(106) << L"Access denied! Please check your credentials.";
        set_Color(0, 3);
        std::wcout << std::endl << std::endl << std::setw(83) << "| Press 1: Login again\n";
        std::wcout << std::setw(85) << L"| Press 2: Register Page\n";
        std::wcout << std::setw(82) << L"| Press 3: Start Page\n";
        std::wcout << std::setw(79) << L"| Press 4: To Exit\n";
        reset_Mode();
        int a = pickMenu1();
        if (a == 1) {
            loginActAdm();
        }
        else if (a == 2) {
            registerAct();
        }
        else if (a == 3) {
            startAct();
        }
        else if (a == 4) {
            exitAct();
        }
        else {
            errorAct();
        }
    }
}

// Start/home page
void startAct() {
    int ch;
    clrscr();
    startPage();
    ch = pickMenu1();

    if (ch == 1) {
        registerAct();
    }

    else if (ch == 2) {
        loginAct();
    }

    else if (ch == 3) {
        loginActAdm();
    }

    else if (ch == 4) {
        aboutAct();
    }
    else if (ch == 5) {
        exitAct();
    }

    else {
        errorAct();
    }
}

// About page
void aboutAct() {
    int ch;
    clrscr();
    aboutPage();
    ch = pickMenu1();
    if (ch == 1)
        startAct();
    else if (ch == 2)
        exitAct();
    else
        errorAct();
}