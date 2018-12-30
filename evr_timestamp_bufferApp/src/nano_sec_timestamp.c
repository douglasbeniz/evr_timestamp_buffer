#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>

static epicsInt64 nano_second_timestamp(aSubRecord *prec) {
    /* INPA and OUTA fields are accessed by precord->a and precord->vala*/
    /* epicsInt64 or epicsUInt64 */
    epicsTimeStamp tick;

    #ifdef DBR_INT64
        // TODO: remove this print
        // for test purposed only
        printf("Code where Base has INT64 support\n");
 
        if (!dbGetTimeStamp(&(prec->inpa),&tick)) {
            /* Constant to convert from EPICS to Unix epoch (20*365.25*24*3600 = 631152000) */
            const long epics2unixEpochFactor = 631152000;

            /* Store epoch and nano seconds from EPICS timestamp */
            epicsInt64 varSecPastEpoch  = ((epicsInt64)tick.secPastEpoch);
            epicsInt64 varNSec          = ((epicsInt64)tick.nsec);
            /* Store epoch converted from EPICS to Unix */
            epicsInt64 varUnixEpoch = (varSecPastEpoch + epics2unixEpochFactor);

            /* Store calculated timestamps:
                VALA: concatenated epoch and nano seconds as INT64;
                VALB: just epoch seconds part;
                VALC: just nano seconds part. */
            *(epicsInt64 *)prec->vala =  (varUnixEpoch * 1e9) + varNSec;
            *(epicsInt64 *)prec->valb = varUnixEpoch;
            *(epicsInt64 *)prec->valc = varNSec;

            // TODO: remove this print
            // for test purposed only
            printf("Timestamp: %lld \n", *(epicsInt64 *)prec->vala);
            return 0;
        } else {
            printf("Could not retrieve timestamp \n");
            return -1;
        }
    #else
         // TODO: remove this print
         // for test purposed only
         printf("Code for older versions\n");
         return -1;
    #endif
}

/* Note the function must be registered at the end!*/
epicsRegisterFunction(nano_second_timestamp);
