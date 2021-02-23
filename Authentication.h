#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Utils.h"
#include "User.h"

class Authentication
{


	public:
		std::vector <User> userList;
		bool showLoginPage();
		void showRegisterPage();
		bool validateAccount(std::string username, std::string password);
		bool checkExist(std::string username);
		void readFromFile();
		void saveToFile();
};

