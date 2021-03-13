include ../common.mk


all: python.js app.zip


python.js: main.o js.o root
	$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS) --preload-file root@/


%.c: %.pyx
	cython $<


app.zip: app
	rm -f $@
	zip -r $@ $<


clean:
	-rm -fr root
	-rm python.js python.data app.zip
	-rm *.o
