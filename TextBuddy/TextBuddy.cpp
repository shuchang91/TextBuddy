#include "TextBuddy.h"

void main(int argc, char* argv[]) {
	if(TextBuddy::isValidInitialization(argc, argv)) {
		TextBuddy::runTextBuddy(argv);
	}
	else {
		TextBuddy::terminateTextBuddy(MESSAGE_ERROR_INITIALIZATION);
	}
}

//TEXTBUDDY++ EMTRY POINT****************************************************//
void TextBuddy::runTextBuddy(char* argv[]) {
	TextBuddy::setSaveFileName(argv[SAVE_FILE_LOCATION_IN_ARGV]);
	TextBuddy::readFromSaveFile();
	TextBuddy::showMessageWelcome();

	while(true) {
		std::string userInput = TextBuddy::getUserInput();
		TextBuddy::executeInput(userInput);
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

//MAIN PROGRAM LOGIC*********************************************************//
std::string TextBuddy::getUserInput() {
	std::cout << "Enter command: ";

	std::string userInput;
	std::getline(std::cin, userInput);

	return userInput;
}

void TextBuddy::executeInput(std::string userInput) {
	TextBuddy::CommandType userCommand = TextBuddy::determineCommandType(userInput);

	switch(userCommand) {
	case ADD:
		return TextBuddy::addText(userInput);

	case DELETE:
		return TextBuddy::deleteText(userInput);

	case DISPLAY:
		return TextBuddy::displayText();

	case CLEAR:
		return TextBuddy::clearText();

	case SORT:
		return TextBuddy::sortText();

	case SEARCH:
		return TextBuddy::searchText(userInput);

	case INVALID:
		return TextBuddy::showMessage(MESSAGE_ERROR_COMMAND_NOT_RECOGNIZED);

	case EXIT:
		return TextBuddy::exitTextBuddy();

	default:
		return TextBuddy::terminateTextBuddy(MESSAGE_ERROR_UNKNOWN);
	}
}

TextBuddy::CommandType TextBuddy::determineCommandType(std::string userInput) {
	std::string userCommand = TextBuddy::transformToLowercase(TextBuddy::getFirstWord(userInput));

	if(userCommand == "add" && TextBuddy::isValidCommandParameters(userInput)) {
		return TextBuddy::CommandType::ADD;
	} 
	else if(userCommand == "delete" && TextBuddy::isValidDeleteCommand(userInput)) {
		return TextBuddy::CommandType::DELETE;
	} 
	else if(userCommand == "display") {
		return TextBuddy::CommandType::DISPLAY;
	} 
	else if(userCommand == "clear") {
		return TextBuddy::CommandType::CLEAR;
	} 
	else if(userCommand == "sort") {
		return TextBuddy::CommandType::SORT;
	}
	else if(userCommand == "search" && TextBuddy::isValidCommandParameters(userInput)) {
		return TextBuddy::CommandType::SEARCH;
	}
	else if(userCommand == "exit") {
		return TextBuddy::CommandType::EXIT;
	} 
	else {
		return TextBuddy::CommandType::INVALID;
	}
}

bool TextBuddy::isValidCommandParameters(std::string userInput) {
	std::string text = TextBuddy::removeFirstWord(userInput);
	return (!text.empty());
}

bool TextBuddy::isValidDeleteCommand(std::string userInput) {
	std::string text = TextBuddy::removeFirstWord(userInput);
	return (!text.empty() && std::all_of(text.begin(), text.end(), ::isdigit));

}

//READING AND WRITING TO SAVE FILE*******************************************//
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
	for(int i = 0; i < TextBuddy::getTextStorageSize(); i++) {
		textFile << TextBuddy::getLineFromTextStorage(i) << std::endl;
	}
	textFile.close();
}

//DISPLAY MESSAGES TO USER***************************************************//
void showMessage(std::string message) {
	std::cout << message << std::endl;
}

void TextBuddy::showMessageWelcome() {
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), saveFileName.c_str());
	TextBuddy::showMessage(buffer);
}

//STRING MODIFIERS***********************************************************//
std::string TextBuddy::getFirstWord(std::string text) {
	std::istringstream iss(text);
	std::string firstWord;

	iss >> firstWord;

	return firstWord;
}

std::string TextBuddy::removeFirstWord(std::string text) {
	if(isOneWord(text)) {
		return "";
	}
	else {
		return TextBuddy::trimWhiteSpace(text.substr(text.find_first_of(" ")));
	}
}

bool TextBuddy::isOneWord(std::string text) {
	text = TextBuddy::trimWhiteSpace(text);
	return (std::all_of(text.begin(), text.end(), isalnum));
}

std::string TextBuddy::transformToLowercase(std::string text) {
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

std::string TextBuddy::trimWhiteSpace(const std::string& text) {
	return TextBuddy::trimLeft(TextBuddy::trimRight(text));
}

std::string TextBuddy::trimLeft(const std::string& text, const std::string& delimiters) {
	return text.substr(text.find_first_not_of(delimiters));
}

std::string TextBuddy::trimRight(const std::string& text, const std::string& delimiters) {
	return text.substr(0, text.find_last_not_of(delimiters) + 1);
}