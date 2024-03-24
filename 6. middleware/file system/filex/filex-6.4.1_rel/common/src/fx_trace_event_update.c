/***************************************************************************
 * Copyright (c) 2024 Microsoft Corporation 
 * 
 * This program and the accompanying materials are made available under the
 * terms of the MIT License which is available at
 * https://opensource.org/licenses/MIT.
 * 
 * SPDX-License-Identifier: MIT
 **************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** FileX Component                                                       */
/**                                                                       */
/**   Trace                                                               */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#ifndef FX_SOURCE_CODE
#define FX_SOURCE_CODE
#endif

#include "fx_api.h"

#ifdef TX_ENABLE_EVENT_TRACE


/* Include necessary system files.  */



/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _fx_trace_event_update                              PORTABLE C      */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function inserts a FileX event into the current trace buffer.  */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    event                                 Event pointer                 */
/*    timestamp                             Timestamp of the event        */
/*    event_id                              User Event ID                 */
/*    info_field_1                          First information field       */
/*    info_field_2                          First information field       */
/*    info_field_3                          First information field       */
/*    info_field_4                          First information field       */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Internal FileX Functions                                            */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     William E. Lamie         Initial Version 6.0           */
/*  09-30-2020     William E. Lamie         Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/
VOID  _fx_trace_event_update(TX_TRACE_BUFFER_ENTRY *event, ULONG timestamp, ULONG event_id, ULONG info_field_1, ULONG info_field_2, ULONG info_field_3, ULONG info_field_4)
{

TX_INTERRUPT_SAVE_AREA


    /* Disable interrupts.  */
    TX_DISABLE

    /* Determine if the event exists and is still the event originally inserted into the trace.  */
    if ((event) && (event -> tx_trace_buffer_entry_event_id == event_id) && (event -> tx_trace_buffer_entry_time_stamp == timestamp))
    {

        /* Yes, update this trace entry based on the info input parameters.  */

        /* Check for info field 1 update.  */
        if (info_field_1)
        {

            /* Yes, update info field 1.  */
            event -> tx_trace_buffer_entry_information_field_1 =  info_field_1;
        }

        /* Check for info field 2 update.  */
        if (info_field_2)
        {

            /* Yes, update info field 2.  */
            event -> tx_trace_buffer_entry_information_field_2 =  info_field_2;
        }

        /* Check for info field 3 update.  */
        if (info_field_3)
        {

            /* Yes, update info field 3.  */
            event -> tx_trace_buffer_entry_information_field_3 =  info_field_3;
        }

        /* Check for info field 4 update.  */
        if (info_field_4)
        {

            /* Yes, update info field 4.  */
            event -> tx_trace_buffer_entry_information_field_4 =  info_field_4;
        }
    }
    /* Restore interrupts.  */
    TX_RESTORE
}


#endif /* TX_ENABLE_EVENT_TRACE */

