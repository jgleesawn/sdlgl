all:
	cd game; make
	cd generator; make

clean:
	cd game; make clean
	cd generator; make clean
