/*! \file       main.c
 *  \author     Yury Osipov (yusosipov@ya.ru)
 *  \version    1.0.0.0
 *  \date       December, 2019
 *  \brief      Main file for conv test run.
 *
 *  This file contains the main and test functions.
 */

#include <stdio.h>

#include "conv.h"
#include "assert.h"

/*!
 * \brief Test for num_to_str function
 */
void test_num_to_str()
{
    uint64_t result = 0ULL;
    // Case 1
    // Buffer pointer is NULL
    // Expect:
    // 0 bytes written
    // conv_errno = CONV_ERR_NULL_POINTER
    result = num_to_str(255, NULL, 20);
    assert(result == 0);
    assert(conv_errno == CONV_ERR_NULL_POINTER);
    // Case 2
    // Size of buffer is 0
    // Expect:
    // 0 bytes written
    // conv_errno == CONV_ERR_NULL_POINTER
    result = 0;
    char buff[200] = {0};
    result = num_to_str(255, buff, 0);
    assert(result == 0);
    assert(conv_errno == CONV_ERR_ZERO_BUFFER_SIZE);
    // Case 3
    // Valid buffer and buffer size
    // number = 255 (in-range value)
    // Expect:
    // 4 bytes written (3 digits + end of line symbol)
    // conv_errno == CONV_NO_ERROR
    // buffer = "255"
    result = 0;
    memset(buff, 0x0, sizeof(buff));
    result = num_to_str(255, buff, sizeof(buff));
    assert(result == 4);
    assert(conv_errno == CONV_NO_ERROR);
    assert(buff[0]== '2');
    assert(buff[1]== '5');
    assert(buff[2]== '5');
    assert(buff[3]== '\0');
    // Case 4
    // Valid buffer and buffer size
    // number = 0 (minimum value)
    // Expect:
    // 2 bytes written (1 digit + end of line symbol)
    // conv_errno = CONV_NO_ERROR
    // buffer = "0"
    result = 0;
    memset(buff, 0x0, sizeof(buff));
    result = num_to_str(0, buff, sizeof(buff));
    assert(result == 2);
    assert(conv_errno == CONV_NO_ERROR);
    assert(buff[0]== '0');
    assert(buff[1]== '\0');
    // Case 5
    // Valid buffer and buffer size
    // number = 0ULL-1 (maximum value)
    // Expect:
    // 21 bytes written (20 digits + end of line symbol)
    // conv_errno = CONV_NO_ERROR
    // buffer = "18446744073709551615"
    result = 0;
    memset(buff, 0x0, sizeof(buff));
    result = num_to_str(0ULL-1, buff, sizeof(buff));
    assert(result == 21);
    assert(conv_errno == CONV_NO_ERROR);
    assert(strcmp(buff, "18446744073709551615") == 0);
}

/*!
 * \brief Test for str_to_num function
 */
void test_str_to_num()
{
    uint64_t result = 0;
    // Case 1
    // Buffer pointer is NULL
    // Expect:
    // result = 0
    // conv_errno = CONV_ERR_NULL_POINTER
    char buffer[200] = {0};
    result = str_to_num(NULL, sizeof (buffer));
    assert(result == 0);
    assert(conv_errno == CONV_ERR_NULL_POINTER);
    // Case 2
    // Size of buffer is 0
    // Expect:
    // result = 0
    // conv_errno = CONV_ERR_ZERO_BUFFER_SIZE
    result = 0;
    memset(buffer, 0x0, sizeof(buffer));
    result = str_to_num(buffer, 0);
    assert(result == 0);
    assert(conv_errno == CONV_ERR_ZERO_BUFFER_SIZE);
    // Case 3
    // Valid buffer and buffer size
    // buffer = "255"
    // Expect:
    // result = 255
    // conv_errno = CONV_NO_ERROR
    result = 0;
    memset(buffer, 0x0, sizeof(buffer));
    buffer[0] = '2';
    buffer[1] = '5';
    buffer[2] = '5';
    buffer[3] = '\0';
    result = str_to_num(buffer, sizeof (buffer));
    assert(result == 255);
    assert(conv_errno == CONV_NO_ERROR);
    // Case 4
    // Valid buffer and buffer size
    // buffer = "0"
    // Expect:
    // result = 0
    // conv_errno = CONV_NO_ERROR
    result = 0;
    memset(buffer, 0x0, sizeof(buffer));
    buffer[0] = '0';
    buffer[1] = '\0';
    result = str_to_num(buffer, sizeof (buffer));
    assert(result == 0);
    assert(conv_errno == CONV_NO_ERROR);
    // Case 5
    // Valid buffer and buffer size
    // buffer = "18446744073709551615"
    // Expect:
    // result = 18446744073709551615
    // conv_errno = CONV_NO_ERROR
    result = 0;
    memset(buffer, 0x0, sizeof(buffer));
    strcpy(buffer, "18446744073709551615");
    result = str_to_num(buffer, sizeof (buffer));
    assert(result == 18446744073709551615ULL);
    assert(conv_errno == CONV_NO_ERROR);
}

/*!
 * \brief Main function to run conv tests
 * \return 0
 */
int main()
{
    test_num_to_str();
    test_str_to_num();
    return 0;
}
