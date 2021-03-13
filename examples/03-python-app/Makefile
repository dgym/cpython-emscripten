include ../common.mk


all: python.js app.zip


python.js: main.o root
	$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS) --preload-file root@/


app.zip: app
	zip -r $@ $<


clean:
	-rm -fr root
	-rm python.js python.data app.zip
	-rm *.o
