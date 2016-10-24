PROJECT=manual
TEX=pdflatex
BIBTEX=bibtex
BUILDTEX=$(TEX) $(PROJECT).tex

all: source builddoc

source:	main.cpp link.cpp link.h stack.cpp stack.h
	g++ main.cpp link.cpp stack.cpp -o calc

builddoc:
	$(BUILDTEX)
	$(BIBTEX) $(PROJECT)
	$(BUILDTEX)
	$(BUILDTEX)

emptyrule:
