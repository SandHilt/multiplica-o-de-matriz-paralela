SUBDIRS := $(wildcard omp/**/.) $(wildcard mpi/**/.)\
	$(wildcard serial/**/.)

# Para Matriz
SIZE=500
export SIZE

# Para fibonacci
SIZE_F=1000
export SIZE_F

NUMBER_TESTS=2

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
