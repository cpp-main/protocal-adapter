# protocal-adpater

[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Language](https://img.shields.io/badge/language-c++11-red.svg)](https://en.cppreference.com/)
[![Platform](https://img.shields.io/badge/platform-linux-lightgrey.svg)](https://img.shields.io/badge/platform-linux-lightgrey.svg)

[[English]](README.md)

## 介绍
基于 [cpp-tbox](https://gitee.com/cpp-master/cpp-tbox) 框架实现的多协议适配器

## 功能

- 支持UART, MQTT, TCP, UDP协议转换

## 构建
### 步骤一：构建 [cpp-tbox](https://gitee.com/cpp-master/cpp-tbox) 项目  
```
git clone https://gitee.com/cpp-master/cpp-tbox.git
cd cpp-tbox;
STAGING_DIR=$HOME/.tbox make 3rd-party modules RELEASE=1
cd -
```

### 步骤二：构建 protocal-adapter 自身
```
git clone https://gitee.com/cpp-master/protocal-adapter.git
cd protocal-adapter/src;
make
```
构建完成之后，在 src 目录下会生成：adapter 可执行文件。

## 运行
执行命令：
```
./adapter ../config/default.conf
```
提示：  

- 如果没有权限打开串口文件的问题，则加 sudo 再执行。
- 使用者可以根据需要修改 config/default.conf

## 配置文件
详见 config/default.conf，或阅读源码。

## 反馈途径
- Issue: 任何问题都欢迎在issue里交流
- 微信: hevake\_lee
- QQ群: 738084942 (cpp-tbox 技术交流)

## 鼓励我们
如果你觉得很有用，请您给我更多的鼓励。  
你可以做这些：

- 关注 [cpp-tbox](https://gitee.com/cpp-master/cpp-tbox) 开源项目；
- 给它点亮三连： Star, Watch, Fork；
- 向身边的同事与伙伴推荐，在技术论坛向您的读者推荐；
- 加入上面的QQ群、加我微信进入微信群；
- 积极反馈问题，提出建议；
- 参与项目的开发，贡献您的力量。
