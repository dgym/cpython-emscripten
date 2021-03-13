PYVERSION=3.6.7
PYMINOR=$(basename $(PYVERSION))

CC=emcc
OPTFLAGS=-O2
CFLAGS=-std=gnu99 $(OPTFLAGS) -g \
  -I ../../installs/python-$(PYVERSION)/include/python$(PYMINOR)/ \
  -Wno-warn-absolute-paths
LDFLAGS=$(OPTFLAGS) \
  ../../installs/python-$(PYVERSION)/lib/libpython$(PYMINOR).a \
  -s TOTAL_MEMORY=268435456 \
  -s ASSERTIONS=2 \
  -s EMULATE_FUNCTION_POINTER_CASTS=1 \
  -s EXPORTED_FUNCTIONS='["_main","_PyRun_SimpleString"]' \
  --memory-init-file 0

PYX_SRC=$(patsubst ./%,%,$(shell find . -name "*.pyx"))
MOD_SRC_0=$(patsubst %.pyx,gen0/%.c,$(PYX_SRC))
MOD_SRC_1=$(patsubst %.pyx,gen1/%.c,$(PYX_SRC))
MOD_OBJ=$(patsubst %.c,%.o,$(MOD_SRC_1))


all: python.js app.zip


python.js: main.o $(MOD_OBJ) root
	$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS) \
		$(foreach d,$(wildcard root/*),--preload-file $d@/$(notdir $d))


app.zip: app
	if [ -e $@ ]; then rm $@; fi
	zip -r $@ app/*.py


serve: python.js app.zip
	@echo "Serving on port 8062"
	python3 -m http.server 8062


clean:
	-rm -fr root gen0 gen1
	-rm python.js python.data


main.o: main.c ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR) builtins.h
	$(CC) -o $@ $< $(CFLAGS)


%.o: %.c ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR)
	$(CC) -o $@ -c $< $(CFLAGS)


gen0/%.c: %.pyx
	@mkdir -p $(dir $@)
	cython -o $@ $<


gen1/%.c: gen0/%.c
	python ../../utils/patch_cython_module.py $< $@ --start-depth 1
	touch gen1


builtins.h: $(PYX_SRC)
	python ../../utils/make_cython_builtins.py $(MOD_SRC_1) --start-depth 1 > $@


root: ../../installs/python-$(PYVERSION)/lib/python$(PYMINOR) lib_files
	mkdir -p root/lib
	tar -C ../../installs/python-$(PYVERSION) -cf - --files-from lib_files | tar -C root -xvf -
	touch root


../../installs/python-$(PYVERSION)/lib/python$(PYMINOR):
	make -C ../../$(PYVERSION)
