// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/libplatform/libplatform.h"
#include "include/v8.h"
#include <string>
#include <memory>

using namespace v8;
using namespace std;

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
 public:
  virtual void* Allocate(size_t length) {
    void* data = AllocateUninitialized(length);
    return data == NULL ? data : memset(data, 0, length);
  }
  virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
  virtual void Free(void* data, size_t) { free(data); }
};

class V8ClientBase{
    protected:
            Platform* platform; 
            Isolate* isolate;
    protected:
        V8ClientBase(){
            // Initialize V8.
            V8::InitializeICU();
            platform = platform::CreateDefaultPlatform();
            V8::InitializePlatform(platform);
            V8::Initialize();

            // Create a new Isolate and make it the current one.
            ArrayBufferAllocator allocator;
            Isolate::CreateParams create_params;
            create_params.array_buffer_allocator = &allocator;
            isolate = Isolate::New(create_params);

        }



        ~V8ClientBase(){
            // Dispose the isolate and tear down V8.
            isolate->Dispose();
            V8::Dispose();
            V8::ShutdownPlatform();
            delete platform;
        }
};

class V8Client:V8ClientBase{
            Isolate::Scope g_isolate_scope;
            // Create a stack-allocated handle scope.
            HandleScope g_handle_scope;
    public:

            V8Client():g_isolate_scope(isolate),
            g_handle_scope(isolate) {
            }

            Local<Value> gExecute(string src)
            {
                // Create a new context.
                Local<Context> context = Context::New(isolate);

                // Enter the context for compiling and running the hello world script.
                Context::Scope context_scope(context);

                // Create a string containing the JavaScript source code.
                Local<String> source = String::NewFromUtf8(isolate, src.c_str());

                // Compile the source code.
                Local<Script> script = Script::Compile(source);

                // Run the script to get the result.
                Local<Value> result = script->Run();

                return result;
            }

            string* sExecute(string src)
            {
                Isolate::Scope isolate_scope(isolate);

                // Create a stack-allocated handle scope.
                HandleScope handle_scope(isolate);

                // Create a new context.
                Local<Context> context = Context::New(isolate);

                // Enter the context for compiling and running the hello world script.
                Context::Scope context_scope(context);

                // Create a string containing the JavaScript source code.
                Local<String> source = String::NewFromUtf8(isolate, src.c_str());

                // Compile the source code.
                Local<Script> script = Script::Compile(source);

                // Run the script to get the result.
                Local<Value> result = script->Run();

                // Convert the result to an UTF8 string and print it.
                String::Utf8Value utf8(result);
                return (new string(*utf8));
            }
};


int main(int argc, char* argv[]) {
    V8Client v8;
    Local<Value> result = v8.gExecute(string("'Hello' + ', World!'"));
    String::Utf8Value utf8(result);
    printf("g The result: %s\n", *utf8);
    unique_ptr<string> ss(v8.sExecute(string("function a(){return 'a'}; a();")) ); 
    printf("The result: %s\n", ss->c_str());
    (void) result;
}
int main0(int argc, char* argv[]) {
    // Initialize V8.
    V8::InitializeICU();
    Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();

    // Create a new Isolate and make it the current one.
    ArrayBufferAllocator allocator;
    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = &allocator;
    Isolate* isolate = Isolate::New(create_params);
    {
        Isolate::Scope isolate_scope(isolate);

        // Create a stack-allocated handle scope.
        HandleScope handle_scope(isolate);

        // Create a new context.
        Local<Context> context = Context::New(isolate);

        // Enter the context for compiling and running the hello world script.
        Context::Scope context_scope(context);

        // Create a string containing the JavaScript source code.
        Local<String> source = String::NewFromUtf8(isolate, "'Hello' + ', World!'");

        // Compile the source code.
        Local<Script> script = Script::Compile(source);

        // Run the script to get the result.
        Local<Value> result = script->Run();

        // Convert the result to an UTF8 string and print it.
        String::Utf8Value utf8(result);
        printf("%s\n", *utf8);
    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete platform;
    return 0;
}
