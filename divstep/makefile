poly8:
	gcc -c poly8_divstep.c
	gcc -o poly8_divstep poly8_divstep.o
	rm -rf poly8_divstep.o
	./poly8_divstep

own:
	gcc -c own_divstep.c
	gcc -o own_divstep own_divstep.o
	rm -rf own_divstep.o
	./own_divstep


poly64:
	gcc -c poly64_divstep.c -march=armv8-a+crypto
	gcc -o poly64_divstep poly64_divstep.o
	rm -rf poly64_divstep.o
	./poly64_divstep

poly128:
	gcc -c poly128_divstep.c
	gcc -o poly128_divstep poly128_divstep.o
	rm -rf poly128_divstep.o
	./poly128_divstep

jump_poly64:
	gcc -c jump_poly64divstep.c -march=armv8-a+crypto
	gcc -o jump_poly64divstep jump_poly64divstep.o
	./jump_poly64divstep

jump_poly64x2:
	gcc -c jump_poly64x2divstep.c -march=armv8-a+crypto
	gcc -o jump_poly64x2divstep jump_poly64x2divstep.o
	./jump_poly64x2divstep

clean:
	rm -rf poly8_divstep poly8_divstep.o poly64_divstep poly64_divstep.o poly128_divstep poly128_divstep.o own_divstep own_divstep.o
