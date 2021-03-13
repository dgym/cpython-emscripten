include ../common.mk


all: python.js


python.js: main.o root
	$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS) --preload-file root@/


clean:
	-rm -fr root
	-rm python.js python.data
	-rm *.o
