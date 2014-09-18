#include "TextBuddy.h"

void main(int argc, char* argv[]) {
	if(TextBuddy::isValidInitialization(argc, argv)) {
		TextBuddy::runTextBuddy(argv);
	}
	else {
		TextBuddy::terminateTextBuddy(MESSAGE_ERROR_INITIALIZATION);
	}
}

void TextBuddy::runTextBuddy(char* argv[]) {
	TextBuddy::setSaveFileName(argv[SAVE_FILE_LOCATION_IN_ARGV]);
	TextBuddy::readFromSaveFile();
	TextBuddy::showMessageWelcome();

	while(true) {
		//std::string userInput = TextBuddy::getUserInput();
		//TextBuddy::executeCommand(userInput);
	}
}

void TextBuddy::exitTextBuddy() {
	TextBuddy::showMessage(MESSAGE_TERMINATED);
	exit(EXIT_SUCCESS);
}

void TextBuddy::terminateTextBuddy(std::string errorMessage) {
	TextBuddy::showMessage(errorMessage);
	TextBuddy::showMessage(MESSAGE_TERMINATED);
	exit(EXIT_FAILURE);
}

bool TextBuddy::isValidInitialization(int argc, char* argv[]) {
	return (argc == VALID_ARGC && isValidSaveFile(argv[SAVE_FILE_LOCATION_IN_ARGV]));
}

bool TextBuddy::isValidSaveFile(std::string saveFile) {
	return (saveFile.substr(saveFile.find_last_of(".") + 1) == VALID_SAVE_FILE_EXTENSION); 
}

void readFromSaveFile() {
	std::ifstream textFile;
	std::string currentLine;

	textFile.open(TextBuddy::getSaveFileName());
	while(std::getline(textFile, currentLine)) {
		TextBuddy::saveLineToStorage(currentLine);
	}
	textFile.close();
}

void saveToSaveFile() {
	std::ofstream textFile;

	textFile.open(TextBuddy::getSaveFileName());
	for(unsigned int i = 0; i < TextBuddy::getTextStorageSize(); i++) {
		textFile << TextBuddy::getLineFromTextStorage(i) << std::endl;
	}
	textFile.close();
}

void showMessage(std::string message) {
	std::cout << message << std::endl;
}

void TextBuddy::showMessageWelcome() {
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), saveFileName.c_str());
	TextBuddy::showMessage(buffer);
}