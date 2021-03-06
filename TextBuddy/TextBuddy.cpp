#include "TextBuddy.h"

void main(int argc, char* argv[]) {
	if(TextBuddy::isValidInitialization(argc, argv)) {
		TextBuddy::runTextBuddy(argv);
	}
	else {
		TextBuddy::terminateTextBuddy(MESSAGE_ERROR_INITIALIZATION);
	}
}

//TEXTBUDDY++ ENTRY POINT****************************************************//
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
void TextBuddy::readFromSaveFile() {
	std::ifstream textFile;
	std::string currentLine;

	textFile.open(TextBuddy::getSaveFileName());
	while(std::getline(textFile, currentLine)) {
		TextBuddy::saveLineToStorage(currentLine);
	}
	textFile.close();
}

void TextBuddy::saveToSaveFile() {
	std::ofstream textFile;

	textFile.open(TextBuddy::getSaveFileName());
	for(unsigned int i = 0; i < TextBuddy::getTextStorageSize(); i++) {
		textFile << TextBuddy::getLineFromTextStorage(i) << std::endl;
	}
	textFile.close();
}

//ADD LOGIC******************************************************************//
void TextBuddy::addText(std::string userInput) {
	std::string text = TextBuddy::removeFirstWord(userInput);

	TextBuddy::saveLineToStorage(text);
	TextBuddy::saveToSaveFile();
	TextBuddy::showMessageAdded(text);
}

//DELETE LOGIC***************************************************************//
void TextBuddy::deleteText(std::string userInput) {
	int index = std::stoi(TextBuddy::removeFirstWord(userInput)) - 1;

	if(TextBuddy::isValidDeletionIndex(index)) {
		std::string deletedLine = TextBuddy::deleteFromTextStorage(index);
		TextBuddy::saveToSaveFile();
		TextBuddy::showMessageDeleted(deletedLine);
	}
	else {
		TextBuddy::showMessage(MESSAGE_ERROR_DELETION_FAILED);
	}
}

bool TextBuddy::isValidDeletionIndex(unsigned int index) {
	return (index >= 0 && index < TextBuddy::getTextStorageSize());
}

std::string TextBuddy::deleteFromTextStorage(unsigned int index) {
	std::string deletedLine = TextBuddy::getLineFromTextStorage(index);
	TextBuddy::eraseLineFromTextStorage(index);

	return deletedLine;
}

//DISPLAY LOGIC**************************************************************//
void TextBuddy::displayText() {
	for(unsigned int i = 0; i < TextBuddy::getTextStorageSize(); i++) {
		std::cout << i + 1 << ". " << TextBuddy::getLineFromTextStorage(i) << std::endl;
	}
}

//CLEAR LOGIC****************************************************************//
void TextBuddy::clearText() {
	TextBuddy::clearTextStorage();
	TextBuddy::saveToSaveFile();
	TextBuddy::showMessageCleared();
}

//SORT LOGIC*****************************************************************//
void TextBuddy::sortText() {
	TextBuddy::sortTextStorage();
	TextBuddy::saveToSaveFile();
	TextBuddy::displayText();
}

void TextBuddy::sortTextStorage() {
	std::stable_sort(textStorage.begin(), textStorage.end(), TextBuddy::isAlphabeticallySmaller);
}

bool TextBuddy::isAlphabeticallySmaller(std::string first, std::string second) {
	return (TextBuddy::transformToLowercase(first) < TextBuddy::transformToLowercase(second));
}

//SEARCH LOGIC***************************************************************//
void TextBuddy::searchText(std::string userInput) {
	std::string searchString = TextBuddy::removeFirstWord(userInput);

	TextBuddy::searchTextStorage(searchString);
	if(TextBuddy::hasSearchResults()) {
		TextBuddy::displaySearchResults();
	}
	else {
		TextBuddy::showMessage(MESSAGE_ERROR_SEARCH_NOT_FOUND);
	}
}

void TextBuddy::searchTextStorage(std::string searchString) {
	TextBuddy::clearSearchStorage();

	for(unsigned int i = 0; i < TextBuddy::getTextStorageSize(); i++) {
		if(isFoundInLine(searchString, i)) {
			TextBuddy::saveIndexToSearchStorage(i);
		}
	}
}

bool TextBuddy::isFoundInLine(std::string searchString, int index) {
	std::size_t isFound = TextBuddy::getLineFromTextStorage(index).find(searchString);
	return (isFound != std::string::npos);
}

bool TextBuddy::hasSearchResults() {
	return (TextBuddy::getSearchStorageSize() > 0);
}

void TextBuddy::displaySearchResults() {
	for(unsigned int i = 0; i < TextBuddy::getSearchStorageSize(); i++) {
		TextBuddy::displaySingleLine(TextBuddy::getIndexFromSearchStorage(i));
	}
}

void TextBuddy::displaySingleLine(int index) {
	std::cout << index + 1 << ". " << TextBuddy::getLineFromTextStorage(index) << std::endl;
}

//DISPLAY MESSAGES TO USER***********************************************//
void TextBuddy::showMessage(std::string message) {
	std::cout << message << std::endl;
}

void TextBuddy::showMessageWelcome() {
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), saveFileName.c_str());
	TextBuddy::showMessage(buffer);
}

void TextBuddy::showMessageAdded(std::string text) {
	sprintf_s(buffer, MESSAGE_ADDED.c_str(), saveFileName.c_str(), text.c_str());
	TextBuddy::showMessage(buffer);
}

void TextBuddy::showMessageDeleted(std::string deletedLine) {
	sprintf_s(buffer, MESSAGE_DELETED.c_str(), saveFileName.c_str(), deletedLine.c_str());
	TextBuddy::showMessage(buffer);
}

void TextBuddy::showMessageCleared() {
	sprintf_s(buffer, MESSAGE_CLEARED.c_str(), saveFileName.c_str());
	TextBuddy::showMessage(buffer);
}

//STRING MODIFIERS***********************************************************//
std::string TextBuddy::getFirstWord(std::string text, const std::string& delimiters) {
	return text.substr(0, text.find_first_of(delimiters));
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

//GETTER AND SETTER FUNCTIONS FOR INTERNAL STORAGE COMPONENTS************//
std::string TextBuddy::getBuffer() {
	return buffer;
}

void TextBuddy::setSaveFileName(std::string saveFile) {
	saveFileName = saveFile; 
}

std::string TextBuddy::getSaveFileName() {
	return saveFileName; 
}

void TextBuddy::saveLineToStorage(std::string input) {
	textStorage.push_back(input); 
}

std::string TextBuddy::getLineFromTextStorage(int index) {
	return textStorage[index]; 
}

void TextBuddy::eraseLineFromTextStorage(int index) { 
	textStorage.erase(textStorage.begin() + index); 
}

void TextBuddy::clearTextStorage() { 
	textStorage.clear(); 
}

unsigned int TextBuddy::getTextStorageSize() {
	return textStorage.size();
}

void TextBuddy::saveIndexToSearchStorage(int index) { 
	searchStorage.push_back(index); 
}

int TextBuddy::getIndexFromSearchStorage(int index) { 
	return searchStorage[index]; 
}

void TextBuddy::clearSearchStorage() { 
	searchStorage.clear(); 
}

unsigned int TextBuddy::getSearchStorageSize() { 
	return searchStorage.size(); 
}