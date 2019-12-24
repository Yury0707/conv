/*! \file       conv.h
 *  \author     Yury Osipov (yusosipov@ya.ru)
 *  \version    1.0.0.0
 *  \date       December, 2019
 *  \brief      Conv module header file.
 *
 *  This file contains function prototypes of conv module and defined error codes.
 */

#ifndef CONV_H
#define CONV_H

#include <stddef.h>
#include <stdint.h>

/*! \enum conv_errno_t
 *  \brief Conv errors type.
 *
 *  This enum contains errors to generate on conv module
 *  operation to determine what happened.
 */
typedef enum
{
    CONV_NO_ERROR,              // No error
    CONV_ERR_NULL_POINTER,      // NULL pointer
    CONV_ERR_ZERO_BUFFER_SIZE,  // Zero buffer size
    CONV_ERR_BUFFER_OVERFLOW    // Buffer overflow (buffer too small)
} conv_errno_t;

/*!
 * \brief Global conv error code variable
 */
extern conv_errno_t conv_errno;

/*!
 * \brief num_to_str function
 * \param num - some number
 * \param str - buffer to hold the result
 * \param str_size - size of result buffer
 * \return Bytes have been written
 */
size_t num_to_str(uint64_t num, char *str, size_t str_size);

/*!
 * \brief str_to_num function
 * \param str - Input string buffer
 * \param str_len - Size of input buffer
 * \return Converted number from string
 */
uint64_t str_to_num(const char *str, size_t str_len);

#endif /* CONV_H */
