var locale = require("locale"),
    lang = "pt_PT.utf8", val = 1234.56;

try {
	// this will break..
	locale.setlocale();
} catch (e) {
	console.log("setlocale() exception: " + e.message);
}

try {
	if (locale.setlocale(locale.LC_MONETARY, lang) === false) {
		console.log(lang + " locale is not installed in your system..");
	} else {
		console.log(lang + " locale set.");
	}
} catch (e) {
	console.log("Exception: " + e.message);
}
