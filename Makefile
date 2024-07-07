CC = gcc
CFLAGS = -std=c11 -g
SRCS = Collision-Detector.c
OBJS = $(SRCS:.c=.o)
TARGET = pa2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

test: $(TARGET)
	./$(TARGET) points.txt

clean:
	rm -f $(TARGET) $(OBJS) *~