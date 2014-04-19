CFLAGS = -I. -I../../core -Wall -Wextra

SOURCES = main.c ../../core/game.c
OBJECTS = main.o ../../core/game.o
TARGET = engine.html

# Targets start here.
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $(OBJECTS)

clean:
	$(RM) $(TARGET) $(OBJECTS)

depend:
	@$(CC) $(CFLAGS) -MM $(SOURCES)
	
# list targets that do not create files (but not all makes understand .PHONY)
.PHONY:	all clean depend

# Dependences (call 'make depend' to generate); do not delete:
# Build for these is implicit, no need to specify compiler command lines.

main.o: main.c ../../core/game.h
../../core/game.o: ../../core/game.c ../../core/game.h glwrapper.h