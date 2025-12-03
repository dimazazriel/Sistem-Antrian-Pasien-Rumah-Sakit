#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//dtruct untuk menyimpan data pasien
typedef struct Pasien {
    char nama[50];
    int prioritas;       
    struct Pasien *next;
} Pasien;

Pasien *front = NULL;

// Buat node pasien baru
Pasien* buatPasien(char nama[], int prioritas) {
    Pasien *baru = (Pasien*) malloc(sizeof(Pasien));
    strcpy(baru->nama, nama);
    baru->prioritas = prioritas;
    baru->next = NULL;
    return baru;
}

// Menambahkan pasien sesuai prioritas (ascending: 1 duluan)
void enqueue(char nama[], int prioritas) {
    Pasien *baru = buatPasien(nama, prioritas);

    // Jika antrian kosong atau prioritas baru lebih tinggi dari front
    if (front == NULL || prioritas < front->prioritas) {
        baru->next = front;
        front = baru;
        return;
    }

    // Cari posisi yang tepat
    Pasien *temp = front;
    while (temp->next != NULL && temp->next->prioritas <= prioritas) {
        temp = temp->next;
    }

    baru->next = temp->next;
    temp->next = baru;
}

// Menghapus pasien dengan prioritas tertinggi (yang paling depan)
void dequeue() {
    if (front == NULL) {
        printf("Antrian kosong!\n");
        return;
    }

    Pasien *temp = front;
    printf("Pasien dipanggil: %s (Prioritas %d)\n", temp->nama, temp->prioritas);

    front = front->next;
    free(temp);
}

// Menampilkan seluruh antrian
void tampilkanAntrian() {
    if (front == NULL) {
        printf("Antrian kosong!\n");
        return;
    }

    Pasien *temp = front;
    printf("\n=== Daftar Antrian Pasien ===\n");
    while (temp != NULL) {
        printf("Nama: %-15s | Prioritas: %d\n", temp->nama, temp->prioritas);
        temp = temp->next;
    }
}

int main() {
    int pilih;
    char nama[50];
    int prioritas;

    do {
        printf("\n---------- SISTEM ANTRIAN PASIEN ----------\n");
        printf("1. Tambah Pasien\n");
        printf("2. Panggil Pasien (Dequeue)\n");
        printf("3. Tampilkan Antrian\n");
        printf("0. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                printf("Masukkan nama pasien: ");
                scanf(" %49[^\n]", nama);
                printf("Masukkan prioritas (1=tinggi, 2=sedang, 3=rendah): ");
                scanf("%d", &prioritas);
                enqueue(nama, prioritas);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                tampilkanAntrian();
                break;

            case 0:
                printf("Selamat Tinggal\n");
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }

    } while (pilih != 0);

    return 0;
}
