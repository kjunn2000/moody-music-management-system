#include "Playlists.h"
#include "Playlist.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

void Playlists::addPlaylist(Playlist playlist) {
	PlaylistNode* newNode =new PlaylistNode();
	newNode->playlist = playlist;

	newNode->next = NULL;
	if (size == 0) {
		newNode->prev = NULL;
		this->head = this->tail = newNode;
	}
	else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	this->size++;
	std::cout << "Successfully created 1 playlist." << std::endl;
}
void Playlists::displayAllPlaylists() {
	if (this->size == 0) {
		this->displayEmptyMessage();
		return;
	}
	else {
		PlaylistNode* current = head;
		while (current != NULL) {
			std::cout << "Playlist ID : " << current->playlist.getPlaylistId();
			if (current->playlist.getPlaylistId() < 10) {
				std::cout << " ";
			}
			std::cout<<"\tName : " <<current->playlist.getPlaylistName() << "\t\tSongs(Count) : " << current->playlist.getSize()<< std::endl;
			current = current->next; 
		}
	}
}

int Playlists::displayAvailablePlaylists(int songId) {
	PlaylistNode* current = head; 
	bool found = false;
	while (current != NULL) {
		if (!current->playlist.isSongExist(songId)) {
			found = true;
			std::cout << current->playlist.getPlaylistId()
				<< " : " << current->playlist.getPlaylistName() <<std::endl;
		}
		current = current->next; 
	}
	if (!found) {
		std::cout << "No playlist available." << std::endl;
		return 0;
	}
	return 1;
}

int Playlists::checkPlaylist(int playlistId) {
	PlaylistNode* current = head; 
	while (current != NULL) {
		if (current->playlist.getPlaylistId() == playlistId) {
			if (current->playlist.getSize() > 0) return 1;
			return 0;
		}
		current = current->next; 
	}
	return -1;
}


std::vector<int> Playlists::findPlaylistBySongId(int songId) {
	if (size == 0) this->displayEmptyMessage();
	std::vector<int> playlistIds;
	PlaylistNode* current = head;
	bool found = false;
	while (current != NULL) {
		if (current->playlist.isSongExist(songId))
		{
			found = true;
			playlistIds.push_back(current->playlist.getPlaylistId());
			std::cout << "Playlist ID  : " << current->playlist.getPlaylistId() << "\t\t";
			std::cout << "Playlist name: " << current->playlist.getPlaylistName() << std::endl;
		}
		current = current->next;
	}
	if (!found) {
		std::cout << "This song doesn't exists in any playlist." << std::endl;
	}
	return playlistIds;
}

void Playlists::addSongToPlaylist(int playlistId, Song song) {
	PlaylistNode* current = head;
	bool found = false;
	while (current != NULL) {
		if (current->playlist.getPlaylistId() == playlistId) {
			found = true;
			if (current->playlist.getSize() == 50) {
				std::cout << "This playlist already full. Please create a new playlist." << std::endl;
				return;
			}else if (current->playlist.isSongExist(song.songId))
			{
				std::cout << "Song already exist." << std::endl;
				return;
			}
			current->playlist.addSong(song);
			break;
		}
		current = current->next; 
	}
	if (!found) std::cout << "Playlist ID not exist." << std::endl;
}

bool Playlists::viewSongInPlaylist(int playlistId) {
	bool found = false;
	PlaylistNode* current = head; 
	while (true) {
		if (current->playlist.getPlaylistId() == playlistId) {
			found = true;
			break;
		}
		if (current == tail) break;
		current = current->next; 
	}
	if (found) {
		current->playlist.displaySong();
		return true;
	}
	else {
		this->displayNotFoundMessage();
		return false;
	}
} 

void Playlists::removeSongFromPlaylist(int playlistId, int songId) {
	PlaylistNode* current = head;
	bool found = false;
	while (current != NULL) {
		if (current->playlist.getPlaylistId() == playlistId) {
			found = true;
			break;
		}
		if (current == tail) break;
		current = current->next; 
	}if (found) {
			current->playlist.deleteSong(songId);
		}
}

void Playlists::navigatePlaylist(int playlistId) {
	

	PlaylistNode* current = head;
	bool found = false;
	while (current != NULL) {
		if (current->playlist.getPlaylistId() == playlistId) {
			found = true;
			break;
		}
		current = current->next; 
	}
	if (!found) {
		this->displayNotFoundMessage();
		return;
	}
	current->playlist.navigatePlaylist();
}


void Playlists::deletePlaylistById(int playlistId) {
	if (this->size == 0) {
		displayEmptyMessage();
		return; 
	}
	PlaylistNode* toDelete = head;
	bool found = false;
	while (toDelete != NULL) {
		if (toDelete->playlist.getPlaylistId() == playlistId) {
			found = true;
			break;
		}
		toDelete = toDelete->next;
	}
	if (found && size == 1) {
		head = tail = NULL;
	}
	else if (found && toDelete == head) {
		toDelete->next->prev = NULL; 
		head = toDelete->next; 
	}
	else if (found && toDelete == tail) {
		toDelete->prev->next = NULL;
		tail = toDelete->prev; 
	}else if(found) {
		toDelete->next->prev = toDelete->prev;
		toDelete->prev->next = toDelete->next;
	}
	if (found) {
		delete toDelete;
		size--;
		std::cout << "Successfully deleted 1 playlist." << std::endl;
	}
	else {
		displayNotFoundMessage();
	}
}


void Playlists::displayEmptyMessage()
{
	std::cout << "This playlists is empty." << std::endl;
}

void Playlists::displayNotFoundMessage() {
	std::cout << "Playlist Id not exist." << std::endl;
}

void Playlists::readFromFile(Collection collection) {
	std::string line;
	std::ifstream playlistsFile("playlists_file.txt");
	if (playlistsFile.is_open()) {
		int row = 1;
		Playlist playlist;
		while (std::getline(playlistsFile, line))
		{
			switch (row) {
			case 1:
				if (line == "") {
					break;
				}
				try {
					playlist.playlistId = std::stoi(line);
				}
				catch (...) {
					std::cout << "Error occur" << std::endl;
				}
				break;
			case 2:
				playlist.playlistName = line;
				this->addPlaylist(playlist);
				break;
			case 3:
			{
				std::vector<std::string> out;
				std::stringstream ss(line);

				std::string s;
				while (std::getline(ss, s, ' ')) {
					out.push_back(s);
				}

				for (auto& s : out) {
					int songId = std::stoi(s);
					this->addSongToPlaylist(playlist.playlistId, collection.getSong(songId));
				}

				break;
			}
			default:
				row = 0;
				break;
			}
			row++;
		}
	}
}

void Playlists::saveToFile() {



	PlaylistNode* current = head;

	std::ofstream playlistsFile("playlists_file.txt");

	if (playlistsFile.is_open())
	{
		if (this->getSize() == 0) playlistsFile << "";
		else {
			while (current != NULL) {


				playlistsFile << current->playlist.getPlaylistId() << "\n";
				playlistsFile << current->playlist.getPlaylistName() << "\n";
				if (current->playlist.getSize() != 0) {
					SongNode* temp = current->playlist.tail->next;
					while (true) {
						playlistsFile << temp->song.songId << " ";
						if (temp == current->playlist.tail) break;
						temp = temp->next;
					}
				}

				playlistsFile << "\n";
				current = current->next;
				playlistsFile << "\n";
			}
		}
		playlistsFile.close();
		std::cout << "Playlist Data saved to text file." << std::endl;

	}
	else std::cout << "Unable to open file." << std::endl;
}