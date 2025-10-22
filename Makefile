.PHONY: build run build-run

FILE ?= "data.txt"

notes:
	grep -r -n --color=always -E "TODO|FIXME" --exclude-dir=".git"

build:
	@echo "building..."
	@g++ -o ./build/main main.cpp \
		lib/command_mode.cpp \
		lib/editor.cpp \
		lib/insert_mode.cpp \
		lib/normal_mode.cpp \
		lib/string.cpp \
		lib/text_buffer.cpp \
		lib/visual_mode.cpp \

run:
	@echo "runnig..."
	@./build/main ./test-data/$(FILE)

build-run:
	@$(MAKE) build
	@$(MAKE) run
