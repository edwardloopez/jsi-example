//
//  MathOperationsSwift.swift
//  JSIExample
//
//  Created by Edward Andrés López Mojica on 6/01/25.
//

import Foundation

@objc public class MathOperationsSwift: NSObject {
    @objc public func sum(_ a: Double, b: Double) -> Double {
        return a + b
    }

    @objc public func subtract(_ a: Double, b: Double) -> Double {
        return a - b
    }

    @objc public func multiply(_ a: Double, b: Double) -> Double {
        return a * b
    }

    @objc public func divide(_ a: Double, b: Double) -> Double {
        if b == 0 {
            NSLog("Cannot divide by zero.")
            return Double.nan
        }
        return a / b
    }

    private var globalVar1 = 10.0
    private var globalVar2 = 20.0

    @objc public func addGlobalVariables() -> Double {
        return globalVar1 + globalVar2
    }
}
