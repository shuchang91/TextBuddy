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

class TextBuddy {
public:
};

#endif