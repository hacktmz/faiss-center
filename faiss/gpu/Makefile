# Copyright (c) 2015-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the CC-by-NC license found in the
# LICENSE file in the root directory of this source tree.

.SUFFIXES: .cpp .o .cu

include ../makefile.inc






LIBNAME=libgpufaiss

all: test/demo_ivfpq_indexing_gpu.a




INS=1 32 64 128 256 F512 T512 F1024 T1024




.cpp.o:
	$(CC11) -std=c++11 -fPIC -m64 -Wall -g -Wno-sign-compare -O3 -fopenmp \
         -c $< -o $@ $(EXTRAFLAGS) $(CUDACFLAGS)

.cu.o:
	$(NVCC) $(NVCCFLAGS) -g -O3 \
         -c $< -o $@ $(EXTRAFLAGS)


$(LIBNAME).a: $(CPPOBJ) $(CUOBJ)
	ar r $@ $^


test/demo_ivfpq_indexing_gpu.a: test/demo_ivfpq_indexing_gpu.cpp \
	$(LIBNAME).a ../libfaiss.a
	$(NVCC) $(NVCCFLAGS) -o $@ $^ -Xcompiler -fopenmp -lcublas \
	$(BLASLDFLAGSNVCC)

