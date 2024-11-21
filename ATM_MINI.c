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
    char tujuan[20];    // tujuan transfer(nomor rekening)
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
void transferUang(); // Mendeklarasikan fungsi untuk transfer

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
    printf("\n======================================\n");
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
            printf("|        4. Transfer Tunai         |\n");
            printf("|        5. Riwayat Transaksi      |\n");
            printf("|        6. Keluar                 |\n");
            printf("====================================\n");
            printf("Pilih opsi: ");
        } else {
            printf("====================================\n");
            printf("|            ATM Menu              |\n");
            printf("====================================\n");
            printf("|        1. Check Balance          |\n");
            printf("|        2. Withdraw               |\n");
            printf("|        3. Deposit                |\n");
            printf("|        4. Transfer               |\n");
            printf("|        5. Transaction History    |\n");
            printf("|        6. Exit                   |\n");
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
                transferUang();
                break;
            case 5:
                tampilkanRiwayatTransaksi();
                break;
            case 6:
                if (bahasa == 0) {
                    printf("\n====================================\n");
                    printf("| Terima kasih telah menggunakan   |\n");
                    printf("| layanan ATM. ;-)                 |\n");
                    printf("====================================\n");
                } else {
                    printf("\n====================================\n");
                    printf("| Thank you for using our ATM      |\n");
                    printf("| service. ;-)                     |\n");
                    printf("====================================\n");
                }
                exit(0);
            default:
                if (bahasa == 0) {
                    printf("\n====================================\n");
                    printf("| Pilihan tidak valid, coba lagi.  |\n");
                    printf("====================================\n");
                } else {
                    printf("\n====================================\n");
                    printf("| Invalid choice, please try again.|\n");
                    printf("====================================\n");
                }
        }

        if (bahasa == 0) {
            printf("\n====================================\n");
            printf("| Lanjutkan transaksi? (y/t):      |\n");
            printf("====================================\n");
        } else {
            printf("\n====================================\n");
            printf("| Do you want to continue? (y/n):  |\n");
            printf("====================================\n");
        }

        scanf(" %c", &lanjutTransaksi);

        if (lanjutTransaksi == 't' || lanjutTransaksi == 'T' || lanjutTransaksi == 'n' || lanjutTransaksi == 'N') {
            if (bahasa == 0) {
                printf("\n====================================\n");
                printf("| Terima kasih telah menggunakan   |\n");
                printf("| layanan ATM. ;-)                 |\n");
                printf("====================================\n");
            } else {
                printf("\n====================================\n");
                printf("| Thank you for using our ATM      |\n");
                printf("| service. ;-)                     |\n");
                printf("====================================\n");
            }
            exit(0);
        }

    } while (lanjutTransaksi == 'y' || lanjutTransaksi == 'Y');
}


// Fungsi untuk mengecek saldo
void cekSaldo() {
    if (bahasa == 0) {
        printf("\n====================================\n");
        printf("|           Info Saldo             |\n");
        printf("====================================\n");
        printf("|   Saldo Anda: Rp %-15d|\n", saldo);
        printf("====================================\n");
    } else {
        printf("\n====================================\n");
        printf("|          Balance Info            |\n");
        printf("====================================\n");
        printf("|   Your balance: Rp %-15d|\n", saldo);
        printf("====================================\n");
    }
}

// Fungsi untuk melakukan tarik tunai
void tarikTunai() {
    int jumlah;
    if (bahasa == 0) {
        printf("\n====================================\n");
        printf("|         Tarik Tunai              |\n");
        printf("====================================\n");
        printf("| Masukkan jumlah uang yang ingin  |\n");
        printf("| ditarik: Rp ");
    } else {
        printf("\n====================================\n");
        printf("|          Withdraw                |\n");
        printf("====================================\n");
        printf("| Enter the amount you want to     |\n");
        printf("| withdraw: Rp ");
    }

    scanf("%d", &jumlah);

    if (jumlah > saldo) {
        if (bahasa == 0) {
            printf("====================================\n");
            printf("|       Saldo tidak cukup!         |\n");
            printf("====================================\n");
        } else {
            printf("====================================\n");
            printf("|     Insufficient balance!        |\n");
            printf("====================================\n");
        }
    } else {
        saldo -= jumlah;
        if (bahasa == 0) {
            printf("====================================\n");
            printf("| Anda menarik Rp %-15d |\n", jumlah);
            printf("| Sisa saldo: Rp %-15d |\n", saldo);
            printf("====================================\n");
        } else {
            printf("====================================\n");
            printf("| You withdrew Rp %-15d |\n", jumlah);
            printf("| Remaining balance: Rp %-10d |\n", saldo);
            printf("====================================\n");
        }

        if (totalTransaksi < MAX_TRANSACTIONS) {
            strcpy(transaksi[totalTransaksi].jenis, bahasa == 0 ? "Tarik" : "Withdraw");
            transaksi[totalTransaksi].jumlah = jumlah;
            totalTransaksi++;
        } else {
            if (bahasa == 0) {
                printf("====================================\n");
                printf("| Riwayat transaksi penuh!         |\n");
                printf("====================================\n");
            } else {
                printf("====================================\n");
                printf("| Transaction history is full!     |\n");
                printf("====================================\n");
            }
        }
    }
}


// Fungsi untuk melakukan setor tunai
void setorTunai() {
    int jumlah;
    if (bahasa == 0) {
        printf("\n====================================\n");
        printf("|           Setor Tunai            |\n");
        printf("====================================\n");
        printf("| Masukkan jumlah uang yang ingin  |\n");
        printf("| disetor: Rp ");
    } else {
        printf("\n====================================\n");
        printf("|            Deposit               |\n");
        printf("====================================\n");
        printf("| Enter the amount you want to     |\n");
        printf("| deposit: Rp ");
    }

    scanf("%d", &jumlah);

    saldo += jumlah;
    if (bahasa == 0) {
        printf("====================================\n");
        printf("| Anda menyetor Rp %-15d |\n", jumlah);
        printf("| Saldo saat ini: Rp %-10d |\n", saldo);
        printf("====================================\n");
    } else {
        printf("====================================\n");
        printf("| You deposited Rp %-15d |\n", jumlah);
        printf("| Current balance: Rp %-10d |\n", saldo);
        printf("====================================\n");
    }

    if (totalTransaksi < MAX_TRANSACTIONS) {
        strcpy(transaksi[totalTransaksi].jenis, bahasa == 0 ? "Setor" : "Deposit");
        transaksi[totalTransaksi].jumlah = jumlah;
        totalTransaksi++;
    } else {
        if (bahasa == 0) {
            printf("====================================\n");
            printf("| Riwayat transaksi penuh!         |\n");
            printf("====================================\n");
        } else {
            printf("====================================\n");
            printf("| Transaction history is full!     |\n");
            printf("====================================\n");
        }
    }
}

// Fungsi untuk mentransfer uang
void transferUang() {
  int jumlah;
  char tujuan[20];
  
  if (bahasa == 0) {
    printf("=======================================\n");
    printf("|  Masukan nomor rekening tujuan:     |\n");
    printf("=======================================\n");
    scanf("%s", tujuan);
    printf("Masukan Jumlah Uang Yang ingin di Transfer: Rp ");
    scanf("%d", &jumlah);
  } else {
      printf("=======================================\n");
      printf("|Enter the recipient's account number:|\n");
      printf("=======================================\n");
      scanf("%s", tujuan);
      printf("Enter the amount you want to transfer: Rp ");
      scanf("%d", &jumlah);
  }
      if (jumlah > saldo) {
        if (bahasa == 0) {
        printf("=============================================\n");
        printf("|Saldo tidak cukup untuk melakukan transfer.|\n");
        printf("=============================================\n");
        } else 
        printf("==========================================\n");
        printf("|Insufficient balance to make a transfer.|\n");
        printf("==========================================\n");
    } else {
        saldo -= jumlah;
        if (bahasa == 0) {
        printf("=====================================================================\n");
        printf("|Anda telah mentransfer Rp %d ke rekening %s. Sisa saldo: Rp % - 15d|\n", jumlah, tujuan, saldo);
        printf("=====================================================================\n");
        }else 
        printf("=========================================================================\n");
        printf("|You have transferred Rp %d to account %s. Remaining balance: Rp % - 15d|\n", jumlah, tujuan, saldo);
        printf("=========================================================================\n");

        // Simpan transaksi
        if (totalTransaksi < MAX_TRANSACTIONS) {
          strcpy(transaksi[totalTransaksi].jenis, "Transfer");
          transaksi[totalTransaksi].jumlah = jumlah;
          strcpy(transaksi[totalTransaksi].tujuan, tujuan);
          totalTransaksi++;
        } else {
            printf("===============================================================\n");
            printf("|Riwayat transaksi penuh, tidak dapat menyimpan transaksi baru|\n");
            printf("===============================================================\n");
        }
    }
}

// Fungsi untuk menampilkan riwayat transaksi
void tampilkanRiwayatTransaksi() {
    if (totalTransaksi == 0) {
        if (bahasa == 0) {
            printf("\n====================================\n");
            printf("|   Belum ada transaksi dilakukan   |\n");
            printf("====================================\n");
        } else {
            printf("\n====================================\n");
            printf("|   No transactions have been made  |\n");
            printf("====================================\n");
        }
    } else {
        if (bahasa == 0) {
            printf("\n====================================\n");
            printf("|        Riwayat Transaksi          |\n");
            printf("====================================\n");
        } else {
            printf("\n====================================\n");
            printf("|      Transaction History          |\n");
            printf("====================================\n");
        }

        for (int i = 0; i < totalTransaksi; i++) {
            if (bahasa == 0) {
                printf("| %2d. %-10s: Rp %-15d |\n", i + 1, transaksi[i].jenis, transaksi[i].jumlah);
            } else {
                printf("| %2d. %-10s: Rp %-15d |\n", i + 1, transaksi[i].jenis, transaksi[i].jumlah);
            }
        }

        printf("====================================\n");
    }
}
