CC=gcc
CFLAGS=-g #-DPTH

all : counter_test list_test hash_test hash_scale

spin.o : spin.c
	$(CC) $(CFLAGS) -c -fpic spin.c

list.o : list.c
	$(CC) $(CFLAGS) -c -fpic list.c

hash.o : hash.c
	$(CC) $(CFLAGS) -c -fpic hash.c

counter.o : counter.c
	$(CC) $(CFLAGS) -c -fpic counter.c

libspin.so: spin.o
	$(CC) $(CFLAGS) -shared -o $@ $<

libhash.so : hash.o
	$(CC) $(CFLAGS) -shared -o $@ $<

libcounter.so : counter.o
	$(CC) $(CFLAGS) -shared -o $@ $<

liblist.so : list.o
	$(CC) $(CFLAGS) -shared -o $@ $<

counter_test : counter_test.o libspin.so liblist.so libhash.so libcounter.so
	$(CC) $(CFLAGS) $< -o $@ -lhash -llist -lcounter -lspin -L. -lpthread

list_test : list_test.o libspin.so liblist.so libhash.so libcounter.so
	$(CC) $(CFLAGS) $< -o $@ -lhash -llist -lcounter -lspin -L. -lpthread

hash_test : hash_test.o libspin.so liblist.so libhash.so libcounter.so
	$(CC) $(CFLAGS) $< -o $@ -lhash -llist -lcounter -lspin -L. -lpthread

hash_scale : hash_scale.o libspin.so liblist.so libhash.so libcounter.so
	$(CC) $(CFLAGS) $< -o $@ -lhash -llist -lcounter -lspin -L. -lpthread


#clean :
#	rm -rf *.o testCounter testList testHash *.so
