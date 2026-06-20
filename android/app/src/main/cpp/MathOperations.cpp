#include "MathOperations.h"

#include <android/log.h>
#include <jni.h>
#include <jsi/jsi.h>

#include <cmath>
#include <memory>

namespace mathops {

using namespace facebook;

class MathOperationsHostObject : public jsi::HostObject {
private:
    double globalVar1_ = 10.0;
    double globalVar2_ = 20.0;

    static bool validateBinaryArgs(
        jsi::Runtime& runtime,
        const jsi::Value* arguments,
        size_t count) {
        if (count != 2 || !arguments[0].isNumber() || !arguments[1].isNumber()) {
            return false;
        }
        return true;
    }

public:
    jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override {
        auto propName = name.utf8(runtime);

        if (propName == "sum") {
            return jsi::Function::createFromHostFunction(
                runtime,
                jsi::PropNameID::forUtf8(runtime, "sum"),
                2,
                [](jsi::Runtime& rt,
                   const jsi::Value&,
                   const jsi::Value* arguments,
                   size_t count) -> jsi::Value {
                    if (!validateBinaryArgs(rt, arguments, count)) {
                        throw jsi::JSError(rt, "Expected two number arguments for sum.");
                    }
                    return jsi::Value(
                        arguments[0].asNumber() + arguments[1].asNumber());
                });
        }

        if (propName == "subtract") {
            return jsi::Function::createFromHostFunction(
                runtime,
                jsi::PropNameID::forUtf8(runtime, "subtract"),
                2,
                [](jsi::Runtime& rt,
                   const jsi::Value&,
                   const jsi::Value* arguments,
                   size_t count) -> jsi::Value {
                    if (!validateBinaryArgs(rt, arguments, count)) {
                        throw jsi::JSError(rt, "Expected two number arguments for subtract.");
                    }
                    return jsi::Value(
                        arguments[0].asNumber() - arguments[1].asNumber());
                });
        }

        if (propName == "multiply") {
            return jsi::Function::createFromHostFunction(
                runtime,
                jsi::PropNameID::forUtf8(runtime, "multiply"),
                2,
                [](jsi::Runtime& rt,
                   const jsi::Value&,
                   const jsi::Value* arguments,
                   size_t count) -> jsi::Value {
                    if (!validateBinaryArgs(rt, arguments, count)) {
                        throw jsi::JSError(rt, "Expected two number arguments for multiply.");
                    }
                    return jsi::Value(
                        arguments[0].asNumber() * arguments[1].asNumber());
                });
        }

        if (propName == "divide") {
            return jsi::Function::createFromHostFunction(
                runtime,
                jsi::PropNameID::forUtf8(runtime, "divide"),
                2,
                [](jsi::Runtime& rt,
                   const jsi::Value&,
                   const jsi::Value* arguments,
                   size_t count) -> jsi::Value {
                    if (!validateBinaryArgs(rt, arguments, count)) {
                        throw jsi::JSError(rt, "Expected two number arguments for divide.");
                    }
                    double b = arguments[1].asNumber();
                    if (b == 0.0) {
                        __android_log_print(
                            ANDROID_LOG_ERROR,
                            "MathOperations",
                            "Cannot divide by zero.");
                        return jsi::Value(std::nan(""));
                    }
                    return jsi::Value(arguments[0].asNumber() / b);
                });
        }

        if (propName == "addGlobalVariables") {
            return jsi::Function::createFromHostFunction(
                runtime,
                jsi::PropNameID::forUtf8(runtime, "addGlobalVariables"),
                0,
                [this](jsi::Runtime&,
                       const jsi::Value&,
                       const jsi::Value*,
                       size_t) -> jsi::Value {
                    return jsi::Value(globalVar1_ + globalVar2_);
                });
        }

        return jsi::Value::undefined();
    }
};

void installMathOperations(jsi::Runtime& runtime) {
    auto hostObject = std::make_shared<MathOperationsHostObject>();
    runtime.global().setProperty(
        runtime,
        "MathOperationsProxy",
        jsi::Object::createFromHostObject(runtime, hostObject));
}

} // namespace mathops

extern "C" JNIEXPORT void JNICALL
Java_com_jsiexample_bridges_JSIExampleInstaller_nativeInstall(
    JNIEnv*,
    jclass,
    jlong jsContextNativePointer) {
    auto* runtime = reinterpret_cast<facebook::jsi::Runtime*>(jsContextNativePointer);
    if (runtime == nullptr) {
        __android_log_print(
            ANDROID_LOG_ERROR,
            "JSIExampleInstaller",
            "Failed to get JS runtime pointer");
        return;
    }

    mathops::installMathOperations(*runtime);
    __android_log_print(
        ANDROID_LOG_INFO,
        "JSIExampleInstaller",
        "JSI MathOperations installed on Android.");
}
