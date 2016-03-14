SRCS := main.c rs232.c telnet.c match.c queue.c http_util.c cJSON.c config.c
PROG := siproxy
#CC   := ~/openwrt/SWT/baseline1/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-gcc
CURDIR := $(shell pwd)

LIBS = paho-mqtt3a
LINKFLAGS = $(addprefix -l,$(LIBS))
LIBPATH = $(CURDIR)/paho-c/build/output/
LIBINCLUDE = $(CURDIR)/paho-c/src/
LIBPATHS = $(patsubst %,$(LIBPATH)/lib%.so, $(LIBS))

CFLAGS := -g -O0 -Wall -I$(LIBINCLUDE)
LDFLAGS:= -lrt -lpthread -lm
OBJS   := $(SRCS:.c=.o)


$(PROG): $(OBJS)
	$(MAKE) -C paho-c
	$(CC) $(CFLAGS) -L$(LIBPATH) -o $@ $^ $(LDFLAGS) $(LINKFLAGS)

-include $(SRCS:.c=.d)

$.d:%.c
	$(CC) -MM $(CFLAGS) $< | sed 's#\(.*\)\.o:#\1.o\1\1.d:#g' > $@


.PHONY: all
all: $(PROG)

clean:
	$(MAKE) -C paho-c clean
	rm -rf $(PROG) *.d *.o

