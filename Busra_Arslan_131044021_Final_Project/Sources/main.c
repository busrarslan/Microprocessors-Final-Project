#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



//global variables
unsigned int Tcounter;      //buzzer
unsigned int answer=0;      //7-segment

///buzzer 
#define LCD_DAT PORTK
#define LCD_DIR DDRK
#define LCD_E 0x02
#define LCD_RS 0x01
#define CMD 0
#define DATA 1 



//ders slaytlarýndaki kodlardan yararlanildi.


//function prototype
interrupt (((0x10000 - Vtimch5)/2)-1) void timCh5(void);
void writeSeven(int a);
//funtion prototype
void puts2lcd(char *ptr);
void put2lcd(char c, char type);
void delay_50us(int n);
void delay_1ms(int n);
void openlcd(void);


/////////////////////DOGRU YANLIS SORU CEVAP OYUNU//////////////////

void main(void)
{
    unsigned i=0, k=0, l=0, m=0, n=0, z=0;
  
    char *soru1="TURKIYENIN EN BUYUK DAGI AGRI DAGIDIR";
    char *soru2="2X2'NÝN SONUCU 8 EDER";
    char *soru3="MICRO KELIMESI 5 HARFTEN OLUSUR";
    char *soru4="TRABZON KARADENIZ BOLGESINDEDIR";
    char *soru5="TBMM 1820 DE KURULMUSTUR";
    
    char *hata_mesaji= "YANLIS CEVAP";
    char *tebrikler= "TEBRIKLER 5'te 5 YAPTINIZ";
     
  /////buzzer interrupt variables////
     DDRB=0xFF;
     //DDRT=0xFF;
     DDRP=0xFF; 

     DDRH=0x00;
     TSCR1=0x80;    //output compare
     TSCR2=0x00;    //interrupt
   
     ///output compare//////////
     TIOS= TIOS | TIOS_IOS5_MASK;

     TIE= 0x20;
     TFLG1 = 0x20; 
  
    
       
     openlcd();
      PTP=0x0E;   //seven segment
    
    
    //SORU1//////////////////////////////////////////////////
    for(i=0; i<38; ++i) 
    {        //soru 1   
      puts2lcd(&soru1[i]);
      delay_1ms(200);
      put2lcd(0x01, CMD);
    }
    
    if(PTH == 1)           //1>> EVET  
    {
      
       TCTL1 =0x04;   ///buzzer open
        answer++;        //SEVEN SEGMENT
        writeSeven(answer);
    }
    else if(PTH == 2)      //2>> HAYIR
    {
        for(k=0; k<12; ++k)
        {       
          //put2lcd(0x0C, CMD);

          puts2lcd(&hata_mesaji[k]);
          delay_1ms(200);
          put2lcd(0x01, CMD);
        }
    }
    
     delay_1ms(1000);
    //dogru olan cevapta open yapýlan buzzer clear edildi
     TCTL1 =0x00;   //clear buzzer
    
    
    //SORU2///////////////////////////////////////////////////
    for(i=0; i<22; ++i) {       
      //put2lcd(0x0C, CMD);

      puts2lcd(&soru2[i]);
      delay_1ms(200);
      put2lcd(0x01, CMD);
    }
    
    //OYUNUN KURALLARI
    //switch secenekleri
     //1>> EVET  
     //2>> HAYIR
    
    
    if(PTH == 1) 
    {
        for(l=0; l<12; ++l)
        {     

          puts2lcd(&hata_mesaji[l]);
          delay_1ms(200);
          put2lcd(0x01, CMD);
        }
    }
    else if(PTH == 2){
      
       TCTL1 =0x04;   ///buzzer open
       puts2lcd(hata_mesaji);
       put2lcd(0x01, CMD); 
       answer++;         //SEVEN SEGMENT
       writeSeven(answer);
    }
     delay_1ms(1000);
     //dogru olan cevapta open yapýlan buzzer clear edildi
     TCTL1 =0x00;   //clear buzzer  
     
     
     //SORU3///////////////////////////////////////////////
    for(i=0; i<32; ++i) {       // soru 3
     
      puts2lcd(&soru3[i]);
      delay_1ms(200);
      put2lcd(0x01, CMD);
    }
    
    if(PTH == 1)           //1>> EVET
    {
      
       TCTL1 =0x04;   ///buzzer open
       answer++;             //SEVEN SEGMENT
       writeSeven(answer);
    }
    else if(PTH == 2)      //2>> HAYIR
    {
        for(m=0; m<12; ++m)
        {       
          //put2lcd(0x0C, CMD);

          puts2lcd(&hata_mesaji[m]);
          delay_1ms(200);
          put2lcd(0x01, CMD);
        }
    }
       
       
       
     delay_1ms(1000);    
      //dogru olan cevapta open yapýlan buzzer clear edildi
     TCTL1 =0x00;   //clear buzzer   
     
     
     //SORU4/////////////////////////////////////////////////
    for(i=0; i<36; ++i) {      // soru 4
     
 
      puts2lcd(&soru4[i]);
      delay_1ms(200);
      put2lcd(0x01, CMD);
    }
    
    if(PTH == 1)           //1>> EVET  
    {
      
       TCTL1 =0x04;   ///buzzer open
       answer++;                //SEVEN SEGMENT
       writeSeven(answer);
    }
    else if(PTH == 2)      //2>> HAYIR
    {
        for(n=0; n<12; ++n)
        {       
          //put2lcd(0x0C, CMD);

          puts2lcd(&hata_mesaji[n]);
          delay_1ms(200);
          put2lcd(0x01, CMD);
        } 
    }
    
     delay_1ms(1000);
    //dogru olan cevapta open yapýlan buzzer clear edildi
    TCTL1 =0x00;   //clear buzzer   
    
     //SORU5//////////////////////////////////////////////////
    for(i=0; i<25; ++i) {       //soru 5
      puts2lcd(&soru5[i]);
      delay_1ms(200);
      put2lcd(0x01, CMD);
    }
    
        
    if(PTH == 1)           //1>> EVET  
    {
       for(z=0; z<12; ++z)
        {       
          //put2lcd(0x0C, CMD);

          puts2lcd(&hata_mesaji[z]);
          delay_1ms(200);
          put2lcd(0x01, CMD);
        }
    }
    else if(PTH == 2)      //2>> HAYIR
    {
      
       TCTL1 =0x04;   ///buzzer open
       answer++;                //SEVEN SEGMENT
       writeSeven(answer);
    }
       
      delay_1ms(1000);  
     //dogru olan cevapta open yapýlan buzzer clear edildi
     TCTL1 =0x00;   //clear buzzer 
   
 

    
   
    //Tum Sorular dogru bilinirse 
   if(answer == 5) 
   {
      
      for(i=0; i<27; ++i) {      
          puts2lcd(&tebrikler[i]);
          delay_1ms(200);
          put2lcd(0x01, CMD);
      } 
   }
    
   
       
    
      /////LED////////////////////////////////
    //en sonki skor durumunu lede bastirdim.
    PORTB= answer; 
    
    
    ///////////////////////////////////////////                  
  
    
    __asm(swi);


	EnableInterrupts;


  for(;;) {
    _FEED_COP(); 
  } 
  
  
  
}


///////////////////////FUNCTIONSS////////////////////////////////
//output compare
//interrrupt
interrupt (((0x10000 - Vtimch5)/2)-1) void timCh5(void) {
         
        TFLG1 = 0x20; 
          
            
        Tcounter=TCNT;
        
        
        if(PTH == 0){
          //2500 Hz
           TC5= Tcounter + 9600;
           PORTB=1;             //led
        }
        else if(PTH == 1){
          //3000 Hz
           TC5= Tcounter + 8000;
            PORTB=3;           //led
        }
        else if(PTH == 2) {
          //3500 Hz
           TC5= Tcounter + 6858;
          PORTB=7;            //led
        }
        else if(PTH == 3){
          //4000 Hz
           TC5= Tcounter + 6000;
         PORTB=0xFF;          //led
        }
    
}




////////////////////////LCD FUNCTIONS//////////////
void openlcd(void){
  
       LCD_DIR=0xFF;                      
       delay_1ms(100);
       put2lcd(0x28,CMD);
       put2lcd(0x0F,CMD);
       put2lcd(0X06,CMD);
       put2lcd(0x01,CMD);
             
}


void puts2lcd(char *ptr)               //stringi almasi icin 
{
  while(*ptr)
  {
       put2lcd(*ptr, DATA);
       delay_50us(1);
       ++ptr; 
  } 
}


void put2lcd(char c, char type)      //istenilen karakterlerde string 2 parametreli
{
      char chi_1, chi_2;
      chi_1= c & 0x0F;
      chi_2= c & 0xF0;
      
      chi_1= chi_1<<2;       //shift
      chi_2= chi_2>>2;
      
       LCD_DAT &= (~LCD_RS);
      
      
      if(type== DATA)
          LCD_DAT = chi_2 | LCD_RS;        //high
      else
          LCD_DAT = chi_2;
      
      LCD_DAT |= LCD_E;
      
      __asm(nop);
      __asm(nop);
      __asm(nop);
      
      
      
      LCD_DAT &= (~LCD_E);
      
         LCD_DAT &= (~LCD_RS);
      
      if(type==DATA)                         //low
        LCD_DAT = chi_1 | LCD_RS;
      else
        LCD_DAT = chi_1;
      
      
      LCD_DAT |= LCD_E;
      
      __asm(nop);
      __asm(nop);
      __asm(nop);
      
      
      LCD_DAT &= (~LCD_E);
      delay_50us(10);
      delay_1ms(2);
      
}

//DELAY
void delay_50us(int n) {              //microsaniye
     unsigned int i=0, j=0;
     
     for(i=0; i<n ; ++i)
        for(j=0; j<20; ++j);
   
}


void delay_1ms(int n) {                //milisaniye
     unsigned int i=0, j=0;
     
     for(i=0; i<n ; ++i)
        for(j=0; j<4000; ++j);
  
  
}


//7-segment
void writeSeven(int a) {


    if(a==0)
        PORTB=0x3F;
    else if(a==1)
          PORTB=0x06;
    else if(a==2)
          PORTB=0x5B;
    else if(a==3)
          PORTB=0x4F;
    else if(a==4)
          PORTB=0x66;
    else if(a==5)
          PORTB=0x6D;

  
}























