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
void test_temp_range(void); //Test 1
void test_temp_zero(void); //Test 2
void test_temp_return_value(void); //Test 3
void test_temp_high_register_val(void); //Test 4
void test_low_register_val(void); //Test 5
void test_config_rgister(void); //Test 6
void test_config_rgister_MSB(void); //Test 7
void test_config_rgister_LSB(void); //Test 8
void test_config_rgister_extended_mode(void); //Test 9
void test_config_rgister_alert_bit(void);//Test 10
void  Testsuite_RunTests(void);

#endif /* UNITTEST_H_ */
