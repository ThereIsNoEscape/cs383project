FILENAME=manual

all: source builddoc

source:	main.cpp link.cpp link.h stack.cpp stack.h
	g++ main.cpp link.cpp stack.cpp -o calc

builddoc:
	pdflatex $(FILENAME).tex
#	latex --verbose $(FILENAME).tex
#	dvips $(FILENAME).dvi
#	ps2pdf $(FILENAME).ps	

emptyrule:
