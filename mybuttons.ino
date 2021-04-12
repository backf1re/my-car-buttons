// библиотека для потенциометра, скачать.
// скачивать тут https://sites.google.com/site/tfagerscode/home/digipotx9cxxx
#include <DigiPotX9Cxxx.h>

//задаем на каких пинах сидит управление потенциометром (INC,CS,U/D)
DigiPot pot(2,5,4);

//задаем начальные значение переменных
int i=0;
int prevButton=0;

// Коды имеющихся на руле кнопок
const int VOL_UP=1;
const int VOL_DN=2;
const int PREV_TR=3;
const int NEXT_TR=4;
const int MODE=5;
const int MUTE=6;

// задаем аналоговый пин, на котором мы считываем сопротивление нажатой на руле кнопки
int wheelPin=A5;

void setup()
{               
pinMode(wheelPin, INPUT);
pot.reset();
}


// Эта функция читает сопротивление с кнопок на руле и возвращает код нажатой кнопки, либо 0
int getR()
{
// читаем сопротивление (на самом деле напряжение, конечно) на аналоговом пине
int r=analogRead(wheelPin);

//Serial.println(r); //можно вывести в терминал значение нажатой кнопки
 
// Ищем, какая кнопка соответствует этому сопротивлению. 
// Данные значения сопротивлений подходят для Suzuki Swift, для других автомобилей числа будут другие.
if (r>=4 && r<=9) return(VOL_UP);
if (r>=14 && r<=20) return(VOL_DN);
if (r>=99 && r<=106) return(PREV_TR);
if (r>=53 && r<=59) return(NEXT_TR);
if (r>=27 && r<=33) return(MODE);
if (r>=0 && r<=2) return(MUTE);

// если ни одна из кнопок не нажата, возвращаем 0
return (0);
}

// ОСНОВНОЙ ЦИКЛ
void loop()
{
int currButton=getR(); // заносим в переменную currButton код нажатой кнопки
if (currButton!=prevButton) // если значение поменялось с прошлого раза
{
delay(10);
currButton=getR(); // ждем 10ms и читаем еще раз, чтобы исключить "дребезг" кнопки

if (currButton!=prevButton) // если код кнопки точно поменялся с прошлого раза
{
prevButton=currButton;     // сохраняем новое значение в переменную prevButton

// Выставляем сопротивление на потенциометре, тем самым посылаем команду на магнитолу.
// Значения сопротивлений даны для Pioneer, для магнитол других марок числа будут другие.
    
     
pot.reset(); 
switch(currButton)
{
case VOL_UP: pot.set(18); break;  // 16k
case VOL_DN: pot.set(27); break;  // 24k   
case PREV_TR: pot.set(13); break;  // 11k
case NEXT_TR: pot.set(9); break;  // 8k
case MODE: pot.set(2); break;  // 1.6k
case MUTE: pot.set(3); break;  // 3k
default: pot.reset(); break; // 0k
}
}
}
delay(5);
}
