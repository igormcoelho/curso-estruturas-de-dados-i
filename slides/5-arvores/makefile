MDFILE=5-arvores.md
OUTHTML=index.html
OUTPDF=5-arvores.pdf

all: deps
	/usr/bin/pandoc -s --embed-resources --standalone -V theme=beige -s -t revealjs \
     --filter pandoc-katex --css katex.min.css \
		$(MDFILE) -o $(OUTHTML) --slide-level 2 # --toc
	#
	#
	# -F pandoc-crossref
	/usr/bin/pandoc --toc -s --embed-resources --standalone -V theme:Warsaw -t beamer \
	 -H header.tex \
		$(MDFILE) -o $(OUTPDF) --slide-level 2

#--filter pandoc-source-exec

run:
	python3 -m http.server 8081
	#python2 -m SimpleHTTPServer 8081

env:
	source ~/.cargo/env
	conda activate

deps:
	wget -nc https://cdn.jsdelivr.net/npm/katex@0.11.1/dist/katex.min.css
	wget -nc https://github.com/hakimel/reveal.js/archive/master.tar.gz
	# tar -xzvf master.tar.gz && mv reveal.js-master reveal.js
