
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
  static void checkWinUpdate(){
    _channel.invokeMethod('checkWinUpdate');
  }
  static void checkWinUpdateAndInstall(){
    _channel.invokeMethod('checkWinUpdateAndInstall');
  }
  static void checkWinUpdateWithoutUI(){
    _channel.invokeMethod('checkWinUpdateWithoutUI');
  }
  static Future<String?> initWinUpdate(String feedUrl) async {
    final String? url = await _channel.invokeMethod('initWinSparkle',{'feedUrl':feedUrl});
    return url;
  }
}
