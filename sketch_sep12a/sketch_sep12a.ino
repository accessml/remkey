
#define pinILed 6
#define pinBeep 7
#define pinIrSens 8

#define bitnum 32

#define B_C  523
#define B_Cs 554
#define B_Df 554
#define B_D  587
#define B_Ds 622
#define B_Ef 622
#define B_E  659
#define B_F  698
#define B_Fs 740
#define B_Gf 740
#define B_G  784
#define B_Gs 831
#define B_Af 831
#define B_A  880
#define B_As 932
#define B_Bf 932
#define B_B  988

void mtone(int n1,int n2){
  tone(pinBeep,n1,n2);
}

void xbeep(int A,float B,int C){
  if (A!=0) tone (pinBeep,A,60000/C*B);
  delay(60000/C*B);
}

void cxbeep(int A,float B,int C){
  tone (pinBeep,A,60000/C*B-10);
  delay(60000/C*B);
}

void dxbeep(int A,float B,int C){
  for(int i=0 ; i<60000/C*B/60 ; i++){
  tone (pinBeep,A,30);
  delay(30);
  tone (pinBeep,A/2,30);
  delay(30);
  }
}

void setup() {

  Serial.begin(9600);

  pinMode(pinILed,OUTPUT);
  pinMode(pinBeep,OUTPUT);
  pinMode(pinIrSens,INPUT);
  
  mtone (2000,100);
  delay(100);
  mtone (1000,100);
  delay(100);
  delay(900);
 
}

  short int bpm=100;

void loop() {

  //while(1) delay(1000);

  reconsider:

  unsigned short int recData[150]={0};
  int counter=0;
  boolean endflg=0;
  
    while (1){
      delayMicroseconds(10);
      if(digitalRead(pinIrSens)==LOW) break;
    }

    while(1){
      while(digitalRead(pinIrSens)==LOW){
        recData[counter]++;
        if (recData[counter]>1000) {
          endflg=1;
          break;
        }
        delayMicroseconds(10);
      }
      if (endflg==1) break;
      counter++;
      while(digitalRead(pinIrSens)==HIGH){
        recData[counter]++;
        if (recData[counter]>1000) {
          endflg=1;
          break;
        }
        delayMicroseconds(10);
      }
      if (endflg==1) break;
      counter++;
    }

    if (counter!=67) goto reconsider;


   boolean bitv[bitnum]={0};

   for (int i=0; i<bitnum ;i++){
    if((recData[i*2+3]/(recData[2]-5))<2){
      bitv[i]=0;
    }else{
      bitv[i]=1;
    }
   }

   unsigned short int eValue[bitnum/8]={0};

   for (int i=0; i<(bitnum/8); i++){
    eValue[i]+=bitv[i*8+0]*1;
    eValue[i]+=bitv[i*8+1]*2;
    eValue[i]+=bitv[i*8+2]*4;
    eValue[i]+=bitv[i*8+3]*8;
    eValue[i]+=bitv[i*8+4]*16;
    eValue[i]+=bitv[i*8+5]*32;
    eValue[i]+=bitv[i*8+6]*64;
    eValue[i]+=bitv[i*8+7]*128;
   }
   
   //eValue[0];
   //eValue[1];
   //eValue[2];
   //eValue[3];

    

   //Serial.println(eValue[0]);
   //Serial.println(eValue[1]);
   Serial.println(eValue[2]);
   //Serial.println(eValue[3]);

   
    delay(10);
    if (eValue[2]==1){
      mtone (B_C,120);
    }else if (eValue[2]==2){
      mtone (B_D,120);
    }else if (eValue[2]==3){
      mtone (B_E,120);
    }else if (eValue[2]==4){
      mtone (B_F,120);
    }else if (eValue[2]==5){
      mtone (B_G,120);
    }else if (eValue[2]==6){
      mtone (B_A,120);
    }else if (eValue[2]==7){
      mtone (B_B,120);
    }else if (eValue[2]==8){
      mtone (B_C*2,120);
    }else if (eValue[2]==9){
      mtone (B_D*2,120);
    }else if (eValue[2]==10){
      mtone (B_E*2,120);
    }else if (eValue[2]==11){
      mtone (B_F*2,120);
    }else if (eValue[2]==12){
      mtone (B_G*2,120);
    }else{
      mtone (B_C,120);
    }
   goto reconsider;
}
