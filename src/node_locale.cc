/* This code is PUBLIC DOMAIN, and is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND. See the accompanying 
 * LICENSE file.
 */

#include <v8.h>
#include <node.h>
#include <stdlib.h>
#include <math.h>
#include <libintl.h>
#include <locale.h>
#include <monetary.h>
#include <time.h>

using namespace node;
using namespace v8;

/**
 * Helper function to strftime()
 **/
char* node_locale_strftime_hw(const char* format, double value) {
	time_t ts = (time_t) floor(value / 1000);
	struct tm *timeptr;
	char* ret = (char *)malloc(100);

	timeptr = localtime(&ts);

	strftime(ret, 100, format, timeptr);

	return ret;
}

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
 * bindtextdomain(domain, path)
 *
 * Sets the <path> for a given text <domain>.
 *
 **/
static Handle<Value> node_bindtextdomain(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a domain string")));
	}
	if (!args[1]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 2 must be the domain path")));
	}

	String::Utf8Value domain(args[0]->ToString());
	String::Utf8Value path(args[1]->ToString());

	if (bindtextdomain(*domain, *path) == NULL) {
		return scope.Close(Boolean::New(false));
	}

	return scope.Close(Boolean::New(true));
}

/**
 * textdomain(domain)
 *
 * Sets the current text <domain>.
 *
 **/
static Handle<Value> node_textdomain(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a domain string")));
	}

	String::Utf8Value domain(args[0]->ToString());

	if (textdomain(*domain) == NULL) {
		return scope.Close(Boolean::New(false));
	}

	return scope.Close(Boolean::New(true));
}

/**
 * gettext(text)
 *
 * Get converted <text>.
 *
 **/
static Handle<Value> node_gettext(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a string")));
	}

	String::Utf8Value text(args[0]->ToString());

	return scope.Close(String::New(gettext(*text)));
}

/**
 * dgettext(domain, text)
 *
 * Get converted <text> using <domain>.
 *
 **/
static Handle<Value> node_dgettext(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a domain string")));
	}
	if (!args[1]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 2 must be a string")));
	}

	String::Utf8Value domain(args[0]->ToString());
	String::Utf8Value text(args[1]->ToString());

	return scope.Close(String::New(dgettext(*domain, *text)));
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
	if (!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a string representing monetary format")));
	}
	if (!args[1]->IsDate() && !args[1]->IsNumber()) {
		return ThrowException(Exception::TypeError(String::New("Argument 2 must be a numeric value")));
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
	if (!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a string representing date/time format")));
	}
	if (!args[1]->IsDate() && !args[1]->IsNumber()) {
		return ThrowException(Exception::TypeError(String::New("Argument 2 must be a numeric or a date value")));
	}

	String::Utf8Value format(args[0]->ToString());

	return scope.Close(String::New(node_locale_strftime_hw(*format, args[1]->NumberValue())));
}

/**
 * strptime(string, format)
 *
 * Convert date in <string> using <format> specification to a Date object.
 **/
static Handle<Value> node_strptime(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a string representing a date/time")));
	}
	if (!args[1]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 2 must be a string representing the previous date/time format")));
	}

	String::Utf8Value str(args[0]->ToString());
	String::Utf8Value format(args[1]->ToString());
	struct tm ts;

	if (strptime(*str, *format, &ts) == NULL) {
		return scope.Close(Boolean::New(false));
	}

	static Local<Object> obj = Object::New();
	obj->Set(String::New("tm_sec"), Number::New(ts.tm_sec));
	obj->Set(String::New("tm_min"), Number::New(ts.tm_min));
	obj->Set(String::New("tm_hour"), Number::New(ts.tm_hour));
	obj->Set(String::New("tm_mday"), Number::New(ts.tm_mday));
	obj->Set(String::New("tm_mon"), Number::New(ts.tm_mon));
	obj->Set(String::New("tm_year"), Number::New(ts.tm_year));
	obj->Set(String::New("tm_wday"), Number::New(ts.tm_wday));
	obj->Set(String::New("tm_yday"), Number::New(ts.tm_yday));

	return scope.Close(obj);
}

/**
 * monthname(date[, abbreviated = false])
 *
 * Get month name in current locale, for specified <date>. If <abbreviated>
 * is passed as true, it will return the abbreviated name.
 **/
static Handle<Value> node_monthname(const Arguments& args) {
	HandleScope scope;

	if (args.Length() == 0) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsDate() && !args[0]->IsNumber()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a numeric or a date value")));
	}
	if (args.Length() > 1 && !args[1]->IsBoolean()) {
		return ThrowException(Exception::TypeError(String::New("Optional argument 2 must be a boolean")));
	}

	String::Utf8Value format(String::New(args.Length() > 1 && args[1]->ToBoolean()->Value() ? "%b" : "%B"));

	return scope.Close(String::New(node_locale_strftime_hw(*format, args[0]->NumberValue())));
}

/**
 * weekdayname(date[, abbreviated = false])
 *
 * Get weekday name in current locale, for specified <date>. If <abbreviated>
 * is passed as true, it will return the abbreviated name.
 **/
static Handle<Value> node_weekdayname(const Arguments& args) {
	HandleScope scope;

	if (args.Length() == 0) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsDate() && !args[0]->IsNumber()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a numeric or a date value")));
	}
	if (args.Length() > 1 && !args[1]->IsBoolean()) {
		return ThrowException(Exception::TypeError(String::New("Argument 2 must be a boolean")));
	}

	String::Utf8Value format(String::New(args.Length() > 1 && args[1]->ToBoolean()->Value() ? "%a" : "%A"));

	return scope.Close(String::New(node_locale_strftime_hw(*format, args[0]->NumberValue())));
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
	NODE_SET_METHOD(target, "bindtextdomain", node_bindtextdomain);
	NODE_SET_METHOD(target, "textdomain", node_textdomain);
	NODE_SET_METHOD(target, "gettext", node_gettext);
	NODE_SET_METHOD(target, "dgettext", node_dgettext);
	NODE_SET_METHOD(target, "strfmon", node_strfmon);
	NODE_SET_METHOD(target, "strftime", node_strftime);
	NODE_SET_METHOD(target, "strptime", node_strptime);
	NODE_SET_METHOD(target, "monthname", node_monthname);
	NODE_SET_METHOD(target, "weekdayname", node_weekdayname);
}

NODE_MODULE(locale, Init);
