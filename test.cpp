#include "pch.h"
#include <climits>

// STD-001-CPP: Validate the range before converting
// an unsigned long integer to a signed char.
bool safeConversion(unsigned long int u_a, signed char& sc)
{
    if (u_a <= SCHAR_MAX)
    {
        sc = (signed char)u_a;
        return true;
    }
    else
    {
        return false;
    }
}

// Google Test fixture
class DataTypeTest : public ::testing::Test
{
protected:
    signed char result = 0;
};

// Positive Test: Verify a valid integer converts correctly.
TEST_F(DataTypeTest, ValidIntegerConversion)
{
    unsigned long int value = 100;

    // Verify the conversion succeeds
    ASSERT_TRUE(safeConversion(value, result));

    // Verify the converted value matches the original
    EXPECT_EQ(100, result);
}

// Positive Test: Verify the minimum valid value converts correctly.
TEST_F(DataTypeTest, MinimumBoundaryConversion)
{
    unsigned long int value = 0;

    // Verify the conversion succeeds
    ASSERT_TRUE(safeConversion(value, result));

    // Verify the converted value remains 0
    EXPECT_EQ(0, result);
}

// Positive Test: Verify the maximum valid value converts correctly.
TEST_F(DataTypeTest, MaximumBoundaryConversion)
{
    unsigned long int value = SCHAR_MAX;

    // Verify the conversion succeeds
    ASSERT_TRUE(safeConversion(value, result));

    // Verify the converted value matches SCHAR_MAX
    EXPECT_EQ(SCHAR_MAX, result);
}

// Negative Test: Verify a value above SCHAR_MAX is rejected.
TEST_F(DataTypeTest, RejectValueAboveMaximum)
{
    unsigned long int value = SCHAR_MAX + 1;

    // Verify the unsafe conversion is rejected
    ASSERT_FALSE(safeConversion(value, result));

    // Verify the original result was not modified
    EXPECT_EQ(0, result);
}

// Negative Test: Verify ULONG_MAX is rejected to prevent data loss.
TEST_F(DataTypeTest, RejectUnsignedLongMaximum)
{
    unsigned long int value = ULONG_MAX;

    // Verify the unsafe conversion is rejected
    ASSERT_FALSE(safeConversion(value, result));

    // Verify the result was not modified
    EXPECT_EQ(0, result);
}
