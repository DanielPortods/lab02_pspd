CFLAGS=-Wall $(shell pkg-config --cflags glib-2.0 rdkafka)
LDLIBS=$(shell pkg-config --libs glib-2.0 rdkafka)

ALL: producer consumer

producer:
	gcc $(CFLAGS) $(LDLIBS) producer.c -o producer

consumer:
	gcc $(CFLAGS) $(LDLIBS) consumer.c -o consumer