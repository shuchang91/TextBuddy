#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyUnitTest {		
	TEST_CLASS(TextBuddyUnitTest) {
	public:

		TEST_METHOD(SetSaveFile) {
			std::string input = "saveFile.txt";
			std::string expectedOutput = "saveFile.txt";
			TextBuddy::setSaveFileName(input);

			Assert::AreEqual(expectedOutput, TextBuddy::getSaveFileName());
		}

		TEST_METHOD(AddMessage) {
			std::string input = "add test message";
			std::string expectedOutput = "test message";
			unsigned int expectedSize = 1;

			TextBuddy::executeInput(input);

			Assert::AreEqual(expectedSize, TextBuddy::getTextStorageSize());
			Assert::AreEqual(expectedOutput, TextBuddy::getLineFromTextStorage(0));
		}

		TEST_METHOD(DeleteMessage) {
			std::string input = "delete 1";			
			unsigned int expectedSize = 0;

			TextBuddy::executeInput(input);
			Assert::AreEqual(expectedSize, TextBuddy::getTextStorageSize());
		}

		TEST_METHOD(AddMultipleMessage) {
			std::string input1 = "add first test";			
			std::string input2 = "add second test";			
			std::string input3 = "add third test";
			std::string expectedOutput1 = "first test";
			std::string expectedOutput2 = "second test";
			std::string expectedOutput3 = "third test";
			unsigned int expectedSize = 3;

			TextBuddy::executeInput(input1);
			TextBuddy::executeInput(input2);
			TextBuddy::executeInput(input3);

			Assert::AreEqual(expectedSize, TextBuddy::getTextStorageSize());
			Assert::AreEqual(expectedOutput1, TextBuddy::getLineFromTextStorage(0));
			Assert::AreEqual(expectedOutput2, TextBuddy::getLineFromTextStorage(1));
			Assert::AreEqual(expectedOutput3, TextBuddy::getLineFromTextStorage(2));
		}

		TEST_METHOD(AddEmptyMessage) {
			std::string input = "add   ";
			unsigned int expectedSize = 3;

			TextBuddy::executeInput(input);

			Assert::AreEqual(expectedSize, TextBuddy::getTextStorageSize());
		}

		TEST_METHOD(DeleteNonexistentMessage) {
			std::string input = "delete 5";			
			unsigned int expectedSize = 3;

			TextBuddy::executeInput(input);
			Assert::AreEqual(expectedSize, TextBuddy::getTextStorageSize());
		}

		TEST_METHOD(ClearMessages) {
			std::string input = "clear";			
			unsigned int expectedSize = 0;

			TextBuddy::executeInput(input);
			Assert::AreEqual(expectedSize, TextBuddy::getTextStorageSize());
		}
	};
}