/**
* @file
* @author Steve Karg
* @date October 2019
* @brief Header file for a basic WriteProperty service handler
*
* @section LICENSE
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef HANDLER_WRITE_PROPERTY_H
#define HANDLER_WRITE_PROPERTY_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
/* BACnet Stack defines - first */
#include "bacnet/bacdef.h"
/* BACnet Stack API */
#include "bacnet/bacenum.h"
#include "bacnet/apdu.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    BACNET_STACK_EXPORT
    void handler_write_property(
        uint8_t * service_request,
        uint16_t service_len,
        BACNET_ADDRESS * src,
        BACNET_CONFIRMED_SERVICE_DATA * service_data);

    BACNET_STACK_EXPORT
    bool WPValidateString(
        BACNET_APPLICATION_DATA_VALUE * pValue,
        int iMaxLen,
        bool bEmptyAllowed,
        BACNET_ERROR_CLASS * pErrorClass,
        BACNET_ERROR_CODE * pErrorCode);

    BACNET_STACK_EXPORT
    bool WPValidateArgType(
        BACNET_APPLICATION_DATA_VALUE * pValue,
        uint8_t ucExpectedType,
        BACNET_ERROR_CLASS * pErrorClass,
        BACNET_ERROR_CODE * pErrorCode);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif