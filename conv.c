/*! \file       conv.c
 *  \author     Yury Osipov (yusosipov@ya.ru)
 *  \version    1.0.0.0
 *  \date       December, 2019
 *  \brief      Conv module header file.
 *
 *  This file contains conv module functions code.
 */

#include "conv.h"

conv_errno_t conv_errno = CONV_NO_ERROR;

static inline uint32_t get_digit_count(uint64_t num)
{
    uint32_t ret_val = 0;

    char found = 0;

    if(num == 0)
    {
        ;
    }
    else
    {
        uint64_t p = 10;
        for (ret_val=1; ret_val<20; ret_val++) {
            if (num < p)
            {
                found = 1;
                break;
            }
            p = 10*p;
        }
        if(found == 0)
        {
            ret_val = 20;
        }
    }

    return ret_val;
}

size_t num_to_str(uint64_t num, char *str, size_t str_size)
{
    size_t ret_val = 0;

    if(str == NULL)
    {
        conv_errno = CONV_ERR_NULL_POINTER;
    }
    else if(str_size == 0)
    {
        conv_errno = CONV_ERR_ZERO_BUFFER_SIZE;
    }
    else if (num == 0)
    {
        if(str_size < 2)
        {
            conv_errno = CONV_ERR_BUFFER_OVERFLOW;
        }
        else
        {
            str[ret_val] = '0';
            ret_val = 1;
            str[ret_val] = '\0';
            ret_val = 2;
        }
    }
    else
    {
        uint32_t digit_count = get_digit_count(num);

        uint32_t offset = digit_count;

        if(str_size < digit_count + 1)
        {
            conv_errno = CONV_ERR_BUFFER_OVERFLOW;
        }
        else
        {
            while(offset > 0)
            {
                str[offset - 1] = num % 10 + '0';
                num = num/10;
                ret_val++;
                offset--;
            }
            str[ret_val] = '\0';
            ret_val++;
        }
        conv_errno = CONV_NO_ERROR;
    }

    return ret_val;
}

uint64_t str_to_num(const char *str, size_t str_len)
{
    uint64_t ret_val = 0;

    if(str == NULL)
    {
        conv_errno = CONV_ERR_NULL_POINTER;
    }
    else if(str_len == 0)
    {
        conv_errno = CONV_ERR_ZERO_BUFFER_SIZE;
    }
    else
    {
        size_t dig_count = 0;
        for(size_t i = 0; i<str_len; i++)
        {
            if(str[i] == '\0')
            {
                dig_count = i;
                break;
            }
        }
        if(dig_count == 0)
        {
            // Consider digit count equal to buffer length if no end of string met
            dig_count = str_len;
        }

        size_t i = 0;
        uint64_t p = 10;
        while (dig_count > 0)
        {
            if(i!=0)
            {
                ret_val += ((uint64_t)str[dig_count-1] - '0') * p;
                p*=10;
            }
            else
            {
                ret_val += ((uint64_t)str[dig_count-1] - '0');
            }
            i++;
            dig_count--;
        }
        conv_errno = CONV_NO_ERROR;
    }

    return ret_val;
}
