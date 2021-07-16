#include "test/v8_test.h"
#include "common_head.h"
#include "base/files/file_path.h"
#include "v8/include/v8.h"
#include "v8/include/libplatform/libplatform.h"

using namespace base;

void V8Test() {
  std::string path = base::CommandLine::ForCurrentProcess()->GetProgram().value();
  v8::V8::InitializeICUDefaultLocation(path.data());
  v8::V8::InitializeExternalStartupData(path.data());
  std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
  v8::V8::InitializePlatform(platform.get());
  v8::V8::Initialize();
  v8::Isolate::CreateParams create_params;
  create_params.array_buffer_allocator =
      v8::ArrayBuffer::Allocator::NewDefaultAllocator();
  v8::Isolate* isolate = v8::Isolate::New(create_params);
  {
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Context> context = v8::Context::New(isolate);
    v8::Context::Scope context_scope(context);
    {
      v8::Local<v8::String> source = v8::String::NewFromUtf8Literal(isolate, "'Hello' + ', World!'");
      v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();
      v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();
      v8::String::Utf8Value utf8(isolate, result);
      printf("%s\n", *utf8);
    }
  }

  // Dispose the isolate and tear down V8.
  isolate->Dispose();
  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
  delete create_params.array_buffer_allocator;
}
