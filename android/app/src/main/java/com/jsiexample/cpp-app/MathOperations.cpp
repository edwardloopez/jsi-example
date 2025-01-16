//
// Created by Edward Andrés López Mojica on 5/01/25.
//

#include <jsi/jsi.h>
#include <jni.h>
#include <fbjni/fbjni.h>
#include "MathOperations.h"

using namespace facebook;
using namespace std;

namespace mathops {
    class MathOperationsProxy : public jsi::HostObject {
    private:
        jobject mathOperationsInstance;

    public:
        MathOperationsProxy() {
            JNIEnv* env = jni::Environment::current();
            jclass mathOpsClass = env->FindClass("com/jsiexample/mathops/MathOperationsKotlin");
            if (!mathOpsClass) {
                //LOGE("Failed to find MathOperationsKotlin class");
                throw std::runtime_error("Failed to find MathOperationsKotlin class");
            }

            jmethodID constructor = env->GetMethodID(mathOpsClass, "<init>", "()V");
            if (!constructor) {
                //LOGE("Failed to find MathOperationsKotlin constructor");
                throw std::runtime_error("Failed to find MathOperationsKotlin constructor");
            }

            jobject localInstance = env->NewObject(mathOpsClass, constructor);
            if (!localInstance) {
                //LOGE("Failed to create MathOperationsKotlin instance");
                throw std::runtime_error("Failed to create MathOperationsKotlin instance");
            }

            mathOperationsInstance = env->NewGlobalRef(localInstance); // Save global reference
        }

        ~MathOperationsProxy() override {
            JNIEnv* env = jni::Environment::current();
            env->DeleteGlobalRef(mathOperationsInstance); // Release global reference
        }

        jdouble callKotlinMethod(const char* methodName, jdouble a, jdouble b) {
            JNIEnv* env = jni::Environment::current();
            jclass mathOpsClass = env->GetObjectClass(mathOperationsInstance);

            if (!mathOpsClass) {
                //LOGE("Failed to get MathOperationsKotlin class reference");
                throw std::runtime_error("Failed to get MathOperationsKotlin class reference");
            }

            jmethodID method = env->GetMethodID(mathOpsClass, methodName, "(DD)D");
            if (!method) {
                //LOGE("Failed to find method: %s", methodName);
                throw std::runtime_error("Failed to find method");
            }

            return env->CallDoubleMethod(mathOperationsInstance, method, a, b);
        }

        jdouble callKotlinGlobalVarMethod() {
            JNIEnv* env = jni::Environment::current();
            jclass mathOpsClass = env->GetObjectClass(mathOperationsInstance);

            if (!mathOpsClass) {
                //LOGE("Failed to get MathOperationsKotlin class reference");
                throw std::runtime_error("Failed to get MathOperationsKotlin class reference");
            }

            jmethodID method = env->GetMethodID(mathOpsClass, "addGlobalVariables", "()D");
            if (!method) {
                //LOGE("Failed to find addGlobalVariables method");
                throw std::runtime_error("Failed to find addGlobalVariables method");
            }

            return env->CallDoubleMethod(mathOperationsInstance, method);
        }

        jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& propName) override {
            auto name = propName.utf8(runtime);

            if (name == "sum") {
                return jsi::Function::createFromHostFunction(
                        runtime,
                        jsi::PropNameID::forUtf8(runtime, "sum"),
                        2,
                        [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                            if (count < 2 || !arguments[0].isNumber() || !arguments[1].isNumber()) {
                                throw jsi::JSError(runtime, "Expected two number arguments for sum.");
                            }

                            double a = arguments[0].asNumber();
                            double b = arguments[1].asNumber();

                            double result = callKotlinMethod("sum", a, b);
                            return {result};
                        }
                );
            } else if (name == "subtract") {
                return jsi::Function::createFromHostFunction(
                        runtime,
                        jsi::PropNameID::forUtf8(runtime, "subtract"),
                        2,
                        [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                            if (count < 2 || !arguments[0].isNumber() || !arguments[1].isNumber()) {
                                throw jsi::JSError(runtime, "Expected two number arguments for subtract.");
                            }

                            double a = arguments[0].asNumber();
                            double b = arguments[1].asNumber();

                            double result = callKotlinMethod("subtract", a, b);
                            return {result};
                        }
                );
            } else if (name == "multiply") {
                return jsi::Function::createFromHostFunction(
                        runtime,
                        jsi::PropNameID::forUtf8(runtime, "multiply"),
                        2,
                        [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                            if (count < 2 || !arguments[0].isNumber() || !arguments[1].isNumber()) {
                                throw jsi::JSError(runtime, "Expected two number arguments for multiply.");
                            }

                            double a = arguments[0].asNumber();
                            double b = arguments[1].asNumber();

                            double result = callKotlinMethod("multiply", a, b);
                            return {result};
                        }
                );
            } else if (name == "divide") {
                return jsi::Function::createFromHostFunction(
                        runtime,
                        jsi::PropNameID::forUtf8(runtime, "divide"),
                        2,
                        [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                            if (count < 2 || !arguments[0].isNumber() || !arguments[1].isNumber()) {
                                throw jsi::JSError(runtime, "Expected two number arguments for divide.");
                            }

                            double a = arguments[0].asNumber();
                            double b = arguments[1].asNumber();

                            double result = callKotlinMethod("divide", a, b);
                            return jsi::Value(result);
                        }
                );
            } else if (name == "addGlobalVariables") {
                return jsi::Function::createFromHostFunction(
                        runtime,
                        jsi::PropNameID::forUtf8(runtime, "addGlobalVariables"),
                        0,
                        [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                            double result = callKotlinGlobalVarMethod();
                            return {result};
                        }
                );
            }

            return jsi::Value::undefined();
        }

    };
};

void mathops::MathOperations::install(jni::alias_ref<jni::JClass>, jni::alias_ref<jni::JObject> proxy, jlong jsContextNativePointer) {
    auto* runtime = reinterpret_cast<jsi::Runtime*>(jsContextNativePointer);
    if (!runtime) {
        throw std::runtime_error("Failed to get JS runtime pointer");
    }

    auto mathOperationsProxy = std::make_shared<mathops::MathOperationsProxy>();
    runtime->global().setProperty(
            *runtime,
            "MathOperationsProxy",
            jsi::Object::createFromHostObject(*runtime, mathOperationsProxy)
    );
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jsiexample_mathops_MathOperationsKotlinInstaller_install(JNIEnv *env, jclass clazz, jobject proxy, jlong jsContextNativePointer) {
    mathops::MathOperations::install(nullptr, proxy, jsContextNativePointer);
}