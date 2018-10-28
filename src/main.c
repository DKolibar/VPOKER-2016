#include <stdio.h>
#include <stdlib.h>
#include <conio.c>
#include <windows.h>
#include <time.h>

//deklaracia funkcii
void cennik();
void CLEANER();
void kartyrandom();
void kartyz_tahhraca();
void kontrola();
void menu();
void SIZEC();
void tahanie();
void pokracovanie();
void urcinasobok();
void pokracovanietest();
void ohre();
void zaciatoknovejhry();
void save();

//PREMENNE PRE PRACU S KARTAMI
int vybratekarty[5],pouzitevysledky[10];
char drzkartu[5]={'F','F','F','F','F'};

//PRACA SO SUBOROM
FILE * fsmernik;
int pokracovaniejemozne=0,pokracovat=0;

//ZAKLADNE PREMENNE
int volbaceny=1,status=1,tah,posuvnik,cennikzvyrazni[9],handcislo=1,najvacsiavyhra=0,vraciamsadomenu=0,menicmince=1,skonciavratsadomenu=0,prehral=0,rychly_rezim=0;

//ZVUK
int zvuk=1;

//URCENIE OBMEZDENIA
int kredity,maximalnacena;

//PENIAZE *na zaciatku je automaticky pridelene 25dolarov=100coinov
int zbudget=25;
double nasobok=4,budget1; 

//VYHERNE CIASTKY ZA JEDEN COIN, DVA, ...
int cena1[9]={250,50,25,9,6,4,3,2,1};
int cena2[9]={500,100,50,18,12,8,6,4,2};
int cena3[9]={750,150,75,27,18,12,9,6,3};
int cena4[9]={1000,200,100,36,24,16,12,8,4};
int cena5[9]={4000,250,125,45,30,20,15,10,5};

void SIZEC() //CTRL+C
{
	HANDLE wHnd;    
	HANDLE rHnd;
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);    
   
    SetConsoleTitle("Video Poker 2.0.5 - Jacks or Better");
    
    SMALL_RECT windowSize = {0, 0, 52, 28};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);  
        
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);	
}

void CLEANER() // CTRL+C
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void cennik()
{
	char tabulka[11][7]={
							{218,194,194,194,194,194,191},
							{179,179,179,179,179,179,179},
							{179,179,179,179,179,179,179},
							{179,179,179,179,179,179,179},
							{179,179,179,179,179,179,179},
							{179,179,179,179,179,179,179},
							{179,179,179,179,179,179,179},
							{179,179,179,179,179,179,179},
							{179,179,179,179,179,179,179},
							{179,179,179,179,179,179,179},
							{192,193,193,193,193,193,217},	
						};
						
	char plochakariet[4][33]={
						{218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191},
						{179,' ',' ',' ',179,' ',' ',179,' ',' ',' ',179,' ',' ',179,' ',' ',' ',179,' ',' ',179,' ',' ',' ',179,' ',' ',179,' ',' ',' ',179},
						{179,' ',' ',' ',179,' ',' ',179,' ',' ',' ',179,' ',' ',179,' ',' ',' ',179,' ',' ',179,' ',' ',' ',179,' ',' ',179,' ',' ',' ',179},
						{192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217},		
						};					
						
	int y,x,a,b,ciastka,plus,styritisic,zvolenacena,vstup,poistka;	
	
	styritisic=1;
	zvolenacena=0;
	
	kredity=budget1*nasobok;
	
	do
	{
		
		if(tah!=0)
			zvolenacena=1;
				
		CLEANER();
		//printf("%d %d\n\n", maximalnacena, tah);
		
		styritisic=1;
		for(y=0;y<11;y++)
		{
			for(x=0;x<7;x++)
			{
				if(y==0&&x==1||y==10&&x==1)
				{
					for(a=0;a<16;a++)
						putchar(196);				
				}
				if(y==0&&x==2||y==0&&x==3||y==0&&x==4||y==0&&x==5||y==0&&x==6||y==10&&x==2||y==10&&x==3||y==10&&x==4||y==10&&x==5||y==10&&x==6)
				{
					for(a=0;a<6;a++)
						putchar(196);				
				}
				//TEXT PRE KOMBINACIE
				for(a=1;a<10;a++)
				{
					if(y==a&&x==1)
					{
						switch(a)
						{
							case 1:
							{								
								if(najvacsiavyhra==9)
									textcolor(LIGHTCYAN);								
								else
									textcolor(WHITE);
								
								if(cennikzvyrazni[0]==1)
								{
									textbackground(GREEN);
									textcolor(WHITE);
								}									
								else
									textbackground(BLACK);	
									
								printf("ROYAL FLUSH     ");
								break;	
							}
							
							case 2:
							{								
								if(najvacsiavyhra==8)
									textcolor(LIGHTCYAN);								
								else
									textcolor(WHITE);
								
								if(cennikzvyrazni[1]==1)
								{
									textbackground(GREEN);
									textcolor(WHITE);
								}									
								else
									textbackground(BLACK);	
									
								printf("STRAIGHT FLUSH  ");
								break;	
							}					
							
							case 3:
							{									
								if(najvacsiavyhra==7)
									textcolor(LIGHTCYAN);									
								else
									textcolor(WHITE);
								
								if(cennikzvyrazni[2]==1)
								{
									textbackground(GREEN);
									textcolor(WHITE);
								}									
								else
									textbackground(BLACK);	
									
								printf("4 OF A KIND     ");
								break;	
							}					
							
							case 4:
							{								
								if(najvacsiavyhra==6)
									textcolor(LIGHTCYAN);									
								else
									textcolor(WHITE);
									
								if(cennikzvyrazni[3]==1)
								{
									textbackground(GREEN);
									textcolor(WHITE);
								}									
								else
									textbackground(BLACK);	
									
								printf("FULL HOUSE      ");
								break;	
							}					
							
							case 5:
							{								
								if(najvacsiavyhra==5)
									textcolor(LIGHTCYAN);									
								else
									textcolor(WHITE);
								
								if(cennikzvyrazni[4]==1)
								{
									textbackground(GREEN);
									textcolor(WHITE);
								}									
								else
									textbackground(BLACK);									
									
								printf("FLUSH           ");
								break;	
							}					
							
							case 6:
							{								
								if(najvacsiavyhra==4)
									textcolor(LIGHTCYAN);									
								else
									textcolor(WHITE);
								
								if(cennikzvyrazni[5]==1)
								{
									textbackground(GREEN);
									textcolor(WHITE);
								}									
								else
									textbackground(BLACK);	
									
								printf("STRAIGHT        ");
								break;	
							}					
							
							case 7:
							{								
								if(najvacsiavyhra==3)
									textcolor(LIGHTCYAN);									
								else
									textcolor(WHITE);
									
								if(cennikzvyrazni[6]==1)
								{
									textbackground(GREEN);
									textcolor(WHITE);
								}									
								else
									textbackground(BLACK);
									
								printf("3 OF A KIND     ");
								break;	
							}
							
							case 8:
							{								
								if(najvacsiavyhra==2)
									textcolor(LIGHTCYAN);									
								else
									textcolor(WHITE);
								
								if(cennikzvyrazni[7]==1)
								{
									textbackground(GREEN);
									textcolor(WHITE);
								}									
								else
									textbackground(BLACK);	
									
								printf("TWO PAIRS       ");
								break;	
							}
							
							case 9:
							{								
								if(najvacsiavyhra==1)
									textcolor(LIGHTCYAN);									
								else
									textcolor(WHITE);
							
								if(cennikzvyrazni[8]==1)
								{
									textbackground(GREEN);
									textcolor(WHITE);
								}									
								else
									textbackground(BLACK);		
									
								cprintf("JACKS OR BETTER ");
								break;	
							}					
						}
						textcolor(WHITE);
						textbackground(BLACK);								
					}
				}			
				
				//TEXT PRE CENY
				ciastka=250;
				plus=250;				
				for(b=1;b<10;b++)
				{	
					if(b==2)
					{
						ciastka=50;
						plus=50;
					}
					if(b==3)
					{
						ciastka=25;
						plus=25;
					}
					if(b==4)
					{
						ciastka=9;
						plus=9;
					}
					if(b==5)
					{
						ciastka=6;
						plus=6;
					}
					if(b==6)
					{
						ciastka=4;
						plus=4;
					}
					if(b==7)
					{
						ciastka=3;
						plus=3;
					}
					if(b==8)
					{
						ciastka=2;
						plus=2;
					}
					if(b==9)
					{
						ciastka=1;
						plus=1;
					}
						
					for(a=2;a<7;a++)
					{
						if(y==1&&x==6&&styritisic==1)
						{
							if(volbaceny==5&&x>5&&x<7)
								textbackground(RED);					
							
							if(volbaceny==5&&cennikzvyrazni[0]==1&&x>5&&x<7)
								textbackground(GREEN);	
								
							printf(" 4000");
							textcolor(YELLOW);
							putchar(15);
							textcolor(WHITE);
							textbackground(BLACK);
							styritisic=0;
							break;
						}
						else if(y==b&&x==a)
						{							
							if(volbaceny==1&&x>1&&x<3||volbaceny==2&&x>2&&x<4||volbaceny==3&&x>3&&x<5||volbaceny==4&&x>4&&x<6||volbaceny==5&&x>5&&x<7)
								textbackground(RED);

							//ROYAL FLUSH ZVYRAZNENIE
							if(volbaceny==1&&cennikzvyrazni[0]==1&&y==1&&x>1&&x<3||volbaceny==2&&cennikzvyrazni[0]==1&&y==1&&x>2&&x<4||volbaceny==3&&cennikzvyrazni[0]==1&&y==1&&x>3&&x<5||volbaceny==4&&cennikzvyrazni[0]==1&&y==1&&x>4&&x<6||volbaceny==5&&cennikzvyrazni[0]==1&&y==1&&x>5&&x<7)
								textbackground(GREEN);
								
							//STRAIGHT FLUSH ZVYRAZNENIE 	
							if(volbaceny==1&&cennikzvyrazni[1]==1&&y==2&&x>1&&x<3||volbaceny==2&&cennikzvyrazni[1]==1&&y==2&&x>2&&x<4||volbaceny==3&&cennikzvyrazni[1]==1&&y==2&&x>3&&x<5||volbaceny==4&&cennikzvyrazni[1]==1&&y==2&&x>4&&x<6||volbaceny==5&&cennikzvyrazni[1]==1&&y==2&&x>5&&x<7)
								textbackground(GREEN);			
								
							//4 OF KIND	
							if(volbaceny==1&&cennikzvyrazni[2]==1&&y==3&&x>1&&x<3||volbaceny==2&&cennikzvyrazni[2]==1&&y==3&&x>2&&x<4||volbaceny==3&&cennikzvyrazni[2]==1&&y==3&&x>3&&x<5||volbaceny==4&&cennikzvyrazni[2]==1&&y==3&&x>4&&x<6||volbaceny==5&&cennikzvyrazni[2]==1&&y==3&&x>5&&x<7)
								textbackground(GREEN);
								
							//FULL HOUSE	
							if(volbaceny==1&&cennikzvyrazni[3]==1&&y==4&&x>1&&x<3||volbaceny==2&&cennikzvyrazni[3]==1&&y==4&&x>2&&x<4||volbaceny==3&&cennikzvyrazni[3]==1&&y==4&&x>3&&x<5||volbaceny==4&&cennikzvyrazni[3]==1&&y==4&&x>4&&x<6||volbaceny==5&&cennikzvyrazni[3]==1&&y==4&&x>5&&x<7)
								textbackground(GREEN);
								
							//FLUSH
							if(volbaceny==1&&cennikzvyrazni[4]==1&&y==5&&x>1&&x<3||volbaceny==2&&cennikzvyrazni[4]==1&&y==5&&x>2&&x<4||volbaceny==3&&cennikzvyrazni[4]==1&&y==5&&x>3&&x<5||volbaceny==4&&cennikzvyrazni[4]==1&&y==5&&x>4&&x<6||volbaceny==5&&cennikzvyrazni[4]==1&&y==5&&x>5&&x<7)
								textbackground(GREEN);
								
							//STRAIGHT
							if(volbaceny==1&&cennikzvyrazni[5]==1&&y==6&&x>1&&x<3||volbaceny==2&&cennikzvyrazni[5]==1&&y==6&&x>2&&x<4||volbaceny==3&&cennikzvyrazni[5]==1&&y==6&&x>3&&x<5||volbaceny==4&&cennikzvyrazni[5]==1&&y==6&&x>4&&x<6||volbaceny==5&&cennikzvyrazni[5]==1&&y==6&&x>5&&x<7)
								textbackground(GREEN);
								
							//3 OF KIND								
							if(volbaceny==1&&cennikzvyrazni[6]==1&&y==7&&x>1&&x<3||volbaceny==2&&cennikzvyrazni[6]==1&&y==7&&x>2&&x<4||volbaceny==3&&cennikzvyrazni[6]==1&&y==7&&x>3&&x<5||volbaceny==4&&cennikzvyrazni[6]==1&&y==7&&x>4&&x<6||volbaceny==5&&cennikzvyrazni[6]==1&&y==7&&x>5&&x<7)
								textbackground(GREEN);
								
							//TWO PAIR
							if(volbaceny==1&&cennikzvyrazni[7]==1&&y==8&&x>1&&x<3||volbaceny==2&&cennikzvyrazni[7]==1&&y==8&&x>2&&x<4||volbaceny==3&&cennikzvyrazni[7]==1&&y==8&&x>3&&x<5||volbaceny==4&&cennikzvyrazni[7]==1&&y==8&&x>4&&x<6||volbaceny==5&&cennikzvyrazni[7]==1&&y==8&&x>5&&x<7)
								textbackground(GREEN);
							
							//JACKS OR BETTER
							if(volbaceny==1&&cennikzvyrazni[8]==1&&y==9&&x>1&&x<3||volbaceny==2&&cennikzvyrazni[8]==1&&y==9&&x>2&&x<4||volbaceny==3&&cennikzvyrazni[8]==1&&y==9&&x>3&&x<5||volbaceny==4&&cennikzvyrazni[8]==1&&y==9&&x>4&&x<6||volbaceny==5&&cennikzvyrazni[8]==1&&y==9&&x>5&&x<7)
								textbackground(GREEN);
								
														
							
							printf(" %4d", ciastka);
							textcolor(YELLOW);
							putchar(15);
							textcolor(WHITE);
							textbackground(BLACK);
						}
													
												
						ciastka+=plus;								
					}							
				}																							
				printf("%c",tabulka[y][x]);
				
				textbackground(BLACK);		
			}
			printf("\n");
		}
		
		textcolor(CYAN);				
		printf("%c USE: %cA D%c or %c4 6%c and ENTER; SPACE or 5 to Draw %c\n", 16, 27, 26, 27, 26, 17);
		if(rychly_rezim==1)
		{
			textcolor(YELLOW);
			printf("%c                FAST MODE ACTIVATED                %c\n", 16, 17);
		}
		else
			printf("                                                                             \n");					
		textcolor(WHITE);	
		
		for(a=0;a<5;a++)
			putchar(254);
			
		printf(" BET N");
		putchar(248);
		printf(": %05d ", handcislo);
		
		for(a=0;a<6;a++)
			putchar(254);
		
		if(tah==0)	
			printf(" ESC - return to menu ");
		else
		{			
			for(a=0;a<22;a++)
			putchar(254);	
		}
		
		for(a=0;a<5;a++)
			putchar(254);
		
		printf("\n");
		putchar(175);		                                          
		printf(" CREDIT: ");
		textcolor(YELLOW); 
		kredity=budget1*nasobok;		
		printf("%d", kredity);
		textcolor(YELLOW);
		putchar(15);	
		textcolor(WHITE);
		//putchar(175);
		printf(" = ");
		textcolor(LIGHTGREEN);		
		printf("%.2f$ ", budget1);
		textcolor(WHITE);		
		putchar(175);
		printf(" PROFIT: ");				 
		if(budget1>zbudget)
		{
			textcolor(GREEN);                   
			printf("+%.2f$ ", budget1-zbudget);					
		}
		else
		{
			textcolor(RED);
			printf("%.2f$ ", budget1-zbudget);						
		}
		textcolor(WHITE);			
		printf("               \n\n");
		
		if(tah==0)
		{
			textcolor(LIGHTMAGENTA);
			printf("           %c %c %c BET:  %d", 26, 26, 26, volbaceny);
		}			
		else
		{
			textcolor(WHITE);
			printf("                 BET:  %d", volbaceny);
		}		
		putchar(15);
		textcolor(WHITE);
		printf(" ");
		putchar(254);
		printf(" 1");
		putchar(15);		
		if(menicmince==1)
			printf(" = 25c");
		else if(menicmince==2)
			printf(" = 50c");	
		else if(menicmince==3)
			printf(" =  1$");
		else if(menicmince==4)
			printf(" =  5$");
		else
			printf(" =  5c");	
			
						
		printf("\n\n");
		
		if(tah==0)
		{		
			for(y=0;y<4;y++)
			{
				printf("          ");
				for(x=0;x<33;x++)
				{
					textbackground(BLACK);
					//                                                                                      XX
					if(y==1&&x>0&&x<4||y==1&&x>7&&x<11||y==1&&x>14&&x<18||y==1&&x>21&&x<25||y==1&&x>28&&x<32||y==2&&x>0&&x<4||y==2&&x>7&&x<11||y==2&&x>14&&x<18||y==2&&x>21&&x<25||y==2&&x>28&&x<32)
						textbackground(LIGHTBLUE);
					
						
					printf("%c", plochakariet[y][x]);	
				}
								
				printf("\n");
			}
		}
		
		if(poistka!=27&&vstup==27)
		{
			for(a=0;a<6;a++)
				printf("                                                   \n");	
		}			
		
		if(skonciavratsadomenu==1)
		{
			skonciavratsadomenu=0;
			vraciamsadomenu=1;
			break;				
		}
		
		if(tah==0)		
			vstup=getch();
			
		if(vstup=='f'||vstup=='F')
		{
			if(zvuk!=0)
				PlaySound("zvuky/gombik.wav",NULL,SND_FILENAME|SND_ASYNC);
			if(rychly_rezim==0)
				rychly_rezim=1;
			else
				rychly_rezim=0;				
		}	
				                                     
		if(vstup==100||vstup==54)
		{
			if(zvuk!=0)
				PlaySound("zvuky/gombik.wav",NULL,SND_FILENAME|SND_ASYNC);
			volbaceny++;	
		}			
						
		if(vstup==97||vstup==52)
		{
			if(zvuk!=0)
				PlaySound("zvuky/gombik.wav",NULL,SND_FILENAME|SND_ASYNC);
			volbaceny--;		
		}
		
		if(vstup==13)
			zvolenacena=1;
			
		if(vstup==27)
		{
			vraciamsadomenu=1;
			break;
		}

		if(tah==0)
		{
			if(volbaceny>maximalnacena)
				volbaceny=1;
			if(volbaceny<1)
				volbaceny=maximalnacena;
		}	
				
		
	}while(zvolenacena!=1);
	
	for(a=1;a<6;a++)
	{		
		if(volbaceny==a&&tah==0&&vraciamsadomenu!=1)
			budget1-=a/nasobok;	
	}
	
	if(tah==0)
		tah++;
	if(rychly_rezim==1)
		Sleep(1);
	else
		Sleep(250);		
}

void kartyz_tahhraca()
{
	int y,x,b,c,vstup,koniectahu;
		
	char plochakariet1[4][33]={
						{201,205,205,205,187,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191},
						{186,' ',' ',    186,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179},
						{186,' ',        186,' ',' ',179,' ',        179,' ',' ',179,' ',        179,' ',' ',179,' ',        179,' ',' ',179,' ',        179},
						{200,205,205,205,188,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217},	
						};	
						
	char plochakariet2[4][33]={
						{218,196,196,196,191,' ',' ',201,205,205,205,187,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191},
						{179,' ',' ',    179,' ',' ',186,' ',' ',    186,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179},
						{179,' ',        179,' ',' ',186,' ',        186,' ',' ',179,' ',        179,' ',' ',179,' ',        179,' ',' ',179,' ',        179},
						{192,196,196,196,217,' ',' ',200,205,205,205,188,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217},	
						};
						
	char plochakariet3[4][33]={
						{218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',201,205,205,205,187,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191},
						{179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',186,' ',' ',    186,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179},
						{179,' ',        179,' ',' ',179,' ',        179,' ',' ',186,' ',        186,' ',' ',179,' ',        179,' ',' ',179,' ',        179},
						{192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',200,205,205,205,188,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217},	
						};					
						
	char plochakariet4[4][33]={
						{218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',201,205,205,205,187,' ',' ',218,196,196,196,191},
						{179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',186,' ',' ',    186,' ',' ',179,' ',' ',    179},
						{179,' ',        179,' ',' ',179,' ',        179,' ',' ',179,' ',        179,' ',' ',186,' ',        186,' ',' ',179,' ',        179},
						{192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',200,205,205,205,188,' ',' ',192,196,196,196,217},	
						};																																				
						
	char plochakariet5[4][33]={
						{218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',201,205,205,205,187},
						{179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',186,' ',' ',    186},
						{179,' ',        179,' ',' ',179,' ',        179,' ',' ',179,' ',        179,' ',' ',179,' ',        179,' ',' ',186,' ',        186},
						{192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',200,205,205,205,188},	
						};
						
	char plochakarietD[4][33]={
						{218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191},
						{179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179,' ',' ',179,' ',' ',    179},
						{179,' ',        179,' ',' ',179,' ',        179,' ',' ',179,' ',        179,' ',' ',179,' ',        179,' ',' ',179,' ',        179},
						{192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217},		
						};
	koniectahu=0;			
	do
	{		
		if(tah==2)
		{	
			koniectahu=1;
			status=6;	
		}	
		
		b=0;
		c=0;				
		CLEANER();		
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	
		
		for(y=0;y<4;y++)
		{	
			printf("          ");	
			for(x=0;x<33;x++)			
			{		
				// prvy riadok                                                                           druhy riadok
				if(y==1&&x>0&&x<3||y==1&&x>6&&x<9||y==1&&x>12&&x<15||y==1&&x>18&&x<21||y==1&&x>24&&x<27||y==2&&x>0&&x<3||y==2&&x>5&&x<8||y==2&&x>10&&x<13||y==2&&x>15&&x<18||y==2&&x>20&&x<23)
				{
					textbackground(WHITE);	
					if(vybratekarty[b]<29)
					{					
						textcolor(LIGHTRED);						
					}				
					else
					{					
						textcolor(BLACK);						
					}									
				}
				else
				{
					textbackground(BLACK);
					textcolor(WHITE);	
				}			
											
				
				//vypisa druh (zelen,cerven,...)
				if(y==1&&x==1||y==1&&x==7||y==1&&x==13||y==1&&x==19||y==1&&x==25)
				{
					if(vybratekarty[c]<29)										
						textcolor(LIGHTRED);									
					else										
						textcolor(BLACK);				
										
					if(vybratekarty[c]<=14)
						putchar(3);
					else if(vybratekarty[c]<=28)
						putchar(4);
					else if(vybratekarty[c]<=42)
						putchar(5);
					else
						putchar(6);
					c++;					
				}								
				
				if(y==2&&x==2||y==2&&x==7||y==2&&x==12||y==2&&x==17||y==2&&x==22)
				{				
					if(vybratekarty[b]==11||vybratekarty[b]==25||vybratekarty[b]==39||vybratekarty[b]==53)
						printf(" J");					
					else if(vybratekarty[b]==12||vybratekarty[b]==26||vybratekarty[b]==40||vybratekarty[b]==54)
						printf(" Q");						
					else if(vybratekarty[b]==13||vybratekarty[b]==27||vybratekarty[b]==41||vybratekarty[b]==55)
						printf(" K");						
					else if(vybratekarty[b]==14||vybratekarty[b]==28||vybratekarty[b]==42||vybratekarty[b]==56)
						printf(" A");											
					else if(vybratekarty[b]<=14)
						printf("%2d", vybratekarty[b]);
					else if(vybratekarty[b]<=28)
						printf("%2d", vybratekarty[b]-14);
					else if(vybratekarty[b]<=42)
						printf("%2d", vybratekarty[b]-28);
					else
						printf("%2d", vybratekarty[b]-42);						
					
					textbackground(BLACK);
					textcolor(WHITE);
					b++;																									
				}							
				
				switch(status)
				{
					case 1:
					{
						if(y==0&&x>=0&&x<=4||y==1&&x==0||y==1&&x==3||y==2&&x==0||y==2&&x==2||y==3&&x>=0&&x<=4)
						{
							textcolor(LIGHTCYAN);
							textbackground(BLACK);
						}
						printf("%c", plochakariet1[y][x]);						
						break;	
					}	
					
					case 2:
					{
						if(y==0&&x>=7&&x<=11||y==1&&x==6||y==1&&x==9||y==2&&x==5||y==2&&x==7||y==3&&x>=7&&x<=11)
						{
							textcolor(LIGHTCYAN);
							textbackground(BLACK);
						}
						printf("%c", plochakariet2[y][x]);						
						break;		
					}					
					
					case 3:
					{
						if(y==0&&x>=14&&x<=18||y==1&&x==12||y==1&&x==15||y==2&&x==10||y==2&&x==12||y==3&&x>=14&&x<=18)
						{
							textcolor(LIGHTCYAN);
							textbackground(BLACK);
						}
						printf("%c", plochakariet3[y][x]);						
						break;		
					}					
					
					case 4:
					{
						if(y==0&&x>=21&&x<=25||y==1&&x==18||y==1&&x==21||y==2&&x==15||y==2&&x==17||y==3&&x>=21&&x<=25)
						{
							textcolor(LIGHTCYAN);
							textbackground(BLACK);
						}
						printf("%c", plochakariet4[y][x]);						
						break;		
					}					
					
					case 5:
					{
						if(y==0&&x>=28&&x<=32||y==1&&x==24||y==1&&x==27||y==2&&x==20||y==2&&x==22||y==3&&x>=28&&x<=32)
						{
							textcolor(LIGHTCYAN);
							textbackground(BLACK);
						}
						printf("%c", plochakariet5[y][x]);						
						break;		
					}
					
					case 6:
					{
						printf("%c", plochakarietD[y][x]);						
						break;
					}
					textcolor(WHITE);
					textbackground(BLACK);					
				}			
				
				
				
			}
			printf("\n");		
		}
				
		textcolor(WHITE);
		textbackground(BLACK);
		printf("          ");
		for(b=0;b<5;b++)
		{
			
			if(drzkartu[b]=='T'&&tah!=2)
			{
				textcolor(YELLOW);
				printf("HELD!");
				textcolor(WHITE);			
			}
			else
			{
				printf("     ");	
			}
			printf("  ");			
		}
		
		if(tah!=2)		
			vstup=getch();
			
		if(vstup=='c'||vstup=='C')
		{
			status=1;
			vstup=13;
		}	
			
		if(vstup=='v'||vstup=='V')
		{
			status=2;
			vstup=13;
		}	
			
		if(vstup=='b'||vstup=='B')
		{
			status=3;
			vstup=13;
		}	
			
		if(vstup=='n'||vstup=='N')
		{
			status=4;
			vstup=13;
		}
		
		if(vstup=='m'||vstup=='M')
		{
			status=5;
			vstup=13;
		}		
		
		if(vstup==100||vstup==54)
		{
			if(zvuk!=0)
				PlaySound("zvuky/gombik.wav",NULL,SND_FILENAME|SND_ASYNC);
			status++;
		}
		
		if(vstup==97||vstup==52)
		{
			if(zvuk!=0)
				PlaySound("zvuky/gombik.wav",NULL,SND_FILENAME|SND_ASYNC);
			status--;
		}
		
		if(vstup==13)
		{
			if(zvuk!=0)
				PlaySound("zvuky/kartah.wav",NULL,SND_FILENAME|SND_ASYNC);
			if(drzkartu[status-1]!='T')
				drzkartu[status-1]='T';
			else
				drzkartu[status-1]='F';
		}		
		
		if(vstup==32||vstup==53)
			koniectahu=1;				
		
		if(status>5)
			status=1;
		if(status<1)
			status=5;
		
	}while(koniectahu!=1);
	tah++;	
	
	//SKRYTIE KARIET	
	b=0;
	c=0;	
	CLEANER();		
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	
	
	if(tah==2)
	{			
		for(y=0;y<4;y++)
		{
			printf("          ");
			for(x=0;x<33;x++)
			{
				if(y==1&&x>0&&x<3||y==1&&x>6&&x<9||y==1&&x>12&&x<15||y==1&&x>18&&x<21||y==1&&x>24&&x<27||y==2&&x>0&&x<3||y==2&&x>5&&x<8||y==2&&x>10&&x<13||y==2&&x>15&&x<18||y==2&&x>20&&x<23)
				{
					textbackground(WHITE);	
					if(vybratekarty[b]<29)
					{					
						textcolor(LIGHTRED);						
					}				
					else
					{					
						textcolor(BLACK);						
					}									
				}
				else
				{
					textbackground(BLACK);
					textcolor(WHITE);	
				}			
											
				
				//vypisa druh (zelen,cerven,...)
				if(y==1&&x==1||y==1&&x==7||y==1&&x==13||y==1&&x==19||y==1&&x==25)
				{
					if(vybratekarty[c]<29)
					{
						if(drzkartu[c]=='T')															
							textcolor(LIGHTRED);
					}									
					else
					{
						if(drzkartu[c]=='T')										
							textcolor(BLACK);				
					}
					if(vybratekarty[c]<=14)
					{
						if(drzkartu[c]=='T')
							putchar(3);
					}
					else if(vybratekarty[c]<=28)
					{
						if(drzkartu[c]=='T')
							putchar(4);					
					}
					else if(vybratekarty[c]<=42)
					{
						if(drzkartu[c]=='T')
							putchar(5);
					}
					else
					{
						if(drzkartu[c]=='T')					
							putchar(6);
					}
					c++;					
				}								
				
				if(y==2&&x==2||y==2&&x==7||y==2&&x==12||y==2&&x==17||y==2&&x==22)
				{				
					if(vybratekarty[b]==11||vybratekarty[b]==25||vybratekarty[b]==39||vybratekarty[b]==53)
					{
						if(drzkartu[b]=='T')
							printf(" J");
					}											
					else if(vybratekarty[b]==12||vybratekarty[b]==26||vybratekarty[b]==40||vybratekarty[b]==54)
					{
						if(drzkartu[b]=='T')
						printf(" Q");
					}
					else if(vybratekarty[b]==13||vybratekarty[b]==27||vybratekarty[b]==41||vybratekarty[b]==55)
					{
						if(drzkartu[b]=='T')
						printf(" K");
					}
					else if(vybratekarty[b]==14||vybratekarty[b]==28||vybratekarty[b]==42||vybratekarty[b]==56)
					{
						if(drzkartu[b]=='T')
						printf(" A");
					}
					else if(vybratekarty[b]<=14)
					{
						if(drzkartu[b]=='T')
						printf("%2d", vybratekarty[b]);
					}
					else if(vybratekarty[b]<=28)
					{
						if(drzkartu[b]=='T')
						printf("%2d", vybratekarty[b]-14);
					}
					else if(vybratekarty[b]<=42)
					{
						if(drzkartu[b]=='T')
						printf("%2d", vybratekarty[b]-28);
					}
					else
					{
						if(drzkartu[b]=='T')
						printf("%2d", vybratekarty[b]-42);						
					}
					textbackground(BLACK);
					textcolor(WHITE);
					b++;																									
				}
				
				
				if(drzkartu[0]=='F'&&y==1&&x==1||drzkartu[0]=='F'&&y==1&&x==2)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					if(x==1)
						printf(" ");					
				}
				else if(drzkartu[0]=='F'&&y==2&&x==1)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					printf("  ");
				}				
				
				if(drzkartu[1]=='F'&&y==1&&x==7||drzkartu[1]=='F'&&y==1&&x==8)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					if(x==7)
						printf(" ");					
				}
				else if(drzkartu[1]=='F'&&y==2&&x==6)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					printf("  ");
				}
				
				if(drzkartu[2]=='F'&&y==1&&x==13||drzkartu[2]=='F'&&y==1&&x==14)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					if(x==13)
						printf(" ");					
				}
				else if(drzkartu[2]=='F'&&y==2&&x==11)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					printf("  ");
				}
				
				if(drzkartu[3]=='F'&&y==1&&x==19||drzkartu[3]=='F'&&y==1&&x==20)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					if(x==19)
						printf(" ");					
				}
				else if(drzkartu[3]=='F'&&y==2&&x==16)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					printf("  ");
				}
				
				if(drzkartu[4]=='F'&&y==1&&x==25||drzkartu[4]=='F'&&y==1&&x==26)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					if(x==25)
						printf(" ");					
				}
				else if(drzkartu[4]=='F'&&y==2&&x==21)
				{
					textcolor(LIGHTBLUE);
					textbackground(LIGHTBLUE);
					printf("  ");
				}
				
								
				printf("%c", plochakarietD[y][x]);	
			}		
			printf("\n");				
		}
		if(rychly_rezim==1)
			Sleep(1);
		else
			Sleep(1700);													
	}		
}

void kontrola()
{
	int pamatprekontrolu[5],a,b,c,vyhral,cenavyhry,l; //ZAKLADNE PREMENNE	
	int jqka[4],minkarta,farby[4],fullhouseA,fullhouseB,fourofkind,royalkarty[5],royalkartyOK; //HLADACIE PREMENNE
	int jacks_or_better,par,postupka; //PREMENNE PRE DANE VYHRY	
	
	l=3+rand()%4;
	
	//obnovenie premennych
	for(a=0;a<4;a++)
	{
		jqka[a]=0;
		farby[a]=0;
	}	
	for(a=0;a<9;a++)
	{
		cennikzvyrazni[a]=0;
	}	
	vyhral=0;
	cenavyhry=0;	
	postupka=0;	
	fullhouseA=0;
	fullhouseB=0;
	fourofkind=0;
	
	printf("\n");	
	for(a=0;a<5;a++)
	{
		if(vybratekarty[a]<15)
			pamatprekontrolu[a]=vybratekarty[a];
		else if(vybratekarty[a]<29)
		{
			pamatprekontrolu[a]=vybratekarty[a];
			pamatprekontrolu[a]-=14;
		}
		else if(vybratekarty[a]<43)
		{
			pamatprekontrolu[a]=vybratekarty[a];
			pamatprekontrolu[a]-=28;
		}
		else if(vybratekarty[a]<57)
		{
			pamatprekontrolu[a]=vybratekarty[a];
			pamatprekontrolu[a]-=42;
		}			
	}
	
	//ROYAL FLUSH 
	if(vyhral!=1)
	{
		royalkartyOK=0;		
		for(a=0;a<4;a++)
		{			
			farby[a]=0;
		}
		
		for(a=0;a<5;a++)
		{			
			royalkarty[a]=0;
		}
		
		for(a=0;a<5;a++)
		{
			if(vybratekarty[a]<15)
				farby[0]++;
			else if(vybratekarty[a]<29)
				farby[1]++;
			else if(vybratekarty[a]<43)
				farby[2]++;
			else if(vybratekarty[a]<57)
				farby[3]++;		
		}
		
		for(a=0;a<5;a++)
		{
			if(pamatprekontrolu[a]==10)
				royalkarty[0]++;
			else if(pamatprekontrolu[a]==11)
				royalkarty[1]++;
			else if(pamatprekontrolu[a]==12)
				royalkarty[2]++;
			else if(pamatprekontrolu[a]==13)
				royalkarty[3]++;
			else if(pamatprekontrolu[a]==14)
				royalkarty[4]++;			
		}
		
		for(a=0;a<5;a++)
		{
			if(royalkarty[a]==1)
				royalkartyOK=1;
			else
			{
				royalkartyOK=0;	
				break;
			}						
		}
		
		for(a=0;a<4;a++)
		{
			if(farby[a]==5&&royalkartyOK==1)
			{	
				if(tah==1)
				{
					if(zvuk!=0)
						PlaySound("zvuky/zhoda.wav",NULL,SND_FILENAME|SND_ASYNC);
					printf("                   ");
					textcolor(LIGHTGRAY);
					putchar(16);
					printf(" ROYAL FLUSH ");
					putchar(17);
					textcolor(WHITE);	
				}
				if(tah!=1)
				{					
					printf("\n\n\n\n           ");					 
					textcolor(LIGHTMAGENTA);
					putchar(l);
					printf(" YOU WON WITH ROYAL FLUSH!!! ");
					putchar(l);
					textcolor(WHITE);
					switch(volbaceny)
					{
						case 1:
						{
							cenavyhry=cena1[0];
							break;	
						}
						case 2:
						{
							cenavyhry=cena2[0];
							break;	
						}
						case 3:
						{
							cenavyhry=cena3[0];
							break;	
						}
						case 4:
						{
							cenavyhry=cena4[0];
							break;	
						}
						case 5:
						{
							cenavyhry=cena5[0];
							break;	
						}	
					}
					if(najvacsiavyhra<9)
						najvacsiavyhra=9;	
				}				
				vyhral=1;
				cennikzvyrazni[0]=1;
				break;	
			}	
		}
	}
	
	//STRAIGHT FLUSH
	if(vyhral!=1)
	{
		postupka=0;
		for(a=0;a<4;a++)
		{			
			farby[a]=0;
		}
		
		for(b=0;b<5;b++)
		{
			for(c=0;c<5;c++)
			{
				if(pamatprekontrolu[b]==pamatprekontrolu[c]&&b!=c)
					postupka=69;	
			}	
		}
		
		minkarta=pamatprekontrolu[0];
		for(a=0;a<5;a++)
		{
			if(pamatprekontrolu[a]<minkarta)
				minkarta=pamatprekontrolu[a];						
		}	
		
		//postupka test
		for(b=1;b<=4;b++)
		{		
			for(a=0;a<5;a++)
			{
				if(minkarta+b==pamatprekontrolu[a])
				{
					postupka++;	
					break;
				}							
			}
		}
		
		for(a=0;a<5;a++)
		{
			if(vybratekarty[a]<15)
				farby[0]++;
			else if(vybratekarty[a]<29)
				farby[1]++;
			else if(vybratekarty[a]<43)
				farby[2]++;
			else if(vybratekarty[a]<57)
				farby[3]++;		
		}
		
		for(a=0;a<4;a++)
		{
			if(farby[a]==5&&postupka==4)
			{	
				if(tah==1)
				{
					if(zvuk!=0)
						PlaySound("zvuky/zhoda.wav",NULL,SND_FILENAME|SND_ASYNC);
					printf("                 ");
					textcolor(LIGHTGRAY);
					putchar(16);
					printf(" STRAIGHT FLUSH ");
					putchar(17);
					textcolor(WHITE);	
				}
				if(tah!=1)
				{
					printf("\n\n\n\n         ");					 
					textcolor(YELLOW);
					putchar(l);
					printf(" YOU WON WITH STRAIGHT FLUSH!!! ");
					putchar(l);
					textcolor(WHITE);
					switch(volbaceny)
					{
						case 1:
						{
							cenavyhry=cena1[1];
							break;	
						}
						case 2:
						{
							cenavyhry=cena2[1];
							break;	
						}
						case 3:
						{
							cenavyhry=cena3[1];
							break;	
						}
						case 4:
						{
							cenavyhry=cena4[1];
							break;	
						}
						case 5:
						{
							cenavyhry=cena5[1];
							break;	
						}	
					}
					if(najvacsiavyhra<8)
						najvacsiavyhra=8;	
				}				
				vyhral=1;
				cennikzvyrazni[1]=1;
				break;	
			}	
		}		
	}	
	
	//FOUR OF KIND
	if(vyhral!=1)
	{	
		par=0;	
		for(a=0;a<5;a++)
		{
			for(b=0;b<5;b++)
			{
				if(pamatprekontrolu[a]==pamatprekontrolu[b]&&a!=b)
					par++;
			}
		}
		
		if(par==12)
		{
			if(tah==1)
			{
				if(zvuk!=0)
					PlaySound("zvuky/zhoda.wav",NULL,SND_FILENAME|SND_ASYNC);
				printf("                  ");
				textcolor(LIGHTGRAY);
				putchar(16);
				printf(" FOUR OF KIND ");
				putchar(17);
				textcolor(WHITE);	
			}
			if(tah!=1)
			{
				printf("\n\n\n\n          ");					 
				textcolor(YELLOW);
				putchar(l);
				printf(" YOU WON WITH FOUR OF KIND!!! ");
				putchar(l);
				textcolor(WHITE);
				switch(volbaceny)
				{
					case 1:
					{
						cenavyhry=cena1[2];
						break;	
					}
					case 2:
					{
						cenavyhry=cena2[2];
						break;	
					}
					case 3:
					{
						cenavyhry=cena3[2];
						break;	
					}
					case 4:
					{
						cenavyhry=cena4[2];
						break;	
					}
					case 5:
					{
						cenavyhry=cena5[2];
						break;	
					}						
				}
				if(najvacsiavyhra<7)
					najvacsiavyhra=7;	
			}				
			vyhral=1;
			cennikzvyrazni[2]=1;				
		}	
	}
	
	//FULL HOUSE
	if(vyhral!=1)
	{
		for(a=0;a<5;a++)
		{
			for(b=0;b<5;b++)
			{
				if(pamatprekontrolu[a]==pamatprekontrolu[b]&&a!=b)
				if(fullhouseA<6)
				{
					fullhouseA++;
				}
				else
					fullhouseB++;					
			}
		}
		
		if(fullhouseA==6&&fullhouseB==2)
		{
				if(tah==1)
				{
					if(zvuk!=0)
						PlaySound("zvuky/zhoda.wav",NULL,SND_FILENAME|SND_ASYNC);
					printf("                   ");
					textcolor(LIGHTGRAY);
					putchar(16);
					printf(" FULL HOUSE ");
					putchar(17);
					textcolor(WHITE);	
				}
				if(tah!=1)
				{
					printf("\n\n\n\n           ");					 
					textcolor(YELLOW);
					putchar(l);
					printf(" YOU WON WITH FULL HOUSE!!! ");
					putchar(l);
					textcolor(WHITE);
					switch(volbaceny)
					{
						case 1:
						{
							cenavyhry=cena1[3];
							break;	
						}
						case 2:
						{
							cenavyhry=cena2[3];
							break;	
						}
						case 3:
						{
							cenavyhry=cena3[3];
							break;	
						}
						case 4:
						{
							cenavyhry=cena4[3];
							break;	
						}
						case 5:
						{
							cenavyhry=cena5[3];
							break;	
						}	
					}
					if(najvacsiavyhra<6)
						najvacsiavyhra=6;	
				}				
				vyhral=1;
				cennikzvyrazni[3]=1;								
		}
		
	} 	
	
	//FLUSH
	if(vyhral!=1)
	{
		for(a=0;a<4;a++)
		{			
			farby[a]=0;
		}
		
		for(a=0;a<5;a++)
		{
			if(vybratekarty[a]<15)
				farby[0]++;
			else if(vybratekarty[a]<29)
				farby[1]++;
			else if(vybratekarty[a]<43)
				farby[2]++;
			else if(vybratekarty[a]<57)
				farby[3]++;		
		}
		
		for(a=0;a<4;a++)
		{
			if(farby[a]==5)
			{	
				if(tah==1)
				{
					if(zvuk!=0)
						PlaySound("zvuky/zhoda.wav",NULL,SND_FILENAME|SND_ASYNC);
					printf("                      ");
					textcolor(LIGHTGRAY);
					putchar(16);
					printf(" FLUSH ");
					putchar(17);
					textcolor(WHITE);	
				}
				if(tah!=1)
				{
					printf("\n\n\n\n              ");					 
					textcolor(YELLOW);
					putchar(l);
					printf(" YOU WON WITH FLUSH!!! ");
					putchar(l);
					textcolor(WHITE);
					switch(volbaceny)
					{
						case 1:
						{
							cenavyhry=cena1[4];
							break;	
						}
						case 2:
						{
							cenavyhry=cena2[4];
							break;	
						}
						case 3:
						{
							cenavyhry=cena3[4];
							break;	
						}
						case 4:
						{
							cenavyhry=cena4[4];
							break;	
						}
						case 5:
						{
							cenavyhry=cena5[4];
							break;	
						}	
					}
					if(najvacsiavyhra<5)
						najvacsiavyhra=5;	
				}				
				vyhral=1;
				cennikzvyrazni[4]=1;				
				break;	
			}	
		}
	}
	
	//STRAIGHT
	if(vyhral!=1)
	{
		postupka=0;
		minkarta=pamatprekontrolu[0];
		
		for(b=0;b<5;b++)
		{
			for(c=0;c<5;c++)
			{
				if(pamatprekontrolu[b]==pamatprekontrolu[c]&&b!=c)
					postupka=69;	
			}	
		}
		
		for(a=0;a<5;a++)
		{			
			if(pamatprekontrolu[a]<minkarta)
				minkarta=pamatprekontrolu[a];					
		}	
		
		//postupka test
		for(b=1;b<=4;b++)
		{		
			for(a=0;a<5;a++)
			{
				if(minkarta+b==pamatprekontrolu[a])
				{
					postupka++;	
					break;
				}							
			}
		}
		
		if(postupka==4)
		{
				if(tah==1)
				{
					if(zvuk!=0)
						PlaySound("zvuky/zhoda.wav",NULL,SND_FILENAME|SND_ASYNC);
					printf("                    ");
					textcolor(LIGHTGRAY);
					putchar(16);
					printf(" STRAIGHT ");
					putchar(17);
					textcolor(WHITE);	
				}
				if(tah!=1)
				{
					printf("\n\n\n\n            ");					 
					textcolor(YELLOW);
					putchar(l);
					printf(" YOU WON WITH STRAIGHT!!! ");
					putchar(l);
					textcolor(WHITE);
					switch(volbaceny)
					{
						case 1:
						{
							cenavyhry=cena1[5];
							break;	
						}
						case 2:
						{
							cenavyhry=cena2[5];
							break;	
						}
						case 3:
						{
							cenavyhry=cena3[5];
							break;	
						}
						case 4:
						{
							cenavyhry=cena4[5];
							break;	
						}
						case 5:
						{
							cenavyhry=cena5[5];
							break;	
						}	
					}
					if(najvacsiavyhra<4)
						najvacsiavyhra=4;	
				}				
				vyhral=1;
				cennikzvyrazni[5]=1;				
		}
	}
	
	//THREE OF KIND
	if(vyhral!=1)
	{
		par=0;	
		for(a=0;a<5;a++)
		{
			for(b=0;b<5;b++)
			{
				if(pamatprekontrolu[a]==pamatprekontrolu[b]&&a!=b)
					par++;
			}
		}
		
		if(par==6)
		{
				if(tah==1)
				{
					if(zvuk!=0)
						PlaySound("zvuky/zhoda.wav",NULL,SND_FILENAME|SND_ASYNC);
					printf("                    ");
					textcolor(LIGHTGRAY);
					putchar(16);
					printf(" 3 OF KIND ");
					putchar(17);
					textcolor(WHITE);	
				}
				if(tah!=1)
				{
					printf("\n\n\n\n            ");					 
					textcolor(YELLOW);
					putchar(l);
					printf(" YOU WON WITH 3 OF KIND!!! ");
					putchar(l);
					textcolor(WHITE);
						switch(volbaceny)
					{
						case 1:
						{
							cenavyhry=cena1[6];
							break;	
						}
						case 2:
						{
							cenavyhry=cena2[6];
							break;	
						}
						case 3:
						{
							cenavyhry=cena3[6];
							break;	
						}
						case 4:
						{
							cenavyhry=cena4[6];
							break;	
						}
						case 5:
						{
							cenavyhry=cena5[6];
							break;	
						}	
					}
					if(najvacsiavyhra<3)
						najvacsiavyhra=3;	
				}				
				vyhral=1;
				cennikzvyrazni[6]=1;				
		}
	}
	
	//TWO PAIRS
	if(vyhral!=1)
	{
		par=0;	
		for(a=0;a<5;a++)
		{
			for(b=0;b<5;b++)
			{
				if(pamatprekontrolu[a]==pamatprekontrolu[b]&&a!=b)
					par++;
			}
		}
		
		if(par==4)
		{
				if(tah==1)
				{
					if(zvuk!=0)
						PlaySound("zvuky/zhoda.wav",NULL,SND_FILENAME|SND_ASYNC);
					printf("                    ");
					textcolor(LIGHTGRAY);
					putchar(16);
					printf(" TWO PAIRS ");
					putchar(17);
					textcolor(WHITE);	
				}
				if(tah!=1)
				{
					printf("\n\n\n\n            ");					 
					textcolor(YELLOW);
					putchar(l);
					printf(" YOU WON WITH TWO PAIRS!!! ");
					putchar(l);
					textcolor(WHITE);
					switch(volbaceny)
					{
						case 1:
						{
							cenavyhry=cena1[7];
							break;	
						}
						case 2:
						{
							cenavyhry=cena2[7];
							break;	
						}
						case 3:
						{
							cenavyhry=cena3[7];
							break;	
						}
						case 4:
						{
							cenavyhry=cena4[7];
							break;	
						}
						case 5:
						{
							cenavyhry=cena5[7];
							break;	
						}							
					}
					if(najvacsiavyhra<2)
						najvacsiavyhra=2;	
				}				
				vyhral=1;
				cennikzvyrazni[7]=1;				
		}
	}
	
	//JACKS OR BETTER test
	if(vyhral!=1)
	{		
		for(a=0;a<5;a++)
		{
			if(pamatprekontrolu[a]==11)
				jqka[0]++;
			
			if(pamatprekontrolu[a]==12)
				jqka[1]++;
			
			if(pamatprekontrolu[a]==13)
				jqka[2]++;
			
			if(pamatprekontrolu[a]==14)
				jqka[3]++;					
		}		
		
		jacks_or_better=0;
		for(b=0;b<4;b++)
		{
			if(jqka[b]==2)
			{
				for(a=0;a<4;a++)
				{
					if(jqka[a]!=2&&a!=b)
					{
						jacks_or_better++;	
					}
				}				
			}		
		}	
		if(jacks_or_better==3)
		{
				if(tah==1)
				{
					if(zvuk!=0)
						PlaySound("zvuky/zhoda.wav",NULL,SND_FILENAME|SND_ASYNC);
					printf("                 ");
					textcolor(LIGHTGRAY);
					putchar(16);
					printf(" JACKS OR BETTER ");
					putchar(17);
					textcolor(WHITE);	
				}
				if(tah!=1)
				{
					printf("\n\n\n\n         ");					 
					textcolor(YELLOW);
					putchar(l);
					printf(" YOU WON WITH JACKS OR BETTER!!! ");
					putchar(l);
					textcolor(WHITE);
					switch(volbaceny)
					{
						case 1:
						{
							cenavyhry=cena1[8];
							break;	
						}
						case 2:
						{
							cenavyhry=cena2[8];
							break;	
						}
						case 3:
						{
							cenavyhry=cena3[8];
							break;	
						}
						case 4:
						{
							cenavyhry=cena4[8];
							break;	
						}
						case 5:
						{
							cenavyhry=cena5[8];
							break;	
						}							
					}
					if(najvacsiavyhra<1)
						najvacsiavyhra=1;	
				}				
				vyhral=1;
				cennikzvyrazni[8]=1;								
		}	
	}	
	
	//GAME OVER
	if(vyhral!=1&&tah!=1)
	{
		for(a=0;a<9;a++)
		{
			cennikzvyrazni[a]=0;
		}
		printf("\n\n\n\n                    ");					 
		textcolor(LIGHTRED);
		putchar(254);
		printf(" GAME OVER ");		
		putchar(254);
		printf("          ");
		textcolor(WHITE);		
	}	
	
	if(budget1<=0&&vyhral!=1&&tah!=1)	
	{		
		for(a=0;a<9;a++)		
			cennikzvyrazni[a]=0;
		if(zvuk!=0)			
			PlaySound("zvuky/bankrupt.wav",NULL,SND_FILENAME|SND_ASYNC);
		printf("\n\n           ");					 
		textcolor(LIGHTRED);
		putchar(16);
		printf(" ALL OF YOUR MONEY ARE GONE! "); 
		putchar(17);
		printf("          \n");
		printf("         Press any key for return to menu...");			
		skonciavratsadomenu=1;
		tah=1;
		prehral=1;
		remove("hrac.dk");	//<<< ODSTRANI DATA O HRACOVI
	}	
	
	if(budget1*nasobok<1&&vyhral!=1&&tah!=1)
	{
		for(a=0;a<9;a++)		
			cennikzvyrazni[a]=0;		
		printf("\n\n       ");					 
		textcolor(WHITE);
		putchar(16);
		printf(" YOU DON'T HAVE ENOUGH COINS TO BET! ");
		if(zvuk!=0)
			printf("\a");
		putchar(17);
		printf("          \n");
		printf("         Press any key for return to menu...");				
		skonciavratsadomenu=1;
		tah=1;					
	}	
	
	if(tah!=1)
	{
		if(vyhral==1)
		{
			if(zvuk!=0)
			{
				if(cennikzvyrazni[1]==1||cennikzvyrazni[0]==1&&volbaceny!=5)
					PlaySound("zvuky/cinkcink_morerare.wav",NULL,SND_FILENAME|SND_ASYNC);			
				else if(cennikzvyrazni[2]==1)
					PlaySound("zvuky/cinkcink_rare.wav",NULL,SND_FILENAME|SND_ASYNC);
				else				
					PlaySound("zvuky/cinkcink.wav",NULL,SND_FILENAME|SND_ASYNC);	
			}			
			printf("\n\n");
			textcolor(LIGHTGREEN);
			printf("                       + %4d", cenavyhry);		
			putchar(15);
			textcolor(WHITE);
			budget1+=cenavyhry/nasobok;	
		}
		if(cennikzvyrazni[0]==1&&volbaceny==5)
		{
			Sleep(900);
			textcolor(LIGHTCYAN);			
			printf("\n\n            JACKPOT!!! CALL THE ATTENDANT");
			if(zvuk!=0)			
				PlaySound("zvuky/rf.wav",NULL,SND_FILENAME|SND_ASYNC);
			for(a=0;a<45;a++)
			{
				CLEANER();								
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                         ");
				sleep(1);
				CLEANER();
				textcolor(10+rand()%6);
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n            JACKPOT!!! CALL THE ATTENDANT");
				sleep(1);	
			}						
			textcolor(WHITE);
		}			
		else		
			printf("\n\n            Press any key to continue!...");		
	}
	textcolor(WHITE);				
}

void kartyrandom()
{	
	int pamatkariet[52]={						//       J   Q   K   A
					 2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, // cerven ALT+3 -0
					16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, // pica   ALT+4 -14
					30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, // gula   ALT+5 -28
					44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, // zelen  ALT+6 -42
					};
					
	int vysledok,a,b,semafor;
	
	a=0;
	semafor=0;				
	while(a!=5)
	{		
		vysledok=rand()%52; 
		
		for(b=0;b<10;b++)
		{
			if(pamatkariet[vysledok]!=pouzitevysledky[b])
				semafor=1;						
			else
			{
				semafor=0;
				break;					
			}
				
		}
		
		if(semafor==1)
		{
			vybratekarty[a]=pamatkariet[vysledok];
			pouzitevysledky[posuvnik]=pamatkariet[vysledok];
			a++;
			semafor=0;
			posuvnik++;				
		}				
	}					
}

void tahanie()
{
	int ulozenekarty[5],a;	
	
	for(a=0;a<5;a++)
	{
		if(drzkartu[a]=='T')
			ulozenekarty[a]=vybratekarty[a];
		else
			ulozenekarty[a]=0;	
	}
	
	kartyrandom();
	
	for(a=0;a<5;a++)
	{
		if(ulozenekarty[a]!=0)
			vybratekarty[a]=ulozenekarty[a];				
	}	
}

void ohre()
{
	int a,y,x;
	
	char plochakariet[4][33]={
						{218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191},
						{179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179},
						{179,' ','1','0',179,' ',' ',179,' ',' ','J',179,' ',' ',179,' ',' ','Q',179,' ',' ',179,' ',' ','K',179,' ',' ',179,' ',' ','A',179},
						{192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217},	
						};
	
	system("cls");
	
	for(y=0;y<4;y++)
	{	
		printf("          ");
		for(x=0;x<33;x++)			
		{		
			// prvy riadok                                                                           druhy riadok
			if(y==1&&x>0&&x<4||y==1&&x>7&&x<11||y==1&&x>14&&x<18||y==1&&x>21&&x<25||y==1&&x>28&&x<32||y==2&&x>0&&x<4||y==2&&x>7&&x<11||y==2&&x>14&&x<18||y==2&&x>21&&x<25||y==2&&x>28&&x<32)
			{
				textbackground(WHITE);							
				textcolor(LIGHTRED);														
			}
			else
			{
				textbackground(BLACK);
				textcolor(WHITE);	
			}				
			printf("%c", plochakariet[y][x]);					
			textcolor(WHITE);
			textbackground(BLACK);									
		}
		printf("\n");
	}
	
	printf("            VIDEO POKER "); 			
	printf("- JACKS OR BETTER\n\n");
	
	for(a=0;a<5;a++)
		putchar(254);
		
	printf(" ABOUT: ");
	
	for(a=0;a<40;a++)
		putchar(254);	
	
			
	printf("\n\n@: You are playing Video Poker game.    \n");
	printf("   It's slot-machine game, but in contrast of\n");
	printf("   classic slots, for video poker you nedd  \n");
	printf("   skill to play it and win.\n");
	printf("   There is a lot of different modes, but this\n");
	printf("   one is called Jacks or Better, included with\n");
	printf("   6/9 paytable.\n");
	printf("   Game includes autosaving! You can have only\n");
	printf("   one game in progress... Enjoy!\n");
	printf("\n   This slot-machine is playing fairly! There  \n");
	printf("   is used only simple rand() generator:         \n");				
	textcolor(LIGHTGREEN);
	printf("   vysledok=rand()");
	putchar(37);
	printf("52;\n");			
	textcolor(WHITE);
	printf("\n   Autor: Daniel Kolib");
	putchar(160);
	printf("r\n");
	printf("\n   Press any key for return to menu...");			
	getch();
	
	system("cls");	
}

void zaciatoknovejhry()
{
	int a,y,x,vstup;
	
	char plochakariet[4][33]={
						{218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191},
						{179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179},
						{179,' ','1','0',179,' ',' ',179,' ',' ','J',179,' ',' ',179,' ',' ','Q',179,' ',' ',179,' ',' ','K',179,' ',' ',179,' ',' ','A',179},
						{192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217},	
						};
						
	char peniazkychar[3][35]={
						{218,196,196,196,196,196,196,191,' ',218,196,196,196,196,196,196,191,' ',218,196,196,196,196,196,196,191,' ',218,196,196,196,196,196,196,191},
						{179,' ',' ',' ','5','$',' ',179,' ',179,' ',' ','1','0','$',' ',179,' ',179,' ',' ','2','5','$',' ',179,' ',179,' ','1','0','0','$',' ',179},
						{192,196,196,196,196,196,196,217,' ',192,196,196,196,196,196,196,217,' ',192,196,196,196,196,196,196,217,' ',192,196,196,196,196,196,196,217},
					};
	
	while(1)
	{
		system("cls");	
		for(y=0;y<4;y++)
		{	
			printf("          ");
			for(x=0;x<33;x++)			
			{		
				// prvy riadok                                                                           druhy riadok
				if(y==1&&x>0&&x<4||y==1&&x>7&&x<11||y==1&&x>14&&x<18||y==1&&x>21&&x<25||y==1&&x>28&&x<32||y==2&&x>0&&x<4||y==2&&x>7&&x<11||y==2&&x>14&&x<18||y==2&&x>21&&x<25||y==2&&x>28&&x<32)
				{
					textbackground(WHITE);							
					textcolor(LIGHTRED);														
				}
				else
				{
					textbackground(BLACK);
					textcolor(WHITE);	
				}				
				printf("%c", plochakariet[y][x]);					
				textcolor(WHITE);
				textbackground(BLACK);									
			}
			printf("\n");
		}
		
		printf("            VIDEO POKER "); 			
		printf("- JACKS OR BETTER\n\n");
		
		for(a=0;a<5;a++)
			putchar(254);
			     
		printf(" NEW GAME: ");
		
		for(a=0;a<37;a++)
			putchar(254);
		
		printf("\n\n");	
		for(y=0;y<3;y++)
		{
			printf("   ");
			for(x=0;x<35;x++)
			{
				textcolor(LIGHTGREEN);
				printf("%c", peniazkychar[y][x]);
			}
			printf("\n");	
		}
		textcolor(WHITE);	
			
		printf("\n   %c INSERT CASH: ", 175);
		scanf("%d", &vstup);
		
		if(vstup%5==0)
		{
			zbudget=vstup;
			break;			
		}			
		else
		{
			if(zvuk!=0)
				printf("\a");	
		}
		
		
				
	}
	
	textcolor(LIGHTCYAN);
	printf("\n   LOADING ");
	Sleep(100);
	for(a=0;a<3;a++)
	{		
		printf(".");
		Sleep(100);
	}
	textcolor(WHITE);	
	system("cls");
	
	//OBNOVENIE PREMENNYCH
	volbaceny=1;
	status=1;
	handcislo=1;
	najvacsiavyhra=0;
	vraciamsadomenu=0;	
	skonciavratsadomenu=0;
	prehral=0;
	urcinasobok();	
}

void menu()
{
	int volba,a=4,status=1,y,x,vstup,koniecmenu=0,cislo;
		
		//      Y   X
	char volba1[20][14]={
						 {' ',201,205,205,205,205,205,205,205,205,205,187,' '},
						 {201,188,'1',' ','C','R','E','D','I','T',':',200,187},										
						 {200,187,' ',' ',' ',                ' ',' ',201,188},
						 {' ',200,205,205,205,205,205,205,205,205,205,188,' '},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'R','E','S','U','M','E',' ','G','A','M','E',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'N','E','W',' ','G','A','M','E','.','.','.',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'S','O','U','N','D',':',' ',                179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,' ',' ',' ','A','B','O','U','T',' ',' ',' ',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},	
						};
						
	char volba2[20][14]={
						 {' ',218,196,196,196,196,196,196,196,196,196,191,' '},
						 {218,217,'1',' ','C','R','E','D','I','T',':',192,191},										
						 {192,191,' ',' ',' ',                ' ',' ',218,217},
						 {' ',192,196,196,196,196,196,196,196,196,196,217,' '},
						 {' '},
						 {201,205,205,205,205,205,205,205,205,205,205,205,187},
						 {186,'R','E','S','U','M','E',' ','G','A','M','E',186},										
						 {200,205,205,205,205,205,205,205,205,205,205,205,188},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'N','E','W',' ','G','A','M','E','.','.','.',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'S','O','U','N','D',':',' ',                179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,' ',' ',' ','A','B','O','U','T',' ',' ',' ',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},	
						};			
																		
	char volba3[20][14]={
						 {' ',218,196,196,196,196,196,196,196,196,196,191,' '},
						 {218,217,'1',' ','C','R','E','D','I','T',':',192,191},										
						 {192,191,' ',' ',' ',                ' ',' ',218,217},
						 {' ',192,196,196,196,196,196,196,196,196,196,217,' '},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'R','E','S','U','M','E',' ','G','A','M','E',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {201,205,205,205,205,205,205,205,205,205,205,205,187},
						 {186,'N','E','W',' ','G','A','M','E','.','.','.',186},										
						 {200,205,205,205,205,205,205,205,205,205,205,205,188},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'S','O','U','N','D',':',' ',                179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,' ',' ',' ','A','B','O','U','T',' ',' ',' ',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},	
						};
						
	char volba4[20][14]={
						 {' ',218,196,196,196,196,196,196,196,196,196,191,' '},
						 {218,217,'1',' ','C','R','E','D','I','T',':',192,191},										
						 {192,191,' ',' ',' ',                ' ',' ',218,217},
						 {' ',192,196,196,196,196,196,196,196,196,196,217,' '},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'R','E','S','U','M','E',' ','G','A','M','E',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'N','E','W',' ','G','A','M','E','.','.','.',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {201,205,205,205,205,205,205,205,205,205,205,205,187},
						 {186,'S','O','U','N','D',':',' ',                186},										
						 {200,205,205,205,205,205,205,205,205,205,205,205,188},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,' ',' ',' ','A','B','O','U','T',' ',' ',' ',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},	
						};
						
	char volba5[20][14]={
						 {' ',218,196,196,196,196,196,196,196,196,196,191,' '},
						 {218,217,'1',' ','C','R','E','D','I','T',':',192,191},										
						 {192,191,' ',' ',' ',                ' ',' ',218,217},
						 {' ',192,196,196,196,196,196,196,196,196,196,217,' '},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'R','E','S','U','M','E',' ','G','A','M','E',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'N','E','W',' ','G','A','M','E','.','.','.',179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {218,196,196,196,196,196,196,196,196,196,196,196,191},
						 {179,'S','O','U','N','D',':',' ',                179},										
						 {192,196,196,196,196,196,196,196,196,196,196,196,217},
						 {' '},
						 {201,205,205,205,205,205,205,205,205,205,205,205,187},
						 {186,' ',' ',' ','A','B','O','U','T',' ',' ',' ',186},										
						 {200,205,205,205,205,205,205,205,205,205,205,205,188},	
						};					
																											
	char plochakariet[4][33]={
						{218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191,' ',' ',218,196,196,196,191},
						{179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179,' ',' ',179,  3,' ',' ',179},
						{179,' ','1','0',179,' ',' ',179,' ',' ','J',179,' ',' ',179,' ',' ','Q',179,' ',' ',179,' ',' ','K',179,' ',' ',179,' ',' ','A',179},
						{192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217,' ',' ',192,196,196,196,217},	
						};						
	
	system("cls");	
	
	pokracovanietest();	
	if(pokracovaniejemozne!=0)
		pokracovanie(); //NACITAJ DATA
	
	while(koniecmenu!=1)
	{
		CLEANER();
		urcinasobok();
		
		for(y=0;y<4;y++)
		{	
			printf("          ");
			for(x=0;x<33;x++)			
			{		
				// prvy riadok                                                                           druhy riadok
				if(y==1&&x>0&&x<4||y==1&&x>7&&x<11||y==1&&x>14&&x<18||y==1&&x>21&&x<25||y==1&&x>28&&x<32||y==2&&x>0&&x<4||y==2&&x>7&&x<11||y==2&&x>14&&x<18||y==2&&x>21&&x<25||y==2&&x>28&&x<32)
				{
					textbackground(WHITE);							
					textcolor(LIGHTRED);														
				}
				else
				{
					textbackground(BLACK);
					textcolor(WHITE);	
				}				
				printf("%c", plochakariet[y][x]);					
				textcolor(WHITE);
				textbackground(BLACK);									
			}
			printf("\n");
		}	
					                
		printf("            VIDEO POKER "); 			
		printf("- JACKS OR BETTER\n\n");		
			
		for(y=0;y<20;y++)
		{				
			printf("                    ");
			for(x=0;x<14;x++)
			{
				if(y==1&&x>1&&x<11||y==2&&x>1&&x<5)
					textcolor(YELLOW);					
				else					
					textcolor(WHITE);
				
				if(y==2&&x==4)
				{
					textcolor(LIGHTGREEN);
					if(menicmince==1)										
						printf(" 25c");											
					else if(menicmince==2)					
						printf(" 50c");											
					else if(menicmince==3)					
						printf(" 1 $");											
					else if(menicmince==4)					
						printf(" 5 $");											
					else					
						printf(" 5 c");											
					textcolor(WHITE);
				}
				
				if(y==1&&x==13&&budget1*nasobok<1&&pokracovaniejemozne==1)
				{
					textcolor(LIGHTRED);
					printf(" INCORRECT CREDIT");
					textcolor(WHITE);					
				}				
				else if(y==1&&x==13)
					printf("                      ");
					
				if(y==2&&x==9&&budget1*nasobok<1&&pokracovaniejemozne==1)
				{
					textcolor(LIGHTRED);
					printf(" SIZE FOR RESUME!");
					textcolor(WHITE);					
				}				
				else if(y==2&&x==9)
					printf("                      ");	
					
				
				if(y==6&&x==13&&pokracovaniejemozne==1)
				{
					if(budget1*nasobok<1)
						textcolor(LIGHTRED);
					else
						textcolor(LIGHTGREEN);
					printf(" %c %.2f$", 175, budget1);
					textcolor(WHITE);
				}					
					
				if(y==14&&x==7)
				{
					if(zvuk==1)
					{
						if(vstup==13&&status==4)
							PlaySound("zvuky/gombik.wav",NULL,SND_FILENAME|SND_ASYNC);
						textcolor(LIGHTGREEN);
						printf("  ON");
						textcolor(WHITE);
					}						
					else
					{
						textcolor(LIGHTRED);
						printf(" OFF");	
						textcolor(WHITE);
					}
							
				}
					
					
				if(pokracovaniejemozne!=1||budget1*nasobok<1)
				{
					if(y==5&&x>=0&&x<=19||y==6&&x>=0&&x<=19||y==7&&x>=0&&x<=19)
						textcolor(DARKGRAY);	
				}							
						
				switch(status)
				{						
					case 1:
					{
						if(y==0&&x>0&&x<13||y==1&&x<2||y==1&&x>10||y==2&&x<2||y==2&&x>6||y==3&&x>0&&x<13)
							textcolor(LIGHTCYAN);
						printf("%c", volba1[y][x]);
						textcolor(WHITE);
						break;	
					}
					
					case 2:
					{
						if(y==5&&x>=0&&x<=12||y==6&&x==0||y==6&&x==12||y==7&&x>=0&&x<=12)
							textcolor(LIGHTCYAN);
						printf("%c", volba2[y][x]);
						textcolor(WHITE);
						break;	
					}						
					case 3:
					{
						if(y==9&&x>=0&&x<=12||y==10&&x==0||y==10&&x==12||y==11&&x>=0&&x<=12)
							textcolor(LIGHTCYAN);
						printf("%c", volba3[y][x]);
						textcolor(WHITE);
						break;	
					}						
					case 4:
					{
						if(y==13&&x>=0&&x<=12||y==14&&x==0||y==14&&x==8||y==15&&x>=0&&x<=12)
							textcolor(LIGHTCYAN);
						printf("%c", volba4[y][x]);
						textcolor(WHITE);
						break;	
					}						
					case 5:
					{
						if(y==17&&x>=0&&x<=12||y==18&&x==0||y==18&&x==12||y==19&&x>=0&&x<=12)
							textcolor(LIGHTCYAN);
						printf("%c", volba5[y][x]);
						textcolor(WHITE);
						break;	
					}													
				}	
			}			
			printf("\n");		
		}
		textcolor(CYAN);			
		printf("\n          %c USE: ENTER and ", 16);
		putchar(24);
		printf("W ");
		putchar(25);
		printf("S or ");
		putchar(24);
		printf("8 ");
		putchar(25);
		printf("2 %c\n", 17);
		textcolor(WHITE);
		
		vstup=getch();
		
		if(vstup==119|vstup==56)
		{
			if(zvuk!=0)
				PlaySound("zvuky/gombik.wav",NULL,SND_FILENAME|SND_ASYNC);
			status--;
			if(pokracovaniejemozne!=1||budget1*nasobok<1)
			{
				if(status==2)
					status=1;
			}
			if(status<1)
				status=5;				
		}
	
		if(vstup==115||vstup==50)
		{
			if(zvuk!=0)
				PlaySound("zvuky/gombik.wav",NULL,SND_FILENAME|SND_ASYNC);
			status++;
			if(pokracovaniejemozne!=1||budget1*nasobok<1)
			{
				if(status==2)
					status=3;
			}
			if(status>5)
				status=1;
		}
		
		if(vstup==13)
		{
			if(zvuk!=0&&status!=4)
				PlaySound("zvuky/gombik.wav",NULL,SND_FILENAME|SND_ASYNC);
			switch(status)
			{
				case 1:
				{					
					menicmince++;
					if(menicmince>5)
						menicmince=1;					
					break;
					volbaceny=1;						
				}
				
				case 2:
				{
					if(pokracovaniejemozne==1)
					{
						pokracovat=1;						
						koniecmenu=1;						
					}
					else
					{
						if(zvuk!=0)
							printf("\a");						
					}
						
					break;
				}
				
				case 3:
				{
					zaciatoknovejhry();
					pokracovat=0;
					koniecmenu=1;
					break;					
				}
				
				case 4:
				{
					if(zvuk==0)
						zvuk=1;
					else
						zvuk=0;
					break;					
				}
				
				case 5:
				{
					ohre();
					break;	
				}				
			}
		}
		
		if(vstup==27)
			exit(0);
	}	
	system("cls");
}

void urcinasobok()
{
	if(menicmince==5)
		nasobok=20;	
	
	if(menicmince==1)
		nasobok=4;
	
	if(menicmince==2)
		nasobok=2;
	
	if(menicmince==3)
		nasobok=1;
	
	if(menicmince==4)
		nasobok=0.2;	
}

void pokracovanie()
{
	int a;	
	float premenne[5],cislo;
	
	fsmernik=fopen("hrac.dk", "r");	
	while(fscanf(fsmernik, "%f", &cislo)>0)
	{
        premenne[a]=cislo;
        a++;
    }    
    fclose(fsmernik);
	
	budget1=premenne[0];
	zbudget=premenne[1];
	handcislo=premenne[2];
	najvacsiavyhra=premenne[3];
	zvuk=premenne[4];						
}

void pokracovanietest()
{
	if(fsmernik=fopen("hrac.dk", "r"))
    {
        fclose(fsmernik);
        pokracovaniejemozne=1;
    }
    else
    	pokracovaniejemozne=0;
}

void save()
{
	fsmernik = fopen("hrac.dk", "w");
	fprintf(fsmernik,"%f\n", budget1);			
	fprintf(fsmernik,"%d\n", zbudget);
	fprintf(fsmernik,"%d\n", handcislo);
	fprintf(fsmernik,"%d\n", najvacsiavyhra);
	fprintf(fsmernik,"%d\n", zvuk);							
	fclose(fsmernik);
}

int main() 
{
	int a;
	
	//SRAND pre random
	srand(time(NULL));
	
	SIZEC();
	
	//TEST CI SUBOR EXISTUJE
	pokracovanietest();		
	
	textbackground(BLACK);
	textcolor(WHITE);	
	
	//nastavenie nul do pamati
	for(a=0;a<5;a++)
		vybratekarty[a]=0;
	for(a=0;a<10;a++)
		pouzitevysledky[a]=0;
	
	while(1) //CYKLUS PRE NAVRAT DO MENU!
	{
		if(vraciamsadomenu==1&&prehral!=1)
		{
			//SAVE V PRIPADE NAVRATU DO MENU
			save();						
		}		
		
		//reset cast
		tah=0;
		posuvnik=0;
		for(a=0;a<9;a++)
			cennikzvyrazni[a]=0;		
		for(a=0;a<5;a++)
			vybratekarty[a]=0;
		for(a=0;a<10;a++)
			pouzitevysledky[a]=0;
		for(a=0;a<5;a++)
			drzkartu[a]='F';
		vraciamsadomenu=0;
		
		menu();	
		urcinasobok();		
		
		if(pokracovat==0)
			budget1=zbudget;
		
		do //SAMOTNA HRA
		{
			//AUTOMATICKY SAVE
			save();
					
			//reset cast			
			tah=0;
			posuvnik=0;
			for(a=0;a<9;a++)
				cennikzvyrazni[a]=0;		
			for(a=0;a<5;a++)
				vybratekarty[a]=0;
			for(a=0;a<10;a++)
				pouzitevysledky[a]=0;
			for(a=0;a<5;a++)
				drzkartu[a]='F';
				
			//ombedz stavky
			kredity=budget1*nasobok;
						
			if(kredity<5)
			{
				for(a=1;a<6;a++)
				{
					if(kredity>=a)
						maximalnacena=a;
				}	
			}
			else	
				maximalnacena=5;
				
			if(kredity<volbaceny)
				volbaceny=1;				
						
			system("cls");
													
			tahanie();
			cennik(); //VOLBA STAVKY
			if(vraciamsadomenu!=1)
			{					
				kontrola(); //SKONTROLUJ CI HRAC NEMA HNED NA RUKE KOMBINACIU
				cennik(); //ZOBRAZ VYHERNU CENU					
				kartyz_tahhraca(); //TAH HRACA								
				tahanie();											
				kartyz_tahhraca(); 		
				kontrola();	
				cennik(); //ZOBRAZ VYHERNU CENU
				
				getch();		
				handcislo++;				
			}
		}while(vraciamsadomenu!=1);
	}
	return 0;	
}
