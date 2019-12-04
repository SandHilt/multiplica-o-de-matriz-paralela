SUBDIRS := $(wildcard omp/matriz/.) $(wildcard mpi/matriz/.)\
	$(wildcard serial/matriz/.)

all: clear $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ clean all 

.PHONY: all $(SUBDIRS)

clear:
	rm -rf *.dat