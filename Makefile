CC = gcc
CFLAGS = -std=c11 -g
SRCS = collision_detection.c
OBJS = $(SRCS:.c=.o)
TARGET = pa2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS) *~
