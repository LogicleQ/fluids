build:
	@cd src; \
		g++ -O3 -o ../fluids -lSDL3 *.cpp
