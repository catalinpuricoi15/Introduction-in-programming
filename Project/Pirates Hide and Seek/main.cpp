#include <bits/stdc++.h>
#include <graphics.h>
#include <winbgim.h>
#include <MMSystem.h>
#define APASAT 1
#define RELAXAT 2
using namespace std;
char Meniu_text[][20]= {"PIRATES HIDE'N SEEK","START","REGULI","SETARI","IESIRE"}, Start_text[80][50], Titlul[10];
char Sterge_piese[9][40];
char Folder_provocare[40],Folder_scor[40],Nume_jucatori[30][20];
struct Setari_date
{
    int culoare;
    int sunet;
}Seteaza;
struct Matrici
{
    int x1,y1,x2,y2;
    char poza[30];
} patratele_tabla[10][10]; //patrat, cele 9 patratele din patrat
struct Timp
{
    int minut;
    int secunda;
    char Text[20];
}Cronometru;
struct Provocare_nivel
{
    int numar_imagini;
    char nume_imagine[8][30];
}Provocare[62];
struct buton
{
    char text[50];
    int marime;
    int x,y;
    int x1,y1,x2,y2;
} Meniu_butoane[10], Start_butoane[80], Nivel_butoane[20],Setari_butoane[20],Scor[3],Selectie_Jucator_butoane[31][20];
struct Patrate
{
    int x1,y1,x2,y2, latura;
    bool ocupat;
} Patrat[9], Fundal_provocare;
struct coordonate_bar
{
    int x1, y1, x2, y2;
};
struct piese
{
    int latura;
    int stare;
    int patrat; //patratul in care se afla piesa
    int patrat_liber[5][3]; //stare,cate patratele libere
    char Poza[9][5][40]; //patrat,stare,numele pozei
    coordonate_bar Adaug[4][4]; //in functie de coordonatele de inceput, cat trebuie sa adaug sa obtin piesa care are o stare si e impartitata in 3 sub_piese
    coordonate_bar Stare[4][4]; //in functie de coordonatele de inceput, coordonatele fiecarei bucati din piesa da prima fiind starea si a doua fiind numarul sub_piesei
} Piesa[5];
struct Sageata
{
    int x1,y1,x2,y2;
    int cap[7];
} sageata[10];
struct Pagini
{
    int Nr_Pagini;
    int Nr_Butoane;
    int Nr_Butoane_pe_Pagina[50];
}Selectie_Jucator;
struct date_jucator
{
    int Niveluri;
    int Primul;
    int Cel_Mai_Bun;
}Date_jucator[65];

void Grafica_Selectare_Jucator(int L,int H);
void Init_Provocari(int LatimeEcran,int InaltimeEcranEcran);
void Init_Selectare_Jucator(int L,int H);
void Init_Text(buton& b, char text0[50], int x0, int y0, int m0);
void Deseneaza_Buton(buton b, int stil,int bkcolor,int text_color);
void ceas(int LatimeEcran, int InaltimeEcran);
void Butoane(int LatimeEcran, int InaltimeEcran);
void Titlu(int mijL, int Imax, int mijI);
void Grafica_meniu(int LatimeEcran, int InaltimeEcran);
void Meniu(int LatimeEcran, int InaltimeEcran);

void Init_Selectare_Jucator(int LatimeEcran, int InaltimeEcran);
void Grafica_Selectare_Jucator(int LatimeEcran, int InaltimeEcran);
void Selectare_Jucator(int LatimeEcran, int InaltimeEcran, int Nr_pagina);
void Citire_Tastatura(char text[200], int x, int y, int culoareFundal, int culoareText);
void Init_Sageata(int x_sg, int y_sg,int l_sg, int h_sg,int numar);
void Deseneaza_Sageata(int LatimeEcran,int InaltimeEcran,int numar);
void Grafica_Start(int LatimeEcran, int InaltimeEcran,int NrPagina);
void Start(int LatimeEcran, int InaltimeEcran,int Nr_Pagina,char Jucator[20]);

void Grafica_Setari(int LatimeEcran,int InaltimeEcran);
void Setari(int LatimeEcran,int InaltimeEcran);
void Reguli(int LatimeEcran, int InaltimeEcran);

void Genereaza_Nivel(int LatimeEcran,int InaltimeEcran);
void Dimeniune_Patrate(int LatimeEcran, int InaltimeEcran, int &sus, int &stanga, int &numar, int &latura);
void Grila_Patrat(int sus, int stanga, int latura,int numar);
void Bordare_Patrat(int stanga, int sus, int latura, int culoare);
void Grafica_Piesa(int LatimeEcran,int InaltimeEcran, int piesa, int patrat, int stare);
void Init_Piese(int LatimeEcran, int InaltimeEcran);
void Init_tabla(int LatimeEcran, int InaltimeEcran);
void Grafica_Nivel(int LatimeEcran, int InaltimeEcran, int nivel_actual, char Jucator[20]);
void Verificare_Niveluri(int LatimeEcran,int InaltimeEcran,char Jucator[20]);
void Deseneaza_Provocare(int LatimeEcran, int InaltimeEcran,int numar_imagini,int nivel_actual);
void Mutari_Nivel(int numar_mutari);
void Nivel(int LatimeEcran, int InaltimeEcran,int nivel_actual,char Jucator[20]);
void Cronometru_tabla(int LatimeEcran, int InaltimeEcran,int minut, int secunda);

int main()
{
    DWORD LatimeEcran= GetSystemMetrics(SM_CXSCREEN);
    DWORD InaltimeEcran= GetSystemMetrics(SM_CYSCREEN);
    initwindow(LatimeEcran, InaltimeEcran,"", -3, -3);
    Seteaza.sunet=1;
    Seteaza.culoare=COLOR(255, 204, 102);
    Init_Piese(LatimeEcran, InaltimeEcran);
    Butoane(LatimeEcran, InaltimeEcran);
    Init_Provocari(LatimeEcran, InaltimeEcran);
    char* WAV = "Muzica/Fundal_meniu.wav";
    if(Seteaza.sunet==1)
    sndPlaySound(WAV, SND_ASYNC);
    Meniu(LatimeEcran, InaltimeEcran);
    getch();
    closegraph();

    return 0;
}
void Titlu(int mijL, int Imax, int mijI)
{
    setcolor(WHITE);
    setbkcolor(BLACK);
    settextjustify(1,2);
    settextstyle(8,HORIZ_DIR, 8);
    outtextxy(mijL,Imax-mijI*(4)-50,Meniu_text[0]);
}
void Init_Text(buton& b, char text0[50], int x0, int y0, int m0)
{
    strcpy(b.text,text0);
    b.x=x0;
    b.y=y0;
    b.marime=m0;
    settextstyle(SIMPLEX_FONT,HORIZ_DIR,b.marime);
    b.x1=x0-textwidth(b.text)/2-5;
    b.x2=x0+textwidth(b.text)/2+5;
    b.y1=y0-textheight(b.text)/2-5;
    b.y2=y0+textheight(b.text)/2+5;
}
void Butoane(int LatimeEcran, int InaltimeEcran)
{
    //Meniu
    int mijL=LatimeEcran/2, mijI=InaltimeEcran/6;
    for(int i=1; i<5; i++)
        Init_Text(Meniu_butoane[i],Meniu_text[i],mijL,InaltimeEcran-mijI*(5-i),4);
    //Start
    int nr_butoane=0, dist_butoane=0;
    mijL=LatimeEcran/4, mijI=InaltimeEcran/4;
    strcpy(Start_text[0],"Meniu");
    strcpy(Titlul,"Nivel ");
    char c_z[2], c_u[2];
    c_z[1]='\0';
    c_u[1]='\0';
    for(int i=1; i<=60; i++)
    {
        strcat(Start_text[i],Titlul);
        if(i>9)
        {
            c_z[0]=char(i/10+'0');
            strcat(Start_text[i],c_z);
        }
        c_u[0]=char(i%10+'0');
            strcat(Start_text[i],c_u);
    }
    Init_Text(Start_butoane[nr_butoane],Start_text[nr_butoane],150,150,4);
    for(int k=1; k<8; k++)
        for(int i=1; i<4; i++)
            for(int j=1; j<4; j++)
                nr_butoane++, Init_Text(Start_butoane[nr_butoane],Start_text[nr_butoane],LatimeEcran-mijL*(4-j),InaltimeEcran-mijI*(4-i),4);
    nr_butoane-=3;

    dist_butoane=90;
    for(int i=1; i<=7; i++)
    {
        c_u[0]=char(i+'0');
        strcat(Start_text[i+60],"  ");
        strcat(Start_text[i+60],c_u);
        strcat(Start_text[i+60],"  ");
        Init_Text(Start_butoane[i+60],Start_text[i+60],LatimeEcran/2-dist_butoane*4+dist_butoane*i,InaltimeEcran-mijI/2,4);
    }
    nr_butoane+=8;
    Init_Text(Start_butoane[nr_butoane],"Genereaza nivel",LatimeEcran/2,InaltimeEcran-mijI/4-mijI,4);

    //Setari
    int nr=0;
    int dist_inaltime=200;
    dist_butoane=100;
    nr_butoane=0;
    mijL=LatimeEcran/2;
    mijI=InaltimeEcran/2;
    char Setari_text[][30]={"Sunet:", "Pornit", "Oprit", "Culori_butoane:","Bej","Rosu","Mov"};

    Init_Text(Setari_butoane[nr],Setari_text[nr],mijL-dist_butoane*2,mijI-dist_inaltime/2,6),nr++;
    for(int i=nr; i<=nr+1; i++)
        Init_Text(Setari_butoane[i],Setari_text[i],Setari_butoane[i-1].x2+dist_butoane,Setari_butoane[i-1].y,5);
    nr=nr+2;
    Init_Text(Setari_butoane[nr],Setari_text[nr],mijL-dist_butoane*3,mijI+dist_inaltime/2,6),nr++;
    for(int i=nr; i<=nr+2; i++)
        Init_Text(Setari_butoane[i],Setari_text[i],Setari_butoane[i-1].x2+dist_butoane,Setari_butoane[i-1].y,5);

    //Nivel
    char Nivel_text[][20]= {"Start","Next Level","Provocare","BRAVOOO(^_^)"};
    int numar, sus, stanga, sus_inceput, stanga_inceput, latura;
    Dimeniune_Patrate(LatimeEcran, InaltimeEcran, sus_inceput, stanga_inceput, numar, latura);
    sus=sus_inceput+latura*3+latura/2;
    stanga=stanga_inceput-latura*3-latura/2;
    Init_Text(Nivel_butoane[0],Nivel_text[0],stanga,sus,4);

    for(int i=1; i<=3; i=i+2)
    {
    sus=sus_inceput+latura*3+latura/2;
    stanga=stanga_inceput+latura*10+latura/2;
    Init_Text(Nivel_butoane[i],Nivel_text[i],stanga,sus,4);
    }

    sus=sus_inceput+latura*8+latura/2+15;
    stanga=stanga_inceput+latura*3+latura/2;
    Init_Text(Nivel_butoane[2],Nivel_text[2],stanga,sus,4);
}
void Deseneaza_Buton(buton b, int stil,int bkcolor,int text_color)
{
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, b.marime);
    setcolor(bkcolor);
    setfillstyle(SOLID_FILL,bkcolor);
    bar(b.x1,b.y1,b.x2,b.y2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    if (stil==RELAXAT)
    {
        setbkcolor(bkcolor);
        setcolor(text_color);
        outtextxy((b.x1+b.x2)/2,(b.y1+b.y2)/2+2,b.text);
        setcolor(bkcolor);
        line(b.x1+1,b.y2+1,b.x2+1,b.y2+1);
        line(b.x2+1,b.y1+1,b.x2+1,b.y2+1);
    }
    else
    {
        setbkcolor(bkcolor);
        setcolor(text_color);
        outtextxy((b.x1+b.x2)/2+2,(b.y1+b.y2)/2+4,b.text);
        setcolor(bkcolor);
        line(b.x1-1,b.y1-1,b.x2-1,b.y1-1);
        line(b.x1-1,b.y1-1,b.x1-1,b.y2-1);
    }
}
void Init_Sageata(int x_sg, int y_sg,int l_sg, int h_sg,int numar)
{
    int acopera=10;
    if(l_sg<0)
        acopera=-10;
    sageata[numar]={x_sg,y_sg-h_sg,x_sg+l_sg+acopera,y_sg+h_sg};
    sageata[numar].cap[0]=x_sg+l_sg;
    sageata[numar].cap[1]=y_sg-2*h_sg;
    sageata[numar].cap[2]=x_sg+l_sg+2*h_sg;
    sageata[numar].cap[3]=y_sg;
    sageata[numar].cap[4]=x_sg+l_sg;
    sageata[numar].cap[5]=y_sg+2*h_sg;
}
void Deseneaza_Sageata(int LatimeEcran,int InaltimeEcran,int numar)
{
    setfillstyle(SOLID_FILL,Seteaza.culoare);
    fillpoly(3,sageata[numar].cap);
    setfillstyle(SOLID_FILL,Seteaza.culoare);
    bar(sageata[numar].x1,sageata[numar].y1,sageata[numar].x2,sageata[numar].y2);
}
void Dimeniune_Patrate(int LatimeEcran, int InaltimeEcran, int &sus, int &stanga, int &numar, int &latura)
{
    int width, height;
    width=height=290;
    numar=3;
    latura=width/numar;
    sus=InaltimeEcran/2-latura-height;
    stanga=LatimeEcran/2-latura/2-width;
}
void Grafica_meniu(int LatimeEcran, int InaltimeEcran)
{
    int mijL=LatimeEcran/2, mijI=InaltimeEcran/5;
    readimagefile("Imagini/fundal_meniu.jpg",0,0,LatimeEcran,InaltimeEcran);
    Titlu( mijL,InaltimeEcran,mijI);
    for(int i=1; i<=4; i++)
        Deseneaza_Buton(Meniu_butoane[i],RELAXAT,Seteaza.culoare,BLACK);
}
void Meniu(int LatimeEcran, int InaltimeEcran)
{
    int x, y, ok=0 ;
    Grafica_meniu(LatimeEcran,InaltimeEcran);
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(Meniu_butoane[1].x1<=x && x<=Meniu_butoane[1].x2 && Meniu_butoane[1].y1<=y && y<=Meniu_butoane[1].y2)
            {
                Deseneaza_Buton(Meniu_butoane[1],APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Meniu_butoane[1],RELAXAT,Seteaza.culoare,BLACK);

                if(Selectie_Jucator.Nr_Butoane>0)
                {
                ofstream g("Numar_jucatori.txt");
                g<<Selectie_Jucator.Nr_Butoane-1<<'\n';
                for(int i=1; i<Selectie_Jucator.Nr_Butoane; i++)
                    g<<Nume_jucatori[i]<<'\n';
                g.close();
                }

                ifstream f("Numar_jucatori.txt");
                f>>Selectie_Jucator.Nr_Butoane;
                f.get();
                for(int i=1; i<=Selectie_Jucator.Nr_Butoane; i++)
                    f.getline(Nume_jucatori[i],20);
                Selectie_Jucator.Nr_Butoane+=1;
                f.close();

                Selectare_Jucator(LatimeEcran,InaltimeEcran,1);
            }
            if(Meniu_butoane[2].x1<=x && x<=Meniu_butoane[2].x2 && Meniu_butoane[2].y1<=y && y<=Meniu_butoane[2].y2)
            {
                Deseneaza_Buton(Meniu_butoane[2],APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Meniu_butoane[2],RELAXAT,Seteaza.culoare,BLACK);
                Reguli(LatimeEcran, InaltimeEcran);
                ok=1;
            }
            if(Meniu_butoane[3].x1<=x && x<=Meniu_butoane[3].x2 && Meniu_butoane[3].y1<=y && y<=Meniu_butoane[3].y2)
            {
                Deseneaza_Buton(Meniu_butoane[3],APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Meniu_butoane[3],RELAXAT,Seteaza.culoare,BLACK);
                setbkcolor(BLACK);
                cleardevice();
                Setari(LatimeEcran,InaltimeEcran);
                ok=1;
            }
            if(Meniu_butoane[4].x1<=x && x<=Meniu_butoane[4].x2 && Meniu_butoane[4].y1<=y && y<=Meniu_butoane[4].y2)
            {
                Deseneaza_Buton(Meniu_butoane[4],APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Meniu_butoane[4],RELAXAT,Seteaza.culoare,BLACK);
                 if(Selectie_Jucator.Nr_Butoane>0)
                {
                ofstream g("Numar_jucatori.txt");
                g<<Selectie_Jucator.Nr_Butoane-1<<'\n';
                for(int i=1; i<Selectie_Jucator.Nr_Butoane; i++)
                    g<<Nume_jucatori[i]<<'\n';
                g.close();
                }

                exit(0);
            }
        }

    }
    while (ok==0);
}
void Reguli(int LatimeEcran, int InaltimeEcran)
{
    int x,y;
    int finall=0;
    int colt_sx, colt_sy, colt_dx, colt_dy,dist, nivel;
    buton Buton_meniu;
    dist=80;
    colt_sx=colt_sy=dist;
    colt_dx=LatimeEcran-dist;
    colt_dy=InaltimeEcran-dist;
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,0,LatimeEcran,InaltimeEcran);
    readimagefile("Imagini/fundal_reguli.jpg",colt_sx,colt_sy,colt_dx,colt_dy);

    settextstyle(10,HORIZ_DIR,7);
    setbkcolor(BLACK);
    setcolor(WHITE);
    outtextxy((colt_sx+colt_dx)/2,colt_sy/2+20,"BINE ATI VENIT IN TINUTUL PIRATILOR");
    Init_Text(Buton_meniu,"Meniu",(colt_sx+colt_dx)/2,colt_dy+(InaltimeEcran-colt_dy)/2,4);
    Deseneaza_Buton(Buton_meniu,RELAXAT,Seteaza.culoare,BLACK);

    char text[15][256];
    ifstream f("sir_reguli.txt");
    for(int i=0; i<15; i++)
        f.getline(text[i],256);
    f.close();

    nivel=250;
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setbkcolor(COLOR(234,205,145));
    settextstyle(10,HORIZ_DIR,2);
    setcolor(BLACK);
    for(int i=0; i<15; i++)
    {
        outtextxy(LatimeEcran/2,nivel,text[i]);
        nivel+=50;
    }
    while(finall==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(Buton_meniu.x1<=x && x<=Buton_meniu.x2 && Buton_meniu.y1<=y && y<=Buton_meniu.y2)
            {
                Deseneaza_Buton(Buton_meniu,APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Buton_meniu,RELAXAT,Seteaza.culoare,BLACK);
                finall=1;
                Meniu(LatimeEcran,InaltimeEcran);
            }
        }
    }
}
void Grafica_Setari(int LatimeEcran,int InaltimeEcran)
{
    Deseneaza_Buton(Setari_butoane[0],RELAXAT,BLACK,WHITE);
    Deseneaza_Buton(Setari_butoane[3],RELAXAT,BLACK,WHITE);
    for(int i=1; i<=2; i++)
    Deseneaza_Buton(Setari_butoane[i],RELAXAT,Seteaza.culoare,BLACK);
     for(int i=4; i<=6; i++)
    Deseneaza_Buton(Setari_butoane[i],RELAXAT,Seteaza.culoare,BLACK);

    Deseneaza_Buton(Start_butoane[0],RELAXAT,Seteaza.culoare,BLACK);
}
void Setari(int LatimeEcran,int InaltimeEcran)
{
   Grafica_Setari(LatimeEcran, InaltimeEcran);
   int x,y,ok;
   do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(Start_butoane[0].x1<=x && x<=Start_butoane[0].x2 && Start_butoane[0].y1<=y && y<=Start_butoane[0].y2)
            {
                Deseneaza_Buton(Start_butoane[0],APASAT,Seteaza.culoare,BLACK); delay(250);
                Deseneaza_Buton(Start_butoane[0],RELAXAT,Seteaza.culoare,BLACK);
                ok=1;
                Meniu(LatimeEcran,InaltimeEcran);
            }
            if(Setari_butoane[1].x1<=x && x<=Setari_butoane[1].x2 && Setari_butoane[1].y1<=y && y<=Setari_butoane[1].y2)
            {
                Deseneaza_Buton(Setari_butoane[1],APASAT,Seteaza.culoare,BLACK); delay(250);
                Deseneaza_Buton(Setari_butoane[1],RELAXAT,Seteaza.culoare,BLACK);
                Seteaza.sunet=1;
                char* WAV = "Muzica/Fundal_start.wav";
                sndPlaySound(WAV, SND_ASYNC);
                continue;
            }
             if(Setari_butoane[2].x1<=x && x<=Setari_butoane[2].x2 && Setari_butoane[2].y1<=y && y<=Setari_butoane[2].y2)
            {
                Deseneaza_Buton(Setari_butoane[2],APASAT,Seteaza.culoare,BLACK); delay(250);
                Deseneaza_Buton(Setari_butoane[2],RELAXAT,Seteaza.culoare,BLACK);
                Seteaza.sunet=2;
                PlaySound(0, 0, 0);
                continue;
            }
            for(int i=4; i<=6; i++)
            if(Setari_butoane[i].x1<=x && x<=Setari_butoane[i].x2 && Setari_butoane[i].y1<=y && y<=Setari_butoane[i].y2)
            {
                Deseneaza_Buton(Setari_butoane[i],APASAT,Seteaza.culoare,BLACK); delay(250);
                Deseneaza_Buton(Setari_butoane[i],RELAXAT,Seteaza.culoare,BLACK);
                if(i==4)
                Seteaza.culoare=COLOR(255, 204, 102);
                if(i==5)
                Seteaza.culoare=RED;
                if(i==6)
                Seteaza.culoare=MAGENTA;
                Grafica_Setari(LatimeEcran,InaltimeEcran);
                break;
            }
        }

    }
    while(ok==0);
}
void Init_Selectare_Jucator(int LatimeEcran, int InaltimeEcran)
{
    int Numar_jucatori;
    int Numar_pagini;
    int mijL,mijI;
    int contor=0;
    int Nr_Butoane;
    strcpy(Nume_jucatori[Selectie_Jucator.Nr_Butoane],"Jucator nou");
    Nr_Butoane=Selectie_Jucator.Nr_Butoane;
    Selectie_Jucator.Nr_Pagini=Selectie_Jucator.Nr_Butoane/5;
    if(Selectie_Jucator.Nr_Butoane%5!=0)
        Selectie_Jucator.Nr_Pagini++;
    mijL=LatimeEcran/2;
    for(int k=1; k<=Selectie_Jucator.Nr_Pagini; k++)
    {
        if(Nr_Butoane>5)
            Selectie_Jucator.Nr_Butoane_pe_Pagina[k] = 5, mijI= 6;
        else
            Selectie_Jucator.Nr_Butoane_pe_Pagina[k] = Nr_Butoane, mijI=Nr_Butoane;
        for(int i=1; i<=Selectie_Jucator.Nr_Butoane_pe_Pagina[k]; i++)
            contor++, Init_Text(Selectie_Jucator_butoane[k][i],Nume_jucatori[contor],LatimeEcran/2,InaltimeEcran-(InaltimeEcran/(Selectie_Jucator.Nr_Butoane_pe_Pagina[k]+1))*(Selectie_Jucator.Nr_Butoane_pe_Pagina[k]+1-i),4);
        Nr_Butoane-=5;
    }
    Init_Sageata(LatimeEcran-180,InaltimeEcran/2,90,25,3);
    Init_Sageata(180,InaltimeEcran/2,-90,-25,4);
}
void Grafica_Selectare_Jucator(int LatimeEcran, int InaltimeEcran,int Nr_Pagina)
{
    readimagefile("Imagini/fundal_start.jpg",0,0,LatimeEcran,InaltimeEcran);
    Deseneaza_Buton(Start_butoane[0],RELAXAT,Seteaza.culoare,BLACK);
    for(int i=1; i<=Selectie_Jucator.Nr_Butoane_pe_Pagina[Nr_Pagina]; i++)
        Deseneaza_Buton(Selectie_Jucator_butoane[Nr_Pagina][i],RELAXAT,Seteaza.culoare,BLACK);
    if(Nr_Pagina<Selectie_Jucator.Nr_Pagini)
    Deseneaza_Sageata(LatimeEcran,InaltimeEcran,3);
    if(Nr_Pagina>1)
    Deseneaza_Sageata(LatimeEcran,InaltimeEcran,4);
}
void Selectare_Jucator(int LatimeEcran, int InaltimeEcran, int Nr_Pagina)
{
    int finall=0,x,y;
    Init_Selectare_Jucator(LatimeEcran,InaltimeEcran);
    Grafica_Selectare_Jucator(LatimeEcran,InaltimeEcran,Nr_Pagina);
    while(finall==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(Start_butoane[0].x1<=x && x<=Start_butoane[0].x2 && Start_butoane[0].y1<=y && y<Start_butoane[0].y2)
            {
                Deseneaza_Buton(Start_butoane[0],APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Start_butoane[0],RELAXAT,Seteaza.culoare,BLACK);
                Meniu(LatimeEcran,InaltimeEcran);
            }
            if( Nr_Pagina<Selectie_Jucator.Nr_Pagini && ((sageata[3].x1<=x && sageata[3].x2>=x && sageata[3].y1<=y && sageata[3].y2>=y)
                    || ((sageata[3].cap[0]<=x && x<=sageata[3].cap[2]) && ((sageata[3].cap[1]<=y && y<=sageata[3].cap[3] && y-sageata[3].cap[1]>=x-sageata[3].cap[0]) || (sageata[3].cap[3]<=y && y<=sageata[3].cap[5] && x+y<=sageata[3].cap[4]+sageata[3].cap[5]))))) //de avut grija caci coordonatele sunt diferite si nu respecta fara anumite artificii proprietatile diagonalei matricii
            {
                setbkcolor(BLACK);
                cleardevice();
                finall=1;
                Selectare_Jucator(LatimeEcran,InaltimeEcran,Nr_Pagina+1);
                continue;
            }
            if( Nr_Pagina>1 && ( (sageata[4].x2<=x && x<=sageata[4].x1 && sageata[4].y2<=y && y<=sageata[4].y1)
                                 || ((sageata[4].cap[2]<=x && x<=sageata[4].cap[4]) && ((sageata[4].cap[5]<=y && y<=sageata[4].cap[3] && x+y>=sageata[4].cap[2]+sageata[4].cap[3]) || (sageata[4].cap[3]<=y && y<=sageata[4].cap[1] && y-sageata[4].cap[3]<=x-sageata[4].cap[2])))))
            {
                setbkcolor(BLACK);
                cleardevice();
                finall=1;
                Selectare_Jucator(LatimeEcran,InaltimeEcran,Nr_Pagina-1);
                continue;
            }
            int i=Selectie_Jucator.Nr_Butoane_pe_Pagina[Selectie_Jucator.Nr_Pagini];
            if(Selectie_Jucator_butoane[Selectie_Jucator.Nr_Pagini][i].x1<=x && x<=Selectie_Jucator_butoane[Selectie_Jucator.Nr_Pagini][i].x2 && Selectie_Jucator_butoane[Selectie_Jucator.Nr_Pagini][i].y1<=y && y<=Selectie_Jucator_butoane[Selectie_Jucator.Nr_Pagini][i].y2)
            {
                char Nume[20];
                Deseneaza_Buton(Selectie_Jucator_butoane[Nr_Pagina][i],APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Selectie_Jucator_butoane[Nr_Pagina][i],RELAXAT,Seteaza.culoare,BLACK);

                setfillstyle(SOLID_FILL,Seteaza.culoare);
                bar(Selectie_Jucator_butoane[Nr_Pagina][i].x1,Selectie_Jucator_butoane[Nr_Pagina][i].y1-4,Selectie_Jucator_butoane[Nr_Pagina][i].x2,Selectie_Jucator_butoane[Nr_Pagina][i].y2);

                Citire_Tastatura(Nume,Selectie_Jucator_butoane[Nr_Pagina][i].x,Selectie_Jucator_butoane[Nr_Pagina][i].y, Seteaza.culoare,BLACK);
                if(strlen(Nume)>1)
                {
                    strcpy(Nume_jucatori[Selectie_Jucator.Nr_Butoane],Nume);
                    Selectie_Jucator.Nr_Butoane+=1;
                    char fisier_txt[30];
                    strcpy(fisier_txt,"Selectie_Jucator/");
                    strcat(fisier_txt,Nume);
                    strcat(fisier_txt,".txt");
                    ofstream g(fisier_txt);
                    g<<1<<' '<<0<<' '<<0;
                    g.close();

                    Init_Selectare_Jucator(LatimeEcran, InaltimeEcran);
                    Grafica_Selectare_Jucator(LatimeEcran,InaltimeEcran,Nr_Pagina);
                }
                else
                    Deseneaza_Buton(Selectie_Jucator_butoane[Selectie_Jucator.Nr_Pagini][Selectie_Jucator.Nr_Butoane_pe_Pagina[Selectie_Jucator.Nr_Pagini]],RELAXAT,Seteaza.culoare,BLACK);
            }
            else
            {
                for(int i=1; i<=Selectie_Jucator.Nr_Butoane_pe_Pagina[Nr_Pagina]; i++)
                {
                    if(Selectie_Jucator_butoane[Nr_Pagina][i].x1<=x && x<=Selectie_Jucator_butoane[Nr_Pagina][i].x2 && Selectie_Jucator_butoane[Nr_Pagina][i].y1<=y && y<=Selectie_Jucator_butoane[Nr_Pagina][i].y2)
                    {
                        Deseneaza_Buton(Selectie_Jucator_butoane[Nr_Pagina][i],APASAT,Seteaza.culoare,BLACK), delay(250);
                        Deseneaza_Buton(Selectie_Jucator_butoane[Nr_Pagina][i],RELAXAT,Seteaza.culoare,BLACK);
                        char fisier_txt[30];
                        strcpy(fisier_txt,"Selectie_Jucator/");
                        strcat(fisier_txt,Selectie_Jucator_butoane[Nr_Pagina][i].text);
                        strcat(fisier_txt,".txt");
                        Verificare_Niveluri(LatimeEcran,InaltimeEcran,fisier_txt);
                        Start(LatimeEcran,InaltimeEcran,1,fisier_txt);
                        finall=1;
                        break;
                        continue;
                    }
                }
            }
        }
    }
}
void Citire_Tastatura(char text[200], int x, int y, int culoareFundal, int culoareText)
{
    char tasta, sir[2];
    sir[1]='\0';
    char text_[200];
    strcpy(text,"");
    strcpy(text_,"_");
    setbkcolor(culoareFundal);
    setcolor(culoareText);
    outtextxy(x,y,text_);
    do
    {
        tasta=getch();
        if (tasta==8 && strlen(text)>0)
        {
            setbkcolor(culoareFundal);
            strcpy(text_,text);
            strcat(text_,"_");
            setcolor(culoareFundal);
            outtextxy(x,y,text_);
            text[strlen(text)-1]='\0';
            strcpy(text_,text);
            strcat(text_,"_");
            setcolor(culoareText);
            outtextxy(x,y,text_);
        }
        if (tasta>=32 && tasta<=127 && strlen(text)<=8)
        {
            setbkcolor(culoareFundal);
            strcpy(text_,text);
            strcat(text_,"_");
            setcolor(culoareFundal);
            outtextxy(x,y,text_);
            text_[strlen(text_)-1]='\0';
            sir[0]=tasta;
            setcolor(culoareText);
            strcat(text,sir);
            strcpy(text_,text);
            strcat(text_,"_");
            outtextxy(x,y,text_);
        }
    }
    while (tasta!=13);
}
void Grafica_Start(int LatimeEcran, int InaltimeEcran, int Nr_Pagina)
{
    readimagefile("Imagini/Fundal_Jucator.jpg",0,0,LatimeEcran,InaltimeEcran);

    Init_Sageata(LatimeEcran-180,InaltimeEcran/2,90,25,1);
    Init_Sageata(0+180,InaltimeEcran/2,-90,-25,2);
    Deseneaza_Buton(Start_butoane[0],RELAXAT,Seteaza.culoare,BLACK);
    for(int i=1+9*(Nr_Pagina-1); i<=9+9*(Nr_Pagina-1); i++)
    {
        if(Date_jucator[i].Niveluri==0)
        Deseneaza_Buton(Start_butoane[i],RELAXAT,Seteaza.culoare,BLACK);
        else
        Deseneaza_Buton(Start_butoane[i],RELAXAT,GREEN,BLACK);
    }
    for(int i=61; i<=67; i++)
        Deseneaza_Buton(Start_butoane[i],RELAXAT,Seteaza.culoare,BLACK);
    if(Nr_Pagina==7)
        Deseneaza_Buton(Start_butoane[68],RELAXAT,Seteaza.culoare,BLACK);
    if(Nr_Pagina<7)
    Deseneaza_Sageata(LatimeEcran,InaltimeEcran,1);
    if(Nr_Pagina>1)
    Deseneaza_Sageata(LatimeEcran,InaltimeEcran,2);
}
void Start(int LatimeEcran, int InaltimeEcran, int Nr_Pagina,char Jucator[20])
{
    int x, y, ok=0;
    Grafica_Start(LatimeEcran,InaltimeEcran,Nr_Pagina);
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(Start_butoane[0].x1<=x && x<=Start_butoane[0].x2 && Start_butoane[0].y1<=y && y<=Start_butoane[0].y2)
            {
                Deseneaza_Buton(Start_butoane[0],APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Start_butoane[0],RELAXAT,Seteaza.culoare,BLACK);
                setbkcolor(BLACK);
                cleardevice();
                ok=1;
                ofstream g(Jucator);
                for(int i=1; i<=60; i++)
                    if(Date_jucator[i].Niveluri==1)
                        g<<i<<' '<<Date_jucator[i].Primul<<' '<<Date_jucator[i].Cel_Mai_Bun<<'\n';
                g.close();
                PlaySound(0, 0, 0);
                delay(20);
                char* WAV = "Muzica/Fundal_meniu.wav";
                if(Seteaza.sunet==1)
                sndPlaySound(WAV, SND_ASYNC);
                Meniu(LatimeEcran,InaltimeEcran);
                continue;
            }
            if( Nr_Pagina<7 && ((sageata[1].x1<=x && sageata[1].x2>=x && sageata[1].y1<=y && sageata[1].y2>=y)
                             || ((sageata[1].cap[0]<=x && x<=sageata[1].cap[2]) && ((sageata[1].cap[1]<=y && y<=sageata[1].cap[3] && y-sageata[1].cap[1]>=x-sageata[1].cap[0]) || (sageata[1].cap[3]<=y && y<=sageata[1].cap[5] && x+y<=sageata[1].cap[4]+sageata[1].cap[5]))))) //de avut grija caci coordonatele sunt diferite si nu respecta fara anumite artificii proprietatile diagonalei matricii
            {
                if(Nr_Pagina==6)
                {
                setbkcolor(BLACK);
                cleardevice();
                }
                Start(LatimeEcran,InaltimeEcran,Nr_Pagina+1,Jucator);
                ok=1;
                continue;
            }
            if( Nr_Pagina>1 && ( (sageata[2].x2<=x && x<=sageata[2].x1 && sageata[2].y2<=y && y<=sageata[2].y1)
                              || ((sageata[2].cap[2]<=x && x<=sageata[2].cap[4]) && ((sageata[2].cap[5]<=y && y<=sageata[2].cap[3] && x+y>=sageata[2].cap[2]+sageata[2].cap[3]) || (sageata[2].cap[3]<=y && y<=sageata[2].cap[1] && y-sageata[2].cap[3]<=x-sageata[2].cap[2])))))
            {
                if(Nr_Pagina==2)
                {
                setbkcolor(BLACK);
                cleardevice();
                }
                Start(LatimeEcran,InaltimeEcran,Nr_Pagina-1,Jucator);
                ok=1;
                continue;
            }
            for(int i=1+9*(Nr_Pagina-1); i<=9+9*(Nr_Pagina-1); i++)
            {
                if(Start_butoane[i].x1<=x && x<=Start_butoane[i].x2 && Start_butoane[i].y1<=y && y<=Start_butoane[i].y2 && Date_jucator[i].Niveluri==1)
                {

                    Deseneaza_Buton(Start_butoane[i],APASAT,GREEN,BLACK), delay(250);
                    Deseneaza_Buton(Start_butoane[i],RELAXAT,GREEN,BLACK);
                    setbkcolor(BLACK);
                    cleardevice();
                    Nivel(LatimeEcran,InaltimeEcran,i,Jucator);
                    ok=1;
                    break;
                    continue;
                }
            }
            for(int i=61; i<=67; i++)
            {
                if(Start_butoane[i].x1<=x && x<=Start_butoane[i].x2 && Start_butoane[i].y1<=y && y<=Start_butoane[i].y2)
                {
                    Deseneaza_Buton(Start_butoane[i],APASAT,Seteaza.culoare,BLACK), delay(250);
                    Deseneaza_Buton(Start_butoane[i],RELAXAT,Seteaza.culoare,BLACK);
                    if(Nr_Pagina!=i-60)
                    {
                    if(i==61 || i==67)
                    {
                    setbkcolor(BLACK);
                    cleardevice();
                    }
                    Start(LatimeEcran,InaltimeEcran,i-60,Jucator);
                    ok=1;
                    }
                    break;

                }
            }
            if(Nr_Pagina==7 && Start_butoane[68].x1<=x && x<=Start_butoane[68].x2 && Start_butoane[68].y1<=y && y<=Start_butoane[68].y2)
            {
                Deseneaza_Buton(Start_butoane[68],APASAT,Seteaza.culoare,BLACK), delay(250);
                    Deseneaza_Buton(Start_butoane[68],RELAXAT,Seteaza.culoare,BLACK);
                setbkcolor(BLACK);
                cleardevice();
                Nivel(LatimeEcran,InaltimeEcran,61,Jucator);
                ok=1;
            }
        }
    }
    while(ok==0);
}
void Verificare_Niveluri(int LatimeEcran,int InaltimeEcran, char Jucator[20])
{
    int x,nivel,Prima_incercare,Cea_mai_buna_incercare;
    ifstream f(Jucator);
    for(int i=1; i<=60; i++)
        Date_jucator[i].Niveluri=0;
    while(f>>nivel)
    {
        Date_jucator[nivel].Niveluri=1;
        f>>Prima_incercare;
        Date_jucator[nivel].Primul=Prima_incercare;
        f>>Cea_mai_buna_incercare;
        Date_jucator[nivel].Primul=Cea_mai_buna_incercare;
    }
    f.get();
}
void init_imagini_piese(int piesa, char Nume_piesa[5])
{
    char patrat[2], stare[2];
    patrat[1]='\0';
    stare[1]='\0';
    for(int i=1; i<=2; i++)
    {
        patrat[0]=char(i+'0');
        for(int j=0; j<=3; j++)
        {
            stare[0]=char(j+'0');
            strcat(Piesa[piesa].Poza[i][j],"Imagini/");
            strcat(Piesa[piesa].Poza[i][j],patrat);
            strcat(Piesa[piesa].Poza[i][j],Nume_piesa);
            strcat(Piesa[piesa].Poza[i][j],stare);
            strcat(Piesa[piesa].Poza[i][j],".jpg");
        }
    }
}
void Init_Piese(int LatimeEcran, int InaltimeEcran)
{
    int sus_inceput, stanga_inceput, latura, sus, stanga, numar;
    Dimeniune_Patrate(LatimeEcran, InaltimeEcran, sus_inceput, stanga_inceput, numar, latura);

    //Piesa 1 - H
    sus=sus_inceput-latura+10;
    stanga=stanga_inceput-latura*5;
    Piesa[1]={latura,0,1};
    //Stare 0
    Piesa[1].Adaug[0][1]={0,0,latura,latura*3};
    Piesa[1].Adaug[0][2]={latura,latura,latura*2,latura*2};
    Piesa[1].Adaug[0][3]={latura*2,0,latura*3,latura*3};
    Piesa[1].patrat_liber[0][1]=2; Piesa[1].patrat_liber[0][2]=8;
    //Stare 1
    Piesa[1].Adaug[1][1]={0,0,latura*3,latura};
    Piesa[1].Adaug[1][2]={latura,latura,latura*2,latura*2};
    Piesa[1].Adaug[1][3]={0,latura*2,latura*3,latura*3};
    Piesa[1].patrat_liber[1][1]=4; Piesa[1].patrat_liber[1][2]=6;
    //Stare 2
    Piesa[1].Adaug[2][1]={0,0,latura,latura*3};
    Piesa[1].Adaug[2][2]={latura,latura,latura*2,latura*2};
    Piesa[1].Adaug[2][3]={latura*2,0,latura*3,latura*3};
    Piesa[1].patrat_liber[2][1]=2; Piesa[1].patrat_liber[2][2]=8;
    //Stare 3
    Piesa[1].Adaug[3][1]={0,0,latura*3,latura};
    Piesa[1].Adaug[3][2]={latura,latura,latura*2,latura*2};
    Piesa[1].Adaug[3][3]={0,latura*2,latura*3,latura*3};
    Piesa[1].patrat_liber[3][1]=4; Piesa[1].patrat_liber[3][2]=6;
    init_imagini_piese(1,"_H_");
    Patrat[1]={stanga,sus,stanga+latura*3,sus+latura*3,latura,TRUE};

    //Piesa 2 - busola
    sus=sus_inceput+latura*5-10;
    stanga=stanga_inceput-latura*5;
    Piesa[2]={latura,0,5};
    // Stare 0
    Piesa[2].Adaug[0][1]={0,0,latura,latura*3};
    Piesa[2].Adaug[0][2]={latura,0,latura*2,latura*2};
    Piesa[2].Adaug[0][3]={latura*2,latura,latura*3,latura*3};
    Piesa[2].patrat_liber[0][1]=3; Piesa[2].patrat_liber[0][2]=8;
    //Stare 1
    Piesa[2].Adaug[1][1]={0,0,latura*3,latura};
    Piesa[2].Adaug[1][2]={latura,latura,latura*3,latura*2};
    Piesa[2].Adaug[1][3]={0,latura*2,latura*2,latura*3};
    Piesa[2].patrat_liber[1][1]=4; Piesa[2].patrat_liber[1][2]=9;
    //Stare 2
    Piesa[2].Adaug[2][1]={latura*2,0,latura*3, latura*3};
    Piesa[2].Adaug[2][2]={latura,latura,latura*2,latura*3};
    Piesa[2].Adaug[2][3]={0,0,latura,latura*2};
    Piesa[2].patrat_liber[2][1]=2; Piesa[2].patrat_liber[2][2]=7;
    //Stare 3
    Piesa[2].Adaug[3][1]={0,latura*2,latura*3, latura*3};
    Piesa[2].Adaug[3][2]={0,latura,latura*2,latura*2};
    Piesa[2].Adaug[3][3]={latura,0,latura*3, latura};
    Piesa[2].patrat_liber[3][1]=1; Piesa[2].patrat_liber[3][2]=6;
    init_imagini_piese(2,"_Busola_");
    Patrat[5]={stanga,sus,stanga+latura*3,sus+latura*3,latura,TRUE};

    //Piesa 3 + U
    sus=sus_inceput-latura+10;
    stanga=stanga_inceput+latura*9;
    Piesa[3]={latura,0,4};
    //Stare 0
    Piesa[3].Adaug[0][1]={0,0,latura, latura*3};
    Piesa[3].Adaug[0][2]={latura,latura*2,latura*2,latura*3};
    Piesa[3].Adaug[0][3]={latura*2,0,latura*3, latura*3};
    Piesa[3].patrat_liber[0][1]=2; Piesa[3].patrat_liber[0][2]=5;
    //Stare 1
    Piesa[3].Adaug[1][1]={0,0,latura*3, latura};
    Piesa[3].Adaug[1][2]={0,latura,latura,latura*2};
    Piesa[3].Adaug[1][3]={0,latura*2,latura*3,latura*3};
    Piesa[3].patrat_liber[1][1]=5; Piesa[3].patrat_liber[1][2]=6;
    //Stare 2
    Piesa[3].Adaug[2][1]={latura*2,0,latura*3,latura*3};
    Piesa[3].Adaug[2][2]={latura,0,latura*2,latura};
    Piesa[3].Adaug[2][3]={0,0,latura,latura*3};
    Piesa[3].patrat_liber[2][1]=5; Piesa[3].patrat_liber[2][2]=8;
    //Stare 3
    Piesa[3].Adaug[3][1]={0,latura*2,latura*3,latura*3};
    Piesa[3].Adaug[3][2]={latura*2,latura,latura*3,latura*2};
    Piesa[3].Adaug[3][3]={0,0,latura*3,latura};
    Piesa[3].patrat_liber[3][1]=5; Piesa[3].patrat_liber[3][2]=4;
    init_imagini_piese(3,"_U_");
    Patrat[4]={stanga,sus,stanga+latura*3,sus+latura*3,latura,TRUE};

    //Piesa 4 - ColtOpus
    sus=sus_inceput+latura*5-10;
    stanga=stanga_inceput+latura*9;
    Piesa[4]={latura,0,8};
    //Stare 0
    Piesa[4].Adaug[0][1]=Piesa[4].Adaug[2][1]={latura,0,latura*3,latura};
    Piesa[4].Adaug[0][2]=Piesa[4].Adaug[2][2]={0,latura,latura*3,latura*2};
    Piesa[4].Adaug[0][3]=Piesa[4].Adaug[2][3]={0,latura*2,latura*2,latura*3};
    Piesa[4].patrat_liber[0][1]=1; Piesa[4].patrat_liber[0][2]=9;
    //Stare 1
    Piesa[4].Adaug[1][1]=Piesa[4].Adaug[3][1]={latura*2,latura,latura*3,latura*3};
    Piesa[4].Adaug[1][2]=Piesa[4].Adaug[3][2]={latura,0,latura*2,latura*3};
    Piesa[4].Adaug[1][3]=Piesa[4].Adaug[3][3]={0,0,latura,latura*2};
    Piesa[4].patrat_liber[1][1]=3; Piesa[4].patrat_liber[1][2]=7;
    //Stare 2
    Piesa[4].Adaug[2][1]={latura,0,latura*3,latura};
    Piesa[4].Adaug[2][2]={0,latura,latura*3,latura*2};
    Piesa[4].Adaug[2][3]={0,latura*2,latura*2,latura*3};
    Piesa[4].patrat_liber[2][1]=1; Piesa[4].patrat_liber[2][2]=9;
    //Stare 3
    Piesa[4].Adaug[3][1]={latura*2,latura,latura*3,latura*3};
    Piesa[4].Adaug[3][2]={latura,0,latura*2,latura*3};
    Piesa[4].Adaug[3][3]={0,0,latura,latura*2};
    Piesa[4].patrat_liber[3][1]=3; Piesa[4].patrat_liber[3][2]=7;
    init_imagini_piese(4,"_ColtOpus_");
    Patrat[8]={stanga,sus,stanga+latura*3,sus+latura*3,latura,TRUE};

    char patrat[2];
    patrat[1]='\0';
    for(int i=1; i<=8; i++)
    {
        patrat[0]=char(i+'0');
        strcat(Sterge_piese[i],"Imagini/patrat_");
        strcat(Sterge_piese[i],patrat);
        strcat(Sterge_piese[i],".jpg");
    }
}
void Init_Provocari(int LatimeEcran,int InaltimeEcran)
{
    char numar_nivel[20];
    ifstream f("Niveluri_implementate.txt");
    for(int i=1; i<=60; i++)
    {
       f.getline(numar_nivel,30);
       f>>Provocare[i].numar_imagini;
       f.get();
       for(int j=1; j<=Provocare[i].numar_imagini; j++)
          {
              strcpy(Provocare[i].nume_imagine[j],"tabla/");
              f.getline(Provocare[i].nume_imagine[j]+6,30);
          }
    }
    f.close();
}
void Grafica_Piesa(int stanga,int sus, int piesa,int patrat,int stare, int marime)
{
    Piesa[piesa].patrat=patrat;
    Piesa[piesa].stare=stare;
    setfillstyle(SOLID_FILL,WHITE);
    for(int i=1; i<=3; i++)
    {
         Piesa[piesa].Stare[stare][i].x1=stanga+Piesa[piesa].Adaug[stare][i].x1-marime;
         Piesa[piesa].Stare[stare][i].y1=sus+Piesa[piesa].Adaug[stare][i].y1-marime;
         Piesa[piesa].Stare[stare][i].x2=stanga+Piesa[piesa].Adaug[stare][i].x2+marime;
         Piesa[piesa].Stare[stare][i].y2=sus+Piesa[piesa].Adaug[stare][i].y2+marime;
    }
    if(patrat==1 || patrat==4 || patrat==5 || patrat==8)
    readimagefile(Piesa[piesa].Poza[1][stare],stanga,sus,stanga+Piesa[piesa].latura*3,sus+Piesa[piesa].latura*3);
    else
    readimagefile(Piesa[piesa].Poza[2][stare],stanga,sus,stanga+Piesa[piesa].latura*3,sus+Piesa[piesa].latura*3);

}
void Bordare_Patrat(int stanga, int sus, int latura, int culoare)
{
    setfillstyle(SOLID_FILL,culoare);
    bar(stanga-10,sus-10,stanga+latura*3+10,sus);//sus
    bar(stanga-10,sus,stanga,sus+latura*3); //stanga
    bar(stanga+latura*3,sus,stanga+latura*3+10,sus+latura*3); //dreapta
    bar(stanga-10,sus+latura*3,stanga+latura*3+10,sus+latura*3+10);//jos
}
void Grila_Patrat(int stanga,int sus, int numar, int latura)
{
    setcolor(WHITE);
    for (int i=1; i<=numar; i++)
        for (int j=1; j<=numar; j++)
            rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);
}
void Init_tabla(int LatimeEcran, int InaltimeEcran, int nivel_actual)
{
    int numar, latura, sus, stanga, sus_inceput, stanga_inceput;
    int distanta_margini=20;
    Dimeniune_Patrate(LatimeEcran, InaltimeEcran, sus_inceput, stanga_inceput, numar, latura);
    //contur
    sus=sus_inceput;
    stanga=stanga_inceput;
    setfillstyle(SOLID_FILL,COLOR(17,160,190));
    bar(stanga-latura+distanta_margini,sus-latura,stanga+latura*8-distanta_margini,sus+latura*8);
    setfillstyle(SOLID_FILL,GREEN);
    bar(stanga-latura+distanta_margini,sus-latura,stanga+latura*8-distanta_margini,sus-latura+distanta_margini);//sus
    bar(stanga-latura+distanta_margini,sus+latura*8-distanta_margini,stanga+latura*8-distanta_margini,sus+latura*8);//jos
    bar(stanga-latura,sus-latura+distanta_margini,stanga-latura+distanta_margini,sus+latura*8-distanta_margini); //stanga
    bar(stanga+latura*8,sus-latura+distanta_margini,stanga+latura*8-distanta_margini,sus+latura*8-distanta_margini); //dreapta

    setcolor(GREEN);
    for(int i=distanta_margini; i<=distanta_margini*2; i++)
    {
        arc(stanga-latura+i,sus-latura+distanta_margini,90,180,distanta_margini);
        arc(stanga+latura*8-3*distanta_margini+i,sus-latura+distanta_margini,0,90,distanta_margini);
        arc(stanga-latura+i,sus+latura*8-distanta_margini,180,270,distanta_margini);
        arc(stanga+latura*8-i,sus+latura*8-distanta_margini,270,360,distanta_margini);
    }
    for(int i=1; i<=distanta_margini; i++)
    {
        arc(stanga-latura+distanta_margini*2,sus-latura+distanta_margini+i,90,180,distanta_margini);
        arc(stanga+latura*8-2*distanta_margini,sus-latura+distanta_margini+i,0,90,distanta_margini);
        arc(stanga-latura+distanta_margini+i,sus+latura*8-2*distanta_margini,180,270,distanta_margini);
        arc(stanga+latura*8-i-distanta_margini,sus+latura*8-2*distanta_margini,270,360,distanta_margini);
    }

    //stanga sus
    Patrat[2]={stanga,sus,stanga+latura*3, sus+latura*3, latura, FALSE};
    Bordare_Patrat(stanga, sus,latura,WHITE);
    //dreapta sus
    sus=sus_inceput;
    stanga=stanga_inceput+latura*4;
    Patrat[3]={stanga,sus,stanga+latura*3, sus+latura*3, latura, FALSE};
    Bordare_Patrat(stanga, sus,latura,WHITE);
    //stanga jos
    sus=sus_inceput+latura*4;
    stanga=stanga_inceput;
    Grila_Patrat(stanga,sus,numar,latura);
    Patrat[6]={stanga,sus,stanga+latura*3, sus+latura*3,latura, FALSE};
    Bordare_Patrat(stanga, sus,latura,WHITE);;
    //dreapta jos
    sus=sus_inceput+latura*4;
    stanga=stanga_inceput+latura*4;
    Patrat[7]={stanga,sus,stanga+latura*3, sus+latura*3,latura, FALSE};
    Bordare_Patrat(stanga, sus,latura,WHITE);

    int patrat_tabla[]={2,3,6,7};
    if(nivel_actual<=60)
    {
        char c_u[2],c_z[2];
        int x_start,y_start,x_inceput,y_inceput,x_final,y_final,pozitie,contor;
        char Patrat_2[][30]= {"Apa.jpg","Pirat.jpg","Corabie_scufundata.jpg","Corabie.jpg","Apa.jpg","Comoara.jpg","Caracatita.jpg","Apa.jpg","Apa.jpg"};
        char Patrat_3[][30]= {"Pirat.jpg","Turn.jpg","Apa.jpg","Apa.jpg","Corabie.jpg","Comoara.jpg","Caracatita.jpg","Corabie_pirati.jpg","Apa.jpg"};
        char Patrat_6[][30]= {"Pirat.jpg","Corabie_scufundata.jpg","Corabie_pirati.jpg","Corabie.jpg","Comoara.jpg","Apa.jpg","Corabie_pirati.jpg","Turn.jpg","Insula.jpg"};
        char Patrat_7[][30]= {"Apa.jpg","Apa.jpg","Apa.jpg","Turn.jpg","Pirat.jpg","Insula.jpg","Corabie.jpg","Corabie_pirati.jpg","Comoara.jpg"};
        c_u[1]='\0', c_z[1]='\0';
        for(int i=0; i<4; i++)
        {
            pozitie=patrat_tabla[i];
            x_start=Patrat[pozitie].x1;
            y_start=Patrat[pozitie].y1;
            contor=1;
            for(int j=0; j<3; j++)
            {
                for(int k=0; k<3; k++)
                {
                    x_inceput=x_start+k*latura;
                    y_inceput=y_start+j*latura;
                    x_final=x_inceput+latura;
                    y_final=y_inceput+latura;
                    patratele_tabla[pozitie][contor].x1=x_inceput;
                    patratele_tabla[pozitie][contor].y1=y_inceput;
                    patratele_tabla[pozitie][contor].x2=x_final;
                    patratele_tabla[pozitie][contor].y2=y_final;
                    strcpy(patratele_tabla[pozitie][contor].poza,"tabla/");
                    if(pozitie==2)
                        strcat(patratele_tabla[pozitie][contor].poza,Patrat_2[contor-1]);
                    if(pozitie==3)
                        strcat(patratele_tabla[pozitie][contor].poza,Patrat_3[contor-1]);
                    if(pozitie==6)
                        strcat(patratele_tabla[pozitie][contor].poza,Patrat_6[contor-1]);
                    if(pozitie==7)
                        strcat(patratele_tabla[pozitie][contor].poza,Patrat_7[contor-1]);
                    contor++;
                }
            }
        }
    }
    else
    Genereaza_Nivel(LatimeEcran,InaltimeEcran);
    for(int i=0; i<4; i++)
        for(int j=1; j<=9; j++)
          readimagefile(patratele_tabla[patrat_tabla[i]][j].poza,patratele_tabla[patrat_tabla[i]][j].x1,patratele_tabla[patrat_tabla[i]][j].y1,patratele_tabla[patrat_tabla[i]][j].x2,patratele_tabla[patrat_tabla[i]][j].y2);
    for(int i=0;i<4; i++)
        Grila_Patrat(Patrat[patrat_tabla[i]].x1,Patrat[patrat_tabla[i]].y1,numar,latura);
}
void Deseneaza_Provocare(int LatimeEcran,int InaltimeEcran,int numar_imagini,int nivel_actual)
{
    int numar, latura, sus, stanga, sus_inceput, stanga_inceput, dist_piese,dist_inaltime,dist_laterale, mijL;
    Dimeniune_Patrate(LatimeEcran, InaltimeEcran, sus, stanga, numar, latura);
    mijL=LatimeEcran/2;
    sus=sus+latura*8;
    dist_piese=20;
    dist_inaltime=5;
    dist_laterale=10;
    latura=95;
    if(numar_imagini%2==0)
    stanga=mijL-numar_imagini/2*(dist_piese+latura)+dist_piese/2;
    if(numar_imagini%2==1)
    stanga=mijL-numar_imagini/2*(dist_piese+latura)-latura/2;


    Fundal_provocare={stanga-dist_laterale,sus,stanga+numar_imagini*latura+(numar_imagini-1)*dist_piese+dist_laterale, sus+latura+2*dist_inaltime, latura, FALSE};
    setfillstyle(SOLID_FILL,COLOR(71, 179, 192));

    bar(Fundal_provocare.x1,Fundal_provocare.y1,Fundal_provocare.x2,Fundal_provocare.y2);

    for(int i=1; i<=numar_imagini; i++)
    {
            readimagefile(Provocare[nivel_actual].nume_imagine[i],stanga,sus+dist_inaltime,stanga+latura,sus+latura);
            stanga=stanga+latura+dist_piese;
    }
}
void Mutari_Nivel(int nr_mutari)
{
    char c_z[2],c_u[2];
    c_z[1]='\0';
    c_u[1]='\0';
    buton afisare_mutari;

    strcpy(afisare_mutari.text,"Numar mutari: ");
    if(nr_mutari>9)
    {
        c_z[0]=char(nr_mutari/10+'0');
        strcat(afisare_mutari.text,c_z);
    }
    c_u[0]=char(nr_mutari%10+'0');
    strcat(afisare_mutari.text,c_u);

    Init_Text(afisare_mutari,afisare_mutari.text,Nivel_butoane[1].x,Nivel_butoane[2].y1+80,4);
    setbkcolor(COLOR(201,255,255));
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, afisare_mutari.marime);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(BLACK);
    outtextxy((afisare_mutari.x1+afisare_mutari.x2)/2,(afisare_mutari.y1+afisare_mutari.y2)/2+2,afisare_mutari.text);

}
void Cronometru_tabla(int LatimeEcran, int InaltimeEcran,int minut, int secunda)
{
    char c_u[2],c_z[2];
    c_u[1]=c_z[1]='\0';
    Cronometru.minut=minut;
    Cronometru.secunda=secunda;
    strcpy(Cronometru.Text,"Timp: ");
    if(minut>9)
    {
        c_z[0]=char(minut+'0');
        strcat(Cronometru.Text,c_z);
    }
    else
            strcat(Cronometru.Text,"0");
    c_u[0]=char(minut%10+'0');
    strcat(Cronometru.Text,c_u);
    strcat(Cronometru.Text,":");
    if(secunda>9)
    {
        c_z[0]=char(secunda/10+'0');
        strcat(Cronometru.Text,c_z);
    }
    else
        strcat(Cronometru.Text,"0");
    c_u[0]=char(secunda%10+'0');
    strcat(Cronometru.Text,c_u);

    setbkcolor(COLOR(201,255,255));
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(BLACK);
    outtextxy(Nivel_butoane[0].x,Nivel_butoane[2].y1+40,Cronometru.Text);
}
void Genereaza_Nivel(int LatimeEcran,int InaltimeEcran)
{
    int x_start,y_start,x_inceput,y_inceput,x_final,y_final,deplasare,numar,latura,nr_poza,distanta,liber;
    int pozitie,stare,a_doua_stare,nimic,prima_stare;
    int patrat_tabla[]={2,3,6,7};
    char imagine[][30]={"Apa.jpg","Corabie.jpg","Corabie_pirati.jpg","Apa.jpg","Insula.jpg","Pirat.jpg","Turn.jpg","Apa.jpg","Corabie_scufundata.jpg", "Caracatita.jpg","Comoara.jpg","Apa.jpg"};
    Dimeniune_Patrate(LatimeEcran, InaltimeEcran, y_start, x_start, numar, latura);
    ofstream g("nivel_generat.txt");
    char c[2];
    int ok=0;
    int stare_generata=5;
    int patrat_generat=5;
    int vf[5]= {0};
    int nr=0;
    int contor;
    srand(time(0));
    c[1]='\0';
    for(int i=0; i<4; i++)
    {
        pozitie=patrat_tabla[i];
        x_start=Patrat[pozitie].x1;
        y_start=Patrat[pozitie].y1;
        contor=1;
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                x_inceput=x_start+k*latura;
                y_inceput=y_start+j*latura;
                x_final=x_inceput+latura;
                y_final=y_inceput+latura;
                patratele_tabla[pozitie][contor].x1=x_inceput;
                patratele_tabla[pozitie][contor].y1=y_inceput;
                patratele_tabla[pozitie][contor].x2=x_final;
                patratele_tabla[pozitie][contor].y2=y_final;
                nr_poza=rand()%12;
                strcpy(patratele_tabla[pozitie][contor].poza,"tabla/");
                strcat(patratele_tabla[pozitie][contor].poza,imagine[nr_poza]);
                contor++;
            }
        }
    }
    for(int i=1; i<=4; i++)
    {
        while(ok==0)
        {
            patrat_generat=rand()%4;
            if(vf[patrat_generat]==0)
            {
                vf[patrat_generat]=1;
                g<<patrat_tabla[patrat_generat]<<' ';
                ok=1;
            }
        }
        stare_generata=rand()%4;
        if(i==1 || i==4)
        {
            if(stare_generata==0 || stare_generata==2)
                g<<0<<" "<<2<<" ";
            if(stare_generata==1 || stare_generata==3)
                g<<1<<" "<<3<<" ";
        }
        if(i==2 || i==3)
            g<<stare_generata<<" ";
        g<<-1<<" ";
        ok=0;
    }
    g.close();
    contor=0;
    ifstream f("nivel_generat.txt");
    for(int i=1; i<=4; i++)
    {
        f>>pozitie;
        f>>stare;
        if(i==1 || i==4)
            f>>nimic;
        f>>nimic;
        for(int k=1; k<=2; k++)
        {
            liber=Piesa[i].patrat_liber[stare][k];
            if(strstr(patratele_tabla[pozitie][liber].poza,"tabla/Apa.jpg")==0)
                strcpy(Provocare[61].nume_imagine[++contor],patratele_tabla[pozitie][liber].poza);
        }
    }
    f.close();
    Provocare[61].numar_imagini=contor;
}
void Grafica_Nivel(int LatimeEcran, int InaltimeEcran, int nivel_actual)
{
    setfillstyle(SOLID_FILL,COLOR(201,255,255));
    bar(0,0,LatimeEcran,InaltimeEcran);
    Init_tabla(LatimeEcran,InaltimeEcran,nivel_actual);

    //reinitializez mereu patratele si piesele la inceputul unui nivel pentru a nu se suprapune cu nivelul trecut
    Patrat[1].ocupat=TRUE;
    Patrat[2].ocupat=FALSE;
    Patrat[3].ocupat=FALSE;
    Patrat[4].ocupat=TRUE;
    Patrat[5].ocupat=TRUE;
    Patrat[6].ocupat=FALSE;
    Patrat[7].ocupat=FALSE;
    Patrat[8].ocupat=TRUE;
    for(int i=1; i<=4; i++)
        for(int j=0; j<=3; j++)
            for(int k=1; k<=3; k++)
                Piesa[i].Stare[j][k]={0,0,0,0};

    Grafica_Piesa(Patrat[1].x1,Patrat[1].y1,1,1,0,0);
    Grafica_Piesa(Patrat[4].x1,Patrat[4].y1,2,4,0,0);
    Grafica_Piesa(Patrat[5].x1,Patrat[5].y1,3,5,0,0);
    Grafica_Piesa(Patrat[8].x1,Patrat[8].y1,4,8,0,0);

    Bordare_Patrat(Patrat[1].x1,Patrat[1].y1,Patrat[1].latura,GREEN);
    Bordare_Patrat(Patrat[4].x1,Patrat[4].y1,Patrat[4].latura,GREEN);
    Bordare_Patrat(Patrat[5].x1,Patrat[5].y1,Patrat[5].latura,GREEN);
    Bordare_Patrat(Patrat[8].x1,Patrat[8].y1,Patrat[8].latura,GREEN);

    for(int i=0; i<=2; i++)
    Deseneaza_Buton(Nivel_butoane[i],RELAXAT,Seteaza.culoare,BLACK);

    //citesc din fisiere datele de la nivelul dat
    char c_z[2], c_u[2];
    c_z[1]='\0';
    c_u[1]='\0';
    strcpy(Scor[1].text,"Prima rezolvare: ");
    if(Date_jucator[nivel_actual].Primul>9)
    {
        c_z[0]=char(Date_jucator[nivel_actual].Primul/10+'0');
        strcat(Scor[1].text,c_z);
    }
    c_u[0]=char(Date_jucator[nivel_actual].Primul%10+'0');
    strcat(Scor[1].text,c_u);

    strcpy(Scor[2].text,"Cea mai buna rezolvare: ");
    if(Date_jucator[nivel_actual].Cel_Mai_Bun>9)
    {
        c_z[0]=char(Date_jucator[nivel_actual].Cel_Mai_Bun/10+'0');
        strcat(Scor[2].text,c_z);
    }
    c_u[0]=char(Date_jucator[nivel_actual].Cel_Mai_Bun%10+'0');
    strcat(Scor[2].text,c_u);

    Init_Text(Scor[1],Scor[1].text,Nivel_butoane[1].x,Nivel_butoane[2].y1,4);
    Init_Text(Scor[2],Scor[2].text,Nivel_butoane[1].x,Nivel_butoane[2].y1+40,4);

    setbkcolor(COLOR(201,255,255));
    for(int i=1; i<=2; i++)
    {
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, Scor[i].marime);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        setcolor(BLACK);
        outtextxy((Scor[i].x1+Scor[i].x2)/2,(Scor[i].y1+Scor[i].y2)/2,Scor[i].text);
    }

    Mutari_Nivel(0);
    PlaySound(0, 0, 0);
    delay(500);
    if(nivel_actual<=60 && Seteaza.sunet==1)
    {
        if(nivel_actual%2==1)
        {
            char* WAV = "Muzica/Nivel_impar.wav";
            sndPlaySound(WAV, SND_ASYNC);
        }
        else
        {
            char* WAV = "Muzica/Nivel_par.wav";
            sndPlaySound(WAV, SND_ASYNC);
        }
    }
    else
    {
        char* WAV = "Muzica/Nivel_Generat.wav";
        if(Seteaza.sunet==1)
        sndPlaySound(WAV, SND_ASYNC);
    }

}
void Nivel(int LatimeEcran, int InaltimeEcran, int nivel_actual,char Jucator[20])
{
    int mX, mY, x, y, finall=0, ok=0, provocare=0, stare, sterge, dist=50, nr_mutari=0,j, liber,incepe_cronometru=0, timer_1=0,timer_2=0,secunde=30,minute=0;
    Grafica_Nivel(LatimeEcran,InaltimeEcran,nivel_actual);
    secunde=60+(nivel_actual/10*15);
    if(secunde>=60)
        minute=secunde/60;
    secunde=secunde-minute*60;
    Cronometru_tabla(LatimeEcran,InaltimeEcran,minute,secunde);
    while(finall==0)
    {
        if(incepe_cronometru==1 && timer_1+timer_2>=40000000)
        {
            timer_1=0; timer_2=0;
            if(Cronometru.secunda<=0)
            {
                if(Cronometru.minut>0)
                    Cronometru.minut--,Cronometru.secunda=60;

            }
            if(Cronometru.secunda>0 || Cronometru.minut>0)
            {
                Cronometru.secunda--;
                Cronometru_tabla(LatimeEcran,InaltimeEcran,Cronometru.minut,Cronometru.secunda);
            }
            else
            {
                PlaySound(0, 0, 0);
                setfillstyle(SOLID_FILL,COLOR(201,255,255));
                bar(0,0,LatimeEcran,InaltimeEcran);
                cleardevice();
                settextstyle(10, HORIZ_DIR, 5);
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                setcolor(BLACK);
                char* WAV = "Muzica/Timp_terminat.wav";
                if(Seteaza.sunet==1)
                sndPlaySound(WAV, SND_ASYNC);
                outtextxy(LatimeEcran/2,InaltimeEcran/2,"Data viitoare vei reusi (^_^)"); delay(4000);
                finall=1;
                Start(LatimeEcran,InaltimeEcran,1,Jucator);
            }
        }
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            ok=0;
            for(int i=1; i<=4; i++)
            {
                stare=Piesa[i].stare;
                if ((x>=Piesa[i].Stare[stare][1].x1 && x<=Piesa[i].Stare[stare][1].x2 && y>=Piesa[i].Stare[stare][1].y1 && y<=Piesa[i].Stare[stare][1].y2) ||
                        (x>=Piesa[i].Stare[stare][2].x1 && x<=Piesa[i].Stare[stare][2].x2 && y>=Piesa[i].Stare[stare][2].y1 && y<=Piesa[i].Stare[stare][2].y2) ||
                        (x>=Piesa[i].Stare[stare][3].x1 && x<=Piesa[i].Stare[stare][3].x2 && y>=Piesa[i].Stare[stare][3].y1 && y<=Piesa[i].Stare[stare][3].y2))
                {
                   incepe_cronometru=1;
                    for(j=1; j<=8; j++)
                    {
                        if(Patrat[j].x1<=x && x<=Patrat[j].x2 && Patrat[j].y1<=y && y<=Patrat[j].y2)
                        {
                            Patrat[j].ocupat=FALSE;
                            sterge=j;
                            Bordare_Patrat(Patrat[j].x1,Patrat[j].y1,Piesa[i].latura,RED);
                            break;

                        }
                    }
                    clearmouseclick(WM_RBUTTONDOWN);
                    while(ok==0)
                    {
                        if(incepe_cronometru==1 && timer_1+timer_2>=40000000)
                        {
                            timer_1=0; timer_2=0;
                            if(Cronometru.secunda<=0)
                            {
                                if(Cronometru.minut>0)
                                    Cronometru.minut--,Cronometru.secunda=60;

                            }
                            if(Cronometru.secunda>0 || Cronometru.minut>0)
                            {
                                Cronometru.secunda--;
                                Cronometru_tabla(LatimeEcran,InaltimeEcran,Cronometru.minut,Cronometru.secunda);
                            }
                            else
                            {

                                PlaySound(0, 0, 0);
                                setbkcolor(COLOR(201,255,255));
                                cleardevice();
                                settextstyle(10, HORIZ_DIR, 5);
                                settextjustify(CENTER_TEXT, CENTER_TEXT);
                                setcolor(BLACK);
                                PlaySound(0, 0, 0);
                                delay(500);
                                char* WAV = "Muzica/Timp_terminat.wav";
                                if(Seteaza.sunet==1)
                                sndPlaySound(WAV, SND_ASYNC);
                                outtextxy(LatimeEcran/2,InaltimeEcran/2,"Data viitoare vei reusi (^_^)"); delay(4000);
                                ok=1;

                                if(Seteaza.sunet==1)
                                WAV = "Muzica/Fundal_start.wav";
                                sndPlaySound(WAV, SND_ASYNC);
                                Start(LatimeEcran,InaltimeEcran,1,Jucator);
                            }
                        }
                        stare=Piesa[i].stare;
                        if(ismouseclick(WM_RBUTTONDOWN))
                        {
                            clearmouseclick(WM_RBUTTONDOWN);
                            Piesa[i].stare=(stare+1)%4;
                            Grafica_Piesa(Patrat[j].x1, Patrat[j].y1,i,j,Piesa[i].stare,0);
                            if(j==2 || j==3 || j==6 || j==7)
                            {
                                nr_mutari++;
                                Mutari_Nivel(nr_mutari);
                                for(int k=1; k<=2; k++)
                                {
                                      liber=Piesa[i].patrat_liber[Piesa[i].stare][k];
                                      readimagefile(patratele_tabla[j][liber].poza,patratele_tabla[j][liber].x1,patratele_tabla[j][liber].y1,patratele_tabla[j][liber].x2,patratele_tabla[j][liber].y2);
                                }
                            }
                        }
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            x=mousex();
                            y=mousey();
                            for(int j=1; j<=8; j++)
                            {
                                if(Patrat[j].x1<=x && x<=Patrat[j].x2 && Patrat[j].y1<=y && y<=Patrat[j].y2 && Patrat[j].ocupat==FALSE)
                                {
                                    Patrat[j].ocupat=TRUE;
                                    Piesa[i].patrat=j;
                                    if(sterge==1 || sterge==4 || sterge==5 || sterge==8)
                                        Bordare_Patrat(Patrat[sterge].x1,Patrat[sterge].y1,Piesa[i].latura,GREEN);
                                    else
                                        Bordare_Patrat(Patrat[sterge].x1,Patrat[sterge].y1,Piesa[i].latura,WHITE);
                                    ok=1;
                                    if(sterge!=j)
                                    {
                                        if(sterge==2 || sterge==3 || sterge==6 || sterge==7)
                                        {
                                            for(int k=1; k<=9; k++)
                                                readimagefile(patratele_tabla[sterge][k].poza,patratele_tabla[sterge][k].x1,patratele_tabla[sterge][k].y1,patratele_tabla[sterge][k].x2,patratele_tabla[sterge][k].y2);
                                            Grila_Patrat(Patrat[sterge].x1,Patrat[sterge].y1,3,Patrat[sterge].latura);
                                        }
                                        else
                                            readimagefile(Sterge_piese[sterge],Patrat[sterge].x1,Patrat[sterge].y1,Patrat[sterge].x2,Patrat[sterge].y2);

                                        Grafica_Piesa(Patrat[j].x1, Patrat[j].y1,i,j,Piesa[i].stare,0);
                                        if(j==2 || j==3 || j==6 || j==7)
                                        {
                                            nr_mutari++;
                                            Mutari_Nivel(nr_mutari);
                                            for(int k=1; k<=2; k++)
                                            {
                                                liber=Piesa[i].patrat_liber[Piesa[i].stare][k];
                                                readimagefile(patratele_tabla[j][liber].poza,patratele_tabla[j][liber].x1,patratele_tabla[j][liber].y1,patratele_tabla[j][liber].x2,patratele_tabla[j][liber].y2);
                                            }
                                        }
                                    }
                                    timer_2++;
                                    break;
                                }
                            }
                        }
                        timer_2+=2;
                    }

                    break;
                    continue;
                }
            }
            if(Nivel_butoane[0].x1<=x && x<=Nivel_butoane[0].x2 && Nivel_butoane[0].y1<=y && y<=Nivel_butoane[0].y2) //Start
            {
                Deseneaza_Buton(Nivel_butoane[0],APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Nivel_butoane[0],RELAXAT,Seteaza.culoare,BLACK);
                finall=1;
                PlaySound(0, 0, 0);
                delay(50);
                char* WAV = "Muzica/Fundal_start.wav";
                if(Seteaza.sunet==1)
                sndPlaySound(WAV, SND_ASYNC);
                readimagefile("Imagini/Fundal_Jucator.jpg",0,0,LatimeEcran,InaltimeEcran);
                Start(LatimeEcran,InaltimeEcran,1,Jucator);
                continue;
            }
            if(Nivel_butoane[1].x1<=x && x<=Nivel_butoane[1].x2 && Nivel_butoane[1].y1<=y && y<=Nivel_butoane[1].y2)//Next Level
            {
                int prima_stare,a_doua_stare,rezolvat=1,nimic,pozitie;
                int vf[10]={0},nr_piesa=0;
                for(int i=1; i<=4; i++)
                {
                    for(int j=1; j<=2; j++)
                    {
                            liber=Piesa[i].patrat_liber[Piesa[i].stare][j];
                            if(strcmp(patratele_tabla[Piesa[i].patrat][liber].poza,"tabla/Apa.jpg")!=0)
                                nr_piesa++;
                            for(int k=1; k<=Provocare[nivel_actual].numar_imagini; k++)
                            {
                                if(strcmp(patratele_tabla[Piesa[i].patrat][liber].poza,Provocare[nivel_actual].nume_imagine[k])==0 && vf[k]==0)
                                      {
                                          vf[k]=1;
                                          break;
                                      }
                            }
                    }
                }
                timer_2+=2;
                for(int i=1; i<=4; i++)
                    if(Piesa[i].patrat==1 || Piesa[i].patrat==4 || Piesa[i].patrat==5 || Piesa[i].patrat==8)
                    rezolvat=0;

                int k=Provocare[nivel_actual].numar_imagini;
                if(strcmp(Provocare[nivel_actual].nume_imagine[k],"tabla/Busola_Est.jpg")==0)
                    vf[k]=1,nr_piesa++;

                if(strcmp(Provocare[nivel_actual].nume_imagine[k],"tabla/Busola_Vest.jpg")==0)
                    vf[k]=1,nr_piesa++;

                if(strcmp(Provocare[nivel_actual].nume_imagine[k],"tabla/Busola_Nord.jpg")==0)
                    vf[k]=1,nr_piesa++;

                if(strcmp(Provocare[nivel_actual].nume_imagine[k],"tabla/Busola_Sud.jpg")==0)
                    vf[k]=1,nr_piesa++;

                for(int i=1; i<=Provocare[nivel_actual].numar_imagini; i++)
                if(vf[i]==0)
                {
                    rezolvat=0;
                    break;
                }

                if(nr_piesa!=Provocare[nivel_actual].numar_imagini)
                    rezolvat=0;


                if(rezolvat==1 && nivel_actual<=60)
                {
                    if(Date_jucator[nivel_actual].Primul==0)
                        Date_jucator[nivel_actual].Primul=nr_mutari;
                    if(nr_mutari<Date_jucator[nivel_actual].Cel_Mai_Bun || Date_jucator[nivel_actual].Cel_Mai_Bun==0)
                        Date_jucator[nivel_actual].Cel_Mai_Bun=nr_mutari;
                }

                if(Date_jucator[nivel_actual+1].Niveluri==1 && nivel_actual<=59)
                    rezolvat=1;

                if(rezolvat==1)
                {
                    PlaySound(0, 0, 0);
                    delay(50);
                    char* WAV = "Muzica/Nivel_terminat.wav";
                    if(Seteaza.sunet==1)
                    sndPlaySound(WAV, SND_ASYNC);

                    Deseneaza_Buton(Nivel_butoane[1],APASAT,Seteaza.culoare,BLACK), delay(350);
                    Deseneaza_Buton(Nivel_butoane[3],RELAXAT,Seteaza.culoare,BLACK); delay(1200);
                    Deseneaza_Buton(Nivel_butoane[3],APASAT,Seteaza.culoare,BLACK); delay(350);
                    Deseneaza_Buton(Nivel_butoane[3],RELAXAT,Seteaza.culoare,BLACK);
                    Date_jucator[nivel_actual+1].Niveluri=1;
                    finall=1;
                    if(nivel_actual<60)
                    {
                    Nivel(LatimeEcran,InaltimeEcran,nivel_actual+1,Jucator);
                    Date_jucator[nivel_actual+1].Niveluri=1;
                    }
                    else
                    Nivel(LatimeEcran,InaltimeEcran,nivel_actual,Jucator);
                }
                if(rezolvat==1 && nivel_actual>=60)
                {
                    PlaySound(0, 0, 0);
                    delay(50);
                    char* WAV = "Muzica/Nivel_terminat.wav";
                    if(Seteaza.sunet==1)
                    sndPlaySound(WAV, SND_ASYNC);
                    Deseneaza_Buton(Nivel_butoane[1],APASAT,Seteaza.culoare,BLACK), delay(350);
                    Deseneaza_Buton(Nivel_butoane[3],RELAXAT,Seteaza.culoare,BLACK); delay(1200);
                    Deseneaza_Buton(Nivel_butoane[3],APASAT,Seteaza.culoare,BLACK); delay(350);
                    Deseneaza_Buton(Nivel_butoane[3],RELAXAT,Seteaza.culoare,BLACK);
                    Start(LatimeEcran,InaltimeEcran,1,Jucator);
                }
                continue;
            }
            if(Nivel_butoane[2].x1<=x && x<=Nivel_butoane[2].x2 && Nivel_butoane[2].y1<=y && y<=Nivel_butoane[2].y2 && provocare==0)//Provocare_buton
            {
                Deseneaza_Buton(Nivel_butoane[2],APASAT,Seteaza.culoare,BLACK), delay(250);
                Deseneaza_Buton(Nivel_butoane[2],RELAXAT,Seteaza.culoare,BLACK);
                Deseneaza_Provocare(LatimeEcran,InaltimeEcran,Provocare[nivel_actual].numar_imagini,nivel_actual);
                provocare=1;
                continue;
            }
            if(Fundal_provocare.x1 <=x && x<=Fundal_provocare.x2 && Fundal_provocare.y1<=y && y<=Fundal_provocare.y2 && provocare==1)//Provocare_imagini
            {
                setfillstyle(SOLID_FILL,COLOR(201,255,255));
                bar(Fundal_provocare.x1,Fundal_provocare.y1,Fundal_provocare.x2,Fundal_provocare.y2);
                Deseneaza_Buton(Nivel_butoane[2],RELAXAT,Seteaza.culoare,BLACK);
                provocare=0;
                continue;
            }
            timer_2+=2;
        }
        timer_1++;
    }
}
