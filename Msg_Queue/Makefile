cliSRC=client.c comm.c
serSRC=comm.c server.c
cli=client
ser=server
cc=gcc

.PHONY:all
all:$(ser) $(cli)

$(cli):$(cliSRC)
	$(cc) -o $@ $^
$(ser):$(serSRC)
	$(cc) -o $@ $^ -g

.PHONY:clean
clean:
	rm -i $(cli) $(ser)
