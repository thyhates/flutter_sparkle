
import 'dart:async';

import 'package:flutter/services.dart';

class FlutterSparkle {
  static const MethodChannel _channel = MethodChannel('flutter_sparkle');

  static Future<String?> get platformVersion async {
    final String? version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }
  static void checkMacUpdate (String feedUrl){
    _channel.invokeMethod('checkMacUpdate',feedUrl);
  }
}
