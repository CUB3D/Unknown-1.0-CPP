make=make

clean:
	$(make) -C Unknown\ 1.0++/ clean
	$(make) -C Unknown\ Test/ clean

all:
	$(make) -C Unknown\ 1.0++/
	$(make) -C Unknown\ Test/
