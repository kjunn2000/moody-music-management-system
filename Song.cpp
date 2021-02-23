#include "Song.h"

std::string Song::toString() {
	return this->songId+" "+this->title + " " + this->singer + " " + std::to_string(this->duration);
}
