#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <string.h>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void addNewcontact(void);
void listAll(void);
void deletecontact(void);
int caricontact(void);
int deletesemua(void);
string nama[10];
int count_nama = 0;

typedef struct contact{
    int number;
    char name[20];
    char phone[15];
    char email[20];
    struct contact *next;
    int count;
    } Contact;
Contact *firstc,*currentc,*newc;

int cnum = 0;

int main(){
    FILE *datafile;
    char const *filename = "contactdatabase.dat";
    char ch;
    firstc = NULL;
    datafile = fopen(filename,"r");

    if(datafile)
    {
	    firstc = (struct contact *)malloc(sizeof(struct contact));
	    currentc = firstc;
	    while(1)
     	    {
		    newc = (struct contact *)malloc(sizeof(struct contact));
		    fread(currentc,sizeof(struct contact),1,datafile);
		    if(currentc->next == NULL)
			    break;
		    currentc->next = newc;
            currentc->count=0;
		    currentc = newc;
	    }
	    fclose(datafile);
	    cnum = currentc->number;

    }
    do{
        fflush(stdin);
        puts("\nWelcome To The Contact Database");
        puts("-- -----------------------------");
        puts("1 - Tambah contact baru");
        puts("2 - Hapus contact");
        puts("3 - Daftar semua contact");
        puts("4 - Lihat info contact");
        puts("5 - Hapus seluruh contact");
        puts("-- -----------------------------");
        puts("Q - keluar dan simpan\n");
        printf("\tPerintah: ");
        ch = getchar();
	    ch = toupper(ch);
        switch(ch)
        {
        case '1':
            system("clear");
            puts("Add a new contact\n");
	        fflush(stdin);
            addNewcontact();
            getchar();
            system("clear");
            break;
	    case '2':
	        system("clear");
            puts("Delete a contact\n");
            deletecontact();
            getchar();
            system("clear");
            break;
	    case '3':
	        system("clear");
            puts("List seluruh contact\n");
            listAll();
            getchar();
            break;
	    case '4':
	        system("clear");
            puts("List seluruh contact\n");
            caricontact();
            getchar();
            system("clear");
            break;
	    case '5':
	        deletesemua();
            break;
        case 'Q':
            puts("Save and quit\n");
            default:
            break;
        }
    }
    while(ch != 'Q');
    currentc = firstc;
    if(currentc == NULL)
	    return(0);
    datafile = fopen(filename,"w");
    if(datafile == NULL)
    {
	    printf("Error %s\n",filename);
	    return(1);
    }
    while(currentc != NULL)
    {
	    fwrite(currentc,sizeof(struct contact),1,datafile);
	    currentc = currentc->next;
    }
    fclose(datafile);
    return(0);
}

void addNewcontact(void){
    Mat gambar;
    string dumdum;
    newc = (struct contact *)malloc(sizeof(struct contact));
    if(firstc==NULL)
        firstc = currentc = newc;
    else{
        currentc = firstc;
        while(currentc->next != NULL)currentc = currentc->next;
        currentc->next = newc;
        currentc = newc;
    }
    cnum++;
    printf("%27s: %5i\n","contact number",cnum);
    currentc->number = cnum;   

    printf("%27s: ","Masukan nama: ");
    cin >> nama[count_nama];
    strcpy(currentc->name, nama[count_nama].c_str());

    printf("%27s: ","Masukan nomor telefon: ");
    cin >> dumdum;
    strcpy(currentc->phone, dumdum.c_str());

    printf("%27s: ","Masukan e-mail: ");
    cin >> dumdum;
    strcpy(currentc->email, dumdum.c_str());
    VideoCapture cap(0);
    while(1){
        cap >> gambar;
        imshow("tekan esc untuk mengambil gambar", gambar);
        if(waitKey(10) == 27){
            string almaat = "/home/nathan/Documents/foto/" + nama[count_nama] + ".jpg";
            imwrite(almaat, gambar);
            break;
        }
    }
    destroyAllWindows();
    printf("Penambahan berhasil");
    count_nama++;
    currentc->count=0;

    currentc->next = NULL;
}

void listAll(void){
    if(firstc==NULL)
        puts("Contact kosong");
    else{
	    printf("%6s %-20s\n","Acct#","Name");
        puts("------ --------------------");
        currentc=firstc;

        do{
                printf("%6d: %-20s\n",\
                currentc->number,\
                currentc->name);
        }
        while((currentc=currentc->next) != NULL);
    }
}
int deletesemua(void){
    if(remove("contactdatabase.dat") == 0){
        printf("Contact berhasil dihapus");
        getchar();

    }
    else{
        printf("Contact gagal dihapus");
    }
    system("clear");
    return main();
}

void deletecontact(void){
    int record;
    struct contact *previousa;
    if(firstc==NULL)
    {
        puts("Contact masih kosong");
        return;
    }

    listAll();
    printf("Nomor contact yang ingin dihapus: ");
    scanf("%d",&record);
    currentc = firstc;

    while(currentc != NULL){
        if(currentc->number == record)
	{
	    if(currentc == firstc)
		firstc=currentc->next;
	    else
		previousa->next = currentc->next;
        free(currentc);
	    printf("contact %d deleted!\n",record);
	    return;
	}
	else
	{
        previousa = currentc;
	    currentc = currentc->next;
	}
    }
    printf("contact %d not found!\n",record);
    getchar();
 }

int caricontact(void){
    int nomor;
    listAll();
    printf("Nomor contact yang ingin dilihat: ");
    scanf("%d",&nomor);
    currentc = firstc;

    while(currentc != NULL){
        if(currentc->number == nomor){
            string alamat = ("/home/nathan/Documents/foto/" + nama[nomor-1] + ".jpg");
            cout << alamat << endl;
            Mat fotoo = imread(alamat);
            printf("\n");
            printf("%6s %-20s %-15s %-15s\n","Acct#","Name","Phone","Email");
            printf("%6d: %-20s %-15s %-20s\n",\
            currentc->number,\
            currentc->name,\
            currentc->phone,\
            currentc->email);
            while(1){
                imshow("foto", fotoo);
                if(waitKey(10) == 27){
                    break;
                }
            }
            destroyAllWindows();
			return 0;
        }
        else{
            currentc = currentc->next;
        }
    }
    printf("contact %d tidak ditemukan\n", nomor);
    getchar();
    return 1;
}