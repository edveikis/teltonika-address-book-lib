target := libaddrbook
src := $(wildcard *.c)
obj := $(src:.c=.o)
libdir := /opt/lib

all: $(target)

$(target):
	$(CC) -Wall -fPIC -c *.c
	$(CC) -shared -Wl,-soname,$(target).so.1 -o $(target).so.1.0 *.o

install:
	sudo mkdir -p $(libdir) && mv $(target).so.1.0 $(libdir)/
	sudo ln -sf $(libdir)/$(target).so.1.0 $(libdir)/$(target).so.1
	sudo ln -sf $(libdir)/$(target).so.1.0 $(libdir)/$(target).so

clean:
	rm -f $(obj) $(target).*