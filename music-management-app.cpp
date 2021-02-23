#include<iostream>
#include<string.h>
#include "Collection.h"
#include "Playlists.h"
#include "Utils.h"
#include "Authentication.h"

int main(){

	Authentication authentication;
	Collection collection;
	Playlists playlists;
	authentication.readFromFile();
	collection.readFromFile();
	playlists.readFromFile(collection);

	while (authentication.showLoginPage()) {
		while (true) {
			bool logOut = false;
			std::cout << "\n----------Welcome to Moody Music App !!!--------------" << std::endl;
			std::cout << "|                                                    |" << std::endl;
			std::cout << "| COLLECTION                                         |" << std::endl;
			std::cout << "| ----------                                         |" << std::endl;
			std::cout << "| 1. Add song to the colleciton.                     |" << std::endl;
			std::cout << "| 2. Display all the song.                           |" << std::endl;
			std::cout << "| 3. Delete song.                                    |" << std::endl;
			std::cout << "| 4. Search playlist.                                |" << std::endl;
			std::cout << "|                                                    |" << std::endl;
			std::cout << "| PLAYLIST                                           |" << std::endl;
			std::cout << "| ----------                                         |" << std::endl;
			std::cout << "| 5. Create playlist.                                |" << std::endl;
			std::cout << "| 6. View playlist.                                  |" << std::endl;
			std::cout << "| 7. Add song to playlist.                           |" << std::endl;
			std::cout << "| 8. View songs in playlist.                         |" << std::endl;
			std::cout << "| 9. Remove song from playlist.                      |" << std::endl;
			std::cout << "| 10. Navigate playlist.                             |" << std::endl;
			std::cout << "| 11. Delete playlist.                               | " << std::endl;
			std::cout << "| 12. Exit.                                          |" << std::endl;
			std::cout << "|                                                    |" << std::endl;
			std::cout << "------------------------------------------------------\n" << std::endl;
			int option;
			option = Utils::getOptionInput();
			switch (option)
			{
			case 1:
			{
				Song song;
				std::string  durationStr;
				int songId = Utils::getSongIdInput();
				if (collection.getSize() > 0 && collection.checkSongExist(songId)) {
					std::cout << "Song ID already exist." << std::endl;
					break;
				}
				song.songId = songId;
				std::cout << "Please enter the song title : ";
				std::getline(std::cin, song.title);
				std::cout << "Please enter the singer : ";
				std::getline(std::cin, song.singer);
				while (true) {
					std::cout << "Please enter the duration (seconds) : ";
					std::getline(std::cin, durationStr);
					if (Utils::validateIntInput(durationStr)) {
						break;
					}
					Utils::displayInvalidInputMessage();
				}
				song.duration = std::stoi(durationStr);
				collection.addSong(song);
				break;
			}
			case 2:
				collection.displaySong();
				break;
			case 3:
			{
				collection.showSong();
				std::cout << "\n";
				if (collection.getSize() == 0) break;
				int songId = Utils::getSongIdInput();
				std::vector<int> playlistIdsToDelete = playlists.findPlaylistBySongId(songId);
				for (int playlistIdToDelete : playlistIdsToDelete) {
					playlists.removeSongFromPlaylist(playlistIdToDelete, songId);
				}
				collection.deleteSong(songId);
				break;
			}
			case 4:
			{
				collection.showSong();
				std::cout << "\n";
				int songId = Utils::getSongIdInput();
				std::cout << "\n";
				std::vector<int> playlistIds = playlists.findPlaylistBySongId(songId);
				break;
			}
			case 5:
			{
				std::cout << "\n";
				int playlistId = Utils::getPlaylistIdInput();
				if (playlists.checkPlaylist(playlistId) != -1) {
					std::cout << "Playlist ID already exist." << std::endl;
					break;
				}
				std::string playlistName;
				std::cout << "Please enter new playlist name: ";
				std::getline(std::cin, playlistName);
				Playlist playlist(playlistId, playlistName);
				playlists.addPlaylist(playlist);
				break;
			}
			case 6:
			{
				std::cout << "\n";
				playlists.displayAllPlaylists();
				break;
			}
			case 7:
			{
				
				if (collection.getSize() == 0) {
					collection.displayEmptyMessage();
					break;
				}
				else if (playlists.getSize() == 0) {
					playlists.displayEmptyMessage();
					break;
				}
				std::cout << "\n";
				collection.showSong();
				std::cout << "\n";
				int songId = Utils::getSongIdInput();
				std::cout << "\n";
				if (!collection.checkSongExist(songId)) {
					std::cout << "Song Id not found." << std::endl;
					break;
				};
				if (playlists.displayAvailablePlaylists(songId) == 0) break;
				std::cout << "\n";
				int playlistId = Utils::getPlaylistIdInput();
				playlists.addSongToPlaylist(playlistId, collection.getSong(songId));
				break;
			}
			case 8:
			{
				if (playlists.getSize() == 0) {
					playlists.displayEmptyMessage();
					break;
				}
				std::cout << "\n";
				playlists.displayAllPlaylists();
				std::cout << "\n";
				int playlistId = Utils::getPlaylistIdInput();
				std::cout << "\n";
				playlists.viewSongInPlaylist(playlistId);
				break;
			}
			case 9:
			{
				if (collection.getSize() == 0) {
					collection.displayEmptyMessage();
					break;
				}
				else if (playlists.getSize() == 0) {
					playlists.displayEmptyMessage();
					break;
				}
				std::cout << "\n";
				playlists.displayAllPlaylists();
				std::cout << "\n";
				int playlistId = Utils::getPlaylistIdInput();
				std::cout << "\n"; 
				int result = playlists.checkPlaylist(playlistId);

				if (result == 1) {
					if (playlists.viewSongInPlaylist(playlistId)) {
						std::cout << "\n";
						int songId = Utils::getSongIdInput();
						playlists.removeSongFromPlaylist(playlistId, songId);
						break;
					}
					else {
						std::cout << "This song ID is not in the playlist." << std::endl;
						break;
					};
				}
				else if (result == 0) {
					std::cout << "This playlist is empty." << std::endl;
					break;
				}
				else if (result == -1) {
					playlists.displayNotFoundMessage();
					break;
				}
			}
			case 10:
			{
				std::cout << "\n";
				playlists.displayAllPlaylists();
				if (playlists.getSize() == 0) {
					playlists.displayEmptyMessage();
					break;
				}
				std::cout << "\n";
				int playlistId = Utils::getPlaylistIdInput();
				playlists.navigatePlaylist(playlistId);
				std::cout << "\n";
				break;
			}
			case 11:
			{
				std::cout << "\n";
				playlists.displayAllPlaylists();
				if (playlists.getSize() == 0) {
					playlists.displayEmptyMessage();
					break;
				}
				std::cout << "\n";
				int playlistId = Utils::getPlaylistIdInput();
				playlists.deletePlaylistById(playlistId);
				break;
			}
			case 12:
				logOut = true;
				break;
			default:
				std::cout << "Please enter valid option.\n" << std::endl;
				break;
			}
			if (logOut) break;
			std::cout << std::endl;
		}
	}
	collection.saveToFile();
	playlists.saveToFile();
	authentication.saveToFile();
	
}