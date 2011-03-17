NodeJS Locale Bindings
======================

The goal of this repo is to bind the common used functions from **locale.h**, **time.h**
and **intl.h**. If you have more suggestions please post an issue.

## Installation

You need to build the code. To do this you need `node-waf` command. Just pull the code,
go to `src` folder and type:

    node-waf configure
    node-waf build
    node-waf install

## Usage

To use this module you just have to:

    var locale = require("locale");

Check [[API]] for the list available functions.
