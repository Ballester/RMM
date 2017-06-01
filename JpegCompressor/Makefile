
all:
	g++ cod_pred.cpp
	./a.out lena.raw 512 512 1
	g++ dec_pred.cpp
	./a.out lena.raw 512 512 1

debug:
	g++ -g jo_jpeg.cpp
	gdb ./a.out
