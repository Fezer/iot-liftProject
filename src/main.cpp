#include <Arduino.h>
#include <Stepper.h>

int i;

int stepsPerRevolution = 65;

Stepper motor(stepsPerRevolution, 10, 11, 12, 13);

const int a = 3; // 2
const int b = 2; // 1
const int c = 8; // 7
const int d = 7; // 6
const int e = 6; // 5
const int f = 4; // 3
const int g = 5; // 4
const int dp = 9;
int pino = 2;
int digito = 0;
int andarSolicitado = -1;
int andarAtual = -1;
int andarAnterior = -1;
boolean maintenance = false;

byte displaySetSeg[4][7] = {
    {LOW, LOW, LOW, HIGH, LOW, LOW, LOW},     // Digito 0
    {LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}, // Digito 1
    {LOW, LOW, HIGH, LOW, LOW, LOW, HIGH},    // Digito 2
    {LOW, LOW, HIGH, LOW, HIGH, LOW, LOW}     // Digito 3
};

void setup()
{
  Serial.begin(9600);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

void loop()
{
  if (andarAtual <= 0)
  {
    while (andarAtual <= 0)
    {
      pino = 2;
      if (digitalRead(A0) == HIGH && digitalRead(A1) == HIGH)
      { // Pressiona botao 1 e botao 2 para entrar em modo de manutencao
        maintenance = true;
        for (int cont = 0; cont < 3; cont++)
        {
          digitalWrite(A3, LOW);
          digitalWrite(A4, LOW);
          digitalWrite(A5, LOW);
          delay(500);
          digitalWrite(A3, HIGH);
          digitalWrite(A4, HIGH);
          digitalWrite(A5, LOW);
          delay(500);
        }
        while (maintenance)
        {
          if (digitalRead(A0) == HIGH)
          {
            Serial.println("Sobe:");
            motor.setSpeed(300);
            motor.step(500);
          }
          else if (digitalRead(A1) == HIGH)
          {
            Serial.println("Desce:");
            motor.setSpeed(300);
            motor.step(-500);
          }
          else if (digitalRead(A2) == HIGH)
          {
            maintenance = false;
            digitalWrite(A3, HIGH);
            digitalWrite(A4, HIGH);
            digitalWrite(A5, HIGH);
          }
        }
      }
      else if ((digitalRead(A1) == HIGH && digitalRead(A2) == HIGH))
      { // Pressiona botao 2 e botao 3 para entrar em modo de configuracao
        for (int cont = 0; cont < 3; cont++)
        {
          digitalWrite(A3, LOW);
          digitalWrite(A4, LOW);
          digitalWrite(A5, LOW);
          delay(500);
          digitalWrite(A3, LOW);
          digitalWrite(A4, HIGH);
          digitalWrite(A5, HIGH);
          delay(500);
        }
        while (andarAtual <= 0)
        {
          if (digitalRead(A0) == HIGH)
          {
            andarAtual = 1;
            digitalWrite(A3, HIGH);
            digitalWrite(A4, LOW);
            digitalWrite(A5, LOW);
            pino = 2;
            for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
            {
              digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
              ++pino;
            }
          }
          else if (digitalRead(A1) == HIGH)
          {
            andarAtual = 2;
            digitalWrite(A3, LOW);
            digitalWrite(A4, HIGH);
            digitalWrite(A5, LOW);
            pino = 2;
            for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
            {
              digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
              ++pino;
            }
          }
          else if (digitalRead(A2) == HIGH)
          {
            andarAtual = 3;
            digitalWrite(A3, LOW);
            digitalWrite(A4, LOW);
            digitalWrite(A5, HIGH);
            pino = 2;
            for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
            {
              digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
              ++pino;
            }
          }
        }
      }
      else if (andarAtual == -1)
      {
        andarAtual = 0;
        pino = 2;
        for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
        {
          digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
          ++pino;
        }
        digitalWrite(A3, HIGH);
        digitalWrite(A4, HIGH);
        digitalWrite(A5, HIGH);
      }
    }
  }

  if (digitalRead(A0) == HIGH)
  {
    andarSolicitado = 1;
  }
  else if (digitalRead(A1) == HIGH)
  {
    andarSolicitado = 2;
  }
  else if (digitalRead(A2) == HIGH)
  {
    andarSolicitado = 3;
  }

  if (andarSolicitado > 0 && andarSolicitado != andarAtual)
  {
    pino = 2;
    switch (andarSolicitado)
    {
    case 1:
      if (andarAtual == 2)
      {
        motor.setSpeed(300);
        motor.step(-7000);
        andarAtual = andarSolicitado;
        digitalWrite(A3, HIGH);
        digitalWrite(A4, LOW);
        digitalWrite(A5, LOW);
        pino = 2;
        for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
        {
          digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
          ++pino;
        }
      }
      else if (andarAtual == 3)
      {
        motor.setSpeed(300);
        motor.step(-7000);
        digitalWrite(A3, LOW);
        digitalWrite(A4, HIGH);
        digitalWrite(A5, LOW);
        andarAtual = 2;
        pino = 2;
        for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
        {
          digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
          ++pino;
        }
        motor.setSpeed(300);
        motor.step(-7000);
        andarAtual = andarSolicitado;
        digitalWrite(A3, HIGH);
        digitalWrite(A4, LOW);
        digitalWrite(A5, LOW);
        pino = 2;
        for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
        {
          digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
          ++pino;
        }
      }
      break;
    case 2:
      if (andarAtual == 1)
      {
        motor.setSpeed(300);
        motor.step(7000);
        andarAtual = andarSolicitado;
        digitalWrite(A3, LOW);
        digitalWrite(A4, HIGH);
        digitalWrite(A5, LOW);
        pino = 2;
        for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
        {
          digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
          ++pino;
        }
      }
      else if (andarAtual == 3)
      {
        motor.setSpeed(300);
        motor.step(-7000);
        andarAtual = andarSolicitado;
        digitalWrite(A3, LOW);
        digitalWrite(A4, HIGH);
        digitalWrite(A5, LOW);
        pino = 2;
        for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
        {
          digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
          ++pino;
        }
      }
      break;
    case 3:
      if (andarAtual == 1)
      {
        motor.setSpeed(300);
        motor.step(7000);
        digitalWrite(A3, LOW);
        digitalWrite(A4, HIGH);
        digitalWrite(A5, LOW);
        andarAtual=2;
        pino = 2;
        for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
        {
          digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
          ++pino;
        }
        motor.setSpeed(300);
        motor.step(7000);
        andarAtual = andarSolicitado;
        digitalWrite(A3, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A5, HIGH);
        pino = 2;
        for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
        {
          digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
          ++pino;
        }
      }
      else if (andarAtual == 2)
      {
        motor.setSpeed(300);
        motor.step(7000);
        andarAtual = andarSolicitado;
        digitalWrite(A3, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A5, HIGH);
        pino = 2;
        for (byte contSgmnts = 0; contSgmnts < 7; ++contSgmnts)
        {
          digitalWrite(pino, displaySetSeg[andarAtual][contSgmnts]);
          ++pino;
        }
      }
      break;
    }
  }
}