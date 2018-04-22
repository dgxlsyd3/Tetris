#pragma once

namespace Tetris
{
	//ע������洢��������һά������
	template<class T> void RotateRight(int _rows,int _cols,T* _pdata,T* _new_pdata)
	{
		int _new_rows=_cols;
		int _new_cols=_rows;

		//Դ���������һ�У��ӵ׶˿�ʼ���϶�ȡ�������¾���ĵ�һ����
		int _new_i=0;
		for (int j=0;j<_cols;j++,_new_i++)
		{
			int _new_j=0;
			for (int i=_rows-1;i>=0;i--,_new_j++)
			{
				int _new_pos=_new_i*_new_cols+_new_j;
				int pos=i*_cols+j;
				_new_pdata[_new_pos]=_pdata[pos];
			}
		}
	}

	template<class T> void RotateLeft(int _rows,int _cols,T* _pdata,T* _new_pdata)
	{
		int _new_rows=_cols;
		int _new_cols=_rows;

		//Դ���������һ�У��Ӷ��˿�ʼ���¶�ȡ�������¾���ĵ�һ����
		int _new_i=0;
		for (int j=_cols-1;j>=0;j--,_new_i++)
		{
			int _new_j=0;
			for (int i=0;i<_rows;i++,_new_j++)
			{
				int _new_pos=_new_i*_new_cols+_new_j;
				int pos=i*_cols+j;
				_new_pdata[_new_pos]=_pdata[pos];
			}
		}
	}

	class CMatrix
	{
	public:
		CMatrix(void);
		CMatrix(CMatrix& objMatrix);
		CMatrix& operator=(CMatrix& objMatrix);

		~CMatrix(void);
	protected:
		BYTE *_pdata;
		int _row;
		int _column;
	public:
		void Init(IN int row,IN int column);
		void SetData(IN BYTE *data);
		void SetData(IN int row, IN int column, IN BYTE data);
		BYTE GetData(IN int row, IN int column);
		int GetRowCount();
		int GetColCount();
		void RotateRight();
		void RotateLeft();
		void DebugTrace();
	};
}
