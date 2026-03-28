/** This file contains a class to solve the equation Ax = b where A is an
 * NxN-dimensional matrix, and x and b are n-dimensional vectors.  Note that
 * the methods in this class are all static so that you can simply call them
 * as if they were global functions.
 *
 * @file GaussJordan.h
 * @author Barton Stander
 * @author Terry Fleury
 * @date March 31, 2002
 */

#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H

#include "tnt_matrix.h"
#include "tnt_vector.h"

#include <cmath>

namespace TNT
{

class GaussJordan
{
public:
  /// Solves the equation Ax=b using Gauss-Jordan method.
  static bool Solve(TNT::Matrix<double> &A, TNT::Vector<double> &b);
  
  /// Inverts the matrix A which is returned in AInv.
  static bool Invert(TNT::Matrix<double> &A, TNT::Matrix<double> &AInv);
};

#include <cmath>

/** 
 * Solves the equation Ax=b using Gauss-Jordan method.  You pass
 * in the matrix A and the vector b.  Upon return, A holds the inverse of
 * the original matrix A and b holds the solution x = A^-1 * b.  In other
 * words, this method destroys both input A and b.
 * @param A Input Matrix, set to the inverse of A upon return.
 * \param b Input vector, set to the solution x upon return.
 * \return False If matrix A is singular or some other problem arises.
 */
bool GaussJordan::Solve(TNT::Matrix<double> &A, TNT::Vector<double> &b)
{  
  int n = b.size();

  TNT::Vector<int> indxc(n);
  TNT::Vector<int> indxr(n);
  TNT::Vector<int> ipiv(n,0);

  int i,j,k,l,ll;
	int icol = 0;
	int irow = 0;
  double big,dum,pivinv;

  for (i = 1; i <= n; i++) {
    big=0.0;
    for (j = 1; j <= n; j++)
      if (ipiv(j) != 1)
        for (k = 1; k <= n; k++) {
          /* Find biggest in row j */
          if (ipiv(k) == 0) {
            if (fabs(A(j,k)) >= big) {
              big=fabs(A(j,k));
              irow=j;
              icol=k;
            }
          } else if (ipiv(k) > 1) {
             std::cout << "ERROR! Singular matrix 1" << std::endl;
            return false;
          }
        }

    ipiv(icol)++;

    if (irow != icol) {
      for (l = 1; l <= n; l++)
        std::swap(A(irow,l),A(icol,l));
      std::swap(b(irow),b(icol));
    }

    indxr(i) = irow;
    indxc(i) = icol;

/*
    if (fabs(A(icol,icol)) < 0.00001) {
      std::cout << "ERROR! Singular matrix 2" << std::endl;
    return false;
    }

    if (fabs(A(icol,icol)) > 100000.0) {
      return false;
    }
*/

    pivinv = 1.0/A(icol,icol);

    A(icol,icol) = 1.0;

    for (l = 1; l <= n; l++)
      A(icol,l) *= pivinv;

    b(icol) *= pivinv;

    for (ll = 1; ll <= n; ll++)
      if (ll != icol) {
        dum = A(ll,icol);
        A(ll,icol) = 0.0;
        for (l = 1; l <= n; l++)
          A(ll,l) -= A(icol,l)*dum;
        b(ll) -= b(icol)*dum;
      }
  }

  for (l = n; l > 0; l--) {
    if (indxr(l) != indxc(l))
      for (k = 1; k <= n; k++)
        std::swap(A(k,indxr(l)),A(k,indxc(l)));        
    }
    
  return true;
} 

/** 
 * Inverts the matrix X which is returned in AInv.  This method leaves A
 * untouched.  If there is some problem with the input matrix A, we return
 * false.
 * @param A The input matrix to be inverted.
 * @param AInv The resulting inverted matrix.
 * @return False if there was some problem during the inversion process.
 *	   Otherwise, True upon success.
 */
bool GaussJordan::Invert(TNT::Matrix<double> &A, TNT::Matrix<double> &AInv)
{
  TNT::Vector<double> b(A.num_cols(),1.0);

  AInv = A;

  return GaussJordan::Solve(AInv,b);
}

}

#endif
