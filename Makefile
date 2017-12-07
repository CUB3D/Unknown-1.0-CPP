UnknownTestDir=Unknown\ Test
UnknownDir=Unknown\ 1.0++

all: build

clean:
	$(MAKE) -C $(UnknownDir)/ clean
	$(MAKE) -C $(UnknownTestDir)/ clean

build: 
	$(MAKE) -C $(UnknownDir)/
	$(MAKE) -C $(UnknownTestDir)/

test:
	cd 'Unknown Test' && LD_LIBRARY_PATH=../Output/lib/linux/ ./a.out 2>&1

build-all-test: build test
