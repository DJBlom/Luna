/********************************************************************************
 * Contents: Test Fixture for algorithms.
 * Author: Dawid Blom.
 * Date: January 6, 2023.
 *
 * Note: 
 *******************************************************************************/

#include "CppUTest/TestHarness.h"

extern "C" 
{

}

using genericType = std::uint32_t;

/**
 **/
TEST_GROUP(RingBufferTest)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(RingBufferTest, EnsureCircularBehaviourWhenDequeueingLessItems)
{
    CHECK_EQUAL(1, 1);
}
