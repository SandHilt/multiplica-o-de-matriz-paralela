SUBDIRS := $(wildcard omp/matriz/.) $(wildcard mpi/matriz/.) $(wildcard serial/matriz/.)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)