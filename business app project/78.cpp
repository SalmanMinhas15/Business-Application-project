#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <cctype>
using namespace std;
string security_key = "3120"; //  security key for admin
string option;
fstream file;
int counts = 0;    // for users which have been signed up
int itemCount = 0; // chk how many products have been entered
int sug_count = 0; // chk feedback counts

int empIdx = 0;   // no of employes
int saleIdx = 0;  //  sale 
void headerofApp();
void menuHeader();    
void setColor(int color)     // for color
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void resetColor()
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
string menu();    //  login page(Sign In  /  Sign up)
void invalidChoice();     
void signUpHeader();     
bool signUp(string name, string password, string role, string Name[], string Password[], string Role[]);
bool passwordchk(string password);    // chk is password 6 character
string adminInterface(); // user 1: Admin
void adminInterfacebody();   //  border
string staffInterface(); // submenu of admin user
void employelist(string empName[], int empAge[], int empSalary[]);
void addEmploye(string empName[], int empAge[], int empSalary[]);
bool isInteger(string input);       //   chk is strng integer
int getIntegerInput(string inputsrt);    // to assure the int input 
string stringLength(string str);     // chk whether input size is specified (small)
void removeEmploye(string empName[], int empAge[], int empSalary[], int SrNo);
string customerInterface(); // user 2 : customer
void customerinterfacebody();
void buyProduct(string item_name[], int item_quantity[], int item_price[], string sale_name[], int sale_quantity[], int sale_total[], string coupan, int discount);
void systemRecomendation(); // System recommnneded medicines if possible .(unique feature)
void recommendMedicines(string name, string gender, string array[], int sympCount);
void feedback(string suggestions[]); // feedback by user
string signIn(string name, string password, string Name[], string Password[], string Role[]);
void viewprofile(string Name[], string Password[], string Role[], string profile);// admin,Customrer can see profile
void signInAdminheader();    // header show after sign In
void signInCustomerheader(); // header show after sign In
void enterstock(string item_name[], int item_quantity[], int item_price[]);
void removeStock(string item_name[], int item_quantity[], int item_price[], int SrNo);
void viewStock(string item_name[], int item_quantity[], int item_price[]);
void updateStock(string item_name[], int item_quantity[], int item_price[], int SrNo);
void searchStock(string item_name[], int item_quantity[], int item_price[], string search_name);
void generateCoupan(string coupan, int discount);   // admin generate coupan code for discount
void viewfeedback(string suggestions[]);      // admin see feedbacks
void viewSale(string sale_name[], int sale_quantity[], int sale_total[]);
void logout();
void changePassword(string Name[], string Password[], string Role[]);  // admin and customer can change his password
void gotoxy(int x, int y);
void load(string Name[], string Password[], string Role[], string empName[], int empAge[], int empSalary[], string item_name[], int item_quantity[], int item_price[], string suggestions[],string sale_name[], int sale_quantity[], int sale_total[]);
string getField(string, int);    //  read data from file 
main()
{
  string Name[100];
  string Password[100];
  string Role[100];
  string item_name[100];       // stock
  int item_quantity[100];      //  stock quantity
  int item_price[100];        // stock price
  string empName[100];   
  int empAge[100];
  int empSalary[100];
  string sale_name[100];     // medicine name  (  sale record)
  int sale_quantity[100];    // sale record
  int sale_total[100];       // sale record
  string suggestions[100];   // feedbacks
  int SrNo;                  // for serial number
  string name, password, role, SI_name, SI_password;    // for sign In
  string profile = "", coupan;      // profile
  string itemName;  
  int itemQuantity, itemPrice;
  int discount;      
  
  load(Name, Password, Role, empName, empAge, empSalary, item_name, item_quantity, item_price, suggestions, sale_name, sale_quantity, sale_total);
  while (true)
  {
    system("cls");
    headerofApp();
    menuHeader();
    string menuOption = menu();
    if (menuOption == "1") // sign up
    {
      string s_key;
      system("cls");
      headerofApp();
      signUpHeader();
      // take input name, password, role;
      setColor(2);
      cout << "\n\tEnter Your Name: ";
      cin.ignore(0);
      getline(cin, name);
      while (true)     
      {
        cout << "\tEnter your Password (6 characters): ";
        getline(cin, password);
        bool isPasswordValid = passwordchk(password);    // chk is password 6 characters
        if (isPasswordValid)
        {
          while (true)
          {

            cout << "\tEnter Your role (A for Admin,C for Customer): ";
            getline(cin, role);
            if (role == "A" || role == "a")
            {
              while (true)
              {
                cout << "\tEnter Admin Security Key: ";
                getline(cin, s_key);
                if (s_key == security_key)     // chk security key (for admin only)
                {
                  break;
                }
                else
                {
                  cout << "\tInvalid Security Key " << endl;
                  Sleep(300);
                }
              }
              break;
            }
            if (role == "C" || role == "c")    // customer
            {
              break;
            }
            else
            {
              cout << "\tInvalid Entry ." << endl;
              Sleep(200);
            }
          }
          break;
        }
        else
        {
          cout << "\tInvalid Password ." << endl;
          Sleep(200);
        }
      }
      bool chkSignUp = signUp(name, password, role, Name, Password, Role);  //chk whether username already exists?
      if (chkSignUp)
      {
        Name[counts] = name;
        Password[counts] = password;
        Role[counts] = role;
        counts++;
        resetColor();
        setColor(4);
        cout << "\n\n\t\tSigned Up successfuly ...." << endl;
        resetColor();
        setColor(2);
        cout << "\t\tPress any key to continue .";
        resetColor();
        file.open("sign up.txt", ios::out);
        for (int i = 0; i < counts; i++)
        {
          file << Name[i] << "," << Password[i] << "," << Role[i] << endl;
        }
        file << endl;
        file.close();
        getch();
      }
      if (!chkSignUp)
      {
        setColor(4);
        cout << "\n\n\t\tThis username already exists ." << endl;
        resetColor();
        setColor(2);
        cout << "\t\tPress any key to continue ...";
        resetColor();
        getch();
      }
    }
    else if (menuOption == "2")     //  sign In
    {

      system("cls");
      headerofApp();

      gotoxy(10, 14);
      setColor(9);
      cout << "\t _                _         " << endl;
      cout << "\t| |    ___   __ _(_)_ __    " << endl;
      cout << "\t| |   / _ \\ / _` | | '_ \\   " << endl;
      cout << "\t| |__| (_) | (_| | | | | |  " << endl;
      cout << "\t|_____\\___/ \\__, |_|_| |_|  " << endl;
      cout << "\t            |___/            " << endl;
      resetColor();
      gotoxy(10, 23);
      setColor(2);
      cout << "Enter Your Name: ";
      cin.ignore(0);
      getline(cin, SI_name);
      profile = SI_name;
      gotoxy(10, 24);
      cout << "Enter your password: ";
      getline(cin, SI_password);
      resetColor();

      string chkSignIn = signIn(SI_name, SI_password, Name, Password, Role);
      if (chkSignIn == "Admin")
      {
        setColor(4);
        gotoxy(10, 26);
        cout << "Sign In sucsessfuly ...." << endl;
        resetColor();
        Sleep(300);
        while (true)
        {
          string adminOp = adminInterface();   //admin menu

          if (adminOp == "1")
          {
            while (true)
            {
              string staffOp = staffInterface();   // sub menu
              if (staffOp == "1")
              {
                signInAdminheader();
                setColor(11);
                cout << "\n\n\tMain Menu >> Staff Management >> View Employe List >>\n\n";
                resetColor();
                employelist(empName, empAge, empSalary);   //  list of all employees
                cout << "\n\n\tPress any key to back main menu   ";
                getch();
              }
              else if (staffOp == "2")
              {
                addEmploye(empName, empAge, empSalary);    //  enter employee record
              }
              else if (staffOp == "3")
              {
                removeEmploye(empName, empAge, empSalary, SrNo);   //  delete empoloye record
              }
              else if (staffOp == "4")   // logout
              {
                break;
              }
              else if (staffOp == "5")    //  exit
              {
                return 0;
              }
            }
          }
          else if (adminOp == "2")     // enter medicine stock
          {
            enterstock(item_name, item_quantity, item_price);
          }
          else if (adminOp == "3")    // view stock
          {
            signInAdminheader();
            setColor(11);
            cout << "\n\n\tMain Menu >> View Stock >>\n\n";
            resetColor();
            viewStock(item_name, item_quantity, item_price);
            cout << "\n\n\tPress any key to move main menu  ";
            getch();
          }
          else if (adminOp == "4")   //  delete stock record
          {
            removeStock(item_name, item_quantity, item_price, SrNo);
          }
          else if (adminOp == "5")   //   update price,quantity of stock
          {
            updateStock(item_name, item_quantity, item_price, SrNo);
          }
          else if (adminOp == "6")
          {
            string search_name;
            system("cls");
            headerofApp();
            signInAdminheader();
            setColor(11);
            cout << "\n\n\tMain Menu >> Search Stock (Medicine) >>" << endl;
            resetColor();
            setColor(2);
            cout << "\n\tEnter the name of Medicine :";
            getline(cin, search_name);
            searchStock(item_name, item_quantity, item_price, search_name);
            resetColor();
          }
          else if (adminOp == "7")   // admin place customer order
          {
            buyProduct(item_name, item_quantity, item_price, sale_name, sale_quantity, sale_total, coupan, discount);
          }
          else if (adminOp == "8")
          {
            generateCoupan(coupan, discount);    //   coupan for discount
          }
          else if (adminOp == "9")
          {
            viewfeedback(suggestions);
          }
          else if (adminOp == "10")
          {
            viewSale(sale_name, sale_quantity, sale_total);
          }
          else if (adminOp == "11")
          {
            changePassword(Name, Password, Role);  // admin change password
          }
          else if (adminOp == "12")
          {
            viewprofile(Name, Password, Role, profile);   // can view profile
          }
          else if (adminOp == "13")
          {
            logout();
            break;
          }
          else if (adminOp == "14")   // exit
          {
            return 0;
          }
        }
      }
      else if (chkSignIn == "Customer")    //  User 2:  Customer
      {
        Sleep(200);
        gotoxy(10, 26);
        setColor(4);
        cout << "Sign In sucsessfuly ...." << endl;
        resetColor();
        Sleep(300);
        gotoxy(0, 30);
        while (true)
        {
          string customer_Op = customerInterface();    // customer options
          if (customer_Op == "1")
          {
            signInAdminheader();
            setColor(11);
            cout << "\n\n\tMain Menu >> View Stock >>\n\n";
            resetColor();
            viewStock(item_name, item_quantity, item_price);
            cout << "\n\n\tPress any key to move main menu  ";
            getch();
          }
          else if (customer_Op == "2")
          {
            buyProduct(item_name, item_quantity, item_price, sale_name, sale_quantity, sale_total, coupan, discount);
          }
          else if (customer_Op == "3")
          {
            systemRecomendation();    // customer input symptoms to system and system suggest him medicines
          }
          else if (customer_Op == "4")
          {
            feedback(suggestions);   // customer record feedback
          }
          else if (customer_Op == "5")
          {
            changePassword(Name, Password, Role);
          }
          else if (customer_Op == "6")
          {
            viewprofile(Name, Password, Role, profile);
          }
          else if (customer_Op == "7")
          {
            cout<<endl;
            logout();
            break;
          }
          else if (customer_Op == "8")
          {
            return 0;
          }
        }
      }
      else if (chkSignIn == "invalid")    // if user is not signed up
      {
        setColor(4);
        cout << "\n\t\tYou are not registered .\n\t\tplease sign up first ." << endl;
        resetColor();
        setColor(2);
        cout << "\t\tPress any key to continue ....  ";
        resetColor();
        getch();
      }
      else if (chkSignIn == "password_incorrect")  // username is true but password is correct
      {
        setColor(4);
        gotoxy(10, 27);
        cout << "  Incorrect password" << endl;
        resetColor();
        Sleep(300);
        gotoxy(10, 28);
        setColor(2);
        cout << "Press any key to continue  ";
        resetColor();
        getch();
      }
      else if (chkSignIn == "wrong_username")  // password is correct but usrename is incorrect
      {
        setColor(4);
        gotoxy(10, 27);
        cout << "  Incorrect Username " << endl;
        resetColor();
        Sleep(300);
        gotoxy(10, 28);
        setColor(2);
        cout << "Press any key to continue  ";
        resetColor();
        getch();
      }
    }
    else if (menuOption == "3")  // exit the program
    {
      return 0;
    }
    else
    {
      gotoxy(73, 25);
      setColor(4);
      cout << "Invalid Choice .";
      resetColor();
      Sleep(300);
    }
  }
}
void gotoxy(int x, int y)
{
  COORD coordinates;
  coordinates.X = x;
  coordinates.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void invalidChoice()
{
  setColor(4);
  cout << "\tInvalid Choice .";
  Sleep(300);
  resetColor();
}
bool isInteger(string input)
{
  for (int i = 0; input[i] != '\0'; i++)
  {
    if (!isdigit(input[i]))
    {
      return false;
    }
  }
  return true;
}
int getIntegerInput(string inputstr)
{
  string input;
  while (true)
  {
    cout << inputstr;
    getline(cin, input);
    if (input.empty())
    {
      invalidChoice();
      cout << endl;
      setColor(2);
    }
    else if (input.length() >= 8)
    {
      setColor(4);
      cout << "\tInput length exceeded" << endl;
      resetColor();
      setColor(2);
    }
    else if (isInteger(input))
    {
      return stoi(input);
    }
    else
    {
      invalidChoice();
      cout << endl;
      setColor(2);
    }
  }
}
string stringLength(string str)
{
  string input;
  while (true)
  {
    cout << str;
    getline(cin, input);
    if (input.length() <= 20)
    {
      return input;
      break;
    }
    else
    {
      setColor(4);
      cout << "\tInput Length exceeded" << endl;
      resetColor();
      setColor(2);
    }
  }
}
void headerofApp()
{
  setColor(11);
  std::cout << "\n\n\n\n\n";
  cout << "     \t\t\t\t\t\t _    ____       ____  _   _    _    ____  __  __    _    ______   __    " << endl;
  cout << "\t\t\t\t\t\t   / \\  |  _ \\     |  _ \\| | | |  / \\  |  _ \\|  \\/  |  / \\  / ___\\ \\ / /      " << endl;
  cout << "\t\t\t\t\t\t  / _ \\ | |_) |    | |_) | |_| | / _ \\ | |_) | |\\/| | / _ \\| |    \\ V /     " << endl;
  cout << "\t\t\t\t\t\t / ___ \\|  _ <     |  __/|  _  |/ ___ \\|  _ <| |  | |/ ___ \\ |___  | |      " << endl;
  cout << "\t\t\t\t\t\t/_/   \\_\\_| \\_\\    |_|   |_| |_/_/   \\_\\_| \\_\\_|  |_/_/   \\_\\____| |_|      " << endl;

  resetColor();
}
string menu()
{
  string option;
  gotoxy(70, 18);
  cout << "\033[3;31m>>\033[0m \033[1;34m1. Sign Up.\033[0m" << endl;
  gotoxy(70, 20);
  cout << "\033[3;31m>>\033[0m \033[1;34m2. Sign In.\033[0m" << endl;
  gotoxy(70, 22);
  cout << "\033[3;31m>>\033[0m \033[1;34m3. Exit.\033[0m" << endl;
  gotoxy(70, 24);
  cout << "\033[3;31m>>\033[0m \033[1;34mYour Option ... \033[0m";
  setColor(6);
  getline(cin, option);
  resetColor();
  return option;
}
void menuHeader()
{
  int x = 49;
  int y = 14;
  setColor(1);
  gotoxy(x, y = y + 1);
  cout << "   _________________________________________________________________" << endl;
  gotoxy(x, y = y + 1);
  cout << "      __________________________________________________________    " << endl;
  gotoxy(x, y = y + 1);
  cout << "                                                                    " << endl;
  gotoxy(x, y = y + 1);
  cout << "                                                                    " << endl;
  gotoxy(x, y = y + 1);
  cout << "                                                                    " << endl;
  gotoxy(x, y = y + 1);
  cout << "                                                                    " << endl;
  gotoxy(x, y = y + 1);
  cout << "                                                                    " << endl;
  gotoxy(x, y = y + 1);
  cout << "                                                                    " << endl;
  gotoxy(x, y = y + 1);
  cout << "                                                                    " << endl;
  gotoxy(x, y = y + 1);
  cout << "                                                                    " << endl;
  gotoxy(x, y = y + 1);
  cout << "                                                                    " << endl;
  gotoxy(x, y = y + 1);
  cout << "      __________________________________________________________    " << endl;
  gotoxy(x, y = y + 1);
  cout << "   _________________________________________________________________" << endl;

  resetColor();
}
void signUpHeader()
{
  setColor(6);
  gotoxy(58, 14);
  cout << "-----------------------------------------------------" << endl;
  gotoxy(58, 15);
  cout << ".              Welcome to AR PHARMACY               ." << endl;
  gotoxy(58, 16);
  cout << "-----------------------------------------------------" << endl;
  resetColor();
  cout << endl;
  setColor(9);
  cout << "\t ____  _                  _   _ ____       " << endl;
  cout << "\t/ ___|(_) __ _ _ __      | | | |  _ \\      " << endl;
  cout << "\t\\___ \\| |/ _` | '_ \\     | | | | |_) |     " << endl;
  cout << "\t ___) | | (_| | | | |    | |_| |  __/      " << endl;
  cout << "\t|____/|_|\\__, |_| |_|     \\___/|_|         " << endl;
  cout << "\t         |___/                             " << endl;
  resetColor();
  cout << endl;
}
bool passwordchk(string password)
{
  if (password.length() == 6)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool signUp(string name, string password, string role, string Name[], string Password[], string Role[])
{
  for (int i = 0; i <= counts; i++)
  {
    if (name == Name[i])
    {
      return false;
      break;
    }
  }
  return true;
}
void signInAdminheader()
{
  system("cls");
  headerofApp();
  setColor(6);
  gotoxy(58, 15);
  cout << "-----------------------------------------------------" << endl;
  gotoxy(58, 16);
  cout << ".                      Admin                        ." << endl;
  gotoxy(58, 17);
  cout << "-----------------------------------------------------" << endl;
  resetColor();
}
void signInCustomerheader()
{
  system("cls");
  headerofApp();
  setColor(6);
  gotoxy(58, 15);
  cout << "-----------------------------------------------------" << endl;
  gotoxy(58, 16);
  cout << ".                     Customer                      ." << endl;
  gotoxy(58, 17);
  cout << "-----------------------------------------------------" << endl;
  resetColor();
}
string signIn(string SI_name, string SI_password, string Name[], string Password[], string Role[])
{
  for (int i = 0; i < counts; i++)
  {
    if (SI_name == Name[i] && SI_password == Password[i])
    {
      if (Role[i] == "A" || Role[i] == "a")
      {
        return "Admin";
        break;
      }
      else if (Role[i] == "C" || Role[i] == "c")
      {
        return "Customer";
        break;
      }
    }
    else if (SI_name == Name[i] && SI_password != Password[i])
    {
      return "password_incorrect";
      break;
    }
  }
  for (int i = 0; i < counts; i++)
  {
    if (SI_password == Password[i] && SI_name != Name[i])
    {
      return "wrong_username";
    }
  }
  return "invalid";
}
void viewprofile(string Name[], string Password[], string Role[], string profile)
{
  system("cls");
  headerofApp();
  setColor(11);
  cout << "\n\n\n\tView Profile >> \n"
       << endl;
  resetColor();
  setColor(6);
  for (int i = 0; i < counts; i++)
  {
    if (Name[i] == profile)
    {
      cout << "\n\t\t\t>> Username: " << profile << endl;
      cout << "\t\t\t>> Password: " << Password[i] << endl;
      if (Role[i] == "c")
      {
        cout << "\t\t\t>> Role    : Customer" << endl;
      }
      else
      {
        cout << "\t\t\t>> Role       : Admin" << endl;
      }
    }
  }
  resetColor();
  setColor(2);
  cout << "\n\tPress any key to continue    ";
  getch();
}
void adminInterfacebody(){
int x = 7;
  int y = 21;
setColor(4);
  gotoxy(x, y = y + 1);
  cout << "   ________________________________________________" << endl;
  gotoxy(x, y = y + 1);
  cout << "  |  ____________________________________________  |" << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |____________________________________________| |" << endl;
  gotoxy(x, y = y + 1);
  cout << "  |________________________________________________|" << endl;
  resetColor();
}
string adminInterface()
{
  while (true)
  {
    signInAdminheader();
    setColor(11);
    cout << "\n\n\t   Main Menu >>\n"
         << endl;
    resetColor();
    adminInterfacebody();
    setColor(6);
    int x=15,y=24;
    gotoxy(x, y = y + 1);
    cout << ">> 1. Staff Management" << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 2. Add stock (Products): " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 3. View stock: " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 4. Remove stock: " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 5. Update stock: " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 6. Search stock: " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 7. Customer Order: " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 8. Generate Coupan: " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 9. View Feedback of Customers: " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 10. View Sale  " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 11. Change Password  " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 12. View Profile  " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 13. Logout  " << endl;
    gotoxy(x, y = y + 1);
    cout << ">> 14. Exit  \n" << endl;
    resetColor();
    setColor(2);
    cout << "\t\t  Your option ...";
    getline(cin, option);
    resetColor();
    if (option == "1" || option == "2" || option == "3" || option == "4" || option == "5" || option == "6" || option == "7" || option == "8" || option == "10" || option == "9" || option == "11" || option == "12" || option == "13" || option == "14")
    {
      return option;
      break;
    }
    else
    {
      setColor(4);
      cout<<"\t\t            Invalid Entry";
      Sleep(100);
      resetColor();
      setColor(2);
    }
  }
}
string staffInterface()
{
  while (true)
  {
    signInAdminheader();
    setColor(11);
    cout << "\n\n\t\tMain Menu >> Staff Management >>\n\n"
         << endl;
    resetColor();
    setColor(4);
    cout << "\t\t=======================================\n"
         << endl;
    resetColor();
    setColor(6);
    cout << "\t\t\t1. View Employe list" << endl;
    cout << "\t\t\t2. Add Employe" << endl;
    cout << "\t\t\t3. Remove Employe" << endl;
    cout << "\t\t\t4. Go back to Main Menu " << endl;
    cout << "\t\t\t5. Exit\n"
         << endl;
    resetColor();
    setColor(4);
    cout << "\t\t======================================\n"
         << endl;
    resetColor();
    setColor(6);
    cout << "\t\t\t   Option :  ";
    getline(cin, option);
    resetColor();
    if (option == "1" || option == "2" || option == "3" || option == "4" || option == "5")
    {
      return option;
      break;
    }
    else
    {
      setColor(4);
      cout << "\n\t\t\t    Invalid Choice ";
      resetColor();
      Sleep(300);
    }
  }
}
void employelist(string empName[], int empAge[], int empSalary[])
{

  setColor(6);
  if (empIdx == 0)
  {
    cout << "\n\tNo Employes are in Lists ." << endl;
  }
  if (empIdx != 0)
  {
    cout << "\n\t________________________________________________________________________________\n"
         << endl;
    cout << "\t| Sr# |\tEmployee Name\t\t\t| Age\t\t\t| Salary\t|" << endl;
    cout << "\t|_____|_________________________________|_______________________|_______________|" << endl;
    cout << "\t|     |\t         \t\t\t|         \t\t|      \t\t|" << endl;
    int y = 28;
    for (int i = 0; i < empIdx; i++)
    {
      gotoxy(8, y);
      cout << "|";
      gotoxy(11, y);
      cout << i + 1;
      gotoxy(14, y);
      cout << "|";
      gotoxy(16, y);
      cout << empName[i];
      gotoxy(48, y);
      cout << "|";
      gotoxy(50, y);
      cout << empAge[i];
      gotoxy(72, y);
      cout << "|";
      gotoxy(74, y);
      cout << empSalary[i];
      gotoxy(88, y);
      cout << "|";
      y++;
    }
    cout << "\n\t________________________________________________________________________________" << endl;
  }
  resetColor();
  setColor(2);
}
void addEmploye(string empName[], int empAge[], int empSalary[])
{
  string name;
  signInAdminheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> Staff Management >> Add Employe >> \n\n"
       << endl;
  resetColor();
  setColor(2);

  empName[empIdx] = stringLength("\tEnter Employe name :");

  empAge[empIdx] = getIntegerInput("\tEnter Employe Age: ");
  empSalary[empIdx] = getIntegerInput("\tEnter Employe Salary: ");
  cout << "\n\n\tEmployee added Successfuly " << endl;
  empIdx++;
  file.open("employee data.txt", ios::out);
  for (int i = 0; i < empIdx; i++)
  {
    file << empName[i] << "," << empAge[i] << "," << empSalary[i] << endl;
  }
  file.close();
  cout << "\tPress any key to continue    ";
  getch();
  resetColor();
}
void removeEmploye(string empName[], int empAge[], int empSalary[], int SrNo)
{
  signInAdminheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> Staff Management >> Remove Employe >>\n\n";
  resetColor();
  employelist(empName, empAge, empSalary);cout<<endl;
  setColor(2);
  SrNo = getIntegerInput("\tEnter serial number of Employe which you want to remove: ");
  if (SrNo > 0 && SrNo <= empIdx)
  {
    for (int i = SrNo - 1; i < empIdx; i++)
    {
      empName[i] = empName[i + 1];
      empAge[i] = empAge[i + 1];
      empSalary[i] = empSalary[i + 1];
    }
    empIdx--;
    cout << "\n\n\tEmploye removed successfuly ." << endl;
  }
  else
  {
    invalidChoice();
    cout << endl;
    setColor(2);
  }
  remove("employee data.txt");
  file.open("employee data.txt", ios ::out);
  for (int i = 0; i < empIdx; i++)
  {
    file << empName[i] << "," << empAge[i] << "," << empSalary[i] << endl;
  }
  file.close();
  cout << "\tPress any key to back main menu .";
  getch();
  resetColor();
}
void customerinterfacebody(){
  int x = 7;
  int y = 21;
setColor(4);
gotoxy(x, y = y + 1);
  cout << "   ________________________________________________" << endl;
  gotoxy(x, y = y + 1);
  cout << "  |  ____________________________________________  |" << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |                                            | |  " << endl;
  gotoxy(x, y = y + 1);
  cout << "  | |____________________________________________| |" << endl;
  gotoxy(x, y = y + 1);
  cout << "  |________________________________________________|" << endl;
}
string customerInterface()
{
  while (true)
  {
    signInCustomerheader();
    setColor(11);
    cout << "\n\n\t  Main Menu >>\n"
         << endl;
    resetColor();
    customerinterfacebody();
    setColor(6);
    int x=15,y=24;
    gotoxy(x, y = y + 1);
    cout << "\t>>  1. View Stock " << endl;
    gotoxy(x, y = y + 1);
    cout << "\t>>  2. Buy Product (Medicines)" << endl;
    gotoxy(x, y = y + 1);
    cout << "\t>>  3. System Recommended Medicine" << endl;
    gotoxy(x, y = y + 1);
    cout << "\t>>  4. Feedback" << endl;
    gotoxy(x, y = y + 1);
    cout << "\t>>  5. Change Password " << endl;
    gotoxy(x, y = y + 1);
    cout << "\t>>  6. View Profile " << endl;
    gotoxy(x, y = y + 1);
    cout << "\t>>  7. Logout " << endl;
    gotoxy(x, y = y + 1);
    cout << "\t>>  8. Exit" <<endl;
    resetColor();
   setColor(2);
    cout << "\n\t\t  Your Option   ";
    getline(cin, option);
    resetColor();
    if (option == "1" || option == "2" || option == "3" || option == "4" || option == "5" || option == "6" || option == "7" || option == "8")
    {
      return option;
      break;
    }
    else
    {
      setColor(4);
      cout<<"\n\t\t   Invalid entry";
      resetColor();
      Sleep(150);
    }
  }
}
void buyProduct(string item_name[], int item_quantity[], int item_price[], string sale_name[], int sale_quantity[], int sale_total[], string coupan, int discount)
{
  signInCustomerheader();
  string prod_name, prod_quan;
  setColor(11);
  cout << "\n\n\tMain Menu >> Buy Product >>" << endl;
  resetColor();
  setColor(2);
  cout << "\n\tEnter Product (Medicine) Name : ";
  getline(cin, prod_name);
  bool chk_name = false;
  for (int i = 0; i < itemCount; i++)
  {
    if (prod_name == item_name[i])
    {
      chk_name = true;
      break;
    }
  }
  if (!chk_name)
  {
    cout << "\n\n\tSorry this Medicine is not avalaible in Stock ." << endl;
    cout << "\tPress any key to continue .";
    getch();
  }
  if (itemCount != 0)
  {
    for (int i = 0; i < itemCount; i++)
    {
      if (prod_name == item_name[i])
      {
        int buy_quantity;
        buy_quantity = getIntegerInput("\tEnter Quantity: ");
        if (buy_quantity <= item_quantity[i])
        {
          char ch;
          string choice, code;
          int ntotal = buy_quantity * item_price[i];
          cout << "\n\tTotal : " << ntotal << " /" << endl;
          if (ntotal > discount)
          {
            while (true)
            {
              cout << "\tUse Coupan for discount (y/n): ";
              getline(cin, choice);
              if (choice == "y" || choice == "Y")
              {
                cout << "\tEnter Coupan Code: ";
                getline(cin, code);
                if (code == coupan)
                {
                  ntotal -= discount;
                  cout << "\tTotal after discount: " << ntotal << endl;
                  break;
                }
                else
                {
                  cout << "\tInavlid Coupan code " << endl;
                }
              }
              else if (choice == "n" || choice == "N")
              {
                break;
              }
              else
              {
                cout << "\tInvalid choice" << endl;
                Sleep(300);
              }
            }
          }
          cout << "\tEnter 1 to Buy Medicine  " << endl;
          cout << "\tPress any key to exit    ";
          ch = getch();
          if (ch == '1')
          {
            cout << "\n\n\tThanks for buying Medicine .\n\tWish you a nice day " << endl;
            item_quantity[i] = item_quantity[i] - buy_quantity;
            sale_name[saleIdx] = item_name[i];
            sale_quantity[saleIdx] = buy_quantity;
            sale_total[saleIdx] = ntotal;
            saleIdx++;
            file.open("sale.txt", ios::out);
            for (int i = 0; i < saleIdx; i++)
            {
              file << sale_name[i] << "," << sale_quantity[i] << "," << sale_total[i] << endl;
            }
            file.close();
            remove("stock data.txt");
            file.open("stock data.txt", ios::out);
            for (int i = 0; i < itemCount; i++)
            {
              file << item_name[i] << "," << item_quantity[i] << "," << item_price[i] << endl;
            }
            file.close();
            cout << "\tPress any key to move main menu   ";
            getch();
            break;
          }
          else
          {
            exit(0);
          }
        }
        else
        {
          cout << "\n\n\tSorry ! Maximum available Stock of this Medicine is " << item_quantity[i] << " ." << endl;
          cout << "\tPress any key to back mainmenu  ";
          getch();
          break;
        }
        break;
      }
    }
  }
  resetColor();
}

void systemRecomendation()
{
  signInCustomerheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> System Recomanded Medicines >>\n"
       << endl;
  resetColor();
  setColor(2);
  string customerName, customerGender, symptom;
  string symp_array[5];
  int sympCount = 0;
  cout << "\tEnter your name: ";
  getline(cin, customerName);
  cout << "\tEnter your gender: ";
  getline(cin, customerGender);
  cout << "\tEnter your Disease Symptoms : " << endl;
  string choice;
  while (true)
  {
    cout << "\tSymptom : ";
    getline(cin, symptom);
    symp_array[sympCount] = symptom;
    sympCount++;
    cout << "\tPress 'y' for more symptom or 'n' for no more: ";
    getline(cin, choice);
    if (choice == "Y" || choice == "y")
    {
      continue;
    }
    else if (choice == "N" || choice == "n")
    {
      break;
    }
    else
    {
      cout << "\tInvalid Choice  " << endl;
    }
  }
  cout << "\n";
  recommendMedicines(customerName, customerGender, symp_array, sympCount);
  cout << "\n\tPress any key to back main menu  ";
  getch();
  resetColor();
}
void recommendMedicines(string name, string gender, string symp_array[], int sympCount)
{
  int count = 0;
  for (int i = 0; i < sympCount; i++)
  {
    if (symp_array[i] == "pain" || symp_array[i] == "Pain")
    {
      cout << "\tDiclorane" << endl;
      count++;
    }
    if (symp_array[i] == "fever" || symp_array[i] == "Fever")
    {
      cout << "\tPanadol\n\tNims" << endl;
      count++;
    }
    if (symp_array[i] == "flu" || symp_array[i] == "Flu")
    {
      cout << "\tDisprene\n\tboflam" << endl;
      count++;
    }
    if (symp_array[i] == "vomting" || symp_array[i] == "Vomting")
    {
      cout << "\tAntacid" << endl;
      count++;
    }
    if (symp_array[i] == "headache" || symp_array[i] == "Headache")
    {
      cout << "\tBesoquin\n\ttonoflex" << endl;
      count++;
    }
    if (symp_array[i] == "Cough" || symp_array[i] == "cough")
    {
      cout << "\tCough Syrup" << endl;
      count++;
    }
    if (symp_array[i] == "bodyache" || symp_array[i] == "Bodyache")
    {
      cout << "\tIbuprofen\n\tPanadol Extra" << endl;
      count++;
    }

    if (symp_array[i] == "sorethroat" || symp_array[i] == "Sorethroat")
    {
      cout << "\tThroat Lozenges\n\tCepacol" << endl;
      count++;
    }

    if (symp_array[i] == "diarrhea" || symp_array[i] == "Diarrhea")
    {
      cout << "\tImodium\n\tORS Solution" << endl;
      count++;
    }

    if (symp_array[i] == "constipation" || symp_array[i] == "Constipation")
    {
      cout << "\tFiber Supplement\n\tLaxative" << endl;
      count++;
    }

    if (symp_array[i] == "shortnessofbreath" || symp_array[i] == "Shortnessofbreath")
    {
      cout << "\tInhaler\n\tBronchodilator" << endl;
      count++;
    }
  }
  if (count == 0)
  {
    cout << "\tSorry, I am unable to recommend you. Please consult a doctor.";
  }
}
void feedback(string suggestions[])
{
  signInCustomerheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> Feedback >>" << endl;
  resetColor();
  setColor(2);
  cout << "\n\tEnter your message : ";
  getline(cin, suggestions[sug_count]);
  sug_count++;
  file.open("feedback.txt", ios::out);
  for (int i = 0; i < sug_count; i++)
  {
    file << suggestions[i] << endl;
  }
  file.close();
  cout << "\n\n\tYour Feedback has been submitted ." << endl;
  cout << "\tPress any key to continue  ";
  getch();
}
void enterstock(string item_name[], int item_quantity[], int item_price[])
{
  signInAdminheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> Add Stock (Medicines) >>\n\n"
       << endl;
  resetColor();
  setColor(2);
  item_name[itemCount] = stringLength("\tProduct (Medicine) name: ");
  item_quantity[itemCount] = getIntegerInput("\tEnter Quantity: ");
  item_price[itemCount] = getIntegerInput("\tEnter price: ");
  itemCount++;
  file.open("stock data.txt", ios::out);
  for (int i = 0; i < itemCount; i++)
  {
    file << item_name[i] << "," << item_quantity[i] << "," << item_price[i] << endl;
  }
  file.close();
  Sleep(200);
  cout << "\n\n\tProduct added to Stock.\n";
  cout << "\tPress any key to back main menu." << endl;
  getch();
  resetColor();
}
void removeStock(string item_name[], int item_quantity[], int item_price[], int SrNo)
{
  signInAdminheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> Remove Stock >>\n\n";
  resetColor();
  viewStock(item_name, item_quantity, item_price);
  cout << endl;
  setColor(2);
  SrNo = getIntegerInput("\tEnter serial number of product which you want to remove: ");
  if (SrNo > 0 && SrNo <= itemCount)
  {
    for (int i = SrNo - 1; i < itemCount; i++)
    {
      item_name[i] = item_name[i + 1];
      item_quantity[i] = item_quantity[i + 1];
      item_price[i] = item_price[i + 1];
    }
    itemCount--;
    cout << "\n\n\tItem removed ." << endl;
  }
  else 
  {
    invalidChoice();cout<<endl;
    setColor(2);
  }
  remove("stock data.txt");
  file.open("stock data.txt", ios::out);
  for (int i = 0; i < itemCount; i++)
  {
    file << item_name[i] << "," << item_quantity[i] << "," << item_price[i] << endl;
  }
  file.close();
  cout << "\tPress any key to back main menu ";
  getch();
  resetColor();
}
void viewStock(string item_name[], int item_quantity[], int item_price[])
{
  if (itemCount == 0)
  {
    setColor(6);
    cout << "\tNo Avalaible Stock ." << endl;
    resetColor();
  }
  else if (itemCount != 0)
  {
    setColor(6);
    cout << "\n\t________________________________________________________________________________\n"
         << endl;
    cout << "\t| Sr# |\tDrug Name\t\t\t| Quantity\t\t| Price\t\t|" << endl;
    cout << "\t|_____|_________________________________|_______________________|_______________|" << endl;
    cout << "\t|     |\t         \t\t\t|         \t\t|      \t\t|" << endl;
    int y = 28;
    for (int i = 0; i < itemCount; i++)
    {
      gotoxy(8, y);
      cout << "|";
      gotoxy(11, y);
      cout << i + 1;
      gotoxy(14, y);
      cout << "|";
      gotoxy(16, y);
      cout << item_name[i];
      gotoxy(48, y);
      cout << "|";
      gotoxy(50, y);
      cout << item_quantity[i];
      gotoxy(72, y);
      cout << "|";
      gotoxy(74, y);
      cout << item_price[i];
      gotoxy(88, y);
      cout << "|";
      y++;
    }
    cout << "\n\t________________________________________________________________________________" << endl;
    resetColor();
  }
  setColor(2);
}
void updateStock(string item_name[], int item_quantity[], int item_price[], int SrNo)
{
  string new_name;
  int new_quant, new_price;
  system("cls");
  headerofApp();
  signInAdminheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> Update Stock >>\n\n";
  resetColor();
  setColor(6);
  if (itemCount == 0)
  {
    cout << "\tNo Avalaible Stock ." << endl;
  }
  else if (itemCount != 0)
  {
    viewStock(item_name, item_quantity, item_price);
    cout << endl;
    setColor(2);
    SrNo = getIntegerInput("\tEnter serial number of product which you want to update: ");
    if (SrNo > 0 && SrNo <= itemCount)
    {
      cout << "\n\tEnter New Name of Drug :";
      getline(cin, new_name);
      item_name[SrNo - 1] = new_name;
      new_quant = getIntegerInput("\tEnter new Quantity: ");
      item_quantity[SrNo - 1] = new_quant;
      new_price = getIntegerInput("\tEnter new price: ");
      item_price[SrNo - 1] = new_price;
      cout << "\n\tStock Updated ." << endl;
      remove("stock data.txt");
      file.open("stock data.txt", ios::out);
      for (int i = 0; i < itemCount; i++)
      {
        file << item_name[i] << "," << item_quantity[i] << "," << item_price[i] << endl;
      }
      file.close();
    }
  else
  {
    invalidChoice();cout<<endl;
    setColor(2);
  }
  }
  cout << "\tPress any key to back main menu   ";
  getch();
  resetColor();
}
void searchStock(string item_name[], int item_quantity[], int item_price[], string search_name)
{
  setColor(6);
  bool result = false;
  for (int i = 0; i < itemCount; i++)
  {
    if (search_name == item_name[i])
    {
      cout << "\n\tYes ! " << item_name[i] << " is in Stock ." << endl;
      cout << "\tThe quantity is " << item_quantity[i] << " and Price of one tablet is " << item_price[i] << " ." << endl;
      result = true;
      break;
    }
  }
  if (result)
  {
    cout << "\n";
  }
  else
  {
    cout << "\n\t" << search_name << " not found in Stock ." << endl;
  }
  resetColor();
  setColor(2);
  cout << "\n\n\tPress any key to back main menu  ";
  getch();
}
void generateCoupan(string coupan, int discount)
{
  system("cls");
  headerofApp();
  signInAdminheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> Generate Coupan >> \n"
       << endl;
  resetColor();
  setColor(2);
  coupan = stringLength("Generate Coupan code: ");
  discount = getIntegerInput("\tEnter Discount for Coupan: ");
  cout << "\n\tCoupan have generated" << endl;
  cout << "\tPress any key to continue   ";
  cin.ignore();
  getch();
  resetColor();
}
void viewfeedback(string suggestions[])
{
  signInAdminheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> View Feedback >>\n"
       << endl;
  resetColor();
  setColor(6);
  if (sug_count == 0)
  {
    cout << "\n\tNo Feedback yet ." << endl;
  }
  
  
  for (int i = 0; i < sug_count; i++)
  {
    cout << "\t" << i + 1 << ". " << suggestions[i] << endl;
  }
  
  resetColor();
  setColor(2);
  cout << "\n\tPress any key to back main menu  ";
  getch();
  resetColor();
}
void viewSale(string sale_name[], int sale_quantity[], int sale_total[])
{
  signInAdminheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> View Sale >>\n"
       << endl;
  resetColor();
  if (saleIdx == 0)
  {
    setColor(6);
    cout << "\t\t\tNo Sale Record ." << endl;
    resetColor();
  }
  else if (saleIdx != 0)
  {
     setColor(6);
    cout << "\n\t________________________________________________________________________________\n"
         << endl;
    cout << "\t| Sr# |\tDrug Name\t\t\t| Quantity\t\t| Total\t\t|" << endl;
    cout << "\t|_____|_________________________________|_______________________|_______________|" << endl;
    cout << "\t|     |\t         \t\t\t|         \t\t|      \t\t|" << endl;
    int y = 28;
    for (int i = 0; i < itemCount; i++)
    {
      gotoxy(8, y);
      cout << "|";
      gotoxy(11, y);
      cout << i + 1;
      gotoxy(14, y);
      cout << "|";
      gotoxy(16, y);
      cout << sale_name[i];
      gotoxy(48, y);
      cout << "|";
      gotoxy(50, y);
      cout << sale_quantity[i];
      gotoxy(72, y);
      cout << "|";
      gotoxy(74, y);
      cout << sale_total[i];
      gotoxy(88, y);
      cout << "|";
      y++;
    }
    cout << "\n\t________________________________________________________________________________" << endl;
    resetColor();
  }
  setColor(2);
  cout << "\n\n\tPress any key to main menu   ";
  getch();
  resetColor();
}
void changePassword(string Name[], string Password[], string Role[])
{
  system("cls");
  headerofApp();
  signInAdminheader();
  setColor(11);
  cout << "\n\n\tMain Menu >> Change Password >>\n"
       << endl;
  resetColor();
  setColor(2);
  string name, password, new_password;
  cout << "\tEnter Username: ";
  getline(cin, name);
  cout << "\tEnter your Old Password: ";
  getline(cin, password);
  cout << "\tEnter New Password: ";
  getline(cin, new_password);
  bool passwordfound = false;
  for (int i = 0; i < counts; i++)
  {
    if (name == Name[i] && password == Password[i])
    {
      Password[i] = new_password;
      cout << "\n\tPassword changed ." << endl;
      passwordfound = true;
      remove("sign up.txt");
      file.open("sign up.txt", ios::out);
      for (int i = 0; i < counts; i++)
      {
        file << Name[i] << "," << Password[i] << "," << Role[i] << endl;
      }
      file.close();
      break;
    }
  }
  if (!passwordfound)
  {
    cout << "\n\tSomething went wrong " << endl;
  }
  cout << "\tPress any key to continue   ";
  getch();
}
void logout()
{
  setColor(6);
  cout << "\t\t  Loging out";
  for (int i = 0; i < 5; i++)
  {
    cout<<". ";
    Sleep(100);
  }
  resetColor();
}
void load(string Name[], string Password[], string Role[], string empName[], int empAge[], int empSalary[], string item_name[], int item_quantity[], int item_price[], string suggestions[], string sale_name[], int sale_quantity[], int sale_total[])
{
  string line = "";
  file.open("sign up.txt", ios::in);
  while (!file.eof())
  {
    getline(file, line);
    if (line == "")
    {
      break;
    }

    Name[counts] = getField(line, 0);
    Password[counts] = (getField(line, 1));
    Role[counts] = (getField(line, 2));
    counts++;
  }
  file.close();
  file.open("employee data.txt", ios::in);
  while (!file.eof())
  {
    getline(file, line);
    if (line == "")
    {
      break;
    }
    empName[empIdx] = getField(line, 0);
    empAge[empIdx] = stoi(getField(line, 1));
    empSalary[empIdx] = stoi(getField(line, 2));
    empIdx++;
  }
  file.close();
  file.open("stock data.txt", ios::in);
  while (!file.eof())
  {
    getline(file, line);
    if (line == "")
    {
      break;
    }
    item_name[itemCount] = getField(line, 0);
    item_quantity[itemCount] = stoi(getField(line, 1));
    item_price[itemCount] = stoi(getField(line, 2));
    itemCount++;
  }
  file.close();
  file.open("feedback.txt", ios::in);
  while (!file.eof())
  {
    getline(file, line);
    if (line == "")
    {
      break;
    }
    suggestions[sug_count] = line;
    sug_count++;
  }
  file.close();
  file.open("sale.txt", ios::in);
  while (!file.eof())
  {
    getline(file, line);
    if (line == "")
    {
      break;
    }
    sale_name[saleIdx] = getField(line, 0);
    sale_quantity[saleIdx] = stoi(getField(line, 1));
    sale_total[saleIdx] = stoi(getField(line, 2));
    saleIdx++;
  }
  file.close();
}
string getField(string record, int field)
{
  int commaCount = 0;
  string content = "";
  char comma = ',';

  for (int i = 0; i < record.length(); i++)
  {
    if (record[i] == comma)
    {
      commaCount++;
    }
    else if (commaCount == field)
    {
      content += record[i];
    }
  }
  return content;
}
