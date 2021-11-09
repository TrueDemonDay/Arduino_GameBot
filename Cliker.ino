#include <Mouse.h>
#include <MouseTo.h>
#include "GyverButton.h"

GButton butt1(3);
int SUPER_DELAY = 1000 ;
int BIG_DELAY = 50;
int LOW_DElAY = 25;
int GLOBAL_F = 0;

void setup()
  {
    //переключатель, инициирующий нажатие кнопки мыши
    pinMode(5,OUTPUT);
    pinMode(7,OUTPUT);
    //переключатель, который будет прерывать нажатие кнопки
    Mouse.begin();
    MouseTo.setCorrectionFactor(1);
    Serial.begin(9600);
  }
    
//------------------------------------------------------------------------------

int EventButton(int x)
{
  return (200+50*(x-1));
}    
//------------------------------------------------------------------------------

void MouseMove(int x, int y, int f)
{
    MouseTo.setTarget(x, y);
    while (MouseTo.move() == false) {} 
    if (f==1) {OneClick();}
}
//------------------------------------------------------------------------------

void SmartDelay(int n)
{
  int i=0;
  while ((i<n) and (GLOBAL_F != 0))
    {
      CheckButtClick();
      delay(1);
      i++;
    }
}

//------------------------------------------------------------------------------

void OneWorldReset(int n, int nn, bool f)
  {
    CheckButtClick();
    MobClick(1);
    LvlUp(nn,f);
    UseSkills(n); 
    WorldReset();
  }
  
//------------------------------------------------------------------------------

void CheckButtClick()
  {
    butt1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
    
    if (butt1.isSingle()) 
      {
        if (GLOBAL_F !=0)
          {
            GLOBAL_F = 0;
            digitalWrite(7,0);
            digitalWrite(5,0);
          }
        else
          {
            GLOBAL_F = 1;
            digitalWrite(7,1);
            digitalWrite(5,0);
          }
        Serial.println("Single");
      }     // проверка на один клик
    if (butt1.isDouble()) 
      {
        GLOBAL_F = 2;
        digitalWrite(7,0);
        digitalWrite(5,1); 
        Serial.println("Double");
      }     // проверка на двойной клик
    if (butt1.isTriple()) 
      {
        GLOBAL_F = 3; 
        Serial.println("Triple");
        digitalWrite(7,1);
        digitalWrite(5,1);
      }     // проверка на тройной клик
  }

//------------------------------------------------------------------------------

void OneClick()
  {
    CheckButtClick();
    if (GLOBAL_F != 0)  
      {
        SmartDelay(LOW_DElAY);
        CheckButtClick();
        Mouse.press();  
        Mouse.release();   
      } 
  }

//------------------------------------------------------------------------------

void MobClick(int n)
  {
    CheckButtClick();
    int i=0;
    MouseMove(890, 270, 0); //Кликнуть по мобу, и закрыть рекламу
    while ((i<n) and (GLOBAL_F != 0))
      {
        OneClick();
        i++;
      }
       
  }

//------------------------------------------------------------------------------

void LvlUp(int n, bool f)
  {
    CheckButtClick();
    int i=0;
    MouseMove(500, 525, 1);//Качаем х200 прокачку   
    while ((i<n) and (GLOBAL_F != 0))
      {      
        CheckButtClick();
        MouseMove(410, 330, 0);
        CheckButtClick();
        SmartDelay(SUPER_DELAY);
        OneClick();
        MouseMove(590, 330, 0);
        CheckButtClick();
        SmartDelay(SUPER_DELAY);
        OneClick();
        if (((i==0) or (i==3)) and (f>0))
          {
            MouseMove(500, 325, 1);
            //MouseMove(500, 425, 1);
            SmartDelay(150-BIG_DELAY);
            CheckButtClick();
          }
        i++;
      }    
  }

//------------------------------------------------------------------------------

void UseSkills(int n)
  {
    int i=0;
    while (((i<n) and (i<8))and (GLOBAL_F != 0))
      {
        MouseMove(680, 200+50*i, 1);
        i++;
      } 
  }

//------------------------------------------------------------------------------

void WorldReset()
  {
    CheckButtClick();
    if (GLOBAL_F == 0)
      return;
    MouseMove(1120, EventButton(1), 1); //Летим к ресету
    MouseMove(620, 480, 1); //Летим к потверждению ресета
    MouseMove(700, 425, 0); //Летим к награде ресета
    CheckButtClick();
    SmartDelay(1000-BIG_DELAY);
    OneClick(); 
  }
  
//------------------------------------------------------------------------------

void FaplogyEventReset()
  {
        if (GLOBAL_F == 0)
          return;
        MouseMove(50, 60, 1);// Летим зайдем на самих титанов
        MouseMove(63, 35, 1);// Летим ресет нажмем в хроме
        SmartDelay(7000);
        MouseMove(915, 125, 1); //Закрываем рекламу    
        MouseMove(1008, 127, 1);//Закрываем рекламу эвента
        //MouseMove(1008, 107, 1);//Закрываем доп рекламу эвента
        MouseMove(1120, EventButton(2), 1); //Летим к эвенту
        
        SmartDelay(SUPER_DELAY); //Ждём загрузку эвента
        
        MouseMove(600, 500, 1); //Забрать монетки
        MouseMove(700, 350, 1); //Нажать ок
        MouseMove(1100, 105, 1); //Выйти из эвента 
  }
  
//------------------------------------------------------------------------------

void loop() 
  {
    CheckButtClick();
    if (GLOBAL_F == 1)
      {
        OneClick();
      }
      
    if (GLOBAL_F == 2)
      {
        //MouseMove(1120, EventButton(2), 0); SmartDelay(1000); //тестовая часть для полётов
        OneWorldReset(0,6,0);
      }
      
    if (GLOBAL_F == 3)
      {
        int i=0;
        while ((i<5) and (GLOBAL_F >0))
          {
            OneWorldReset(2,6,1);
            i++;
          }
        FaplogyEventReset();  
      }
  }
