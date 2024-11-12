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
int bahasa;                            // 0 untuk Bahasa Indonesia, 1 untuk English

// Deklarasi Fungsi
void pilihBahasa();
void verifikasiPIN();
void tampilkanMenu();
void cekSaldo();
void tarikTunai();
void setorTunai();
void tampilkanRiwayatTransaksi(); // Mendeklarasikan fungsi untuk riwayat transaksi

int main() {
    pilihBahasa();
    
    do {
        // Proses verifikasi PIN
        verifikasiPIN();
        
        // Tampilkan menu utama setelah berhasil verifikasi PIN
        tampilkanMenu();
        
    } while (1); // Loop utama, dikelola oleh proses verifikasi PIN dan keputusan pengguna

    return 0;
}

// Fungsi untuk memilih bahasa dengan validasi input
void pilihBahasa() {
    int validInput;
    do {
        printf("======================================\n");
        printf("|   Pilih Bahasa / Select Language:  |\n");
        printf("======================================\n");
        printf("|    0. Bahasa Indonesia             |\n");
        printf("|    1. English                      |\n");
        printf("======================================\n");
        printf("Pilih Nomor => ");
        
        validInput = scanf("%d", &bahasa);
        
        // Cek jika input bukan angka atau bukan pilihan yang benar
        if (validInput != 1 || (bahasa != 0 && bahasa != 1)) {
            printf("Pilihan tidak valid. Silakan pilih lagi.\n");
            // Membersihkan buffer untuk menghindari loop tanpa akhir saat input non-angka
            while (getchar() != '\n'); 
        }
    } while (validInput != 1 || (bahasa != 0 && bahasa != 1));
}

// Fungsi untuk melakukan verifikasi PIN dengan batas 3 kali percobaan
void verifikasiPIN() {
    int kesempatan = MAX_TRIES;
    int inputPin;

    if (bahasa == 0) {
    printf("\n======================================\n");
    printf("|    SELAMAT DATANG DI ATMBUDDY      |\n");
    printf("======================================\n");
    }else {
    printf("======================================\n");
    printf("|        WELCOME TO ATMBUDDY         |\n");
    printf("======================================\n");
    }

    while (kesempatan--) {
        if (bahasa == 0) printf("Masukkan PIN Anda: ");
        else printf("Enter your PIN: ");
        
        scanf("%d", &inputPin);

        if (inputPin == PIN_DEFAULT) {
            if (bahasa == 0) printf("PIN Benar!\n");
            else printf("PIN Correct!\n");
            return;
        }

        if (kesempatan == 0) {
            if (bahasa == 0) printf("PIN Anda diblokir!. Silakan hubungi bank.\n");
            else printf("Your PIN is blocked!. Please contact the bank.\n");
            exit(0); // Mengakhiri program jika gagal 3 kali
        }

        if (bahasa == 0) printf("PIN Salah! Kesempatan tersisa: %d\n", kesempatan);
        else printf("Incorrect PIN! Remaining attempts: %d\n", kesempatan);
    }
}

// Fungsi untuk menampilkan menu transaksi
void tampilkanMenu() {
    int pilihan;
    char lanjutTransaksi;

    do {
        if (bahasa == 0) {
            printf("\n====================================\n");
            printf("|           Menu ATM               |\n");
            printf("====================================\n");
            printf("|        1. Cek Saldo              |\n");
            printf("|        2. Tarik Tunai            |\n");
            printf("|        3. Setor Tunai            |\n");
            printf("|        4. Riwayat Transaksi      |\n");
            printf("|        5. Keluar                 |\n");
            printf("====================================\n");
            printf("Pilih opsi: ");
            
        } else {
            printf("====================================\n");
            printf("|            ATM Menu              |\n");
            printf("====================================\n");
            printf("|        1. Check Balance          |\n");
            printf("|        2. Withdraw               |\n");
            printf("|        3. Deposit                |\n");
            printf("|        4. Transaction History    |\n");
            printf("|        5. Exit                   |\n");
            printf("====================================\n");
            printf("Choose an option:");
        }
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
                if (bahasa == 0) printf("Terima kasih telah menggunakan layanan ATM. ;-)\n");
                else printf("Thank you for using our ATM service. ;-)\n");
                exit(0);
            default:
                if (bahasa == 0) printf("Pilihan tidak valid, silakan coba lagi.\n");
                else printf("Invalid choice, please try again.\n");
        }

        if (bahasa == 0) printf("\nApakah Anda ingin melanjutkan transaksi? (y/t): ");
        else printf("\nDo you want to continue the transaction? (y/n): ");
        
        scanf(" %c", &lanjutTransaksi);

        if (lanjutTransaksi == 't' || lanjutTransaksi == 'T' || lanjutTransaksi == 'n' || lanjutTransaksi == 'N') {
            if (bahasa == 0) printf("Terima kasih telah menggunakan layanan ATM. ;-)\n");
            else printf("Thank you for using our ATM service. ;-)\n");
            exit(0);
        }

    } while (lanjutTransaksi == 'y' || lanjutTransaksi == 'Y');
}

// Fungsi untuk mengecek saldo
void cekSaldo() {
    if (bahasa == 0) printf("Saldo Anda: Rp %d\n", saldo);
    else printf("Your balance: Rp %d\n", saldo);
}

// Fungsi untuk melakukan tarik tunai
void tarikTunai() {
    int jumlah;
    if (bahasa == 0) printf("Masukkan jumlah uang yang ingin ditarik: Rp ");
    else printf("Enter the amount you want to withdraw: Rp ");
    
    scanf("%d", &jumlah);

    if (jumlah > saldo) {
        if (bahasa == 0) printf("Saldo tidak cukup!\n");
        else printf("Insufficient balance!\n");
    } else {
        saldo -= jumlah;
        if (bahasa == 0) printf("Anda menarik Rp %d. Sisa saldo: Rp %d\n", jumlah, saldo);
        else printf("You withdrew Rp %d. Remaining balance: Rp %d\n", jumlah, saldo);

        if (totalTransaksi < MAX_TRANSACTIONS) {
            strcpy(transaksi[totalTransaksi].jenis, bahasa == 0 ? "Tarik" : "Withdraw");
            transaksi[totalTransaksi].jumlah = jumlah;
            totalTransaksi++;
        } else {
            if (bahasa == 0) printf("Riwayat transaksi penuh, tidak dapat menyimpan transaksi baru.\n");
            else printf("Transaction history is full, cannot save new transactions.\n");
        }
    }
}

// Fungsi untuk melakukan setor tunai
void setorTunai() {
    int jumlah;
    if (bahasa == 0) printf("Masukkan jumlah uang yang ingin disetor: Rp ");
    else printf("Enter the amount you want to deposit: Rp ");
    
    scanf("%d", &jumlah);

    saldo += jumlah;
    if (bahasa == 0) printf("Anda menyetor Rp %d. Saldo saat ini: Rp %d\n", jumlah, saldo);
    else printf("You deposited Rp %d. Current balance: Rp %d\n", jumlah, saldo);

    if (totalTransaksi < MAX_TRANSACTIONS) {
        strcpy(transaksi[totalTransaksi].jenis, bahasa == 0 ? "Setor" : "Deposit");
        transaksi[totalTransaksi].jumlah = jumlah;
        totalTransaksi++;
    } else {
        if (bahasa == 0) printf("Riwayat transaksi penuh, tidak dapat menyimpan transaksi baru.\n");
        else printf("Transaction history is full, cannot save new transactions.\n");
    }
}

// Fungsi untuk menampilkan riwayat transaksi
void tampilkanRiwayatTransaksi() {
    if (totalTransaksi == 0) {
        if (bahasa == 0) printf("Belum ada transaksi yang dilakukan.\n");
        else printf("No transactions have been made.\n");
    } else {
        if (bahasa == 0) printf("\n--- Riwayat Transaksi ---\n");
        else printf("\n--- Transaction History ---\n");
        
        for (int i = 0; i < totalTransaksi; i++) {
            if (bahasa == 0) printf("%d. %s: Rp %d\n", i + 1, transaksi[i].jenis, transaksi[i].jumlah);
            else printf("%d. %s: Rp %d\n", i + 1, transaksi[i].jenis, transaksi[i].jumlah);
        }
    }
}
