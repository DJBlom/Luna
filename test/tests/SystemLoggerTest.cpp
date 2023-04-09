/********************************************************************************
 * Contents: Template Test.
 * Author: Dawid Blom.
 * Date: March 28, 2023.
 *
 * Note: 
 *******************************************************************************/
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" 
{

}

using genericType = std::uint32_t;

/***************** TEST LIST ***************************************************
 * 1) Item 1.
 **/
TEST_GROUP(Template)
{
    void setup()
    {

    }

    void teardown()
    {
    }
};

TEST(Template, PassingTest)
{
    CHECK_EQUAL(1, 1);
}
