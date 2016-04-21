CC = g++
OP = mmu

CLIST = main.o random.o helper.o page_table.o page_table_entry.o input_handler.o instruction.o \
instruction_type.o pager_factory.o pager.o frame.o frame_table.o options.o simulator.o \
fcfs.o  second_chance.o clock.o clock_virtual.o random_pager.o lru.o nru.o aging.o aging_virtual.o

mmu : $(CLIST)
	$(CC) -o $(OP) $(CLIST)

main.o : main.cpp main.hpp
	$(CC) -c main.cpp

random.o : random.cpp random.hpp
	$(CC) -c random.cpp

helper.o : helper.cpp helper.hpp
	$(CC) -c helper.cpp

page_table.o : page_table.cpp page_table.hpp
	$(CC) -c page_table.cpp

page_table_entry.o : page_table_entry.cpp page_table_entry.hpp
	$(CC) -c page_table_entry.cpp

input_handler.o : input_handler.cpp input_handler.hpp
	$(CC) -c input_handler.cpp

instruction.o : instruction.cpp instruction.hpp
	$(CC) -c instruction.cpp

instruction_type.o : instruction_type.cpp instruction_type.hpp
	$(CC) -c instruction_type.cpp

pager_factory.o : pager_factory.cpp pager_factory.hpp
	$(CC) -c pager_factory.cpp

pager.o : pager.cpp pager.hpp
	$(CC) -c pager.cpp

frame.o : frame.cpp frame.hpp
	$(CC) -c frame.cpp

frame_table.o : frame_table.cpp frame_table.hpp
	$(CC) -c frame_table.cpp

simulator.o : simulator.cpp simulator.hpp
	$(CC) -c simulator.cpp

options.o : options.cpp options.hpp
	$(CC) -c options.cpp

fcfs.o : fcfs.cpp fcfs.hpp
	$(CC) -c fcfs.cpp

second_chance.o : second_chance.cpp second_chance.hpp
	$(CC) -c second_chance.cpp

clock.o : clock.cpp clock.hpp
	$(CC) -c clock.cpp

clock_virtual.o : clock_virtual.cpp clock_virtual.hpp
	$(CC) -c clock_virtual.cpp

random_pager.o : random_pager.cpp random_pager.hpp
	$(CC) -c random_pager.cpp

lru.o : lru.cpp lru.hpp
	$(CC) -c lru.cpp

nru.o : nru.cpp nru.hpp
	$(CC) -c nru.cpp

aging.o : aging.cpp aging.hpp
	$(CC) -c aging.cpp

aging_virtual.o : aging_virtual.cpp aging_virtual.hpp
	$(CC) -c aging_virtual.cpp

clean : 
	-rm $(OP) $(CLIST)
