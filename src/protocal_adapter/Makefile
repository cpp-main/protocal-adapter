.PHONY: clean distclean

CXX ?= g++
AR  ?= ar

LIB_NAME = adapter
STATIC_LIB = lib$(LIB_NAME).a
SHARED_LIB = lib$(LIB_NAME).so.0.0.0

OBJECTS = \
	create.o \
	plugin.o \
	main_module.o \
	protocals/mqtt.o \
	protocals/uart.o \
	protocals/udp.o \
	protocals/tcp_client.o \
	protocals/tcp_server.o \

CXXFLAGS := -I$(HOME)/.tbox/include/ -fPIC -DLOG_MODULE_ID='"pa"'
LDFLAGS := -L$(HOME)/.tbox/lib/
LIBS := \
	-ltbox_main \
	-ltbox_terminal \
	-ltbox_network \
	-ltbox_mqtt \
	-ltbox_eventx \
	-ltbox_event \
	-ltbox_log \
	-ltbox_util \
	-ltbox_base \
	-lmosquitto \
	-lpthread \
	-ldl

all: $(STATIC_LIB) $(SHARED_LIB)

$(STATIC_LIB) : $(OBJECTS)
	$(AR) rc $@ $^

$(SHARED_LIB) : $(OBJECTS)
	$(CXX) -shared $^ -Wl,-soname,$(SHARED_LIB) -o $@ $(LDFLAGS) $(LIBS)

clean: 
	rm -f $(OBJECTS)

distclean: clean
	rm -f $(STATIC_LIB) $(SHARED_LIB)
