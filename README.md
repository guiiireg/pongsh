# PongSH

`pongsh` est un projet d'apprentissage en C visant à construire progressivement un shell Unix basique, en commençant par refaire le socle de la bibliothèque standard (`libmy`, `my_printf`).

Le projet contient actuellement une bibliothèque personnelle qui réimplémente plusieurs fonctions courantes de manipulation de chaînes, d'affichage, de mémoire et de nombres.

## État actuel

Le shell n'est pas encore implémenté.

Fonctionnalités disponibles :

- Fonctions de manipulation de chaînes (`my_strlen`, `my_strcpy`, `my_strcmp`, `my_strcat`, etc.).
- Prédicats et validation de caractères (`my_str_isalpha`, `my_str_isnum`, etc.).
- Affichage de texte, nombres et mémoire (`my_putchar`, `my_putstr`, `my_put_nbr`, `my_showstr`, `my_showmem`).
- Tri de tableaux d'entiers (`my_sort_int_array`).
- Moteur de base de `my_printf` (parcours de format, comptage de caractères, format nul, `%%`).
- Suite complète de tests unitaires avec Criterion (166 tests).

## Architecture du dépôt

- `include/` : En-têtes publics (`my.h`, `my_printf.h`).
- `lib/my/` : Primitives et fonctions utilitaires de `libmy`.
- `lib/my_printf/` : Implémentation modulaire et progressive de `my_printf`.
- `tests/` : Tests unitaires Criterion (`test_my_*.c`).
- `Makefile` : Automatisation de la compilation, des tests et du nettoyage.

## Commandes et Compilation

La compilation est gérée par le `Makefile` racine avec GCC selon des règles strictes (`-Wall -Wextra -Werror`).

### Compiler la bibliothèque

Génère la bibliothèque statique `libmy.a` (incluant `lib/my/` et `lib/my_printf/`) :

```bash
make
```

### Compiler les tests unitaires

Génère l'exécutable `unit_tests` lié avec `libmy.a` et Criterion :

```bash
make unit_tests
```

### Lancer la suite de tests

Compile et exécute automatiquement l'ensemble des tests unitaires Criterion :

```bash
make tests_run
```

### Nettoyage

Supprimer uniquement les fichiers objets (`obj/`) :

```bash
make clean
```

Supprimer tous les fichiers objets, la bibliothèque statique et les exécutables de test :

```bash
make fclean
```

Recompiler entièrement le projet à partir de zéro :

```bash
make re
```

### Analyse mémoire (Valgrind)

Vérifier l'absence de fuites et d'erreurs mémoire sur les tests unitaires :

```bash
valgrind --leak-check=full --error-exitcode=1 ./unit_tests
```

## Roadmap

> Cette roadmap est indicative et pourra évoluer au cours du développement.

### 1. Socle utilitaire (`libmy`)

Fonctions de base pour la manipulation des strings, des nombres, des tableaux et de la mémoire.

- [x] Premières fonctions de manipulation de strings.
- [x] Fonctions d'affichage élémentaires.
- [x] Premières fonctions de conversion.
- [ ] Ajouter les fonctions nécessaires aux futures commands.
- [ ] Stabiliser l'API de la bibliothèque.
- [ ] Ajouter des tests unitaires.

### 2. Formatage (`my_printf`)

- [x] **Niveau 1** - Primitives de sortie : `my_putchar`, `my_strlen` et `my_putstr`
- [x] **Niveau 2** - Analyse du format, comptage des caractères, gestion d'un format `NULL` et échappement `%%`.
- [ ] **Niveau 3** - Arguments variadiques avec `<stdarg.h>`, conversions `%c` et `%s`.
- [ ] **Niveau 4** - Entiers décimaux signés et non signés : `%d`, `%i` et `%s`.
- [ ] **Niveau 5** - Conversions octale et haxadécimale : `%o`, `%x` et `%X`
- [ ] **Niveau 6** - Pointeurs avec `%p`, conversions inconnues et propagation des erreurs d'écriture.
- [ ] **Niveau 7** - Optimisation des écritures par blocs.
- [ ] **Niveau 8** - Largeur, précision et indicateurs de format : `-`, `0`, `+`, espace et `#`.
- [ ] Ajouter des tests unitaires et comparer les résultats avec `printf`.

### 3. Commands Unix

Réimplémentation progressive d'un sous-ensemble de commands courantes.

- [ ] `echo`
- [ ] `pwd`
- [ ] `cat`
- [ ] `ls`
- [ ] `grep`
- [ ] Définir les options prises en charge pour chaque commande.
- [ ] Gérer les erreurs, permissions et code de sortie.
- [ ] Ajouter des tests d'intégration.

> L'objectif n'est pas nécessairement de reproduire toutes les options des implémentations GNU, mais de définir et documenter un paramètre précis pour chaque commande.

### 4. Shell Unix

- [ ] Créer une boucle interactive REPL.
- [ ] Lire et éditer une ligne de commande.
- [ ] Construire le lexer.
- [ ] Construire le parser.
- [ ] Exécuter des programmes externes.
- [ ] Implémenter les builtins.
- [ ] Gérer les variables d'environnement.
- [ ] Gérer les codes de retour.
- [ ] Gérer les redirections.
- [ ] Gérer les signaux.
- [ ] Ajouter des tests d'intégration.

### 5. Qualité et documentation

- [ ] Compiler sans avertissement.
- [ ] Vérifier les fuites et erreurs mémoire.
- [ ] Documenter l'architecture.
- [ ] Documenter les différences avec les outils de référence.
- [ ] Automatiser les tests.
- [ ] Ajouter une intégration continue.
