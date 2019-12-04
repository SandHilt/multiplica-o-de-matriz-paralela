SUBDIRS := $(wildcard omp/matriz/.) $(wildcard mpi/matriz/.)\
	$(wildcard serial/matriz/.)

america: clear
great: all

again:
	./run.sh

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ clean all 

.PHONY: all $(SUBDIRS)

clear:
	rm -rf *.dat