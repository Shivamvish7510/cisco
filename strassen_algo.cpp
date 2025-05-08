#include <iostream>

class Matrix {
private:
    int** data;
    int size;
    
    // Private constructor for internal use
    Matrix(int size, bool allocate) : size(size) {
        if (allocate) {
            data = new int*[size];
            for (int i = 0; i < size; i++) {
                data[i] = new int[size]();
            }
        }
    }

public:
    // Constructor
    Matrix(int size) : size(size) {
        if (size <= 0 || (size & (size - 1)) != 0) {
            std::cerr << "Error: Size must be a positive power of 2\n";
            exit(1);
        }
        
        data = new int*[size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size]();
        }
    }
    
    // Copy constructor
    Matrix(const Matrix& other) : size(other.size) {
        data = new int*[size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size];
            for (int j = 0; j < size; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    
    // Destructor
    ~Matrix() {
        for (int i = 0; i < size; i++) {
            delete[] data[i];
        }
        delete[] data;
    }
    
    // Assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            // Free existing resources
            for (int i = 0; i < size; i++) {
                delete[] data[i];
            }
            delete[] data;
            
            // Allocate new resources
            size = other.size;
            data = new int*[size];
            for (int i = 0; i < size; i++) {
                data[i] = new int[size];
                for (int j = 0; j < size; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }
    
    // Access operator
    int* operator[](int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of range\n";
            exit(1);
        }
        return data[index];
    }
    
    // Const access operator
    const int* operator[](int index) const {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of range\n";
            exit(1);
        }
        return data[index];
    }
    
    // Get size
    int getSize() const { return size; }
    
    // Matrix addition
    Matrix operator+(const Matrix& other) const {
        if (size != other.size) {
            std::cerr << "Error: Matrix sizes must match\n";
            exit(1);
        }
        
        Matrix result(size, false);
        result.data = new int*[size];
        for (int i = 0; i < size; i++) {
            result.data[i] = new int[size];
            for (int j = 0; j < size; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    
    // Matrix subtraction
    Matrix operator-(const Matrix& other) const {
        if (size != other.size) {
            std::cerr << "Error: Matrix sizes must match\n";
            exit(1);
        }
        
        Matrix result(size, false);
        result.data = new int*[size];
        for (int i = 0; i < size; i++) {
            result.data[i] = new int[size];
            for (int j = 0; j < size; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
    
    // Get submatrix
    Matrix getSubMatrix(int rowStart, int colStart, int subSize) const {
        Matrix sub(subSize, false);
        sub.data = new int*[subSize];
        for (int i = 0; i < subSize; i++) {
            sub.data[i] = new int[subSize];
            for (int j = 0; j < subSize; j++) {
                sub.data[i][j] = data[rowStart + i][colStart + j];
            }
        }
        return sub;
    }
    
    // Set submatrix
    void setSubMatrix(const Matrix& sub, int rowStart, int colStart) {
        int subSize = sub.size;
        for (int i = 0; i < subSize; i++) {
            for (int j = 0; j < subSize; j++) {
                data[rowStart + i][colStart + j] = sub.data[i][j];
            }
        }
    }
    
    // Print matrix
    void print() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << data[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
    
    // Strassen's multiplication (static method)
    static Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
        if (A.size != B.size) {
            std::cerr << "Error: Matrix sizes must match\n";
            exit(1);
        }
        
        int size = A.size;
        
        // Base case
        if (size == 1) {
            Matrix C(1);
            C[0][0] = A[0][0] * B[0][0];
            return C;
        }
        
        int newSize = size / 2;
        
        // Create submatrices
        Matrix a11 = A.getSubMatrix(0, 0, newSize);
        Matrix a12 = A.getSubMatrix(0, newSize, newSize);
        Matrix a21 = A.getSubMatrix(newSize, 0, newSize);
        Matrix a22 = A.getSubMatrix(newSize, newSize, newSize);
        
        Matrix b11 = B.getSubMatrix(0, 0, newSize);
        Matrix b12 = B.getSubMatrix(0, newSize, newSize);
        Matrix b21 = B.getSubMatrix(newSize, 0, newSize);
        Matrix b22 = B.getSubMatrix(newSize, newSize, newSize);
        
        // Calculate the 7 products
        Matrix p1 = strassenMultiply(a11 + a22, b11 + b22);
        Matrix p2 = strassenMultiply(a21 + a22, b11);
        Matrix p3 = strassenMultiply(a11, b12 - b22);
        Matrix p4 = strassenMultiply(a22, b21 - b11);
        Matrix p5 = strassenMultiply(a11 + a12, b22);
        Matrix p6 = strassenMultiply(a21 - a11, b11 + b12);
        Matrix p7 = strassenMultiply(a12 - a22, b21 + b22);
        
        // Calculate the quadrants
        Matrix c11 = p1 + p4 - p5 + p7;
        Matrix c12 = p3 + p5;
        Matrix c21 = p2 + p4;
        Matrix c22 = p1 + p3 - p2 + p6;
        
        // Combine results
        Matrix result(size);
        result.setSubMatrix(c11, 0, 0);
        result.setSubMatrix(c12, 0, newSize);
        result.setSubMatrix(c21, newSize, 0);
        result.setSubMatrix(c22, newSize, newSize);
        
        return result;
    }
};

int main() {
    const int size = 4; // Must be power of 2
    Matrix A(size);
    Matrix B(size);
    
    // Initialize matrices
    int counter = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = counter;
            B[i][j] = (size * size) + 1 - counter;
            counter++;
        }
    }
    
    std::cout << "Matrix A:" << std::endl;
    A.print();
    std::cout << "\nMatrix B:" << std::endl;
    B.print();
    
    Matrix C = Matrix::strassenMultiply(A, B);
    
    std::cout << "\nResult of A × B:" << std::endl;
    C.print();
    
    return 0;
}