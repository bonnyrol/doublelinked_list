CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIB = list.a
EXEC = main.out
MENU = main.c
OBJDIR = build
WORKDIR = functions

SOURCES = $(wildcard $(WORKDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))

all: $(EXEC)

$(EXEC): $(LIB)
	$(CC) $(MENU) -L. $(LIB) -o $@

$(LIB): $(OBJDIR) $(OBJECTS)
	ar rcs $@ $(OBJDIR)/*.o 
	ranlib $(LIB)

$(OBJDIR)/%.o: $(WORKDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir build

clean:
	rm -rf $(OBJDIR)
	rm -f $(LIB)
	rm -f *.out

leak:
	valgrind --tool=memcheck --leak-check=yes ./$(EXEC)

rebulid: clean all

echo:
	@echo $(SOURCES)
	@echo $(OBJECTS)


