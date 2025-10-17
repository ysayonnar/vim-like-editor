.PHONY: build run build-run

FILE ?= "data.txt"

notes:
	grep -r -n --color=always -E "TODO|FIXME" --exclude-dir=".git"

build:
	g++ -o ./build/main main.cpp lib/string.cpp

run: 
	./build/main ./test-data/$(FILE)

build-run:
	$(MAKE) build
	$(MAKE) run