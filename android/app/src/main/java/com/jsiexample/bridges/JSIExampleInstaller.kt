package com.jsiexample.bridges

import android.util.Log
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod

class JSIExampleInstaller(reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext) {

    private var installed = false

    override fun getName(): String = "JSIExampleInstaller"

    override fun initialize() {
        super.initialize()
        reactApplicationContext.addReactInstanceEventListener { installInternal() }
        if (reactApplicationContext.hasActiveReactInstance()) {
            installInternal()
        }
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    fun install(): Boolean = installInternal()

    private fun installInternal(): Boolean {
        if (installed) {
            return true
        }

        val jsContext = reactApplicationContext.javaScriptContextHolder?.get()
        if (jsContext == null || jsContext == 0L) {
            Log.e(TAG, "JavaScript context is not available yet.")
            return false
        }

        nativeInstall(jsContext)
        installed = true
        Log.i(TAG, "JSI MathOperations installed on Android.")
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
