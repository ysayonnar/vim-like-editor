.PHONY: build run build-run

DEFAULT_FILE_PATH ?= "test-data/data.txt"

notes:
	grep -r -n --color=always -E "TODO|FIXME" --exclude-dir=".git"

build:
	g++ -o ./build/main main.cpp lib/string.cpp

run: 
	./build/main $(DEFAULT_FILE_PATH)

build-run:
	$(MAKE) build
	$(MAKE) run