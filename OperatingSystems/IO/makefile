CC = g++ -g
OP = io

CLIST = main.o helper.o input_handler.o instruction.o scheduler_factory.o scheduler.o event.o \
event_manager.o process.o simulator.o states.o fifo.o sstf.o direction.o scan.o cscan.o fscan.o

io : $(CLIST)
	$(CC) -o $(OP) $(CLIST)

main.o : main.cpp main.hpp
	$(CC) -c main.cpp

helper.o : helper.cpp helper.hpp
	$(CC) -c helper.cpp

instruction.o : instruction.cpp instruction.hpp
	$(CC) -c instruction.cpp

input_handler.o : input_handler.cpp input_handler.hpp
	$(CC) -c input_handler.cpp

scheduler_factory.o : scheduler_factory.cpp scheduler_factory.hpp
	$(CC) -c scheduler_factory.cpp

scheduler.o : scheduler.cpp scheduler.hpp
	$(CC) -c scheduler.cpp

event.o : event.cpp event.hpp
	$(CC) -c event.cpp

event_manager.o : event_manager.cpp event_manager.hpp
	$(CC) -c event_manager.cpp

process.o : process.cpp process.hpp
	$(CC) -c process.cpp

simulator.o : simulator.cpp simulator.hpp
	$(CC) -c simulator.cpp

states.o : states.cpp states.hpp
	$(CC) -c states.cpp

direction.o : direction.cpp direction.hpp
	$(CC) -c direction.cpp

fifo.o : fifo.cpp fifo.hpp
	$(CC) -c fifo.cpp

sstf.o : sstf.cpp sstf.hpp
	$(CC) -c sstf.cpp

scan.o : scan.cpp scan.hpp
	$(CC) -c scan.cpp

cscan.o : cscan.cpp cscan.hpp
	$(CC) -c cscan.cpp

fscan.o : fscan.cpp fscan.hpp
	$(CC) -c fscan.cpp

clean : 
	-rm $(OP) $(CLIST)
