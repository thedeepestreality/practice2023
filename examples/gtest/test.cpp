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

TEST(Create, negative_double_val) {
	FixedPoint<4> p(-2.4000);
	EXPECT_EQ(p.toString(), std::string("-2.4000")) << p.toString();
}

TEST(Create, negative_double_round) {
	FixedPoint<2> p(-2.446);
	EXPECT_EQ(p.toString(), std::string("-2.45")) << p.toString();
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

TEST(Compare, small_fixed_diff){
	FixedPoint<6> left(1.250000);
	FixedPoint<8> right(1.25000001);
	EXPECT_FALSE(left == right);
}

TEST(Compare, less_true){
	FixedPoint<6> left(1.250000);
	FixedPoint<8> right(1.25000001);
	EXPECT_TRUE(left < right);
}

TEST(Compare, less_false){
	FixedPoint<6> left(1.250000);
	FixedPoint<8> right(1.25000000);
	EXPECT_FALSE(left < right);
}

TEST(Arithmetics, assign_plus_same_size_no_overflow){
	FixedPoint<4> left(2.1234);
	FixedPoint<4> right(3.4321);
	FixedPoint<4> result(5.5555);
	left += right;
	EXPECT_EQ(left, result);
}

TEST(Arithmetics, assign_plus_same_size_simple_overflow){
	FixedPoint<4> left(2.1239);
	FixedPoint<4> right(3.4321);
	FixedPoint<4> result(5.5560);
	left += right;
	EXPECT_EQ(left, result);
}

TEST(Arithmetics, assign_plus_same_size_int_overflow){
	FixedPoint<4>   left(2.9939);
	FixedPoint<4>  right(3.4391);
	FixedPoint<4> result(6.4330);
	left += right;
	EXPECT_EQ(left, result);
}

TEST(Arithmetics, plus_same_size_no_overflow){
	FixedPoint<4> left(2.1234);
	FixedPoint<4> right(3.4321);
	FixedPoint<4> result(5.5555);
	EXPECT_EQ(left+right, result);
}

TEST(Arithmetics, plus_same_size_simple_overflow){
	FixedPoint<4> left(2.1239);
	FixedPoint<4> right(3.4321);
	FixedPoint<4> result(5.5560);
	EXPECT_EQ(left+right, result);
}

TEST(Arithmetics, plus_same_size_int_overflow){
	FixedPoint<4>   left(2.9939);
	FixedPoint<4>  right(3.4391);
	FixedPoint<4> result(6.4330);
	EXPECT_EQ(left+right, result);
}

TEST(Arithmetics, assign_plus_no_overflow){
	FixedPoint<4> left(2.1234);
	FixedPoint<8> right(3.43210000);
	FixedPoint<4> result(5.5555);
	left += right;
	EXPECT_EQ(left, result);
}

TEST(Arithmetics, assign_plus_simple_overflow){
	FixedPoint<4> left(2.1234);
	FixedPoint<8> right(3.43219000);
	FixedPoint<4> result(5.5556);
	left += right;
	EXPECT_EQ(left, result);
}

TEST(Arithmetics, plus_no_overflow){
	FixedPoint<4> left(2.1234);
	FixedPoint<8> right(3.43210000);
	FixedPoint<8> result(5.55550000);
	EXPECT_EQ(left+right, result);
}

TEST(Arithmetics, plus_negative){
	FixedPoint<4> left(2.5000);
	FixedPoint<4> right(-1.2000);
	FixedPoint<4> result_expected(1.3000);
	FixedPoint<4> result_fact = left+right;
	EXPECT_EQ(result_fact, result_expected) << result_fact.toString();
}