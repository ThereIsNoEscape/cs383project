all: source document

source:	main.cpp link.cpp link.h stack.cpp stack.h
    g++ main.cpp link.cpp stack.cpp -ocalc
    
document:
    echo "?!?!??!"
