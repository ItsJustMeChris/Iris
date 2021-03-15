#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "../includes/quickjs/quickjs.h"
#include "../includes/lib.hpp"
#include <string>
#include <iostream>

/* translates a JSValue.tag to a const char*  */
const char* tagtos(long long tag) {
    switch(tag) {
        case JS_TAG_INT:               return "int";
        case JS_TAG_BOOL:              return "bool";
        case JS_TAG_NULL:              return "null";
        case JS_TAG_UNDEFINED:         return "undefined";
        case JS_TAG_CATCH_OFFSET:      return "catch offset";
        case JS_TAG_EXCEPTION:         return "exception";
        case JS_TAG_FLOAT64:           return "float64";
        case JS_TAG_MODULE:            return "module";
        case JS_TAG_OBJECT:            return "object";
        case JS_TAG_STRING:            return "string";
        case JS_TAG_FIRST:             return "first";
        case JS_TAG_BIG_INT:           return "big_int";
        case JS_TAG_BIG_FLOAT:         return "big_float";
        case JS_TAG_SYMBOL:            return "symbol";
        case JS_TAG_FUNCTION_BYTECODE: return "function bytecode";
        default:                       return "unknown type!";
    }
}


int main(const int argc, const char** argv) {
    std::string str = "import * as iris from 'iris'; iris.print(true);"; 
    
     
    JSRuntime* runtime = JS_NewRuntime();
   
    if (!runtime) {
        printf("line %d : JS_NewRuntime returned NULL\n", __LINE__-2);
        return 1;
    }
  
    JSContext* ctx = JS_NewContext(runtime);
    if (!ctx) {
        printf("line %d : JS_NewContext returned NULL\n", __LINE__-2);
        free(runtime);
        return 1;
    }
    
    JS_AddModuleExport(ctx, JS_INIT_MODULE(ctx, "iris"), "iris");

    JSValue result = JS_Eval(ctx, str.c_str(), str.length(), "ROOT", JS_EVAL_TYPE_MODULE);

    if (JS_IsException(result)) {
        printf("JS err : %s\n", JS_ToCString(ctx, JS_GetException(ctx)));
    } else if (JS_IsFunction(ctx, result)) {
        JSValue jsthis = JS_DupValue(ctx, result);
        JSValue res = JS_Call(ctx, result, jsthis, 0, NULL);
        puts(JS_ToCString(ctx, result));
        puts(JS_ToCString(ctx, res));
        JS_FreeValue(ctx, result);
        JS_FreeValue(ctx, res);
    } else {
        printf("val = %s : %s\n", JS_ToCString(ctx, result), tagtos(result.tag));
    }

    JS_FreeValue(ctx, result);

    JS_RunGC(runtime);

    free(ctx);
    free(runtime);
    return 0;
}