/* This code is PUBLIC DOMAIN, and is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND. See the accompanying 
 * LICENSE file.
 */

#include <v8.h>
#include <node.h>
#include <locale.h>
//#include <monetary.h>

using namespace node;
using namespace v8;
	
static Handle<Value> node_setlocale(const Arguments& args) {
	HandleScope scope;
	
	if (args.Length() == 0) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	
	int lc_type = args[0]->Uint32Value();
	String::Utf8Value locale(args[1]->ToString());
	
	if (setlocale(lc_type, *locale) == NULL) {
		return scope.Close(Boolean::New(false));
	}
	return scope.Close(Boolean::New(true));
}

void Init(Handle<Object> target) {
	HandleScope scope;
	
	NODE_DEFINE_CONSTANT(target, LC_ALL);
	NODE_DEFINE_CONSTANT(target, LC_COLLATE);
	NODE_DEFINE_CONSTANT(target, LC_CTYPE);
	NODE_DEFINE_CONSTANT(target, LC_MONETARY);
	NODE_DEFINE_CONSTANT(target, LC_NUMERIC);
	NODE_DEFINE_CONSTANT(target, LC_TIME);
	NODE_DEFINE_CONSTANT(target, LC_MESSAGES);
	
	NODE_SET_METHOD(target, "setlocale", node_setlocale);
}

NODE_MODULE(locale, Init);
