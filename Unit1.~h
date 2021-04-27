//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *Board;
        TShape *UpperBound;
        TShape *LowerBound;
        TImage *LeftPaddle;
        TImage *RightPaddle;
        TImage *Ball;
        TTimer *BallTimer;
        TTimer *leftPaddleUp;
        TTimer *leftPaddleDown;
        TTimer *rightPaddleUp;
        TTimer *rightPaddleDown;
        TButton *NextRound;
        TLabel *ScoreBoard;
        TLabel *Pauza;
        TLabel *RoundBoard;
        TButton *NewGame;
        TLabel *BounceCounter;
        TButton *Hints;
        TButton *Continue;
        TLabel *ScorePoint;
        void __fastcall BallTimerTimer(TObject *Sender);
        void __fastcall leftPaddleUpTimer(TObject *Sender);
        void __fastcall leftPaddleDownTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall rightPaddleUpTimer(TObject *Sender);
        void __fastcall rightPaddleDownTimer(TObject *Sender);
        void __fastcall NextRoundClick(TObject *Sender);
        void __fastcall NewGameClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
        void __fastcall HintsClick(TObject *Sender);
        void __fastcall ContinueClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
