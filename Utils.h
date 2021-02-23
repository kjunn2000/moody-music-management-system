#pragma once
#include <vector>

class Utils
{
	public: 
		
		static void displayInvalidInputMessage();

		static bool validateIntInput(std::string input);

		static void clearCinInput();

		static int getOptionInput();

		static int getSongIdInput();

		static int getPlaylistIdInput();

};

