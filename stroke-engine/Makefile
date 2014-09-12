# This part is for converting code to JavaScript using emscripten.

EMSCRIPTEN_HOME=~/emscripten/
.PHONY: all clean

all: engine_c.js

engine_c.js: engine_c.bc builtTreeDict1.txt builtTreeDict2.txt builtTree1.txt builtTree2.txt
	~/emscripten/em++ engine_c.bc -O3 \
	--preload-file builtTreeDict1.txt --preload-file builtTreeDict2.txt --preload-file builtTree1.txt --preload-file builtTree2.txt \
	-s \
	EXPORTED_FUNCTIONS="['_assocSearchInit','_assocSearchSearch','_strokeSearchInit','_strokeSearchSearch']" \
	-o $@

engine_c.bc: assocTernaryTree.cpp assocSearch.cpp strokeTernaryTree.cpp strokeSearch.cpp
	~/emscripten/em++ -O3 assocTernaryTree.cpp assocSearch.cpp strokeTernaryTree.cpp strokeSearch.cpp -o $@

clean:
	rm -f *.model* *.s
	rm -f *.bc
	rm -f *.js *.data *.js.map
	rm -f *.o