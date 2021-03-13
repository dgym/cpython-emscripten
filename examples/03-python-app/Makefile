PYVERSION=3.6.7
PYMINOR=$(basename $(PYVERSION))

CC=emcc
OPTFLAGS=-O2
CFLAGS=-std=gnu99 $(OPTFLAGS) -g -I ../../installs/python-$(PYVERSION)/include/python$(PYMINOR)/ -Wno-warn-absolute-paths
LDFLAGS=$(OPTFLAGS) ../../installs/python-$(PYVERSION)/lib/libpython$(PYMINOR).a \
  -s TOTAL_MEMORY=268435456 \
  -s ASSERTIONS=2 \
  -s EMULATE_FUNCTION_POINTER_CASTS=1 \
  -s EXPORTED_FUNCTIONS='["_main","_PyRun_SimpleString"]' \
  --memory-init-file 0


all: python.js app.zip


python.js: main.o root
	$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS) \
		$(foreach d,$(wildcard root/*),--preload-file $d@/$(notdir $d))


app.zip: app
	zip -r $@ $<


serve: python.js app.zip
	@echo "Serving on port 8062"
	python3 -m http.server 8062


clean:
	-rm -fr root
	-rm python.js python.data
	-rm *.o


%.o: %.c ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)
	$(CC) -o $@ -c $< $(CFLAGS)


root: ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR) lib_files
	mkdir -p root/lib
	tar -C ../../installs/python-$(PYVERSION) -cf - --files-from lib_files | tar -C root -xvf -
	touch root


../../installs/python-$(PYVERSION)/lib/python$(PYMINOR):
	make -C ../../$(PYVERSION)
