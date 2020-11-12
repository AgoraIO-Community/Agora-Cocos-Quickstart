# Agora Cocos2d-x Quickstart

*其他语言：[简体中文](README.zh.md)*

This sample is an open-source demo that will help you get voice and video chat integrated directly into your Cocos2d-x gaming applications using the Agora SDK.

With this sample app, you can:

- Join / leave channel
- Add / Remove render view

## Running the App

First, create a developer account at [Agora.io](https://dashboard.agora.io/en/signin), and obtain an App ID. Update "Classes/HelloWorldScene.h" with your App ID.

```
#define AGORA_APP_ID <#YOUR APP ID#>
```

This sample app needs open-source project [Cocos2d-x](https://www.cocos.com/products#Cocos2d-x), download [Cocos2d-x SDK](https://www.cocos.com/cocos2dx), and replace files under **cocos2d** folder.

**Tips**

This only for Cocos2d-x 3.x version，if you want to use 4.x version，please refer to the [offical migration doc](https://docs.cocos.com/cocos2d-x/v4/manual/en/upgradeGuide/migration.html).

### **Run project for Android**

- Click [Agora SDK](https://docs.agora.io/en/Agora%20Platform/downloads) and download Android SDK from **Video SDK**.

- Unzip and copy **libs/agora-rtc-sdk.jar** to **sdk/android/lib** folder in this project, and copy the .h and .so files from **libs** folder to the corresponding directory in **sdk/android/agora/** folder.

- Use Android Studio to open **proj.android** folder, connect the device, build and run.

### **Run project for iOS**

- Click [Agora SDK](https://docs.agora.io/en/Agora%20Platform/downloads) and download iOS SDK from **Video SDK**.

- Unzip and copy **libs/\*.framework** to **sdk/ios/agora** folder. If you want to support simulator, you should use **libs/ALL_ARCHITECTURE/\*.framework** instead of。

- Use Xcode to open **proj.ios_mac/Hello-Cocos2d-Agora.xcodeproj** project，connect the device, build and run.

## Developer Environment Requirements

- Android Studio 3.0+ / Xcode 8.0+
- Real Android / iOS devices(Nexus 5X or other devices)
- Some simulators are function missing or have performance issue, so real device is the best choice

## Connect Us

- You can find full API document at [Document Center](https://docs.agora.io/en)
- You can file bugs about this demo at [issue](https://github.com/AgoraIO-Community/Agora-Cocos-Quickstart/issues)

## License

The MIT License (MIT).
