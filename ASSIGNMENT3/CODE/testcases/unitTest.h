/*
 * unitTest.h
 *
 *  Created on: Oct 22, 2019
 *      Author: SURAJ THITE , Atharv Desai
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_
#include "main.h"
#include "System.h"

//Test Suite to run tests
void Testsuite_RunTests(void);//TestSuit


//Test functions
void test_memory_allocation_limits(); //test 1
void test_equal_data();//test 2
void test_bit0_set();//test 3
void test_bit32_set();//test 4
void test_bit0_clear();//test 5
void test_bit32_clear();//test 6
void check_whether_32_bit();//test 7
void check_whether_16_bit();//test 8
void check_whether_8_bit();//test 9
void check_inversion();//test 10

#endif /* UNITTEST_H_ */
