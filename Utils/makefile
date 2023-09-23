OBJECTS = tmp/assert.o

PHONY = cleanup

default : libutils.a cleanup

tmp/%.o : src/%.cc
	g++  -c -o $@ $< ${CFLAGS}	

libutils.a : ${OBJECTS}
	ar -cvq $@ $<

cleanup :
	rm -r tmp/*