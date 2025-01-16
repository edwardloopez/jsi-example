package com.jsiexample.mathops

import android.util.Log

class MathOperationsKotlin {
    fun sum(a: Double, b: Double): Double {
        return a + b
    }

    fun subtract(a: Double, b: Double): Double {
        return a - b
    }

    fun multiply(a: Double, b: Double): Double {
        return a * b
    }

    fun divide(a: Double, b: Double): Double {
        if (b == 0.0) {
            Log.e("MathOperationsKotlin", "Cannot divide by zero.")
            return Double.NaN
        }
        return a / b
    }

    private var globalVar1 = 10.0
    private var globalVar2 = 20.0

    fun addGlobalVariables(): Double {
        return globalVar1 + globalVar2
    }
}