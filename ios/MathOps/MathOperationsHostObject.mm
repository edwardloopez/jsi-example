//
//  MathOperationsProxy.m
//  JSIExample
//
//  Created by Edward Andrés López Mojica on 7/01/25.
//

#import <Foundation/Foundation.h>

#import "React/RCTBridgeModule.h"
#import "React/RCTEventEmitter.h"
#import <jsi/jsi.h>

#import <JSIExample-Swift.h>

using namespace facebook;
using namespace facebook::jsi;

class MathOperationsHostObject : public jsi::HostObject {
private:
  MathOperationsSwift* mathOperations;
  
public:
  MathOperationsHostObject() {
    mathOperations = [MathOperationsSwift new];
  }
  
  double callSwiftMethod(NSString* methodName, double a, double b) {
      SEL selector = NSSelectorFromString([NSString stringWithFormat:@"%@:b:", methodName]);
      if ([mathOperations respondsToSelector:selector]) {
          NSMethodSignature* signature = [mathOperations methodSignatureForSelector:selector];
          NSInvocation* invocation = [NSInvocation invocationWithMethodSignature:signature];
          [invocation setSelector:selector];
          [invocation setTarget:mathOperations];
          [invocation setArgument:&a atIndex:2];
          [invocation setArgument:&b atIndex:3];
          [invocation invoke];
          double result;
          [invocation getReturnValue:&result];
          return result;
      }
      return 0.0;
  }

  double addGlobalVariables() {
      return [mathOperations addGlobalVariables];
  }
  
  jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override {
      auto propName = name.utf8(runtime);

      if (propName == "sum") {
          return jsi::Function::createFromHostFunction(
              runtime, jsi::PropNameID::forUtf8(runtime, "sum"), 2,
              [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                  if (count != 2 || !arguments[0].isNumber() || !arguments[1].isNumber()) {
                      throw jsi::JSError(runtime, "Expected two number arguments for sum.");
                  }
                  double result = this->callSwiftMethod(@"sum", arguments[0].asNumber(), arguments[1].asNumber());
                  return jsi::Value(result);
              });
      } else if (propName == "subtract") {
          return jsi::Function::createFromHostFunction(
              runtime, jsi::PropNameID::forUtf8(runtime, "subtract"), 2,
              [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                  if (count != 2 || !arguments[0].isNumber() || !arguments[1].isNumber()) {
                      throw jsi::JSError(runtime, "Expected two number arguments for subtract.");
                  }
                  double result = this->callSwiftMethod(@"subtract", arguments[0].asNumber(), arguments[1].asNumber());
                  return jsi::Value(result);
              });
      } else if (propName == "multiply") {
          return jsi::Function::createFromHostFunction(
              runtime, jsi::PropNameID::forUtf8(runtime, "multiply"), 2,
              [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                  if (count != 2 || !arguments[0].isNumber() || !arguments[1].isNumber()) {
                      throw jsi::JSError(runtime, "Expected two number arguments for multiply.");
                  }
                  double result = this->callSwiftMethod(@"multiply", arguments[0].asNumber(), arguments[1].asNumber());
                  return jsi::Value(result);
              });
      } else if (propName == "divide") {
          return jsi::Function::createFromHostFunction(
              runtime, jsi::PropNameID::forUtf8(runtime, "divide"), 2,
              [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                  if (count != 2 || !arguments[0].isNumber() || !arguments[1].isNumber()) {
                      throw jsi::JSError(runtime, "Expected two number arguments for divide.");
                  }
                  double result = this->callSwiftMethod(@"divide", arguments[0].asNumber(), arguments[1].asNumber());
                  return jsi::Value(result);
              });
      } else if (propName == "addGlobalVariables") {
          return jsi::Function::createFromHostFunction(
              runtime, jsi::PropNameID::forUtf8(runtime, "addGlobalVariables"), 0,
              [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                  double result = this->addGlobalVariables();
                  return jsi::Value(result);
              });
      }

      return jsi::Value::undefined();
  }
};

void install(jsi::Runtime& runtime) {
    auto mathOperationsHostObject = std::make_shared<MathOperationsHostObject>();
    runtime.global().setProperty(runtime, "MathOperationsProxy", jsi::Object::createFromHostObject(runtime, mathOperationsHostObject));
}
