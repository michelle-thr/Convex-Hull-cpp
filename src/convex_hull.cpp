#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <GL/glut.h>

using namespace std;

vector < pair <int,int> > ch;
vector < pair <int,int> > ttk;

// prosedur untuk menampilkan window
void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (-20.0, 120.0, -20.0, 120.0);
}

// prosedur untuk menampilkan titik dan garis
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

    // warna titik (RGB)
	glColor3f(255.0, 0.0, 0.0);
    // ukuran titik
    glPointSize(3.5f);
	// meggambar titik-titik dari vektor
	glBegin(GL_POINTS);
	{
		for(int i=0; i<ttk.size(); i++){
            glVertex2i(ttk[i].first, ttk[i].second);
        }
	}
	glEnd();

	// memberi warna pada garis
    glColor3f(0.0, 0.0, 255.0);
    // ukuran (lebar) garis
    glLineWidth(1.0f);
    // menggambar garis antara 2 koordinat dari vektor
	glBegin(GL_LINES);
        for(int j=0; j<ch.size()-1; j++){
            glVertex2i(ch[j].first,ch[j].second);
            glVertex2i(ch[j+1].first,ch[j+1].second);
        }
	glEnd();

	glFlush();
}

// prosedur untuk menampilkan isi vector
void printVector(vector < pair <int,int> > v){
    for(int i=0; i<v.size(); i++){
        cout << "(" << v[i].first << "," << v[i].second << ")" << endl;
    }
}

// prosedur untuk menampilkan isi vector dalam bentuk list
void printVectorList(vector < pair <int,int> > v){

    cout << "[";
    for(int i=0; i<v.size(); i++){
        cout << "(" << v[i].first << "," << v[i].second << ")";
        if(i!=v.size()-1){
            cout << ",";
        }
    }
    cout << "]";
}

// fungsi untuk mengeluarkan hasil rumus terhadap titik-titik yang dibandingkan
// apabila hasil positif, fungsi mengembalikan nilai 1
// apabila hasil negatif, fungsi mengembalikan nilai -1
// apabila hasil 0, fungsi mengembalikan nilai 0
int rumus(int a,int b,int c,int x,int y){
    if( ((a*x)+(b*y)-c) > 0 ){
        return 1;
    }
    if( ((a*x)+(b*y)-c) < 0 ){
        return -1;
    }
    else{
        return 0;
    }
}

// program utama
int main(int argc,char *argv[]){
    int titik;
    int x, y, a, b, c;
    int idxTerkiri, idxCalonCH, idxPasanganCalonCH, idxTB, prev, patokan;
    bool found, sama;
    time_t start, end;

    srand (time(NULL)); // untuk fungsi random sehingga hasil setiap compile/run berbeda-beda

    cout << "Jumlah titik: "; // menerima input jumlah titik
    cin >> titik;

    // me-generate koordinat x dan y secara random
    // input titik x dan y ke dalam vektor ttk
    for(int i=0; i<titik; i++){
        x = rand() % 100;
        y = rand() % 100;
        ttk.push_back({x,y});
    }

    cout << "Titik-titik:" << endl; // menampilkan titik-titik yang telah di generate
    printVector(ttk);

    // inisiasi penghitung waktu yang dibutuhkan program untuk menentukan convex hull
    time(&start);

    // cari titik paling kiri karena titik kiri pasti merupakan titik kandidat convex hull
    idxTerkiri = 0;
    for(int j=0; j<ttk.size(); j++){
        if(ttk[j].first < ttk[idxTerkiri].first){
            idxTerkiri = j;
        }
    }
    idxCalonCH = idxTerkiri;

    prev = -999;
    idxPasanganCalonCH;

    // algoritma untuk menemukan convex hull
    do{
        idxPasanganCalonCH = 0;
        found = false;

        //cari titik pasangan
        while(!found){
            // kasus titik calon pasangan sama dengan titik calon convex hull
            if(idxPasanganCalonCH == idxCalonCH || idxPasanganCalonCH == prev){
                idxPasanganCalonCH++;
                continue;
            }

            // perhitungan untuk menentukan a, b, dan c
            a = ttk[idxPasanganCalonCH].second - ttk[idxCalonCH].second;
            b = ttk[idxCalonCH].first - ttk[idxPasanganCalonCH].first;
            c = (ttk[idxCalonCH].first*ttk[idxPasanganCalonCH].second) - (ttk[idxCalonCH].second*ttk[idxPasanganCalonCH].first);

            //bandingin titik di luar titik yg membentuk garis
            idxTB = 0;
            while (idxTB == idxCalonCH || idxTB == idxPasanganCalonCH) {
                idxTB++;
            }

            sama = true;
            // patokan adalah hasil dari perbandingan dengan titik pertama index terdekat pada vektor
            patokan = rumus(a, b, c, ttk[idxTB].first, ttk[idxTB].second);

            // membandingkan dengan semua titik pada vektor
            while(idxTB < ttk.size() && sama){
                //cek index titik banding tidak boleh sama dengan titik yang membentuk garis dan jika line yang
                // diperiksa mengandung titik yang dicek bukan pertama maka tidak boleh membandingkan dengan titik
                // yang sebelumnya merupakan titik dari line sebelumnya
                if(!(idxTB == idxCalonCH || idxTB == idxPasanganCalonCH))
                {
                    if( (rumus(a,b,c,ttk[idxTB].first,ttk[idxTB].second) != patokan) && (rumus(a,b,c,ttk[idxTB].first,ttk[idxTB].second) != 0) ){
                        sama = false;
                    }

                }
                idxTB++;
            }

            // kasus semua titik di kanan semua atau di kiri semua sehingga garis adalah convex hull
            if(sama){
                prev = idxCalonCH;
                ch.push_back({ttk[idxCalonCH].first,ttk[idxCalonCH].second});
                idxCalonCH = idxPasanganCalonCH;
                if(idxCalonCH==idxTerkiri){
                    ch.push_back({ttk[idxPasanganCalonCH].first,ttk[idxPasanganCalonCH].second});
                }
                found = true;
            }
            // kasus garis bukan convex hull
            else{
                idxPasanganCalonCH++;
            }
        }

    } while(idxCalonCH!=idxTerkiri);

    // mencatat waktu saat convex hull ditemukan
    time(&end);

    // menghitung jarak waktu
    double time_taken = double(end - start); 

    // menampilkan koordinat (x,y) convex hull dalam bentuk list
    cout << "Convex Hull:" << endl;
    printVectorList(ch);

    // menampilkan waktu yang dibutuhkan untuk mencari convex hull
    cout << endl << endl << "Waktu pencarian convex hull : " << fixed 
         << time_taken; 
    cout << " detik " << endl; 

    // pengaturan untuk menampilkan gambar convex hull
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Convex Hull");
    init2D(255.0,255.0,255.0);
    glutDisplayFunc(display);
    glutMainLoop();
    
}