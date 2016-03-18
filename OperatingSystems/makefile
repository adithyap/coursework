scheduler : main.o random.o event.o event_manager.o scheduler_factory.o simulator.o states.o scheduler.o fcfs.o process.o lcfs.o sjf.o rr.o prio.o
	g++ -o scheduler main.o random.o event.o event_manager.o scheduler_factory.o simulator.o states.o scheduler.o fcfs.o process.o lcfs.o sjf.o rr.o prio.o

main.o : main.cpp random.hpp
	g++ -c main.cpp

random.o : random.cpp random.hpp
	g++ -c random.cpp

event.o : event.cpp event.hpp
	g++ -c event.cpp

process.o : process.cpp process.hpp
	g++ -c process.cpp

event_manager.o : event_manager.cpp event_manager.hpp
	g++ -c event_manager.cpp

simulator.o : simulator.cpp simulator.hpp
	g++ -c simulator.cpp

states.o : states.cpp states.hpp
	g++ -c states.cpp

scheduler.o : scheduler.cpp scheduler.hpp
	g++ -c scheduler.cpp

fcfs.o : fcfs.cpp fcfs.hpp
	g++ -c fcfs.cpp

lcfs.o : lcfs.cpp lcfs.hpp
	g++ -c lcfs.cpp

sjf.o : sjf.cpp sjf.hpp
	g++ -c sjf.cpp

scheduler_factory.o : scheduler_factory.cpp scheduler_factory.hpp
	g++ -c scheduler_factory.cpp

rr.o : rr.cpp rr.hpp
	g++ -c rr.cpp

prio.o: prio.cpp prio.hpp
	g++ -c prio.cpp

clean : 
	-rm scheduler main.o random.o event.o event_manager.o scheduler_factory.o simulator.o states.o scheduler.o fcfs.o process.o lcfs.o sjf.o rr.o prio.o
