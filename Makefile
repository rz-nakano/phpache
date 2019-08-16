DST=/usr/local/bin/
BIN=phpache
SRC=phpache.c

all: $(BIN)

$(BIN): $(SRC)
	$(CC) -o $@ $^

install: $(BIN)
	install -o apache -g apache -m 6555 $(BIN) $(DST)

clean:
	$(RM) $(BIN)
