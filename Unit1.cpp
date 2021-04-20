//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Markup.h"
#include <windows.h>
#include "mmsystem.h"
#include <vector>
#include <string.h>
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int Vx = -8;
int Vy = -8;
AnsiString leftPlayerName = "ZIELONY";
AnsiString rightPlayerName = "CZERWONY";
int greenPlayerScore = 0;
int redPlayerScore = 0;
int turnNumber = 1;
int bounceCounter = 0;

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

       // skucha lewej paletki
       if(Ball->Left + Ball->Width <= LeftPaddle->Left + LeftPaddle->Width - 10)
       {
         BallTimer->Enabled = false;
         Ball->Visible = false;
         ScorePoint->Caption = "Punkt zdobywa gracz "+ rightPlayerName + "!";
         redPlayerScore ++;
         ScorePoint->Visible = true;
         turnNumber++;
         PlaySound(TEXT("ScorePoint.wav"), NULL, SND_FILENAME | SND_ASYNC);
       }

       // odbicie od gornej sciany
       if (Ball -> Top <= Board -> Top)
       {
                Vy *= -1;
       }
       //odbicie od dolnej scianki
       if (Ball->Top + Ball->Height >= LowerBound->Top)
       {
                Vy *= -1;
       }

       // skucha  prawej paletki
       if (Ball->Left + Ball->Width >= RightPaddle->Left + RightPaddle->Width + 15)
       {
                BallTimer->Enabled = false;
                Ball->Visible = false;
                ScorePoint->Caption = "Punkt zdobywa gracz "+leftPlayerName+ "!";
                greenPlayerScore ++;
                ScorePoint->Visible = true;
                turnNumber++;
                PlaySound(TEXT("ScorePoint.wav"), NULL, SND_FILENAME | SND_ASYNC);
       }

       //odbicie od  lewej paletki
        else if(Ball->Top+Ball->Height/2 > LeftPaddle->Top && Ball->Top < LeftPaddle->Top+LeftPaddle->Height &&
         Ball->Left < LeftPaddle->Left+LeftPaddle->Width)
   {
       if(Vx < 0)
       {
         Vx = - Vx;
         //szybsze odbicie od lewej paletki
         if(Ball->Top+Ball->Height/2 > LeftPaddle->Top+LeftPaddle->Height/2-60 &&
         Ball->Top < LeftPaddle->Top+LeftPaddle->Height/2+30)
         {
             Vx *= 1.2;
             Vy *= 1.2;
         }
       }
       bounceCounter ++;
       PlaySound(TEXT("pingPong.wav"), NULL, SND_FILENAME | SND_ASYNC);
   }
      //odbicie od  prawej paletki
  else if(Ball->Top+Ball->Height/2 > RightPaddle->Top &&
   Ball->Top < RightPaddle->Top+RightPaddle->Height && Ball->Left+Ball->Width > RightPaddle->Left)
   {
       if(Vx > 0)
       {
         Vx = - Vx;
         //szybsze odbicie
         if(Ball->Top+Ball->Height/2 > RightPaddle->Top+RightPaddle->Height/2-60&&
         Ball->Top < RightPaddle->Top+RightPaddle->Height/2+30)
         {
             Vx *= 1.2;
             Vy *= 1.2;
         }
       }
        bounceCounter ++;
        PlaySound(TEXT("pingPong.wav"), NULL, SND_FILENAME | SND_ASYNC);
   }
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
        if(Key == VK_SPACE)
        {
           BallTimer->Enabled = false;
           Pauza->Visible=true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') leftPaddleUp -> Enabled = false;
        if (Key == 'Z') leftPaddleDown -> Enabled = false;
        if (Key == VK_UP) rightPaddleUp -> Enabled = false;
        if (Key == VK_DOWN) rightPaddleDown -> Enabled = false;
        if(Key == VK_SPACE)
        {
           BallTimer->Enabled = true;
           Pauza->Visible=false;
        }
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

void __fastcall TForm1::ScorePointClick(TObject *Sender)
{
          Ball -> Left = Board->Width/2 ;
          Ball -> Top = Board->Top + Board->Height/2  ;
          Ball->Visible = true;
          Vx = -6;
          Vy = -6;
          BallTimer->Enabled = true;
          LeftPaddle->Enabled = true;
          RightPaddle->Enabled = true;
          ScorePoint->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewGameClick(TObject *Sender)
{
   BallTimer -> Enabled = false;
  if(greenPlayerScore != 0 || redPlayerScore != 0)
  {
      if (Application -> MessageBox("Czy na pewno chcesz rozpocz¹æ now¹ grê ?",
        "PotwierdŸ", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
      turnNumber = 1;
      bounceCounter = 0;
      greenPlayerScore = 0;
      redPlayerScore = 0;
      Vx = -6;
      Vy = -6;
      ScoreBoard->Visible = true;
      RoundBoard->Visible = true;
      ScoreBoard->Caption = "ZIELONY    "+IntToStr(greenPlayerScore)+" : "+IntToStr(redPlayerScore)+"    CZERWONY";
      RoundBoard -> Caption = "Runda: " + IntToStr(turnNumber);
      LeftPaddle->Enabled = true;
      RightPaddle->Enabled = true;
      Ball->Visible = true;
      BallTimer->Enabled = true;
      Ball -> Left = Board->Width/2 ;
      Ball -> Top = Board->Top + Board->Height/2  ;
      ScorePoint->Visible=false;
    }
  }
  else
    {
     BallTimer -> Enabled = true;
     LeftPaddle->Enabled = true;
     RightPaddle->Enabled = true;
     Ball -> Left = Board->Width/2 ;
     Ball -> Top = Board->Top + Board->Height/2  ;
     Ball->Visible = true;
     Vx = -6;
     Vy = -6;
     ScorePoint->Visible=false;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PauzaClick(TObject *Sender)
{
        BallTimer -> Enabled = false;
        Application -> MessageBox("Wróciæ  do gry?", "Pauza", MB_OK);
        BallTimer -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EndGameClick(TObject *Sender)
{
        BallTimer -> Enabled = false;
  if (Application -> MessageBox("Czy na pewno chcesz zakoñczyæ program?",
        "PotwierdŸ", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
         Application -> Terminate();
        }
   BallTimer -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  if(Application->MessageBox(
    "Witaj w grze PingPong2D."
    "STEROWANIE :"
    " * GRACZ ZIELONY : "
        "  paletka w górê -> 'A' "
        "  paletka w dó³  -> 'Z' "
    " * GRACZ CZERWONY : "
        "  paletka w górê -> strza³ka w górê "
        "  paletka w dó³  -> strza³aka w dó³ "
    "Kiedy odbijesz pi³kê œrodkow¹ czêœci¹ paletki, "
    "zmieni siê jej k¹t lotu i pi³ka przyœpieszy."
    "Jeœli chcesz zatrzymaæ grê - wciœnij spacjê. Puszczenie spacji wznowi rozgrywkê."
    "Mi³ej zabawy!","PingPong",MB_OK | MB_ICONWARNING) == IDOK)
    {
      Action = caNone;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NextRoundClick(TObject *Sender)
{
      bounceCounter = 0;
      ScoreBoard->Caption = "ZIELONY    "+IntToStr(greenPlayerScore)+" : "+IntToStr(redPlayerScore)+"    CZERWONY";
      RoundBoard -> Caption = "Runda: " + IntToStr(turnNumber);
      LeftPaddle->Enabled = true;
      RightPaddle->Enabled = true;
      BallTimer->Enabled = true;
      Ball -> Left = Board->Width/2 ;
      Ball -> Top = Board->Top + Board->Height/2  ;
      Ball->Visible = true;
      Vx = -6;
      Vy = -6;
      ScorePoint->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HintsClick(TObject *Sender)
{
        BallTimer->Enabled = false;
        ShowMessage("Witaj w grze PingPong2D."
    "STEROWANIE :"
    " * GRACZ ZIELONY : "
        "  paletka w górê -> 'A' "
        "  paletka w dó³  -> 'Z' "
    " * GRACZ CZERWONY : "
        "  paletka w górê -> strza³ka w górê "
        "  paletka w dó³  -> strza³aka w dó³ "
    "Kiedy odbijesz pi³kê œrodkow¹ czêœci¹ paletki, "
    "zmieni siê jej k¹t lotu i pi³ka przyœpieszy."
    "Jeœli chcesz zatrzymaæ grê - wciœnij spacjê. Puszczenie spacji wznowi rozgrywkê.");
}
//---------------------------------------------------------------------------

