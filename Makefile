.DEFAULT_GOAL := pongsh

BUILD_DIR := tests/.build
UNITY_DIR := tests/vendor/unity
TEST_BIN := $(BUILD_DIR)/test_libmy
TEST_ARCHIVE := $(BUILD_DIR)/libmy.a
TEST_SOURCES := tests/test_libmy.c
LIB_DIRS := lib/my lib/my_printf
LIB_HEADERS := $(wildcard include/*.h)
LIB_SOURCES := $(sort $(wildcard $(addsuffix /my_*.c,$(LIB_DIRS))))
LIB_OBJECTS := $(addprefix $(BUILD_DIR)/,$(notdir $(LIB_SOURCES:.c=.o)))
LIB_DEPS := $(LIB_HEADERS) Makefile

LS_DIR := lib/my_ls
LS_FILES := $(sort $(wildcard $(LS_DIR)/*.c $(LS_DIR)/*/*.c))
LS_UNIT_BIN := $(BUILD_DIR)/test_my_ls
LS_UNIT_MODULES := options/options.c directory/sort.c directory/entry.c
LS_UNIT_FILES := $(addprefix $(LS_DIR)/,$(LS_UNIT_MODULES))
LS_UNIT_SOURCES := tests/test_my_ls.c $(LS_UNIT_FILES)
LS_FLAGS := -D_DEFAULT_SOURCE -ffreestanding -Iinclude
LS_BUILD := $(CC) $(CPPFLAGS) $(CFLAGS) $(LS_FLAGS) $(LDFLAGS)

SH_DIR := src
SH_FILES := $(sort $(wildcard $(SH_DIR)/*.c $(SH_DIR)/*/*.c))
SH_FLAGS := -D_DEFAULT_SOURCE -ffreestanding -Iinclude
SH_BUILD := $(CC) $(CPPFLAGS) $(CFLAGS) $(SH_FLAGS) $(LDFLAGS)

vpath %.c $(LIB_DIRS)
UNITY_HEADERS := $(addprefix $(UNITY_DIR)/,unity.h unity_internals.h)
TEST_INPUTS := $(TEST_SOURCES) $(UNITY_DIR)/unity.c $(TEST_ARCHIVE)
TEST_INCLUDES := -Iinclude -I$(UNITY_DIR)
TEST_CC := $(CC) $(CPPFLAGS) $(CFLAGS) $(TEST_INCLUDES) $(LDFLAGS)
LS_UNIT_INPUTS := $(LS_UNIT_SOURCES) $(UNITY_DIR)/unity.c $(TEST_ARCHIVE)
LS_UNIT_DEPS := $(UNITY_HEADERS) include/my_ls.h include/my.h Makefile
CFLAGS += -std=c11 -Wall -Wextra

test: test-libmy test-ls test-pongsh

test-libmy: $(TEST_BIN)
	$(abspath $(TEST_BIN))

test-ls-unit: $(LS_UNIT_BIN)
	$(abspath $(LS_UNIT_BIN))

test-ls: my_ls test-ls-unit
	sh tests/test_my_ls.sh $(abspath my_ls)

my_ls: $(LS_FILES) $(LIB_DEPS) lib/my/libmy.a
	$(LS_BUILD) $(LS_FILES) lib/my/libmy.a $(LDLIBS) -o $@

test-pongsh: pongsh
	sh tests/test_pongsh.sh $(abspath pongsh)

pongsh: $(SH_FILES) $(LIB_DEPS) lib/my/libmy.a
	$(SH_BUILD) $(SH_FILES) lib/my/libmy.a $(LDLIBS) -o $@

lib/my/libmy.a: $(LIB_SOURCES) $(LIB_DEPS) lib/my/Makefile
	$(MAKE) -C lib/my

$(TEST_BIN): $(TEST_INPUTS) $(UNITY_HEADERS) include/my.h Makefile
	$(TEST_CC) $(TEST_INPUTS) $(LDLIBS) -o $@

$(LS_UNIT_BIN): $(LS_UNIT_INPUTS) $(LS_UNIT_DEPS)
	$(TEST_CC) $(LS_FLAGS) $(LS_UNIT_INPUTS) $(LDLIBS) -o $@

$(TEST_ARCHIVE): $(LIB_OBJECTS) Makefile
	$(AR) rcs $@ $(LIB_OBJECTS)

$(BUILD_DIR)/%.o: %.c $(LIB_DEPS) | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -ffreestanding -Iinclude -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) my_ls pongsh
	$(MAKE) -C lib/my fclean

.PHONY: test test-libmy test-ls test-ls-unit test-pongsh clean
