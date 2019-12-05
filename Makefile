SUBDIRS := $(wildcard omp/**/.) $(wildcard mpi/**/.)\
	$(wildcard serial/**/.)

SIZE=1000
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
