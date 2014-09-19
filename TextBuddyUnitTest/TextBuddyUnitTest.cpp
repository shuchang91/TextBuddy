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

			TextBuddy::addText(input);

			Assert::AreEqual(expectedSize, TextBuddy::getTextStorageSize());
			Assert::AreEqual(expectedOutput, TextBuddy::getLineFromTextStorage(0));
			}
	};
}