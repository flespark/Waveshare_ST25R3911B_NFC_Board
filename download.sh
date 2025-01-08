#!/bin/sh

# change cwd to porject root
cd $(dirname $0)
# set jlink_sn
jlink_sn=99999999
# flash
JLink -SelectEmuBySN ${jlink_sn} -CommanderScript device/flash_mcu.jlink