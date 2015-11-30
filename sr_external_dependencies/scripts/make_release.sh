#!/bin/bash

START_PATH=`pwd`

#We copy the released protocol files to the correct directory
cd ${START_PATH}
chmod -R a+w released/*

#copy the currently used protocol and compiled firmware to the release
echo "Releasing protocol"
cp -r include/sr_external_dependencies/external/* released/external/
echo "Releasing firmware"
cp -r compiled_firmware/* released/

chmod -R a-w released/*

#TODO: write the current versions of the host software / firmware in a file.
pushd /tmp
rm -rf ./firmware
git clone https://github.com/shadow-robot/hand-firmware.git firmware

VERS_GIT_FIRMWARE=`git --git-dir /tmp/firmware/.git log --pretty=format:%h -n 1`
VERS_GIT_ETHERCAT=`git --git-dir $(dirname $(rosstack find shadow_robot_ethercat))/.git log --pretty=format:%h -n 1`
VERS_GIT_SHADOW=`git --git-dir $(dirname $(rosstack find shadow_robot))/.git log --pretty=format:%h -n 1`

rm -rf ./firmware

popd

echo "git_firmware:"${VERS_GIT_FIRMWARE}" ; git_shadow:"${VERS_GIT_SHADOW} "; git_ethercat:"${VERS_GIT_ETHERCAT} > tested_version.yaml

git tag --force "git_firmware:"${VERS_GIT_FIRMWARE}"__git_shadow_"${VERS_GIT_SHADOW}"__git_ethercat_"${VERS_GIT_ETHERCAT}
