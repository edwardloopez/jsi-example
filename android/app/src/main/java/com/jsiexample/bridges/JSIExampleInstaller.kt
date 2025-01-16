package com.jsiexample.bridges

import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod
import com.jsiexample.mathops.MathOperationsKotlinInstaller

class JSIExampleInstaller(reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext) {

    override fun getName(): String {
        return "JSIExampleInstaller"
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    fun install() {
        val jsContext = reactApplicationContext.javaScriptContextHolder?.get()
        jsContext?.let { MathOperationsKotlinInstaller.install(this, it) }
    }

    companion object {
        init {
            System.loadLibrary("jsi_example")
        }
    }
}