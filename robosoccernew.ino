
//Receiver signal pins
double ch1_pin = 3;  //PWM pin left right stick
double ch2_pin = 5;  //PWM pin forward back stick

//Right motor driver pins
int R_EN_right = 2; 
int L_EN_right = 4;
int R_PWM_right = 6; //PWM pin
int L_PWM_right = 9; //PWM pin

//Left motor driver pins
int R_EN_left = 7; 
int L_EN_left = 8;
int R_PWM_left = 10; //PWM pin
int L_PWM_left = 11; //PWM pin

// ---**--   Rx threshold values - Update based on your TX values
//ch2
int Ch2_start_Fwd = 1492;                        
int Ch2_End_Fwd = 1990;

int Ch2_start_Bac = 1479;
int Ch2_End_Bac = 990;

//ch1
int Ch1_start_right = 1500;   

int Ch1_End_right = 1990;

int Ch1_start_left = 1407;
int Ch1_End_left = 980;

// ---------***---------------***----------

void setup()
{
  Serial.begin(9600);

  pinMode(3,INPUT);
  pinMode(5,INPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT); 
  pinMode(9,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT); 
  pinMode(11,OUTPUT);
}

void loop()
{
 


//Receiver signal pins data
double ch1 = pulseIn(3,HIGH);
double ch2 = pulseIn(5,HIGH);

Serial.print("ch1: ");
Serial.println(ch1);
//Serial.print("\t");
Serial.print("ch2: ");
Serial.print(ch2);
//Serial.println("");

//Speed mapping for right motor driver
//ch1 
//int spdFwd_RightLeft = map(ch1, Ch1_start_Fwd, Ch1_End_Fwd, 0, 255);   
//int spdBac_RightLeft = map(ch1, Ch1_start_Bac, Ch1_End_Bac, 0, 255);    
int forwadval = map(ch2, Ch2_start_Fwd, Ch2_End_Fwd, 0, 255);   
int backval = map(ch2, Ch2_start_Bac, Ch2_End_Bac, 0, 255);    


//ch2
int rightval = map(ch1, Ch1_End_right,Ch1_start_right, 0, 255);   
int leftval = map(ch1,Ch1_End_left ,  Ch1_start_left, 0, 255);    

//combined movemnets
int right_lftrgt_val = map(ch1, Ch1_End_right,Ch1_start_right, 255, 0);   
int left_lftrgt_val = map(ch1, Ch1_End_left,Ch1_start_left, 255, 0);  




digitalWrite(R_EN_right, HIGH);
digitalWrite(L_EN_right, HIGH);
digitalWrite(R_EN_left, HIGH);
digitalWrite(L_EN_left, HIGH);

if((ch1==0)&&(ch2==0))
{     
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,0);
}
//FWD
else if((ch2>Ch2_start_Fwd)&&(ch1>Ch1_start_left )&&(ch1<Ch1_start_right))
{     
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,forwadval); 
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,forwadval); 
}


//Left
else if((ch1<Ch1_start_left && ch2<Ch2_start_Fwd  && ch2>1396))
{     
 Serial.println("Left");

analogWrite(R_PWM_right,rightval);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,rightval);
}

//turnn LEFT forward
else if((ch1<1450 && ch2>1500))
{ 
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,left_lftrgt_val);
}

//turnn Left backward
else if((ch1<1450 && ch2<1441))
{ 

analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,left_lftrgt_val);
analogWrite(L_PWM_left,0);
}
//Right
else if((ch1>Ch1_start_right && ch2<Ch2_start_Fwd  && ch2>1439))
{ 
  Serial.println("Right");
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,leftval);
analogWrite(R_PWM_left,leftval);
analogWrite(L_PWM_left,0);
}
//turnn Right forward
else if((ch1>1450 && ch2>1500))
{ 
  Serial.println("Right fwd");
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,right_lftrgt_val);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,0);

}
//turnn Right backward
else if((ch1>1500 && ch2<1480))
{
  Serial.println("Right back");
analogWrite(R_PWM_right,right_lftrgt_val);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,0);
}


//BACK
else if((ch2<Ch2_start_Bac)&&(ch1>Ch1_start_left )&&(ch1<Ch1_start_right))
{  

//--------------------------------------
Serial.println("Going back");
analogWrite(R_PWM_right,backval);
analogWrite(L_PWM_right,0); 
analogWrite(R_PWM_left,backval);
analogWrite(L_PWM_left,0); 


/*
//Right

analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,backval); 
analogWrite(R_PWM_left,backval);
analogWrite(L_PWM_left,0); 
*/
}
else
{     
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,0);
}

}
