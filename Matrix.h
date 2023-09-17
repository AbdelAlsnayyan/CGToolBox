

class Matrix{

 public:
  Matrix(int rows,int cols){row_size = rows; col_size=cols;};
  int row_size(){return m_row_size;};
  int col_size(){return m_col_size;};


 private:
  int m_row_size;
  int m_col_size;
};
