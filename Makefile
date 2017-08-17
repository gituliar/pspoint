VINCIA = ~/opt/pythia8226/vincia-2.2.00
PYTHIA = ~/opt/pythia8226

pspoint: pspoint.cc
	g++ $< -o $@ \
		$(VINCIA)/lib/libvincia.a \
		$(VINCIA)/lib/libVinciaMG4.a \
		$(VINCIA)/lib/libVinciaMG5.a \
		$(PYTHIA)/lib/libpythia8.a \
		-I $(VINCIA)/include/ \
		-I $(PYTHIA)/include/ \
		-ansi -pedantic -W -Wall -Wshadow -fPIC -ldl
	
