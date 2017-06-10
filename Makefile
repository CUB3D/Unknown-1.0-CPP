UnknownTestDir=Unknown\ Test
UnknownDir=Unknown\ 1.0++

all: build

clean:
	$(MAKE) -C $(UnknownDir)/ clean
	$(MAKE) -C $(UnknownTestDir)/ clean

build: 
	$(MAKE) -C $(UnknownDir)/
	$(MAKE) -C $(UnknownTestDir)/
