#include "stdafx.h"
#include "Car.h"
#include <boost/test/included/unit_test.hpp>

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsEngineOn());
	}

	BOOST_AUTO_TEST_CASE(gear_0_by_default)
	{
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}

	BOOST_AUTO_TEST_CASE(speed_0_by_default)
	{
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

	BOOST_AUTO_TEST_CASE(cant_be_turned_off)
	{
		BOOST_CHECK(!car.TurnOffEngine());
	}

	BOOST_AUTO_TEST_CASE(cant_set_gear_when_turned_off)
	{
		BOOST_CHECK(!car.SetGear(1));
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}

	BOOST_AUTO_TEST_CASE(cant_set_speed_when_turned_off)
	{
		BOOST_CHECK(!car.SetSpeed(10));
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		car.TurnOnEngine();
		BOOST_CHECK(car.IsEngineOn());
	}

	struct when_turned_on_ : CarFixture
	{
		when_turned_on_()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)

		BOOST_AUTO_TEST_CASE(cant_be_turned_on)
		{
			BOOST_CHECK(!car.TurnOnEngine());
		}

		BOOST_AUTO_TEST_CASE(can_be_turned_off_when_speed_0_and_gear_0)
		{
			car.TurnOffEngine();
			BOOST_CHECK(!car.IsEngineOn());
		}

		BOOST_AUTO_TEST_CASE(can_set_gear_1_N_R)
		{
			car.SetGear(-1);
			BOOST_CHECK_EQUAL(car.GetGear(), -1);
			car.SetGear(1);
			BOOST_CHECK_EQUAL(car.GetGear(), 1);
			car.SetGear(0);
			BOOST_CHECK_EQUAL(car.GetGear(), 0);
		}

		struct when_gear_1_ : when_turned_on_
		{
			when_gear_1_()
			{
				car.SetGear(1);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_gear_1, when_gear_1_)

			BOOST_AUTO_TEST_CASE(can_set_speed_0_to_30)
			{
				car.SetSpeed(30);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
			}

			BOOST_AUTO_TEST_CASE(can_set_gear_2_when_speed_20)
			{
				car.SetSpeed(10);
				BOOST_CHECK(!car.SetGear(2));
				car.SetSpeed(20);
				car.SetGear(2);
				BOOST_CHECK_EQUAL(car.GetGear(), 2);
			}

			struct when_direction_is_forward_ : when_gear_1_
			{
				when_direction_is_forward_()
				{
					car.SetSpeed(10);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(when_direction_is_forward, when_direction_is_forward_)

				BOOST_AUTO_TEST_CASE(cant_set_gear_R_when_gear_not_1_or_N_and_speed_not_0)
				{
					BOOST_CHECK(!car.SetGear(-1));
				}

				BOOST_AUTO_TEST_CASE(can_set_gear_N)
				{
					BOOST_CHECK(car.SetGear(0));
				}

			BOOST_AUTO_TEST_SUITE_END()

			struct when_direction_is_reverse_ : when_gear_1_
			{
				when_direction_is_reverse_()
				{
					car.SetGear(-1);
					car.SetSpeed(10);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(when_direction_is_reverse, when_direction_is_reverse_)

				BOOST_AUTO_TEST_CASE(cant_set_gear_1)
				{
					BOOST_CHECK(!car.SetGear(1));
				}

				BOOST_AUTO_TEST_CASE(can_set_gear_N)
				{
					BOOST_CHECK(car.SetGear(0));
				}

			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

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