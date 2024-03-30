#include <gtest/gtest.h>
#include "FixedPoint.h"

TEST(Create, default_constructor) {
	FixedPoint<8> p;
	EXPECT_EQ(p.toString(), std::string("0.00000000"));
}

TEST(Create, parameter_constructor) {
	FixedPoint<8> p(100500);
	EXPECT_EQ(p.toString(), std::string("100500.00000000"));
}

TEST(Create, negative_val_init) {
	FixedPoint<8> p(-273);
	EXPECT_EQ(p.toString(), std::string("-273.00000000"));
}

TEST(Create, compare_init) {
	FixedPoint<8> p1(-273);
	FixedPoint<8> p2(-273);
	EXPECT_EQ(p1.toString(), p2.toString());
}

TEST(Create, double_init_two_degree) {
	FixedPoint<2> p(0.5);
	EXPECT_EQ(p.toString(), std::string("0.50"));
}

TEST(Create, double_init_precision6) {
	FixedPoint<6> p(0.102503);
	EXPECT_EQ(p.toString(), std::string("0.102503")) << p.toString();
}

TEST(Create, double_init_precision12) {
	FixedPoint<12> p(0.102503);
	EXPECT_EQ(p.toString(), std::string("0.102503000000")) << p.toString();
}

TEST(Create, copy_constructor){
	FixedPoint<8> source(2.5);
	FixedPoint<8> dest = source;
	EXPECT_EQ(source.toString(), dest.toString());
}

TEST(Create, copy_constructor_different_precision){
	FixedPoint<8> source(2.5);
	FixedPoint<12> dest = source;
	EXPECT_EQ(source, dest);
}