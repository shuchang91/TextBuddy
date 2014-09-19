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

static const int MAX_STRING_LENGTH = 1000;
static const int VALID_ARGC = 2;
static const int SAVE_FILE_LOCATION_IN_ARGV = 1;
static const std::string VALID_SAVE_FILE_EXTENSION = "txt";

static const std::string MESSAGE_WELCOME = 
	"Welcome to TextBuddy++. %s is ready for use.";
static const std::string MESSAGE_TERMINATED = 
	"TextBuddy++ terminated.";
static const std::string MESSAGE_ADDED = 
	"Added to %s: \"%s\".";
static const std::string MESSAGE_DELETED = 
	"Deleted from %s: \"%s\".";
static const std::string MESSAGE_CLEARED = 
	"All messages cleared from %s.";

static const std::string MESSAGE_ERROR_INITIALIZATION = 
	"Please initialize TextBuddy++ with the format TextBuddy.exe <SaveFile>.txt.";
static const std::string MESSAGE_ERROR_COMMAND_NOT_RECOGNIZED = 
	"Command not recognized. Please enter one of the following commands:\nAdd <string>\nDelete <index>\nDisplay\nClear\nSort\nSearch <keyword>\nExit\n";
static const std::string MESSAGE_ERROR_DELETION_FAILED = 
	"Deletion failed because message database is empty or index does not exist.";
static const std::string MESSAGE_ERROR_SEARCH_NOT_FOUND = 
	"Search string was not found.";
static const std::string MESSAGE_ERROR_UNKNOWN = 
	"Unknown error encountered. Please contact the developer.";

static std::string saveFileName;
static std::vector<std::string> textStorage;
static std::vector<int> searchStorage;
static char buffer[MAX_STRING_LENGTH];

class TextBuddy {

public:

	enum CommandType {
		ADD, DELETE, DISPLAY, CLEAR, SORT, SEARCH, INVALID, EXIT
	};

//TEXTBUDDY++ ENTRY POINT************************************************//
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

//MAIN PROGRAM LOGIC*****************************************************//
	//Prompts for and takes in a line of string as user input.
	static std::string getUserInput();
	//Executes the input specified.
	static void executeInput(std::string userInput);
	//Determines the command type of the user input.
	static CommandType determineCommandType(std::string userInput);
	//Checks the validity of a command regarding the parameter(s) specified. 
	//Returns true if there is a parameter when the program expects one.
	static bool isValidCommandParameters(std::string userInput);
	//Checks the validity of a delete command parameter. 
	//Returns true if parameter specified is an integer.
	static bool isValidDeleteCommand(std::string userInput);

//READING AND WRITING TO SAVE FILE***************************************//
	//Reads the content from the save file and copies it to internal storage.
	static void readFromSaveFile();
	//Saves the content from internal storage to the save file.
	static void saveToSaveFile();

//ADD LOGIC**************************************************************//
	//Adds the text specified to the save file.
	static void addText(std::string userInput);

//DELETE LOGIC***********************************************************//
	//Deletes the line of text specified by the index from the save file.
	static void deleteText(std::string userInput);
	//Checks the validity of the index specified. 
	//Returns true if index exists.
	static bool isValidDeletionIndex(unsigned int index);
	//Deletes the line of text specified by the index from the internal textStorage vector.
	//Returns the deleted line of text as a string.
	static std::string deleteFromTextStorage(unsigned int index);

//DISPLAY LOGIC**********************************************************//
	//Displays all text in the save file.
	static void displayText();

//CLEAR LOGIC************************************************************//
	//Deletes all lines of text in the save file.
	static void clearText();

//SORT LOGIC*************************************************************//
	//Sorts all lines of text in the save file alphabetically.
	static void sortText();
	//Sorts all lines of text in the internal textStorage vector alphabetically.
	static void sortTextStorage();

//SEARCH LOGIC***********************************************************//

//DISPLAY MESSAGES TO USER***********************************************//
	//Displays the message specified to the user.
	static void showMessage(std::string message);
	//Displays the formatted welcome message.
	static void showMessageWelcome();
	//Displays confirmation that the given text has been added.
	static void showMessageAdded(std::string text);
	//Displays confirmation that the text specified has been deleted.
	static void showMessageDeleted(std::string deletedLine);
	//Displays confirmation that all text has been deleted.
	static void showMessageCleared();

//STRING MODIFIERS*******************************************************//
	//Returns the first word in a line of text.
	static std::string getFirstWord(std::string text);
	//Returns a line of text with the first word removed.
	static std::string removeFirstWord(std::string text);
	//Checks if a line of text contains only one word.
	static bool isOneWord(std::string text);
	//Returns a line of text converted to lowercase.
	static std::string transformToLowercase(std::string text);
	//Returns a line of text with whitespaces at its two ends removed.
	static std::string trimWhiteSpace(const std::string& text);
	//Returns a line of text with whitespaces at its beginning removed.
	static std::string trimLeft(const std::string& text, const std::string& delimiters = " \f\n\r\t\v");
	//Returns a line of text with whitespaces at its end removed.
	static std::string trimRight(const std::string& text, const std::string& delimiters = " \f\n\r\t\v");

//GETTER AND SETTER FUNCTIONS FOR INTERNAL STORAGE COMPONENTS************//
	static std::string getBuffer();
	
	//Functions for the save file name
	static void setSaveFileName(std::string saveFile);
	static std::string getSaveFileName();

	//Functions for the internal text storage vector
	static void saveLineToStorage(std::string input);
	static std::string getLineFromTextStorage(int index);
	static void eraseLineFromTextStorage(int index);
	static void clearTextStorage();
	static unsigned int getTextStorageSize();

	//Function for the internal search storage vector
	static void saveIndexToSearchStorage(int index);
	static int getIndexFromSearchStorage(int index);
	static void clearSearchStorage();
	static unsigned int getSearchStorageSize();
};

#endif