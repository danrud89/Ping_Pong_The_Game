//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Markup.h"
#include <vector>
#include <string.h>
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int Vx = -8;
int Vy = -8;
AnsiString leftPlayerName = "";
AnsiString rightPlayerName = "";
unsigned int leftPlayerScore = 0;
unsigned int rightPlayerScore = 0;
unsigned int turnNumber = 1;
unsigned int bounceCounter = 0;
//---------------------------------------------------------------------------
class Player
{
    std::string playerName;
    std::string playerScores;
    Player(std::string name = "", std::string score = "")
    {
          //this name -> playerName;
          //this score -> playerScore;
    }
};

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BallTimerTimer(TObject *Sender)
{
       Ball -> Top += Vy;
       Ball -> Left += Vx;

       // skucha od lewej paletki
       if(Ball->Left >= LeftPaddle->Left + LeftPaddle->Width)

       // odbicie od gornej sciany
       if (Ball -> Top <= Board -> Top) Vy *= -1;

       //odbicie od dolnej scianki
       if (Ball->Top + Ball->Height >= LowerBound->Top) Vy *= -1;

       // skucha od prawej paletki
       if (Ball->Left + Ball->Height >= RightPaddle->Left) ;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::leftPaddleUpTimer(TObject *Sender)
{
     if (LeftPaddle->Top > Board->Top +15)
     LeftPaddle -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftPaddleDownTimer(TObject *Sender)
{
     if (LeftPaddle -> Top + LeftPaddle -> Height < LowerBound -> Top - 15)
     LeftPaddle -> Top += 10;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') leftPaddleUp -> Enabled = true;
        if (Key == 'Z') leftPaddleDown -> Enabled = true;
        if (Key == VK_UP) rightPaddleUp -> Enabled = true;
        if (Key == VK_DOWN) rightPaddleDown -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') leftPaddleUp -> Enabled = false;
        if (Key == 'Z') leftPaddleDown -> Enabled = false;
        if (Key == VK_UP) rightPaddleUp -> Enabled = false;
        if (Key == VK_DOWN) rightPaddleDown -> Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightPaddleUpTimer(TObject *Sender)
{
       if (RightPaddle->Top > Board->Top +15)
       RightPaddle -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightPaddleDownTimer(TObject *Sender)
{
        if (RightPaddle -> Top + RightPaddle -> Height < LowerBound -> Top - 15)
        RightPaddle -> Top += 10;
}
//---------------------------------------------------------------------------

