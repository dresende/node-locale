NodeJS Locale Bindings
======================

The goal of this repo is to bind the common used functions from **locale.h**.

The next code shows how it will look like in the future. This actually works, but it's
the only method and constants supported for now (`setlocale`).

    var locale = require("locale");
    
    if (locale.setlocale(locale.LC_ALL, "en_US.utf8")) {
    	//...
    }

## Installation

You need to build the code. To do this you need `node-waf` command. Just pull the code,
go to `src` folder and type:

    node-waf configure
    node-waf build
    node-waf install

