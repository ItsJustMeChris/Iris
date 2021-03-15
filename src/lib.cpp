#include <stdio.h>
#include "../includes/lib.hpp"

static JSValue js_print(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    printf("%s\n", JS_ToCString(ctx, argv[0]));
    return JS_NewInt32(ctx, 32); // width of text
}

static const JSCFunctionListEntry js_iris_funcs[] = {
    JS_CFUNC_DEF("print", 7, js_print ),
};

static int js_iris_init(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_iris_funcs, 1);
}

JSModuleDef *JS_INIT_MODULE(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_iris_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_iris_funcs, 1);
    return m;
}
