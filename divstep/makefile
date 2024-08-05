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
	gcc -c poly64_divstep.c
	gcc -o poly64_divstep poly64_divstep.o
	rm -rf poly64_divstep.o
	./poly64_divstep

poly128:
	gcc -c poly128_divstep.c
	gcc -o poly128_divstep poly128_divstep.o
	rm -rf poly128_divstep.o
	./poly128_divstep

poly64_jump:
	gcc -c poly64_jumpdivstep.c
	gcc -o poly64_jumpdivstep poly64_jumpdivstep.o
	rm -rf poly64_jumpdivstep.o
	./poly64_jumpdivstep


clean:
	rm -rf poly8_divstep poly8_divstep.o poly64_divstep poly64_divstep.o poly128_divstep poly128_divstep.o own_divstep own_divstep.o
