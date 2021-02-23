#include "Playlist.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include "Utils.h"


bool Playlist::isSongExist(int songId) {
	if (this->size == 0) {
		return false;
	}
	bool found = false;
	SongNode* current = this->tail->next;
	while (true) {
		if (current->song.songId == songId) {
			found = true;
			break;
		}
		if (current == tail) break;
		current = current->next; 
	}
	return found;
}

void Playlist::addSong(Song song)
{
	if (this->size == 0) {
		addSongToEmptyList(song);
	}
	else {
		addSongAtEnd(song);
	}
	this->size++;
	std::cout << "Successfully added 1 song to playlist." << std::endl;
}

void Playlist::addSongToEmptyList(Song song)
{
	SongNode* newNode = new SongNode();
	newNode->song = song;
	newNode->next = newNode->prev = tail = newNode;
}
void Playlist::addSongAtEnd(Song song)
{
	SongNode* newNode = new SongNode();
	newNode->song = song;
	newNode->next = tail->next;
	newNode->prev = tail;
	tail->next->prev = newNode;
	tail->next = newNode;
	tail = newNode;
}

Song Playlist::getSong(int index) {
	SongNode* current = this->tail->next;
	int ind = 0;
	while (true)
	{
		if (ind == index) return current->song;
		if (current == tail) {
			break;
		}
		current = current->next;
		ind++;
	}
}

void Playlist::displaySong()
{
	if (this->size == 0) {

		this->displayEmptyMessage();
		return;
	}
	SongNode* current = this->tail->next;
	while (true)
	{
		std::cout << "Song ID : " << current->song.songId << "\t";
		std::cout << "Song Title : " << current->song.title << "\t";
		std::cout << "Song Singer : " << current->song.singer << "\t";
		std::cout << "Song Duration : " << current->song.duration << std::endl;
		if (current == tail) {
			break;
		}
		current = current->next;
	}
}

void Playlist::navigatePlaylist() {

	if (this->size == 0) {
		this->displayEmptyMessage();
		return;
	}

	std::cout << "\n------------------" << std::endl;
	std::cout << "Navigate option \n" << std::endl;
	std::cout << "1. Classic Play." << std::endl;
	std::cout << "2. Shuffle Play." << std::endl;
	std::cout << "--------------------\n" << std::endl;

	std::string option;
	while (true) {
		std::cout << "Please enter your option : ";
		std::getline(std::cin, option);
		if (Utils::validateIntInput(option)) break;
		Utils::displayInvalidInputMessage();
	}
	if (std::stoi(option) == 1) {
		classicPlay();
	}
	else if (std::stoi(option) == 2) {
		shufflePlay();
	}
	else {
		Utils::displayInvalidInputMessage();
		return;
	}
}

void Playlist::classicPlay() {

	SongNode* current = this->tail->next;
	while (true) {

		std::cout << "\n----------Current Song----------" << std::endl;
		std::cout << "|Song ID    : " << current->song.songId << std::endl;
		std::cout << "|Song Title : " << current->song.title << std::endl;
		std::cout << "|Singer     : " << current->song.singer << std::endl;
		std::cout << "|Duration   : " << current->song.duration << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << "|1. previous song ->" << current->prev->song.title << std::endl;
		std::cout << "|2. next song     ->" << current->next->song.title << std::endl;
		std::cout << "|3. replay        ->" << current->song.title << std::endl;
		std::cout << "|4. quit navigation." << std::endl;
		std::cout << "---------------------------------\n" << std::endl;
		int option = Utils::getOptionInput();
		if (option == 1) {
			current = current->prev;
			continue;
		}
		else if (option == 2) {
			current = current->next;
			continue;
		}
		else if (option == 3) {
			continue;
		}
		else if (option == 4) {
			return;
		}
		else {
			std::cout << "Invalid option. " << std::endl;
			continue;
		}

	}
}

void Playlist::shufflePlay() {
	
	std::stack <Song> songStack;
	int nextIndex = rand() % this->getSize();
	Song prevSong ;
	Song currentSong = getSong(nextIndex);
	nextIndex = rand() % this->getSize();
	Song nextSong = getSong(nextIndex);

	while (true) {

		std::cout << "\n----------Current Song----------" << std::endl;
		std::cout << "|Song ID    : " << currentSong.songId << std::endl;
		std::cout << "|Song Title : " << currentSong.title << std::endl;
		std::cout << "|Singer     : " << currentSong.singer << std::endl;
		std::cout << "|Duration   : " << currentSong.duration << std::endl;
		std::cout << "---------------------------------\n" << std::endl;
		std::cout << "|1. quit navigation." << std::endl;
		std::cout << "|2. next song     ->" << nextSong.title << std::endl;
		std::cout << "|3. replay        ->" << currentSong.title << std::endl;

		if (!songStack.empty()) {
			std::cout << "|4. previous song ->" << prevSong.title << std::endl;
		}
		std::cout << "---------------------------------\n" << std::endl;
		int option = Utils::getOptionInput();
		if (option == 1) {
			return;
		}
		else if (option == 2) {
			songStack.push(currentSong);
			prevSong = currentSong; 
			currentSong = nextSong; 
			nextIndex = rand() % this->getSize();
			nextSong = getSong(nextIndex);
			continue;
		}
		else if (option == 3) {
			continue;
		}
		else if (option == 4) {
			if (songStack.empty()) {
				Utils::displayInvalidInputMessage();
				continue; 
			}
			nextIndex = rand() % this->getSize();
			nextSong = getSong(nextIndex);
			currentSong = prevSong;
			songStack.pop();
			if (songStack.size() > 1) {
				prevSong = songStack.top();
			}
			continue; 
		}
		else {
			Utils::displayInvalidInputMessage();
			continue;
		}

	}
}


void Playlist::deleteSong(int songId)
{	
	if (this->size == 0) {
		this->displayEmptyMessage();
		return;
	}

	bool found = false;
	SongNode* toDelete = tail->next;
	while (true) {
		if (toDelete->song.songId == songId) {
			found = true;
			break;
		}
		if (toDelete == tail) break;
		toDelete = toDelete->next;
	}
	if (found && this->size > 1) {
		toDelete->prev->next = toDelete->next;
		toDelete->next->prev = toDelete->prev;
		if (toDelete == tail) tail = toDelete->prev;
	}
	else if (found && this->size == 1) tail = NULL;
	else std::cout << "The song ID not found." << std::endl;
	if (found) {
		delete toDelete;
		this->size--;
		std::cout << "Successfully deleted 1 song from playlist." << std::endl;
	}
}

void Playlist::displayEmptyMessage()
{
	std::cout << "This playlist is empty." << std::endl;
}
