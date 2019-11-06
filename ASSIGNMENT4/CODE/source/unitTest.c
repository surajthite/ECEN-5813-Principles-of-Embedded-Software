/*
 * unitTest.c
 *
 *  Created on: Oct 22, 2019
 *      Author: SURAJ THITE ,ATHARV
 */

#include "uCUnit-v1.0.h"
#include "stdint.h"
#include "main.h"
#include "i2c.h"


//test-example-1
/*******************************************************************************************************
 * Function test_temp_range(void)
 * Description : this function tests whether read temperature is between 0 and 75 degrees C
 * @input:void
 * @Return :void
 *******************************************************************************************************/

static void test_temp_range(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST1:Checking for Range of Temperature");
	uint16_t  temp;
	temp = i2c_read_temperature(0x90,0x00);
	printf("\n \r %d",temp);
	UCUNIT_CheckIsInRange(temp, 0, 50); //FAIL
	UCUNIT_TestcaseEnd();
}


/*******************************************************************************************************
 * Function Name:static void test_temp_zero(void)
 * Description : This function tests whether the temperature is zero or not.
 * @input:void
 * @Return :void
 *******************************************************************************************************/

//test-example-2
static void test_temp_zero(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST2:Check for Zero Temperature");
	uint16_t temp;
	temp = i2c_read_temperature(0x90,0x00);
	UCUNIT_CheckIsEqual(temp,0); //FAIL
	UCUNIT_TestcaseEnd();
}

/*******************************************************************************************************
 * Function Name:test_temp_return_value(void)
 * Description : this function tests whether MSB is set at the memory location
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-3
static void test_temp_return_value(void)
{

	UCUNIT_TestcaseBegin(" \n \r TEST3:Whether value returned by the i2c read temperature function is a 16 bit value");
	uint16_t temp;
	temp = i2c_read_temperature(0x90,0x00);
	UCUNIT_CheckIs16Bit(temp);  //PASS
	UCUNIT_TestcaseEnd();

}

/*******************************************************************************************************
 * Function Name:static void test_temp_high_register_val(void)
 * Description : This function tests for  HIGH REGISTER
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-4
static void test_temp_high_register_val(void)
{
	UCUNIT_TestcaseBegin(" \n \r TEST4:Whether high register value is 75..");
	uint16_t temp;
	temp = i2c_read_temperature(0x90,0x11);
	UCUNIT_CheckIsEqual(temp ,75); //FAIL
	UCUNIT_TestcaseEnd();
}

/*******************************************************************************************************
 * Function Name:static void test_temp_low_register_val(void)
 * Description : This function tests for  TLOW REGISTER
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-5
static void test_low_register_val(void)
{
	UCUNIT_TestcaseBegin(" \n \r TEST5:Whether Low Register Value is 75 ...");
	uint16_t temp;
	temp = i2c_read_temperature(0x90,0x10);
	UCUNIT_CheckIsEqual(temp ,80); //FAIL
	UCUNIT_TestcaseEnd();
}

/*******************************************************************************************************
 * Function Name: test_config_rgister(void)
 * Description :	test whether value returned by CONFIG_REGISTER_VALUE is a word or not.
 * @input:void
 * @Return :void.
 *******************************************************************************************************/

//test-example-6
static void test_config_rgister(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST6:Checking whether bit 32 is clear");
	uint16_t temp;
	temp = CONFIG_REGISTER_VALUE();
	UCUNIT_CheckIs16Bit(temp);	//PASS
}


/*******************************************************************************************************
 * Function Name: test_config_rgister_MSB(void)
 * Description :test whether MSB of config register is set or not.
 * @input:void
 * @Return :void
 *******************************************************************************************************/

//test-example-7
static void test_config_rgister_MSB(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST7:Test Whether config Register value is set");
	uint16_t temp;
	temp = CONFIG_REGISTER_VALUE();
	UCUNIT_CheckIsBitSet(temp, 16); //FAIL
}


/*******************************************************************************************************
 * Function Name: test_config_rgister_LSB(void)
 * Description :test whether LSB of config register is set or not.
 * @input:void
 * @Return :void.
 *******************************************************************************************************/

//test-example-8
static void test_config_rgister_LSB(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST8:Test Whether LSB config Register value is set");
	uint16_t temp;
	temp = CONFIG_REGISTER_VALUE();
	printf("\n \r %d",temp);
	UCUNIT_CheckIsBitSet(temp,0);	//FAIL
}
/*******************************************************************************************************
 * Function Name: test_config_rgister_extended_mode(void)
 * Description :test whether E bit of config register is set or not.
 * @input:void
 * @Return :void.
 *******************************************************************************************************/

//test-example-8
static void test_config_rgister_extended_mode(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST7:Test Extended MOde");
	uint16_t temp;
	temp = CONFIG_REGISTER_VALUE();
	UCUNIT_CheckIsBitSet(temp,4);  //PASS
}



/*******************************************************************************************************
 * Function Name:void check_inversion(void)
 * Description : this function checks the inversion
 * @input:void
 * @Return :void
 *******************************************************************************************************/
//test-example-10
static void test_config_rgister_alert_bit(void)
{
	UCUNIT_TestcaseBegin("\n \r TEST10:Alert Bit");
	uint16_t temp;
	temp = CONFIG_REGISTER_VALUE();
	UCUNIT_CheckIsBitSet(temp,5);	//PASS
}

/*******************************************************************************************************
 * Function Name:Testsuite_RunTests(void)
 * Description : this function runs all the ten tests in the test suite
 * @input:void
 * @Return :void
 *******************************************************************************************************/
void  Testsuite_RunTests(void)
{
	test_temp_range(); //Test 1
	test_temp_zero(); //Test 2
	test_temp_return_value(); //Test 3
	test_temp_high_register_val(); //Test 4
	test_low_register_val(); //Test 5
	test_config_rgister(); //Test 6
	test_config_rgister_MSB(); //Test 7
	test_config_rgister_LSB(); //Test 8
	test_config_rgister_extended_mode();//Test 9
	test_config_rgister_alert_bit();//Test 10
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
