# Agora Cocos2d-x Quickstart

*Other Languages: [English](README.md)*

这个开源示例项目演示了如何快速集成 Agora SDK 到 Cocos2d-x 中，实现在游戏中音视频通话。

在这个示例项目中包含了以下功能：

- 加入通话和离开通话；
- 添加视频渲染和移除视频渲染；

## 运行示例程序

首先在 [Agora.io](https://dashboard.agora.io/cn/signup) 注册账号，并创建自己的测试项目，获取到 AppID。将 AppID 填写进 "Classes/HelloWorldScene.h"

```
#define AGORA_APP_ID <#YOUR APP ID#>
```

本示例项目依赖于开源的 [Cocos2d-x](https://www.cocos.com/products#Cocos2d-x) 项目，下载 [Cocos2d-x SDK](https://www.cocos.com/cocos2dx)，并用相应内容来替换本项目下的 **cocos2d** 文件夹。

**提示**

此方式只适用于 Cocos2d-x 3.x 版本，如果使用4.x版本，请参考[官方升级文档](https://docs.cocos.com/cocos2d-x/v4/manual/zh/upgradeGuide/migration.html)。

### **运行 Android 项目**

- 在 [Agora SDK](https://docs.agora.io/cn/Agora%20Platform/downloads) 下载 **视频通话/视频互动直播 SDK** 中的Android SDK。

- 解压后将其中的 **libs/agora-rtc-sdk.jar** 复制到本项目的 **sdk/android/lib** 下，将 **libs** 中的 .h 文件和 .so 文件分别复制到本项目的 **sdk/android/agora/** 下对应的目录中。

- 使用 Android Studio 打开 **proj.android** 目录，连上设备，编译并运行。

### **运行 iOS 项目**

- 在 [Agora SDK](https://docs.agora.io/cn/Agora%20Platform/downloads) 下载 **视频通话/视频互动直播 SDK** iOS SDK。

- 解压后将其中的 **libs/\*.framework** 复制到本项目的 **sdk/ios/agora** 下。如果您需要支持模拟器，则需要用 **libs/ALL_ARCHITECTURE/\*.framework** 来代替。

- 使用 Xcode 打开 **proj.ios_mac/Hello-Cocos2d-Agora.xcodeproj** 工程文件，连上设备，编译并运行。

## 运行环境

- Android Studio 3.0+ 或 Xcode 8.0+
- 真实 Android / iOS 设备(Nexus 5X 或者其它设备)
- 部分模拟器会存在功能缺失或者性能问题，所以推荐使用真机

## 联系我们

- 完整的 API 文档见 [文档中心](https://docs.agora.io/cn)
- 如果在集成中遇到问题, 你可以到 [开发者社区](https://dev.agora.io) 提问
- 如果有售前咨询问题, 可以拨打 400 632 6626
- 如果需要售后技术支持, 你可以在 [Agora Dashboard](https://dashboard.agora.io) 提交工单
- 如果发现了示例代码的bug, 欢迎提交 [issue](https://github.com/AgoraIO-Community/Agora-Cocos-Quickstart/issues)

## 代码许可

The MIT License (MIT).
