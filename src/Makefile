CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIB = list.a
EXEC = main.out
MENU = main.c
OBJDIR = obj
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
	mkdir obj

clean:
	rm -rf $(OBJDIR)
	rm -r $(LIB)
	rm -r *.out

leak:
	valgrind --took=memcheck --leak-check=yes ./$(EXEC)

echo:
	@echo $(SOURCES)
	@echo $(OBJECTS)


