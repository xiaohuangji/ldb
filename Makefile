CC=/usr/local/Cellar/gcc47/4.7.3/bin/g++-4.7

ldb_server : main.o  lconfig.o ldb.o lnet.o lconfig.o lcommand.o linker.o linkerManager.o llog.o levent.o
	${CC} -o ldb_server main.o  ldb.o lnet.o lconfig.o lcommand.o linker.o linkerManager.o llog.o levent.o  /usr/lib/libleveldb.a

main.o : main.cpp lnet.h levent.h lconfig.h
	${CC} -c main.cpp lnet.h levent.h llog.h
    
lprotocol.o : lprotocol.h
	${CC} -c lprotocol.h
    
server.o : server.h
	${CC} -c server.h

llog.o : llog.cpp llog.h
	${CC} -c llog.cpp llog.h
    
ldb.o : ldb.cpp ldb.h
	${CC} -c ldb.cpp ldb.h

levent.o : levent.cpp levent.h llog.h linkerManager.h
	${CC} -c levent.cpp levent.h llog.h linkerManager.h

lnet.o : lnet.cpp lnet.h llog.h
	${CC} -c lnet.cpp lnet.h llog.h

lconfig.o : lconfig.cpp lconfig.h server.h
	${CC} -c lconfig.cpp lconfig.h server.h
    
lcommand.o : lcommand.cpp lcommand.h lprotocol.h ldb.h
	${CC} -c lcommand.cpp lcommand.h lprotocol.h ldb.h
    
linker.o: linker.cpp linker.h lprotocol.h lcommand.h ldb.h llog.h server.h lnet.h
	${CC} -c linker.cpp linker.h lprotocol.h lcommand.h ldb.h llog.h server.h lnet.h
    
linkerManager.o : linkerManager.cpp linkerManager.h linker.h llog.h
	${CC} -c linkerManager.cpp linkerManager.h linker.h llog.h

clean : 
	rm -rf *.o *.gch
    


