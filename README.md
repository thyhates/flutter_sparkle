# flutter_sparkle
A flutter plugin to check update and install your macOS app which use [Sparkle](https://sparkle-project.org/).

Just support for macOS platform.
#Setup
- Enable network connections for your app
- Run `./bin/generate_keys` tool (from the Sparkle distribution root) to generate public key.
- Add your public key to your app’s `Info.plist` as a `SUPublicEDKey` property
#Usage
Import flutter_sparkle plugin
```dart
import 'package:flutter_sparkle/flutter_sparkle.dart';
```
Pass your appcast.xml url to  `checkMacUpdate` method. 
```dart
 FlutterSparkle.checkMacUpdate('https://test.asfarastheeyecansee.cn/get/mac/version');
```
All done.