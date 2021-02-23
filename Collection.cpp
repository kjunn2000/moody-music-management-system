#include "Collection.h"
#include "Utils.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>

void Collection::addSong(Song song)
{
	if (this->size == 300) {
		std::cout << "The collection already has 300 songs. Please delete some song. " << std::endl;
		return;
	}
	if (this->size == 0) {
		addSongToEmptyList(song);
	}
	else {
		addSongAtEnd(song);
	}
	this->size++;
	std::cout << "Successfully added 1 song." << std::endl;
}
void Collection::addSongToEmptyList(Song song)
{
	SongNode* newNode = new SongNode();
	newNode->song = song;
	newNode->next = newNode->prev = tail = newNode;
}
void Collection::addSongAtEnd(Song song)
{
	SongNode* newNode = new SongNode();
	newNode->song = song;
	newNode->next = tail->next;
	newNode->prev = tail;
	tail->next->prev = newNode;
	tail->next = newNode;
	tail = newNode;
}

void Collection::showSong()
{
	if (this->size == 0) {
		this->displayEmptyMessage();
		return;
	}

	SongNode* current = this->tail->next;
	while (true)
	{
		std::cout << "Song ID : " << current->song.songId << "\t";
		std::cout << "Song Title : " << current->song.title << "\t\n";
		if (current == tail) {
			break;
		}
		current = current->next;
	}
}


void Collection::displaySong()
{
	if (this->size == 0) {
		this->displayEmptyMessage();
		return;
	}

	while (true) {
		std::cout << "\n--------------------" << std::endl;
		std::cout << "1. Sort by Time of Created." << std::endl;
		std::cout << "2. Sort by Title. " << std::endl;
		std::cout << "3. Sort by Duration. " << std::endl;
		std::cout << "4. Exit. " << std::endl;
		std::cout << "\n--------------------\n" << std::endl;
		std::string option;
		while (true) {
			std::cout << "Please enter your option : ";
			std::getline(std::cin, option);
			std::cout << "\n"; 
			if (Utils::validateIntInput(option)) break;
			Utils::displayInvalidInputMessage();
		}
		switch (std::stoi(option)) {
			case 1:
				displaySongByCreatedTime();
				break;
			case 2:
				displaySongByTitle();
				break;
			case 3:
				displaySongByDuration();
				break;
			case 4:
				return;
			default:
				Utils::displayInvalidInputMessage();
				break;
		}
	}
	
}


void Collection::displaySongByCreatedTime() {
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
		int minutes = current->song.duration / 60;
		int seconds = current->song.duration % 60;
		std::cout << "Song Duration : " << minutes << ":" <<seconds << "\n" << std::endl;
		if (current == tail) {
			break;
		}
		current = current->next;
	}
}

void Collection::displaySongByTitle() {
	SongNode* current = this->tail->next;
	std::vector<Song> songList;
	while (true)
	{
		songList.push_back(current->song);
		if (current == tail) {
			break;
		}
		current = current->next;
	}
	std::sort(songList.begin(), songList.end(), [](const Song& lhs, const Song& rhs) {
		return lhs.title < rhs.title;
		});
	for(Song song : songList)
	{
		std::cout << "Song Title : " << song.title << "\t";
		std::cout << "Song ID : " << song.songId << "\t";
		std::cout << "Song Singer : " << song.singer << "\t";
		int minutes = song.duration / 60;
		int seconds = song.duration % 60;
		std::cout << "Song Duration : " << minutes << ":" << seconds << "\n" << std::endl;
	}
}

void Collection::displaySongByDuration() {
	SongNode* current = this->tail->next;
	std::vector<Song> songList;
	while (true)
	{
		songList.push_back(current->song);
		if (current == tail) {
			break;
		}
		current = current->next;
	}
	std::sort(songList.begin(), songList.end(), [](const Song& lhs, const Song& rhs) {
		return lhs.duration < rhs.duration;
		});
	for (Song song : songList)
	{
		int minutes = song.duration / 60;
		int seconds = song.duration % 60;
		std::cout << "Song Duration : " << minutes << ":" << seconds << "\t";;
		std::cout << "Song Title : " << song.title << "\t";
		std::cout << "Song ID : " << song.songId << "\t";
		std::cout << "Song Singer : " << song.singer << "\n" << std::endl;
	}
}

void Collection::deleteSong(int songId)
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
	if (found && this->size>1) {
		toDelete->prev->next = toDelete->next;
		toDelete->next->prev = toDelete->prev;
		if (toDelete == tail) tail = toDelete->prev;
	}
	else if (found && this->size == 1) tail = NULL; 
	else {
		std::cout << "The song ID not found." << std::endl;
	}
	if (found){
		delete toDelete;
		this->size--;
		std::cout << "Successfully deleted 1 song." <<std::endl;
	}
}

void Collection::displayEmptyMessage()
{
	std::cout << "This collection is empty." << std::endl;

}

bool Collection::checkSongExist(int songId) {
	bool found = false;
	SongNode* node = this->tail->next;
	while (true) {
		if (node->song.songId == songId) {
			found = true; 
			return found;
		}
		if (node == tail) break;
		node = node->next;
	}
	return found;
}


Song Collection::getSong(int songId) {
	SongNode* node = this->tail->next;
	while (true) {
		if (node->song.songId == songId) return node->song;
		if (node == tail) break;
		node = node->next; 
	}
}

void Collection::readFromFile() {
	std::string line;
	std::ifstream collectionFile("collection_file.txt");
	if (collectionFile.is_open()) {
		int row = 1;
		Song song;
		while (std::getline(collectionFile, line))
		{
			switch (row) {
			case 0:
				break;
			case 1:
				if (line == "") {
					break;
				}
				try {
					song.songId = std::stoi(line);
				}
				catch (...) {
					std::cout << "Error occur" << std::endl;
				}
				break;
			case 2:
				song.title = line;
				break;
			case 3:
				song.singer = line;
				break;
			case 4:
				song.duration = std::stoi(line);
				break;
			default:
				this->addSong(song);
				row = 0;
				break;
			}
			row++;
		}
	}
}

void Collection::saveToFile(){

	SongNode* current = tail->next; 
	
	std::ofstream collectionFile("collection_file.txt");
	
	if (collectionFile.is_open())
	{
		
		while (true) {
			
			if (this->getSize() == 0) collectionFile << "";
			else {
				collectionFile << current->song.songId << "\n";
				collectionFile << current->song.title << "\n";
				collectionFile << current->song.singer << "\n";
				collectionFile << current->song.duration << "\n\n";
			}
			if (current == tail) break;
			current = current->next;
		}
		collectionFile.close();
		std::cout << "Song Data saved to text file." << std::endl;
	}
	else std::cout << "Unable to open file." << std::endl;
}
