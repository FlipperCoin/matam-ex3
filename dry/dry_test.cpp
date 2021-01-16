//
// Created by Itai on 16/01/2021.
//
#include "gtest/gtest.h"
#include "dry.cpp"

using namespace dry;
using std::vector;

class SliceTests : public ::testing::Test {

protected:
    vector<int> *vec;

    void SetUp() override {
        vec = new std::vector<int>({0,1,2,3,4,5,6,7});
    }

    void TearDown() override {
        delete vec;
    }
};

TEST_F(SliceTests, NormalSlice) {
    vector<int> sliced_expected({2,3,4,5,6});
    vector<int> sliced = slice(*vec, 2, 1, 7);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, FromStartSlice) {
    vector<int> sliced_expected({0,1,2,3,4,5,6});
    vector<int> sliced = slice(*vec, 0, 1, 7);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, ToFinishSlice) {
    vector<int> sliced_expected({2,3,4,5,6,7});
    vector<int> sliced = slice(*vec, 2, 1, 8);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, FromStartToFinishSlice) {
    vector<int> sliced_expected({0,1,2,3,4,5,6,7});
    vector<int> sliced = slice(*vec, 0, 1, 8);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, FromStartToStartSlice) {
    vector<int> sliced_expected;
    vector<int> sliced = slice(*vec, 0, 1, 0);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, FromStartToStartSlice2) {
    vector<int> sliced_expected;
    vector<int> sliced = slice(*vec, 5, 1, 5);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, FromFinishToFinishSlice) {
    vector<int> sliced_expected({7});
    vector<int> sliced = slice(*vec, 7, 1, 8);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, StartOverStopSlice) {
    vector<int> sliced_expected;
    vector<int> sliced = slice(*vec, 6, 1, 5);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, StepsSlice) {
    vector<int> sliced_expected({1,4,7});
    vector<int> sliced = slice(*vec, 1, 3, 8);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, StepsSlice2) {
    vector<int> sliced_expected({2,5});
    vector<int> sliced = slice(*vec, 2, 3, 8);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, StepsSlice3) {
    vector<int> sliced_expected({1,4});
    vector<int> sliced = slice(*vec, 1, 3, 6);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, StepsSlice4) {
    vector<int> sliced_expected({0,2,4,6});
    vector<int> sliced = slice(*vec, 0, 2, 8);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, StepsSlice5) {
    vector<int> sliced_expected({1,3,5});
    vector<int> sliced = slice(*vec, 1, 2, 7);

    EXPECT_EQ(sliced_expected, sliced);
}
TEST_F(SliceTests, InvalidStep) {
    vector<int> sliced_expected({0,1,2,3,4,5,6,7});
    EXPECT_THROW(vector<int> sliced = slice(*vec, 0, -1, 8), BadInput);
    EXPECT_THROW(vector<int> sliced = slice(*vec, 0, 0, 8), BadInput);
}
TEST_F(SliceTests, InvalidStart) {
    vector<int> sliced_expected({0,1,2,3,4,5,6,7});
    EXPECT_THROW(vector<int> sliced = slice(*vec, -1, 1, 8), BadInput);
    EXPECT_THROW(vector<int> sliced = slice(*vec, 8, 1, 8), BadInput);
    EXPECT_THROW(vector<int> sliced = slice(*vec, 9, 1, 8), BadInput);
}
TEST_F(SliceTests, InvalidStop) {
    vector<int> sliced_expected({0,1,2,3,4,5,6,7});
    EXPECT_THROW(vector<int> sliced = slice(*vec, 2, 1, -1), BadInput);
    EXPECT_THROW(vector<int> sliced = slice(*vec, 2, 1, 9), BadInput);
}

//int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}