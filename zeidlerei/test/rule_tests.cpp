#include <iostream>

#include "LeftInsertionRule.h"
#include "RightInsertionRule.h"
#include "LeftDeletionRule.h"
#include "RightDeletionRule.h"
#include "LeftSubstitutionRule.h"
#include "RightSubstitutionRule.h"
#include "AnyInsertionRule.h"
#include "AnyDeletionRule.h"
#include "AnySubstitutionRule.h"

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
	Word w1("abcde"), w2("bcdea");
	LeftDeletionRule r("a");
	std::vector<Word> result = r.apply(w1);
	ASSERT_TRUE(r.isApplicable(w1));
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].getContent(), "bcde");
	ASSERT_FALSE(r.isApplicable(w2));
}

TEST(Rules, RightDeletion)
{
	Word w1("abcde"), w2("eabcd");
	RightDeletionRule r("de");
	std::vector<Word> result = r.apply(w1);
	ASSERT_TRUE(r.isApplicable(w1));
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].getContent(), "abc");
	ASSERT_FALSE(r.isApplicable(w2));
}

TEST(Rules, LeftSubstitution)
{
	Word w1("abcde"), w2("bcdea");
	LeftSubstitutionRule r("a", "c");
	std::vector<Word> result = r.apply(w1);
	ASSERT_TRUE(r.isApplicable(w1));
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].getContent(), "cbcde");
	ASSERT_FALSE(r.isApplicable(w2));
}

TEST(Rules, RightSubstitution)
{
	Word w1("abcde"), w2("eabcd");
	RightSubstitutionRule r("de", "ba");
	std::vector<Word> result = r.apply(w1);
	ASSERT_TRUE(r.isApplicable(w1));
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].getContent(), "abcba");
	ASSERT_FALSE(r.isApplicable(w2));
}

TEST(Rules, AnyInsertion)
{
	Word w("abcd");
	AnyInsertionRule r("a");
	std::vector<Word> result = r.apply(w);

	std::vector<Word> expected = { Word("aabcd"), Word("aabcd"), Word("abacd"), Word("abcad"), Word("abcda") };
	ASSERT_EQ(result.size(), expected.size());
	for (int i = 0; i < expected.size(); ++i)
	{
		EXPECT_EQ(result[i], expected[i]);
	}
}

TEST(Rules, AnyDeletion)
{
	Word w("baaaacaa");
	AnyDeletionRule r("aa");

	ASSERT_TRUE(r.isApplicable(w));

	std::vector<Word> result = r.apply(w);

	std::vector<Word> expected = { Word("baacaa"), Word("baacaa"), Word("baacaa"), Word("baaaac") };
	ASSERT_EQ(result.size(), expected.size());
	for (int i = 0; i < expected.size(); ++i)
	{
		EXPECT_EQ(result[i], expected[i]);
	}
}

TEST(Rules, AnySubstitution)
{
	Word w("baaaac");
	AnySubstitutionRule r("aa", "d");

	ASSERT_TRUE(r.isApplicable(w));

	std::vector<Word> result = r.apply(w);

	std::vector<Word> expected = { Word("bdaac"), Word("badac"), Word("baadc") };
	ASSERT_EQ(result.size(), expected.size());
	for (int i = 0; i < expected.size(); ++i)
	{
		EXPECT_EQ(result[i], expected[i]);
	}
}

//int main(int argc, char** argv)
//{
//	testing::InitGoogleTest(&argc, argv);
//	RUN_ALL_TESTS();
//	std::getchar();
//}
