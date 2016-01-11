#pragma once

#include "Matrix.h"

namespace Tetris
{
	class CMatrixBlock :
		public CMatrix
	{
	public:
		CMatrixBlock(void);
		~CMatrixBlock(void);
		static BYTE s_MatrixBlockData[7][16];
		static COLORREF s_Color[7];

		int col;
		int row;
	};
}