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

