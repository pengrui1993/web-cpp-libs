#include<iostream>
#include<gtest/gtest.h>

#include<string>
using std::operator""s;
TEST(TestName,Subtest_1){
	ASSERT_TRUE(1==1);
}
TEST(TestName,Subtest_2){
	ASSERT_FALSE(1==1);
}
TEST(Compare,equal){
	ASSERT_EQ("a"s,"a"s);
}

/*
	EXPECT_... non-fatal failure
	ASSERT_... fatal failure	
	== != < <= > >=
	EXPECT_EQ
	...

	ASSERT_EQ
	ASSERT_NE
	ASSERT_LT
	ASSERT_LE
	ASSERT_GT
	ASSERT_GE
*/
int main(int argc,char*argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

