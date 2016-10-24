all: source document

source:	main.cpp link.cpp link.h stack.cpp stack.h
	g++ main.cpp link.cpp stack.cpp -o calc
    
document:
	echo "Utilize command below this (in makefile) for Latex-compiled documentation?"

latex:
	latex lexer.tex    

emptyrule:
