PYVERSION=3.5.2
PYMINOR=$(basename $(PYVERSION))

ROOT=$(abspath ..)

HOSTINSTALL=$(ROOT)/build/$(PYVERSION)/host
HOSTBUILD=$(HOSTINSTALL)/Python-$(PYVERSION)
HOSTPYTHON=$(HOSTINSTALL)/bin/python3$(EXE)
HOSTPGEN=$(HOSTINSTALL)/bin/pgen$(EXE)

BUILD=$(ROOT)/build/$(PYVERSION)/Python-$(PYVERSION)
INSTALL=$(ROOT)/installs/python-$(PYVERSION)
TARBALL=$(ROOT)/downloads/Python-$(PYVERSION).tgz
URL=https://www.python.org/ftp/python/$(PYVERSION)/Python-$(PYVERSION).tgz
LBASE=libpython$(PYMINOR)
LIB=$(LBASE).a
DLIB=$(LBASE).so
JSLIB=$(LBASE).js

all: install


install: $(BUILD)/$(LIB) $(BUILD)/$(JSLIB)
	( \
		cd $(BUILD); \
		sed -i -e 's/libinstall:.*/libinstall:/' Makefile; \
		EMCC_FORCE_STDLIBS=1 emmake make CFLAGS="-s MAIN_MODULE=1 -s LINKABLE=1 -s ASSERTIONS=2 -g" LDFLAGS="-s MAIN_MODULE=1 -g" HOSTPYTHON=$(HOSTPYTHON) PYTHON_FOR_BUILD=$(HOSTPYTHON) CROSS_COMPILE=yes inclinstall libinstall $(LIB) && \
		cp $(LIB) $(INSTALL)/lib/ && \
		cp $(JSLIB) $(INSTALL)/lib/ && \
		cp $(HOSTINSTALL)/lib/python$(PYMINOR)/_sysconfigdata.py $(INSTALL)/lib/python$(PYMINOR)/ \
	)


clean:
	-rm -fr $(HOSTINSTALL)
	-rm -fr $(BUILD)


$(TARBALL):
	[ -d ../downloads ] || mkdir ../downloads
	wget -q -O $@ $(URL)
	md5sum --quiet --check checksums || (rm $@; false)


$(HOSTPYTHON) $(HOSTPGEN): $(TARBALL)
	mkdir -p $(HOSTINSTALL)
	[ -d $(HOSTBUILD) ] || tar -C $(HOSTINSTALL) -xf $(TARBALL)
	( \
		cd $(HOSTBUILD); \
		./configure --prefix=$(HOSTINSTALL) && \
		make install && \
		cp Parser/pgen$(EXE) $(HOSTINSTALL)/bin/ && \
		make distclean \
	)


$(BUILD)/.patched: $(TARBALL)
	[ -d $(BUILD) ] || (mkdir -p $(dir $(BUILD)); tar -C $(dir $(BUILD)) -xf $(TARBALL))
	cp posixmodule.c $(BUILD)/Modules
	cp random.c $(BUILD)/Python
	cat patches/*.patch | (cd $(BUILD) ; patch -p1)
	touch $@


$(BUILD)/Makefile: $(BUILD)/.patched
	cp config.site $(BUILD)/
	( \
		cd $(BUILD); \
		CONFIG_SITE=./config.site READELF=true emconfigure ./configure --without-threads --without-pymalloc --disable-shared --disable-ipv6 --without-gcc --host=asmjs-unknown-emscripten --build=$(shell $(BUILD)/config.guess) --prefix=$(INSTALL) CFLAGS="-s MAIN_MODULE=1 -s ASSERTIONS=2 -s LINKABLE=1" LDFLAGS="-s MAIN_MODULE=1 -s LINKABLE=1" ; \
	)


$(BUILD)/$(LIB): $(BUILD)/Makefile $(HOSTPYTHON) $(HOSTPGEN) Setup.local
	cp Setup.local $(BUILD)/Modules/
	( \
		cd $(BUILD)/Modules/zlib; \
		CFLAGS="-s MAIN_MODULE=1 -s ASSERTIONS=2 -s LINKABLE=1 -g" LDFLAGS="-s MAIN_MODULE=1 -g" EMCC_FORCE_STDLIBS=1 emconfigure ./configure --static \
	)
	( \
		cd $(BUILD); \
		EMCC_FORCE_STDLIBS=1 emmake make CFLAGS="-s MAIN_MODULE=1 -s ASSERTIONS=2 -s LINKABLE=1 -g" LDFLAGS="-s MAIN_MODULE=1 -g" HOSTPYTHON=$(HOSTPYTHON) HOSTPGEN=$(HOSTPGEN) CROSS_COMPILE=yes $(LIB) \
	)

$(BUILD)/$(JSLIB): $(BUILD)/$(LIB)
	( \
		cd $(BUILD); \
		EMCC_FORCE_STDLIBS=1 emmake make CFLAGS="-s MAIN_MODULE=1 -s ASSERTIONS=2 -s LINKABLE=1 -g" LDFLAGS="-s MAIN_MODULE=1 -g" HOSTPYTHON=$(HOSTPYTHON) HOSTPGEN=$(HOSTPGEN) CROSS_COMPILE=yes $(DLIB); \
		emcc -g -s MAIN_MODULE=1 -s LINKABLE=1 $(DLIB) -o $(JSLIB) \
	)
