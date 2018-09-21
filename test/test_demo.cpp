#include <gtest.h>

TEST(Demo, 2_plus_2_equals_4)
{
  EXPECT_EQ(4, 2 + 2);
}

TEST(Demo, 2_plus_2_not_equal_5)
{
  EXPECT_NE(5, 2 + 2);
}

TEST(Demo, DISABLED_true_is_true)
{
  EXPECT_TRUE(37);
}

TEST(Demo, floats_are_equal)
{
    float x = 1.f;
    float y = 1.f;

    EXPECT_EQ(x, y);
}

TEST(Demo, floats_are_equal_3)
{
    float x = 1.f;
    float y = 0.f;

    do {
        y = x;
        x = x + 1.f;
    } while( x != y);
    printf("%f\n", x);

    EXPECT_TRUE(x == y);
}

TEST(Demo, throws)
{
    std::string s = "hello!";

    EXPECT_ANY_THROW(throw(s));
}

TEST(Demo, throws_3)
{
    std::string s = "hello!";

    EXPECT_THROW(throw(s), std::string);
}

TEST(Demo, throws_2)
{
    std::string s = "hello!";

    EXPECT_NO_THROW(s);
}
