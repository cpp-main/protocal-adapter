.PHONY: clean distclean

CXX = g++

TARGET = adapter
OBJECTS = apps.o

include protocal_adapter/app.mk

CXXFLAGS := -I$(HOME)/.tbox/include/ -DLOG_MODULE_ID='"adapter"'
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

$(TARGET) : $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

clean: 
	rm -f $(OBJECTS)

distclean: clean
	rm -r $(TARGET)
