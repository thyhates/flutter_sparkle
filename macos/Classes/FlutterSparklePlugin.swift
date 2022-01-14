import Cocoa
import FlutterMacOS
import Sparkle

public class FlutterSparklePlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "flutter_sparkle", binaryMessenger: registrar.messenger)
    let instance = FlutterSparklePlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    switch call.method {
    case "getPlatformVersion":
      result("macOS " + ProcessInfo.processInfo.operatingSystemVersionString)
    case "checkMacUpdate":
        guard let args = call.arguments else {
                return
              }
         let url = args as? String
        let updater = SUUpdater.shared()
        updater?.feedURL = URL(string: url!)
        updater?.checkForUpdates(self)
    default:
      result(FlutterMethodNotImplemented)
    }
  }
}
