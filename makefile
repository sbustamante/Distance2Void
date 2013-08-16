CC=gcc
CFLAGS=-g -I. -c

#Principal Program
Halo_Distance:inout.o distance.o halo_distance.o
	gcc inout.o distance.o halo_distance.o -o Halo_Distance.out -lm
	rm -r *.o

edit:
	kate *.c *.h &

clean:
	rm -r *.o *.out *.png *.tmp script.gpl