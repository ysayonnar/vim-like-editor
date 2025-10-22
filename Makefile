.PHONY: build run build-run

FILE ?= "data.txt"

notes:
	grep -r -n --color=always -E "TODO|FIXME" --exclude-dir=".git"

build:
	@g++ -o ./build/main main.cpp \
		lib/command_mode.cpp \
		lib/editor.cpp \
		lib/insert_mode.cpp \
		lib/normal_mode.cpp \
		lib/string.cpp \
		lib/text_buffer.cpp \
		lib/visual_mode.cpp \

run:
	# ./build/main ./test-data/$(FILE)
	./build/main ./lib/string.cpp

build-run:
	$(MAKE) build
	$(MAKE) run
