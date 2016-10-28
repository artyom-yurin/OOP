#include "stdafx.h"
#include "../dictionary/dictionary_functions.h"

BOOST_AUTO_TEST_SUITE(GetTranslate_function)

	BOOST_AUTO_TEST_CASE(when_word_have_not_translate)
	{
		std::stringstream buffer;
		std::map <std::string, std::string> dictionary;
		bool result = GetTranslate(buffer, dictionary, "word");
		BOOST_CHECK(!result);
	}

	BOOST_AUTO_TEST_CASE(correct_word_find_key)
	{
		std::stringstream buffer;
		std::map <std::string, std::string> dictionary;
		dictionary["word"] = "слово";
		bool result = GetTranslate(buffer, dictionary, "word");
		BOOST_CHECK(result);
		std::string line = "";
		getline(buffer, line);
		BOOST_CHECK_EQUAL(line, dictionary["word"]);
	}

	BOOST_AUTO_TEST_CASE(correct_word_find_value)
	{
		std::stringstream buffer;
		std::map <std::string, std::string> dictionary;
		dictionary["word"] = "слово";
		bool result = GetTranslate(buffer, dictionary, "слово");
		BOOST_CHECK(result);
		std::string line = "";
		getline(buffer, line);
		std::string correctLine = "word";
		BOOST_CHECK_EQUAL(line, correctLine);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AddNewWord_function)

	BOOST_AUTO_TEST_CASE(when_translation_empty)
	{
		std::stringstream inBuffer("");
		std::stringstream outBuffer;
		std::map <std::string, std::string> dictionary;
		bool result = AddNewWord(inBuffer, outBuffer, dictionary, "word");
		BOOST_CHECK(!result);
		std::string line = "";
		getline(outBuffer, line);
		std::string correctLine = "Слово \"word\" было проигнорировано.";
		BOOST_CHECK_EQUAL(line, correctLine);
	}

	BOOST_AUTO_TEST_CASE(correct_translation)
	{
		std::string translation = "слово";
		std::stringstream inBuffer(translation);
		std::stringstream outBuffer;
		std::map <std::string, std::string> dictionary;
		bool result = AddNewWord(inBuffer, outBuffer, dictionary, "word");
		BOOST_CHECK(result);
		BOOST_CHECK_EQUAL(translation, dictionary["word"]);
	}

BOOST_AUTO_TEST_SUITE_END()