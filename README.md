# pongsh

pongsh est un projet personnel en C. Aujourd'hui, le dépôt ne contient
que **libmy** : une bibliothèque statique qui réimplémente un sous-ensemble
de la bibliothèque standard C (chaînes, mémoire, ctype, entrées/sorties,
tableaux de mots) ainsi qu'une réimplémentation de `printf`. L'application
pongsh elle-même n'est pas encore écrite.

## Organisation du dépôt

```
pongsh/
├── include/
│   ├── my.h                    # Tous les prototypes publics (garde MY_H_)
│   ├── my_printf_internal.h    # Header interne de my_printf
│   └── word_array_internal.h   # Header interne du module word_array
├── lib/
│   ├── my/                     # Sources de la bibliothèque
│   │   ├── ctype/              # my_isalpha, my_toupper, ...
│   │   ├── io/                 # my_putchar, my_putstr, my_puterr
│   │   ├── memory/             # my_memset, my_memcpy, my_calloc, ...
│   │   ├── string/             # my_strlen, my_strcat, my_strdup, ...
│   │   └── word_array/         # my_str_to_word_array, my_sort, ...
│   └── my_printf/              # Réimplémentation de my_printf
│       ├── core/               # Boucle principale, émission
│       ├── parse/              # Analyse des drapeaux, largeur, précision
│       ├── render/              # Rendu des nombres (chiffres, préfixes)
│       └── convert/            # Conversions %c, %s, %d, ...
├── tests/                      # Tests criterion : un fichier par fonction
└── Makefile                    # Construit libmy.a et les tests
```

Chaque fichier source porte le nom de la fonction publique qu'il définit :
`lib/my/<module>/my_<fonction>.c`. La liste des fonctions disponibles est
la liste des prototypes de `include/my.h`, qui fait référence.

## Compilation

Le compilateur est `gcc` avec `-Wall -Wextra -Werror -Iinclude` : aucun
avertissement n'est toléré.

| Commande | Effet |
|---|---|
| `make` / `make all` | Compile les sources et crée `libmy.a` avec `ar rc` puis `ranlib` |
| `make clean` | Supprime les fichiers objets |
| `make fclean` | `clean`, puis supprime `libmy.a` et `unit_tests` |
| `make re` | `fclean` puis `all` |
| `make tests_run` | Compile les sources avec les tests et lance `unit_tests` |

La liste des sources est maintenue à la main dans la variable `SRC` du
`Makefile` : ajouter une fonction suppose d'y ajouter son fichier.

## Tests

Les tests utilisent [criterion](https://github.com/Snaipe/Criterion), qui
doit être installé sur la machine. Ils sont compilés par
`make tests_run`, qui lance le binaire `unit_tests` juste après l'avoir
construit ; un résumé du type `Testés: 209 | Validés: 209` s'affiche alors.

Il y a un fichier de test par fonction (`tests/test_<fonction>.c`), et
chaque `Test()` couvre un cas précis :

- cas courants et cas limites (chaînes vides, zéro, bornes) ;
- sécurité NULL : passer `NULL` renvoie `NULL` ou `-1`, sans crash ;
- pour `my_printf`, vérification de la sortie (via `cr_redirect_stdout`)
  et du nombre d'octets écrits.

## Conventions

- Tous les prototypes publics vivent dans `include/my.h` et uniquement
  là ; les fichiers `.c` l'incluent avec `#include "my.h"`.
- Les éventuels helpers internes restent `static` dans leur `.c`, ou
  vivent dans les headers internes (`my_printf_internal.h`,
  `word_array_internal.h`).
- Les fonctions sont NULL-sûres : les erreurs se signalent par la valeur
  de retour (`NULL` ou `-1`), jamais par un crash ni un `exit`.
- Le style est le style EPITECH, compilé en `-Wall -Wextra -Werror`.
- Une nouvelle fonction suppose trois points de contact : le `.c` dans
  le bon module, le prototype dans `include/my.h`, et un fichier
  `tests/test_<fonction>.c`.

## Utilisation

Une fois `make` exécuté, la bibliothèque est `libmy.a` dans le répertoire
racine. Un programme l'utilise en compilant avec `-Iinclude -L. -lmy` :

```sh
gcc mon_programme.c -Iinclude -L. -lmy -o mon_programme
```

Toutes les fonctions gèrent `NULL` en entrée et signalent leurs erreurs
par leur valeur de retour (`NULL` ou `-1`), jamais en interrompant le
programme.

Chaînes de caractères — copie, concaténation, duplication :

```c
char dest[11] = "Hello";

my_strcat(dest, "World");       // dest vaut "HelloWorld"
my_strcmp("abc", "abd");        // renvoie une valeur négative
char *copy = my_strdup("test"); // nouvelle chaîne allouée, NULL si échec
```

Mémoire — allocation et manipulation de zones :

```c
char *buffer = my_calloc(10, sizeof(char)); // zone mise à zéro, NULL si échec

my_memset(buffer, 'a', 3); // buffer commence par "aaa"
```

Tableaux de mots — découpage, tri, affichage, libération :

```c
char **words = my_str_to_word_array("hello world");
// words[0] == "hello", words[1] == "world", words[2] == NULL
my_sort_word_array(words);      // trie le tableau par ordre alphabétique
my_show_word_array(words);      // affiche un mot par ligne
my_free_word_array(words);     // libère chaque mot puis le tableau
```

Sortie formatée — `my_printf` écrit sur la sortie standard et renvoie le
nombre d'octets écrits, ou `-1` en cas d'échec. Il gère les conversions
`%c %s %d %i %u %o %x %X %p` et `%%`, les drapeaux `- 0 + espace #`, une
largeur et une précision numériques ou `*`. Un spécificateur non supporté
est recopié tel quel :

```c
my_printf("%s: %d items\n", "cart", 3); // affiche "cart: 3 items"
my_printf("%+05d\n", 42);               // affiche "+0042"
```
