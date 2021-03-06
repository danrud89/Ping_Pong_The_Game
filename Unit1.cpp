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
int Vx = -16;
int Vy = -16;
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
         PlaySound(MAKEINTRESOURCE(4), HInstance, SND_RESOURCE);
         redPlayerScore ++;
         BallTimer->Enabled = false;
         Ball->Visible = false;
         ScorePoint->Caption = "Punkt zdobywa gracz : "+ rightPlayerName + "!";
         ScorePoint->Visible = true;
         ScoreBoard->Caption = "ZIELONY    "+IntToStr(greenPlayerScore)+" : "+IntToStr(redPlayerScore)+"    CZERWONY";
         LeftPaddle->Enabled = false;
         RightPaddle->Enabled = false;
         turnNumber ++;
         RoundBoard->Caption = "Runda: " + IntToStr(turnNumber);
         NextRound->Visible = true;
         NextRound->Enabled = true;
         BounceCounter->Caption = "Liczba odbi? : " + IntToStr(bounceCounter);
         BounceCounter->Visible = true;
         NewGame->Enabled = true;
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
                PlaySound(MAKEINTRESOURCE(4), HInstance, SND_RESOURCE);
                greenPlayerScore ++;
                BallTimer->Enabled = false;
                Ball->Visible = false;
                ScorePoint->Caption = "Punkt zdobywa gracz : "+leftPlayerName+ "!";
                ScorePoint->Visible = true;
                ScoreBoard->Caption = "ZIELONY    "+IntToStr(greenPlayerScore)+" : "+IntToStr(redPlayerScore)+"    CZERWONY";
                LeftPaddle->Enabled = false;
                RightPaddle->Enabled = false;
                turnNumber ++;
                RoundBoard->Caption = "Runda: " + IntToStr(turnNumber);
                NextRound->Visible = true;
                NextRound->Enabled = true;
                BounceCounter->Caption = "Liczba odbi? : " + IntToStr(bounceCounter);
                BounceCounter->Visible = true;
                NewGame->Enabled = true;
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
       PlaySound(MAKEINTRESOURCE(3), HInstance, SND_RESOURCE);
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
        PlaySound(MAKEINTRESOURCE(3), HInstance, SND_RESOURCE);
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::leftPaddleUpTimer(TObject *Sender)
{
     if (LeftPaddle->Top >= Board->Top +15)
     {
         if (GetKeyState(VK_SPACE) & 0x8000) {}
         else LeftPaddle -> Top -= 10;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftPaddleDownTimer(TObject *Sender)
{
     if (LeftPaddle -> Top + LeftPaddle -> Height <= LowerBound -> Top - 15)
     {
          if (GetKeyState(VK_SPACE) & 0x8000) {}
          else  LeftPaddle -> Top += 10;
     }
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
       if (RightPaddle->Top >= Board->Top +15)
       {
         if (GetKeyState(VK_SPACE) & 0x8000) {}
         else  RightPaddle -> Top -= 10;
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightPaddleDownTimer(TObject *Sender)
{
        if (RightPaddle -> Top + RightPaddle -> Height <= LowerBound -> Top - 15)
        {
         if (GetKeyState(VK_SPACE) & 0x8000) {}
         else RightPaddle -> Top += 10;
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::NextRoundClick(TObject *Sender)
{
   if (Application -> MessageBox("Gramy dalej ?",
        "Potwierd?", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
          Ball -> Left = Board->Width/2 ;
          Ball -> Top = Board->Top + Board->Height/2  ;
          Ball->Visible = true;
          BallTimer->Enabled = true;
          LeftPaddle->Enabled = true;
          RightPaddle->Enabled = true;
          NextRound->Visible=false;
          ScorePoint->Visible = false;
          BounceCounter->Caption = "Liczba odbi? : " + IntToStr(bounceCounter);
          Vx = -10;
          Vx = -10;
          BounceCounter->Visible = false;
          NewGame->Enabled = false;
          PlaySound(MAKEINTRESOURCE(2), HInstance, SND_RESOURCE);
        }
     else
     {
      turnNumber = 1;
      bounceCounter = 0;
      greenPlayerScore = 0;
      redPlayerScore = 0;
      LeftPaddle->Enabled = true;
      RightPaddle->Enabled = true;
      ScoreBoard->Caption = "ZIELONY    "+IntToStr(greenPlayerScore)+" : "+IntToStr(redPlayerScore)+"    CZERWONY";
      RoundBoard -> Caption = "Runda: " + IntToStr(turnNumber);
      ScoreBoard->Visible = true;
      RoundBoard->Visible = true;
      Ball->Visible = true;
      BallTimer->Enabled = false;
      Ball -> Left = Board->Width/2 ;
      Ball -> Top = Board->Top + Board->Height/2  ;
      ScorePoint->Visible=false;
      NextRound->Visible=false;
      BounceCounter->Visible = false;
      NewGame->Enabled = true;
     }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewGameClick(TObject *Sender)
{
   BallTimer -> Enabled = false;
  if(greenPlayerScore > 0 || redPlayerScore > 0)
  {
      if (Application -> MessageBox("Czy na pewno chcesz rozpocz?? now? gr? ?",
        "Potwierd?", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
      turnNumber = 1;
      bounceCounter = 0;
      greenPlayerScore = 0;
      redPlayerScore = 0;
      LeftPaddle->Enabled = true;
      RightPaddle->Enabled = true;
      ScoreBoard->Caption = "ZIELONY    "+IntToStr(greenPlayerScore)+" : "+IntToStr(redPlayerScore)+"    CZERWONY";
      RoundBoard -> Caption = "Runda: " + IntToStr(turnNumber);
      ScoreBoard->Visible = true;
      RoundBoard->Visible = true;
      Ball->Visible = true;
      BallTimer->Enabled = true;
      Ball -> Left = Board->Width/2 ;
      Ball -> Top = Board->Top + Board->Height/2  ;
      ScorePoint->Visible=false;
      Sleep(1000);
      PlaySound(MAKEINTRESOURCE(1), HInstance, SND_RESOURCE);
      NewGame->Enabled = false;
      NextRound->Visible=false;
    }
  }
  else
    {
     BallTimer -> Enabled = true;
     LeftPaddle->Enabled = true;
     RightPaddle->Enabled = true;
     ScoreBoard->Visible = true;
     RoundBoard->Visible = true;
     ScoreBoard->Caption = "ZIELONY    "+IntToStr(greenPlayerScore)+" : "+IntToStr(redPlayerScore)+"    CZERWONY";
     RoundBoard -> Caption = "Runda: " + IntToStr(turnNumber);
     Ball -> Left = Board->Width/2 ;
     Ball -> Top = Board->Top + Board->Height/2  ;
     Ball->Visible = true;
     ScorePoint->Visible=false;
     NewGame->Enabled = false;
     NextRound->Visible=false;
     PlaySound(MAKEINTRESOURCE(1), HInstance, SND_RESOURCE);
     }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
  if(Application->MessageBox(
    "Witaj w grze PingPong2D.\n\n"
    "STEROWANIE :\n\n"
    " GRACZ ZIELONY : \n"
        "  paletka w g?r? -> A \n"
        "  paletka w d??  -> Z \n\n"
    " GRACZ CZERWONY : \n"
        "  paletka w g?r? -> strza?ka w g?r? \n"
        "  paletka w d??  -> strza?aka w d?? \n\n"
    "Kiedy odbijesz pi?k? ?rodkow? cz??ci? paletki,\n"
    "zmieni si? jej k?t lotu i pi?ka przy?pieszy.\n"
    "Je?li chcesz zatrzyma? gr? - wci?nij spacj?. Puszczenie spacji wznowi rozgrywk?.\n"
    "Mi?ej gry!","PingPong",MB_OK | MB_ICONWARNING) == IDOK)
    {
      Action = caNone;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HintsClick(TObject *Sender)
{
   BallTimer->Enabled = false;
   ShowMessage("STEROWANIE :\n\n"
    " * GRACZ ZIELONY : \n"
        "  paletka w g?r? -> A \n"
        "  paletka w d??  -> Z \n\n"
    " * GRACZ CZERWONY : \n"
        "  paletka w g?r? -> strza?ka w g?r? \n"
        "  paletka w d??  -> strza?aka w d?? \n\n"
    "Kiedy odbijesz pi?k? ?rodkow? cz??ci? paletki, \n"
    "zmieni si? jej k?t lotu i pi?ka przy?pieszy.\n"
    "Przytrzymanie spacji - zatrzymanie rozgrywki.\n"
    "Puszczenie spacji - wznowienie rozgrywki. \n");
    Continue->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ContinueClick(TObject *Sender)
{
    if(BallTimer->Enabled == false)
    {
      Continue->Enabled = true;
      BallTimer->Enabled = true;
      Continue->Enabled = false;
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
   BallTimer -> Enabled = false;
   PlaySound(MAKEINTRESOURCE(5), HInstance, SND_RESOURCE);
    if (Application -> MessageBox("Czy na pewno chcesz zako?czy? program?",
        "Potwierd?", MB_YESNO | MB_ICONQUESTION) == IDNO)
        {
         Action = caNone;
        }
}
//---------------------------------------------------------------------------



