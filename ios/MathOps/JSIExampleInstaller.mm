//
//  MathOperationsInstaller.m
//  JSIExample
//
//  Created by Edward Andrés López Mojica on 12/01/25.
//

#import "JSIExampleInstaller.h"
#import "MathOperationsHostObject.h"

#import <React/RCTBridge+Private.h>
#import <React/RCTBridge.h>
#import <jsi/jsi.h>

@implementation JSIExampleInstaller

RCT_EXPORT_MODULE();

RCT_EXPORT_SYNCHRONOUS_TYPED_METHOD(NSNumber *, install) {
  RCTBridge *bridge = [RCTBridge currentBridge];
  if (!bridge) {
    NSLog(@"bridge_not_found: No se pudo obtener el puente desde el delegado.");
    return @NO;
  }
  
  // Make sure is the RCTCxxBridge
  RCTCxxBridge* cxxBridge = (RCTCxxBridge *)bridge;
  if (!cxxBridge.runtime) {
    NSLog(@"runtime_not_found: El runtime JSI no está disponible. Asegúrate de que el JS se haya cargado.");
    return @NO;
  }
  
  // Install the HostObject
  jsi::Runtime &runtime = *(jsi::Runtime *)cxxBridge.runtime;
  auto mathOperationsHostObject = std::make_shared<MathOperationsHostObject>();
  runtime.global().setProperty(runtime, "MathOperationsProxy", jsi::Object::createFromHostObject(runtime, mathOperationsHostObject));
  
  NSLog(@"JSI MathOperations instalado correctamente usando el delegado.");
  return @YES;
}

@end
