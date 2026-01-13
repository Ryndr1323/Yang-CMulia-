# 🎵 Aplikasi Simulasi Pemutar Music dengan Struktur Data MLL

![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=C%2B%2B&logoColor=white)

Aplikasi berbasis C++ untuk memainkan/menambahkan/memodifikasi/menghapus data musik berbasis MLL

---

## Fitur Utama
* **🛠️ High-Decent Robustness**: Input Pengguna diatur sedemikian rupa untuk pengalaman yang mulus dan lancar
* **🎛️ Huge Music Support**: Hampir seluruh aksi musik, mulai dari menambahkan, menghapus dan memainkan didukung oleh aplikasi ini

## Aplikasi yang Terlibat

* **Backend & Frontend**: Native C++
* **Aplikasi**: VS Code
  
## Cara Menjalankan Aplikasi

> **Catatan:** Sebelum menjalankan aplikasi ini, pastikan compiler **C++ (g++)** sudah terpasang di komputer Anda.

### 1. Clone repositori

Buka **Command Prompt (cmd)** atau terminal, lalu clone repositori ini:

```bash
<tautan repository Git>
```

### 2. Masuk ke direktori proyek dan build source code

Pindah ke direktori hasil clone, lalu lakukan kompilasi source code.

**Build default (direkomendasikan):**

```bash
cd <folder hasil clone>
g++ src/*.cpp -o Music
```

Perintah di atas akan menghasilkan file executable dengan nama **Music**.

**Kustomisasi nama build (opsional):**
Anda dapat mengganti nama executable sesuai keinginan:

```bash
g++ src/*.cpp -o <nama_aplikasi>
```

**Tanpa parameter `-o` (tidak disarankan):**

```bash
g++ src/*.cpp
```

> ⚠️ Tanpa parameter `-o`, compiler akan menghasilkan nama file default (`a.exe` di Windows atau `a.out` di Linux/macOS) yang kurang deskriptif.

### 3. Menjalankan aplikasi

* **Jika menggunakan build default:**

  ```bash
  .\Music
  ```

* **Jika menggunakan nama kustom:**

  ```bash
  .\<nama_aplikasi>
  ```

---

## Struktur Projek

```text
musicplayer/
├── src/                    # Source Code Aplikasi
│   ├── bonefunction.cpp    # Kode Fungsi Utama
│   ├── bonefunction.h      # Header #1
│   ├── flowinterface.cpp   # Kode Menu Utama
│   ├── flowinterface.h     # Header #2
│   ├── menuinterface.cpp   # Kode Penjalan Menu
│   ├── menuinterface.h     # Header #3
│   └── main.cpp            # Main Interface
└── README.md               # Dokumentasi Projek
```

---

## TBA

---

## Creator

**Naufal Rayandra Gunawan**
* 103012400070
* Telkom University

**M Fahd Asyhab**
* 103012400358
* Telkom University






