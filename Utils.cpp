#include <string>
#include <iostream>
#include <regex>;
#include "Utils.h"
#include <sstream>

void Utils::displayInvalidInputMessage() {
	std::cout << "Invalid Input Data Type." << std::endl ;
}

bool Utils::validateIntInput(std::string input) {
	return std::regex_match(input, std::regex("[0-9]+"));
}

void Utils::clearCinInput() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Utils::getOptionInput(){
	std::string optionStr;
	while (true) {
		std::cout << "Please enter your option: ";
		std::getline(std::cin, optionStr);
		if (Utils::validateIntInput(optionStr)) break;
		Utils::displayInvalidInputMessage();
	}
	return std::stoi(optionStr);
}


int Utils::getSongIdInput() {
	std::string songIdStr;
	while (true) {
		std::cout << "Please enter the song ID : ";
		std::getline(std::cin, songIdStr);
		if (Utils::validateIntInput(songIdStr)) break;
		Utils::displayInvalidInputMessage();
	}
	return std::stoi(songIdStr);
}

int Utils::getPlaylistIdInput() {
	std::string playlistIdStr;
	while (true) {
		std::cout << "Please enter the playlist ID : ";
		std::getline(std::cin, playlistIdStr);
		if (Utils::validateIntInput(playlistIdStr)) break;
		Utils::displayInvalidInputMessage();
	}
	return std::stoi(playlistIdStr);
}
