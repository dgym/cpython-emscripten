PYVERSION=3.6.7
PYMINOR=$(basename $(PYVERSION))

CC=emcc
OPTFLAGS=-O3
CFLAGS=-std=gnu99 $(OPTFLAGS) -g -I ../../installs/python-$(PYVERSION)/include/python$(PYMINOR)/ -Wno-warn-absolute-paths -s WASM=1
LDFLAGS=$(OPTFLAGS) ../../installs/python-$(PYVERSION)/lib/libpython$(PYMINOR).a \
  -s TOTAL_MEMORY=268435456 \
  -s ASSERTIONS=2 \
  -s EMULATE_FUNCTION_POINTER_CASTS=1 \
  -s WASM=1 \
  --memory-init-file 0


all: python.js


python.js: main.o root
	$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS) \
		$(foreach d,$(wildcard root/*),--preload-file $d@/$(notdir $d))


serve: python.js
	@echo "Serving on port 8062"
	python3 -m http.server 8062


clean:
	-rm -fr root
	-rm python.js python.data
	-rm *.o


%.o: %.c ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)
	$(CC) -o $@ -c $< $(CFLAGS)


root: ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)
	mkdir -p root/lib
	cp -a ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)/ root/lib
	# Clean up unused modules
	( \
		cd root/lib/python$(PYMINOR); \
		rm -fr test distutils ensurepip idlelib __pycache__ tkinter; \
	)

../../installs/python-$(PYVERSION)/lib/python$(PYMINOR):
	make -C ../../$(PYVERSION)
