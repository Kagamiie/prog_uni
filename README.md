# LogPulse

> **Visualisez vos logs Apache en un coup d'œil** — texte, graphique SDL ou page web, au choix.

![C](https://img.shields.io/badge/C-99-blue?logo=c&logoColor=white)
![Apache](https://img.shields.io/badge/Apache-Log%20Parser-red?logo=apache&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey?logo=linux&logoColor=white)

---

## À propos

**LogPulse** est un outil écrit en **C (C99)** qui analyse les fichiers `access.log` d'Apache pour produire des **statistiques mensuelles de connexion**. Il propose trois modes de rendu :

| Mode | Commande | Description |
|------|----------|-------------|
| **Texte** | `-txt` | Affichage dans le terminal, pourcentages par mois |
| **Graphique** | `-gr` | Fenêtre SDL avec histogramme coloré |
| **Web (CGI)** | *(sans argument)* | Page HTML dynamique avec barres CSS |

Idéal pour un déploiement en CGI sur un serveur Apache local, ou pour une consultation rapide en ligne de commande.

---

## Aperçu

### Mode texte (`-txt`)

```
Depuis le 01/Jan/2024 on a enregistre 148320 connexions.
   Janvier :  8.3%
   Fevrier :  6.1%
      Mars :  9.7%
     Avril : 11.2%
       Mai : 10.5%
      Juin :  7.8%
   Juillet :  5.9%
      Aout :  4.2%
 Septembre :  9.1%
   Octobre : 10.8%
  Novembre :  8.6%
  Decembre :  7.8%
```

### Mode graphique (`-gr`)

> Une fenêtre SDL (430×350 px) s'ouvre avec un histogramme en **barres oranges**, les labels des mois en bas, et le résumé en haut. Cliquez pour fermer.

### Mode web (CGI)

> Une page HTML est générée avec des barres CSS positionnées dynamiquement, utilisant le style défini dans `aecrire.html`.

## Installation

```bash
git clone https://github.com/votre-utilisateur/logpulse.git
cd logpulse/src
make
```

Le `Makefile` compile le binaire **et** l'installe automatiquement :
- dans `/usr/lib/cgi-bin/` pour le mode web
- les fichiers HTML dans `/var/www/html/`

Pour une installation complète depuis zéro :

```bash
make clean-install
make
```

---

## Utilisation

```bash
# Mode texte
./versiondynamique -txt

# Mode graphique (fenêtre SDL)
./versiondynamique -gr

# Mode web/CGI (affiche du HTML sur stdout)
./versiondynamique
```

En production, le binaire est appelé automatiquement par Apache via CGI.

---

## Structure du projet

```
logpulse/
├── lib/
│   ├── libgraphique.c     # Bibliothèque graphique maison (SDL)
│   ├── libgraphique.h     # Header de la lib graphique + couleurs
│   └── VERSION            # Journal des versions
├── src/
│   ├── main.c             # Point d'entrée, dispatch des modes
│   ├── data.c             # Parsing du fichier access.log
│   ├── output.c           # Rendu texte, graphique et web
│   ├── stats.h            # Types partagés (Data, constantes)
│   ├── aecrire.html       # Feuille de style CSS pour le mode web
│   └── Makefile           # Compilation + déploiement
└── www/
    ├── index.html
    ├── access.log.big     # (ignoré par git)
    └── ...
```

---

## Architecture

```
access.log (Apache)
       │
       ▼
  [ data.c ]  ──── func_opred()  ──── extract_date()
       │
       ▼
  struct Data  { n_rq, monthly[12], first_day/month/year }
       │
       ├──── -txt  ──►  [ output.c ] versiontexte()   ──► stdout
       ├──── -gr   ──►  [ output.c ] versiongraphique() ──► Fenêtre SDL
       └────  (CGI) ──►  [ output.c ] versionweb()    ──► HTML stdout
```

Le fichier log est lu **ligne par ligne** avec un buffer dynamique (doublement de taille au besoin). Chaque ligne est parsée pour en extraire le mois, incrémenté dans le tableau `monthly[12]`.
<p align="center">
  Fait avec ❤️ en C
</p>
