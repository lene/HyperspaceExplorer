// Vector.h: Schnittstelle für die Klasse Vector.
//
//////////////////////////////////////////////////////////////////////

#if !defined(Vector_H)
#define Vector_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//class string;


class Vector {
public:
	Vector ();
	Vector (const Vector &);
	Vector (unsigned i);
	Vector (double x, double y, double z);
	Vector (double w, double x, double y, double z);
	Vector (double *, unsigned);

	virtual ~Vector();

	Vector &operator= (const Vector &);

	double &operator[] (unsigned i) { return X[i]; }
	double  operator[] (unsigned i) const { return X[i]; }
	
	operator bool () { return (X != NULL); }

	Vector &operator+= (const Vector &);
	Vector &operator-= (const Vector &);
	Vector &operator*= (const double &);
	Vector &operator/= (const double &);

	Vector &operator+ (const Vector &) const;
	Vector &operator- (const Vector &) const;
	Vector &operator* (const double &) const;
	Vector &operator/ (const double &) const;

	double  operator* (const Vector &) const;

	double abs (void) { return operator* (*this); }
	Vector &normalize () { return operator/ (abs ()); }

	double *data () { return X; }
	unsigned D () const { return dim; }

	string Print ();

#if 0 // def _DEBUG
	static void PrintCalls (void) {
		MessageBox (NULL, 
				   ("CopyConstructorCalled "+itoa (CopyConstructorCalled)+" times\n"
				    "OperatorEqualCalled   "+itoa (OperatorEqualCalled)  +" times\n"
					"DestructorCalled	   "+itoa (DestructorCalled)	 +" times\n").c_str (),
					"Evaluation", MB_ICONINFORMATION);
	}
#endif

protected:
	unsigned dim;
	double *X;
	bool own;

#ifdef _DEBUG
	static unsigned CopyConstructorCalled,
					OperatorEqualCalled,
					DestructorCalled;
#endif

};

//	inline void glVertex3dv (Vector &V) { ::glVertex3dv (V.data ()); }

Vector vnormalize (const Vector &);
//Vector vnormalize (double, double, double);
Vector vcross (const Vector &, const Vector &);
Vector vcross (const Vector &, const Vector &, const Vector &);


#endif // !defined(AFX_Vector_H__012035AA_F382_11D3_B3AA_004005A4A929__INCLUDED_)
