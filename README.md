# Tugas Kecil 1 IF2211 Strategi Algoritma
> Word Search Puzzle Solver

## Penjelasan Program
Program word search puzzle solver ini diciptakan dalam bahasa C dan menggunakan algoritma secara Brute Force. Program ini menerima input berupa txt file dalam folder test yang berisi Crossword puzzle, kemudian diikuti dengan newline kosong dan diikuti kembali dengan beberapa kata kunci yang ingin dicari dalam puzzle tersebut.

Setelah membaca input, program akan mulai masuk dalam tahap proses pencarian solusi. Program akan mencari secara Brute Force, yakni mengecek huruf pertama dari keyword yang dicari kemudian memeriksa 8 arah mata angin yang memungkinkan untuk membentuk keyword. Proses penarian sebuah keyword akan selesai apabila solusi ditemukan ATAU proses pencarian sudah selesai sampai akhir dan tetap tidak ditemukan solusi.

## Requirements and Setup
* Disarankan agar menjalankan program dalam Terminal OS Windows.
* File input dalam folder test yang ingin dicari solusinya harus sudah sesuai dalam format. Format yang dimaksud adalah word search puzzle berbentuk segiempat kemudian diikuti oleh sebuah baris kosong dan dilanjutkan oleh beberapa keywords. Untuk tiap karakter puzzle yang sebaris dijeda dengan sebuah spasi. Huruf dalam puzzle dan keywords harus seragam yang artinya hanya full uppercase ataupun hanya full lowercase. Berikut adalah contoh dari format input txt file: 
```
D A B Z I X K W P E P E
L N K T Y N A M R E G N
E T A V Y L D S S C S G
E L E L I L X O F N N L
Y N M Z L C K O I A R A
F Q A L N O N Y Y R Q N
S R M C I H H F P F Z D
B P P D H U O Y X U O P
X S A R G E N T I N A S
B R L I G N I L N Y L P
J G Q N N N M W S D F Z
N V R X D B H F K Q M F

SPAIN
ENGLAND
ITALY
GERMANY
HOLLAND
FRANCE
BRAZIL
ARGENTINA
```
* **NOTE** : MOHON JANGAN MENGUBAH STRUKTUR PROGRAM KARENA PROGRAM DEPENDANT KEPADA STRUKTURNYA

## Cara Menggunakan Program
1. Progam dijalankan cukup dengan mengeksekusi file main.exe yang terdapat dalam folder bin. File main.exe dapat dijalankan cukup dengan double click file tersebut. Alternatifnya juga bisa membuka terminal pada direktori folder bin, lalu menjalankan perintah ./main.exe
2. Program akan meminta nama file input txt yang akan dicari solusinya. Silahkan input nama file dengan benar dan lengkap, misalnya "small1.txt" (tanpa tanda kutip). Apabila nama file salah atau tidak ditemukan, maka program akan mengulangi meminta nama file hingga benar
3. Program akan menampilkan solusi dari tiap keyword.
4. Program akan bertanya apakah pengguna selesai menggunakan program, atau ingin mencari solusi puzzle lain. Apabila selesai cukup input "n", dan apabila ingin mencari yang lain cukup input "y" (tanpa tanda kutip)

## Contributors :
- Saul Sayers (13520094)