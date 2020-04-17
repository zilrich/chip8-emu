NAME := chip8

LIBS := $(shell /usr/bin/sdl2-config --cflags --libs) -lpthread

SRCDIR := ./src/
INCDIR := ./inc/
OBJDIR := ./obj/
DEPDIR := ./dep/

SRCFILES := $(wildcard $(SRCDIR)*.c)
INCFILES := $(wildcard $(INCDIR)*.h)
OBJFILES := $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCFILES))
DEPFILES := $(patsubst $(SRCDIR)%.c, $(DEPDIR)%.d, $(SRCFILES))

$(NAME) : $(OBJFILES) $(DEPFILES)
	$(CC) -o $(NAME) $(OBJFILES) $(LIBS)

clean :
	rm -rf $(OBJFILES) $(DEPFILES)

$(DEPDIR)%.d : $(SRCDIR)%.c
	$(CC) -MM -MT $(OBJDIR)$(notdir $(basename $^)).o -MF $(DEPDIR)$(notdir $(basename $^)).d $^

include $(wildcard $(DEPDIR)*.d)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) -c -o $@ -ggdb $<
