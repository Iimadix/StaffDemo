#include "pch.h"
#include <gtest/gtest.h>
#include "../Zavod/Personal.h"

TEST(DriverTest, ConstructorAndGetters) {
    Driver d(1, "John Doe", 5);
    EXPECT_EQ(d.getId(), 1);
    EXPECT_EQ(d.getName(), "John Doe");
}