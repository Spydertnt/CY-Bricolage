CC=gcc

all: exec

main.o: main.c main.h
	$(CC) -c $< -o $@

functions_main.o: functions_main.c main.h
	$(CC) -c $< -o $@

functions_management.o: functions_management.c main.h
	$(CC) -c $< -o $@

functions_purchase.o: functions_purchase.c main.h
	$(CC) -c $< -o $@

management.o: management.c main.h
	$(CC) -c $< -o $@

purchase.o: purchase.c main.h
	$(CC) -c $< -o $@

exec: main.o functions_main.o functions_management.o functions_purchase.o management.o purchase.o
	$(CC) $^ -o $@

clean:
	rm -f *.o
	rm exec
