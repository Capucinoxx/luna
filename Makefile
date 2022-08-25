SRC_DIRS = ./data-structure/
CC = gcc
RM = rm -rf
SRCS = $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS = $(addsuffix .o,$(basename $(SRCS)))
DEPS = $(OBJS:.o=.d)

test: $(OBJS)
	$(CC) ./tests/test.c $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) test.exe test $(OBJS) $(DEPS)

-include $(DEPS)