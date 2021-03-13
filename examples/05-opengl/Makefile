include ../common.mk

CFLAGS += -s USE_SDL=2
LDFLAGS += -s USE_SDL=2 --closure 0


all: python.js app.zip


python.js: main.o app/sdl2.o root
	$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS) --preload-file root@/


app.zip: app
	rm -f $@
	zip -r $@ app/*.py


clean:
	-rm -fr root
	-rm python.js python.data app.zip
	-rm *.o


%.c: %.pyx
	cython $<
