//
//  MathOperationsHostObject.h
//  JSIExample
//
//  Created by Edward Andrés López Mojica on 9/01/25.
//

#ifndef MathOperationsHostObject_h
#define MathOperationsHostObject_h

#include <jsi/jsi.h>
#import <JSIExample-Swift.h>

using namespace facebook;

class MathOperationsHostObject : public jsi::HostObject {
private:
    MathOperationsSwift* mathOperations;

public:
    MathOperationsHostObject();

    double callSwiftMethod(NSString* methodName, double a, double b);
    double addGlobalVariables();

    jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override;
};

#endif /* MathOperationsHostObject_h */
