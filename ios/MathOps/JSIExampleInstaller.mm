#import "JSIExampleInstaller.h"
#import "MathOperationsHostObject.h"

#import <Foundation/Foundation.h>
#import <React/RCTBridge+Private.h>
#import <React/RCTBridge.h>
#import <jsi/jsi.h>

using namespace facebook;
using namespace facebook::jsi;

@implementation JSIExampleInstaller

RCT_EXPORT_MODULE();

RCT_EXPORT_SYNCHRONOUS_TYPED_METHOD(NSNumber *, install) {
  RCTBridge *bridge = [RCTBridge currentBridge];
  if (!bridge) {
    NSLog(@"bridge_not_found: Could not obtain bridge from delegate.");
    return @NO;
  }

  RCTCxxBridge *cxxBridge = (RCTCxxBridge *)bridge;
  if (!cxxBridge.runtime) {
    NSLog(@"runtime_not_found: JSI runtime is not available yet.");
    return @NO;
  }

  jsi::Runtime &runtime = *(jsi::Runtime *)cxxBridge.runtime;
  installMathOperations(runtime);

  NSLog(@"JSI MathOperations installed correctly on iOS.");
  return @YES;
}

@end
