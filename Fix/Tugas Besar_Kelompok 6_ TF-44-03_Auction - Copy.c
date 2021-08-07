#include<stdio.h>
#include<string.h>

// Struct untuk Menyimpan Data Member
struct akunmember{
	char muname[99],mpwd[99],ktk[99],lelangIkut[99];
    int bid;
}mem;

// Struct untuk Menyimpan Data Lelang
struct datalelang{
    char nama[99], deskripsi[99], muname[99];
    int hargaAwal, bid, tgl;
}lelang,temp[99],temp2;

// Struct untuk Menyimpan Data Pemenang Lelang
struct datamenang{
    char nama[99], muname[99];
    int bid;
}menang;

// Variable Global
char uname[99],pwd[99]; // Variabel untuk Login
int i,j,n,pil,bid;
char input[99],tutup[99];

// Prototype Prosedur
void loginadmin();
void admin();
void anggota();
void hapusMember();
void lelangBaru();
void lelangMenang();
void lelangList();
void lelangTutup();
void lelangHapus();
void lelangPantau();
void member();
void menuMember();
void memreg();
void memlog();
void membid();
void memtpl();
void memwin();
void sorting();

//File Sekuensial
FILE *f_member, *f_lelang, *f_menang, *f_cadang;

//Fungsi Utama
int main()
{
	system("cls");
	printf("\t\t Daskom Auction Center\n");
	printf("\t\t    ---DAS'Auction---\n");
	
	printf(" Main Menu: \n");
	printf("1. Admin \n");
	printf("2. Member \n");
	printf("3. Exit \n");
	printf("99. Anggota Kelompok \n");
	printf("\nPilih menu : "); scanf("%d",&pil); getchar();
	system("cls");
	switch (pil) 
	{
		case 1:
			i=3;
			loginadmin();
            main();
            break;
		case 2: 
			member(); 
			break;
		case 3: 
            printf("Sampai Jumpa Kembali"); getchar();
			system("exit");
            break;
        case 99:
        	anggota();
        	getchar();
        	system("cls");
        	main();
        	break;
	}
	return 0;
}

//Penampilan Anggota Kelompok
void anggota()
{
	printf("Anggota Kelompok : \n");
   	printf("1. Ferry Chandra\t\t(1104202092) \n");
    printf("2. Hafidz Abdul Jabbaar\t\t(1104202113) \n");
    printf("3. Joshua Hatorangan Siregar\t(1104201130)\n");
    printf("4. Muhammad Aqila Nizam\t\t(1104202153)\n\n");
}
//Proses Admin
void admin()
{
	printf("\t\t Daskom Auction Center\n");
    printf("\t\t  ---DAS'Auction---\n");
    printf("1. Buat Lelang Baru \n");
    printf("2. List Lelang \n");
    printf("3. Hapus Akun Member \n");
    printf("4. Pantau Lelang \n");
    printf("5. Update Status Pemenang Lelang \n");
    printf("6. Logout \n");
    printf("Pilih menu : "); scanf("%d",&pil); getchar();
	switch(pil)
	{
		case 1: 
            system("cls");
            lelangBaru();
            break;
		case 2: 
            system("cls");
            lelangList();
            break;
		case 3:
			system("cls");
			hapusMember();
			break;
        case 4: 
			system("cls");
			lelangPantau();
			break;
        case 5: 
        	system("cls");
			lelangTutup();
			break;
        case 6: 
			system("cls");
			main();
			break;
	}
}

//Prosedur Login Admin
void loginadmin()
{
	while (i>0)
	{
        system("cls");
        printf("\t\t Daskom Auction Center\n");
        printf("\t\t  ---DAS'Auction---\n");
        printf("\n---Login Admin---\n\n");
        printf("Username : "); gets(uname);
        printf("Password : "); gets(pwd);
        if(strcmp(uname,"Admin")==0 && strcmp(pwd,"1234")==0)
        {
            printf("\nSelamat Login Berhasil \n"); getchar();
            system("cls");
            admin();
        }
        else 
		{
			if(i==1) 
			{
				printf("\nLogin Gagal");
				getchar();
				system("cls");
				main();
			}
			else 
			{
				printf("\nLogin Gagal Sisa Percobaan %d",i-1);
				getchar();
				system("cls");
			}
		}
    	i--;
    }
}

// Untuk Membuat Lelang Baru
void lelangBaru()
{
    printf("\t\t Daskom Auction Center\n");
    printf("\t\t  ---DAS'Auction---\n");
    printf("Nama lelang\t: "); gets(lelang.nama);
    printf("Deskripsi\t: "); gets(lelang.deskripsi);
    printf("Harga Awal\t: "); scanf("%d", &lelang.hargaAwal); getchar();
    printf("Tanggal Akhir\t: "); scanf("%d", &lelang.tgl); getchar();
    strcpy(lelang.muname,"");
    lelang.bid=lelang.hargaAwal;
    f_lelang = fopen("Lelang.txt","ab");
    fwrite(&lelang, sizeof(lelang), 1, f_lelang);
    fclose(f_lelang);
    printf("\nLelang berhasil dibuat!\n");
    getchar();
    system("cls");
    admin();
}

// Penghapusan Akun Member
void hapusMember(){
	int x=0;
	printf("\t\t Daskom Auction Center\n");
    printf("\t\t  ---DAS'Auction---\n");
    printf("\n===LIST MEMBER=== \n\n");
    f_member=fopen("Member.txt","rb");
	while(fread(&mem,sizeof(mem),1,f_member)==1)
	{
		printf("%s\n",mem.muname);
	}
	fclose(f_member);
	
	f_member=fopen("Member.txt","rb");
    f_cadang=fopen("Member(b).txt","wb");
    printf("\nMasukkan Nama untuk Dihapus : "); gets(input);
    while(fread(&mem,sizeof(mem),1,f_member)==1)
    {
        if(strcmp(mem.muname,input)!=0)
        {
            fwrite(&mem,sizeof(mem),1,f_cadang);
            x++;
        }
    }
    fclose(f_member);
    fclose(f_cadang);

    remove("Member.txt");
    rename("Member(b).txt","Member.txt");
    if(x!=0) printf("Penghapusan Gagal / Dibatalkan\n");
    else printf("Penghapusan Berhasil\n");
    getchar();
    system("cls"); 
	admin(); 
}

//List Untuk Lelang
void lelangList()
{
	printf("\t\t Daskom Auction Center\n");
    printf("\t\t  ---DAS'Auction---\n");
    printf("===List Lelang===\n\n");
	f_lelang=fopen("Lelang.txt","rb");
	while(fread(&lelang,sizeof(lelang),1,f_lelang)==1)
	{
		printf("Nama Lelang\t: %s\n",lelang.nama);
		printf("Deskripsi\t: %s\n",lelang.deskripsi);
   		printf("Harga Awal\t: %d\n",lelang.hargaAwal);
    	printf("Tanggal Akhir\t: %d\n\n",lelang.tgl);
	}
	fclose(f_lelang);
	getchar();
	system("cls");
	admin();
}

//Pemantauan Lelang
void lelangPantau()
{
	printf("\t\t Daskom Auction Center\n");
    printf("\t\t  ---DAS'Auction---\n");
    printf("===List Lelang===\n\n");
	f_lelang=fopen("Lelang.txt","rb");
	while(fread(&lelang,sizeof(lelang),1,f_lelang)==1)
	{
		printf("Nama Lelang\t  : %s\n",lelang.nama);
		printf("Deskripsi\t  : %s\n",lelang.deskripsi);
   		printf("Harga Awal\t  : %d\n",lelang.hargaAwal);
   		printf("Tawaran Tertinggi : %d\n",lelang.bid);
   		printf("Penawar\t\t  : %s\n",lelang.muname);
    	printf("Tanggal Akhir\t  : %d\n\n",lelang.tgl);
	}
	fclose(f_lelang);
	getchar();
	
	system("cls");
	admin();
}



//Penutupan Lelang
void lelangTutup()
{
	i=0;
	system("cls");
	printf("\t\t Daskom Auction Center\n");
    printf("\t\t  ---DAS'Auction---\n");
    printf("===List Lelang===\n\n");
    f_lelang=fopen("Lelang.txt","rb");
    //Penampilan Lelang
	while(fread(&lelang,sizeof(lelang),1,f_lelang)==1)
	{
		printf("Nama Lelang\t: %s\n",lelang.nama);
		printf("Deskripsi\t: %s\n",lelang.deskripsi);
   		printf("Harga Awal\t: %d\n",lelang.hargaAwal);
		printf("Bid Tertinggi\t: %d\n",lelang.bid);
		printf("Penawar\t\t: %s\n",lelang.muname);
    	printf("Tanggal Akhir\t: %d\n\n",lelang.tgl);
	}
	fclose(f_lelang);
	//Penutupan Lelang
	printf("Lelang yang Akan Ditutup : "); gets(input);
	lelangMenang();
	lelangHapus();
}

void lelangMenang()
{
	f_lelang=fopen("Lelang.txt","rb");
	f_menang=fopen("Menang.txt","ab");
	rewind(f_lelang);
	while(fread(&lelang,sizeof(lelang),1,f_lelang)==1)
	{
		if(strcmp(input,lelang.nama)==0)
		{
			i=1;
			strcpy(menang.nama,lelang.nama);
			strcpy(menang.muname,lelang.muname);
			menang.bid=lelang.bid;
			fwrite(&menang,sizeof(menang),1,f_menang);
			break;
		}
	}
	fclose(f_menang);
	fclose(f_lelang);
}

//Hapus Lelang
void lelangHapus()
{
	f_lelang=fopen("Lelang.txt","rb");
	f_cadang=fopen("Lelang(b).txt","wb");
	while(fread(&lelang,sizeof(lelang),1,f_lelang)==1)
	{
		if(strcmp(lelang.nama,input)!=0)
		{
			fwrite(&lelang,sizeof(lelang),1,f_cadang);
		}
	}
	fclose(f_lelang);
	fclose(f_cadang);
		
	remove("Lelang.txt");
	rename("Lelang(b).txt","Lelang.txt");
	system("cls");
	admin();
}

// Prosedur Member
void member()
{	
	system("cls");
	printf("\t\tDaskom Auction Center\n");
	printf("\t\t  ---DAS'Auction---\n");
	
	printf("\n=Menu Member=\n\n");
	printf("1. Registrasi\t[New Account]\n");
	printf("2. Login\t[Existed Account]\n");
	printf("3. Logout\n");
	printf("Masukkan Kode Input : "); scanf("%d",&pil);getchar();
	system("cls");

	switch(pil)
	{
		case 1:
            memreg();
            system("cls"); member();
            break;
		case 2:
		    n=3;
            memlog(); break;
		case 3:
			system("cls");
			main();break;
	}
}

//Untuk Member Daftar
void memreg()
{
	f_member=fopen("Member.txt","ab");

    printf("\t\t Daskom Auction Center\n");
    printf("\t\t  ---DAS'Auction---\n");
    printf("\n=Registrasi=\n\n");
    printf("Username\t: ");gets(mem.muname);
    printf("Password\t: ");gets(mem.mpwd);
    printf("Kontak\t\t: ");gets(mem.ktk);
    strcpy(mem.lelangIkut,"");
    mem.bid=0;
    fwrite(&mem,sizeof(mem),1,f_member);
    printf("Registrasi Berhasil\n");
    fclose(f_member);
    getchar();
}

//Untuk Member Login
void memlog()
{
	printf("\t\t Daskom Auction Center\n");
    printf("\t\t  ---DAS'Auction---\n");
    printf("\n---Login---\n\n");
    printf("Username\t: "); gets(uname);
    printf("Password\t: "); gets(pwd);
    i=0;
    f_member=fopen("Member.txt","rb");                                                         
	while(fread(&mem,sizeof(mem),1,f_member)==1)
	{
        if(strcmp(uname,mem.muname)==0&&strcmp(pwd,mem.mpwd)==0)
		{
			i=1;
            break;
        }
    }
    fclose(f_member);
    // Status Login
    if(i==1){
        printf("\nLOGIN BERHASIL!!!\n");
        getchar();
        system("cls");
        menuMember();
    }
	else{
        printf("\nLOGIN GAGAL\n");
        getchar();
        system("cls");
        n--;
        if(n>0) memlog();
        else {
            printf("\nKESEMPATAN HABIS\n"); 
            member();
        }
    system("cls");
    }
}
// Menu Member
void menuMember(){
    printf("\t\t Daskom Auction Center\n");
	printf("\t\t  ---DAS'Auction---\n");
	
	printf("\n=Selamat datang, %s=\n\n",uname);
	printf("1. Tampilkan Semua Lelang\n");
	printf("2. Lelang yang Dimenangkan\n");
	printf("3. Logout\n\n");
	printf("Masukkan Kode Input : "); scanf("%d",&pil); getchar();
	system("cls");
    switch(pil){
        case 1: system("cls");memtpl();break;
        case 2: system("cls");memwin();break;
        case 3: system("cls");main();break;
    }
}

//Penampilan Lelang
void memtpl()
{
	char yn;
	system("cls");
	printf("\t\t Daskom Auction Center\n");
    printf("\t\t  ---DAS'Auction---\n");
    printf("===LIST LELANG===\n\n");
	f_lelang=fopen("Lelang.txt","rb");
	while(fread(&lelang,sizeof(lelang),1,f_lelang)==1)
	{
		printf("Nama Lelang\t: %s\n",lelang.nama);
		printf("Deskripsi\t: %s\n",lelang.deskripsi);
   		printf("Harga Awal\t: %d\n",lelang.hargaAwal);
		printf("Bid tertinggi: %d\n",lelang.bid);
    	printf("Tanggal Akhir\t: %d\n\n",lelang.tgl);
	}
	fclose(f_lelang);
	printf("Apakah Anda ingin Melelang? [y/n] ");scanf("%c",&yn);getchar();
	if(yn=='y')
	{
		sorting();
		membid();
	}
	else if(yn=='n') 
	{
		getchar();
		system("cls");
	}
	menuMember();
}

void sorting()
{
	int i=0,j=0,n;
	f_lelang=fopen("Lelang.txt","rb");
	while(fread(&lelang,sizeof(lelang),1,f_lelang)==1)
	{
		strcpy(temp[i].nama,lelang.nama);
		strcpy(temp[i].deskripsi,lelang.deskripsi);
		temp[i].hargaAwal=lelang.hargaAwal;
		strcpy(temp[i].muname,lelang.muname);
		temp[i].bid=lelang.bid;
		temp[i].tgl=lelang.tgl;
		i++;
		n=i;
	}
//Bubble Sorting
	fclose(f_lelang);
	i=0;j=0;
	for(i=n-1;i>=1;i--){
		for(j=1;j<=i;j++)
		{
			if(temp[j-1].tgl>temp[j].tgl)
			{
				temp2=temp[j-1];
				temp[j-1]=temp[j];
				temp[j]=temp2;
			}
		}
	}
//Menampilkan Hasil Sorting
	printf("\n===SORTED LIST===\n\n");
	for(i=0;i<n;i++)
	{
		printf("Nama Lelang\t: %s\n",temp[i].nama);
		printf("Deskripsi\t: %s\n",temp[i].deskripsi);
   		printf("Harga Awal\t: %d\n",temp[i].hargaAwal);
   		printf("Bid Tertinggi\t: %d\n",temp[i].bid);
    	printf("Tanggal Akhir\t: %d\n\n",temp[i].tgl);
	}
	getchar();
}

//Penawaran oleh Member
void membid()
{
	i=0;
	f_lelang=fopen("Lelang.txt","rb+");
	f_member=fopen("Member.txt","rb+");
	printf("\n\n===BIDDING SYSTEM===\n\n");
	printf("Nama Barang\t\t: ");gets(input);
	printf("Masukkan Tawaran\t: ");scanf("%d",&bid);getchar();
	while(fread(&lelang,sizeof(lelang),1,f_lelang)==1)
	{
		if(strcmp(input,lelang.nama)==0 && bid>lelang.bid)
		{
			i=1;
			fseek(f_lelang, -sizeof(lelang), SEEK_CUR);
			strcpy(lelang.nama,input);
			strcpy(lelang.muname,uname);
			lelang.bid=bid;
			fwrite(&lelang,sizeof(lelang),1,f_lelang);
			break;
		}
	}
	fclose(f_lelang);
	if(i==1){
		while(fread(&mem, sizeof(mem), 1, f_member)==1){
			if(strcmp(uname, mem.muname)==0){
				fseek(f_member, -sizeof(mem), SEEK_CUR);
				strcpy(mem.lelangIkut,input);
				mem.bid=bid;
				fwrite(&mem, sizeof(mem), 1, f_member);
				break;
			}
		}
		fclose(f_member);
		printf("Berhasil Bid ke %s\n",input);
	}else
	{
		printf("Lelang tidak ada atau bid harus lebih besar dari saat ini");
	}
	getchar();
	system("cls");
	menuMember();
}

//Tawaran yang Dimenangkan Member
void memwin()
{
	i=0;
	f_menang=fopen("Menang.txt","rb");
	printf("\t\t Daskom Auction Center\n");
	printf("\t\t  ---DAS'Auction---\n");
	while(fread(&menang,sizeof(menang),1,f_menang)==1){
		if(strcmp(uname,menang.muname)==0){
			printf("%d. Nama Barang\t: %s\n",i+1,mem.lelangIkut);
			printf("   Tawaran\t: %d\n\n",mem.bid);
			i++;
		}
	}
	fclose(f_menang);
	if(i==0) printf("Anda belum menang apapun\n");
	getchar();
	system("cls");
	menuMember();
}
