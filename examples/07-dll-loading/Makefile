PYVERSION=3.5.2
PYMINOR=$(basename $(PYVERSION))

CC=EMCC_FORCE_STDLIBS=1 emcc
OPTFLAGS=-O3
CFLAGS=-std=gnu99 $(OPTFLAGS) -g -I ../../installs/python-$(PYVERSION)/include/python$(PYMINOR)/ -Wno-warn-absolute-paths
LDFLAGS=$(OPTFLAGS) \
  -s TOTAL_MEMORY=268435456 \
  -s MAIN_MODULE=1 \
  -s ASSERTIONS=1 \
  -s EXPORTED_FUNCTIONS='["_main"]' \
  -s EMULATE_FUNCTION_POINTER_CASTS=1 \
  --memory-init-file 0


all: python.asm.js


python.asm.js: main.bc root
	$(CC) -o $@ $(filter %.bc,$^) $(LDFLAGS) \
		$(foreach d,$(wildcard root/*),--preload-file $d@/$(notdir $d))


serve: python.asm.js
	@echo "Serving on port 8062"
	python -m SimpleHTTPServer 8062


clean:
	-rm -fr root
	-rm python.asm.js python.asm.data
	-rm *.bc


%.bc: %.c ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)
	$(CC) -o $@ $< $(CFLAGS)


root: ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)
	mkdir -p root/lib
	#cp ../../installs/python-$(PYVERSION)/lib/libpython$(PYMINOR).js root
	cp -a ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)/ root/lib

../../installs/python-$(PYVERSION)/lib/python$(PYMINOR):
	make -C ../../$(PYVERSION)
