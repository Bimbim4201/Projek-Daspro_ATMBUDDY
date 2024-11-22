#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Deklarasi Konstanta
#define PIN_DEFAULT 852
#define MAX_TRIES 3
#define MAX_TRANSACTIONS 100 // Batas maksimal transaksi yang dapat disimpan

// Struktur Data untuk Akun Pengguna
typedef struct {
    char username[20];   // Username akun
    int pin;             // PIN pengguna
    int saldo;           // Saldo akun pengguna
} Akun;
// Array untuk menyimpan akun-akun pengguna
Akun akun[100];
int totalAkun = 0; // Jumlah akun yang terdaftar

// Struktur Data untuk Transaksi
typedef struct {
    char jenis[10];    // Jenis transaksi, misalnya "Tarik" atau "Setor"
    int jumlah;        // Jumlah uang yang ditarik atau disetor
    char tujuan[20];    // tujuan transfer(nomor rekening)
    char waktu[20]; // Waktu transaksi
} Transaksi;


// Deklarasi Variabel Global
Transaksi transaksi[MAX_TRANSACTIONS]; // Array untuk menyimpan riwayat transaksi
int totalTransaksi = 0;                // Counter untuk jumlah transaksi
int saldo;
int bahasa;                            // 0 untuk Bahasa Indonesia, 1 untuk English

// Deklarasi Fungsi
void pilihBahasa();
void bacaAkunDariFile();
void simpanAkunKeFile();
void verifikasiPIN();
void tampilkanMenu();
void cekSaldo();
void tarikTunai();
void setorTunai();
void tampilkanRiwayatTransaksi(); // Mendeklarasikan fungsi untuk riwayat transaksi
void transferUang(); // Mendeklarasikan fungsi untuk transfer

int main() {
    pilihBahasa();

    // Membaca akun-akun dari file
    bacaAkunDariFile();
    
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
    char username[20];
    int pin;
    int ditemukan = 0;
    int percobaan = 0; // menyimpan jumlah percbaan

    if (bahasa == 0) {
        printf("\n======================================\n");
        printf("|    SELAMAT DATANG DI ATMBUDDY      |\n");
        printf("======================================\n");
    } else {
        printf("\n======================================\n");
        printf("|        WELCOME TO ATMBUDDY         |\n");
        printf("======================================\n");
    }

    while (percobaan < MAX_TRIES) {
        if (bahasa == 0) printf("Masukkan Username: ");
        else printf("Enter your Username: ");
        
        scanf("%s", username);

        if (bahasa == 0) printf("\nMasukkan PIN Anda: ");
        else printf("\nEnter your PIN: ");
        
        scanf("%d", &pin);

        // Cari akun berdasarkan username dan PIN
        for (int i = 0; i < totalAkun; i++) {
            if (strcmp(akun[i].username, username) == 0 && akun[i].pin == pin) {
                saldo = akun[i].saldo; // Mengatur saldo berdasarkan akun yang ditemuk0an
                printf("PIN Benar! Selamat datang, %s!\n", username);
                ditemukan = 1;
                return;
            }
        }

        percobaan++;

        if (ditemukan == 0) {
            if (bahasa == 0) printf("Username atau PIN salah! Silakan coba lagi.\n");
            else printf("Incorrect Username or PIN! Please try again.\n");
        }

        // jika percobaan mencapai batas, maka program akan keluar
        if (percobaan == MAX_TRIES) {
            if (bahasa == 0) printf("Akun Anda telah terblokir setelah 3 kali percobaan yang salah.\n");
            else printf("Your account has been locked after 3 incorrect attempts.\n");
            exit(0); // keluar program
            }
            
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
            printf("\n====================================\n");
            printf("|            ATM Menu              |\n");
            printf("====================================\n");
            printf("|        1. Check Balance          |\n");
            printf("|        2. Withdraw               |\n");
            printf("|        3. Deposit                |\n");
            printf("|        4. Transfer               |\n");
            printf("|        5. Transaction History    |\n");
            printf("|        6. Exit                   |\n");
            printf("====================================\n");
            printf("Choose an option: ");
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

void bacaAkunDariFile() {
    FILE *file = fopen("akun.txt", "r");
    if (file == NULL) {
        printf("Tidak dapat membuka file akun.\n");
        return;
    }

    while (fscanf(file, "%s %d %d\n", akun[totalAkun].username, &akun[totalAkun].pin, &akun[totalAkun].saldo) == 3) {
        totalAkun++;
    }

    fclose(file);
}

// Fungsi untuk menyimpan akun dan saldo ke file
void simpanAkunKeFile() {
    FILE *file = fopen("akun.txt", "w");
    if (file == NULL) {
        printf("Tidak dapat membuka file untuk menyimpan akun.\n");
        return;
    }

    for (int i = 0; i < totalAkun; i++) {
        fprintf(file, "%s %d %d\n", akun[i].username, akun[i].pin, akun[i].saldo);
    }

    fclose(file);
}


// Fungsi untuk mendapatkan waktu saat ini
void dapatkanWaktu(char *buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", t);
}

// Fungsi untuk melakukan tarik tunai
void tarikTunai() {
    char username[20];
    int jumlah;
    char waktu[20];  // Menyimpan waktu transaksi

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

    if (jumlah <= 0) {
        if (bahasa == 0) {
            printf("====================================\n");
            printf("|       Jumlah tidak valid!        |\n");
            printf("====================================\n");
        } else {
            printf("====================================\n");
            printf("|     Invalid amount!              |\n");
            printf("====================================\n");
        }
        return; // Kembali tanpa memproses transaksi
    }

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
        saldo -= jumlah;  // Kurangi saldo setelah tarik tunai

        // Menyimpan transaksi tarik tunai ke dalam array transaksi[]
        dapatkanWaktu(waktu);  // Ambil waktu transaksi
        strcpy(transaksi[totalTransaksi].jenis, "Tarik");
        transaksi[totalTransaksi].jumlah = jumlah;
        strcpy(transaksi[totalTransaksi].waktu, waktu);
        totalTransaksi++;

        // Update saldo pada akun pengguna yang sesuai
        for (int i = 0; i < totalAkun; i++) {
            if (strcmp(akun[i].username, username) == 0) {
                akun[i].saldo = saldo;
            }
        }

        // Simpan akun yang sudah diperbarui ke file
        simpanAkunKeFile();

        if (bahasa == 0) {
            printf("====================================\n");
            printf("| Anda menarik Rp %-15d |\n", jumlah);
            printf("| Sisa saldo: Rp %-15d |\n", saldo);
            printf("====================================\n");
        } else {
            printf("====================================\n");
            printf("| You withdraw Rp %-15d  |\n", jumlah);
            printf("| Remaining balance: Rp %-10d |\n", saldo);
            printf("====================================\n");
        }
    }
}




// Fungsi untuk melakukan setor tunai
void setorTunai() {
    char username[20];
    int jumlah;
    char waktu[20];

    if (bahasa == 0) {
        printf("\n====================================\n");
        printf("|           Setor Tunai             |\n");
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

    if (jumlah <= 0) {
        if (bahasa == 0) {
            printf("====================================\n");
            printf("|       Jumlah tidak valid!        |\n");
            printf("====================================\n");
        } else {
            printf("====================================\n");
            printf("|     Invalid amount!              |\n");
            printf("====================================\n");
        }
        return; // Kembali tanpa memproses transaksi
    }

    saldo += jumlah;  // Tambah saldo setelah setor tunai

    // Menyimpan transaksi setor tunai ke dalam array transaksi[]
    dapatkanWaktu(waktu);  // Ambil waktu transaksi
    strcpy(transaksi[totalTransaksi].jenis, "Setor");
    transaksi[totalTransaksi].jumlah = jumlah;
    strcpy(transaksi[totalTransaksi].waktu, waktu);
    totalTransaksi++;

    // Update saldo pada akun pengguna yang sesuai
    for (int i = 0; i < totalAkun; i++) {
        if (strcmp(akun[i].username, username) == 0) {
            akun[i].saldo = saldo;
        }
    }

    // Simpan akun yang sudah diperbarui ke file
    simpanAkunKeFile();

    if (bahasa == 0) {
        printf("====================================\n");
        printf("| Anda menyetor Rp %-15d |\n", jumlah);
        printf("| Saldo saat ini: Rp %-10d |\n", saldo);
        printf("====================================\n");
    } else {
        printf("====================================\n");
        printf("| You deposited Rp %-15d |\n", jumlah);
        printf("| Current balance: Rp %-10d   |\n", saldo);
        printf("====================================\n");
    }
}


void transferUang() {
    char username[20];
    char penerima[20];
    int jumlah;
    char waktu[20];
    int penerimaIndex = -1, pengirimIndex = -1;



    if (bahasa == 0)
    {
        printf("=======================================\n");
        printf("|   Masukkan username pengirim:       |\n");
        printf("=======================================\n");
        scanf("%s", username);
    } else {
        printf("=======================================\n");
        printf("|   Enter sender's username:          |\n");
        printf("=======================================\n");
        scanf("%s", username);
    }

        for (int i = 0; i < totalAkun; i++) {
        if (strcmp(akun[i].username, username) == 0) {
            pengirimIndex = i;
            break;
        }
    }

    if (pengirimIndex == -1) {
        if (bahasa == 0) {
            printf("===========================================\n");
            printf("| Username pengirim tidak ditemukan!       |\n");
            printf("===========================================\n");
        } else {
            printf("===========================================\n");
            printf("| Sender username not found!              |\n");
            printf("===========================================\n");
        }
        return;
    }

    if (bahasa == 0) {
        printf("=======================================\n");
        printf("|  Masukan username penerima:         |\n");
        printf("=======================================\n");
        scanf("%s", penerima);
        printf("Masukan jumlah uang yang ingin ditransfer: Rp ");
        scanf("%d", &jumlah);
    } else {
        printf("=======================================\n");
        printf("|Enter the recipient's username:      |\n");
        printf("=======================================\n");
        scanf("%s", penerima);
        printf("Enter the amount you want to transfer: Rp ");
        scanf("%d", &jumlah);
    }

    if (jumlah <= 0) {
        if (bahasa == 0) {
            printf("====================================\n");
            printf("|       Jumlah tidak valid!        |\n");
            printf("====================================\n");
        } else {
            printf("====================================\n");
            printf("|     Invalid amount!              |\n");
            printf("====================================\n");
        }
        return;
    }

    // Cari akun penerima berdasarkan username
    for (int i = 0; i < totalAkun; i++) {
        if (strcmp(akun[i].username, penerima) == 0) {
            penerimaIndex = i;
            break;
        }
    }

    if (penerimaIndex == -1) {
        if (bahasa == 0) {
            printf("===========================================\n");
            printf("| Username penerima tidak ditemukan!       |\n");
            printf("===========================================\n");
        } else {
            printf("===========================================\n");
            printf("| Recipient username not found!           |\n");
            printf("===========================================\n");
        }
        return;
    }

    if (jumlah > akun[pengirimIndex].saldo) {
        if (bahasa == 0) {
            printf("=============================================\n");
            printf("| Saldo tidak cukup untuk melakukan transfer.|\n");
            printf("=============================================\n");
        } else {
            printf("==========================================\n");
            printf("| Insufficient balance to make a transfer.|\n");
            printf("==========================================\n");
        }
    } else {
        // Kurangi saldo pengirim
        akun[pengirimIndex].saldo -= jumlah;
        akun[penerimaIndex].saldo += jumlah;  // Tambahkan saldo penerima

        // Simpan perubahan ke file
        simpanAkunKeFile();

        // Simpan riwayat transaksi
        dapatkanWaktu(waktu);
        strcpy(transaksi[totalTransaksi].jenis, "Transfer");
        transaksi[totalTransaksi].jumlah = jumlah;
        strcpy(transaksi[totalTransaksi].tujuan, penerima);
        strcpy(transaksi[totalTransaksi].waktu, waktu);
        totalTransaksi++;

        if (bahasa == 0) {
            printf("=======================================\n");
            printf("| Anda mentransfer Rp %-15d ke %-15s |\n", jumlah, penerima);
            printf("| Saldo saat ini: Rp %-10d           |\n", akun[pengirimIndex].saldo);
            printf("=======================================\n");
        } else {
            printf("=======================================\n");
            printf("| You transferred Rp %-15d to %-15s |\n", jumlah, penerima);
            printf("| Current balance: Rp %-10d          |\n", akun[pengirimIndex].saldo);
            printf("=======================================\n");
        }
    }
}



void tampilkanRiwayatTransaksi() {
    if (totalTransaksi == 0) {
        printf("Tidak ada transaksi.\n");
    } else {
        printf("\n=====================================\n");
        printf("|     Riwayat Transaksi            |\n");
        printf("=====================================\n");
        for (int i = 0; i < totalTransaksi; i++) {
            printf("%s | Rp %d | %s | %s\n", 
                   transaksi[i].jenis, 
                   transaksi[i].jumlah, 
                   transaksi[i].tujuan, 
                   transaksi[i].waktu);
        }
        printf("=====================================\n");
    }
}
