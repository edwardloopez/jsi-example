//
// Created by Edward Andrés López Mojica on 5/01/25.
//

#ifndef JSIEXAMPLE_MATHOPERATIONS_H
#define JSIEXAMPLE_MATHOPERATIONS_H

#include <jni.h>
#include <fbjni/fbjni.h>
#include <memory>

namespace mathops {
    using namespace facebook;

    class MathOperations {
    public:
        static void install(jni::alias_ref<jni::JClass>, jni::alias_ref<jni::JObject>, jlong);
    };
}


#endif //JSIEXAMPLE_MATHOPERATIONS_H
