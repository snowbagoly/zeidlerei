#include "stdafx.h"  
#include <iostream>

#include "LeftInsertionRule.h"
#include "RightInsertionRule.h"
#include "LeftDeletionRule.h"

#include "gtest/gtest.h"

TEST(Rules, LeftInsertion)
{
	Word w("abcd");
	LeftInsertionRule r("e");
	std::vector<Word> result = r.apply(w);
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].getContent(), "eabcd");
}

TEST(Rules, RightInsertion)
{
	Word w("abcd");
	RightInsertionRule r("e");
	std::vector<Word> result = r.apply(w);
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].getContent(), "abcde");
}

TEST(Rules, LeftDeletion)
{
	Word w1("abcde"), w2("eabcd");
	LeftDeletionRule r("a");
	std::vector<Word> result = r.apply(w1);
	ASSERT_TRUE(r.isApplicable(w1));
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].getContent(), "bcde");
	ASSERT_FALSE(r.isApplicable(w2));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	std::getchar();
}
