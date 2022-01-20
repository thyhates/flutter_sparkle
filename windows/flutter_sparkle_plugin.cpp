#include "include/flutter_sparkle/flutter_sparkle_plugin.h"
#include "include/winSparkle/winsparkle.h"
// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <map>
#include <memory>
#include <sstream>

namespace {
class FlutterSparklePlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  FlutterSparklePlugin();

  virtual ~FlutterSparklePlugin();

 private:
  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

// static
void FlutterSparklePlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "flutter_sparkle",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterSparklePlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

FlutterSparklePlugin::FlutterSparklePlugin() {}

FlutterSparklePlugin::~FlutterSparklePlugin() {}

void FlutterSparklePlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  }
  else if(method_call.method_name().compare("initWinSparkle") == 0){
     auto* arguments = std::get_if<flutter::EncodableMap>(method_call.arguments());
    auto* feed_url = std::get_if<std::string>(&(arguments->find(flutter::EncodableValue("feedUrl"))->second));
//    auto feed_url_it = arguments->find(flutter::EncodableValue("feedUrl"));
//    if(feed_url_it!=arguments->end()){
//        feed_url = std::get<std::string>(feed_url_it->second);
//    }
//feed_url = arguments;
    win_sparkle_set_appcast_url(feed_url->c_str());
    win_sparkle_init();
//  }else if(method_call.method_name().compare("clearWinSparkle") == 0){
//    win_sparkle_cleanup();
    result->Success(flutter::EncodableValue(feed_url->c_str()));
  }else if(method_call.method_name().compare("checkWinUpdate") == 0){
    win_sparkle_check_update_with_ui();
     result->Success(flutter::EncodableValue("success"));
  }else if(method_call.method_name().compare("checkWinUpdateAndInstall") == 0){
    win_sparkle_check_update_with_ui_and_install();
     result->Success(flutter::EncodableValue("success"));
  }else if(method_call.method_name().compare("checkWinUpdateWithoutUI") == 0){
    win_sparkle_check_update_without_ui();
     result->Success(flutter::EncodableValue("success"));
  }else if(method_call.method_name().compare("setPubPem") == 0){
      auto* args = std::get_if<flutter::EncodableMap>(method_call.arguments());
      auto* pub_pem = std::get_if<std::string>(&(args->find(flutter::EncodableValue("pubPem"))->second));
    win_sparkle_set_dsa_pub_pem(reinterpret_cast<const char*>(pub_pem->c_str()));
     result->Success(flutter::EncodableValue("success"));
  }
  else {
    result->NotImplemented();
  }
}

}  // namespace

void FlutterSparklePluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  FlutterSparklePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
