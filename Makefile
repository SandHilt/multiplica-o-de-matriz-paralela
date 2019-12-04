SUBDIRS := $(wildcard omp/matriz/.) $(wildcard mpi/matriz/.)\
	$(wildcard serial/matriz/.)

SIZE=100
export SIZE

NUMBER_TESTS=5

america: clear
great: all

again:
	./run.sh $(NUMBER_TESTS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ clean all 

.PHONY: all $(SUBDIRS)

clear:
	rm -rf *.dat *.png