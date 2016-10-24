all: source document

source:	main.cpp link.cpp link.h stack.cpp stack.h
	g++ main.cpp link.cpp stack.cpp -o calc
    
document:
	echo "Insert command for Latex here, to process documentation."
