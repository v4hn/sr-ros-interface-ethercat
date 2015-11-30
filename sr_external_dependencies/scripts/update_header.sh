#!/bin/bash

TEMP_GIT_REPO_PATH=/tmp/firmware
PREVIOUS_PATH=`pwd`
START_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${START_PATH}

chmod -R a+w ../include/sr_external_dependencies/external
rm -rf ../include/sr_external_dependencies/external
mkdir -p ../include/sr_external_dependencies/external
cd "../include/sr_external_dependencies/external"

function copy_released_files {
    DIR_NAME=${1}
    GIT_PATH=${TEMP_GIT_REPO_PATH}/${2}

	echo "Updating ${DIR_NAME} from ${GIT_PATH}"
	mkdir -p ${DIR_NAME}
	cp -R ${GIT_PATH}/*.h ${GIT_PATH}/*.hpp ${GIT_PATH}/*.hex ${GIT_PATH}/*.txt ${DIR_NAME}
	rm -f ${DIR_NAME}/this_node.h

    #removes write access
	chmod -R a-w ${DIR_NAME}
}

rm -rf ${TEMP_GIT_REPO_PATH}
git clone https://github.com/shadow-robot/hand-firmware.git ${TEMP_GIT_REPO_PATH}

copy_released_files common PIC32/nodes/common
copy_released_files 0220_palm_edc PIC32/nodes/0220_palm_edc
copy_released_files 0320_palm_edc_muscle PIC32/nodes/0320_palm_edc_muscle
copy_released_files 0230_palm_edc_TS PIC32/nodes/0230_palm_edc_TS
copy_released_files simplemotor-bootloader EDC/simplemotor-bootloader

cd ${START_PATH}
cd ".."
chmod -R a+w ./released_firmware
rm -rf ./released_firmware
copy_released_files released_firmware EDC/simplemotor/released_firmware

rm -rf ${TEMP_GIT_REPO_PATH}

cd ${PREVIOUS_PATH}

echo "Firmware update finished"
