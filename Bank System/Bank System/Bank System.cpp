#include <iostream>
#include <string>
#include <cctype>
#include <functional>
#include <algorithm>
#include <fstream>
#include<sstream>
#include <vector>
#include <windows.h>
using namespace std;
class Validition
{
public:
	static bool checkName(string n)
	{
		bool test = true;

		if ((n.size() >= 5 && n.size() <= 20))
		{
			for (int i = 0; i < n.size(); i++)
			{
				if ((n[i] >= 'a' && n[i] <= 'z') || (n[i] >= 'A' && n[i] <= 'Z'))
				{
					test = true;
				}
				else
				{
					test = false;
					break;
				}
			}
		}
		else
		{
			test = false;
		}

		return test;
	}

	static bool checkPassword(string p)
	{

		if ((p.size() >= 8 && p.size() <= 20))
		{
			return true;
		}

		return false;
	}

	static bool checkSalary(double s)
	{
		if (s >= 5000)
		{
			return true;
		}
		return false;
	}

	static bool checkBalance(double b)
	{
		if (b >= 1500)
		{
			return true;
		}

		return false;
	}
};
class Person
{
private:
	int id;
	string name, password;
public:
	Person()
	{
		id = 0;
		name = "No-Name";
		password = "No-Password";
	}

	Person(int id, string name, string password)
	{
		setId(id);
		setName(name);
		setPassword(password);
	}

	void setId(int id)
	{
		this->id = id;
	}

	bool setName(string name)
	{
		if (Validition::checkName(name))
		{
			this->name = name;
			return true;
		}
		else
		{
			cout << "Invalid name\n";
			return false;
		}
	}

	bool setPassword(string password)
	{
		if (Validition::checkPassword(password))
		{
			this->password = password;
			return true;
		}
		else
		{
			if (password.size() < 8)
			{
				cout << "Password less than 8\n";
			}
			else if (password.size() > 20)
			{
				cout << "Password greater than 20\n";
			}
			return false;
		}
	}

	int getId()
	{
		return id;
	}

	string getName()
	{
		return name;
	}

	string getPassword()
	{
		return password;
	}

	void Display()
	{
		cout << "id : " << id << "\n";
		cout << "Name : " << name << "\n";
		cout << "Password : " << password << "\n";
	}
};

class Client : public Person
{
private:
	double balance;
public:
	Client()
	{
		balance = 1500;
	}

	Client(int id, string name, string password, double balance) : Person(id, name, password)
	{
		setBalance(balance);
	}

	bool setBalance(double balance)
	{
		if (Validition::checkBalance(balance))
		{
			this->balance = balance;
			return true;
		}
		else
		{
			cout << "\n*************************************\n";
			cout << "Balance less than 1500\n";
			cout << "*************************************\n\n";
			return false;
		}
	}

	double getBalance()
	{
		return balance;
	}

	void Deposit(double amount)
	{
		balance += amount;
	}

	void Withdraw(double amount)
	{
		if (amount <= balance && (balance - amount) >= 1500)
		{
			balance -= amount;
			cout << "\n********************\n";
			cout << "Process Done!\n";
			cout << "********************\n\n";
		}
		else
		{
			cout << "\n*************************************\n";
			cout << "Amount less than your balance\n";
			cout << "*************************************\n\n";
		}
	}

	void transferTo(double amount, Client& c)
	{
		if (amount <= balance && (balance - amount) >= 1500)
		{
			balance -= amount;
			c.balance += amount;
			cout << "\n********************\n";
			cout << "Process Done!\n";
			cout << "********************\n\n";
		}
		else
		{
			cout << "\n*************************************\n\n";
			cout << "Amount less than your balance\n";
			cout << "*************************************\n\n";
		}
	}

	void checkBalance()
	{
		cout << "Your balance = " << balance << endl;
	}

	void Display()
	{
		Person::Display();
		cout << "Balance : " << balance << endl;
	}

};
static vector<Client> All_Client;

static vector<Client>::iterator  ClientIt;
class Employee : public Person
{
protected:
	double salary;

public:
	Employee()
	{
		salary = 5000;
	}

	Employee(int id, string name, string password, double salary) : Person(id, name, password)
	{
		setSalary(salary);
	}

	bool setSalary(double salary)
	{

		if (Validition::checkSalary(salary))
		{
			this->salary = salary;
			return true;
		}
		else
		{
			cout << "\n*************************************\n";
			cout << "Salary less than 5000\n";
			cout << "*************************************\n\n";
			return false;
		}

	}

	double getSalary()
	{
		return salary;
	}

	void Display()
	{
		Person::Display();
		cout << "Salary : " << salary << endl;
	}

	void addClient(Client client)
	{
		All_Client.push_back(client);
	}

	Client* searchClient(int id) {
		for (ClientIt = All_Client.begin(); ClientIt != All_Client.end(); ClientIt++)
		{
			if (ClientIt->getId() == id)
			{
				return ClientIt._Ptr;
			}
		}
		return NULL;
	}

	void listClient()
	{
		for (int i = 0; i < All_Client.size(); i++) {
			cout << "Client Info:" << i + 1 << endl;
			All_Client[i].Display();
			cout << "===============================" << endl;
		}
	}

	void editClient(int id, string name, string password, double balance)
	{
		Client* c = searchClient(id);
		if (c == nullptr) {
			cout << "client not found" << endl;
			exit(0);
		}
		else {
			c->setName(name);
			c->setPassword(password);
			c->setBalance(balance);

		}
	}

};
static vector<Employee> All_Employee;

static vector<Employee>::iterator  EmployeeIt;

static Employee _Employee;

class Admin : public Employee
{
public:

	Admin()
	{

	}
	Admin(int id, string name, string password, double salary) : Employee(id, name, password, salary)
	{

	}
	void addEmployee(Employee employee)
	{
		All_Employee.push_back(employee);
	}
	Employee* searchEmployee(int id)
	{
		for (EmployeeIt = All_Employee.begin(); EmployeeIt != All_Employee.end(); EmployeeIt++)
		{
			if (EmployeeIt->getId() == id)
			{
				return EmployeeIt._Ptr;
			}
		}
		return NULL;
	}
	void editEmployee(int id, string name, string password, double salary)
	{
		Employee* e = searchEmployee(id);
		if (e == NULL) {
			cout << " Employee not found" << endl;
			exit(0);
		}
		else {
			e->setName(name);
			e->setPassword(password);
			e->setSalary(salary);

		}
	}
	void listEmployee()
	{
		for (int i = 0; i < All_Employee.size(); i++) {
			cout << "Employee Info:" << i + 1 << endl;
			All_Employee[i].Display();
			cout << "===============================" << endl;
		}
	}

};
static vector<Admin> All_Admin;

static vector<Admin>::iterator  AdminIt;

static Admin _Admin;
class Parser
{
public:

	static vector<string> split(string returned_line_from_file)
	{
		vector<string>string_splited;
		string part;
		stringstream lines(returned_line_from_file);

		while (getline(lines, part, '|'))
		{
			string_splited.push_back(part);
		}
		return string_splited;
	}
	static Client parseToClient(string returned_line_from_Client)
	{
		vector<string> returned_line_parts = split(returned_line_from_Client);
		Client _Client(stoi(returned_line_parts[0]), returned_line_parts[1], returned_line_parts[2], stod(returned_line_parts[3]));
		return _Client;
	}
	static Employee parseToEmployee(string returned_line_from_Employee)
	{
		vector<string> returned_line_parts = split(returned_line_from_Employee);
		Employee _Employee(stoi(returned_line_parts[0]), returned_line_parts[1], returned_line_parts[2], stod(returned_line_parts[3]));
		return _Employee;
	}
	static Admin parseToAdmin(string returned_line_from_Admin)
	{
		vector<string> returned_line_parts = split(returned_line_from_Admin);
		Admin _Admin(stoi(returned_line_parts[0]), returned_line_parts[1], returned_line_parts[2], stod(returned_line_parts[3]));
		return _Admin;
	}
};
class FilesHelper
{
public:
	static void saveLast(string fileName, int id)
	{
		fstream file;
		file.open(fileName, ios::out);
		file << id;
		file.close();
	}
	static int  getLast(string fileName)
	{
		fstream file_id;
		string id;

		file_id.open(fileName, ios::in);
		file_id >> id;

		if (id.size() == 0)
		{
			id = "0";
			file_id.open(fileName, ios::out);
			file_id << "0";
		}

		file_id.close();
		return stoi(id);
	}
	static void saveClient(Client c)
	{
		int id = getLast("client_id.txt");
		fstream cf;
		cf.open("Client.txt", ios::app);
		cf << id + 1 << '|' << c.getName() << '|' << c.getPassword() << '|' << c.getBalance() << '\n';
		cf.close();
		saveLast("client_id.txt", id + 1);
	}
	static void saveEmployee(string fileName, string lastIdFile, Employee e)
	{
		int id = getLast(lastIdFile);
		fstream Employee_File;
		Employee_File.open(fileName, ios::app);
		Employee_File << id + 1 << '|' << e.getName() << '|' << e.getPassword() << '|' << e.getSalary() << '\n';
		Employee_File.close();
		saveLast(lastIdFile, id + 1);
	}
	static void saveAdmin(Admin a)
	{
		int id = getLast("Admin_id.txt");
		fstream af;
		af.open("Admin.txt", ios::app);
		af << id + 1 << '|' << a.getName() << '|' << a.getPassword() << '|' << a.getSalary() << '\n';
		af.close();
		saveLast("Admin_id.txt", id + 1);
	}
	static void getClients()
	{

		fstream client_file;
		client_file.open("Client.txt", ios::in);
		string returned_line_from_Client;
		while (getline(client_file, returned_line_from_Client, '\n'))
		{
			All_Client.push_back(Parser::parseToClient(returned_line_from_Client));
		}
		client_file.close();
	}
	static void getEmployees()
	{
		fstream employee_file;
		employee_file.open("Employee.txt", ios::in);
		string returned_line_from_Employee;
		while (getline(employee_file, returned_line_from_Employee, '\n'))
		{
			All_Employee.push_back(Parser::parseToEmployee(returned_line_from_Employee));
		}
		employee_file.close();
	}
	static void getAdmins()
	{
		fstream admin_file;
		admin_file.open("Admin.txt", ios::in);
		string line;
		while (getline(admin_file, line, '\n'))
		{
			All_Admin.push_back(Parser::parseToAdmin(line));
		}
		admin_file.close();
	}
	static void clearFile(string fileName, string lastIdFile)
	{
		fstream clientFile, clientLastId;
		clientFile.open(fileName, ios::out);
		clientLastId.open(lastIdFile, ios::out);
		clientFile.close();
		clientLastId.close();
	}
};
class DataSourceInterface
{
protected:
	virtual void addClient(Client c) = 0;
	virtual void addEmployee(Employee e) = 0;
	virtual void addAdmin(Admin a) = 0;
	virtual void getAllClients() = 0;
	virtual void getAllEmployees() = 0;
	virtual void getAllAdmins() = 0;
	virtual void removeAllClients() = 0;
	virtual void removeAllEmployees() = 0;
	virtual void removeAllAdmins() = 0;
};
class FileManager : public DataSourceInterface
{
public:

	void addClient(Client c)
	{
		FilesHelper::saveClient(c);
	}
	void addEmployee(Employee e)
	{
		FilesHelper::saveEmployee("Employee.txt", "Employee_id.txt", e);
	}
	void addAdmin(Admin a)
	{
		FilesHelper::saveAdmin(a);
	}
	void getAllClients()
	{
		FilesHelper::getClients();
	}
	void getAllEmployees()
	{
		FilesHelper::getEmployees();
	}
	void getAllAdmins()
	{
		FilesHelper::getAdmins();
	}
	void removeAllClients()
	{
		FilesHelper::clearFile("Client.txt", "client_id.txt");
	}
	void removeAllEmployees()
	{
		FilesHelper::clearFile("Employee.txt", "Employee_id.txt");
	}
	void removeAllAdmins()
	{
		FilesHelper::clearFile("Admin.txt", "Admin_id.txt");
	}
	void getAllData()
	{
		getAllClients();
		getAllEmployees();
		getAllAdmins();
	}
	void updateClientFile()
	{
		removeAllClients();

		for (int i = 0; i < All_Client.size(); i++)
		{
			addClient(All_Client[i]);
		}
	}
	void updateEmployeeFile()
	{
		removeAllEmployees();

		for (int i = 0; i < All_Employee.size(); i++)
		{
			addEmployee(All_Employee[i]);
		}
	}
	void updateAdminFile()
	{
		removeAllAdmins();

		for (int i = 0; i < All_Admin.size(); i++)
		{
			addAdmin(All_Admin[i]);
		}
	}
	void updateAllFiles()
	{
		updateClientFile();
		updateEmployeeFile();
		updateAdminFile();
	}
};




bool test = true;
class ClientManger
{
public:
	static void printClientMenu()
	{
		system("cls");
		cout << "\t\t\t\t\t\tClient Functions\n";
		cout << "1-Deposit\n";
		cout << "2-Withdraw\n";
		cout << "3-transferTo\n";
		cout << "4-checkBalance\n";
		cout << "5-Display\n";
		cout << "6-Update Password\n";
		cout << "7-Logout\n";
		cout << endl;
	}
	static bool clientOptions(Client* _Client)
	{
		int x = 0;

		cout << "Enter your choise : ";

		cin >> x;

		switch (x)
		{
		case 1:
		{
			system("cls");
			double amount = 1500;
			cout << "Enter Amount To Deposit : ";
			cin >> amount;
			_Client->Deposit(amount);
			break;
		}
		case 2:
		{
			system("cls");
			double amount = 1500;
			cout << "Enter Amount To Withdraw : ";
			cin >> amount;
			_Client->Withdraw(amount);
			break;
		}
		case 3:
		{
			system("cls");
			double amount = 1500;
			Client* otherClient;
			int id = 0;
			cout << "Enter Client Id you want TransferTo : ";
			cin >> id;
			otherClient = _Employee.searchClient(id);
			cout << "Enter Amount To transferTo : ";
			cin >> amount;
			if (otherClient != NULL)
			{
				_Client->transferTo(amount, *otherClient);
			}
			else
			{
				cout << "\n******************************************\n";
				cout << "The Other Client Not Found In System\n";
				cout << "******************************************\n\n";
			}
			break;
		}
		case 4:
		{
			system("cls");
			_Client->checkBalance();
			break;
		}
		case 5:
		{
			system("cls");
			_Client->Display();
			break;
		}
		case 6:
		{
			system("cls");
			updatePassword(_Client);
			break;
		}
		case 7:
		{
			return true;
		}
		default:
		{
			cout << "\n*************************************\n";
			cout << "Your Choise Not Found In List\n";
			cout << "*************************************\n\n";
			clientOptions(_Client);
		}
		}
		Back(_Client);
	}
	static void Back(Client* _Client)
	{
		system("pause");
		printClientMenu();
		clientOptions(_Client);
	}
	static void updatePassword(Person* person)
	{
		string password;
		cout << "Enter New Password : ";
		cin >> password;
		if (person->setPassword(password))
		{
			cout << "\n*********************\n";
			cout << "Password Updated \n";
			cout << "*********************\n\n";
		}
	}
	static Client* login(int id, string password)
	{
		Client* clientptr = _Employee.searchClient(id);
		if (clientptr == NULL)
		{
			cout << "\n****************************\n";
			cout << "Incorrect Id Or Password\n";
			cout << "****************************\n\n";
			return NULL;
		}
		else
		{
			if (clientptr->getPassword() == password)
			{
				return clientptr;
			}
			else
			{
				cout << "\n****************************\n";
				cout << "Incorrect Id Or Password\n";
				cout << "****************************\n\n";
				return NULL;
			}
		}
	}


};

class EmployeeManager
{
public:
	static void printEmployeeMenu()
	{
		system("cls");
		cout << "\t\t\t\t\t\tEmployee Functions\n";
		cout << "1-Add New Client\n";
		cout << "2-List Of All Clients\n";
		cout << "3-Search For A Client\n";
		cout << "4-Edit Client\n";
		cout << "5-Display\n";
		cout << "6-Update Password\n";
		cout << "7-Logout\n";
		cout << endl;
	}
	static void newClient(Employee* employee)
	{
		Client client;
		string name, password;
		double balance;
		int id;
		cout << "Enter New Client\n\n";
		cout << "Name : ";
		cin >> name;
		cout << "Password : ";
		cin >> password;
		cout << "Balance : ";
		cin >> balance;
		if (client.setName(name) && client.setPassword(password) && client.setBalance(balance))
		{
			id = FilesHelper::getLast("client_id.txt");
			client.setId(id + 1);
			FilesHelper::saveLast("client_id.txt", id + 1);
			employee->addClient(client);
			cout << "\n*******************\n";
			cout << "Client Accepted\n";
			cout << "*******************\n\n";
		}
		else
		{
			cout << "\n**************************\n";
			cout << "Client Not Accepted\n";
			cout << "**************************\n\n";
		}

	}
	static void listAllClients(Employee* employee)
	{
		employee->listClient();
	}
	static void searchForClient(Employee* employee)
	{
		int id;
		cout << "Client Id : ";
		cin >> id;
		Client* client = employee->searchClient(id);
		if (client == NULL)
		{
			cout << "\n**************************\n";
			cout << "Client Not Found\n";
			cout << "**************************\n\n";
		}
		else
		{
			cout << "**************************\n";
			cout << "Client Found And His Info:\n";
			client->Display();
		}
	}
	static void editClientInfo(Employee* employee)
	{
		int x;
		int id;
		string name, password;
		double balance;
		cout << "Enter Id : ";
		cin >> id;

		Client* client = employee->searchClient(id);

		if (client != NULL)
		{
			cout << "\nWhat You Want To Edit : \n";
			cout << "1-All data\n";
			cout << "2-Name\n";
			cout << "3-Password\n";
			cout << "4-Balance\n";

			cout << "\nEnter Your Choise : ";
			cin >> x;

			switch (x)
			{
			case 1:
			{
				cout << "\nEnter New Name : ";
				cin >> name;
				cout << "\nEnter New Password : ";
				cin >> password;
				cout << "\nEnter New balance : ";
				cin >> balance;
				employee->editClient(id, name, password, balance);

				break;
			}
			case 2:
			{
				cout << "\nEnter New Name : ";
				cin >> name;
				password = client->getPassword();
				balance = client->getBalance();
				employee->editClient(id, name, password, balance);
				break;
			}
			case 3:
			{
				cout << "\nEnter New Password : ";
				cin >> password;
				name = client->getName();
				balance = client->getBalance();
				employee->editClient(id, name, password, balance);
				break;
			}
			case 4:
			{
				cout << "\nEnter New Balance : ";
				cin >> balance;
				name = client->getName();
				password = client->getPassword();
				employee->editClient(id, name, password, balance);
				break;
			}
			default:
			{

				cout << "\n*************************************\n";
				cout << "Your Choise Not Found In List\n";
				cout << "*************************************\n\n";
				editClientInfo(employee);
				break;
			}
			}
		}
		else
		{
			cout << "\n************************\n";
			cout << "Client not found\n\n";
			cout << "************************\n\n";
			cout << "\n1 - Try Again\n";
			cout << "2 - Return\n";
			int x;
			cout << "\nEnter Your Choise : ";
			cin >> x;
			system("cls");
			if (x == 1)
			{
				editClientInfo(employee);
			}
			else if (x == 2)
			{
				printEmployeeMenu();
				employeeOptions(employee);
			}
			else
			{
				cout << "\n*************************************\n";
				cout << "Your Choise Not Found In List\n";
				cout << "*************************************\n\n";
				system("pause");
				printEmployeeMenu();
				employeeOptions(employee);
			}
		}
	}
	static bool employeeOptions(Employee* employee)
	{
		int x = 0;

		cout << "Enter your choise : ";

		cin >> x;

		switch (x)
		{
		case 1:
		{
			system("cls");
			newClient(employee);
			break;
		}
		case 2:
		{
			system("cls");
			listAllClients(employee);
			break;
		}
		case 3:
		{
			system("cls");
			searchForClient(employee);
			break;
		}
		case 4:
		{
			system("cls");
			editClientInfo(employee);
			break;
		}
		case 5:
		{
			system("cls");
			employee->Display();
			break;
		}
		case 6:
		{
			system("cls");
			updatePassword(employee);
			break;
		}
		case 7:
		{
			return true;
		}
		default:
		{
			cout << "\nYour Choise Not Found In List\n";
			employeeOptions(employee);
		}
		}
		Back(employee);
	}
	static void Back(Employee* employee)
	{
		system("pause");
		printEmployeeMenu();
		employeeOptions(employee);
	}
	static void updatePassword(Person* person)
	{
		string password;
		cout << "Enter New Password : ";
		cin >> password;
		if (person->setPassword(password))
		{
			cout << "\n*********************\n";
			cout << "Password Updated \n";
			cout << "*********************\n\n";
		}
	}
	static Employee* Login(int id, string password)
	{
		Employee* employeeptr = _Admin.searchEmployee(id);

		if (employeeptr == NULL)
		{
			cout << "\n****************************\n";
			cout << "Incorrect Id Or Password\n";
			cout << "****************************\n\n";
			return NULL;
		}
		else
		{
			if (employeeptr->getPassword() == password)
			{
				return employeeptr;
			}
			else
			{
				cout << "\n****************************\n";
				cout << "Incorrect Id Or Password\n";
				cout << "****************************\n\n";
				return NULL;
			}
		}
	}
};

class AdminManager : public EmployeeManager
{
public:
	static void printAdminMenu()
	{
		system("cls");
		cout << "\t\t\t\t\t\tAdmin Functions\n";
		cout << "1-Add New Client\n";
		cout << "2-List Of All Clients\n";
		cout << "3-Search For A Client\n";
		cout << "4-Edit Client\n";
		cout << "5-Add New Employee\n";
		cout << "6-List Of All Employee\n";
		cout << "7-Search For A Employee\n";
		cout << "8-Edit Employee\n";
		cout << "9-Display\n";
		cout << "10-Update Password\n";
		cout << "11-Logout\n";
		cout << endl;
	}
	static void newEmployee(Admin* admin)
	{
		Employee employee;
		string name, password;
		double salary;
		int id;
		cout << "Enter New Employee\n\n";
		cout << "Name : ";
		cin >> name;
		cout << "Password : ";
		cin >> password;
		cout << "Salary : ";
		cin >> salary;
		if (employee.setName(name) && employee.setPassword(password) && employee.setSalary(salary))
		{
			id = FilesHelper::getLast("Employee_id.txt");
			employee.setId(id + 1);
			FilesHelper::saveLast("Employee_id.txt", id + 1);
			admin->addEmployee(employee);
			cout << "\n*******************\n";
			cout << "Employee Accepted\n";
			cout << "*******************\n\n";
		}
		else
		{
			cout << "\n**************************\n";
			cout << "Employee Not Accepted\n";
			cout << "**************************\n\n";
		}

	}
	static void listAllEmployee(Admin* admin)
	{
		admin->listEmployee();
	}
	static void searchForEmployee(Admin* admin)
	{
		int id;
		cout << "Employee Id : ";
		cin >> id;
		Employee* employee = admin->searchEmployee(id);
		if (employee == NULL)
		{
			cout << "\n**************************\n";
			cout << "Employee Not Found\n";
			cout << "**************************\n\n";
		}
		else
		{
			cout << "**************************\n";
			cout << "Employee Found And His Info:\n";
			employee->Display();
		}
	}
	static void editEmployeeInfo(Admin* admin)
	{
		int x;
		int id;
		string name, password;
		double salary;
		cout << "Enter Id : ";
		cin >> id;

		Employee* employee = admin->searchEmployee(id);

		if (employee != NULL)
		{
			cout << "\nWhat You Want To Edit : \n";
			cout << "1-All data\n";
			cout << "2-Name\n";
			cout << "3-Password\n";
			cout << "4-Salary\n";

			cout << "\nEnter Your Choise : ";
			cin >> x;

			switch (x)
			{
			case 1:
			{
				cout << "\nEnter New Name : ";
				cin >> name;
				cout << "\nEnter New Password : ";
				cin >> password;
				cout << "\nEnter New Salary : ";
				cin >> salary;
				admin->editEmployee(id, name, password, salary);
				break;
			}
			case 2:
			{
				cout << "\nEnter New Name : ";
				cin >> name;
				password = employee->getPassword();
				salary = employee->getSalary();
				admin->editEmployee(id, name, password, salary);
				break;
			}
			case 3:
			{
				cout << "\nEnter New Password : ";
				cin >> password;
				name = employee->getName();
				salary = employee->getSalary();
				admin->editEmployee(id, name, password, salary);
				break;
			}
			case 4:
			{
				cout << "\nEnter New Salary : ";
				cin >> salary;
				name = employee->getName();
				password = employee->getPassword();
				admin->editEmployee(id, name, password, salary);
				break;
			}
			default:
			{
				cout << "\n*************************************\n";
				cout << "Your Choise Not Found In List\n";
				cout << "*************************************\n\n";
				editEmployeeInfo(admin);
				break;
			}
			}
		}
		else
		{
			cout << "\n************************\n";
			cout << "Employee not found\n\n";
			cout << "************************\n\n";
			cout << "\n1 - Try Again\n";
			cout << "2 - Return\n";
			int x;
			cout << "\nEnter Your Choise : ";
			cin >> x;
			system("cls");
			if (x == 1)
			{
				editEmployeeInfo(admin);
			}
			else if (x == 2)
			{
				printAdminMenu();
				AdminOptions(admin);
			}
			else
			{
				cout << "\nYour Choise Not Found In List\n\n";
				system("pause");
				printAdminMenu();
				AdminOptions(admin);
			}
		}
	}
	static bool AdminOptions(Admin* admin)
	{
		int x = 0;

		cout << "Enter your choise : ";

		cin >> x;

		switch (x)
		{
		case 1:
		{
			system("cls");
			newClient(admin);
			break;
		}
		case 2:
		{
			system("cls");
			listAllClients(admin);
			break;
		}
		case 3:
		{
			system("cls");
			searchForClient(admin);
			break;
		}
		case 4:
		{
			system("cls");
			editClientInfo(admin);
			break;
		}
		case 5:
		{
			system("cls");
			newEmployee(admin);
			break;
		}
		case 6:
		{
			system("cls");
			listAllEmployee(admin);
			break;
		}
		case 7:
		{
			system("cls");
			searchForEmployee(admin);
			break;
		}
		case 8:
		{
			system("cls");
			editEmployeeInfo(admin);
			break;
		}
		case 9:
		{
			system("cls");
			admin->Display();
			break;
		}
		case 10:
		{
			system("cls");
			updatePassword(admin);
			break;
		}
		case 11:
		{
			return true;
		}
		default:
		{
			cout << "\n*************************************\n";
			cout << "Your Choise Not Found In List\n";
			cout << "*************************************\n\n";
			AdminOptions(admin);
		}
		}
		Back(admin);
	}
	static void Back(Admin* admin)
	{
		system("pause");
		printAdminMenu();
		AdminOptions(admin);
	}
	static void updatePassword(Person* person)
	{
		string password;
		cout << "Enter New Password : ";
		cin >> password;
		if (person->setPassword(password))
		{
			cout << "\n*********************\n";
			cout << "Password Updated \n";
			cout << "*********************\n\n";
		}
	}
	static Admin* searchAdmin(int id)
	{
		for (AdminIt = All_Admin.begin(); AdminIt != All_Admin.end(); AdminIt++)
		{
			if (AdminIt->getId() == id)
			{
				return AdminIt._Ptr;
			}
		}
		return NULL;
	}
	static Admin* Login(int id, string password)
	{
		Admin* Adminptr = searchAdmin(id);

		if (Adminptr == NULL)
		{
			cout << "\n****************************\n";
			cout << "Incorrect Id Or Password\n";
			cout << "****************************\n\n";
			return NULL;
		}
		else
		{
			if (Adminptr->getPassword() == password)
			{
				return Adminptr;
			}
			else
			{
				cout << "\n****************************\n";
				cout << "Incorrect Id Or Password\n";
				cout << "****************************\n\n";
				return NULL;
			}
		}
	}
};

FileManager _Filemanager;
string name = " ";
class Screens
{
public:

	static void loginOptions()
	{
		cout << "\t\t\t\t\t\tLogin As\n";
		cout << "1 - Client\n\n";
		cout << "2 - Employee\n\n";
		cout << "3 - Admin\n\n";
		cout << "4 - Exit\n\n";
	}
	static int loginAs()
	{
		int x;
		cout << "Login As : ";
		cin >> x;

		switch (x)
		{
		case 1:
		{
			return 1;
			break;
		}
		case 2:
		{
			return 2;
			break;
		}
		case 3:
		{
			return 3;
			break;
		}
		case 4:
		{
			return 4;
			break;
		}
		default:
		{
			Invalid(x);
			break;
		}
		}
	}
	static void Invalid(int c)
	{
		cout << "\n\n*************************************\n";
		cout << "Your Choise Not Found In List\n";
		cout << "*************************************\n\n";
		loginAs();
	}
	static void LoginClient()
	{
		cout << "\t\t\t\t\t\tLogin Client Page\n";
		int id;
		string password;
		cout << "Id : ";
		cin >> id;
		cout << "Password : ";
		cin >> password;
		Client* client = ClientManger::login(id, password);
		if (client != NULL)
		{
			ClientManger::printClientMenu();
			if (ClientManger::clientOptions(client))
			{
				system("cls");
				name = client->getName();
				loginOptions();
				loginScreen(loginAs());
			}

		}
		else
		{
			cout << "\n1 - Try Again\n";
			cout << "2 - Return\n";
			cout << "\nEnter Your Choise : ";
			int x;
			cin >> x;
			switch (x) {
			case 1: {
				system("cls");
				LoginClient();
				break;
			}
			case 2: {
				system("cls");
				loginOptions();
				loginScreen(loginAs());
				break;
			}
			default: {
				cout << "\n\n*************************************\n";
				cout << "Your Choise Not Found In List\n";
				cout << "*************************************\n\n";
				system("pause");
				system("cls");
				loginOptions();
				loginScreen(loginAs());
			}
			}
		}
	}
	static void LoginEmployee()
	{
		cout << "\t\t\t\t\t\tLogin Employee Page\n";
		int id;
		string password;
		cout << "Id : ";
		cin >> id;
		cout << "Password : ";
		cin >> password;
		Employee* employee = EmployeeManager::Login(id, password);
		if (employee != NULL)
		{
			EmployeeManager::printEmployeeMenu();
			if (EmployeeManager::employeeOptions(employee))
			{
				system("cls");
				name = employee->getName();
				loginOptions();
				loginScreen(loginAs());
			}
		}
		else
		{
			cout << "\n1 - Try Again\n";
			cout << "2 - Return\n";
			cout << "\nEnter Your Choise : ";
			int x;
			cin >> x;
			switch (x) {
			case 1: {
				system("cls");
				LoginEmployee();
				break;
			}
			case 2: {
				system("cls");
				loginOptions();
				loginScreen(loginAs());
				break;
			}
			default: {
				cout << "\n\n*************************************\n";
				cout << "Your Choise Not Found In List\n";
				cout << "*************************************\n\n";
				system("pause");
				system("cls");
				loginOptions();
				loginScreen(loginAs());
			}
			}
		}
	}
	static void LoginAdmin()
	{
		cout << "\t\t\t\t\t\tLogin Admin Page\n";
		int id;
		string password;
		cout << "Id : ";
		cin >> id;
		cout << "Password : ";
		cin >> password;

		Admin* admin = AdminManager::Login(id, password);
		if (admin != NULL)
		{
			AdminManager::printAdminMenu();
			if (AdminManager::AdminOptions(admin))
			{
				system("cls");
				name = admin->getName();
				loginOptions();
				loginScreen(loginAs());
			}
		}
		else
		{
			cout << "\n1 - Try Again\n";
			cout << "2 - Return\n";
			cout << "\nEnter Your Choise : ";
			int x;
			cin >> x;
			switch (x) {
			case 1: {
				system("cls");
				LoginAdmin();
				break;
			}
			case 2: {
				system("cls");
				loginOptions();
				loginScreen(loginAs());
				break;
			}
			default: {
				cout << "\n\n*************************************\n";
				cout << "Your Choise Not Found In List\n";
				cout << "*************************************\n\n";
				system("pause");
				system("cls");
				loginOptions();
				loginScreen(loginAs());
			}
			}
		}
	}
	static void loginScreen(int c)
	{
		switch (c)
		{

		case 1:
		{
			system("cls");
			LoginClient();
			break;
		}
		case 2:
		{
			system("cls");
			LoginEmployee();
			break;
		}
		case 3:
		{
			system("cls");
			LoginAdmin();
			break;
		}
		case 4:
		{
			SayThank();
			_Filemanager.updateAllFiles();
		}

		}
	}
	static void SayThank()
	{
		system("cls");
		system("Color f4");
		cout << "\n\n\n\n\n\n\n\n\n";
		cout << "\t\t    ########  ##    ##   ######   ####    ##  ##   ##     ##    ##     ##     ##    ##\n";
		cout << "\t\t       ##     ##    ##  ##    ##  ## ##   ##  ##  ##       ##  ##    ##  ##   ##    ##\n";
		cout << "\t\t       ##     ########  ########  ##  ##  ##  ## #           ##     ##    ##  ##    ##\n";
		cout << "\t\t       ##     ##    ##  ##    ##  ##   ## ##  ##  ##         ##      ##  ##    ##  ##\n";
		cout << "\t\t       ##     ##    ##  ##    ##  ##    ####  ##   ##        ##        ##        ##\n";
		Sleep(2500);
		system("cls");
	}
	static void BankName()
	{
		cout << "\n\n\n\n\n\n\n\n\n";
		cout << "\t\t      ##     ##      ######      ##     ##     #######   ########  ####    ##  ##   ##\n";
		cout << "\t\t      ###   ###     ##    ##     ###   ###     ##    ##  ##    ##  ## ##   ##  ##  ##\n";
		cout << "\t\t      ## # # ##     ########     ## # # ##     #######   ########  ##  ##  ##  ## #\n";
		cout << "\t\t      ##  #  ##     ##    ##     ##  #  ##     ##    ##  ##    ##  ##   ## ##  ##  ##\n";
		cout << "\t\t      ##     ##  @  ##    ##  @  ##     ##     #######   ##    ##  ##    ####  ##   ##\n   ";
		Sleep(2500);
	}
	static void Welcome()
	{
		cout << "\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t##       ##   ######    ##      #######  ########   ##     ##   ######\n";
		cout << "\t\t\t##   #   ##   ##        ##      ##       ##    ##   ###   ###   ##\n";
		cout << "\t\t\t##  # #  ##   ######    ##      ##       ##    ##   ## # # ##   ######\n";
		cout << "\t\t\t## #   # ##   ##        ##      ##       ##    ##   ##  #  ##   ##\n";
		cout << "\t\t\t###     ###   ######    ######  #######  ########   ##     ##   ######\n";
		Sleep(2500);
	}
	static void runApp()
	{
		system("Color f4");
		BankName();
		system("cls");
		Welcome();
		system("cls");
		system("Color f4");
		_Filemanager.getAllData();
		loginOptions();
		loginScreen(loginAs());
	}
};

int main() {

	Screens::runApp();



	return 0;
};













