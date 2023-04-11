LLVM_ROOT=../../
LLVM_PASS_LOC=$(LLVM_ROOT)/build/lib/LLVMLab.so
LLVM_PASS=--lab

all: one two

one: one.c $(LLVM_PASS_LOC)
	$(LLVM_ROOT)/build/bin/clang -c -emit-llvm one.c
	$(LLVM_ROOT)/build/bin/opt -enable-new-pm=0 --load=$(LLVM_PASS_LOC) $(LLVM_PASS) < one.bc > oneopt.bc
	$(LLVM_ROOT)/build/bin/llvm-dis oneopt.bc
	$(LLVM_ROOT)/build/bin/llc oneopt.bc
	$(LLVM_ROOT)/build/bin/clang -o one oneopt.s

two: two.c $(LLVM_PASS_LOC)
	$(LLVM_ROOT)/build/bin/clang -c -emit-llvm two.c
	$(LLVM_ROOT)/build/bin/opt -enable-new-pm=0 --load=$(LLVM_PASS_LOC) $(LLVM_PASS) < two.bc > twoopt.bc
	$(LLVM_ROOT)/build/bin/llvm-dis twoopt.bc
	$(LLVM_ROOT)/build/bin/llc twoopt.bc
	$(LLVM_ROOT)/build/bin/clang -o two twoopt.s

clean:
	rm -f *.bc *.ll *.s one two
