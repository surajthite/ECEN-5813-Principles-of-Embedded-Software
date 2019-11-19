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

#include "uCUnit-v1.0.h"
#include "stdint.h"

#include "circularbuff.h"

//Test Suite to run tests
void Testsuite_RunTests(void);//TestSuit


//Test functions

void test_cbuff_init(void);
void test_cbuff_add(void);
void test_cbuff_wrap_add(void);
void test_cbuff_full(void);
void test_delete(void);
void test_head_ptr(void);
void test_cuff_resize(void);
void test_cbuff_destroy(void);

#endif /* UNITTEST_H_ */
