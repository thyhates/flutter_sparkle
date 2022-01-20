# flutter_sparkle
A flutter plugin to check update and install your macOS app which use [Sparkle](https://sparkle-project.org/).

Only support for macOS and Windows platform.
# Setup
## mac
- Enable network connections for your app
- Run `./bin/generate_keys` tool (from the Sparkle distribution root) to generate public key.
- Add your public key to your app’s `Info.plist` as a `SUPublicEDKey` property

# Usage

Import flutter_sparkle plugin
```dart
import 'package:flutter_sparkle/flutter_sparkle.dart';
```
## mac
Pass your appcast.xml url to  `checkMacUpdate` method. 
```dart
 FlutterSparkle.checkMacUpdate('https://test.asfarastheeyecansee.cn/get/mac/version');
```
All done.
## windows
initial winSparkle at `main` with your appcast.xml feed url.
```dart
await FlutterSparkle.initWinUpdate('https://test.asthestarsfall.cn/get/win/version');
```
check update with `checkWinUpdate()`
```dart
FlutterSparkle.checkWinUpdate();
```
`checkWinUpdateAndInstall` check and install 


`checkWinUpdateWithoutUI` check without Ui but still install when new version coming. 
# change log
## 0.0.2
add support for windows platform