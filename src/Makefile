# Nom de l'exécutable
TARGET = programme

# Fichiers sources
SRC = main.c version.c

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Règle par défaut : compiler tout
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Supprimer l'exécutable et les fichiers objets
clean:
	rm -f $(TARGET) *.o
