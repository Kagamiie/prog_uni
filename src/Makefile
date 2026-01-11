CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIB_DIR = ../lib
CFLAGS += -I$(LIB_DIR)
LDFLAGS = -lSDL -lSDL_ttf -lm
TARGET = versiondynamique
SOURCES = main.c data.c output.c $(LIB_DIR)/libgraphique.c

CGIDIR = /usr/lib/cgi-bin/
LOGDIR = /var/log/apache2/
WWWDIR = /var/www/
HTMLDIR = $(WWWDIR)/html/

# par défaut
all: clean $(TARGET) install

# Compile programme
$(TARGET): $(SOURCES) stats.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# Installe
install: install-html install-cgi
	@sudo chmod a+rx $(LOGDIR)
	@sudo chmod a+r $(LOGDIR)/access.log

install-cgi:
	sudo cp aecrire.html $(TARGET) ../www/codescompiles/ 
	@cd ../www/codescompiles/ ; \
	sudo cp aecrire.html $(TARGET) \
	     $(CGIDIR) ; \
	cd ../../src/  # Retour au dossier src
	@echo "Installation du programme :"
	sudo cp $(TARGET) $(CGIDIR)

install-html:
	@echo "Copie des fichiers aux bons emplacements"
	@sudo tar xf ../www/www.tar -C /
	@echo "Copie d'un fichier de log de taille conséquente"
	@sudo cp ../www/access.log.big $(LOGDIR)/access.log

clean:
	rm -f $(TARGET) *.o
	rm -f ../www/codescompiles/*

clean-install: clean
	@sudo rm -rf /var/www/*
	@sudo mkdir $(HTMLDIR)
	@sudo cp ../www/index.html $(HTMLDIR)
	@sudo rm -rf $(CGIDIR)/*

.PHONY: all install install-cgi install-html clean clean-install