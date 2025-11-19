##
# HTTP Server because i'm unoriginal like that
#
# @file
# @version 0.1

# a lot of this is stolen here: https://makefiletutorial.com/#makefile-cookbook
EXE = http_serv
SRC_DIR = ./src
BUILD_DIR = ./build

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

INC_DIRS = $(shell find $(SRC_DIRS) -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

CC = gcc
CFLAGS += -Wall -Wextra $(INC_FLAGS) -MMD -MD

$(BUILD_DIR)/$(EXE): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
	all clean

clean:
	rm -r $(BUILD_DIR)
-include $(DEPS)
# end
