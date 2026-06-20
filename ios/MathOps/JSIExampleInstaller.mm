#import "JSIExampleInstaller.h"
#import "MathOperationsHostObject.h"

#import <Foundation/Foundation.h>
#import <React/RCTBridge+Private.h>
#import <React/RCTBridge.h>
#import <ReactCommon/CallInvoker.h>
#import <ReactCommon/RCTTurboModule.h>
#import <ReactCommon/RCTTurboModuleWithJSIBindings.h>
#import <jsi/jsi.h>

using namespace facebook;
using namespace facebook::jsi;
using namespace facebook::react;

@interface JSIExampleInstaller () <RCTTurboModule, RCTTurboModuleWithJSIBindings>
@end

@implementation JSIExampleInstaller {
  BOOL _installed;
}

@synthesize bridge = _bridge;

RCT_EXPORT_MODULE();

+ (BOOL)requiresMainQueueSetup {
  return NO;
}

- (dispatch_queue_t)methodQueue {
  return RCTJSThread;
}

- (jsi::Runtime *)runtimeFromBridge:(RCTBridge *)bridge {
  if (bridge == nil || ![bridge respondsToSelector:@selector(runtime)]) {
    return nullptr;
  }

  void *runtimePtr = [(id)bridge runtime];
  if (runtimePtr == nullptr) {
    return nullptr;
  }

  return (jsi::Runtime *)runtimePtr;
}

- (BOOL)installOnRuntime:(jsi::Runtime &)runtime {
  if (_installed) {
    return YES;
  }

  installMathOperations(runtime);
  _installed = YES;
  NSLog(@"JSI MathOperations installed correctly on iOS.");
  return YES;
}

- (std::shared_ptr<TurboModule>)getTurboModule:(const ObjCTurboModule::InitParams &)params {
  return std::make_shared<ObjCTurboModule>(params);
}

- (void)installJSIBindingsWithRuntime:(jsi::Runtime &)runtime
                          callInvoker:(const std::shared_ptr<CallInvoker> &)callInvoker {
  [self installOnRuntime:runtime];
}

RCT_EXPORT_SYNCHRONOUS_TYPED_METHOD(NSNumber *, install) {
  if (_installed) {
    return @YES;
  }

  RCTBridge *bridge = self.bridge ?: [RCTBridge currentBridge];
  jsi::Runtime *runtime = [self runtimeFromBridge:bridge];
  if (runtime == nullptr) {
    NSLog(@"runtime_not_found: JSI runtime is not available yet.");
    return @NO;
  }

  return @([self installOnRuntime:*runtime]);
}

@end
