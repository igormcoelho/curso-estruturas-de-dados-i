#!/bin/bash

#echo "will compile tex"
pdflatex simple.tex 2>/dev/null 1>&2
#echo "will crop pdf"
#pdfcrop simple.pdf 2>/dev/null 1>&2
#echo "will convert to jpg"
#convert -quality 100 -density 300 simple-crop.pdf -flatten -sharpen 0x1.0 image.jpg 2>/dev/null 1>&2
