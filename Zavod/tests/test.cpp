#include "pch.h"
#include "../Zavod/Personal.h"
#include "gtest/gtest.h"

TEST(DriverTest, CalcPayment) {
    Driver d(1, "Ivanov", 300);
    d.setWorkTime(10);
    d.calc();
    EXPECT_EQ(d.getPayment(), 300 * 10 + static_cast<int>(0.05 * 300 * 10));
}


