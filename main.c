#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deklarasi Konstanta
#define PIN_DEFAULT 852
#define MAX_TRIES 3
#define MAX_TRANSACTIONS 100 // Batas maksimal transaksi yang dapat disimpan

// Struktur Data untuk Transaksi
typedef struct {
    char jenis[10];    // Jenis transaksi, misalnya "Tarik" atau "Setor"
    int jumlah;        // Jumlah uang yang ditarik atau disetor
} Transaksi;

// Deklarasi Variabel Global
int saldo = 1000000;
Transaksi transaksi[MAX_TRANSACTIONS]; // Array untuk menyimpan riwayat transaksi
int totalTransaksi = 0;                // Counter untuk jumlah transaksi

// Deklarasi Fungsi
void verifikasiPIN();
void tampilkanMenu();
void cekSaldo();
void tarikTunai();
void setorTunai();
void tampilkanRiwayatTransaksi();

int main() {
    do {
        // Proses verifikasi PIN
        verifikasiPIN();
        
        // Tampilkan menu utama setelah berhasil verifikasi PIN
        tampilkanMenu();
        
    } while (1); // Loop utama, dikelola oleh proses verifikasi PIN dan keputusan pengguna

    return 0;
}

// Fungsi untuk melakukan verifikasi PIN dengan batas 3 kali percobaan
void verifikasiPIN() {
    int kesempatan = MAX_TRIES;
    int inputPin;

    while (kesempatan--) {
        printf("Masukkan PIN Anda: ");
        scanf("%d", &inputPin);

        if (inputPin == PIN_DEFAULT) {
            printf("PIN Benar!\n");
            return;
        }

        if (kesempatan == 0) {
            printf("PIN Anda diblokir. Silakan hubungi bank.\n");
            exit(0); // Mengakhiri program jika gagal 3 kali
        }

        printf("PIN Salah! Kesempatan tersisa: %d\n", kesempatan);
    }
}

// Fungsi untuk menampilkan menu transaksi
void tampilkanMenu() {
    int pilihan;
    char lanjutTransaksi;

    do {
        printf("\n--- Menu ATM ---\n");
        printf("1. Cek Saldo\n2. Tarik Tunai\n3. Setor Tunai\n4. Lihat Riwayat Transaksi\n5. Keluar\nPilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                cekSaldo();
                break;
            case 2:
                tarikTunai();
                break;
            case 3:
                setorTunai();
                break;
            case 4:
                tampilkanRiwayatTransaksi();
                break;
            case 5:
                printf("Terima kasih telah menggunakan layanan ATM.\n");
                exit(0); // Keluar dari program saat pengguna memilih opsi "Keluar"
            default:
                printf("Pilihan tidak valid, silakan coba lagi.\n");
        }

        // Tanya apakah ingin melanjutkan transaksi
        printf("Apakah Anda ingin melanjutkan transaksi? (y/t): ");
        scanf(" %c", &lanjutTransaksi);

        // Jika jawabannya "t" (tidak), keluar dari loop menu
        if (lanjutTransaksi == 't' || lanjutTransaksi == 'T') {
            printf("Terima kasih telah menggunakan layanan ATM.\n");
            exit(0);
        }

        // Jika jawabannya "y" (ya), meminta PIN lagi sebelum melanjutkan transaksi
        if (lanjutTransaksi == 'y' || lanjutTransaksi == 'Y') {
            verifikasiPIN();
        }

    } while (lanjutTransaksi == 'y' || lanjutTransaksi == 'Y');
}

// Fungsi untuk mengecek saldo
void cekSaldo() {
    printf("Saldo Anda: Rp %d\n", saldo);
}

// Fungsi untuk melakukan tarik tunai
void tarikTunai() {
    int jumlah;
    printf("Masukkan jumlah uang yang ingin ditarik: Rp ");
    scanf("%d", &jumlah);

    if (jumlah > saldo) {
        printf("Saldo tidak cukup!\n");
    } else {
        saldo -= jumlah;
        printf("Anda menarik Rp %d. Sisa saldo: Rp %d\n", jumlah, saldo);

        // Simpan transaksi ke dalam array
        if (totalTransaksi < MAX_TRANSACTIONS) {
            strcpy(transaksi[totalTransaksi].jenis, "Tarik");
            transaksi[totalTransaksi].jumlah = jumlah;
            totalTransaksi++;
        } else {
            printf("Riwayat transaksi penuh, tidak dapat menyimpan transaksi baru.\n");
        }
    }
}

// Fungsi untuk melakukan setor tunai
void setorTunai() {
    int jumlah;
    printf("Masukkan jumlah uang yang ingin disetor: Rp ");
    scanf("%d", &jumlah);

    saldo += jumlah;
    printf("Anda menyetor Rp %d. Saldo saat ini: Rp %d\n", jumlah, saldo);

    // Simpan transaksi ke dalam array
    if (totalTransaksi < MAX_TRANSACTIONS) {
        strcpy(transaksi[totalTransaksi].jenis, "Setor");
        transaksi[totalTransaksi].jumlah = jumlah;
        totalTransaksi++;
    } else {
        printf("Riwayat transaksi penuh, tidak dapat menyimpan transaksi baru.\n");
    }
}

// Fungsi untuk menampilkan riwayat transaksi
void tampilkanRiwayatTransaksi() {
    if (totalTransaksi == 0) {
        printf("Belum ada transaksi yang dilakukan.\n");
    } else {
        printf("\n--- Riwayat Transaksi ---\n");
        for (int i = 0; i < totalTransaksi; i++) {
            printf("%d. %s: Rp %d\n", i + 1, transaksi[i].jenis, transaksi[i].jumlah);
        }
    }
}
