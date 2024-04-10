.PHONY: clean distclean

CXX = g++

EXE = adapter
OBJECTS = apps.o
PROTOCAL_ADAPTER_LIB = ./protocal_adapter/libadapter.a

CXXFLAGS := -I$(HOME)/.tbox/include/
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

all: $(EXE)

$(PROTOCAL_ADAPTER_LIB):
	make -C protocal_adapter libadapter.a

$(EXE) : $(OBJECTS) $(PROTOCAL_ADAPTER_LIB)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

clean: 
	rm -f $(OBJECTS)

distclean: clean
	make -C protocal_adapter distclean
	rm -f $(EXE)
