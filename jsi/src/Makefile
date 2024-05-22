COMPILER = gcc
TARGET = ../lib/libjsi.a
OBJS = jsi.o

%.o: %.c
	@echo compiling $<
	@$(COMPILER) -c -o $@ $<

$(TARGET): $(OBJS)
	@echo making static libary
	@ar rcs $(TARGET) $(OBJS)
test: test.c jsi.*
	@echo making test
	@$(COMPILER) -o $@ $< $(TARGET) -g

# Objects.
jsi.o: jsi.c jsi.h

clean:
	rm *.o
	rm test
	rm $(TARGET)
