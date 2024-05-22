COMPILER = g++
LDFLAGS = -static-libstdc++ -static-libgcc

OBJS = main.o rps.o rps_logger.o
TARGET = ../rps_game

%.o: %.cpp
	@echo compiling $<
	@$(COMPILER) $(CFLAGS) -c -o $@ $<
$(TARGET): $(OBJS)
	@echo making exe
	@$(COMPILER) -o $(TARGET) $(OBJS) $(LDFLAGS)
debug:
	$(COMPILER) -c *.cpp -g
	$(COMPILER) -o $(TARGET) $(OBJS) $(LDFLAGS) -g

# Objects
main.o: *.cpp *.h
rps.o: rps.cpp rps.h
rps_logger.o: rps_logger.cpp rps_logger.h rps.cpp rps.h

clean:
	rm *.o
	rm $(TARGET)
