NodeJS Locale Bindings
======================

The goal of this repo is to bind the common used functions from **locale.h**.

The next code shows what you can do for now.

    var locale = require("locale");
    
    if (locale.setlocale(locale.LC_ALL, "pt_PT.utf8")) {
    	console.log("Monetary: " + locale.strfmon("%i", 1234.56));
    	console.log("    Date: " + locale.strftime("%A, %b %d %Y %H:%M:%S", new Date()));
    }

## Installation

You need to build the code. To do this you need `node-waf` command. Just pull the code,
go to `src` folder and type:

    node-waf configure
    node-waf build
    node-waf install

## API

### locale.setlocale(type, locale)

Change current locale to `locale` (ie. "en\_US"). `type` should be one of `locale.LC\_ALL`,
`locale.LC\_MONETARY`, etc..

### locale.strfmon(format, value)

Return `value` formatted as a monetary value, based on current locale. `format` is a string
that accepts everything that C function `strfmon()` accepts.

### locale.strftime(format, value)

Return `value` formatted as a date value, based on current locale. `format` is a string
that accepts everything that C function `strftime()` accepts. `value` should be a _Date_
object or a numeric value representing Unix timestamp **in miliseconds**.

### locale.strptime(string, format)

Returns an _Object_ with the Date parameters that were extracted from the `string`, using
the `format`. This format is the same as in the C function `strptime()`.

### locale.monthname(value[, abbreviated = false])

Returns a month name based on the `value`. This is a _Date_ object or a numeric value
representing Unix timestamp **in miliseconds**. If you use the second argument and set
it to `true`, the month name returned will be the abbreviated form. Note that this is
the same as calling `locale.strftime("%b", value)` or `locale.strftime("%B", value)`
depending on the situation.

### locale.weekdayname(value[, abbreviated = false])

Returns a weekday name based on the `value`. This is a _Date_ object or a numeric value
representing Unix timestamp **in miliseconds**. If you use the second argument and set
it to `true`, the weekday name returned will be the abbreviated form. Note that this is
the same as calling `locale.strftime("%a", value)` or `locale.strftime("%A", value)`
depending on the situation.

