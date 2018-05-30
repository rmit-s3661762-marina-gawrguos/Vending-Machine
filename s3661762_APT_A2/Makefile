SOURCES=vm.c vm_menu.c vm_options.c vm_stock.c vm_coin.c utility.c
HEADERS=vm.h vm_menu.h vm_options.h vm_stock.h vm_coin.h utility.h vm_system.h
PROGRAM=vm
DEBUG=-g
FLAGS=-ansi -pedantic -Wall $(DEBUG)
OBJECTS=utility.o vm.o vm_coin.o vm_menu.o vm_options.o vm_stock.o

all: $(OBJECTS)
	gcc $(FLAGS) -o $(PROGRAM) $(OBJECTS)

utility.o: utility.c utility.h
	gcc $(FLAGS) -c utility.c

vm.o: vm.c vm.h
	gcc $(FLAGS) -c vm.c

vm_coin.o: vm_coin.c vm_coin.h
	gcc $(FLAGS) -c vm_coin.c

vm_menu.o: vm_menu.c vm_menu.h
	gcc $(FLAGS) -c vm_menu.c

vm_options.o: vm_options.c vm_options.h
	gcc $(FLAGS) -c vm_options.c

vm_stock.o: vm_stock.c vm_stock.h
	gcc $(FLAGS) -c vm_stock.c

clean:
	rm $(PROGRAM) $(OBJECTS)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile