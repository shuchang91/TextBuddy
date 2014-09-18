// TextBuddy++ is a message management tool that can store your messages in a text
// file. While the storage text file is human readable, it should not be modified
// by the user as it may cause compatibility issues with TextBuddy++. The length
// of each string entered should not exceed 900 characters.
//
// The available inputs are
// 1) add <string>     : adds <string> to the database
// 2) delete <index>   : deletes the string at the index specified
// 3) display          : displays all messages stored in the database
// 4) clear            : clears all messages stored in the database
// 5) sort             : sorts all messages alphabetically and displays the result
// 6) search <keyword> : searches for <keyword> in all messages and displays the results
// 7) exit             : exits TextBuddy++
//
// Update: As compared to TextBuddy, TextBuddy++ is able to recognize an incorrect 
//		   input format and will prompt the user to enter the command in the correct
//         format.
//
// @author: Shu Chang, 2014

#ifndef TEXTBUDDY_H
#define TEXTBUDDY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

enum CommandType {
		ADD, DELETE, DISPLAY, CLEAR, SORT, SEARCH, INVALID, EXIT
	};

const int MAX_STRING_LENGTH = 1000;
const int VALID_ARGC = 1;
const int SAVE_FILE_LOCATION_IN_ARGV = 2;
const std::string VALID_SAVE_FILE_EXTENSION = "txt";

const std::string MESSAGE_WELCOME = 
	"Welcome to TextBuddy++. %s is ready for use.";
const std::string MESSAGE_TERMINATED = 
	"TextBuddy++ terminated.";
const std::string MESSAGE_ADDED = 
	"Added to %s: \"%s\".";
const std::string MESSAGE_DELETED = 
	"Deleted from %s: \"%s\".";
const std::string MESSAGE_CLEARED = 
	"All messages cleared from %s.";

const std::string MESSAGE_ERROR_INITIALIZATION = 
	"Please initialize TextBuddy++ with the format TextBuddy.exe <SaveFile>.txt.";
const std::string MESSAGE_ERROR_COMMAND_NOT_RECOGNIZED = 
	"Command not recognized. Please enter one of the following commands:\nAdd <string>\nDelete <index>\nDisplay\nClear\nSort\nSearch <keyword>\nExit\n";
const std::string MESSAGE_ERROR_DELETION_FAILED = 
	"Deletion failed because message database is empty or index does not exist.";
const std::string MESSAGE_ERROR_SEARCH_NOT_FOUND = 
	"Search string was not found.";
const std::string MESSAGE_ERROR_UNKNOWN = 
	"Unknown error encountered. Please contact the developer.";

class TextBuddy {

private:
	static char buffer[MAX_STRING_LENGTH];
	static std::string saveFileName;
	static std::vector<std::string> textStorage;
	static std::vector<int> searchStorage;

public:
	//***********************************************************************//
	//Runs TextBuddy++.
	static void runTextBuddy(char* argv[]);
	//Exits TextBuddy++.
	static void exitTextBuddy();
	//Terminates TextBuddy++ with the given error message.
	static void terminateTextBuddy(std::string errorMessage);
	//Checks if the initialization parameters are valid.
	static bool isValidInitialization(int argc, char* argv[]);
	//Checks if the save file specified is a txt file.
	static bool isValidSaveFile(std::string saveFile);

	//***********************************************************************//
	//Reads the content from the save file and copies it to internal storage.
	static void readFromSaveFile();
	//Saves the content from internal storage to the save file.
	static void saveToSaveFile();

	//***********************************************************************//
	//Displays the message specified to the user.
	static void showMessage(std::string message);
	//Displays the formatted welcome message.
	static void showMessageWelcome();

	//***********************************************************************//
	//Setter and Getter functions for the internal storage components.
	static std::string getBuffer() { return buffer;}
	static void setSaveFileName(std::string saveFile) { saveFileName = saveFile; }
	static std::string getSaveFileName() { return saveFileName; }
	static void saveLineToStorage(std::string input) { textStorage.push_back(input); }
	static std::string getLineFromTextStorage(int index) { return textStorage[index]; }
	static int getTextStorageSize() { return textStorage.size(); }
	static void saveIndexToSearchStorage(int index) { searchStorage.push_back(index); }
	static int getIndexFromSearchStorage(int index) { return searchStorage[index]; }
	static int getSearchStorageSize() { return searchStorage.size(); }
};

#endif