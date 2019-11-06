/*
 * unitTest.c
 *
 *  Created on: Oct 22, 2019
 *      Author: SURAJ THITE ,ATHARV
 */

#include "uCUnit-v1.0.h"
#include "stdint.h"
#include "main.h"
uint32_t  *ptr_test_case;


//test-example-1
/*******************************************************************************************************
 * Function Name:test_memory_allocation_limits(void)
 * Description : this function tests the successful allocation of the memory
 * @input:void
 * @Return :void
 *******************************************************************************************************/

static void test_memory_allocation_limits(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST1:Checking for returned pointer of memory allocation");
	uint32_t  *ptr1;
	ptr1 =  allocate_words(1);
	UCUNIT_CheckIsNull(ptr1);//fail
	UCUNIT_TestcaseEnd();//Fail
	ptr_test_case = ptr1;
}
/*******************************************************************************************************
 * Function Name:test_equal_data(void)
 * Description : this function tests for the equal data at the memory location
 * @input:void
 * @Return :void
 *******************************************************************************************************/

//test-example-2
static void test_equal_data(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST2:check for equality of data in two locations ");
	uint32_t *ptr1 =ptr_test_case;
	//write_pattern(ptr1,4,5);
	UCUNIT_CheckIsEqual(*ptr1,*(ptr1+1)); //Fail
	UCUNIT_CheckIsEqual(*ptr1,*ptr1); //Pass
	UCUNIT_TestcaseEnd(); //Fail
}
/*******************************************************************************************************
 * Function Name:test_bit0_set(void)
 * Description : this function tests whether MSB is set at the memory location
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-3
static void test_bit0_set(void)
{

	UCUNIT_TestcaseBegin(" \n \r TEST3:Checking whether bit 0 is set");
	uint32_t  *ptr1;
	ptr1 = ptr_test_case;
	write_memory(*ptr1, 0xFFFFFFFF);
	UCUNIT_CheckIsBitSet(*ptr1,0);//Pass
	UCUNIT_TestcaseEnd();

}

/*******************************************************************************************************
 * Function Name:test_bit32_set(void)
 * Description : this function tests whether MSB is set at the memory location
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-4
static void test_bit32_set(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST4:Checking whether bit 32 is set");
	uint32_t  *ptr1;
	ptr1 = ptr_test_case;
	write_memory(*ptr1, 0xFFFFFFFF);
	UCUNIT_CheckIsBitSet(*ptr1,32);//Pass
	UCUNIT_TestcaseEnd();

}

/*******************************************************************************************************
 * Function Name:void test_bit0_clear(void)
 * Description : this function tests  whether LSB is clear in the data at memory location
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-5
static void test_bit0_clear(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST5:Checking whether bit 0 is clear");
	uint32_t  *ptr1;
	ptr1 = ptr_test_case;
	write_memory(*ptr1, 0xFFFFFFFF);
	UCUNIT_CheckIsBitClear(*ptr1,0);//Fail
	UCUNIT_TestcaseEnd();
}

/*******************************************************************************************************
 * Function Name:test_bit32_clear(void)
 * Description : this function tests whether MSB is clear in the data at a memory location
 * @input:void
 * @Return :void
 *******************************************************************************************************/

//test-example-6
static void test_bit32_clear(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST6:Checking whether bit 32 is clear");
	uint32_t  *ptr1;
	ptr1 = ptr_test_case;
	write_memory(*ptr1, 0xFFFFFFFF);
	UCUNIT_CheckIsBitClear(*ptr1,32);//Fail
	UCUNIT_TestcaseEnd();
}


/*******************************************************************************************************
 * Function Name:void check_whether_32_bit(void)
 * Description : this function tests the whether data is 32 bit data in the memory location
 * @input:void
 * @Return :void
 *******************************************************************************************************/

//test-example-7
static void check_whether_32_bit(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST7:Checking whether value at location is 32 bit or not ");
	uint32_t  *ptr1;
	ptr1 = ptr_test_case;
	write_memory(*ptr1, 0xFFFFFFFF);
	UCUNIT_CheckIs32Bit(*ptr1); //Pass
	UCUNIT_TestcaseEnd();
}

/*******************************************************************************************************
 * Function Name:void check_whether_16_bit(void)
 * Description : this function tests the whether data is 16 bit data in the memory location
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-8
static void check_whether_16_bit(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST8:Checking whether value at location is 16 bit or not ");
	uint32_t  *ptr1;
	ptr1 = ptr_test_case;
	write_memory(*ptr1, 0xFFFFFFFF);
	UCUNIT_CheckIs16Bit(*ptr1); //Fail
	UCUNIT_TestcaseEnd();

}

/*******************************************************************************************************
 * Function Name:void check_whether_8_bit(void)
 * Description : this function tests the whether data is 8 bit data in the memory location
 * @input:void
 * @Return :void
 *******************************************************************************************************/

//test-example-9
static void check_whether_8_bit(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST9:Checking whether value at location is 8 bit or not ");
	uint32_t  *ptr1;
	ptr1 = ptr_test_case;
	write_memory(*ptr1, 0xFFFFFFFF);
	UCUNIT_CheckIs16Bit(*ptr1); //Fail
	UCUNIT_TestcaseEnd();

}


/*******************************************************************************************************
 * Function Name:void check_inversion(void)
 * Description : this function checks the inversion
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-10
static void check_inversion(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST10:Checking for inversion");
	uint32_t  *ptr1;
	ptr1 = ptr_test_case;
	*(ptr1+4) = 0;
	invert_block(ptr1+4,1);
	UCUNIT_CheckIsEqual(0xFFFFFFFF,ptr1+4);
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
	test_memory_allocation_limits(); //test 1
	test_equal_data();//test 2
	test_bit0_set();//test 3
	test_bit32_set();//test 4
	test_bit0_clear();//test 5
	test_bit32_clear();//test 6
	check_whether_32_bit();//test 7
	check_whether_16_bit();//test 8
	check_whether_8_bit();//test 9
	check_inversion();//test 10
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
