//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Natalia Bubakova <xbubak01@stud.fit.vutbr.cz>
// $Date:       $2021-03-10
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Natalia Bubakova
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//


class MatrixTest : public ::testing::Test{
protected:

    virtual void SetUp()
    {
        m3x2.set(0, 0, 10);
        m3x2.set(0, 1, 20);
        m3x2.set(1, 0, 30);
        m3x2.set(1, 1, 40);
        m3x2.set(2, 0, 50);
        m3x2.set(2, 1, 60);

        m2x3 = m3x2.transpose();
        m3x3 = m3x2 * m2x3;
        m2x2 = m2x3 * m3x2;
    }

/* 4 test matrixes of different sizes ( m[row]x[col] ), set in SetUp  */

    Matrix m3x2{3, 2};
    Matrix m2x3;
    Matrix m2x2;
    Matrix m3x3;

};


TEST_F (MatrixTest, Constructor)
{
    EXPECT_ANY_THROW(Matrix(0, 0));
    EXPECT_ANY_THROW(Matrix(0, 1));
    EXPECT_ANY_THROW(Matrix(1, 0));
    EXPECT_ANY_THROW(Matrix(-1, -2));

    EXPECT_NO_THROW(Matrix());
    EXPECT_NO_THROW(Matrix(1, 1));
    EXPECT_NO_THROW(Matrix(3, 4));
    EXPECT_NO_THROW(Matrix(10, 10));
}


TEST_F (MatrixTest, Set)
{
    Matrix m{2,2};

    std::vector<std::vector<double> > same(2, std::vector<double>(2, 2));
    std::vector<std::vector<double> > diff(1, std::vector<double>(2, 2));

    EXPECT_TRUE(m.set(same));
    EXPECT_FALSE(m.set(diff));
}


TEST_F (MatrixTest, Set_Get)
{
    Matrix m{2,2};

    EXPECT_TRUE(m.set(0,1,10));
    EXPECT_TRUE(m.set(1,1,10));
    EXPECT_FALSE(m.set(0,3,30));
    EXPECT_FALSE(m.set(-1,2,30));

    EXPECT_ANY_THROW(m.get(0,3));
    EXPECT_EQ(0, m.get(0, 0));
    EXPECT_EQ(10, m.get(1, 1));
}


TEST_F (MatrixTest, Transpose)
{
    /* already transposed in SetUp */
    EXPECT_EQ(m3x2.get(0,0),m2x3.get(0,0));
    EXPECT_EQ(m3x2.get(2,1),m2x3.get(1,2));

    /* double transposed gives the original*/
    EXPECT_EQ(m3x2.get(2,1),(m2x3.transpose()).get(2,1));
}


TEST_F (MatrixTest, Multiply_CheckSizes)
{
    Matrix m;
    /* wrong sizes */
    EXPECT_ANY_THROW(m = m2x3 * m2x3);
    EXPECT_ANY_THROW(m = m3x2 * m3x2);
    EXPECT_ANY_THROW(m = m3x3 * m2x2);

    /* suitable sizes */
    EXPECT_NO_THROW(m = m3x3 * m3x3);
    EXPECT_NO_THROW(m = m2x2 * m2x2);
    EXPECT_NO_THROW(m = m2x3 * m3x2);
    EXPECT_NO_THROW(m = m3x2 * m2x3);
}

TEST_F (MatrixTest, Multiply_CheckResults)
{
    Matrix m;

    /* already multiplied in SetUp*/
    m = m2x3 * m3x2;
    EXPECT_EQ(m.get(1,1),m2x2.get(1,1));
    EXPECT_EQ(5600,m2x2.get(1,1));
    EXPECT_EQ(2500,m3x3.get(1,1));

    m = m3x3 * m3x3;
    EXPECT_EQ(4350000, m.get(0,0));
    m = m2x2 * m2x2;
    EXPECT_EQ(31610000, m.get(0,0));
}


TEST_F (MatrixTest, Multiply_Constant)
{
    Matrix m;

    m = m2x3 * -2;
    EXPECT_EQ(-40,m.get(1,0));
    m = m3x2 * 3;
    EXPECT_EQ(90,m.get(1,0));
    m = m2x2 * 2;
    EXPECT_EQ(8800,m.get(1,0));
    m = m3x3 * -1;
    EXPECT_EQ(-1100,m.get(1,0));
}


TEST_F (MatrixTest, Add_CheckSizes)
{
    Matrix m;

    /* different sizes */
    EXPECT_ANY_THROW(m = m3x2 + m2x3);
    EXPECT_ANY_THROW(m = m3x3 + m2x2);
    EXPECT_ANY_THROW(m = m3x2 + m2x2);

    /* same sizes */
    EXPECT_NO_THROW(m = m3x3 + m3x3);
    EXPECT_NO_THROW(m = m2x2 + m2x2);
    EXPECT_NO_THROW(m = m3x2 + m3x2);
}

TEST_F (MatrixTest, Add_CheckResults)
{
    Matrix m;

    m = m3x2 + m3x2;
    EXPECT_EQ(40, m.get(0,1));
    m = m.transpose() + m2x3;
    EXPECT_EQ(60, m.get(1,0));
    m = m2x3 + m2x3;
    EXPECT_EQ(60, m.get(0,1));
    m = m3x3 + m3x3;
    EXPECT_EQ(12200, m.get(2,2));
    m = m2x2 + m2x2;
    EXPECT_EQ(11200, m.get(1,1));
}


TEST_F (MatrixTest, Equality)
{
    Matrix m;

    m = m2x2;
    EXPECT_ANY_THROW(m2x2 == m3x3);
    EXPECT_ANY_THROW(m2x3 == m3x2);
    EXPECT_NO_THROW(m * 5 == m2x2);

    EXPECT_TRUE(m == m2x2);
    EXPECT_FALSE(m * 2 == m2x2);
}

TEST_F (MatrixTest, Solve_Equation)
{
    Matrix m{1,1};
    m.set(0,0,5);
    std::vector<double> right_side = {10};
    std::vector<double> results = {2};
    EXPECT_NO_THROW(m.solveEquation(right_side));
    EXPECT_EQ(results, m.solveEquation(right_side));

    right_side = {11400, 14400};
    results = {2, 1};
    EXPECT_ANY_THROW(m2x3.solveEquation(right_side)); /* it must be square matrix */
    EXPECT_ANY_THROW(m3x2.solveEquation(right_side));
    EXPECT_NO_THROW(m2x2.solveEquation(right_side));
    EXPECT_EQ(results, m2x2.solveEquation(right_side));

    right_side = {0, 800, 1600};
    EXPECT_ANY_THROW(m3x2.solveEquation(right_side));
    EXPECT_ANY_THROW(m2x2.solveEquation(right_side)); /* more numbers on right side than rows in the matrix */
    EXPECT_ANY_THROW(m3x3.solveEquation(right_side)); /* determinant = 0 */

    Matrix mx{4,4};
    right_side = {1, 1, 1, 1};
    EXPECT_ANY_THROW(mx.solveEquation(right_side));  /* mx={0,..,0} -> determinant = 0 */
}


TEST_F (MatrixTest, Inverse)
{
    Matrix m{1,1};
    m.set(0,0,9);

    EXPECT_ANY_THROW(m.inverse()); /* must be 2x2 or 3x3 */
    EXPECT_ANY_THROW(m3x2.inverse());
    EXPECT_ANY_THROW(m2x3.inverse());
    EXPECT_ANY_THROW(m3x3.inverse()); /* determinant = 0 */
    EXPECT_NO_THROW(m2x2.inverse());

    Matrix m2{2,2};
    m2.set(std::vector<std::vector<double>> {{1, 2},{3, 4}});
    EXPECT_EQ(1,(m2.inverse()).get(0,1));

    Matrix m3{3,3};
    m3.set(std::vector<std::vector<double>> {{2,1,0},{1,2,1},{0,1,2}});
    EXPECT_EQ(1,(m3.inverse()).get(1,1));
}


/*** Konec souboru white_box_tests.cpp ***/
