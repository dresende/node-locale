/* This code is PUBLIC DOMAIN, and is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND. See the accompanying 
 * LICENSE file.
 */

#include <v8.h>
#include <node.h>
#include <math.h>
#include <locale.h>
#include <monetary.h>
#include <time.h>

using namespace node;
using namespace v8;

/**
 * setlocale(type, locale)
 *
 * Change locale to <locale>. <type> can be LC_ALL or any other common
 * locale type.
 *
 **/
static Handle<Value> node_setlocale(const Arguments& args) {
	HandleScope scope;
	
	if (args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	
	int lc_type = args[0]->Uint32Value();
	String::Utf8Value locale(args[1]->ToString());
	
	if (setlocale(lc_type, *locale) == NULL) {
		return scope.Close(Boolean::New(false));
	}
	return scope.Close(Boolean::New(true));
}

/**
 * strfmon(format, value)
 *
 * Format monetary <value> using <format> specification.
 **/
static Handle<Value> node_strfmon(const Arguments& args) {
	HandleScope scope;
	
	if (args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	
	String::Utf8Value format(args[0]->ToString());
	double value = args[1]->NumberValue();
	char string[100];
	
	strfmon(string, 100, *format, value);
	
	return scope.Close(String::New(string));
}

/**
 * strftime(format, date)
 *
 * Format date <date> using <format> specification.
 **/
static Handle<Value> node_strftime(const Arguments& args) {
	HandleScope scope;
	
	if (args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[1]->IsDate() && !args[1]->IsNumber()) {
		return ThrowException(Exception::TypeError(String::New("Argument 2 must be a numeric or a date value")));
	}
	
	String::Utf8Value format(args[0]->ToString());
	time_t ts = (time_t) floor(args[1]->NumberValue() / 1000);
	struct tm *timeptr;
	char string[100];

	timeptr = localtime(&ts);

	strftime(string, 100, *format, timeptr);

	return scope.Close(String::New(string));
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
	NODE_SET_METHOD(target, "strfmon", node_strfmon);
	NODE_SET_METHOD(target, "strftime", node_strftime);
}

NODE_MODULE(locale, Init);
