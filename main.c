
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUK 50
#define PANJANG_NAMA 60

// Array utama
char namaProduk[MAX_PRODUK][PANJANG_NAMA];
double harga[MAX_PRODUK];
int stok[MAX_PRODUK];
int terjual[MAX_PRODUK];

int jumlahProduk = 0;
double totalPendapatan = 0;

// Membaca input teks
void inputTeks(char pesan[], char hasil[], int ukuran) {
    printf("%s", pesan);
    fgets(hasil, ukuran, stdin);
    hasil[strcspn(hasil, "\n")] = '\0';
}

// Membaca input integer
int inputInteger(char pesan[]) {
    char buffer[100];
    char *akhir;
    long nilai;

    while (1) {
        inputTeks(pesan, buffer, sizeof(buffer));
        nilai = strtol(buffer, &akhir, 10);

        while (isspace((unsigned char)*akhir))
            akhir++;

        if (buffer[0] != '\0' && *akhir == '\0' &&
            nilai >= -2147483647L - 1 &&
            nilai <= 2147483647L) {
            return (int)nilai;
        }

        printf("Input harus berupa angka bulat!\n");
    }
}

// Membaca input harga
double inputHarga(char pesan[]) {
    char buffer[100];
    char *akhir;
    double nilai;

    while (1) {
        inputTeks(pesan, buffer, sizeof(buffer));
        nilai = strtod(buffer, &akhir);

        while (isspace((unsigned char)*akhir))
            akhir++;

        if (buffer[0] != '\0' && *akhir == '\0' && nilai >= 0)
            return nilai;

        printf("Harga tidak valid atau negatif!\n");
    }
}

// Data produk awal
void dataAwal() {
    strcpy(namaProduk[0], "Nasi Goreng");
    strcpy(namaProduk[1], "Mie Ayam");
    strcpy(namaProduk[2], "Es Teh");
    strcpy(namaProduk[3], "Air Mineral");
    strcpy(namaProduk[4], "Roti Bakar");

    harga[0] = 15000;
    harga[1] = 12000;
    harga[2] = 5000;
    harga[3] = 4000;
    harga[4] = 10000;

    stok[0] = 20;
    stok[1] = 15;
    stok[2] = 30;
    stok[3] = 40;
    stok[4] = 12;

    for (int i = 0; i < 5; i++)
        terjual[i] = 0;

    jumlahProduk = 5;
}

// Menampilkan seluruh produk
void tampilProduk() {
    printf("\n========== DAFTAR PRODUK ==========\n");
    printf("%-5s %-20s %-15s %-10s %-10s\n",
           "No", "Nama", "Harga", "Stok", "Terjual");

    for (int i = 0; i < jumlahProduk; i++) {
        printf("%-5d %-20s Rp %-12.2f %-10d %-10d\n",
               i + 1, namaProduk[i], harga[i],
               stok[i], terjual[i]);
    }
}

// Menambahkan produk
void tambahProduk() {
    if (jumlahProduk >= MAX_PRODUK) {
        printf("Kapasitas produk sudah penuh!\n");
        return;
    }

    char nama[PANJANG_NAMA];

    inputTeks("Nama produk: ", nama, sizeof(nama));

    if (strlen(nama) == 0) {
        printf("Nama produk tidak boleh kosong!\n");
        return;
    }

    for (int i = 0; i < jumlahProduk; i++) {
        if (strcmp(namaProduk[i], nama) == 0) {
            printf("Produk sudah tersedia!\n");
            return;
        }
    }

    double h = inputHarga("Harga produk: ");
    int s = inputInteger("Stok produk: ");

    if (s < 0) {
        printf("Stok tidak boleh negatif!\n");
        return;
    }

    strcpy(namaProduk[jumlahProduk], nama);
    harga[jumlahProduk] = h;
    stok[jumlahProduk] = s;
    terjual[jumlahProduk] = 0;

    jumlahProduk++;

    printf("Produk berhasil ditambahkan!\n");
}

// Mengubah produk
void ubahProduk() {
    tampilProduk();

    int nomor = inputInteger("Nomor produk: ");

    if (nomor < 1 || nomor > jumlahProduk) {
        printf("Produk tidak ditemukan!\n");
        return;
    }

    int i = nomor - 1;

    printf("1. Ubah harga\n");
    printf("2. Ubah stok\n");
    printf("3. Ubah harga dan stok\n");

    int pilihan = inputInteger("Pilih: ");

    if (pilihan == 1 || pilihan == 3)
        harga[i] = inputHarga("Harga baru: ");

    if (pilihan == 2 || pilihan == 3) {
        int s = inputInteger("Stok baru: ");

        if (s < 0) {
            printf("Stok tidak boleh negatif!\n");
            return;
        }

        stok[i] = s;
    }

    if (pilihan < 1 || pilihan > 3) {
        printf("Pilihan tidak tersedia!\n");
        return;
    }

    printf("Data produk berhasil diubah!\n");
}

// Menambah stok
void tambahStok() {
    tampilProduk();

    int nomor = inputInteger("Nomor produk: ");

    if (nomor < 1 || nomor > jumlahProduk) {
        printf("Produk tidak ditemukan!\n");
        return;
    }

    int tambahan = inputInteger("Jumlah stok tambahan: ");

    if (tambahan <= 0) {
        printf("Jumlah harus lebih dari nol!\n");
        return;
    }

    if (tambahan > 2147483647 - stok[nomor - 1]) {
        printf("Jumlah stok terlalu besar!\n");
        return;
    }

    stok[nomor - 1] += tambahan;

    printf("Stok berhasil ditambahkan!\n");
}

// Pencarian produk berdasarkan nama
void cariProduk() {
    char kataKunci[PANJANG_NAMA];
    int ditemukan = 0;

    inputTeks("Masukkan nama produk: ",
              kataKunci, sizeof(kataKunci));

    for (int i = 0; i < jumlahProduk; i++) {
        if (strstr(namaProduk[i], kataKunci) != NULL) {
            printf("\nProduk ditemukan!\n");
            printf("Nama  : %s\n", namaProduk[i]);
            printf("Harga : Rp %.2f\n", harga[i]);
            printf("Stok  : %d\n", stok[i]);
            ditemukan = 1;
        }
    }

    if (!ditemukan)
        printf("Produk tidak ditemukan!\n");
}

// Transaksi penjualan beberapa produk
void transaksi() {
    int nomor, jumlah;
    int indeks[ MAX_PRODUK ];
    int jumlahBeli[ MAX_PRODUK ];
    int banyak = 0;

    double total = 0;

    if (jumlahProduk == 0) {
        printf("Belum ada produk!\n");
        return;
    }

    tampilProduk();

    printf("\n===== TRANSAKSI PENJUALAN =====\n");
    printf("Masukkan 0 untuk menyelesaikan transaksi.\n");

    while (1) {
        nomor = inputInteger("\nNomor produk: ");

        if (nomor == 0)
            break;

        if (nomor < 1 || nomor > jumlahProduk) {
            printf("Produk tidak ditemukan!\n");
            continue;
        }

        int i = nomor - 1;

        jumlah = inputInteger("Jumlah pembelian: ");

        if (jumlah <= 0) {
            printf("Jumlah pembelian harus lebih dari nol!\n");
            continue;
        }

        int posisi = -1;

        for (int j = 0; j < banyak; j++) {
            if (indeks[j] == i) {
                posisi = j;
                break;
            }
        }

        int sudahDipesan = (posisi == -1) ? 0 : jumlahBeli[posisi];

        if (jumlah > stok[i] - sudahDipesan) {
            printf("Stok tidak mencukupi!\n");
            continue;
        }

        if (posisi == -1) {
            indeks[banyak] = i;
            jumlahBeli[banyak] = jumlah;
            banyak++;
        } else {
            jumlahBeli[posisi] += jumlah;
        }

        printf("Produk berhasil dimasukkan!\n");
    }

    if (banyak == 0) {
        printf("Transaksi dibatalkan!\n");
        return;
    }

    printf("\n========== RINCIAN PEMBELIAN ==========\n");

    for (int i = 0; i < banyak; i++) {
        int p = indeks[i];

        double subtotal = harga[p] * jumlahBeli[i];

        printf("%s x %d = Rp %.2f\n",
               namaProduk[p], jumlahBeli[i], subtotal);

        total += subtotal;
    }

    printf("---------------------------------------\n");
    printf("TOTAL PEMBAYARAN: Rp %.2f\n", total);

    char konfirmasi[10];

    inputTeks("Konfirmasi pembayaran (y/n): ",
              konfirmasi, sizeof(konfirmasi));

    if (tolower((unsigned char)konfirmasi[0]) != 'y') {
        printf("Transaksi dibatalkan!\n");
        return;
    }

    // Memperbarui stok dan jumlah terjual
    for (int i = 0; i < banyak; i++) {
        int p = indeks[i];

        stok[p] -= jumlahBeli[i];
        terjual[p] += jumlahBeli[i];
    }

    totalPendapatan += total;

    printf("Transaksi berhasil!\n");
}

// Laporan penjualan
void laporanPenjualan() {
    int totalUnit = 0;
    int terlaris = -1;

    printf("\n========== LAPORAN PENJUALAN ==========\n");

    for (int i = 0; i < jumlahProduk; i++) {
        printf("%s : %d terjual\n",
               namaProduk[i], terjual[i]);

        totalUnit += terjual[i];

        if (terlaris == -1 ||
            terjual[i] > terjual[terlaris]) {
            terlaris = i;
        }
    }

    printf("---------------------------------------\n");
    printf("Total unit terjual : %d\n", totalUnit);
    printf("Total pendapatan   : Rp %.2f\n",
           totalPendapatan);

    if (totalUnit == 0) {
        printf("Produk terlaris    : Belum ada penjualan\n");
    } else {
        printf("Produk terlaris    : %s (%d unit)\n",
               namaProduk[terlaris], terjual[terlaris]);
    }
}

// Mengurutkan produk
void urutkanProduk() {
    printf("\n1. Harga termurah\n");
    printf("2. Penjualan terbanyak\n");

    int pilihan = inputInteger("Pilih pengurutan: ");

    if (pilihan != 1 && pilihan != 2) {
        printf("Pilihan tidak tersedia!\n");
        return;
    }

    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            int tukar = 0;

            if (pilihan == 1 && harga[j] > harga[j + 1])
                tukar = 1;

            if (pilihan == 2 && terjual[j] < terjual[j + 1])
                tukar = 1;

            if (tukar) {
                char namaSementara[PANJANG_NAMA];
                double hargaSementara;
                int stokSementara, terjualSementara;

                strcpy(namaSementara, namaProduk[j]);
                strcpy(namaProduk[j], namaProduk[j + 1]);
                strcpy(namaProduk[j + 1], namaSementara);

                hargaSementara = harga[j];
                harga[j] = harga[j + 1];
                harga[j + 1] = hargaSementara;

                stokSementara = stok[j];
                stok[j] = stok[j + 1];
                stok[j + 1] = stokSementara;

                terjualSementara = terjual[j];
                terjual[j] = terjual[j + 1];
                terjual[j + 1] = terjualSementara;
            }
        }
    }

    printf("Pengurutan berhasil!\n");
    tampilProduk();
}

// Mengecek stok menipis
void cekStok() {
    int ditemukan = 0;

    printf("\n===== PRODUK DENGAN STOK KURANG DARI 5 =====\n");

    for (int i = 0; i < jumlahProduk; i++) {
        if (stok[i] < 5) {
            printf("%s - Stok: %d\n",
                   namaProduk[i], stok[i]);

            ditemukan = 1;
        }
    }

    if (!ditemukan)
        printf("Tidak ada stok yang menipis.\n");
}

// Menu utama
void menu() {
    printf("\n========================================\n");
    printf(" SISTEM MONITORING STOK KANTIN KAMPUS\n");
    printf("========================================\n");
    printf("1. Lihat Daftar Produk\n");
    printf("2. Tambah Produk\n");
    printf("3. Ubah Produk\n");
    printf("4. Transaksi Penjualan\n");
    printf("5. Tambah Stok\n");
    printf("6. Cari Produk\n");
    printf("7. Urutkan Produk\n");
    printf("8. Laporan Penjualan\n");
    printf("9. Cek Stok Menipis\n");
    printf("0. Keluar\n");
    printf("========================================\n");
}

// Program utama
int main() {
    int pilihan;

    dataAwal();

    printf("SELAMAT DATANG DI KANTIN KAMPUS\n");

    do {
        menu();

        pilihan = inputInteger("Pilih menu: ");

        switch (pilihan) {
            case 1:
                tampilProduk();
                break;

            case 2:
                tambahProduk();
                break;

            case 3:
                ubahProduk();
                break;

            case 4:
                transaksi();
                break;

            case 5:
                tambahStok();
                break;

            case 6:
                cariProduk();
                break;

            case 7:
                urutkanProduk();
                break;

            case 8:
                laporanPenjualan();
                break;

            case 9:
                cekStok();
                break;

            case 0:
                printf("Terima kasih. Program selesai.\n");
                break;

            default:
                printf("Menu tidak tersedia!\n");
        }

    } while (pilihan != 0);

    return 0;
}

