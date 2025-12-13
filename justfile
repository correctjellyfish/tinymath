#!/usr/bin/env just --justfile

alias s := setup
alias c := compile
alias t := test
alias d := docs

browser := "firefox"

default: setup compile test

setup:
    meson setup builddir

compile:
    meson compile -C builddir

test:
    meson test -C builddir

docs_generate:
    doxygen

docs_open:
    {{ browser }} docs/html/index.html

docs: docs_generate docs_open
