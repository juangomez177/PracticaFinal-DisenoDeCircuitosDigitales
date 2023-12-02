// C++ code

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Frame del Dinosaurio
byte DINO_PARADO_PARTE_1[8] = {B00000, B00000, B10000, B11001, B01111, B00111, B00011, B00010};
byte DINO_PARADO_PARTE_2[8] = {B01110, B01011, B01111, B11000, B11100, B11000, B11000, B01000};
byte DINO_PIE_DERE_PART_1[8] = {B00000, B00000, B10000, B11001, B01111, B00111, B00011, B00010};
byte DINO_PIE_DERE_PART_2[8] = {B01110, B01011, B01111, B11000, B11100, B11000, B11000, B00000};
byte DINO_PIE_IZQU_PART_1[8] = {B00000, B00000, B10000, B11001, B01111, B00111, B00011, B00000};
byte DINO_PIE_IZQU_PART_2[8] = {B01110, B01011, B01111, B11000, B11100, B11000, B11000, B01000};

// Frame de los cactus
byte DOS_RAMAS_PART_1[8] = {B10100, B10100, B10101, B10101, B11111, B00100, B00100, B00100};
byte DOS_RAMAS_PART_2[8] = {B00100, B00101, B00101, B10101, B11111, B00100, B00100, B00100};
byte DOS_RAMAS_PART_3[8] = {B00000, B00100, B10100, B10100, B11111, B00101, B00100, B00100};

// Frame de la ave
byte AVE_ALAS_PART1[8] = {B00001, B00001, B00100, B01110, B11111, B00001, B00001, B00000};
byte AVE_ALAS_PART2[8] = {B00000, B10000, B11000, B11100, B11111, B11100, B11110, B11000};
byte AVE_ALAS2_PART1[8] = {B00100, B01110, B11111, B00011, B00001, B00001, B00001, B00001};
byte AVE_ALAS2_PART2[8] = {B00000, B11000, B11111, B11100, B11110, B11000, B10000, B00000};

// Deninición de variables
int columna_dino1 = 1;
int columna_dino2 = 2;
int fila_dino = 1;
unsigned long reloj = 0; // para usar la funcion millis en vez de delay
int periodo = 100;       // es el periodo en milisegundo
int flag = 1;
int fila_rama = 0;
int columna_rama = 13;
int periodo2 = 100;
unsigned long reloj2 = 0;
int a = 0;
int b = 1;
int c = 2;
int d = 0;
unsigned long reloj3 = 0;
int periodo3 = 100;
int puntos = 0;
int punto2 = 0;
int numerorandom = 0;
int columnaave = 13;
int senalactual = 0;
int senalantigua = 0;
int e = 13;
int aceleracion = 1;
int switchConm = 7;
int switchValue = 0;
int ledV = 8;
int ledR = 9;
int alarma = 6;
bool nuevoJuego = false;

void setup()
{
    lcd.begin(16, 2);
    lcd.createChar(0, DINO_PARADO_PARTE_1);
    lcd.createChar(1, DINO_PARADO_PARTE_2);
    lcd.createChar(2, DINO_PIE_DERE_PART_1);
    lcd.createChar(3, DINO_PIE_DERE_PART_2);
    lcd.createChar(4, DINO_PIE_IZQU_PART_1);
    lcd.createChar(5, DINO_PIE_IZQU_PART_2);

    pinMode(switchConm, INPUT);
    pinMode(ledV, OUTPUT);
    pinMode(ledR, OUTPUT);
    pinMode(alarma, OUTPUT);

    numerorandom = random(0, 4); // Se inicializa el random con el tipo de obstáculo
}
void loop()
{

    // Lee el Switch
    switchValue = digitalRead(switchConm);

    // Se enciende el juego
    if (switchValue == 1)
    {

        digitalWrite(ledV, HIGH);
        digitalWrite(ledR, LOW);

        if (nuevoJuego == false)
        {

            lcd.clear();
            lcd.setCursor(3, 0);
            lcd.print("INICIANDO");
            delay(1000);
            lcd.clear();

            nuevoJuego = true;
        }

        // Retardo para los pies del dinosaurio
        if (millis() > reloj + periodo)
        {
            reloj = millis();
            if (flag == 1)
            {
                flag = 2;
            }
            else if (flag == 2)
            {
                flag = 1;
            }
        }

        // Retardo para la velocidad de los obstáculos
        if (millis() > reloj2 + periodo2)
        {
            reloj2 = millis();

            columna_rama = columna_rama - 1;
            if (columna_rama < 0)
            {
                columna_rama = 13;
                periodo2 = periodo2 - aceleracion; // aceleracion
                numerorandom = random(0, 4);       // se obtiene un nuevo random; ya que, es cada vez que regresa a la columna 13
            }

            e = columna_rama + 1;
            lcd.setCursor(e, 1); // limpio abajo
            lcd.print(" ");

            e = columna_rama + 1;
            lcd.setCursor(e, 0); // limpio arriba
            lcd.print(" ");

            lcd.setCursor(0, 1); // limpio arriba
            lcd.print(" ");

            lcd.setCursor(0, 0);
            lcd.print(" ");

            a = 1;
        }

        if (d == 0)
        {
            if (flag == 1)
            {
                lcd.setCursor(columna_dino1, fila_dino);
                lcd.write(byte(2));
                lcd.setCursor(columna_dino2, fila_dino);
                lcd.write(byte(3));
            }
            if (flag == 2)
            {
                lcd.setCursor(columna_dino1, fila_dino);
                lcd.write(byte(4));
                lcd.setCursor(columna_dino2, fila_dino);
                lcd.write(byte(5));
            }
        }

        if (a == 1)
        {
            // Seleccione como obstáculo el cactus 1
            if (numerorandom == 1)
            {
                fila_rama = 1;
                lcd.createChar(6, DOS_RAMAS_PART_1);
                lcd.setCursor(columna_rama, fila_rama);
                lcd.write(byte(6));
            }

            // Seleccione como obstáculo el cactus 2
            else if (numerorandom == 2)
            {
                fila_rama = 1;
                lcd.createChar(7, DOS_RAMAS_PART_2);
                lcd.setCursor(columna_rama, fila_rama);
                lcd.write(byte(7));
            }

            // Seleccione como obstáculo el cactus 3
            else if (numerorandom == 3)
            {
                fila_rama = 1;
                lcd.createChar(8, DOS_RAMAS_PART_3);
                lcd.setCursor(columna_rama, fila_rama);
                lcd.write(byte(8));
            }

            // Seleccione como obstáculo el ave
            else
            {
                columnaave = columna_rama;
                columnaave = columnaave - 1;
                fila_rama = 0;

                if (flag == 1)
                {

                    lcd.createChar(6, AVE_ALAS_PART1);
                    lcd.setCursor(columnaave, fila_rama);
                    lcd.write(byte(6));

                    lcd.createChar(7, AVE_ALAS_PART2);
                    lcd.setCursor(columna_rama, fila_rama); // columna rama porque debe estar a la izquierda de columan ave
                    lcd.write(byte(7));
                }
                if (flag == 2)
                {

                    lcd.createChar(8, AVE_ALAS2_PART1);
                    lcd.setCursor(columnaave, fila_rama);
                    lcd.write(byte(8));

                    lcd.createChar(9, AVE_ALAS2_PART2);
                    lcd.setCursor(columna_rama, fila_rama); // columna rama porque debe estar a la izquierda de columan ave
                    lcd.write(byte(9));
                }
            }

            a = 0;
        }

        // Condiciones de choque
        // Si ocurre en el priner renglon (Arriba)
        if (digitalRead(13) == HIGH && (columna_rama == 1 || columna_rama == 2 || columnaave == 1 || columnaave == 2) && fila_rama == 0)
        {

            nuevoJuego = false;

            digitalWrite(ledV, LOW);
            digitalWrite(ledR, HIGH);

            lcd.clear();
            lcd.setCursor(4, 0);
            lcd.print("GAME OVER");
            lcd.setCursor(2, 1);
            lcd.print("PUNTUACION ");
            lcd.print(punto2);
            delay(3000);
            lcd.clear();
            columna_rama = 15;
            periodo2 = 100;
            puntos = 0;
            punto2 = 0;
            periodo2 = 100;
        }

        // Si ocurre en segundo renglon (Abajo)
        if ((columna_rama == b || columna_rama == c) && fila_rama == 1)
        {
            nuevoJuego = false;

            digitalWrite(ledV, LOW);
            digitalWrite(ledR, HIGH);

            lcd.clear();
            lcd.setCursor(4, 0);
            lcd.print("GAME OVER");
            lcd.setCursor(2, 1);
            lcd.print("PUNTUACION ");
            lcd.print(punto2);
            delay(3000);
            lcd.clear();
            columna_rama = 15;
            periodo2 = 100;
            puntos = 0;
            punto2 = 0;
            periodo2 = 100;
        }

        // Cambio de renglon (Salto)
        if (digitalRead(13) == HIGH)
        {

            b = 50; // bc con un un valor mayor a 15 para que no coincida con el movimiento de la columna
            c = 50;

            if (d == 0)
            {
                lcd.setCursor(0, 1); // LIMPIA ABAJO
                lcd.print("    ");
            }
            d = 1;

            lcd.setCursor(columna_dino1, 0);
            lcd.write(byte(2));
            lcd.setCursor(columna_dino2, 0);
            lcd.write(byte(3));
        }
        else
        {
            b = 1; // que regrese a su valor de inicio
            c = 2;
            d = 0;
        }

        // Retardo para la suma de puntos
        if (millis() > reloj3 + periodo3)
        {
            reloj3 = millis();
            lcd.setCursor(14, 1);
            lcd.print(puntos);

            puntos = puntos + 1;

            if (puntos == 100)
            {
                puntos = 0;
                punto2 = punto2 + 1;

                tone(alarma, 2500);
                delay(200);
                noTone(alarma);
            }
        }
        lcd.setCursor(14, 1);
        lcd.print(puntos);
        lcd.setCursor(14, 0);
        lcd.print(punto2);

        // detector de cambio de estado
        senalactual = digitalRead(13);
        if (senalactual != senalantigua)
        {
            lcd.setCursor(1, 0);
            lcd.print("  ");
        }
        senalantigua = senalactual;
    }

    // Se espera que el juego comience
    else
    {
        nuevoJuego = false;

        digitalWrite(ledV, LOW);
        digitalWrite(ledR, LOW);

        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("PRESS START");
        delay(500);
        lcd.clear();
        delay(200);
    }
}