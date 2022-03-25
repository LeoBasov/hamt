#!/bin/bash

latexmk -pdf -output-directory="../" main.tex
latexmk -c -output-directory="../"
