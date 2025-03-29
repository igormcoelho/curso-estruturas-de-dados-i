MDFILE=1-revisao-tipos.md
OUTHTML=index.html
OUTPDF=1-revisao-tipos.pdf

all: deps
	/usr/bin/pandoc -s -V revealjs-url=./reveal.js --standalone -V theme=beige -s -t revealjs \
         --filter pandoc-katex --css katex.min.css \
	$(MDFILE) -o $(OUTHTML) --slide-level 2 # --toc
	# sed -i 's|//dist/|/dist/|g' index.html
	#
	#
	# -F pandoc-crossref
	/usr/bin/pandoc --toc -s --embed-resources --standalone --filter pandoc-latex-fontsize -V theme:Warsaw -t beamer \
	 -H header.tex \
		$(MDFILE) -o $(OUTPDF) --slide-level 2
# $(OUTPDF)

#--filter pandoc-source-exec

run:
	python3 -m http.server 8081
	#python2 -m SimpleHTTPServer 8081

env:
	source ~/.cargo/env
	conda activate

deps:
	wget -nc https://cdn.jsdelivr.net/npm/katex@0.16.21/dist/katex.min.css
	# wget -nc https://github.com/hakimel/reveal.js/archive/master.tar.gz
	wget -nc https://github.com/hakimel/reveal.js/archive/refs/tags/5.2.1.tar.gz
	# tar -xzvf master.tar.gz && mv reveal.js-master reveal.js
	tar -xzvf 5.2.1.tar.gz && mv reveal.js-5.2.1 reveal.js
