include ../common.mk

PYX_SRC=$(patsubst ./%,%,$(shell find . -name "*.pyx"))
MOD_SRC_0=$(patsubst %.pyx,gen0/%.c,$(PYX_SRC))
MOD_SRC_1=$(patsubst %.pyx,gen1/%.c,$(PYX_SRC))
MOD_OBJ=$(patsubst %.c,%.o,$(MOD_SRC_1))


all: python.js app.zip


python.js: main.o $(MOD_OBJ) root
	$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS) --preload-file root@/


app.zip: app
	rm -f $@
	zip -r $@ app/*.py


clean:
	-rm -fr root gen0 gen1
	-rm python.js python.data app.zip


gen0/%.c: %.pyx
	@mkdir -p $(dir $@)
	cython -o $@ $<


gen1/%.c: gen0/%.c
	python ../../utils/patch_cython_module.py $< $@ --start-depth 1
	touch gen1


builtins.h: $(PYX_SRC)
	python ../../utils/make_cython_builtins.py $(MOD_SRC_1) --start-depth 1 > $@
