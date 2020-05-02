#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include<conio.h>
using namespace std;

const string FILE_OF_PASSWORLD = "Accounts.txt";

//const string LINE = "                                ==================================================================";
//const string 
//
//            cout << "                                ==================================================================" << endl;
//            cout << "                                |                          |Enter the system|                    |" << endl;
//            cout << "                                |                      1 - account login                         |" << endl;
//            cout << "                                |                      2 - account registration                  |" << endl;
//            cout << "                                |                      0 - exit                                  |" << endl;
//            cout << "                                                       ->";
//
//            cout << "                                ================================================================== " << endl;
//            cout << "                                |                    This is not in the menu!                    | " << endl;
//            cout << "                                ================================================================== " << endl;
//
//            cout << "                                  ================================================================" << endl;
//            cout << "                                  |                         Enter password                       |" << endl;
//            cout << "                                                       ->";
//
//cout << "                                  ================================================================" << endl;
//cout << "                                  |                          Invalid password                    |" << endl;
//
//cout << "                                 =================================================================" << endl;
//cout << "                                 |                    Please, enter login                        |" << endl;
//cout << "                                 =================================================================" << endl;
//cout << "                                                       ->";
//
//cout << "                                ==================================================================" << endl;
//cout << "                                |  This login is entered incorrectly or the login does not exist |" << endl;
//cout << "                                ==================================================================" << endl;
//
//cout << "                              ==============================================================================";
//
//cout << "                                ==================================================================" << endl;
//cout << "                                           This login already exists! Enter another               " << endl;
//cout << "                                                       ->";
//
//cout << "                                ==================================================================" << endl;
//cout << "                                           Login size does not meet the requirement!              " << endl;
//cout << "                                                           Enter again!                           " << endl;
//cout << "                                                      -> ";
//
//cout << "                                ==================================================================" << endl;
//cout << "                                |                Enter password (5 symbols minimum )             |" << endl;
//cout << "                                                       ->";
//
//cout << endl;
//cout << "                                ==================================================================" << endl;
//cout << "                                |      Password does not meet the requirement! Enter again       |" << endl;
//cout << "                                                       ->";
//
//cout << "                                ==================================================================" << endl;
//cout << "                                |                       Re-enter the password                    |" << endl;
//cout << "                                                       ->";
//
//cout << "                                ==================================================================" << endl;
//cout << "                                |                 Password mismatch! Enter again                 |" << endl;
//
//cout << "                                ================================================================" << endl;
//cout << "                                |       Enter the login name of the account you want to change |" << endl;
//cout << "                                        ->";
//

struct Accounts
{
	string login;
	string password;
	int role;                 //0-admin 1-user 2-visitor
	int access;               //0-working condition 1-in the waiting state
};

int get_size_of_array();
void readFile(Accounts* arr_of_accounts, int& number_of_accounts);
Accounts* menu_of_authorization(Accounts* arr_of_accounts, int& number_of_accounts);
int letter_protection();
void login(Accounts* arr_of_accounts, int& number_of_accounts);
string password();
int enter_login(bool& correct_login, string login, Accounts* arr_of_accounts, int& number_of_accounts);
bool chose_of_action(bool& correct_login, Accounts* arr_of_accounts, int& number_of_accounts);
void menu(Accounts* arr_of_accounts, int& number_of_accounts, int role);
Accounts* getRememberForArray(Accounts* arr_of_accounts, int& number_of_accounts, int new_number);
void Add_an_account(Accounts* arr_of_accounts, int& number_of_accounts);
void menu(Accounts* arr_of_accounts, int& number_of_accounts, int role);
void admin_menu(Accounts* arr_of_accounts, int& number_of_accounts);
void Account_management(Accounts* arr_of_accounts, int& number_of_accounts);
void ToViewTheAccounts(Accounts* arr_of_accounts, int& number_of_accounts);
void EditAnAccounts(Accounts* arr_of_accounts, int& number_of_accounts);
string Change_login(Accounts* arr_of_accounts, int& number_of_accounts);
string Change_password();
void Change_role_or_access(Accounts* arr_of_accounts, int& number_of_accounts, bool role, int& i);
void DeleteAccount(Accounts* arr_of_accounts, int& number_of_accounts);
void WriteNewArrayInFile(Accounts* arr_of_accounts, int& number_of_accounts);

int main()
{
	int number_of_accounts = get_size_of_array();
	Accounts* arr_of_accounts = new Accounts[number_of_accounts];
	readFile(arr_of_accounts, number_of_accounts);
	arr_of_accounts = menu_of_authorization(arr_of_accounts, number_of_accounts);
	WriteNewArrayInFile(arr_of_accounts, number_of_accounts);
	delete[] arr_of_accounts;
	return 0;
}

int get_size_of_array()
{
	int number = 0;
	string str;
	ifstream fin(FILE_OF_PASSWORLD, ios::in);
	if (fin.is_open())
	{
		while (getline(fin, str))
		{
			number++;
		}
	}
	else
	{
		number = 1;
	}
	fin.close();
	return number;
}

void readFile(Accounts* arr_of_accounts, int& number_of_accounts)
{

	if (number_of_accounts == 1)
	{
		ofstream fout(FILE_OF_PASSWORLD);         //open file for writing
		if (!fout.is_open())
		{
			cout << "File opening error" << endl;
			return;
		}
		else
		{
			cout << "                                ================================================================" << endl;
			cout << "                                |     Standart admin account: Login - admin Password - admin    |" << endl;
			cout << "                                ================================================================" << endl;
			arr_of_accounts[0].login = "admin";
			arr_of_accounts[0].password = "admin";
			arr_of_accounts[0].role = 0;
			arr_of_accounts[0].access = 0;

			fout << arr_of_accounts[0].login << '\t' << arr_of_accounts[0].password << '\t' << arr_of_accounts[0].role << '\t' << arr_of_accounts[0].access << endl;
		}
		fout.close();
	}
	else
	{
		ifstream fin(FILE_OF_PASSWORLD, ios::in);       //open file for reading
		while (!fin.eof())
		{
			for (int i = 0; i < number_of_accounts; i++)
			{
				fin >> arr_of_accounts[i].login >> arr_of_accounts[i].password >> arr_of_accounts[i].role >> arr_of_accounts[i].access;

				cout << arr_of_accounts[i].login << arr_of_accounts[i].password << arr_of_accounts[i].role << arr_of_accounts[i].access << endl;
			}
		}
		fin.close();
	}
}

Accounts* menu_of_authorization(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int choise;
	bool flag = true;
	while (flag)
	{
		cout << "                                ==================================================================" << endl;
		cout << "                                |                          |Enter the system|                    |" << endl;
		cout << "                                |                      1 - account login                         |" << endl;
		cout << "                                |                      2 - account registration                  |" << endl;
		cout << "                                |                      0 - exit                                  |" << endl;
		cout << "                                                       ->";
		choise = letter_protection();

		switch (choise)
		{
		case 1:login(arr_of_accounts, number_of_accounts);
			break;
		case 2: arr_of_accounts = getRememberForArray(arr_of_accounts, number_of_accounts, number_of_accounts + 1);
			Add_an_account(arr_of_accounts, number_of_accounts);
			break;
		case 0: flag = false;
			break;
		default: cout << "                                ================================================================== " << endl;
			cout << "                                |                    This is not in the menu!                    | " << endl;
			cout << "                                ================================================================== " << endl;
			break;
		}
	}
	return arr_of_accounts;
}

int letter_protection()
{
	int number;

	while (!(cin >> number))
	{
		cout << "                                 =================================================================" << endl;
		cout << "                                 |                   Value must be a number!                     |" << endl;
		cout << "                                 =================================================================" << endl;
		cout << "                                                         ->";
		cin.clear();
		cin.ignore(256, '\n');
	}
	return number;
}

void login(Accounts* arr_of_accounts, int& number_of_accounts)
{
	bool correct_login = true;
	int right_login;
	string login;
	right_login = enter_login(correct_login, login, arr_of_accounts, number_of_accounts);
	while (correct_login)
	{
		cout << "                                  ================================================================" << endl;
		cout << "                                  |                         Enter password                       |" << endl;
		cout << "                                                       ->";
		if (password() == arr_of_accounts[right_login].password)
		{
			if (arr_of_accounts[right_login].access == 0)
			{
				menu(arr_of_accounts, number_of_accounts, arr_of_accounts[right_login].role);
				correct_login = false;
			}
			else
			{
				system("cls");
				cout << "       *****Account is temporarily deactivated!Wait for confirmation of the account by the administrator.*****" << endl;
				cout << endl;
				correct_login = false;
			}
		}
		else
		{
			system("cls");
			cout << "                                  ================================================================" << endl;
			cout << "                                  |                          Invalid password                    |" << endl;
			correct_login = chose_of_action(correct_login, arr_of_accounts, number_of_accounts);
		}
	}
}
string password()
{
	string password;
	int p;

	while (true)
	{
		p = _getch();

		if (p == 13)
		{
			break;
		}
		else
			if (p == 8)
			{
				cout << (char)8 << ' ' << (char)8;
				if (!password.empty())
					password.erase(password.length() - 1);
			}

			else
			{
				cout << "*";
				password += (char)p;
			}

	}
	return password;
}

int enter_login(bool& correct_login, string login, Accounts* arr_of_accounts, int& number_of_accounts)
{
	bool invalid_login = true;
	int right_login = NULL;
	while (correct_login)
	{
		cout << "                                 =================================================================" << endl;
		cout << "                                 |                    Please, enter login                        |" << endl;
		cout << "                                 =================================================================" << endl;
		cout << "                                                       ->";
		cin >> login;
		for (int i = 0; i < number_of_accounts; i++)
		{
			if (login == arr_of_accounts[i].login)
			{
				right_login = i;
				invalid_login = true;
				break;
			}
			else
			{
				invalid_login = false;
			}
		}
		if (invalid_login == false)
		{
			system("cls");
			cout << "                                ==================================================================" << endl;
			cout << "                                |  This login is entered incorrectly or the login does not exist |" << endl;
			cout << "                                ==================================================================" << endl;
			correct_login = chose_of_action(correct_login, arr_of_accounts, number_of_accounts);
		}
		else
		{
			break;
		}
	}
	return right_login;
}

bool chose_of_action(bool& correct_login, Accounts* arr_of_accounts, int& number_of_accounts)
{
	int choice;
	cout << "                                                   *******CHOSE AN ACTION******* " << endl;
	cout << "                                                          1 - Enter again        " << endl;
	cout << "                                                          0 - exit               " << endl;
	cout << "                                                       ->";
	choice = letter_protection();
	switch (choice)
	{
	case 1:
		correct_login = true;
		break;
	case 0:
		system("cls");
		correct_login = false;
		break;
	default:cout << "                                              !!!!!!!!! Invalid input !!!!!!!!!" << endl;
		break;
	}
	return correct_login;
}

Accounts* getRememberForArray(Accounts* arr_of_accounts, int& number_of_accounts, int new_number)
{
	Accounts* arr_new;
	if (number_of_accounts < new_number)
	{
		arr_new = new Accounts[new_number];           //create new array
		for (int i = 0; i < number_of_accounts; i++)
		{                                             //rewriting old data into a new array
			arr_new[i].login = arr_of_accounts[i].login;
			arr_new[i].password = arr_of_accounts[i].password;
			arr_new[i].role = arr_of_accounts[i].role;
			arr_new[i].access = arr_of_accounts[i].access;
		}
		for (int i = number_of_accounts; i < new_number; i++)  //create new elements of array
		{
			arr_new[i].login = '0';
			arr_new[i].password = '0';
			arr_new[i].role = 0;
			arr_new[i].access = 0;
		}
		delete[]arr_of_accounts;      //delete old array
		arr_of_accounts = arr_new;
		number_of_accounts = new_number;
	}
	return arr_of_accounts;        //return new array
}

void menu(Accounts* arr_of_accounts, int& number_of_accounts, int role)
{
	if (role == 0)
	{
		system("cls");
		cout << "                                  ================================================================" << endl;
		cout << "                                  |                    Welcome, admin!                           |" << endl;
		admin_menu(arr_of_accounts, number_of_accounts);
	}
	else
		if (role == 1)
		{
			system("cls");
			cout << "                                  ================================================================" << endl;
			cout << "                                  |                   Welcome, user!                             |" << endl;
			//menuUser();
		}
		else
		{
			cout << "                                         !!!!!!!!Role mismatch! Check the data is correct!!!!!!!!!" << endl;
		}
}

void admin_menu(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int number; bool admin = true;
	while (admin)
	{
		cout << "                                ================================================================" << endl;
		cout << "                                |                       *****Admin menu*****                   |" << endl;
		cout << "                                |                  1 - Account management                      |" << endl;
		cout << "                                |                  2 - Work with data                          |" << endl;
		cout << "                                |                  0 - Exit                                    |" << endl;
		cout << "                                                   ->";
		number = letter_protection();
		switch (number)
		{
		case 1: Account_management(arr_of_accounts, number_of_accounts);
			break;
		case 2:
			break;
		case 0: admin = false;
			break;
		default:
			cout << "                                ================================================================== " << endl;
			cout << "                                |                    This is not in the menu!                    | " << endl;
			cout << "                                ================================================================== " << endl;
			break;
		}
	}
}

void Account_management(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int chose;
	bool cycle = true;
	while (cycle)
	{
		cout << "                                ================================================================" << endl;
		cout << "                                |                    1 - To view the accounts                  |" << endl;
		cout << "                                |                    2 - Add an account                        |" << endl;
		cout << "                                |                    3 - Edit an account                       |" << endl;
		cout << "                                |                    4 - Delete an account                     |" << endl;
		cout << "                                |                    0 - Return back                           |" << endl;
		cout << "                                                           ->";
		chose = letter_protection();
		switch (chose)
		{
		case 1:ToViewTheAccounts(arr_of_accounts, number_of_accounts);
			break;
		case 2:arr_of_accounts = getRememberForArray(arr_of_accounts, number_of_accounts, number_of_accounts + 1);
			Add_an_account(arr_of_accounts, number_of_accounts);
			break;
		case 3:EditAnAccounts(arr_of_accounts, number_of_accounts);
			break;
		case 4: DeleteAccount(arr_of_accounts, number_of_accounts);
			break;
		case 0:cycle = false;
			break;
		default:
			cout << "                                        !!!!!!!Enter correct number!!!!!!!               " << endl;
		}
	}
}

void ToViewTheAccounts(Accounts* arr_of_accounts, int& number_of_accounts)
{
	cout << "                              ====================================================================" << endl;
	for (int i = 0; i < number_of_accounts; i++)
	{
		cout << "                                                          " << arr_of_accounts[i].login << arr_of_accounts[i].password << arr_of_accounts[i].role << arr_of_accounts[i].access << endl;
	}
	cout << "                              ====================================================================" << endl;
}

void Add_an_account(Accounts* arr_of_accounts, int& number_of_accounts)
{
	string AddLogin, AddPassword, AddPasswordAgain;
	int i = 0;

	cout << "                                ==================================================================" << endl;
	cout << "                                |if you want to log out of adding an account,enter EXIT          |" << endl;
	cout << "                                |              Enter login (5 symbols minimum)                   |" << endl;
	cout << "                                                       ->";
	cin >> AddLogin;
	while (true)
	{
		if (AddLogin != "EXIT")
		{
			while (i < number_of_accounts)
			{
				if (AddLogin == arr_of_accounts[i].login)
				{
					cout << "                                ==================================================================" << endl;
					cout << "                                           This login already exists! Enter another               " << endl;
					cout << "                                                       ->";
					cin >> AddLogin;
					i = 0;
				}
				else
				{
					i++;
				}
			}
			while (true)
			{
				if (AddLogin.length() <= 4)
				{
					cout << "                                ==================================================================" << endl;
					cout << "                                           Login size does not meet the requirement!              " << endl;
					cout << "                                                           Enter again!                           " << endl;
					cout << "                                                      -> ";
					cin >> AddLogin;
				}
				else
				{
					break;
				}
			}
			arr_of_accounts[number_of_accounts - 1].login = AddLogin;
			while (true)
			{
				cout << "                                ==================================================================" << endl;
				cout << "                                |                Enter password (5 symbols minimum )             |" << endl;
				cout << "                                                       ->";
				AddPassword = password();
				while (true)
				{

					if (AddPassword.length() <= 4)
					{
						cout << endl;
						cout << "                                ==================================================================" << endl;
						cout << "                                |      Password does not meet the requirement! Enter again       |" << endl;
						cout << "                                                       ->";
						AddPassword = password();
					}
					else
					{
						break;
					}
				}

				cout << endl;
				cout << "                                ==================================================================" << endl;
				cout << "                                |                       Re-enter the password                    |" << endl;
				cout << "                                                       ->";
				AddPasswordAgain = password();
				cout << endl;
				if (AddPassword == AddPasswordAgain) {
					arr_of_accounts[number_of_accounts - 1].password = AddPassword;
					break;
				}
				else
				{
					cout << endl;
					cout << "                                ==================================================================" << endl;
					cout << "                                |                 Password mismatch! Enter again                 |" << endl;
					cout << endl;
				}
			}
			arr_of_accounts[number_of_accounts - 1].role = 1;
			arr_of_accounts[number_of_accounts - 1].access = 1;
			break;
		}
		else
		{
			break;
		}
	}
}

void EditAnAccounts(Accounts* arr_of_accounts, int& number_of_accounts)
{
	string ChangeAccount;
	int i = 0, change;
	bool role = true;
	bool cycle = true;
	cout << "                                ==================================================================" << endl;
	cout << "                                |        If you want to exit account editing,enter EXIT          |" << endl;
	cout << "                                |       Enter the login name of the account you want to change   |" << endl;
	cout << "                                        ->";
	cin >> ChangeAccount;
	if (ChangeAccount != "EXIT")
	{
		while (i < number_of_accounts)
		{
			if (ChangeAccount != arr_of_accounts[i].login && i == number_of_accounts - 1)
			{
				cout << "                                ==================================================================" << endl;
				cout << "                                           This login does not exists! Enter another               " << endl;
				cout << "                                                       ->";
				cin >> ChangeAccount;
				i = 0;
			}
			if (ChangeAccount == arr_of_accounts[i].login)
			{
				break;
			}
			else
			{
				i++;
			}
		}

		while (cycle)
		{
			cout << endl;
			cout << "                                |                      1 - Change login                        |" << endl;
			cout << "                                |                      2 - Change password                     |" << endl;
			cout << "                                |                      3 - Change role                         |" << endl;
			cout << "                                |                      4 - Change access                       |" << endl;
			cout << "                                |                      0 - exit                               |" << endl;
			cout << "                                                       ->";
			cin >> change;
			switch (change)
			{
			case 1:arr_of_accounts[i].login = Change_login(arr_of_accounts, number_of_accounts);
				break;
			case 2:arr_of_accounts[i].password = Change_password();
				break;
			case 3:Change_role_or_access(arr_of_accounts, number_of_accounts, role, i);
				break;
			case 4:Change_role_or_access(arr_of_accounts, number_of_accounts, !role, i);
				break;
			case 0: cycle = false;
				break;
			}
		}
	}

}

string Change_login(Accounts* arr_of_accounts, int& number_of_accounts)
{
	string new_login;
	int i = 0;
	cout << "                                 =================================================================" << endl;
	cout << "                                 |                    Please, enter a new login                  |" << endl;
	cout << "                                 =================================================================" << endl;
	cout << "                                                       ->";
	cin >> new_login;
	cout << endl;
	while (i < number_of_accounts)
	{
		if (new_login == arr_of_accounts[i].login)
		{
			cout << "                                ==================================================================" << endl;
			cout << "                                           This login already exists! Enter another               " << endl;
			cout << "                                                       ->";
			cin >> new_login;
			i = 0;
		}
		else
		{
			i++;
		}
	}
	while (true)
	{
		if (new_login.length() <= 4)
		{
			cout << "                                ==================================================================" << endl;
			cout << "                                           Login size does not meet the requirement!              " << endl;
			cout << "                                                           Enter again!                           " << endl;
			cout << "                                                      -> ";
			cin >> new_login;
			cout << endl;
		}
		else
		{
			break;
		}
	}
	return new_login;
}

string Change_password()
{
	string new_password;
	cout << "                                 =================================================================" << endl;
	cout << "                                 |                    Please, enter a new password               |" << endl;
	cout << "                                 =================================================================" << endl;
	cout << "                                                       ->";
	new_password = password();
	cout << endl;
	while (true)
	{
		if (new_password.length() <= 4)
		{
			cout << "                                ==================================================================" << endl;
			cout << "                                           Password size does not meet the requirement!              " << endl;
			cout << "                                                           Enter again!                           " << endl;
			cout << "                                                      -> ";
			new_password = password();
			cout << endl;
		}
		else
		{
			break;
		}
	}
	return new_password;
}

void Change_role_or_access(Accounts* arr_of_accounts, int& number_of_accounts, bool role, int& i)
{
	if (role && arr_of_accounts[i].role == 0)
	{
		arr_of_accounts[i].role = 1;
		cout << "                                ================================================================" << endl;
		cout << "                                |             This account is USER now!          |" << endl;
		cout << "                                ================================================================" << endl;
	}
	else
	{
		if (role && arr_of_accounts[i].role == 1)
		{
			arr_of_accounts[i].role = 0;
			cout << "                                ================================================================" << endl;
			cout << "                                |                This accounts is ADMIN now!              |" << endl;
			cout << "                                ================================================================" << endl;
		}
	}
	if (!role && arr_of_accounts[i].access == 0)
	{
		arr_of_accounts[i].access = 1;
		cout << "                                ================================================================" << endl;
		cout << "                                |             This account is in the waiting state now!          |" << endl;
		cout << "                                ================================================================" << endl;
	}
	else
	{
		if (!role && arr_of_accounts[i].access == 1)
		{
			arr_of_accounts[i].access = 0;
			cout << "                                ================================================================" << endl;
			cout << "                                |             This account is in the working state now!          |" << endl;
			cout << "                                ================================================================" << endl;
		}
	}
}

void DeleteAccount(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int i = 0;
	string deleted_account;
	cout << "                                ==================================================================" << endl;
	cout << "                                |        If you want to exit account editing,enter EXIT          |" << endl;
	cout << "                                |       Enter the login of the account you want to delete        |" << endl;
	cout << "                                                         ->";
	cin >> deleted_account;
	cout << endl;
	if (deleted_account != "EXIT")
	{
		while (i < number_of_accounts)
		{
			if (deleted_account != arr_of_accounts[i].login && i == number_of_accounts - 1)
			{
				cout << "                                ==================================================================" << endl;
				cout << "                                           This login does not exists! Enter another               " << endl;
				cout << "                                                       ->";
				cin >> deleted_account;
				i = 0;
			}
			if (deleted_account == arr_of_accounts[i].login)
			{
				break;
			}
			else
			{
				i++;
			}
		}
		if (arr_of_accounts[i].role == 0) {
			cout << "                                ================================================================" << endl;
			cout << "                                |         You cannot delete an administrator account!          |" << endl;
			cout << "                                |         To delete an administrator, change his role!         |" << endl;
			cout << "                                ================================================================" << endl;
		}
		else {
			for (int deleted_index = i; deleted_index < number_of_accounts - 1; deleted_index++)
			{
				arr_of_accounts[deleted_index] = arr_of_accounts[deleted_index + 1];
			}
			number_of_accounts--;
		}
	}
}

void WriteNewArrayInFile(Accounts* arr_of_accounts, int& number_of_accounts)
{
	ofstream fout(FILE_OF_PASSWORLD);
	int i;
	for (i = 0; i < number_of_accounts - 1; i++)
	{
		fout << arr_of_accounts[i].login << '\t' << arr_of_accounts[i].password << '\t' << arr_of_accounts[i].role << '\t' << arr_of_accounts[i].access << endl;
	}
	fout << arr_of_accounts[i].login << '\t' << arr_of_accounts[i].password << '\t' << arr_of_accounts[i].role << '\t' << arr_of_accounts[i].access;
	fout.close();
}

// Меню не возвращает правильный аккаунт или WriteNewArray не работает
// доработать chose_of_action
// убрать повторяющийся код
//сделать структуру текстовыхсообщений