# protocal-adpater

[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Language](https://img.shields.io/badge/language-c++11-red.svg)](https://en.cppreference.com/)
[![Platform](https://img.shields.io/badge/platform-linux-lightgrey.svg)](https://img.shields.io/badge/platform-linux-lightgrey.svg)

[[中文]](README_CN.md)

## What
Multi-protocol adapter implemented based on the [cpp-tbox](https://github.com/cpp-main/cpp-tbox) framework.

## Feature

- Support Uart, MQTT, TCP as server, TCP as client, UDP

## Build
### Step 1：build [cpp-tbox](https://github.com/cpp-main/cpp-tbox) first  
```
git clone https://github.com/cpp-main/cpp-tbox.git
cd cpp-tbox;
STAGING_DIR=$HOME/.tbox make 3rd-party modules RELEASE=1
cd -
```

### Step 2：build protocal-adapter
```
git clone https://github.com/cpp-main/protocal-adapter.git
cd protocal-adapter/src;
make
```
After build, we will see executable file `adapter` at src/.

## Run
Cmd:
```
./adapter ../config/default.conf
```
Note:

- If there is a problem with not having permission to open the serial port file, add sudo and execute again.
- You can modify config/default.conf as needed.

## Config
See config/default.conf for details, or read the source code.

## Feedback
- Issue: Any questions are welcome to communicate in issue
- WeChat: hevake_lee
- QQ group: 738084942 (cpp-tbox 技术交流)

## Encourage us
If you find it useful, please give me more encouragement.
You can do these:

- Follow [cpp-tbox](https://github.com/cpp-main/cpp-tbox) open source project;
- Light up three combos for it: Star, Watch, Fork;
- Recommend to colleagues and partners around you, and recommend to your readers in technical forums;
- Join the above QQ group, add me on WeChat to enter the WeChat group;
- Positive feedback on issues and suggestions;
- Participate in the development of the project and contribute your strength.
