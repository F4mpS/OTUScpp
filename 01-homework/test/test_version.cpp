#include "lib.cpp"

#include <gtest/gtest.h>

TEST(Lib, version_test)
{
	bool validVersion;

	if (version() > 0)
	{
		validVersion = true;
	}
	else
	{
		validVersion = false;
	}
	

	ASSERT_TRUE(validVersion) << "Vesion is invalid";
}

// BOOST_AUTO_TEST_SUITE(test_version)

// BOOST_AUTO_TEST_CASE(test_valid_version) {
// 	BOOST_CHECK(version() > 0);
// }

// BOOST_AUTO_TEST_SUITE_END()
