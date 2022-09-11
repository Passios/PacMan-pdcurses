#include "HiScore.h"

HiScore::HiScore(const string& file) {

	filePath = file;
	for (int i = 0; i < ENTRIES_NUMBER; i++) {
		entries[i].score = -1;
		strcpy(entries[i].name, "");
	}

	tmpName = "";
	loadFile();
}

void HiScore::loadFile() {

	ifstream file(filePath.c_str(), ios::in | ios::binary);
	if (file) {
		char* temp = (char*)&entries[0];
		file.read(temp, sizeof(Entry) * ENTRIES_NUMBER);
		file.close();
	}
}

void HiScore::saveFile() {

	ofstream file(filePath.c_str(), ios::out | ios::binary | ios::trunc);
	if (!file) {
		throw ios_base::failure("Unable to save scores.");
	}

	char* temp = (char*)&entries[0];
	file.write(temp, sizeof(Entry) * ENTRIES_NUMBER);
	file.close();
}

void HiScore::addScore(const string& name, int score) {

	if (isScoreGoodEnough(score)) {

		// Find position for score.
		int spot = -1;
		for (int i = 0; i < ENTRIES_NUMBER; i++) {
			if (score > entries[i].score) {
				spot = i;
				break;
			}
		}

		// Move entries one spot down.
		for (int i = ENTRIES_NUMBER - 1; i > spot; i--) {
			entries[i].score = entries[i - 1].score;
			strcpy(entries[i].name, entries[i - 1].name);
		}

		// Copy new entry.
		entries[spot].score = score;
		strcpy(entries[spot].name, name.c_str());

		// Save to file.
		saveFile();

	}

}

bool HiScore::isScoreGoodEnough(int score) {
	return score > 0 && score > entries[ENTRIES_NUMBER - 1].score;
}

HiScore& HiScore::operator<<(const string& name) {
	tmpName = name;
	return *this;
}

void HiScore::operator<<(int score) {
	if (tmpName != "") {
		addScore(tmpName, score);
		tmpName = "";
	}
}

ostream& operator<<(ostream& stream, const HiScore& scoreObject) {

	if (scoreObject.entries[0].score == -1)
		stream << "No scores have been saved.";
	else {
		for (int i = 0; i < ENTRIES_NUMBER; i++) {

			string name = scoreObject.entries[i].name;
			int score = scoreObject.entries[i].score;

			if (score != -1) {
				stream << "Spot " << (i + 1) << ": " << name << " - " << score << endl;
			}
			else
				break;
		}
	}
	return stream;
}
