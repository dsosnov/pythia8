// This file contains classes that keep track of generic event info.
// Info: contains information on the generation process.
// ErrorMessages: table with all warnings and errors encountered.
// Copyright C 2006 Torbjorn Sjostrand

#ifndef Pythia8_Information_H
#define Pythia8_Information_H

#include "PythiaStdlib.h"
#include "Settings.h"

namespace Pythia8 {
 
//**************************************************************************

// The Info class contains a mixed bag of information on the event
// generation activity, especially on the current subprocess properties. 
// This is used by the generation machinery, but can also be read
// by the user.

class Info {

public:

  // Constructor. 
  Info() {} 

  // Listing of most available information.
  void list(ostream& os = cout);
  
  // Beam particles (in rest frame). CM energy of event.
  int idA() const {return idAM;}
  int idB() const {return idBM;}
  double pzA() const {return pzAM;}
  double pzB() const {return pzBM;}
  double eA() const {return eAM;}
  double eB() const {return eBM;}
  double mA() const {return mAM;}
  double mB() const {return mBM;}
  double eCM() const {return eCMM;}
  double s() const {return sM;}

  // Process name and code, and the number of final-state particles.
  string name() const {return nameSave;}
  int code() const {return codeSave;}    
  int nFinal() const {return nFinalSave;}

  // Are beam particles resolved, with pdf's? Are they diffractive?
  bool isResolved() const {return isRes;}
  bool isDiffractiveA() const {return isDiffA;} 
  bool isDiffractiveB() const {return isDiffB;} 
  bool isMinBias() const {return isMB;}

  // For minbias identify hardest subprocess.
  bool hasSub() const {return hasSubSave;}
  string nameSub() const {return nameSubSave;}
  int codeSub() const {return codeSubSave;}    
  int nFinalSub() const {return nFinalSubSave;}

  // Incoming parton flavours, x values, densities, couplings, Q2 scales.
  int id1() const {return id1H;}
  int id2() const {return id2H;}
  double x1() const {return x1H;}
  double x2() const {return x2H;}
  double pdf1() const {return pdf1H;}
  double pdf2() const {return pdf2H;}
  double Q2Fac() const {return Q2FacH;}
  double alphaS() const {return alphaSH;}
  double Q2Ren() const {return Q2RenH;}

  // Mandelstam variables (notation as if subcollision).
  double mHat() const {return sqrt(sH);}   
  double sHat() const {return sH;}   
  double tHat() const {return tH;}   
  double uHat() const {return uH;}   
  double pTHat() const {return pTH;} 
  double pT2Hat() const {return pTH*pTH;} 
  double m3Hat() const {return m3H;}   
  double m4Hat() const {return m4H;} 
  double thetaHat() const {return thetaH;}   

  // Impact parameter picture.
  double bMI() const {return (bIsSet) ? bH : 0.;}
  double enhanceMI() const {return (bIsSet) ? enhanceH : 0.;}

  // Number of times steps have been carried out. (incomplete??)
  int nMI() const {return nMIH;}
  int nISR() const {return nISRH;}
  int nFSRinProc() const {return nFSRinProcH;}
  int nFSRinRes() const {return nFSRinResH;}

private:

  // Store global quantities. 
  int idAM, idBM;
  double pzAM, eAM,mAM, pzBM, eBM, mBM, eCMM, sM;

  // Store current-event quantities.
  string nameSave, nameSubSave;
  int codeSave, codeSubSave, nFinalSave, nFinalSubSave, nTotal, id1H, id2H, 
    nMIH, nISRH, nFSRinProcH, nFSRinResH;
  bool isMB, isRes, isDiffA, isDiffB, hasSubSave, bIsSet;  
  double x1H, x2H, pdf1H, pdf2H, Q2FacH, alphaEMH, alphaSH, Q2RenH, 
    sH, tH, uH, pTH, m3H, m4H, thetaH, phiH, bH, enhanceH;

  // Set info on the two incoming beams: only from Pythia class.
  friend class Pythia;
  void setBeamA( int idAin, double pzAin, double eAin, double mAin) {
    idAM = idAin; pzAM = pzAin; eAM = eAin; mAM = mAin;}
  void setBeamB( int idBin, double pzBin, double eBin, double mBin) {
    idBM = idBin; pzBM = pzBin; eBM = eBin; mBM = mBin;}
  void setECM( double eCMin) {eCMM = eCMin; sM = eCMM * eCMM;}

  // Reset info for current event: only from Pythia class.
  void clear() {nameSave = " "; codeSave = nFinalSave = nTotal = id1H
    = id2H = nMIH = nISRH = nFSRinProcH = nFSRinResH; isRes = isDiffA
    = isDiffB = bIsSet = false; x1H = x2H = pdf1H = pdf2H = Q2FacH 
    = alphaEMH = alphaSH = Q2RenH = sH = tH = uH = pTH = m3H = m4H
    = thetaH = phiH = bH = enhanceH = 0.;}

  // Set info on the (sub)process: from ProcessLevel, ProcessContainer or 
  // MultipleInteractions classes.
  friend class ProcessLevel;
  friend class ProcessContainer;
  friend class MultipleInteractions;
  void setType( string nameIn, int codeIn, int nFinalIn,  
    bool isMinBiasIn = false, bool isResolvedIn = true, 
    bool isDiffractiveAin = false, bool isDiffractiveBin = false) {
    nameSave = nameIn; codeSave = codeIn; nFinalSave = nFinalIn; 
    isMB = isMinBiasIn; isRes = isResolvedIn; isDiffA = isDiffractiveAin; 
    isDiffB = isDiffractiveBin; nTotal = 2 + nFinalSave; bIsSet = false;
    hasSubSave = false; nameSubSave = " "; codeSubSave = 0; 
    nFinalSubSave = 0;}
  void setSubType( string nameSubIn, int codeSubIn, int nFinalSubIn) {  
    hasSubSave = true; nameSubSave = nameSubIn; codeSubSave = codeSubIn; 
    nFinalSubSave = nFinalSubIn;}
  void setPDFalpha( int id1In, int id2In,  double pdf1In, double pdf2In, 
    double Q2FacIn, double alphaEMIn, double alphaSIn, double Q2RenIn) 
    {id1H = id1In; id2H = id2In; pdf1H = pdf1In; pdf2H = pdf2In; 
    Q2FacH = Q2FacIn; alphaEMH = alphaEMIn; alphaSH = alphaSIn; 
    Q2RenH = Q2RenIn;}
  void setKin( double x1In, double x2In, double sHatIn, double tHatIn, 
    double uHatIn, double pTHatIn, double m3HatIn, double m4HatIn, 
    double thetaHatIn, double phiHatIn) {x1H = x1In; x2H = x2In; 
    sH = sHatIn; tH = tHatIn; uH = uHatIn; pTH = pTHatIn; m3H = m3HatIn; 
    m4H = m4HatIn; thetaH = thetaHatIn; phiH = phiHatIn;}

  // Set info on impact parameter: from ProcessContainer or PartonLevel.
  friend class PartonLevel;
  void setImpact( double bIn, double enhanceIn) {bH = bIn;
    enhanceH = enhanceIn, bIsSet = true;} 

  // Set info on number of evolution steps: only from PartonLevel class.
  void setCounters( int nMIIn, int nISRIn, int nFSRinProcIn, 
    int nFSRinResIn) { nMIH = nMIIn; nISRH = nISRIn; 
    nFSRinProcH = nFSRinProcIn; nFSRinResH= nFSRinResIn;}

};

//**************************************************************************

// This class holds info on all messages received and how many times.

class ErrorMessages {

public:

  // Constructor.
  ErrorMessages() {}

  // Normal init not needed for now. reInit resets to empty map.
  static void init() {}
  static void reInit() {messages.clear();}

  // Initialize static data members.
  static void initStatic();
  
  // Print a message the first few times. Insert in database.
  static void message(string messageIn, string extraIn = " ");

  // Print statistics on errors/warnings.
  static void statistics(ostream& os = cout);

private:

  // Static initialization data, normally only set once.
  static int timesToPrint;

  // Map for all error messages.
  static map<string, int> messages;
 
};
 
//**************************************************************************

} // end namespace Pythia8

#endif // Pythia8_Information_H