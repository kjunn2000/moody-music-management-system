#include "Authentication.h"

bool Authentication::showLoginPage() {
	while (true) {
		std::cout << "\n----------Welcome to Moody Music !!!-------------------" << std::endl;
		std::cout << "| 1. Log In.                                        | " << std::endl;
		std::cout << "| 2. Register.                                      | " << std::endl;
		std::cout << "| 3. Exit.                                          |" << std::endl;
		std::cout << "------------------------------------------------------\n" << std::endl;
		int option;
		option = Utils::getOptionInput();
		switch (option) {
			case 1:
			{
				std::string username, password;
				std::cout << "Please enter your username: ";
				std::getline(std::cin, username);
				std::cout << "Please enter your password: ";
				std::getline(std::cin, password);
				if (validateAccount(username, password)) return true;
				else { std::cout << "Account not found." << std::endl; }
				break;
			}
			case 2:
				showRegisterPage();
				break;
			case 3: 
				return false;
			default:
				Utils::displayInvalidInputMessage();
				break;
		}
	}
}

void Authentication::showRegisterPage() {
	User user;
	std::cout << "\n----------Register Page !!!----------" << std::endl;
	do {
		std::cout << "Please enter your username: ";
		std::getline(std::cin, user.username);
		if (user.username == "") continue;
	} while (checkExist(user.username));
	std::cout << "Please enter your password: ";
	std::getline(std::cin, user.password);
	std::cout << "------------------------------------\n" << std::endl;
	this->userList.push_back(user);
	std::cout << "Registered Successfully" << std::endl;
}

bool Authentication::validateAccount(std::string username, std::string password) {
	for (User user : this->userList) {
		if (user.username == username && user.password==password) return true;
	}
	return false;
}

bool Authentication::checkExist(std::string username) {
	for (User user : this->userList) {
		if (user.username == username) {
			std::cout << "Username exist." << std::endl;
			return true;
		}
	}
	return false;
}

void Authentication::readFromFile() {
	std::string line;
	std::ifstream userFile("authentication_file.txt");
	if (userFile.is_open()) {
		int row = 1;
		User user;
		while (std::getline(userFile, line))
		{
			switch (row) {
			case 0:
				break;
			case 1:
				user.username = line;
				break;
			case 2:
				user.password = line;
				break;
			default:
				this->userList.push_back(user);
				row = 0;
				break;
			}
			row++;
		}
	}
}

void Authentication::saveToFile() {

	if (this->userList.empty()) return;

	std::ofstream userFile("authentication_file.txt");

	if (userFile.is_open())
	{
		for (User user : this->userList) {
			userFile << user.username << "\n";
			userFile << user.password << "\n\n";
		}
		std::cout << "User Data saved to text file." << std::endl;
	}
	else std::cout << "Unable to open file." << std::endl;
}
