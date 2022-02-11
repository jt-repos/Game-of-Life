#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "tests.h"
#include "unity.h"
#include "logic.h"
#include "file_operations.h"

void TestSetEvos()
{
    int evos;
    evos = SetEvos(5);
    TEST_ASSERT_MESSAGE(evos <= 64 && evos > 0, "number of evolutions is not in range 1-64.");
    TEST_ASSERT_NOT_NULL_MESSAGE(&evos, "numEvos returned null.");

    evos = SetEvos(0);
    TEST_ASSERT_MESSAGE(evos == 0, "number of evolutions is not equal to 0.");
    TEST_ASSERT_NOT_NULL_MESSAGE(&evos, "numEvos returned null.");

    evos = SetEvos(-1);
    TEST_ASSERT_MESSAGE(evos == 0, "number of evolutions is not equal to 0.");
    TEST_ASSERT_NOT_NULL_MESSAGE(&evos, "numEvos returned null.");

    evos = SetEvos(-20);
    TEST_ASSERT_MESSAGE(evos == 0, "number of evolutions is not equal to 0.");
    TEST_ASSERT_NOT_NULL_MESSAGE(&evos, "numEvos returned null.");

    evos = SetEvos(63);
    TEST_ASSERT_MESSAGE(evos <= 64 && evos > 0, "number of evolutions is not in range 1-64.");
    TEST_ASSERT_NOT_NULL_MESSAGE(&evos, "numEvos returned null.");

    evos = SetEvos(64);
    TEST_ASSERT_MESSAGE(evos <= 64 && evos > 0, "number of evolutions is not in range 1-64.");
    TEST_ASSERT_NOT_NULL_MESSAGE(&evos, "numEvos returned null.");

    evos = SetEvos(65);
    TEST_ASSERT_MESSAGE(evos == 0, "number of evolutions is not equal to 0.");
    TEST_ASSERT_NOT_NULL_MESSAGE(&evos, "numEvos returned null.");
}

void TestSetupArray()
{
    int error, cell;
    error = SetupArray("test_files/test.txt");
    TEST_ASSERT_MESSAGE(error == 0, "error is not correctly set");
    cell = GetArrayElem(0, 0, 0);
    TEST_ASSERT_MESSAGE(cell == 0, "cell 0, 0, 0 is not 0");
    cell = GetArrayElem(0, 4, 4);
    TEST_ASSERT_MESSAGE(cell == 1, "cell 0, 4, 4 is not 1");
    cell = GetArrayElem(0, 13, 10);
    TEST_ASSERT_MESSAGE(cell == 0, "cell 0, 13, 10 is not 0");
    cell = GetArrayElem(0, 7, 2);
    TEST_ASSERT_MESSAGE(cell == 1, "cell 0, 7, 2 is not 1");
    cell = GetArrayElem(0, 10, 5);
    TEST_ASSERT_MESSAGE(cell == 0, "cell 0, 10, 5 is not 1");
    cell = GetArrayElem(0, 50, 50);
    TEST_ASSERT_MESSAGE(cell == 0, "cell 0, 50, 50 is not 0");
    ResetArray();

    error = SetupArray("test_files/test_broken.txt");
    TEST_ASSERT_MESSAGE(error == 1, "error is not correctly set");
    ResetArray();

    error = SetupArray("test_files/test_broken2.txt");
    TEST_ASSERT_MESSAGE(error == 1, "error is not correctly set");

    error = SetupArray("test_files/test_broken3.txt");
    TEST_ASSERT_MESSAGE(error == 1, "error is not correctly set");
}

void TestCalculateEvolutions()
{
    int cell;
    SetupArray("test_files/test2.txt");
    SetEvos(5);
    CalculateEvolutions();
    cell = GetArrayElem(1, 1, 1);
    TEST_ASSERT_MESSAGE(cell == 0, "cell 1, 1, 1 is not 0");
    cell = GetArrayElem(1, 2, 2);
    TEST_ASSERT_MESSAGE(cell == 1, "cell 1, 2, 2 is not 1");
    cell = GetArrayElem(1, 1, 3);
    TEST_ASSERT_MESSAGE(cell == 1, "cell 1, 1, 3 is not 1");

    cell = GetArrayElem(5, 1, 1);
    TEST_ASSERT_MESSAGE(cell == 0, "cell 1, 1, 1 is not 0");
    cell = GetArrayElem(5, 2, 2);
    TEST_ASSERT_MESSAGE(cell == 0, "cell 1, 2, 2 is not 0");
    cell = GetArrayElem(5, 1, 3);
    TEST_ASSERT_MESSAGE(cell == 1, "cell 1, 1, 3 is not 1");

    cell = GetArrayElem(15, 1, 1);
    TEST_ASSERT_MESSAGE(cell == 0, "cell in grid out of range is not 0");
    cell = GetArrayElem(15, 2, 2);
    TEST_ASSERT_MESSAGE(cell == 0, "ccell in grid out of range is not 0");
    cell = GetArrayElem(15, 1, 3);
    TEST_ASSERT_MESSAGE(cell == 0, "cell in grid out of range is not 0");
}


void setUp()
{

}

void tearDown()
{

}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(TestSetEvos);
    RUN_TEST(TestSetupArray);
    RUN_TEST(TestCalculateEvolutions);
    return UNITY_END();
}
