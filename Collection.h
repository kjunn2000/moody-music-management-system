#pragma once
#include "Song.h"
#include <string>

class SongNode
{
public:
	Song song;
	SongNode* prev;
	SongNode* next;
	SongNode() {
		prev = NULL;
		next = NULL;
	}
};

class Collection
{
private:
	SongNode* tail;
	int size;
public:
	Collection() {
		tail = NULL;
		size = 0;
	}

	int getSize() { return this->size; };
	void addSong(Song song);
	void addSongToEmptyList(Song song);
	void addSongAtEnd(Song song);
	void showSong();
	void displaySong();
	void displaySongByCreatedTime();
	void displaySongByTitle();
	void displaySongByDuration();
	void deleteSong(int songId);
	void displayEmptyMessage();
	bool checkSongExist(int songId);
	Song getSong(int songId);
	void readFromFile();
	void saveToFile();
};

