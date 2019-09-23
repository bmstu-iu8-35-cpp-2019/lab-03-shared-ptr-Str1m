// Copyright 2019 Sabitov Egor <q.st.stream@gmail.com>

#include <gtest/gtest.h>

#include <header.hpp>

TEST(shared_ptr, test_1){
SharedPtr<int> s_p;
EXPECT_EQ(s_p.use_count(), 0);
int* s = new int (1);
SharedPtr <int> s_p1(s);
SharedPtr <int> s_p2(s_p1);
EXPECT_EQ(s_p1.use_count(), 2);
EXPECT_EQ(s_p2.use_count(), 2);
EXPECT_EQ(*s_p2, 1);
}

TEST(shared_ptr, test_2){
int* s1 = new int (1);
int* s2 = new int (3);
SharedPtr<int> s_p1(s1);
SharedPtr<int> s_p2(s2);
s_p1 = s_p2;
EXPECT_EQ(s_p1.use_count(), 2);
EXPECT_EQ(*s_p1, 3);
}

TEST(shared_ptr, test_3){
int* s1 = new int (1);
int* s2 = new int (3);
SharedPtr<int> s_p1(s1);
SharedPtr<int> s_p2(s2);
s_p1.swap(s_p2);
EXPECT_EQ(s_p1.use_count(), s_p2.use_count());
EXPECT_EQ(s_p1, 3);
EXPECT_EQ(s_p2, 1);
}

TEST(shared_ptr, test_4){
int* s1 = new int (1);
SharedPtr<int> s_p1(s1);
SharedPtr<int> s_p2(s_p1);
EXPECT_EQ(s_p1.use_count(), 2);
s_p1.reset();
EXPECT_EQ(s_p1.use_count(), 0);
EXPECT_EQ(s_p2.use_count(), 1);
}
