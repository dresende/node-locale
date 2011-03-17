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
#include "node_locale_ctype.h"
#include "node_locale_time.h"
#include "node_locale_monetary.h"

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
	
	if (args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	
	if (args.Length() == 1) {
		char *locale;
		if ((locale = setlocale(args[0]->Uint32Value(), NULL)) == NULL) {
			return scope.Close(Boolean::New(false));
		}
		return scope.Close(String::New(locale));
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

	if (args.Length() == 0) {
		char *domain;
		if ((domain = textdomain(NULL)) == NULL) {
			return scope.Close(Boolean::New(false));
		}

		return scope.Close(String::New(domain));
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
 * ngettext(text, plural_text, n)
 *
 * Convert <text> or <plural_text> based on <n> being plural or not.
 *
 **/
static Handle<Value> node_ngettext(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 3) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a string")));
	}
	if (!args[1]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 2 must be a plural string")));
	}
	if (!args[2]->IsNumber()) {
		return ThrowException(Exception::TypeError(String::New("Argument 3 must be a numeric value")));
	}

	String::Utf8Value text(args[0]->ToString());
	String::Utf8Value plural_text(args[1]->ToString());
	unsigned long int n = args[2]->Uint32Value();

	return scope.Close(String::New(ngettext(*text, *plural_text, n)));
}

/**
 * dngettext(domain, text, plural_text, n)
 *
 * Using <domain>, convert <text> or <plural_text> based on <n> being plural or not.
 *
 **/
static Handle<Value> node_dngettext(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 4) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 1 must be a domain string")));
	}
	if (!args[1]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 2 must be a string")));
	}
	if (!args[2]->IsString()) {
		return ThrowException(Exception::TypeError(String::New("Argument 3 must be a plural string")));
	}
	if (!args[3]->IsNumber()) {
		return ThrowException(Exception::TypeError(String::New("Argument 4 must be a numeric value")));
	}

	String::Utf8Value domain(args[0]->ToString());
	String::Utf8Value text(args[1]->ToString());
	String::Utf8Value plural_text(args[2]->ToString());
	unsigned long int n = args[3]->Uint32Value();

	return scope.Close(String::New(dngettext(*domain, *text, *plural_text, n)));
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
	NODE_SET_METHOD(target, "ngettext", node_ngettext);
	NODE_SET_METHOD(target, "dngettext", node_dngettext);

	Handle<Object> o_monetary = Object::New();
	NODE_SET_METHOD(o_monetary, "strfmon", node_strfmon);

	Handle<Object> o_time = Object::New();
	NODE_SET_METHOD(o_time, "strftime", node_strftime);
	NODE_SET_METHOD(o_time, "strptime", node_strptime);
	NODE_SET_METHOD(o_time, "monthname", node_monthname);
	NODE_SET_METHOD(o_time, "weekdayname", node_weekdayname);

	Handle<Object> o_ctype = Object::New();
	NODE_SET_METHOD(o_ctype, "isalpha", node_ctype_isalpha);
	NODE_SET_METHOD(o_ctype, "isalnum", node_ctype_isalnum);
	NODE_SET_METHOD(o_ctype, "isdigit", node_ctype_isdigit);
	NODE_SET_METHOD(o_ctype, "isxdigit", node_ctype_isxdigit);
	NODE_SET_METHOD(o_ctype, "isspace", node_ctype_isspace);
	NODE_SET_METHOD(o_ctype, "isblank", node_ctype_isblank);

	target->Set(String::New("time"), o_time);
	target->Set(String::New("ctype"), o_ctype);
	target->Set(String::New("monetary"), o_monetary);
}

NODE_MODULE(locale, Init);
