#include <nan.h>
#include "screen_avg_color_windows.h"

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	// Check number of arguments passed
	if (args.Length() < 6) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
		return;
	}

	//Check the argument types
	if (!args[1]->IsInt32() || !args[2]->IsInt32() || !args[3]->IsInt32() || !args[4]->IsInt32() || !args[5]->IsInt32()) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
		return;
	}

	const int x = args[1]->Int32Value();
	const int y = args[2]->Int32Value();
	const int width = args[3]->Int32Value();
	const int height = args[4]->Int32Value();
	const int scale = args[5]->Int32Value();

	int* rgb = getScreenAvgColor(x, y, width, height, scale);

	// Callback
	Local<Function> cb = args[0].As<Function>();

	const int argc = 4;
	Local<Value> argv[argc] = {
		Null(isolate),
		Integer::New(isolate, rgb[0]),
		Integer::New(isolate, rgb[1]),
		Integer::New(isolate, rgb[2])
	};

	cb->Call(Null(isolate), argc, argv);
}

void Init(Local<Object> exports, Local<Object> module) {
	NODE_SET_METHOD(module, "exports", Method);
}

NODE_MODULE(screen_avg_color, Init)
