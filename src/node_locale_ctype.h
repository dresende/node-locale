/* This code is PUBLIC DOMAIN, and is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND. See the accompanying 
 * LICENSE file.
 */

#ifndef SRC_NODE_LOCALE_CTYPE_H_
#define SRC_NODE_LOCALE_CTYPE_H_

#include <v8.h>
#include <node.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

using namespace node;
using namespace v8;

/**
 * isalpha(c)
 *
 * Check if <c> is an alpha character in current locale.
 *
 **/
Handle<Value> node_ctype_isalpha(const Arguments& args) {
	HandleScope scope;

	if (args.Length() == 0) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return scope.Close(Boolean::New(false));
	}

	String::Utf8Value s(args[0]->ToString());

	return scope.Close(Boolean::New(isalpha((int)**s) != 0));
}

/**
 * isalnum(c)
 *
 * Check if <c> is an alphanumeric character in current locale.
 *
 **/
Handle<Value> node_ctype_isalnum(const Arguments& args) {
	HandleScope scope;

	if (args.Length() == 0) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return scope.Close(Boolean::New(false));
	}

	String::Utf8Value s(args[0]->ToString());

	return scope.Close(Boolean::New(isalnum((int)**s) != 0));
}

/**
 * isdigit(c)
 *
 * Check if <c> is a digit character in current locale.
 *
 **/
Handle<Value> node_ctype_isdigit(const Arguments& args) {
	HandleScope scope;

	if (args.Length() == 0) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return scope.Close(Boolean::New(false));
	}

	String::Utf8Value s(args[0]->ToString());

	return scope.Close(Boolean::New(isdigit((int)**s) != 0));
}

/**
 * isdigit(c)
 *
 * Check if <c> is an hex digit ([a-fA-F0-9]) character in current locale.
 *
 **/
Handle<Value> node_ctype_isxdigit(const Arguments& args) {
	HandleScope scope;

	if (args.Length() == 0) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return scope.Close(Boolean::New(false));
	}

	String::Utf8Value s(args[0]->ToString());

	return scope.Close(Boolean::New(isxdigit((int)**s) != 0));
}

/**
 * isdigit(c)
 *
 * Check if <c> is a blank character (space or tab) in current locale.
 *
 **/
Handle<Value> node_ctype_isblank(const Arguments& args) {
	HandleScope scope;

	if (args.Length() == 0) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return scope.Close(Boolean::New(false));
	}

	String::Utf8Value s(args[0]->ToString());

	return scope.Close(Boolean::New(isblank((int)**s) != 0));
}

/**
 * isdigit(c)
 *
 * Check if <c> is a space character (space, form-feed, newline, carriage return,
 * horizontal tab and vertical tab) in current locale.
 *
 **/
Handle<Value> node_ctype_isspace(const Arguments& args) {
	HandleScope scope;

	if (args.Length() == 0) {
		return ThrowException(Exception::TypeError(String::New("Missing argument")));
	}
	if (!args[0]->IsString()) {
		return scope.Close(Boolean::New(false));
	}

	String::Utf8Value s(args[0]->ToString());

	return scope.Close(Boolean::New(isspace((int)**s) != 0));
}

#endif  // SRC_NODE_LOCALE_CTYPE_H_
