var locale = require("locale"),
    lang = "pt_PT.utf8",
    val = 1234.56,
    dt = new Date(1999, 11, 31, 23, 59, 59, 0),
    dts = "12/25/93 13:30:00";

try {
	// this will break..
	locale.setlocale();
} catch (e) {
	console.log("setlocale() exception: " + e.message);
}

try {
	if (locale.setlocale(locale.LC_ALL, lang) === false) {
		console.log(lang + " locale is not installed in your system..");
	} else {
		console.log(lang + " locale set.");
	}
	console.log("monetary value " + val + " is '" + locale.strfmon("%i", val) + "'");
	console.log("date value '" + dt + "' is '" + locale.strftime("%A, %b %d %Y %H:%M:%S", dt.getTime()) + "' (using Unix timestamp in miliseconds)");
	console.log("date value '" + dt + "' is '" + locale.strftime("%A, %b %d %Y %H:%M:%S", dt) + "' (using Date object)");
	console.log("date value '" + dt + "' month name is '" + locale.monthname(dt) + "'");
	console.log("date value '" + dt + "' month name is '" + locale.monthname(dt, true) + "' (abbreviated)");
	console.log("date value '" + dt + "' weekday name is '" + locale.weekdayname(dt) + "'");
	console.log("date value '" + dt + "' weekday name is '" + locale.weekdayname(dt, true) + "' (abbreviated)");

	console.log("date '" + dts + "' converted with strptime():");
	console.dir(locale.strptime(dts, "%D %T"));

	console.log("bindtextdomain('test', './') -> " + locale.bindtextdomain("test", "./"));
	//console.log("textdomain('test') -> " + locale.textdomain("test"));
	//console.log("gettext('hello test') -> " + locale.gettext("hello test"));
	// instead of the 2 above lines you could just..
	console.log("dgettext('test', 'hello test') -> " + locale.dgettext("test", "hello test"));
} catch (e) {
	console.log("Exception: " + e.message);
}
