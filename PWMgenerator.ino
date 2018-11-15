unsigned int num = 0; //0x0010 ~ 0X00ff
unsigned int clicknum = 0; //按下次数
unsigned int clicknumnum = 0;

void led_show(int num){
  for(unsigned int i = 0; i < 4; i++)
  {
    //关闭4个输出
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);

    //获取当前位
    unsigned int n = 0;
    switch(i){
      case 0:
        n = num / 1000 % 10;
        break;
      case 1:
        n = num / 100 % 10;
        break;
      case 2:
        n = num / 10 % 10;
        break;
      case 3:
        n = num % 10;
    }
  
    switch(n){
      case 0:
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        break;
      case 1:
        digitalWrite(0, LOW);
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        break;
      case 2:
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        break;
      case 3:
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        break;
      case 4:
        digitalWrite(0, LOW);
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        break;
      case 5:
        digitalWrite(0, HIGH);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        break;
      case 6:
        digitalWrite(0, HIGH);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        break;
      case 7:
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        break;
      case 8:
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        break;
      case 9:
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
    }
  
    digitalWrite(10 + i, HIGH); //点亮
    delay(2); //显示2ms
  }
}

void setup() {
  // put your setup code here, to run once:
  
  //LED
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  //按键
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  
  //PWM
  pinMode(9, OUTPUT);
  TCCR1A=0x80;//匹配时清OC1A，计数值满时置位OC1A，8.相位与频率修正PWM模式
  TCCR1B=0x12;//8预分频
  ICR1=0X00ff;//MAX:0X0FFF
  OCR1AH=0x00;//占空比
  OCR1AL=0x80;//MAX:<ICR1

  num = 0x0010;
  OCR1AL = num/2; //占空比为一半
  ICR1=num;       //PWM频率
  clicknum = 0;
  clicknumnum = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

  //LED
  led_show(num);

  //按键
  if(digitalRead(A3)==LOW)
  {
    if(clicknum == 0){
      switch(num){
        case 0x0002:
          num = 0x0010;
          break;
        case 0x0010:
          num = 0x0080;
          break;
        case 0x0080:
          num = 0x00ff;
          break;
        default:
        case 0x00ff:
          num = 0x0002;
          break;
      }
      OCR1AL = num/2; //占空比为一半
      ICR1=num;       //PWM频率
    }
    clicknum++;
  }
  else if(digitalRead(A4)==LOW)
  {
    if((clicknum == 0 || clicknum > 64 || clicknumnum > 8) && num>0x0002){
      num--;
      OCR1AL = num/2; //占空比为一半
      ICR1=num;       //PWM频率
      if(clicknum > 64)
      {
        clicknum = 48;
        clicknumnum++;
      }
    }
    clicknum++;
  }
  else if(digitalRead(A5)==LOW)
  {
    if((clicknum == 0 || clicknum > 64 || clicknumnum > 8) && num<0X00ff){
      num++;
      OCR1AL = num/2; //占空比为一半
      ICR1=num;       //PWM频率
      if(clicknum > 64)
      {
        clicknum = 48;
        clicknumnum++;
      }
    }
    clicknum++;
  }
  else{
    clicknum = 0;
    clicknumnum = 0;
  }
}
