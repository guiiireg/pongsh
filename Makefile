.DEFAULT_GOAL := test

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

vpath %.c $(LIB_DIRS)
UNITY_HEADERS := $(addprefix $(UNITY_DIR)/,unity.h unity_internals.h)
TEST_INPUTS := $(TEST_SOURCES) $(UNITY_DIR)/unity.c $(TEST_ARCHIVE)
TEST_INCLUDES := -Iinclude -I$(UNITY_DIR)
TEST_CC := $(CC) $(CPPFLAGS) $(CFLAGS) $(TEST_INCLUDES) $(LDFLAGS)
CFLAGS += -std=c11 -Wall -Wextra

test: $(TEST_BIN)
	$(abspath $(TEST_BIN))

$(TEST_BIN): $(TEST_INPUTS) $(UNITY_HEADERS) include/my.h Makefile
	$(TEST_CC) $(TEST_INPUTS) $(LDLIBS) -o $@

$(TEST_ARCHIVE): $(LIB_OBJECTS) Makefile
	$(AR) rcs $@ $(LIB_OBJECTS)

$(BUILD_DIR)/%.o: %.c $(LIB_DEPS) | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -ffreestanding -Iinclude -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: test clean
