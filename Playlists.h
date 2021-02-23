#pragma once
#include "Playlist.h"
#include <string>
#include <vector>

class PlaylistNode{
	
	public: 
		Playlist playlist;
		PlaylistNode* prev;
		PlaylistNode* next;
		PlaylistNode() {
			prev = NULL; 
			next = NULL; 
		}
};

class Playlists
{
	PlaylistNode* head;
	PlaylistNode* tail;
	int size;

	public:
		Playlists() {
			head = NULL;
			tail = NULL; 
			size = 0;
		}
		int getSize() { return this->size; };
		void addPlaylist(Playlist playlist);
		void displayAllPlaylists();
		int displayAvailablePlaylists(int songId);
		int checkPlaylist(int playlistId);
		std::vector<int> findPlaylistBySongId(int songId);
		void addSongToPlaylist(int playlistId, Song song);
		bool viewSongInPlaylist(int playlistId);
		void removeSongFromPlaylist(int playlistId, int songId);
		void navigatePlaylist(int playlistId);
		void deletePlaylistById(int playlistId);
		void displayEmptyMessage();
		void displayNotFoundMessage();
		void readFromFile(Collection collection);
		void saveToFile();

};

