#pragma once
#include "Song.h"
#include "Collection.h"

class Playlist
{
	private:
		
		int size;
		void addSongToEmptyList(Song song);
		void addSongAtEnd(Song song);
	public:
		SongNode* tail;
		int playlistId;
		std::string playlistName;
		Playlist() {
			tail = NULL;
			size = 0;
		}
		Playlist(int playlistId,std::string playlistName) {
			this->playlistId = playlistId;
			this->playlistName = playlistName;
			tail = NULL;
			size = 0;
		}
		int getPlaylistId() { return this->playlistId; };
		std::string getPlaylistName() { return this->playlistName; };
		int getSize() { return this->size; };
		bool isSongExist(int songId);
		void addSong(Song song);
		Song getSong(int index);
		void displaySong();
		void deleteSong(int songId);
		void navigatePlaylist();
		void classicPlay();
		void shufflePlay();
		void displayEmptyMessage();
};



