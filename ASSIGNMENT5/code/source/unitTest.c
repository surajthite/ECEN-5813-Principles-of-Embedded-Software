/*
 * unitTest.c
 *
 *  Created on: Oct 22, 2019
 *      Author: SURAJ THITE ,ATHARV
 */

#include "unitTest.h"
cbuff* test ;

//test-example-1
/*******************************************************************************************************
 * Function:static void test_cbuff_init(void)
 * Description :Test to verify initialization of circular buffer
 * @input:void
 * @Return :void
 *******************************************************************************************************/

void test_cbuff_init(void)
{
	UCUNIT_TestcaseBegin("TEST1:Initialization of Circular Buffer");
	test= malloc(sizeof(cbuff));
	test->cbuffptr = malloc(sizeof(int8_t) * 10);
	cbuff_status s = cbuff_init(test,10);
	UCUNIT_CheckIsEqual(s,cbuff_init_success); //PASS
	UCUNIT_TestcaseEnd();
}


/*******************************************************************************************************
 * Function Name:static void test_cbuff_add(void)
 * Description : Test for addition of data into circular buffer
 * @input:void
 * @Return :void
 *******************************************************************************************************/

//test-example-2
void test_cbuff_add(void)
{
	UCUNIT_TestcaseBegin("TEST2:Test For addition of Elements to circular Buffer");
	cbuff_status s;
	for (int i=0;i<9;i++)
			{
				s = cbuff_add(test,i);
			}
	cbuff_print(test);
	UCUNIT_CheckIsEqual(s,cbuff_success); //PASS
	UCUNIT_TestcaseEnd();
}

/*******************************************************************************************************
 * Function Name:static void test_cbuff_wrap_add(void)
 * Description : Test for wrap addition
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-3
void test_cbuff_wrap_add(void)
{
	UCUNIT_TestcaseBegin("TEST3: Test for Wrap Addition");
	cbuff_status s;
	s = cbuff_add(test,9);
	UCUNIT_CheckIsEqual(s,wrap_add); //PASS
	UCUNIT_TestcaseEnd();
}

/*******************************************************************************************************
 * Function Name:static void test_cbuf_full(void)
 * Description : This function tests whether circular buffer is full or not
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-4
void test_cbuff_full(void)
{
	UCUNIT_TestcaseBegin("TEST4: Test for Buffer Full");
	cbuff_status s;
	s = cbuff_add(test,5);
	UCUNIT_CheckIsEqual(s,cbuff_full); //PASS
	UCUNIT_TestcaseEnd();
}
/*******************************************************************************************************
 * Function Name:static void test_delete(void)
 * Description : Test for checking successful deletion of an element from circular buffer
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-5
void test_delete(void)
{

	UCUNIT_TestcaseBegin("TEST3:Test Whether deletion was Successful in the Circular Buffer");
	uint8_t sar =0;
	cbuff_status s = cbuff_delete(test,&sar);
	cbuff_print(test);
	UCUNIT_CheckIsEqual(s,cbuff_success); //PASS
	UCUNIT_TestcaseEnd();

}


/*******************************************************************************************************
 * Function Name: static void test_head_ptr(void)
 * Description : Test to check validity of circular buffer head pointer
 * @input:void
 * @Return :void.
 *******************************************************************************************************/

//test-example-6
void test_head_ptr(void)
{
	UCUNIT_TestcaseBegin("TEST6:Test for checking whether head is within bounds of circular buffer");
	cbuff_status s = verify_ptr(test->head,test);
	UCUNIT_CheckIsEqual(s,ptr_valid); //PASS
	UCUNIT_TestcaseEnd();
}


/*******************************************************************************************************
 * Function Name: test_cuff_resize(void)
 * Description :test for resizing of the buffer.
 * @input:void
 * @Return :void
 *******************************************************************************************************/

//test-example-7
void test_cuff_resize(void)
{
	UCUNIT_TestcaseBegin("TEST7:Test for Resizing of Circular Buffer");
	cbuff_status s = cbuff_resize(test,20);
	printf(" No of Elements in Circular Buffer :: %d     ",test->size);
	UCUNIT_CheckIsEqual(s,cbuff_success); //PASS
	UCUNIT_TestcaseEnd();
}

/*******************************************************************************************************
 * Function Name: test_cbuff_destroy(void)
 * Description :Test for destroying of Circular Buffer
 * @input:void
 * @Return :void
 *******************************************************************************************************/

//test-example-8
void test_cbuff_destroy(void)
{
	UCUNIT_TestcaseBegin("TEST8:Test for Deletion of Circular Buffer");
	cbuff_status s =  cbuff_destroy(test);
	UCUNIT_CheckIsEqual(s,destroy_pass); //PASS
	UCUNIT_TestcaseEnd();
}



/*******************************************************************************************************
 * Function Name:Testsuite_RunTests(void)
 * Description : this function runs all the ten tests in the test suite
 * @input:void
 * @Return :void
 *******************************************************************************************************/
void  Testsuite_RunTests(void)
{
	test_cbuff_init();
	test_cbuff_add();
	test_cbuff_wrap_add();
	test_cbuff_full();
	test_delete();
	test_head_ptr();
	test_cuff_resize();
	test_cbuff_destroy();
}

//int main(void)
//{
//    UCUNIT_Init();
//    UCUNIT_WriteString("\n**************************************");
//    UCUNIT_WriteString("uCUnit demo application");
//    UCUNIT_WriteString(__DATE__);
//    UCUNIT_WriteString("\nTime:     ");
//    UCUNIT_WriteString(__TIME__);
//
//    UCUNIT_WriteString("\n**************************************");
////    Testsuite_RunTests();
////    UCUNIT_Shutdown();
//
//    return 0;
//}
