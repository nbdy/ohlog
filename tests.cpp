//
// Created by nbdy on 10.10.21.
//

#include "gtest/gtest.h"

#include "ohlog.h"

TEST(ohlog, GET_FILENAME_define) {
    EXPECT_EQ(GET_FILENAME,"tests.cpp");
}

TEST(ohlog, OHLOG_define) {
  EXPECT_NE(OHLOG, nullptr);
}
