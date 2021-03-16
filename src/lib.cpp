#include <_types/_uint8_t.h>
#include <stdio.h>
#include "../includes/lib.hpp"
#include <iostream>
#include <vector>
#include <memory>

int test(int a, uint32_t b) {
    std::cout << "Hi - " << a << " == " << b << std::endl;
    return 1;
}

int a = 0;

struct hook {
    void (*func)();
};

static JSValue js_print(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    for (int i = 0; i < argc; i++) {
        printf("%s", JS_ToCString(ctx, argv[i]));  
    }
    printf("\n");
    return JS_NewInt32(ctx, 1);
}

static JSValue js_writeInt(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    int32_t* address;
    int a = JS_ToInt32(ctx, address, argv[0]);
    
    std::cout << address << std::endl;

    return JS_NewInt32(ctx, 1);
}

static JSValue js_writeFloat(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    int32_t* address;
    int a = JS_ToInt32(ctx, address, argv[0]);
    
    std::cout << address << std::endl;

    return JS_NewInt32(ctx, 1);
}

static JSValue js_writeDouble(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    int32_t* address;
    int a = JS_ToInt32(ctx, address, argv[0]);
    
    std::cout << address << std::endl;

    return JS_NewInt32(ctx, 1);
}

static JSValue js_writeByte(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    int32_t* address;
    int a = JS_ToInt32(ctx, address, argv[0]);
    
    std::cout << address << std::endl;

    return JS_NewInt32(ctx, 1);
}

static JSValue js_writeCString(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    int32_t* address;
    int a = JS_ToInt32(ctx, address, argv[0]);
    
    std::cout << address << std::endl;

    return JS_NewInt32(ctx, 1);
}

static JSValue js_writeSTDString(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    int32_t* address;
    int a = JS_ToInt32(ctx, address, argv[0]);
    
    std::cout << address << std::endl;

    return JS_NewInt32(ctx, 1);
}

static const JSCFunctionListEntry js_iris_funcs[] = {
    JS_CFUNC_DEF("print", 0, js_print ),
    JS_CFUNC_DEF("writeInt", 0, js_print ),
    JS_CFUNC_DEF("writeFloat", 0, js_writeFloat ),
    JS_CFUNC_DEF("writeDouble", 0, js_writeDouble ),
    JS_CFUNC_DEF("writeByte", 0, js_writeByte ),
    JS_CFUNC_DEF("writeCString", 0, js_writeCString ),
    JS_CFUNC_DEF("writeSTDString", 0, js_writeSTDString ),
};

static int js_iris_init(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_iris_funcs, 7);
}

JSModuleDef *JS_INIT_MODULE(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_iris_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_iris_funcs, 7);
    return m;
}
