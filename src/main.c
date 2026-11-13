#include <stdio.h>
#include <string.h>

#define TAILLE_ENTETE 0x150   // CHANGÉ : 300 -> 0x150 (le tableau était trop petit)
#define ADRESSE_TITRE 0x134   // CHANGÉ : 308 écrit en hexa, comme dans Pan Docs

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <fichier.rom>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("Erreur ouverture fichier");
        return 1;
    }

    unsigned char buffer[TAILLE_ENTETE];
    size_t lus = fread(buffer, 1, TAILLE_ENTETE, f);
    fclose(f);

    if (lus < TAILLE_ENTETE) {   // AJOUTÉ : vérifie que le fichier est assez grand
        printf("Erreur : fichier trop petit (%zu octets lus)\n", lus);
        return 1;
    }

    char title[16];
    memcpy(title, &buffer[ADRESSE_TITRE], 15);
    title[15] = '\0';

    if (strlen(title) > 0) {     // AJOUTÉ : évite un pointeur hors du tableau si titre vide
        char *last = title + strlen(title) - 1;
        while (last > title && *last == ' ') {
            *last = '\0';
            last--;
        }
    }

    printf("Titre de la ROM : %s\n", title);
    return 0;
}
