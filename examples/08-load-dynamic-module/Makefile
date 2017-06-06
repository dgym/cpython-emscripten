PYVERSION=3.5.2
PYMINOR=$(basename $(PYVERSION))

CC=emcc
OPTFLAGS=-O2
CFLAGS=-std=gnu99 $(OPTFLAGS) -g -I ../../installs/python-$(PYVERSION)/include/python$(PYMINOR)/ -Wno-warn-absolute-paths
LDFLAGS=$(OPTFLAGS) ../../installs/python-$(PYVERSION)/lib/libpython$(PYMINOR).a \
  -s TOTAL_MEMORY=268435456 \
  -s MAIN_MODULE=1 \
  -s ASSERTIONS=2 \
  -s MAIN_MODULE=1 \
  -s EMULATE_FUNCTION_POINTER_CASTS=1 \
  -s -s EXPORTED_FUNCTIONS='["_main","_runpython"]' \
  --memory-init-file 0


all: python.asm.js hello.js

hello.js: hello.bc
	$(CC) -s SIDE_MODULE=1 -o $@ $< $(CFLAGS)

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

root: hello.js ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)
	mkdir -p root/lib
	cp -a ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)/ root/lib
	cp hello.js root/lib/python$(PYMINOR)/hello.so
	# Clean up unused modules
	( \
		cd root/lib/python$(PYMINOR); \
		rm -fr test distutils ensurepip idlelib __pycache__ tkinter; \
	)


../../installs/python-$(PYVERSION)/lib/python$(PYMINOR):
	make -C ../../$(PYVERSION)
