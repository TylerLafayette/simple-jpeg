OBJS=jpeg_encoder.o simple_jpeg.o
BIN=simple_jpeg
CXXFLAGS ?= -O3 -ffast-math -fno-signed-zeros

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^
run:
	make build
	./simple_jpeg input/ant.bmp