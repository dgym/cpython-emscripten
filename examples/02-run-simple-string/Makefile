include ../common.mk

LDFLAGS += -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'
LDFLAGS += -s EXPORTED_FUNCTIONS='["_main","_PyRun_SimpleString"]'

all: python.js


python.js: main.o root
	$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS) --preload-file root@/


clean:
	-rm -fr root
	-rm python.js python.data
	-rm *.o
