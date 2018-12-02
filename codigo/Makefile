
BIN_NAME=trab3

CC= gcc
CFLAGS= -Wall -g # -D NDEBUG -O2

# Arquivos de bibliotecas
SRCS=$(wildcard src/*.c)
OBJS=$(patsubst src/%.c,build/%.o,$(SRCS))

# Arquivos de executáveis
MAINS=$(wildcard main/*.c)
EXES=$(patsubst main/%.c,bin/%,$(MAINS))


# Marca as regras de arquivos que não devem ser excluídos
.PRECIOUS: %/  build/%.o


# Target padrão
all: exe
	@#cp -f "./bin/$(BIN_NAME)" "./$(BIN_NAME)"

# Compila todos os executáveis
exe: $(EXES)

# Limpa tuto
clean:
	rm -f ./$(BIN_NAME)
	rm -f -r ./.dep
	rm -f -r ./build
	rm -f -r ./bin


# Compila bibliotecas de src/ para build/
build/%.o: src/%.c
	@ mkdir -p $(dir $@) $(dir .dep/$@)
	$(CC) -o $@  -c $<  $(CFLAGS)
	@ $(CC) -MM -MT $@  $< $(CFLAGS)  > .dep/$@.d

# Compila de main/ para para bin/
bin/%: main/%.c $(OBJS)
	@ mkdir -p $(dir $@) $(dir .dep/$@)
	$(CC) -o $@  -I "./src/" $^  $(CFLAGS)
	@ $(CC) -MM -MT $@  $< $(CFLAGS) -I "./src/"  > .dep/$@.d


# Inclui as listas de dependências
include $(wildcard .dep/**/*)

