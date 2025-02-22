CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared
LDLIBS = -lconfigfile 
LIBRARY = libconfigfile.so
SRCDIR = src
INCDIR = include
OBJDIR = obj

LIBDIR = lib

SRCFILES = $(SRCDIR)/conf.c
OBJFILES = $(SRCFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(LIBDIR) $(LIBRARY)

$(OBJDIR):
	mkdir obj

$(LIBDIR):
	mkdir lib

$(LIBRARY): $(OBJFILES)
	$(CC) $(LDFLAGS) -o $(LIBDIR)/$@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(LIBDIR)/$(LIBRARY)

distclean:
	rm -rf $(OBJDIR) $(LIBDIR)
	rm -rf a.out

test:
	$(CC)  $(CFLAGS) -I$(INCDIR) test/main.c -L lib $(LDLIBS)

run:
	@./run

install: $(LIBRARY)
	cp $(LIBDIR)/$(LIBRARY) /usr/local/lib/
	cp $(INCDIR)/conf.h /usr/local/include/

uninstall:
	rm -f /usr/local/lib/$(LIBRARY)
	rm -f /usr/local/include/conf.h

.PHONY: all clean distclean test run install uninstall

