// Header file for basic, often-used helper classes.
// RndmEngine: base class for external random number generators.
// Rndm: random number generator (static member functions).
// Vec4: simple four-vectors.
// RotBstMatrix: matrices encoding rotations and boosts of Vec4 objects.
// Hist: simple one-dimensional histograms.
// Copyright C 2006 Torbjorn Sjostrand

#ifndef Pythia8_Basics_H
#define Pythia8_Basics_H

#include "PythiaStdlib.h"

namespace Pythia8 {
 
//**************************************************************************

// RndmEngine is the base class for external random number generators.
// There is only one pure virtual method, that should do the generation. 

class RndmEngine {

public:

  // A pure virtual method, wherein the derived class method 
  // generates a random number uniformly distributed between 1 and 1.
  virtual double flat() = 0;

protected:

  // Destructor.
  virtual ~RndmEngine() {}

}; 

//**************************************************************************

// Rndm class.
// This class handles random number generation according to the
// Marsaglia-Zaman-Tsang algorithm.

class Rndm {

public:

  // Constructors.
  Rndm() {} 
  Rndm(int seedIn) { init(seedIn);} 

  // Possibility to pass in pointer for external random number generation.
  static bool rndmEnginePtr( RndmEngine* rndmPtrIn);  

  // Initialize, normally at construction or in first call.
  static void init(int seedIn = 0) ;

  // Generate next random number uniformly between 0 and 1.
  static double flat() ;

  // Generate random numbers according to exp(-x).
  static double exp() { return -log(flat()) ;} 

  // Generate random numbers according to x * exp(-x).
  static double xexp() { return -log(flat() * flat()) ;} 

  // Generate random numbers according to exp(-x^2/2).
  static double gauss() ;

  // Pick one option among  vector of (positive) probabilities.
  static int pick(const vector<double>& prob) ; 

private:

  // State of the random number generator.
  static bool initRndm, saveGauss; 
  static int i97, j97, defaultSeed;
  static double u[97], c, cd, cm, save;

  // Pointer for external random number generation.
  static RndmEngine* rndmPtr;
  static bool useExternalRndm; 

};

//**************************************************************************

// Forward reference to RotBstMatrix class.
class RotBstMatrix;

//**************************************************************************

// Vec4 class.
// This class implements four-vectors, in energy-momentum space.
// (But can equally well be used to hold space-time four-vectors.)

class Vec4 {

public:

  // Constructors.
  Vec4(double xIn = 0., double yIn = 0., double zIn = 0., double tIn = 0.)
    : xx(xIn), yy(yIn), zz(zIn), tt(tIn) { }
  Vec4(const Vec4& v) : xx(v.xx), yy(v.yy), zz(v.zz), tt(v.tt) { }
  Vec4& operator=(const Vec4& v) { if (this != &v) { xx = v.xx; yy = v.yy; 
    zz = v.zz; tt = v.tt; } return *this; }
  Vec4& operator=(double value) { xx = value; yy = value; zz = value; 
    tt = value; return *this; }
      
  // Member functions for input.
  void reset() {xx = 0.; yy = 0.; zz = 0.; tt = 0.;}
  void p(double xIn, double yIn, double zIn, double tIn) 
    {xx = xIn; yy = yIn; zz = zIn; tt = tIn;}
  void p(Vec4 pIn) {xx = pIn.xx; yy = pIn.yy; zz = pIn.zz; tt = pIn.tt;} 
  void px(double xIn) {xx = xIn;}
  void py(double yIn) {yy = yIn;}
  void pz(double zIn) {zz = zIn;}
  void e(double tIn) {tt = tIn;}

  // Member functions for output.
  double px() const {return xx;}
  double py() const {return yy;}
  double pz() const {return zz;}
  double e() const {return tt;}
  double m2Calc() const {return tt*tt - xx*xx - yy*yy - zz*zz;}
  double mCalc() const {double temp = tt*tt - xx*xx - yy*yy - zz*zz;
    return (temp >= 0) ? sqrt(temp) : -sqrt(-temp);}
  double pT() const {return sqrt(xx*xx + yy*yy);}
  double pT2() const {return xx*xx + yy*yy;}
  double pAbs() const {return sqrt(xx*xx + yy*yy + zz*zz);}
  double pAbs2() const {return xx*xx + yy*yy + zz*zz;}
  double theta() const {return atan2(sqrt(xx*xx + yy*yy), zz);}
  double phi() const {return atan2(yy,xx);}
  double thetaXZ() const {return atan2(xx,zz);}
  double pPlus() const {return tt + zz;}
  double pMinus() const {return tt - zz;}

  // Member functions that perform operations.
  void rescale3(double fac) {xx *= fac; yy *= fac; zz *= fac;}
  void rescale4(double fac) {xx *= fac; yy *= fac; zz *= fac; tt *= fac;}
  void flip3() {xx = -xx; yy = -yy; zz = -zz;}
  void flip4() {xx = -xx; yy = -yy; zz = -zz; tt = -tt;}
  void rot(double theta, double phi); 
  void rotaxis(double phi, double nx, double ny, double nz); 
  void rotaxis(double phi, const Vec4& n);
  void bst(double betaX, double betaY, double betaZ); 
  void bst(double betaX, double betaY, double betaZ, double gamma); 
  void bst(const Vec4& vec); 
  void rotbst(const RotBstMatrix& M); 

  // Operator overloading with member functions
  Vec4& operator-() {xx = -xx; yy = -yy; zz = -zz; tt = -tt; return *this;}
  Vec4& operator+=(const Vec4& v) {xx += v.xx; yy += v.yy; zz += v.zz; 
    tt += v.tt; return *this;}
  Vec4& operator-=(const Vec4& v) {xx -= v.xx; yy -= v.yy; zz -= v.zz; 
    tt -= v.tt; return *this;}
  Vec4& operator*=(double f) {xx *= f; yy *= f; zz *= f; 
    tt *= f; return *this;}
  Vec4& operator/=(double f) {xx /= f; yy /= f; zz /= f; 
    tt /= f; return *this;}

  // Operator overloading with friends
  friend Vec4 operator+(const Vec4& v1, const Vec4& v2);
  friend Vec4 operator-(const Vec4& v1, const Vec4& v2);
  friend Vec4 operator*(double f, const Vec4& v1);
  friend Vec4 operator*(const Vec4& v1, double f);
  friend Vec4 operator/(const Vec4& v1, double f);
  friend double operator*(const Vec4& v1, const Vec4& v2);

  // Invariant mass of a pair and its square.
  friend double m(const Vec4& v1, const Vec4& v2);
  friend double m2(const Vec4& v1, const Vec4& v2);

  // Scalar and cross product of 3-vector parts.
  friend double dot3(const Vec4& v1, const Vec4& v2);
  friend Vec4 cross3(const Vec4& v1, const Vec4& v2);

  // theta is polar angle between v1 and v2.
  friend double costheta(const Vec4& v1, const Vec4& v2);
  friend double theta(const Vec4& v1, const Vec4& v2) {
    return acos(costheta(v1, v2)); } 

  // phi is azimuthal angle between v1 and v2 around z axis.
  friend double cosphi(const Vec4& v1, const Vec4& v2);
  friend double phi(const Vec4& v1, const Vec4& v2) {
    return acos(cosphi(v1, v2)); } 

  // phi is azimuthal angle between v1 and v2 around n axis.
  friend double cosphi(const Vec4& v1, const Vec4& v2, const Vec4& n);
  friend double phi(const Vec4& v1, const Vec4& v2, const Vec4& n) {
    return acos(cosphi(v1, v2, n)); } 

  // Print a four-vector
  friend ostream& operator<<(ostream&, const Vec4& v) ;

private:

  // Constants: could only be changed in the code itself.
  static const double TINY;

  // The four-vector data members.
  double xx, yy, zz, tt;

};

// Implementation of operator overloading with friends.

inline Vec4 operator+(const Vec4& v1, const Vec4& v2) 
  {Vec4 v = v1 ; return v += v2;}

inline Vec4 operator-(const Vec4& v1, const Vec4& v2) 
  {Vec4 v = v1 ; return v -= v2;}

inline Vec4 operator*(double f, const Vec4& v1) 
  {Vec4 v = v1; return v *= f;}

inline Vec4 operator*(const Vec4& v1, double f) 
  {Vec4 v = v1; return v *= f;}

inline Vec4 operator/(const Vec4& v1, double f) 
  {Vec4 v = v1; return v /= f;}

inline double operator*(const Vec4& v1, const Vec4& v2)
  {return v1.tt*v2.tt - v1.xx*v2.xx - v1.yy*v2.yy - v1.zz*v2.zz;}  

//**************************************************************************

// RotBstMatrix class.
// This class implements 4 * 4 matrices that encode an arbitrary combination
// of rotations and boosts, that can be applied to Vec4 four-vectors.

class RotBstMatrix {

public:

  // Constructors.
  RotBstMatrix() {for (int i = 0; i < 4; ++i) { for (int j = 0; j < 4; ++j) 
    { M[i][j] = (i==j) ? 1. : 0.; } } } 
  RotBstMatrix(const RotBstMatrix& Min) {
    for (int i = 0; i < 4; ++i) { for (int j = 0; j < 4; ++j) {
    M[i][j] = Min.M[i][j]; } } }
  RotBstMatrix& operator=(const RotBstMatrix& Min) {if (this != &Min) {
    for (int i = 0; i < 4; ++i) { for (int j = 0; j < 4; ++j) {
    M[i][j] = Min.M[i][j]; } } } return *this; }

  // Member functions.
  void rot(double = 0., double = 0.);
  void rot(const Vec4& p);
  void bst(double = 0., double = 0., double = 0.);
  void bst(const Vec4&);
  void bstback(const Vec4&);
  void bst(const Vec4&, const Vec4&);
  void rotbst(const RotBstMatrix&);
  void invert();
  void toCMframe(const Vec4&, const Vec4&);
  void fromCMframe(const Vec4&, const Vec4&);
  void reset();

  // Crude estimate deviation from unit matrix.
  double deviation() const;

  // Print a transformation matrix.
  friend ostream& operator<<(ostream&, const RotBstMatrix&) ;

  // Private members to be accessible from Vec4. 
  friend class Vec4;

private:

  // Constants: could only be changed in the code itself.
  static const double TINY;

  // The rotation-and-boost matrix data members.
  double M[4][4];

};

//**************************************************************************

// Hist class.
// This class handles a single histogram at a time.

class Hist{

public:

  // Constructors, including copy constructors.
  Hist() {;}
  Hist(string titleIn, int nBinIn = 100, double xMinIn = 0., 
    double xMaxIn = 1.) {
    book(titleIn, nBinIn, xMinIn, xMaxIn);} 
  Hist(const Hist& h) 
    : title(h.title), nBin(h.nBin), nFill(h.nFill), xMin(h.xMin), 
    xMax(h.xMax), dx(h.dx), under(h.under), inside(h.inside), 
    over(h.over), res(h.res) { }    
  Hist(string titleIn, const Hist& h) 
    : title(titleIn), nBin(h.nBin), nFill(h.nFill), xMin(h.xMin), 
    xMax(h.xMax), dx(h.dx), under(h.under), inside(h.inside), 
    over(h.over), res(h.res) { }         
  Hist& operator=(const Hist& h) { if(this != &h) {
    nBin = h.nBin; nFill = h.nFill; xMin = h.xMin; xMax = h.xMax; 
    dx = h.dx;  under = h.under; inside = h.inside; over = h.over; 
    res = h.res; } return *this; }    
  
  // Book a histogram.
  void book(string titleIn = "  ", int nBinIn = 100, double xMinIn = 0., 
    double xMaxIn = 1.) ; 
 
  // Set title of a histogram.
  void name(string titleIn = "  ") {title = titleIn; }  

  // Reset bin contents.
  void null() ; 

  // Fill bin with weight.
  void fill(double x, double w = 1.) ;

  // Print histogram contents as a table (e.g. for Gnuplot).
  void table(ostream& os = cout) const ;

  // Check whether another histogram has same size and limits.
  bool sameSize(const Hist& h) const ;

  // Operator overloading with member functions
  Hist& operator+=(const Hist& h) ; 
  Hist& operator-=(const Hist& h) ;
  Hist& operator*=(const Hist& h) ; 
  Hist& operator/=(const Hist& h) ;
  Hist& operator+=(double f) ; 
  Hist& operator-=(double f) ; 
  Hist& operator*=(double f) ; 
  Hist& operator/=(double f) ; 

  // Operator overloading with friends
  friend Hist operator+(double f, const Hist& h1);
  friend Hist operator+(const Hist& h1, double f);
  friend Hist operator+(const Hist& h1, const Hist& h2);
  friend Hist operator-(double f, const Hist& h1);
  friend Hist operator-(const Hist& h1, double f);
  friend Hist operator-(const Hist& h1, const Hist& h2);
  friend Hist operator*(double f, const Hist& h1);
  friend Hist operator*(const Hist& h1, double f);
  friend Hist operator*(const Hist& h1, const Hist& h2);
  friend Hist operator/(double f, const Hist& h1);
  friend Hist operator/(const Hist& h1, double f);
  friend Hist operator/(const Hist& h1, const Hist& h2);

  // Print a histogram or a vector of histograms
  friend ostream& operator<<(ostream& os, const Hist& h) ;
  friend ostream& operator<<(ostream& os, const vector<Hist>& h) ;

  // Print a single or a vector of histogram contents as a table 
  // (e.g. for Gnuplot).
  friend void table(const Hist& h, ostream& os = cout) ;
  friend void table(const vector<Hist>& h, ostream& os = cout) ;

private:

  // Constants: could only be changed in the code itself.
  static const int NBINMAX, NLINES;
  static const double TOLERANCE, TINY, SMALLFRAC, DYAC[];
  static const char NUMBER[];

  // Properties and contents of a histogram.
  string title;
  int nBin, nFill; 
  double xMin, xMax, dx, under, inside, over; 
  vector<double> res;

};

//**************************************************************************

} // end namespace Pythia8

#endif // end Pythia8_Basics_H