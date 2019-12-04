SUBDIRS := $(wildcard omp/matriz/.) $(wildcard mpi/matriz/.)\
	$(wildcard serial/matriz/.)

SIZE=1000
export SIZE

NUMBER_TESTS=30

america: clear
great: all

again:
	./run.sh $(NUMBER_TESTS) $(SIZE)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ clean all 

.PHONY: all $(SUBDIRS)

clear:
	rm -rf *.dat *.png