#pragma once

#include "MatrixBlock.h"
#include "MatrixBoard.h"

namespace Tetris
{
	class CTetris
	{
	private:

		//下一个砖块
		CMatrixBlock _MatrixBlockNext;

		//砖块
		CMatrixBlock _MatrixBlock;

		//底板
		CMatrixBoard _MatrixBoard;
		CMatrixBoard _TempMatrixBoard;

		//定时器
		UINT_PTR _nTimer;

		//定时器间隔时间:游戏速度控制
		UINT _nSpeed;

		//分数
		UINT _nScore;

		//使用的方块数量
		UINT _nBlockCount;
	public:
		enum Direction
		{
			LEFT,
			RIGHT,
			DOWN,
			ROTATE,
		};
	public:
		static CTetris* s_Tetris;		
		
		CTetris(void);
		~CTetris(void);	

		void OnTimerProc(UINT_PTR idEvent);

	protected:
		void MoveBlockFastDown(BOOL bFast);
		void MoveBlock(Direction dir);
		void Pause();
		void Run();
		void NewGame();
		void SetSpeed(UINT nSpeed);

	protected:
		virtual void OnDrawMatrixNext(CMatrix* pMatrix)=0;
		virtual void OnDrawMatrixBoard(CMatrix* pMatrix,int nFullRow=-1)=0;
		virtual void OnGameOver()=0;
		virtual void OnUpdateScore(int nScore)=0;
		virtual void OnUpdateBlockCount(int nBlockCount)=0;
	private:
		BOOL IsGameOver();
		void OnPutDown();
		BOOL CanMove();
		void GetMatrixBlock();
		void DeleteFullRow(int nFullRow);
		int FindFullRow();
	};
}
