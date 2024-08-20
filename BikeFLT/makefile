BikeFLT:
	gcc -c BikeFLT.c -march=armv8-a+crypto
	gcc -o BikeFLT BikeFLT.o
	./BikeFLT
	rm -rf BikeFLT BikeFLT.o

test:
	gcc -c test.c -march=armv8-a+crypto
	gcc -o test test.o
	./test
	rm -rf test test.o

k_square_poly64LvL1:
	gcc -c k_square_poly64LvL1.c -march=armv8-a+crypto
	gcc -o k_square_poly64LvL1 k_square_poly64LvL1.o -lm
	./k_square_poly64LvL1
	rm -rf k_square_poly64LvL1 k_square_poly64LvL1.o


poly64_karatsuba:
	gcc -c poly64_karatsuba.c -march=armv8-a+crypto
	gcc -o poly64_karatsuba poly64_karatsuba.o
	./poly64_karatsuba
	rm -rf poly64_karatsuba poly64_karatsuba.o
