nclude <stdio.h>
#include <stdlib.h>
#include <string.h>

// structura de baza
typedef struct {
    char denumire[50];
    char adresa[100];
    char telefon[20];
    char categoria[30];
    int  numar_locuri;
    char specializarea[50];
} Restaurant;

// variabile globale
Restaurant *v = NULL;
int n = 0; // numarul de elemente

// ================== FUNCTII UTILE ==================

void curata_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void citire_linie(char *s, int dim) { // char *s este  ponterul unde se va salva textul tastat de la tastatura iar dim insemn arimea maxima de careactere inregistrarate
    if (fgets(s, dim, stdin)) {       // umbla pe line si scote entreul ca se primesca un rind frumos   
        s[strcspn(s, "\n")] = '\0';
    }
}

// verifica daca un sir contine DOAR cifre (0-9)
int este_numar(const char *s) {
    if (s[0] == '\0') return 0; // sir gol => nu e numar
    for (int i = 0; s[i]; i++) {   // contorul care face ca unde trebue sa se pun cifre se puna cifre
        if (s[i] < '0' || s[i] > '9')    // nr de locuri  etc
            return 0;
    }
    return 1;
}

// citeste un numar intreg pozitiv (>0) dintr-o linie, cu validare
int citire_int_pozitiv(const char *mesaj) {
    char buf[32];
    int val;
    while (1) {
        printf("%s", mesaj);
        citire_linie(buf, 32);

        if (!este_numar(buf)) {
            printf("Eroare: trebuie introdus un numar (doar cifre)!\n");
            continue;
        }

        val = atoi(buf);
        if (val <= 0) {
            printf("Eroare: numarul trebuie sa fie > 0!\n");
            continue;
        }

        return val;
    }
}

// ================== 1. ALOCARE DINAMICA ==================

void alocare() {
    int nou;
    printf("Numarul de restaurante: ");
    if (scanf("%d", &nou) != 1 || nou <= 0) {
        printf("Valoare invalida.\n");
        curata_buffer();
        return;
    }
    curata_buffer();

    free(v);
    v = (Restaurant*)malloc(nou * sizeof(Restaurant));
    if (!v) {
        printf("Eroare la alocare.\n");
        n = 0;
        return;
    }
    n = nou;
    printf("Memorie alocata pentru %d restaurante.\n", n);
}

// ================== 2. INTRODUCERE ELEMENTE ==================

void introducere() {
    if (!v || n == 0) {
        printf("Mai intai aloca memoria (optiunea 1).\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\nRestaurant %d:\n", i + 1);

        printf("Denumire: ");
        citire_linie(v[i].denumire, 50);

        printf("Adresa: ");
        citire_linie(v[i].adresa, 100);

        // Telefon – validare doar cifre
        do {
            printf("Telefon (doar cifre): ");
            citire_linie(v[i].telefon, 20);

            if (!este_numar(v[i].telefon)) {
                printf("Eroare: telefonul trebuie sa contina DOAR cifre!\n");
            }
        } while (!este_numar(v[i].telefon));

        printf("Categoria: ");
        citire_linie(v[i].categoria, 30);

        // Numar locuri – validare numar intreg pozitiv
        v[i].numar_locuri = citire_int_pozitiv("Numar locuri: ");

        printf("Specializarea: ");
        citire_linie(v[i].specializarea, 50);
    }
}

// ================== AFISARE UN ELEMENT ==================

void afisare_unu(Restaurant *r, int index) {
    printf("\n[%d]\n", index + 1);
    printf("  Denumire      : %s\n", r->denumire);
    printf("  Adresa        : %s\n", r->adresa);
    printf("  Telefon       : %s\n", r->telefon);
    printf("  Categoria     : %s\n", r->categoria);
    printf("  Numar locuri  : %d\n", r->numar_locuri);
    printf("  Specializarea : %s\n", r->specializarea);
}

// ================== 3. CAUTARE DUPA DENUMIRE ==================

void cautare() {
    if (!v || n == 0) {
        printf("Nu exista date.\n");
        return;
    }
    char nume[50];
    printf("Denumirea cautata: ");
    citire_linie(nume, 50);
    int gasit = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(v[i].denumire, nume) == 0) {
            afisare_unu(&v[i], i);
            gasit = 1;
        }
    }
    if (!gasit) printf("Nu s-a gasit restaurantul.\n");
}

// ================== 4. SORTARE DUPA DENUMIRE ==================

void sortare() {
    if (!v || n < 2) {
        printf("Nu sunt suficiente elemente pentru sortare.\n");
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(v[i].denumire, v[j].denumire) > 0) {
                Restaurant aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    printf("Tabloul a fost sortat dupa denumire.\n");
}

// ================== 5. REDACTARE ELEMENT ==================

void redactare() {
    if (!v || n == 0) {
        printf("Nu exista date.\n");
        return;
    }
    int idx;
    printf("Numarul elementului de modificat (1..%d): ", n);
    if (scanf("%d", &idx) != 1) {
        printf("Valoare invalida.\n");
        curata_buffer();
        return;
    }
    curata_buffer();
    if (idx < 1 || idx > n) {
        printf("Index in afara intervalului.\n");
        return;
    }
    idx--;

    printf("Date noi pentru elementul %d:\n", idx + 1);

    printf("Denumire: ");
    citire_linie(v[idx].denumire, 50);

    printf("Adresa: ");
    citire_linie(v[idx].adresa, 100);

    // Telefon – validare doar cifre
    do {
        printf("Telefon (doar cifre): ");
        citire_linie(v[idx].telefon, 20);

        if (!este_numar(v[idx].telefon)) {
            printf("Eroare: telefonul trebuie sa contina DOAR cifre!\n");
        }
    } while (!este_numar(v[idx].telefon));

    printf("Categoria: ");
    citire_linie(v[idx].categoria, 30);

    // Numar locuri – validare
    v[idx].numar_locuri = citire_int_pozitiv("Numar locuri: ");

    printf("Specializarea: ");
    citire_linie(v[idx].specializarea, 50);
}

// ================== 6. ADAUGARE LA SFARSIT ==================

void adaugare_sfarsit() {
    int nou = n + 1;
    Restaurant *p = (Restaurant*)realloc(v, nou * sizeof(Restaurant));
    if (!p) {
        printf("Eroare la realocare.\n");
        return;
    }
    v = p;
    n = nou;
    int i = n - 1;

    printf("Date pentru noul restaurant (pozitia %d):\n", n);

    printf("Denumire: ");
    citire_linie(v[i].denumire, 50);

    printf("Adresa: ");
    citire_linie(v[i].adresa, 100);

    // Telefon – validare doar cifre
    do {
        printf("Telefon (doar cifre): ");
        citire_linie(v[i].telefon, 20);

        if (!este_numar(v[i].telefon)) {
            printf("Eroare: telefonul trebuie sa contina DOAR cifre!\n");
        }
    } while (!este_numar(v[i].telefon));

    printf("Categoria: ");
    citire_linie(v[i].categoria, 30);

    // Numar locuri – validare
    v[i].numar_locuri = citire_int_pozitiv("Numar locuri: ");

    printf("Specializarea: ");
    citire_linie(v[i].specializarea, 50);
}

// ================== 7. ELIMINARE ELEMENT ==================

void eliminare() {
    if (!v || n == 0) {
        printf("Nu exista date.\n");
        return;
    }
    int idx;
    printf("Numarul elementului de eliminat (1..%d): ", n);
    if (scanf("%d", &idx) != 1) {
        printf("Valoare invalida.\n");
        curata_buffer();
        return;
    }
    curata_buffer();
    if (idx < 1 || idx > n) {
        printf("Index in afara intervalului.\n");
        return;
    }
    idx--;
    for (int i = idx; i < n - 1; i++) {
        v[i] = v[i + 1];
    }
    n--;
    if (n == 0) {
        free(v);
        v = NULL;
    } else {
        Restaurant *p = (Restaurant*)realloc(v, n * sizeof(Restaurant));
        if (p) v = p; // daca nu reuseste, ramanem cu vechea zona
    }
    printf("Element eliminat.\n");
}

// ================== 8. INSERARE ELEMENT ==================

void inserare() {
    if (!v || n == 0) {
        printf("Nu exista date, folosesc inserarea ca adaugare la sfarsit.\n");
        adaugare_sfarsit();
        return;
    }
    int pos;
    printf("Pozitia unde se insereaza (1..%d): ", n + 1);
    if (scanf("%d", &pos) != 1) {
        printf("Valoare invalida.\n");
        curata_buffer();
        return;
    }
    curata_buffer();
    if (pos < 1 || pos > n + 1) {
        printf("Pozitie invalida.\n");
        return;
    }
    int nou = n + 1;
    Restaurant *p = (Restaurant*)realloc(v, nou * sizeof(Restaurant));
    if (!p) {
        printf("Eroare la realocare.\n");
        return;
    }
    v = p;
    // mutam la dreapta de la pos-1
    for (int i = nou - 1; i > pos - 1; i--) {
        v[i] = v[i - 1];
    }
    n = nou;

    int idx = pos - 1;

    printf("Date pentru noul restaurant la pozitia %d:\n", pos);

    printf("Denumire: ");
    citire_linie(v[idx].denumire, 50);

    printf("Adresa: ");
    citire_linie(v[idx].adresa, 100);

    // Telefon – validare doar cifre
    do {
        printf("Telefon (doar cifre): ");
        citire_linie(v[idx].telefon, 20);

        if (!este_numar(v[idx].telefon)) {
            printf("Eroare: telefonul trebuie sa contina DOAR cifre!\n");
        }
    } while (!este_numar(v[idx].telefon));

    printf("Categoria: ");
    citire_linie(v[idx].categoria, 30);

    // Numar locuri – validare
    v[idx].numar_locuri = citire_int_pozitiv("Numar locuri: ");

    printf("Specializarea: ");
    citire_linie(v[idx].specializarea, 50);
}

// ================== 9. SALVARE IN FISIER ==================

void salvare_fisier() {
    if (!v || n == 0) {
        printf("Nu exista date de salvat.\n");
        return;
    }
    FILE *f = fopen("restaurante.txt", "w");
    if (!f) {
        printf("Nu pot deschide fisierul.\n");
        return;
    }
    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s\n", v[i].denumire);
        fprintf(f, "%s\n", v[i].adresa);
        fprintf(f, "%s\n", v[i].telefon);
        fprintf(f, "%s\n", v[i].categoria);
        fprintf(f, "%d\n", v[i].numar_locuri);
        fprintf(f, "%s\n", v[i].specializarea);
    }
    fclose(f);
    printf("Date salvate in fisierul restaurante.txt.\n");
}

// ================== 10. CITIRE DIN FISIER ==================

void citire_fisier() {
    FILE *f = fopen("restaurante.txt", "r");
    if (!f) {
        printf("Nu pot deschide fisierul (poate nu exista).\n");
        return;
    }
    char linie[256];
    if (!fgets(linie, sizeof(linie), f)) {
        printf("Fisier gol.\n");
        fclose(f);
        return;
    }
    int nou = atoi(linie);
    if (nou <= 0) {
        printf("Numar invalid in fisier.\n");
        fclose(f);
        return;
    }
    Restaurant *p = (Restaurant*)malloc(nou * sizeof(Restaurant));
    if (!p) {
        printf("Eroare la alocare.\n");
        fclose(f);
        return;
    }
    for (int i = 0; i < nou; i++) {
        if (!fgets(p[i].denumire, 50, f)) break;
        p[i].denumire[strcspn(p[i].denumire, "\n")] = '\0';

        if (!fgets(p[i].adresa, 100, f)) break;
        p[i].adresa[strcspn(p[i].adresa, "\n")] = '\0';

        if (!fgets(p[i].telefon, 20, f)) break;
        p[i].telefon[strcspn(p[i].telefon, "\n")] = '\0';

        if (!fgets(p[i].categoria, 30, f)) break;
        p[i].categoria[strcspn(p[i].categoria, "\n")] = '\0';

        if (!fgets(linie, sizeof(linie), f)) break;
        p[i].numar_locuri = atoi(linie);

        if (!fgets(p[i].specializarea, 50, f)) break;
        p[i].specializarea[strcspn(p[i].specializarea, "\n")] = '\0';
    }
    fclose(f);
    free(v);
    v = p;
    n = nou;
    printf("Date citite din fisier pentru %d restaurante.\n", n);
}

// ================== 11. AFISARE TOATE ELEMENTELE ==================

void afisare_toate() {
    if (!v || n == 0) {
        printf("Nu exista date.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        afisare_unu(&v[i], i);
    }
}

// ================== 12. ELIBERARE MEMORIE ==================

void eliberare() {
    free(v);
    v = NULL;
    n = 0;
    printf("Memorie eliberata.\n");
}

// ================== MAIN ==================

int main() {
    int opt;
    do {
        printf("\n===== MENIU =====\n");
        printf("1. Alocare memorie\n");
        printf("2. Introducere elemente\n");
        printf("3. Cautare element\n");
        printf("4. Sortare tablou\n");
        printf("5. Redactare element\n");
        printf("6. Adaugare element la sfarsit\n");
        printf("7. Eliminare element\n");
        printf("8. Inserare element nou\n");
        printf("9. Salvare in fisier\n");
        printf("10. Citire din fisier\n");
        printf("11. Afisare elemente\n");
        printf("12. Eliberare memorie\n");
        printf("0. Iesire\n");
        printf("Optiune: ");

        if (scanf("%d", &opt) != 1) {
            printf("Optiune invalida.\n");
            curata_buffer();
            continue;
        }
        curata_buffer();

        switch (opt) {
            case 1:  alocare();          break;
            case 2:  introducere();      break;
            case 3:  cautare();          break;
            case 4:  sortare();          break;
            case 5:  redactare();        break;
            case 6:  adaugare_sfarsit(); break;
            case 7:  eliminare();        break;
            case 8:  inserare();         break;
            case 9:  salvare_fisier();   break;
            case 10: citire_fisier();    break;
            case 11: afisare_toate();    break;
            case 12: eliberare();        break;
            case 0:  printf("La revedere!\n"); break;
            default: printf("Optiune inexistenta.\n");
        }
    } while (opt != 0);

    eliberare(); // sigur eliberam la final
    return 0;
}