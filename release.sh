#!/bin/bash
rm -rf release
mkdir -p release

cp -rf MyOfflineProcess *.{hpp,cpp,txt,json} LICENSE release/

mv release score-addon-my-offline-process
7z a score-addon-my-offline-process.zip score-addon-my-offline-process
