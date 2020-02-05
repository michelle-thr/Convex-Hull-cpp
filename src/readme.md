# Convex Hull
Program ini dibuat untuk menyelesaikan Tugas Kecil mata kuliah Strategi Algoritma (IF2211) oleh:
Michelle Theresia
13518050
K-02

## Deskripsi Program
Program menggunakan bahasa C++ menampilkan convex hull dari kumpulan titik yang diberkan dalam bidang 2 dimensi.
Program menerima input banyak titik (n). Lalu program akan membangkitkan titik sebanyak n. Setiap titik dinyatakan dengan koordinat (x,y).
Luaran program adalah himpunan titik yang membentuk convex hull, dan waktu yang dibutuhkan untuk menentukan titik-titik convex hull

## Menjalankan Program (WINDOWS)
Untuk menjalankan program ini dapat menggunakan command prompt di windows dengan command:
g++ convex_hull.cpp -lfreeglut -lopengl32 -lglu32 -o c.exe
namun agar lebih cepat ditambahkan shell script (ketik compile.sh pada cmd) untuk mengkompilasi
program menjadi sebuah file .exe, lalu file .exe tersebut dapat dijalankan.