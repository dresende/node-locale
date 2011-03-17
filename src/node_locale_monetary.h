/* This code is PUBLIC DOMAIN, and is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND. See the accompanying 
 * LICENSE file.
 */

#ifndef SRC_NODE_LOCALE_MONETARY_H_
#define SRC_NODE_LOCALE_MONETARY_H_

#include <v8.h>
#include <node.h>
#include <monetary.h>

using namespace node;
using namespace v8;

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

#endif  // SRC_NODE_LOCALE_MONETARY_H_
