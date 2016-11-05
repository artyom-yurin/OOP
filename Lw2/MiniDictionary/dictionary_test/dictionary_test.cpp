#include "stdafx.h"
#include "../dictionary/dictionary_functions.h"
#include <boost/test/included/unit_test.hpp>

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

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

class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
public:
	SpecLogFormatter() : m_indent(0) {}
private:
	void test_unit_start(std::ostream &os,
		boost::unit_test::test_unit const& tu)
	{
		os << std::string(m_indent, ' ') <<
			boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		m_indent += 2;
	}
	void test_unit_finish(std::ostream &os,
		boost::unit_test::test_unit const& tu, unsigned long elapsed)
	{
		elapsed;
		tu;
		os;
		m_indent -= 2;
	}
	int m_indent;
};


boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
