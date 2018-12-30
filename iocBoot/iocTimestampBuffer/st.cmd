#!../../bin/linux-x86_64/evr_timestamp_buffer

#- EPICS IOC to simply return timestamps

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/evr_timestamp_buffer.dbd"
evr_timestamp_buffer_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadTemplate "db/evrTimestampBuffer.substitutions"
dbLoadRecords("db/evrTimestampBuffer.db", "CHIC_SYS=chic01:,CHOP_DRV=chop01:,DEVICE=dev01:")


cd "${TOP}/iocBoot/${IOC}"
iocInit

# Starts pvAccess server to be compatible with EPCIS v4/v7
#pvaSrvStart