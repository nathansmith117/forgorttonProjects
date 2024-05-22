FLCON = fltk-config
COMPILER = $(shell $(FLCON) --cxx)
CFLAGS = $(shell $(FLCON) --use-images --cxxflags)
LDFLAGS = $(shell $(FLCON) --use-images --ldstaticflags) -static-libstdc++ -static-libgcc

TARGET = simple_game

$(TARGET): $(TARGET).cpp
	$(COMPILER) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LDFLAGS)
debug:
	$(COMPILER) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LDFLAGS) -g
clean:
	rm $(TARGET)
