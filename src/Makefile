target := addrbook
tlib := laddrbook
libdir := /opt/lib
src := $(wildcard *.c)
obj := $(src:.c=.o)

all: $(target)

$(target): $(obj)
	gcc -Wall -L$(libdir) *.c -$(tlib) -o $(target)

%.o: %.c
	gcc -c $< -o $@

clean:
	rm -f $(obj) $(target)