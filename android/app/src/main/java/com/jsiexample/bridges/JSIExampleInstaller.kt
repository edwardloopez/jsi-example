package com.jsiexample.bridges

import android.util.Log
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod

class JSIExampleInstaller(reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext) {

    override fun getName(): String = "JSIExampleInstaller"

    @ReactMethod(isBlockingSynchronousMethod = true)
    fun install(): Boolean {
        val jsContext = reactApplicationContext.javaScriptContextHolder?.get()
        if (jsContext == null) {
            Log.e(TAG, "JavaScript context is not available yet.")
            return false
        }

        nativeInstall(jsContext)
        return true
    }

    private external fun nativeInstall(jsContextNativePointer: Long)

    companion object {
        private const val TAG = "JSIExampleInstaller"

        init {
            System.loadLibrary("jsi_example")
        }
    }
}
