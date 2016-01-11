#pragma once
#include "Matrix.h"

namespace Tetris
{
	class CMatrixBoard :
		public CMatrix
	{
	public:
		CMatrixBoard(void);
		~CMatrixBoard(void);
		void Clear();
	};
}
