//Nama : Saul Sayers
//NIM  : 13520094
//Kelas: K01 Stima
//Tucil 1 STIMA - Word Search Puzzle Solver

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "boolean.h"

typedef struct {
    char contents[50][50];
    int rowEff; 
    int colEff; 
} Matrix;

typedef struct {
    char contents[50][50];
    int Neff;
} Keywords; 

/* *** Selektor *** */
#define ROWS(M) (M).rowEff
#define COLS(M) (M).colEff
#define ELMT(M, i, j) (M).contents[(i)][(j)]
#define NEFF(K) (K).Neff
#define ELMTK(K,i) (K).contents[(i)]

void displayMatrix(Matrix m){
    int i, j;
	for (i = 0; i < ROWS(m); i++){
		for (j = 0; j < COLS(m); j++){
			if (j==0) {
                printf("%c", ELMT(m,i,j));
            }
            else {
                printf(" %c", ELMT(m,i,j));
            }
		}
        if (i != ROWS(m) -1) {
            printf("\n");
        }
	}
}

void readinput(Matrix *crossword, Matrix *hasil, Keywords *keys){
    //Reset crossword dan daftar Keywords
    ROWS(*crossword) = 0;
    COLS(*crossword) = 0;
    NEFF(*keys) = 0;
    ROWS(*hasil) = 0;
    COLS(*hasil) = 0;
    FILE *tape; 

    //bagian input nama file hingga benar
    printf("Silahkan input nama file: ");
    char namafile[70] ;
    fflush(stdin); //agar tidak ada error bug di input sebelumnya
    gets(namafile);
    char direktori[80];
    strcpy(direktori, "../test/");
    strcat(direktori, namafile);
    tape = fopen(direktori, "r");
    while (tape == NULL)
    {
        printf("Nama file tidak ditemukan\nSilahkan input ulang nama file: ");
        strcpy(direktori, "../test/");
        gets(namafile);
        strcat(direktori, namafile);
        tape = fopen(direktori, "r");
    }

    //bagian konversi isi file ke matrix crossword
    printf("Word Search Puzzle-nya adalah: \n");
    char c = fgetc(tape);
    char csebelum = c;
    int baris = 0, kolom = 0; 
    while ((c != '\n') || (csebelum != '\n')){
        putchar(c);
        if (c == '\n') {
            ROWS(*crossword) ++;
            baris++;
            COLS(*crossword) = kolom;
            kolom = 0;
        }
        if (c != ' ' && c != '\n') {
            ELMT(*crossword,baris,kolom) = c;
            kolom++;
        }
        csebelum = c;
        c = fgetc(tape);
    }
    //printf("Banyaknya baris puzzle adalah %d\n", ROWS(*crossword));
    //printf("Banyaknya kolom puzzle adalah %d\n\n", COLS(*crossword));

    //bagian konversi isi file ke keywords 
    //printf("\nDaftar keywordsnya adalah: \n");
    char line[100];
    while (fgets(line, sizeof(line), tape)){
        //printf("%s", line);
        strcpy(ELMTK(*keys,NEFF(*keys)), line);
        NEFF(*keys) ++; 
    }
    //printf("\nBanyaknya keywords adalah %d\n\n", NEFF(*keys));

    //bagian menghapus newline dari tiap keywords
    int i,j;
    for (i=0; i<NEFF(*keys)-1; i++){
        ELMTK(*keys,i)[strlen(ELMTK(*keys,i))-1] = '\0';
    }

    //INISIALISASI MATRIKS HASIL BUAT PERCETAKAN
    ROWS(*hasil) = ROWS(*crossword);
    COLS(*hasil) = COLS(*crossword);
    for (i=0; i<ROWS(*hasil);i++){
        for (j=0; j<COLS(*hasil); j++) {
            ELMT(*hasil, i,j) = '-' ;
        }
    }

    //bagian menutup tape
    fclose(tape);

    //BAGIAN TEST MATRIX
    //printf("%d %d",ROWS(crossword), COLS(crossword));
    /*displayMatrix(crossword);
    printf("\n");
    displayMatrix(hasil);

    //BAGIAN TEST KEYWORDS
    for (i=0; i<NEFF(keys); i++){
        printf("\n%s %d ", ELMTK(keys,i), strlen(ELMTK(keys,i)));
    }
    printf("\n");*/
}

void checkright(int a, int i, int j, int *perbandingan, Matrix crossword, Matrix hasil, Keywords keys, boolean *ketemu){
    int panjang = strlen(ELMTK(keys,a));
    if (!(*ketemu) && (j<COLS(crossword) - panjang + 1)){
        boolean betul = true;
        int k = 1;
        while (betul && k < panjang ){
            if (ELMT(crossword,i,j+1) != ELMT(keys,a,k)){
                betul = false;
            }
            k++;
            j++;
            (*perbandingan) ++ ; 
        }
        if (betul) {
            j = j - panjang + 1;
            int bebas ; 
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i,j+bebas) = ELMT(keys,a,bebas); 
            }
            *ketemu = true;
            printf("%s\n", ELMTK(keys,a)); 
            displayMatrix(hasil); 
            printf("\n");
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i,j+bebas) = '-'; 
            }
        }
    }
}

void checkdown(int a, int i, int j, int *perbandingan, Matrix crossword, Matrix hasil, Keywords keys, boolean *ketemu){
    int panjang = strlen(ELMTK(keys,a));
    if (!(*ketemu) && (i < ROWS(crossword) - panjang + 1)){
        boolean betul = true;
        int k = 1;
        while (betul && k < panjang ){
            if (ELMT(crossword,i+1,j) != ELMT(keys,a,k)){
                betul = false;
            }
            k++;
            i++;
            (*perbandingan) ++ ; 
        }
        if (betul) {
            i = i - panjang + 1;
            int bebas ; 
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i+bebas,j) = ELMT(keys,a,bebas); 
            }
            *ketemu = true;
            printf("%s\n", ELMTK(keys,a)); 
            displayMatrix(hasil); 
            printf("\n");
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i+bebas,j) = '-'; 
            }
        }
    }
}

void checkleft(int a, int i, int j, int *perbandingan, Matrix crossword, Matrix hasil, Keywords keys, boolean *ketemu){
    int panjang = strlen(ELMTK(keys,a));
    if (!(*ketemu) && (j>panjang -2)){
        boolean betul = true;
        int k = 1;
        while (betul && k < panjang ){
            if (ELMT(crossword,i,j-1) != ELMT(keys,a,k)){
                betul = false;
            }
            k++;
            j--;
            (*perbandingan) ++ ; 
        }
        if (betul) {
            j = j + panjang - 1;
            int bebas ; 
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i,j-bebas) = ELMT(keys,a,bebas); 
            }
            *ketemu = true;
            printf("%s\n", ELMTK(keys,a)); 
            displayMatrix(hasil); 
            printf("\n");
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i,j-bebas) = '-'; 
            }
        }
    }
}

void checkup(int a, int i, int j, int *perbandingan, Matrix crossword, Matrix hasil, Keywords keys, boolean *ketemu){
    int panjang = strlen(ELMTK(keys,a));
    if (!(*ketemu) && (i>panjang -2)){
        boolean betul = true;
        int k = 1;
        while (betul && k < panjang ){
            if (ELMT(crossword,i-1,j) != ELMT(keys,a,k)){
                betul = false;
            }
            k++;
            i--;
            (*perbandingan) ++ ; 
        }
        if (betul) {
            i = i + panjang - 1;
            int bebas ; 
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i-bebas,j) = ELMT(keys,a,bebas); 
            }
            *ketemu = true;
            printf("%s\n", ELMTK(keys,a)); 
            displayMatrix(hasil); 
            printf("\n");
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i-bebas,j) = '-'; 
            }
        }
    }
}

void checkdownright(int a, int i, int j, int *perbandingan, Matrix crossword, Matrix hasil, Keywords keys, boolean *ketemu){
    int panjang = strlen(ELMTK(keys,a));
    if (!(*ketemu) && (j<COLS(crossword) - panjang + 1) && (i < ROWS(crossword) - panjang + 1)){
        boolean betul = true;
        int k = 1;
        while (betul && k < panjang ){
            if (ELMT(crossword,i+1,j+1) != ELMT(keys,a,k)){
                betul = false;
            }
            k++;
            j++;
            i++;
            (*perbandingan) ++ ; 
        }
        if (betul) {
            j = j - panjang + 1;
            i = i - panjang + 1;
            int bebas ; 
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i+bebas,j+bebas) = ELMT(keys,a,bebas); 
            }
            *ketemu = true;
            printf("%s\n", ELMTK(keys,a)); 
            displayMatrix(hasil); 
            printf("\n");
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i+bebas,j+bebas) = '-'; 
            }
        }
    }
}

void checkdownleft(int a, int i, int j, int *perbandingan, Matrix crossword, Matrix hasil, Keywords keys, boolean *ketemu){
    int panjang = strlen(ELMTK(keys,a));
    if (!(*ketemu) && (j>panjang -2) && (i < ROWS(crossword) - panjang + 1)){
        boolean betul = true;
        int k = 1;
        while (betul && k < panjang ){
            if (ELMT(crossword,i+1,j-1) != ELMT(keys,a,k)){
                betul = false;
            }
            k++;
            j--;
            i++;
            (*perbandingan) ++ ; 
        }
        if (betul) {
            j = j + panjang - 1;
            i = i - panjang + 1;
            int bebas ; 
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i+bebas,j-bebas) = ELMT(keys,a,bebas); 
            }
            *ketemu = true;
            printf("%s\n", ELMTK(keys,a)); 
            displayMatrix(hasil); 
            printf("\n");
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i+bebas,j-bebas) = '-'; 
            }
        }
    }
}

void checkupright(int a, int i, int j, int *perbandingan, Matrix crossword, Matrix hasil, Keywords keys, boolean *ketemu){
    int panjang = strlen(ELMTK(keys,a));
    if (!(*ketemu) && (j<COLS(crossword) - panjang + 1) && (i>panjang -2)){
        boolean betul = true;
        int k = 1;
        while (betul && k < panjang ){
            if (ELMT(crossword,i-1,j+1) != ELMT(keys,a,k)){
                betul = false;
            }
            k++;
            j++;
            i--;
            (*perbandingan) ++ ; 
        }
        if (betul) {
            j = j - panjang + 1;
            i = i + panjang - 1;
            int bebas ; 
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i-bebas,j+bebas) = ELMT(keys,a,bebas); 
            }
            *ketemu = true;
            printf("%s\n", ELMTK(keys,a)); 
            displayMatrix(hasil); 
            printf("\n");
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i-bebas,j+bebas) = '-'; 
            }
        }
    }
}

void checkupleft(int a, int i, int j, int *perbandingan, Matrix crossword, Matrix hasil, Keywords keys, boolean *ketemu){
    int panjang = strlen(ELMTK(keys,a));
    if (!(*ketemu) && (j>panjang -2) && (i>panjang -2)){
        boolean betul = true;
        int k = 1;
        while (betul && k < panjang ){
            if (ELMT(crossword,i-1,j-1) != ELMT(keys,a,k)){
                betul = false;
            }
            k++;
            j--;
            i--;
            (*perbandingan) ++ ; 
        }
        if (betul) {
            j = j + panjang - 1;
            i = i + panjang - 1;
            int bebas ; 
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i-bebas,j-bebas) = ELMT(keys,a,bebas); 
            }
            *ketemu = true;
            printf("%s\n", ELMTK(keys,a)); 
            displayMatrix(hasil); 
            printf("\n");
            for (bebas=0; bebas< panjang; bebas ++) {
                ELMT(hasil,i-bebas,j-bebas) = '-'; 
            }
        }
    }
}

void solvePuzzle(Matrix *crossword, Matrix *hasil, Keywords *keys){
    printf("\nSolusi dari puzzle adalah: \n\n");
    int a,i,j;
    int perbandingan=0, perbandingansebelum=0;
    int selisih = 0;
    boolean ketemu;
    for (a=0;a<NEFF(*keys);a++) {
        i = 0;
        j = 0;
        ketemu = false; 
        while(i < ROWS(*crossword) && !ketemu){
            while (j < COLS(*crossword) && !ketemu){
                perbandingan ++ ; 
                if (ELMT(*crossword,i,j) == ELMT(*keys,a,0)) {
                    checkright(a,i,j,&perbandingan,*crossword, *hasil, *keys,&ketemu);
                    checkdown(a,i,j,&perbandingan,*crossword, *hasil, *keys,&ketemu);
                    checkleft(a,i,j,&perbandingan,*crossword, *hasil, *keys,&ketemu);
                    checkup(a,i,j,&perbandingan,*crossword, *hasil, *keys,&ketemu);
                    checkdownright(a,i,j,&perbandingan,*crossword, *hasil, *keys,&ketemu);
                    checkdownleft(a,i,j,&perbandingan,*crossword, *hasil, *keys,&ketemu);
                    checkupright(a,i,j,&perbandingan,*crossword, *hasil, *keys,&ketemu);
                    checkupleft(a,i,j,&perbandingan,*crossword, *hasil, *keys,&ketemu);
                }
                j++;
            }
            i++; 
            j=0; 
        }
        i=0; 
        if (!ketemu) {
            printf("%s tidak ditemukan dalam puzzle\n\n", ELMTK(*keys,a));
        }
        else {
            printf("diperlukan perbandingan huruf sebanyak %d\n\n", perbandingan - perbandingansebelum);
        }
        perbandingansebelum = perbandingan;
    }
    printf("Total perbandingan huruf ada sebanyak %d\n", perbandingan);

}

int main(){
    boolean kelar = false;
    char opsi;
    clock_t waktu;
    double waktueksekusi; 
    Matrix crossword;
    Matrix hasil; 
    Keywords keys;
    printf("-------------------------------------------------------------------------------\n");
    printf("Selamat datang di program Word Search Puzzle Solver by Saul Sayers (13520094)\n");
    printf("-------------------------------------------------------------------------------\n\n");
    while (!kelar){
        readinput(&crossword, &hasil, &keys);
        waktu = clock();
        solvePuzzle(&crossword, &hasil, &keys);
        waktu = clock() - waktu;
        waktueksekusi = ((double)waktu)/CLOCKS_PER_SEC;
        printf("Waktu eksekusi adalah sebesar %f detik\n\n", waktueksekusi);
        printf("Proses pencarian kata selesai.\nApakah anda ingin memecahkan puzzle lain?\nKetik y untuk iya dan n untuk tidak (defaultnya y) : ");
        scanf(" %c",&opsi);
        printf("-----------------------------------------------------------------------------------------\n");
        if (opsi == 'n' ){
            kelar = true; 
            printf("Terimakasih sudah menggunakan program Word Search Puzzle Solver by Saul Sayers (13520094)\n");
            printf("-----------------------------------------------------------------------------------------\n\n");
        }
    }
    return 0;
}
