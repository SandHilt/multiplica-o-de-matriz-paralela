SUBDIRS := $(wildcard omp/matriz/.) $(wildcard mpi/matriz/.)\
	$(wildcard serial/matriz/.)

SIZE=67
export SIZE

NUMBER_TESTS=30

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ clean all 

.PHONY: all $(SUBDIRS)

america: clean
great: all

again:
	./run.sh $(NUMBER_TESTS) $(SIZE)


clean:
	rm -rf *.dat *.png