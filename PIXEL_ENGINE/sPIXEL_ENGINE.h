#pragma once

#ifndef Windows
#include<Windows.h>
#endif // !Windows

#ifndef math
#include<math.h>
#endif

#ifndef iostream
#include<iostream>
#endif // !iostream


#ifndef chrono
#include<chrono>
#endif // !chrono


#ifndef vector
#include<vector>
#endif // !vector


#ifndef thread
#include<thread>
#endif // !thread




void ErrorExit(std::string ErrorMessage)
{
	std::cout << std::endl << ErrorMessage << std::endl;
	auto i = 0;
	std::cin >> i;
	exit(0);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//UTILITY FUNCTIONS (INDEPENDENT OF GAME ENGINE)





//----------------------STRUCTURE OF POSITION TO PLACE GAME OBJECTS-----------------------------------------------

struct Position
{
	//this Position in int to display in array
	int iX;
	int iY;

	//this Position in float to Calculate Next Position per sec
	float fX;
	float fY;


	Position() :iX(0), iY(0), fX(0.0f), fY(0.0f)
	{}

	Position(int X, int Y) :iX(X), iY(Y), fX(X), fY(Y)
	{}

	void operator*=(const float& Value)
	{
		this->fX *= Value;
		this->fY *= Value;
		this->iY *= Value;
		this->iY *= Value;
	}

	void operator/=(const float& Value)
	{
		this->fX /= Value;
		this->fY /= Value;
		this->iY /= Value;
		this->iY /= Value;
	}

	void operator =(const Position& RHS)
	{
		iX = RHS.iX;
		iY = RHS.iY;
		fX = RHS.fX;
		fY = RHS.fY;
	}

};









//------------------GENERIC VECTORS FOR STORING INFO GAME OBJECTS------------------------------------------------

template<typename T>
struct Generic_Vector
{
	T X;
	T Y;
	

	//CONSTURUCTORS
	Generic_Vector() :X(0), Y(0)
	{}

	Generic_Vector(T x, T y) :X(x), Y(y)
	{}


	//ARITHMATIC FUNCTIONS
	Generic_Vector<T> operator + (const Generic_Vector<T>& RHS)                { return Generic_Vector<T>(X + RHS.X, Y + RHS.Y); }
	Generic_Vector<T> operator -  (const Generic_Vector<T>& RHS)               { return Generic_Vector<T>(X - RHS.X, Y - RHS.Y); }
	Generic_Vector<T> operator /  (const T& Value)                             { return Generic_Vector<T>(X / Value, Y / Value); } 
	Generic_Vector<T> operator * (const T& Value)                              { return Generic_Vector<T>(X * Value, Y * Value); }
																			    																																 
																			    																																 
	//OPERATOR FUNCTIONS													    																										 
	void operator+=(const Generic_Vector<T>& RHS)                              { this->X += RHS.X;this->Y += RHS.Y;  }
	void operator-=(const Generic_Vector<T>& RHS)                              { this->X -= RHS.X;this->Y -= RHS.Y;  }
	void operator/=(const T& Value)                                            { this->X /= Value;this->Y /= Value;  }
	void operator*=(const T& Value)                                            { this->X *= Value;this->Y *= Value;  }    																					  
    bool operator==(const Generic_Vector<T>& RHS)                              { return (X == RHS.X && Y == RHS.Y);  }
	bool operator!=(const Generic_Vector<T>& RHS)                              { return (X != RHS.X && Y != RHS.Y);  }
																			    																																 
	//UTLILITY FUNCTIONS													    																											 
	T SclarProduct(const Generic_Vector<T>& RHS)                               { return (X * RHS.X + Y * RHS.Y); }
	T Mag()                                                                    { return (T)sqrtf((this->X * this->X) + (this->Y * this->Y)); }
	void Normalize()                                                           { T Magitude = this->Mag();   this->X /= Magitude;    this->Y /= Magitude;}

};








//-- VECTOR 2D FOR STORING COORDINATES ALONG WITH DIRECTION OG GAME OBJECTS ----------------

const float RadiansToDegrees = 180.0f / 3.1415f;
const float DegreesToRadians = 3.1415f / 180.0f;

struct Vector2D
{
	//Calculated Values of vector along x-axis and y-axis
	float X;
	float Y;

protected:

	//these from and to coordinates to choose new origin
	float From_X;
	float From_Y;

	float To_X;
	float To_Y;


	//Mag=Magnitude and angle made by vector w.r.t horizontal axis i.e positive x-axis
	float Mag;
	float DirectionAngle;


	//bool value to avoid double conversion 
	bool IsInDegree = false;


public:


	//default constructor
	Vector2D()
	{
		From_X = 0;
		From_Y = 0;
		To_X = 0;
		To_Y = 0;
		X = 0;
		Y = 0;
		Mag = 0.0f;
		DirectionAngle = 0.0f;

		IsInDegree = false;
	}


	//consyructor of vector in which origin is at (0,0)
	Vector2D(float x, float y) :X(x), Y(y)
	{
		From_X = 0.0f;
		From_Y = 0.0f;
		To_X = 0;
		To_Y = 0;


		Mag = sqrtf((X * X) + (Y * Y));


		//it only adjust the angle between the range 0 to 360
		DirectionAngle = atan2f(Y, X);    //Converts to Radian
		if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);


		IsInDegree = false;


	}


	//constructor of vector in which origin if (From_X ,From_Y) and (To_X,To_Y) is destination
	Vector2D(float From_x, float From_y, float To_x, float To_y)
	{
		if ((To_x == From_x) && (To_y == From_y))
		{
			From_X = 0;
			From_Y = 0;
			To_X = 0;
			To_Y = 0;
			X = 0;
			Y = 0;
			Mag = 0.0f;
			DirectionAngle = 0.0f;

			IsInDegree = false;
		}
		else
		{
			To_X = To_x;
			To_Y = To_y;
			From_X = From_x;
			From_Y = From_y;
			IsInDegree = false;
			X = To_X - From_X;
			Y = To_Y - From_Y;

			Mag = sqrtf(((X) * (X)) + ((Y) * (Y)));

			//it only adjust the angle between the range 0 to 360
			DirectionAngle = atan2f(Y, X);               //Converts to Radian
			if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
		}
	}



	//Section-1
	//contains all operators overloaded for vector arithmatic

	Vector2D operator +(const Vector2D& RHS) const                          { return  Vector2D(X + RHS.X, Y + RHS.Y);              }
	Vector2D operator -(const Vector2D& RHS)const                             { return  Vector2D(X - RHS.X, Y - RHS.Y);                 }
	Vector2D operator/(const float& Value)const                                     { return  Vector2D(X / Value, Y / Value);                     }
	Vector2D operator*(const float& Value)const                                     { return  Vector2D(X * Value, Y * Value);                    }
	void operator+=(const Vector2D& RHS);
	void  operator-=(const Vector2D& RHS);
	void operator/=(const float& Value);
	void operator*=(const float& Value);
	void operator =(const Vector2D& RHS);

	bool operator!=(const Vector2D& RHS) const                                     { return ((X != RHS.X) && (Y != RHS.Y) && (DirectionAngle != RHS.DirectionAngle));         }
	bool operator==(const Vector2D& RHS) const                                    { return ((X == RHS.X) && (Y == RHS.Y) && (DirectionAngle == RHS.DirectionAngle));   }


	//Section-2
	//contains  functions for user help

	//Magnitude becomes 1 we get unit vector pointing in that direction
	void Normalize();
	float GetMagnitude()                                                                                 { return Mag;                    }
	float GetDirection()                                                                                    { return DirectionAngle;   }

	void RadiansTo_Degree();          //Changes Angle From Rad To Deg
	void DegreesTo_Radians();       //Changes Angle From Deg To Rad



	//Section-3
	//contains manipluation of vector coordinates and angle by user
	void Subtract_InEach(const float& Value);
	void Add_InEach(const float& Value);

	void AngleChange_InDegrees(const float& Angle_InDegree);      //Make angle change in degrees( inputs in Degrees)
	void AngleChange_InRadians(const float& Angle_InRadian);      //Make angle change in radians (inputs in radians)



	//Section-4
	//contains vector sclar product formule
	float SclarProduct(const Vector2D& RHS)const                                             { return ((X * RHS.X) + (Y * RHS.Y)); }
	Vector2D ParallelogramAddition(const Vector2D&);



	//Destructor
	~Vector2D() {}

};



// ===================VECTOR 2D STRUCTURE IMPLEMENTATIONS=================

//-------------OPERATOR FUNCTIONS IMPLEMENTATIONS--------------
void Vector2D::operator+=(const Vector2D& RHS)
{
	this->X += RHS.X;
	this->Y += RHS.Y;

	this->Mag = sqrtf(X * X + Y * Y);

	this->DirectionAngle = atan2f(Y, X);
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);

}


void Vector2D::operator-=(const Vector2D& RHS)
{
	this->X -= RHS.X;
	this->Y -= RHS.Y;

	this->Mag = sqrtf(X * X + Y * Y);

	this->DirectionAngle = atan2f(Y, X);
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D::operator*=(const float& Value)
{
	this->X *= Value;
	this->Y *= Value;

	this->Mag = sqrtf(X * X + Y * Y);

	this->DirectionAngle = atan2f(Y, X);
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D ::operator/=(const float& Value)
{
	this->X /= Value;
	this->Y /= Value;

	this->Mag = sqrtf(X * X + Y * Y);

	this->DirectionAngle = atan2f(Y, X);
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D ::operator =(const Vector2D& RHS)
{
	X = RHS.X;
	Y = RHS.Y;
	DirectionAngle = RHS.DirectionAngle;
	Mag = RHS.Mag;
	From_X = RHS.From_X;
	From_Y = RHS.From_Y;
	To_X = RHS.To_X;
	To_Y = RHS.To_Y;
	IsInDegree = RHS.IsInDegree;
}



//UTILITY FUNCTIONS IMPLEMENTATIONS

void Vector2D::Normalize()
{
	Mag = sqrtf((X * X) + (Y * Y));

	X = this->X / this->Mag;
	Y = this->Y / this->Mag;

	Mag = sqrtf((X * X) + (Y * Y));
}

void Vector2D::RadiansTo_Degree()
{

	if (!IsInDegree)
		DirectionAngle *= RadiansToDegrees;

	IsInDegree = true;
}

void Vector2D::DegreesTo_Radians()
{

	if (IsInDegree)
		DirectionAngle *= DegreesToRadians;

	IsInDegree = false;

}


//ANGLE MANAGING FUNCTIONS IMPLEMENTATIONS
void Vector2D::Add_InEach(const float& Value)
{
	X += Value;
	Y += Value;

	Mag = sqrtf((X * X) + (Y * Y));

	DirectionAngle = atan2f(Y, X);    //Converts to Radian

	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D::Subtract_InEach(const float& Value)
{
	X -= Value;
	Y -= Value;


	Mag = sqrtf((X * X) + (Y * Y));


	DirectionAngle = atan2f(Y, X);          //Converts to Radian
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D::AngleChange_InDegrees(const float& Angle_InDegree)
{
	if (!IsInDegree)
		this->RadiansTo_Degree();

	float Angl = Angle_InDegree;

	if (Angle_InDegree >= 360)
	{

		float i = Angle_InDegree / 360.0f;

		Angl -= (i * 360.0f);
	}

	DirectionAngle += Angl;

	if (DirectionAngle <= -360.0f)
	{
		float i = DirectionAngle / 360.0f;

		DirectionAngle += (i * 360.0f);

		DirectionAngle += 360.0f;

	}

	if (DirectionAngle<0.0f && DirectionAngle>-360.0f)
	{
		DirectionAngle += 360.0f;
	}


	X = (Mag * cos(DirectionAngle * DegreesToRadians)) + From_X;
	Y = (Mag * sin(DirectionAngle * DegreesToRadians)) + From_Y;


}


void Vector2D::AngleChange_InRadians(const float& Angle_InRadian)
{
	if (IsInDegree)
		this->DegreesTo_Radians();

	float Angl = Angle_InRadian;

	if (Angle_InRadian >= 6.283f)
	{

		float i = Angle_InRadian / 6.283f;

		Angl -= (i * 6.283f);
	}

	DirectionAngle += Angl;

	if (DirectionAngle <= -6.283f)
	{
		float i = DirectionAngle / 6.283f;

		DirectionAngle += (i * 6.283f);

		DirectionAngle += 6.283f;

	}

	if (DirectionAngle<0.0f && DirectionAngle>-6.283f)
	{
		DirectionAngle += 6.283f;
	}


	X = (Mag * cos(DirectionAngle)) + From_X;
	Y = (Mag * sin(DirectionAngle)) + From_Y;
}


//CALCULATINF RESULTANT VECTOR IMPLEMENTATION
Vector2D Vector2D::ParallelogramAddition(const Vector2D& Second_Vector)
{
	float SecondAngle = Second_Vector.DirectionAngle;

	this->DegreesTo_Radians();

	if (Second_Vector.IsInDegree)SecondAngle = SecondAngle * DegreesToRadians;


	float XMag = this->Mag * cosf(this->DirectionAngle) + Second_Vector.Mag * cosf(SecondAngle);
	float YMag = this->Mag * sinf(this->DirectionAngle) + Second_Vector.Mag * sinf(SecondAngle);

	Vector2D Resultant;

	Resultant.Mag = sqrtf(((this->Mag * this->Mag) + (Second_Vector.Mag * Second_Vector.Mag) + 2 * this->Mag * Second_Vector.Mag * cosf(fabsf(this->DirectionAngle - SecondAngle))));

	Resultant.DirectionAngle = atan2f(YMag, XMag);

	if (Resultant.DirectionAngle <= 0.0f)Resultant.DirectionAngle += 2.0f * 3.1415f;

	Resultant.X = Resultant.Mag * cosf(Resultant.DirectionAngle);
	Resultant.Y = Resultant.Mag * sinf(Resultant.DirectionAngle);

	return Resultant;
}









// ----------------    TRACK OF GAME TIME ---   TIME CLASS   -------------------------------------------------------------------------

class Time
{
	int iHours;
	int iMinutes;
	int iSeconds;
	float fSeconds;


	int TimeToNumber();                                          //Returns Number which is calculated from time i.e smallest unit time seconds
	void NumberToTime(const int Number);            //converts given number to time i.e seconds and minutes , hours

public:

	Time()
	{
		iHours = 0;
		iMinutes = 0;
		iSeconds = 0;
		fSeconds = 0.0f;
	}

	Time(int hours, int minutes, int seconds)
	{
		if (hours >= 0 && minutes >= 0 && seconds >= 0)
		{
			int Total = (hours * 60 * 60) + (minutes * 60) + seconds;
			int min, hor;

			int sec = Total % 60;
			int min_t = Total / 60;

			if (min_t > 59)
			{
				min = min_t % 60;
				hor = min_t / 60;
			}
			else
			{
				min = min_t;
				hor = 0;
			}

			iHours = hor;
			iMinutes = min;
			iSeconds = sec;
			fSeconds = iHours * 60 * 60 + iMinutes * 60 + iSeconds;
		}
	}

public:

	//operator functions
	bool operator ==(const Time& RHS)                         { return ((iHours == RHS.iHours) && (iMinutes == RHS.iMinutes) && (iSeconds == RHS.iSeconds));       }
	bool operator !=(const Time& RHS)                          { return ((iHours != RHS.iHours) && (iMinutes != RHS.iMinutes) && (iSeconds != RHS.iSeconds));              }
	void operator =(const Time& RHS)                           { iHours = RHS.iHours; iMinutes = RHS.iMinutes; iSeconds = RHS.iSeconds; fSeconds = RHS.fSeconds;        }

	void operator +=(Time& RHS);
	void operator -=(Time& RHS);
	void operator *=(const int& Value);
	void operator /=(const int& Value);

	Time operator +(Time& RHS);
	Time operator -(Time& RHS);
	Time operator *(const int& Value);
	Time operator /(const int& Value);

	//Arithmatic Functions
	void AddIn_Seconds(const int& Value);
	void AddIn_Minutes(const int& Value);
	void AddIn_Hours(const int& Value);

	void SubtractFrom_Seconds(const int& Value);
	void SubtractFrom_Minutes(const int& Value);
	void SubtractFrom_Hours(const int& Value);

	void AddIn_FSeconds(const float& Value);
	void SubtractFrom_FSeconds(const float& Value);

	//Return Values
	int Get_Seconds()                                                        { return iSeconds;                   }
	int Get_Minutes()                                                        { return iMinutes;                   }
	int Get_Hours()                                                           { return iHours;                      }
	float Get_FSeconds()                                                   { return fSeconds;                    }  
	bool IsTimeOver()                                                       { return !(iHours * 60 * 60 + iMinutes * 60 + iSeconds);    }
};


//=====================TIME CLASS IMPLEMENTATIONS======================

//Private Functions
int Time::TimeToNumber()
{
	return ((60 * 60 * iHours) + (60 * iMinutes) + iSeconds);
}

void Time::NumberToTime(const int Number)
{
	if (Number > 0)
	{
		int min = 0, hor = 0;
		int min_t = Number / 60;
		int sec = Number % 60;

		if (min_t > 59)
		{
			min = min_t % 60;
			hor = min_t / 60;
		}
		else
		{
			min = min_t;
			hor = 0;
		}

		iHours = hor;
		iMinutes = min;
		iSeconds = sec;
	}
	else
	{
		iHours = 0;
		iMinutes = 0;
		iSeconds = 0;
	}
}


//Operator Functions
void Time::operator +=(Time& RHS)
{
	int Rhs = RHS.TimeToNumber();
	int Self = this->TimeToNumber();

	Self = Self + Rhs;

	this->NumberToTime(Self);
}

void Time::operator -=(Time& RHS)
{
	int Rhs = RHS.TimeToNumber();
	int Self = this->TimeToNumber();

	if (Rhs >= Self)
	{
		this->iSeconds = 0;
		this->iMinutes = 0;
		this->iSeconds = 0;

		return;
	}
	else if (Rhs < Self)
	{
		Self = Self - Rhs;
	}
	this->NumberToTime(Self);
	return;
}

void Time::operator *=(const int& Value)
{
	if (Value >= 0)
	{
		int Self = this->TimeToNumber();
		Self = Self * Value;
		this->NumberToTime(Self);
	}
}

void Time::operator /=(const int& Value)
{
	if (Value > 0)
	{
		int Self = this->TimeToNumber();
		Self = Self / Value;
		if (Self <= 0)
		{
			iSeconds = 0;
			iHours = 0;
			iMinutes = 0;
		}
		else
		{
			this->NumberToTime(Self);
		}


	}
}


///////
Time Time::operator + (Time& RHS)
{
	Time Result;
	int Total = this->TimeToNumber() + RHS.TimeToNumber();

	Result.NumberToTime(Total);

	return Result;
}

Time Time::operator - (Time& RHS)
{
	Time Result;
	if (this->TimeToNumber() <= RHS.TimeToNumber())
	{
		return Result;
	}
	else if (this->TimeToNumber() > RHS.TimeToNumber())
	{
		int Total = this->TimeToNumber() - RHS.TimeToNumber();

		Result.NumberToTime(Total);

		return Result;
	}
	return Result;
}

Time Time::operator *(const int& Value)
{
	Time Result;
	if (Value >= 0)
	{

		int Total = this->TimeToNumber() * Value;

		Result.NumberToTime(Total);

		return Result;
	}
	return Result;
}

Time Time::operator/(const int& Value)
{
	Time Result;

	if (Value > 0)
	{
		int Self = this->TimeToNumber();
		Self = Self / Value;
		if (Self <= 0)
		{
			return Result;
		}

		Result.NumberToTime(Self);

		return Result;
	}

	return Result;
}


//Arithmatic Functions

void Time::AddIn_Seconds(const int& Value)
{
	if (Value > 0)
	{
		int Self = this->TimeToNumber();
		Self = Self + Value;
		this->NumberToTime(Self);
	}
}

void Time::AddIn_Minutes(const int& Value)
{
	if (Value > 0)
	{
		int Self = (iHours * 60) + iMinutes;
		Self = Self + Value;

		iMinutes = Self % 60;
		iHours = Self / 60;
	}
}

void Time::AddIn_Hours(const int& Value)
{
	if (Value > 0)
		iHours = iHours + Value;
}


void Time::SubtractFrom_Seconds(const int& Value)
{
	if (Value > 0)
	{
		int Self = this->TimeToNumber();
		if (Self >= Value)
			Self = Self - Value;
		else Self = 0;
		this->NumberToTime(Self);
	}
}

void Time::SubtractFrom_Minutes(const int& Value)
{
	if (Value > 0)
	{
		if (Value < ((iHours * 60) + iMinutes))
		{
			int Self = ((iHours * 60) + iMinutes);
			Self = Self - Value;
			iMinutes = Self % 60;
			iHours = Self / 60;
		}
		else
		{
			iMinutes = 0;
			iHours = 0;
		}
	}
}

void Time::SubtractFrom_Hours(const int& Value)
{
	if (Value < iHours)
	{
		iHours = iHours - Value;
	}
	else
	{
		iHours = 0;
	}
}


////////////

void Time::AddIn_FSeconds(const float& Value)
{
	fSeconds += Value;
	int Self = fSeconds;
	this->NumberToTime(Self);
}

void Time::SubtractFrom_FSeconds(const float& Value)
{
	if (fSeconds > Value)
	{
		fSeconds -= Value;
		int Self = fSeconds;
		this->NumberToTime(Self);
	}
	else
	{
		fSeconds = 0.0f;
		this->NumberToTime(0);
	}
}








//---------------------------------------------------  UTILITY FUNCTIONS DEFINATIONS OVER ---------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//-------------------------------==   CONTAINS ALL IN-USE DATA OF PIXEL ENGINE CLASS  ==----------------------------

struct Screen_Layout
{
	//Total Number of Variables Uesed in this Struct   ------->   25 Variables


	//Main Screen          ---   Variables = 5
	             
	                                     

	Generic_Vector<short> gvsScreen_Coordinates;         // starting coordinates of screen
	short sScreen_Width;                                                    //screen width from origin coordinates
	short sScreen_Height;                                                   //screen height from origin coordinates
	 

	short sScreen_Color;                                                    // Main Screen background color
	bool bScreen_Transperency;                                        //Whether to Draw the screen or not
	

	//-----------------------------------------------------------------------------


	//Text To Display(MESSAGE)           ---- Variables  = 7
	short sText_Color;                      //Message displaying foreground Color

	short sText_FontSize;                  //Message Font Size 


	std::string stText_ToDisplay;      //Message to Display

	                      //Imaginary Box into Whih Message Should be Displayed
	short sText_Width;                      //Box's Width                         
	short sText_Height;                     //box's Height

	short sText_OffsetX;
	short sText_OffsetY;

	//-----------------------------------------------------------------------------


	//Buttons                                               ----- Variables = 12
	bool bButtonAlignH;                      //Buttons Displaying in Vertically(false) or Horizontally(true)

	short sTotal_Buttons;                    //Total Number oF Buttons To Display (maximum 3 buttons)

	short sButton_Width;                     //Width Of the button
	short sButton_Height;                    //Height of button

	short sButton_TextFontSize;          //Font Size to Display in Button Text
	short sButton_TextFontDepth;       //Thickness of Text

	short sButton_Color;                     //Button Background Color
	short sButton_TextColor;              //Button Text Color
	short sButton_BorderColor;          //Button Border Color

	std::string Button1_Name;            //First Button Name
	std::string Button2_Name;            //Second Button Name
	std::string Button3_Name;            //Third Button Name
   	
	short sButton_SelectColor;            //Color To display when the Button is Selected

	short sButton_Selected;                 //Which Button is Selected it Keeps the Track of It (1th or 2nd or 3rd)

	short sButton_OffsetBetButton;



public:

	Screen_Layout()
	{

		//Main Screen 
			


		gvsScreen_Coordinates = { 1,1 };


		sScreen_Width = 160;
		sScreen_Height = 150;


		sScreen_Color = 0xff;
		bScreen_Transperency = false;



		//Text Display
		
		sText_Color = 0x00;

		sText_FontSize = 10;
		
		sText_Width = 99;
		sText_Height =20;

		stText_ToDisplay = "WELCOME";

		sText_OffsetX = 4;
		sText_OffsetY = 4;

		//Button Display

		sButton_Selected = 0;

		bButtonAlignH = false;

		sTotal_Buttons = 1;

		sButton_Height = 25;
		sButton_Width = 50;

		sButton_TextFontSize = 5;
		sButton_TextFontDepth = 1;

		sButton_BorderColor = 0x00;
		sButton_TextColor = 0x00;
		sButton_Color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;

		Button1_Name = "PLAY";
		Button2_Name = "HELLO";
		Button3_Name = "BACK";

		sButton_SelectColor = 0xbe;

		sButton_OffsetBetButton = 4;


	}

};





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class PIXEL_ENGINE
{
private:

	short sScreenWidth;                                 //DEFINES CONSOLE SCREEN WIDTH
	short sScreenHeight;                                //DEFINES CONSOLE SCREEN HEIGHT
	

	//------------------------------------------


	short sPixelWidth;                                  //DEFINES FONT SIZE-----(i.e PIXEL SIZE IN WIDTH)
	short sPixelHeight;                                 //DEFINES FONT SIZE-----(i.e PIXEL SIZE IN HEIGTH)
	

	//-------------------------------------------


	float fElapsedTime;                               //STORES TIME ELASPED AFTER UPDATING LAST FRAME


	//-------------------------------------------


	HANDLE hScreenHandle;                    //HANDLE TO THE OUTPUT SCREEN OR CONSOLE
	SMALL_RECT srWindowSize;             //STORING WINDOW COORD 
	COORD cdBufferSize;                         //STORING BUFFER SIZE
	CONSOLE_FONT_INFOEX cfiexFont;   //STORING PIXEL(i.e FONTS ) RELATED INFO
	bool bSuccessfullyConsoleCreated;       

	//---------------------------------------------


	//----------  TIME TRACKING NEEDED TO UPDATE FRAME  -----------//
	std::chrono::time_point<std::chrono::system_clock> tpStart, tpEnd;
	std::chrono::duration<float, std::ratio<1, 1>> dSecondsPassed;




	//----------------------  PRIVATE FUNCTIONS  ------------------------//

	void pDrawCharacter(const char& Char, const Generic_Vector<short>& OriginCoord, const short& Length=5, const short& Pixel_Color=0x0ff, short Thickness=0);


	
	
protected:

	CHAR_INFO* ciScreen;                //POINTER TO THE ONE DIMENSIONAL ARRAY(i,e  SCREEN)
	
	bool bExitGame;                           // BOOLEAN TO STOP RENDERING GAME (i.e GAME OVER)


	//----------------------------------------


	bool virtual OnUserStart() = 0;                     // USER MUST OVERRIDE THIS FUNCTION

	bool virtual OnUserUpdate() = 0;                // USER MUST OVERRIDE THIS FUNCTION


public:



	// SETTING DEFAULT VALUES
	PIXEL_ENGINE()
	{
		sScreenHeight = 50;
		sScreenWidth = 100;
		sPixelHeight = 16;
		sPixelWidth = 16;
		fElapsedTime = 0.0f;
		bExitGame = false;
		bSuccessfullyConsoleCreated = false;
	}


	// SETTING USER GIVEN VALUES
	PIXEL_ENGINE(short ScreenWidth, short ScreenHeight, short PixelWidth, short PixelHeight)
	{
		if (ScreenWidth > 0 && ScreenHeight > 0 && PixelHeight > 0 && PixelWidth > 0)
		{
			sScreenHeight = ScreenHeight;
			sScreenWidth = ScreenWidth;
			sPixelHeight = PixelHeight;
			sPixelWidth = PixelWidth;
			fElapsedTime = 0.0f;
			bExitGame = false;
			bSuccessfullyConsoleCreated = false;
		}
		else
		{
			bSuccessfullyConsoleCreated = false;
			bExitGame = false;
			fElapsedTime = 0.0f;
			ErrorExit("Error in setting Constructor Values");
		}
	}



public:


	//------RETURNS SOME USEFULL VALUES TO USER---------//
	float Get_fElapsedTime()               {	return fElapsedTime;  }
	short Get_ScreenWidth()               { return sScreenWidth;  }
	short Get_ScreenHeight()              { return sScreenHeight; }
	




	//-------- MAIN GAME ENGINE FUNCTIONS ------------------//
	bool ConstructConsole();
	void StartEngine();



	//---------- DESTRUCTOR -----------------//
	~PIXEL_ENGINE()
	{
		
	}

	
public:

	//----------------- ALL DRAWING AND UTILITY FUNCTIONS ------------------------------------//

	void pDrawLine(const Generic_Vector<short>& InitialCoord,const Generic_Vector<short>& FinalCoord,const short& Pixel_Color=0xff, short Thickness = 0);

	void pDrawSolidRectangle(const Generic_Vector<short>& LeftxTopy, const Generic_Vector<short>& RightxBottomy, const short& Pixel_Color = 0xff);

	void pDrawRectangle(const Generic_Vector<short>& LeftxTopy,const Generic_Vector<short>& RightxBottomy,const short& Pixel_Color=0xff, const short Thickness=0);

	void pDrawCircle(const Generic_Vector<short>& OriginCoord,short Radius,const short& Pixel_Color=0xff,short Thickness=0);

	void pDrawSolidCircle(const Generic_Vector<short>& OriginCoord, short Radius,const short& Pixel_Color=0xff);

	void pDrawArc(const Generic_Vector<short>& OriginCoord, short Radius,const short& StartingAngleDegree, const short& EndingAngleDegree,const short& Pixel_Color=0xff,short Thickness=0);
	
	void pDrawSector(const Generic_Vector<short>& OriginCoord, short Radius, const short& StartingAngleDegree, const short& EndingAngleDegree, const short& Pixel_Color=0xff);

	void pDrawText(const std::string& Text, const Generic_Vector<short>& OriginCoord, const short WidthOfText, const short HeightOfText, const short& IndiviualLength, const short& Pixel_Color=0xff, short Thickness=0);

	void pDrawGrass1(const Generic_Vector<short>& OriginCoord, const short& Length, const short& Pixel_Color, short Thickness);

	void pDrawTree1(const Generic_Vector<short>& OriginCoord, const short& Length, const short& Pixel_Color_Trunk, const short& Pixel_Color_Leafs);

	void pDrawCloud1(const Generic_Vector<short>& OriginCoord, const short& Length, const short& Pixel_Color);

	void pDrawLeveledGround(const Generic_Vector<short>& OriginCoord,const short& Length, const short& Height, const short& Pixel_Color_Upper, const short& Pixel_Color_Lower = 0xff, short Thickness = 0);

	void pDrawCharacterNo1(const Generic_Vector<short>& OriginCoord, const short& Length,const bool& WithGun, const short& Pixel_HairColor, const short& Pixel_BodyColor, const short& Pixel_GunColor1, const short& Pixel_GunColor2);

	void pDrawCharacterNo2(const Generic_Vector<short>& OriginCoord, const short& Length, const bool& WithGun, const short& Pixel_BodyColor, const short& Pixel_GunColor1, const short& Pixel_GunColor2);

	short pBuild_Screen(Screen_Layout& Screen);
};








//============ PIXEL_ENGINE IMPLEMENTATION =======================================


bool PIXEL_ENGINE::ConstructConsole()
{

	//-----SETTING UP VALUES OF BUFFER COORD-------
	cdBufferSize.X = sScreenWidth;
	cdBufferSize.Y = sScreenHeight;



	//-----SETTING UP VALUES OF WINDOW SMALL RECT--------
	srWindowSize.Bottom = sScreenHeight - 1;
	srWindowSize.Right = sScreenWidth - 1;
	srWindowSize.Left = 0;
	srWindowSize.Top = 0;



	//------SETTING UP VALUES OF FONT INFO EX ------------
	cfiexFont.cbSize = sizeof(cfiexFont);
	cfiexFont.dwFontSize.X = sPixelWidth;
	cfiexFont.dwFontSize.Y = sPixelHeight;



	//------- GETTING HANDLE OF PIXEL_ENGINE SCREEN------
	hScreenHandle = GetStdHandle(STD_OUTPUT_HANDLE || STD_INPUT_HANDLE);



	//-------CHECKING FOR VALID HANDLE VALUE -----------
	if (hScreenHandle == INVALID_HANDLE_VALUE)
	{
		ErrorExit("CONSOLE HANDLE NOT OBTAIN ");
		return false;
	}



	//-------- CREATING CONSOLE OF SPECIFIC BUFFER SIZE --------------
	if (!SetConsoleScreenBufferSize(hScreenHandle, cdBufferSize))
	{
		ErrorExit("ERROR IN SETTING BUFFR SIZE ");
		return false;
	}


	//--------- CREATING CONSOLE OF SPECIFIC PIXELs -------
	if (!SetCurrentConsoleFontEx(hScreenHandle, FALSE, &cfiexFont))
	{
		ErrorExit("ERROR IN SETTINFG PIXEL SIZE ");
		return false;
	}



	//---------- CREATING CONSOLE OF SPECIFIC WINDOW SIZE---------
	if (!SetConsoleWindowInfo(hScreenHandle, TRUE, &srWindowSize))
	{
		ErrorExit("ERROR IN SETTING WINDOW SIZE");
		return false;
	}


	//------- SETTING CONSOLE ACTIVE SCREEN BUFFER HANDLE-------
	SetConsoleActiveScreenBuffer(hScreenHandle);


	//------- TAKING UP DYNAMIC MEMORY FROM OPERATING SYSTEM ---------
	ciScreen = new CHAR_INFO[sScreenHeight * sScreenWidth];


	bSuccessfullyConsoleCreated = true;

	return true;
}


void PIXEL_ENGINE::StartEngine()
{
	if (bSuccessfullyConsoleCreated)
	{
		if (!OnUserStart())
		{
			bExitGame = true;
		}

		bool bStartDeltaTime = false;

		while (!bExitGame)
		{

			if (bStartDeltaTime)
			{
				dSecondsPassed = tpEnd - tpStart;
				fElapsedTime = dSecondsPassed.count();
			}

			tpStart = std::chrono::system_clock::now();


			if (!OnUserUpdate()) bExitGame = true;


			WriteConsoleOutput(hScreenHandle, ciScreen, cdBufferSize, { 0,0 }, &srWindowSize);

			tpEnd = std::chrono::system_clock::now();
			bStartDeltaTime = true;
		}

		this->~PIXEL_ENGINE();
	}
}






//----------------- ALL PRIVATE  FUNCTIONS  IMPLEMENTATIONS ------------------------------------//

void PIXEL_ENGINE::pDrawCharacter(const char& Char, const Generic_Vector<short>& OriginCoord, const short& Length, const short& Pixel_Color, short Thickness)
{
	switch (Char)
	{
	case 'A':
	{
		//Leftmost Vertical Line
		pDrawLine(OriginCoord, { OriginCoord.X,OriginCoord.Y + Length+2 }, Pixel_Color, Thickness/4);

		//Top most horizontal line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness/4);

		//Rightmostt vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X + Length,OriginCoord.Y + Length +2}, Pixel_Color, Thickness/4);


		//Middle line
		pDrawLine({ OriginCoord.X,OriginCoord.Y + (Length / 2) }, { OriginCoord.X + Length,OriginCoord.Y + (Length / 2) }, Pixel_Color, Thickness/4);


		break;
	}

	case 'B':
	{
		//Left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X,OriginCoord.Y + Length }, Pixel_Color, Thickness/4);

		//Upper line
		pDrawLine(OriginCoord, { OriginCoord.X + Length ,OriginCoord.Y}, Pixel_Color, Thickness / 4);

		//Middle line
		pDrawLine({ OriginCoord.X,OriginCoord.Y+Length/2 }, { OriginCoord.X+Length,OriginCoord.Y + Length/2 }, Pixel_Color, Thickness / 4);

		//Lower line
		pDrawLine({ OriginCoord.X,OriginCoord.Y+Length }, { OriginCoord.X+Length,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		//upper arc
		pDrawArc({ OriginCoord.X+Length-2 , OriginCoord.Y + (Length  / 4) }, (Length/4 ), 270, 90, Pixel_Color,Thickness/2);

		//lower arc
		pDrawArc({ OriginCoord.X+Length-2 , OriginCoord.Y + (Length * 3) / 4 }, (Length/4 ), 270, 90, Pixel_Color,Thickness/2);



		break;
	}

	case 'C':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//left most vertical line
		pDrawLine( OriginCoord, { OriginCoord.X ,OriginCoord.Y+Length }, Pixel_Color, Thickness / 4);

		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y+  Length }, Pixel_Color, Thickness / 4);



		break;
	}
	
	case 'D':
	{
		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length}, Pixel_Color, Thickness / 4);
		
		//bottom most line small
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X +(Length*2)/8 ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		//upper most line small
		pDrawLine(OriginCoord, { OriginCoord.X + (Length * 2) / 8 ,OriginCoord.Y  }, Pixel_Color, Thickness / 4);

		//Curve
		pDrawArc({ OriginCoord.X+(Length*1)/6,OriginCoord.Y + (Length / 2) }, (Length*6)/8 , 270, 88, Pixel_Color, Thickness / 2);
		

		break;
	}

	case 'E':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		//Middle line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length/2 }, { OriginCoord.X+ Length ,OriginCoord.Y + Length/2 }, Pixel_Color, Thickness / 4);


		break;
	}


	case 'F':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length +2}, Pixel_Color, Thickness / 4);

		//Middle line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length  ,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);


		break;
	}

	case 'G':
	{

		//Draws Arc
		pDrawArc({ OriginCoord.X + (Length / 2),OriginCoord.Y + (Length / 2) }, Length*3/4 , 40, 290, Pixel_Color, Thickness / 2);

		//middle line 
		pDrawLine({ OriginCoord.X + Length / 2,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);

		//vertical line bottom
		pDrawLine({ OriginCoord.X + Length ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length,OriginCoord.Y + Length+4  }, Pixel_Color, Thickness / 4);

		break;
	}


	case 'H':
	{
		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length+2 }, Pixel_Color, Thickness / 4);

		//right most vertical line
		pDrawLine({ OriginCoord.X + Length ,OriginCoord.Y  }, { OriginCoord.X + Length ,OriginCoord.Y + Length+2 }, Pixel_Color, Thickness / 4);

		//middle line
		pDrawLine({ OriginCoord.X  ,OriginCoord.Y+Length/2 }, { OriginCoord.X + Length ,OriginCoord.Y + Length/2 }, Pixel_Color, Thickness / 4);


		break;
	}


	case 'I':
	{
		//upper most horzontal line
		pDrawLine(OriginCoord, { OriginCoord.X + Length+1,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//middle vertical line
		pDrawLine({ OriginCoord.X+Length/2,OriginCoord.Y }, { OriginCoord.X + Length/2,OriginCoord.Y+Length }, Pixel_Color, Thickness / 4);

		//lower most horzontal line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length+1 ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		break;
	}


	case 'J':
	{
		//upper most horzontal line
		pDrawLine(OriginCoord, { OriginCoord.X + Length + 1,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//middle vertical line
		pDrawLine({ OriginCoord.X + Length / 2,OriginCoord.Y }, { OriginCoord.X + Length / 2,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		//lower most horzontal line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X +Length/2 +1 ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		break;
	}


	case 'K':
	{

		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length+2 }, Pixel_Color, Thickness / 4);

		//upper cross vertical line
		pDrawLine({OriginCoord.X,OriginCoord.Y + Length / 2 }, { OriginCoord.X+Length ,OriginCoord.Y}, Pixel_Color, Thickness / 4);

		//lower cross  vertical line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X+Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		break;
	}


	case 'L':
	{
		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		break;
	}


	case 'M':
	{
		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		//Left slanting vertical line
		pDrawLine(OriginCoord, { OriginCoord.X + Length/2,OriginCoord.Y + Length  }, Pixel_Color, Thickness / 4);


		//Right slanting  vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X + Length/2,OriginCoord.Y + Length}, Pixel_Color, Thickness / 4);


		//Rightmostt vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X + Length,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		break;
	}


	case 'N':
	{
		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		//Right most  vertical line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		//Rightmostt vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X + Length,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		break;
	}


	case 'O':
	{
		//Circle
		pDrawCircle({ OriginCoord.X + Length / 2,OriginCoord.Y + Length / 2 }, Length*4/6 , Pixel_Color, Thickness/3);

		break;
	}


	case 'P':
	{
		//rectangle
		pDrawRectangle(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y + Length / 2 }, Pixel_Color,Thickness/4);

		//Leftmost vertical line
		pDrawLine(OriginCoord, { OriginCoord.X,OriginCoord.Y + Length +2}, Pixel_Color, Thickness / 4);
	
		
		break;
	}


	case 'Q':
	{
		//middle circle
		pDrawCircle({ OriginCoord.X + Length / 2,OriginCoord.Y + Length / 2 }, Length * 4 / 6, Pixel_Color, Thickness / 3);

		//slanting line
		pDrawLine({ OriginCoord.X + Length / 2 ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length,OriginCoord.Y + Length +4}, Pixel_Color, Thickness/4 );
		break;
	}


	case 'R':
	{
		//rectangle
		pDrawRectangle(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);

		//Leftmost vertical line
		pDrawLine(OriginCoord, { OriginCoord.X,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);
		
		//slanting line
		pDrawLine({ OriginCoord.X  ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length,OriginCoord.Y + Length +2 }, Pixel_Color, Thickness / 4);




		break;
	}



	case 'S':
	{
		//upper curve
		pDrawArc({ OriginCoord.X + Length/4,OriginCoord.Y + Length / 4 }, Length/3 ,90,270,Pixel_Color,Thickness/3);

		//upper most horzontal line
		pDrawLine(OriginCoord, { OriginCoord.X + Length + 1,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//Middle line
		pDrawLine({ OriginCoord.X+(Length/4) ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length ,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);


		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + (Length*3)/4 ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		//lower curve
		pDrawArc({ OriginCoord.X + (Length*3)/4,OriginCoord.Y + (Length*3) /4  }, Length/3 ,270,90, Pixel_Color, Thickness / 3);

		break;
	}



	case 'T':
	{
		//upper most horzontal line
		pDrawLine(OriginCoord, { OriginCoord.X + Length + 1,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//middle vertical line
		pDrawLine({ OriginCoord.X + Length / 2,OriginCoord.Y }, { OriginCoord.X + Length / 2,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		break;
	}


	case 'U':
	{
		//Leftmost vertical line
		pDrawLine(OriginCoord, { OriginCoord.X,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);


		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		//right most vertical line
		pDrawLine({ OriginCoord.X + Length ,OriginCoord.Y }, { OriginCoord.X + Length ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		break;
	}


	case 'V':
	{
		//Leftmost vertical line
		pDrawLine(OriginCoord, { OriginCoord.X+Length/2,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		//RightMost vertical line
		pDrawLine({ OriginCoord.X+Length,OriginCoord.Y }, { OriginCoord.X+Length/2,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);


		break;
	}


	case 'W':
	{
		//Left most slanting vertical line
		pDrawLine(OriginCoord, { OriginCoord.X + Length/4 ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		//Left slanting vertical line
		pDrawLine({ OriginCoord.X + Length / 4 ,OriginCoord.Y + Length + 2 }, { OriginCoord.X + Length / 2 ,OriginCoord.Y + Length/2 }, Pixel_Color, Thickness / 4);
		
		//Right slanting vertical line
		pDrawLine({ OriginCoord.X + (Length * 3) / 4 ,OriginCoord.Y + Length + 2 }, { OriginCoord.X + Length / 2 ,OriginCoord.Y + Length/2 }, Pixel_Color, Thickness / 4);

		//Right most slanting vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X+(Length*3)/4 ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);


		break;
	}


	case 'X':
	{
		//Left slanting vertical line
		pDrawLine(OriginCoord, { OriginCoord.X + Length ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		//Right slanting vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);


		break;
	}


	case 'Y':
	{
		//Left slanting vertical line
		pDrawLine(OriginCoord, { OriginCoord.X + Length/2 ,OriginCoord.Y + Length/2 }, Pixel_Color, Thickness / 4);

		//Right slanting vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X+Length/2 ,OriginCoord.Y + Length/2 }, Pixel_Color, Thickness / 4);

		//Middle vertical line
		pDrawLine({ OriginCoord.X + Length / 2 ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length / 2 ,OriginCoord.Y + Length +2 }, Pixel_Color, Thickness / 4);


		break;
	}


	case 'Z':
	{
		//upper most horzontal line
		pDrawLine(OriginCoord, { OriginCoord.X + Length + 1,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//Right slanting vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);


		//lower most horzontal line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length + 1 ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		break;
	}

	case '0':
	{
		pDrawRectangle(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		break;
	}

	case '1':
	{
		//middle vertical line

		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length / 2,OriginCoord.Y }, Pixel_Color, Thickness / 4);


		//middle vertical line
		pDrawLine({ OriginCoord.X + Length / 2,OriginCoord.Y }, { OriginCoord.X + Length / 2,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		//lower most horzontal line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length + 1 ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		break;
	}

	case '2':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);



		//Right most vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X + Length,OriginCoord.Y+Length/2 }, Pixel_Color, Thickness / 4);


		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		//left most vertical line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length/2 }, { OriginCoord.X,OriginCoord.Y + Length  }, Pixel_Color, Thickness / 4);


		//Middle line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length ,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);



		break;
	}

	case '3':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//Right most vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X + Length,OriginCoord.Y + Length  }, Pixel_Color, Thickness / 4);



		//Middle line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length ,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);


		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		break;
	}

	case '4':
	{
		//left most vertical line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y  }, { OriginCoord.X,OriginCoord.Y + Length/2 }, Pixel_Color, Thickness / 4);

		//Middle line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length ,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);

		//Right most vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X + Length,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		break;
	}

	case '5':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//left most vertical line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y }, { OriginCoord.X,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);

		//Right most vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y+Length/2 }, { OriginCoord.X + Length,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		//Middle line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length ,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);


		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		break;
	}

	case '6':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		//Middle line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length ,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);


		//Right most vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		break;
	}

	case '7':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//Rightmostt vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X + Length,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		break;
	}

	case '8':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//left most vertical line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length + 2 }, Pixel_Color, Thickness / 4);

		//Middle line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length ,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);


		//Right most vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y  }, { OriginCoord.X + Length,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		break;
	}

	case '9':
	{
		//upper most line
		pDrawLine(OriginCoord, { OriginCoord.X + Length,OriginCoord.Y }, Pixel_Color, Thickness / 4);

		//Left most line
		pDrawLine(OriginCoord, { OriginCoord.X ,OriginCoord.Y + Length/2 }, Pixel_Color, Thickness / 4);


		//Middle line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length / 2 }, { OriginCoord.X + Length ,OriginCoord.Y + Length / 2 }, Pixel_Color, Thickness / 4);


		//Right most vertical line
		pDrawLine({ OriginCoord.X + Length,OriginCoord.Y }, { OriginCoord.X + Length,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);


		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + Length }, { OriginCoord.X + Length ,OriginCoord.Y + Length }, Pixel_Color, Thickness / 4);

		break;
	}

	case '=':
	{
		//upper most line
		pDrawLine({ OriginCoord.X,OriginCoord.Y+(Length/4) }, { OriginCoord.X + Length,OriginCoord.Y + (Length / 4) }, Pixel_Color, Thickness / 4);

		//bottom line
		pDrawLine({ OriginCoord.X ,OriginCoord.Y + (Length *3) / 4 }, { OriginCoord.X + Length ,OriginCoord.Y + (Length * 3) / 4 }, Pixel_Color, Thickness / 4);

		break;
	}

	case '.':
	{
		//Draw solid rectangle
		pDrawSolidRectangle({ OriginCoord.X + (Length / 4),OriginCoord.Y + (Length * 3) / 4 }, { OriginCoord.X + (Length * 3) / 4,OriginCoord.Y + (Length) }, Pixel_Color);

		break;
	}

	case ':':
	{
		//Draw Upper solid rectangle
		pDrawSolidRectangle({ OriginCoord.X + (Length / 4),OriginCoord.Y + (Length ) / 4 }, { OriginCoord.X + (Length * 5) /12,OriginCoord.Y + (Length/2) }, Pixel_Color);

		//Draw Lower solid rectangle
		pDrawSolidRectangle({ OriginCoord.X + (Length / 4),OriginCoord.Y + (Length * 3) / 4 }, { OriginCoord.X + (Length * 5) /12,OriginCoord.Y + (Length) }, Pixel_Color);

		break;
	}
	default:
		break;
	}


}







//----------------- ALL DRAWING  FUNCTIONS  IMPLEMENTATIONS ------------------------------------//

void PIXEL_ENGINE::pDrawLine(const Generic_Vector<short>& InitialCoord, const Generic_Vector<short>& FinalCoord, const short& Pixel_Color , short Thickness )
{
	/*
	LineDirection : It stores angle in which give line is rotated (i.e slope of line)
	CurrPosition  :  It stores the current position of ciScreen pointer while drawing the complete line
	ThickPos       :  It stores the position perpendicular to LineDirection to increase the thickness 
	*/

	Vector2D LineDirection(InitialCoord.X, InitialCoord.Y, FinalCoord.X, FinalCoord.Y);
	Position CurrPosition(InitialCoord.X, InitialCoord.Y);
	Position ThickPos(CurrPosition.iX, CurrPosition.iY);


	/*
	PreX and PreY  : They stores the previous position acquried by CurrPosition variable
	LineMag          : It stroes the magnitude of line drawn uptill now which is always lower than LineDirection Magnitude 
	*/

	float PreX = 0.0f, PreY = 0.0f;
	float LineMag = 0.0f;

	LineDirection.DegreesTo_Radians();


	//Checks for validity of thickness
	if (Thickness < 0)Thickness = 0;


	while (LineMag <= LineDirection.GetMagnitude())
	{
		if ((CurrPosition.iX == FinalCoord.X) && (CurrPosition.iY == FinalCoord.Y))break;

		PreX = CurrPosition.fX;
		PreY = CurrPosition.fY;

		ThickPos = CurrPosition;


		//Draws the pixel on the screen if it's position is inside ScreenWidth And ScreenHeight
		if (CurrPosition.iX >= 0 && CurrPosition.iX < sScreenWidth && CurrPosition.iY >= 0 && CurrPosition.iY < sScreenHeight)
		{
			ciScreen[CurrPosition.iX + sScreenWidth * CurrPosition.iY].Attributes = Pixel_Color;
			ciScreen[CurrPosition.iX + sScreenWidth * CurrPosition.iY].Char.UnicodeChar = L' ';
		}




		//UpperThckness-- It loops foe each Position acquired by CurrPosition Variable and incerase the thickness of line by drawing a single point perpendicular to currposition
		for (int i = 0;i < Thickness;i++)
		{
			ThickPos.fX += cosf(LineDirection.GetDirection() + 1.5712f);
			ThickPos.fY += sinf(LineDirection.GetDirection() + 1.5712f);

			ThickPos.iX = ThickPos.fX;
			ThickPos.iY = ThickPos.fY;
			
			
			//Draws the pixel on the screen if it's position is inside ScreenWidth And ScreenHeight
			if (ThickPos.iX >= 0 && ThickPos.iX < sScreenWidth && ThickPos.iY >= 0 && ThickPos.iY < sScreenHeight)
			{
				ciScreen[ThickPos.iX + ThickPos.iY * sScreenWidth].Attributes = Pixel_Color;
				ciScreen[ThickPos.iX + ThickPos.iY * sScreenWidth].Char.UnicodeChar = L' ';
			}
		}



		//Resets the ThickPos variable values to CurrPOsition to draw lower thickness
		ThickPos = CurrPosition;



		//Lower Thickness-- It loops foe each Position acquired by CurrPosition Variable and incerase the thickness of line by drawing a single point perpendicular to currposition
     	for (int i = 0;i < Thickness;i++)
		{
			ThickPos.fX += cosf(LineDirection.GetDirection() - 1.5712f);
			ThickPos.fY += sinf(LineDirection.GetDirection() - 1.5712f);

			ThickPos.iX = ThickPos.fX;
			ThickPos.iY = ThickPos.fY;

			//Draws the pixel on the screen if it's position is inside ScreenWidth And ScreenHeight
			if (ThickPos.iX >= 0 && ThickPos.iX < sScreenWidth && ThickPos.iY >= 0 && ThickPos.iY < sScreenHeight)
			{
				ciScreen[ThickPos.iX + ThickPos.iY * sScreenWidth].Attributes = Pixel_Color;
				ciScreen[ThickPos.iX + ThickPos.iY * sScreenWidth].Char.UnicodeChar = L' ';
			}
		}



		//Updates the currposition variable in the direction of LineDirection Direction 
		CurrPosition.fX += cosf(LineDirection.GetDirection());
		CurrPosition.fY += sinf(LineDirection.GetDirection());

		//Updates magnitude of line uptill drawn by currPosition variable
		LineMag += sqrtf(((CurrPosition.fX - PreX) * (CurrPosition.fX - PreX)) + ((CurrPosition.fY - PreY) * (CurrPosition.fY - PreY)));


		CurrPosition.iX = CurrPosition.fX;
		CurrPosition.iY = CurrPosition.fY;
	}

}


void PIXEL_ENGINE::pDrawRectangle(const Generic_Vector<short>& LeftxTopy, const Generic_Vector<short>& RightxBottomy, const short& Pixel_Color,const short Thickness)
{

	//Checks whether Bottom right is less than Top left if so returns nothing
	if (RightxBottomy.X < LeftxTopy.X || RightxBottomy.Y < LeftxTopy.Y)
		return;
	else
	{
		short RectWidth = RightxBottomy.X - LeftxTopy.X;
		short RectHeight = RightxBottomy.Y - LeftxTopy.Y;


		
		//Adjust the width and height
		RectWidth -= 1;
		RectHeight -= 1;

		
		//Upper Horizontal 
		pDrawLine(LeftxTopy, { LeftxTopy.X + RectWidth,LeftxTopy.Y }, Pixel_Color,Thickness);


		//Left Vertical 
		pDrawLine( LeftxTopy, { LeftxTopy.X ,LeftxTopy.Y+RectHeight }, Pixel_Color, Thickness);


		//Lower Horizontal
		pDrawLine({ LeftxTopy.X,LeftxTopy.Y+RectHeight }, RightxBottomy, Pixel_Color, Thickness);


		//Right Vertical
		pDrawLine({ LeftxTopy.X+RectWidth,LeftxTopy.Y }, RightxBottomy, Pixel_Color, Thickness);
	}
}


void PIXEL_ENGINE::pDrawSolidRectangle(const Generic_Vector<short>& LeftxTopy, const Generic_Vector<short>& RightxBottomy, const short& Pixel_Color )
{
	//First draws outer rectangle
	pDrawRectangle(LeftxTopy, RightxBottomy, Pixel_Color);

	//checks for valid rectangle co-ordinates
	if (LeftxTopy.X < RightxBottomy.X && LeftxTopy.Y < RightxBottomy.Y)
	{

		short Width = RightxBottomy.X - LeftxTopy.X;
		short Height = RightxBottomy.Y - LeftxTopy.Y;

		Width -= 1;
		Height -= 1;

		//iterate through single pixel which is inside the outer rectangle 
		for (int x = 0;x < Width;x++)
		{
			for (int y = 0;y < Height;y++)
			{
				if ((LeftxTopy.X + x) >= 0 && (LeftxTopy.Y >= 0) && (RightxBottomy.X < sScreenWidth) && (RightxBottomy.Y < sScreenHeight))
				{
					//if inside the screen then it colours the PIXEL
					ciScreen[(LeftxTopy.X + x) + sScreenWidth * (LeftxTopy.Y + y)].Attributes = Pixel_Color;
					ciScreen[(LeftxTopy.X + x) + sScreenWidth * (LeftxTopy.Y + y)].Char.UnicodeChar = L' ';
				}
			}
		}
	}

}


void PIXEL_ENGINE::pDrawCircle(const Generic_Vector<short>& OriginCoord, short Radius, const short& Pixel_Color, short Thickness)
{
	/*
	RadiusHand  :  It gives us the Direction from Origin to (x,y) which is on the circumference of circle
	                         It is then further rotated full 360 degrees to draw circle

    CurrPosition  :  It Stores the current position on the circumference of circle while drawing circle
	*/

	Vector2D RadiusHand(OriginCoord.X, OriginCoord.Y, OriginCoord.X + Radius, OriginCoord.Y);
	Position CurrPosition;


	//Checks for validity of thickness
	if (Thickness < 0)Thickness = 0;


	//converts
	RadiusHand.DegreesTo_Radians();

	while (Thickness >= 0)
	{
		for (int i = 0;i < 360;i++)
		{
			

				if (i == 0 || i == 90 || i == 180 || i == 270)
				{//To avoid additional length of radius so it is subtracted at 0,90,180,270 degrees
					Radius -= 1;
					CurrPosition.fX = Radius * cosf(RadiusHand.GetDirection() + (i * DegreesToRadians));
					CurrPosition.fY = Radius * sinf(RadiusHand.GetDirection() + (i * DegreesToRadians));
					Radius += 1;    //Radius is restored after usage
				}
				else
				{//on other places originl radius is used
					CurrPosition.fX = Radius * cosf(RadiusHand.GetDirection() + (i * DegreesToRadians));
					CurrPosition.fY = Radius * sinf(RadiusHand.GetDirection() + (i * DegreesToRadians));
				}

				CurrPosition.iX = CurrPosition.fX;
				CurrPosition.iY = CurrPosition.fY;

				//circle is drawn if it is inside the screen
				if ((OriginCoord.X + CurrPosition.iX) >= 0 && (OriginCoord.Y + CurrPosition.iY) >= 0 && (OriginCoord.X + CurrPosition.iX) < sScreenWidth && (OriginCoord.Y + CurrPosition.iY) < sScreenHeight)
				{
					ciScreen[(OriginCoord.X + CurrPosition.iX) + ((OriginCoord.Y + CurrPosition.iY) * sScreenWidth)].Attributes = Pixel_Color;
					ciScreen[(OriginCoord.X + CurrPosition.iX) + ((OriginCoord.Y + CurrPosition.iY) * sScreenWidth)].Char.UnicodeChar = L' ';
				}

			
		}
		Thickness -= 1;
		Radius -= 1;
	}
}


void PIXEL_ENGINE::pDrawSolidCircle(const Generic_Vector<short>& OriginCoord, short Radius, const short& Pixel_Color )
{
	while (Radius >= 0)
	{
		//It simply draws outer radius and then gradually  decreases the radius to create layers as circle making it solid
		pDrawCircle(OriginCoord, Radius, Pixel_Color);
		Radius -= 1;
	}
}


//Please note that for drawing arc :  coordinate system is opposite to original system
void PIXEL_ENGINE::pDrawArc(const Generic_Vector<short>& OriginCoord, short Radius, const short& StartingAngleDegree, const short& EndingAngleDegree, const short& Pixel_Color , short Thickness )
{
	/*
	StartAngle  : It Stores the direction from which to start drawing arc.  It also restrict angle between 0 to 360 degress
	EndAngle  : It Stores the direction from which to End drawing arc.  It also restrict angle between 0 to 360 degress
	CurPos     : It Stores current position of pixel on which circumference of arc is drawn currently
	*/

	Vector2D StartAngle(Radius * cosf(StartingAngleDegree * DegreesToRadians), Radius * sinf(StartingAngleDegree * DegreesToRadians));
	Vector2D EndAngle(Radius * cosf(EndingAngleDegree * DegreesToRadians), Radius * sinf(EndingAngleDegree * DegreesToRadians));
	Position CurPos;


	//Checks for validity of thickness
	if (Thickness < 0)Thickness = 0;


	StartAngle.RadiansTo_Degree();
	EndAngle.RadiansTo_Degree();


	float fArcAngle ;
	short sArcAngle;
	short sEndAngle;


	while (Thickness >= 0)
	{
		fArcAngle = StartAngle.GetDirection();
		sArcAngle = fArcAngle;
		sEndAngle = EndAngle.GetDirection();

		while (sArcAngle != sEndAngle)
		{
			//Resets the angle which is greater than 360 degrees to 0 deg
			if (fArcAngle >= 360.0f)fArcAngle = 0.0f;

			//converts float to short from while loop
			sArcAngle = fArcAngle;

			//finds Current position where to draw Arc's next point
			CurPos.fX = Radius * cosf(fArcAngle * DegreesToRadians);
			CurPos.fY = Radius * sinf(fArcAngle * DegreesToRadians);

			//converts  integer for drawing on the screen below
			CurPos.iX = CurPos.fX;
			CurPos.iY = CurPos.fY;

			//Prints on the screen if withen the boundaries
			if ((OriginCoord.X + CurPos.iX) >= 0 && (OriginCoord.X + CurPos.iX) < sScreenWidth && (OriginCoord.Y + CurPos.iY) >= 0 && (OriginCoord.Y + CurPos.iY) < sScreenHeight)
			{
				ciScreen[(OriginCoord.X + CurPos.iX) + (OriginCoord.Y + CurPos.iY) * sScreenWidth].Attributes = Pixel_Color;
				ciScreen[(OriginCoord.X + CurPos.iX) + (OriginCoord.Y + CurPos.iY) * sScreenWidth].Char.UnicodeChar = L' ';
			}

			//counter to sacquire all the angles value between startangle and endangle to draw the arc
			fArcAngle += 1.0f;
		}
		if (Radius > 0)
			Radius -= 1;
		Thickness -= 1;

	}
}


//Please note that for drawing sector :  coordinate system is opposite to original system
void PIXEL_ENGINE::pDrawSector(const Generic_Vector<short>& OriginCoord, short Radius, const short& StartingAngleDegree, const short& EndingAngleDegree, const short& Pixel_Color)
{

	while (Radius >= 0)
	{
		pDrawArc(OriginCoord, Radius, StartingAngleDegree, EndingAngleDegree, Pixel_Color);
		Radius -= 1;
	}
}

 
void PIXEL_ENGINE::pDrawText(const std::string& Text, const Generic_Vector<short>& OriginCoord,const short WidthOfText=1000, const short HeightOfText = 1000, const short& IndiviualLength=1, const short& Pixel_Color, short Thickness)
{
	short Gap = 0;


	//Sets Proper Thickness
	if (Thickness < 0)Thickness = 0;

	//defines gap value according to thickness
	while (Thickness>=0)
	{
		Gap += 1;
		Thickness -= 1;
	}


	// CURPOS will supply TopLeft coord to drawCharacter function to draw character and it is updated in for loop 
	Generic_Vector<short> CurPos = OriginCoord;


	for (int i = 0;i < Text.size();i++)
	{//Checks whether it is inside the screen
		if ((CurPos.X+IndiviualLength >= 0) && (CurPos.Y + IndiviualLength >= 0))
		{//checks whether it has come at the width's end if so it sets new X and y coord of CurPos i.e on next line
			if (CurPos.X + IndiviualLength > WidthOfText && CurPos.Y + IndiviualLength < HeightOfText)
			{
				//Set new CurPos Position

				CurPos.X = OriginCoord.X;
				CurPos.Y = OriginCoord.Y + IndiviualLength + Gap;

				pDrawCharacter(Text[i], CurPos, IndiviualLength, Pixel_Color, Gap-1);

			}
			else if (CurPos.X + IndiviualLength < WidthOfText && CurPos.Y + IndiviualLength < HeightOfText)
			{
				//Draw at regular position

				pDrawCharacter(Text[i], CurPos, IndiviualLength, Pixel_Color, Gap-1);
			}
		}

		CurPos.X += IndiviualLength + Gap;
	}
}


void PIXEL_ENGINE::pDrawGrass1(const Generic_Vector<short>& OriginCoord, const short& Length, const short& Pixel_Color, short Thickness)
{
	//First draws the arc i.e side arc 
	pDrawArc({ OriginCoord.X,OriginCoord.Y + Length }, Length/2, 270, 0, Pixel_Color, Thickness*5);
	pDrawArc({ OriginCoord.X + Length ,OriginCoord.Y + Length }, Length/2,180, 270, Pixel_Color,Thickness*5);

	//for random number generated offset is added 
	const short Offset = Length / 2;

	//radius i.e it stroes random number plus offset
	short Radius = 0;

	//to stored coord generated by andom number
	Generic_Vector<short> FinalCoord;


	//if thickness is more then between angle is more differed  
	int Differby = Thickness * 2;

	//iterate from starting angle to ending angle 
	for (int i = 240;i <= 300;i+=Differby)
	{
		Radius = (rand() % Length / 2) + Offset;

		FinalCoord.X = Radius * cosf(i * DegreesToRadians) + OriginCoord.X + Length / 2;
		FinalCoord.Y = Radius * sinf(i * DegreesToRadians) + OriginCoord.Y + Length;
	
		pDrawLine({ OriginCoord.X + Length / 2,OriginCoord.Y + Length },FinalCoord, Pixel_Color, Thickness/2);
	}

}


void PIXEL_ENGINE::pDrawTree1(const Generic_Vector<short>& OriginCoord, const short& Length, const short& Pixel_Color_Trunk, const short& Pixel_Color_Leafs)
{
	//Block Width and Height

	//X = Length;
	//Y = (3 * Length) / 2;

	//Thickness of Trunk
	const short Thickness = Length / 6;


	//Draw the Trunk
	pDrawLine({ OriginCoord.X + Length / 2,OriginCoord.Y + (3 * Length) / 2 }, { OriginCoord.X + Length / 2,OriginCoord.Y + Length / 2 }, Pixel_Color_Trunk, Thickness);


	//Draw Leafs
	float Radius = 0;
	const short Differby = 30;
	//CANCEL  -  - >//idea is to iterate from starting angle to final angle while changing radius 

	//Fix pattern
	
	//Leftmost leaf
	pDrawSolidCircle({ OriginCoord.X + Length / 6,OriginCoord.Y + Length/2 }, Length / 2, Pixel_Color_Leafs);

	//Middle most leaf
	pDrawSolidCircle({ OriginCoord.X + Length / 2,OriginCoord.Y + Length / 6 }, Length / 2, Pixel_Color_Leafs);

	//Right most
	pDrawSolidCircle({ OriginCoord.X + (Length * 7) / 8,OriginCoord.Y + Length/2 }, Length / 2, Pixel_Color_Leafs);

}


void PIXEL_ENGINE::pDrawCloud1(const Generic_Vector<short>& OriginCoord, const short& Length, const short& Pixel_Color)
{

	//Draws base of the cloud
	pDrawLine({ OriginCoord.X,OriginCoord.Y + Length }, { OriginCoord.X + Length,OriginCoord.Y + Length }, Pixel_Color, Length / 6);


	//Fix Pattern
	
	//Left most 
	pDrawSolidCircle({ OriginCoord.X + Length,OriginCoord.Y + (Length*4 ) / 7 },( Length*3)/5, Pixel_Color);

	//Midle
	pDrawSolidCircle({ OriginCoord.X + Length/2,OriginCoord.Y + (Length * 2) / 4 }, Length / 2, Pixel_Color);

	//Right most
	pDrawSolidCircle({ OriginCoord.X ,OriginCoord.Y + (Length*6)/7 }, Length / 3, Pixel_Color);

}


void PIXEL_ENGINE::pDrawCharacterNo1(const Generic_Vector<short>& OriginCoord, const short& Length, const bool& WithGun=0, const short& Pixel_HairColor = 0x45, const short& Pixel_BodyColor = 0x7d, const short& Pixel_GunColor1 = 0xcc, const short& Pixel_GunColor2 = 0x00)
{

	//Draws Body

	//1--Draws Hair 
	pDrawSolidRectangle(OriginCoord, { OriginCoord.X + (Length * 3) / 4 , OriginCoord.Y + (Length * 3) / 4 }, Pixel_HairColor);

	//2--Draws Head -- Color White
	pDrawSolidCircle({ OriginCoord.X + (Length * 3) / 6,OriginCoord.Y + Length / 2 }, Length / 3, Pixel_BodyColor);

	//3--Draws Remaining body  --  Color White
	pDrawSolidRectangle({ OriginCoord.X + (Length*3) / 7,OriginCoord.Y + Length/2 }, { OriginCoord.X + (Length * 3) / 5,OriginCoord.Y + (2 * Length) }, Pixel_BodyColor);

	//4--Draws Foot  --  Color Grey
	pDrawSolidRectangle({ OriginCoord.X + (Length * 3) / 7,OriginCoord.Y +( Length*17)/9  }, { OriginCoord.X + (Length * 3) / 4,OriginCoord.Y + (2 * Length) }, 0x86);

	//5--Draws Eyes  --  Color Blue
	pDrawSolidCircle({ OriginCoord.X + (Length * 5) / 7,OriginCoord.Y + (Length*8)/ 18 }, (Length / 12)>0 ? (Length / 12) : 4, 0x11);


	//----------------------------------------------------------------------------------------

	if (WithGun)
	{//Draws Gun

	//1--Base metal  --  Color Given by User
		pDrawSolidRectangle({ OriginCoord.X + (Length * 3) / 6,OriginCoord.Y + Length }, { OriginCoord.X + Length - 5,OriginCoord.Y + (Length * 6) / 5 }, Pixel_GunColor1);

		//2--Handle
		pDrawSolidRectangle({ OriginCoord.X + (Length * 3) / 6,OriginCoord.Y + (Length)+(Length / 8) }, { OriginCoord.X + (Length / 2) + (Length * 2) / 12,OriginCoord.Y + (Length)+(Length / 3) }, Pixel_GunColor2);

		//3--Layer1
		pDrawSolidRectangle({ OriginCoord.X + (Length * 6) / 10,OriginCoord.Y + Length - 4 }, { OriginCoord.X + (Length / 2) + (Length * 2) / 8,OriginCoord.Y + (Length * 6) / 5 }, 0x44);


		//4--Layer2
		pDrawSolidRectangle({ OriginCoord.X + (Length * 6) / 8,OriginCoord.Y + Length - 2 }, { OriginCoord.X + (Length / 2) + (Length * 2) / 6,OriginCoord.Y + (Length * 6) / 5 }, 0x99);


		//5--Sidemost opening
		pDrawSector({ OriginCoord.X + Length - 5,OriginCoord.Y + Length + (Length / 12) }, (Length / 8) > 0 ? (Length / 8) : 4, 270, 90, 0xbb);


		//6--SomeDecoration --  On player side
		pDrawSolidRectangle({ OriginCoord.X + (Length * 3) / 6,OriginCoord.Y + Length }, { OriginCoord.X + (Length / 2),OriginCoord.Y + (Length)+(Length / 12) }, 0x31);


	}
}


void PIXEL_ENGINE::pDrawCharacterNo2(const Generic_Vector<short>& OriginCoord, const short& Length, const bool& WithGun=0, const short& Pixel_BodyColor = 0x00, const short& Pixel_GunColor1 = 0x99, const short& Pixel_GunColor2 = 0xff)
{
	//Draws Body

	//1--Draws Head -- Color White
	pDrawSolidCircle({ OriginCoord.X + (Length * 3) / 6,OriginCoord.Y + Length / 2 }, Length / 3, Pixel_BodyColor);

	//2--Draws Remaining body  --  Color White
	pDrawSolidRectangle({ OriginCoord.X + (Length * 3) / 7,OriginCoord.Y + Length / 2 }, { OriginCoord.X + (Length * 3) / 5,OriginCoord.Y + (2 * Length) }, Pixel_BodyColor);

	//3--Draws Foot  --  Color Grey
	pDrawSolidRectangle({ OriginCoord.X + (Length * 3) / 7,OriginCoord.Y + (Length * 17) / 9 }, { OriginCoord.X + (Length * 3) / 4,OriginCoord.Y + (2 * Length) }, 0x86);

	//4--Draws Eyes  --  Color Blue
	pDrawSolidCircle({ OriginCoord.X + (Length * 5) / 7,OriginCoord.Y + (Length * 8) / 18 }, (Length / 12) > 0 ? (Length / 12) : 4, 0x55);


	//Draws Guns  --  If With Gun is true
	if (WithGun)
	{

	//1--Draws Base metal  --  Color -- Gun color

		//1--Base metal  --  Color Given by User
		pDrawSolidRectangle({ OriginCoord.X + (Length * 3) / 6,OriginCoord.Y + Length }, { OriginCoord.X + Length - 5,OriginCoord.Y + (Length * 6) / 5 }, Pixel_GunColor1);

		//2--Handle
		pDrawSolidRectangle({ OriginCoord.X + (Length * 3) / 6,OriginCoord.Y + (Length)+(Length / 8) }, { OriginCoord.X + (Length / 2) + (Length * 2) / 12,OriginCoord.Y + (Length)+(Length / 3) }, Pixel_GunColor2);

		//3--Layer1
		pDrawSolidRectangle({ OriginCoord.X + (Length * 6) / 10,OriginCoord.Y + Length - 3 }, { OriginCoord.X + (Length / 2) + (Length * 2) / 10,OriginCoord.Y + (Length * 6) / 5 }, 0xba);

		//4--Layer2
		pDrawSolidRectangle({ OriginCoord.X + (Length * 6) / 8,OriginCoord.Y + Length - 2 }, { OriginCoord.X + (Length / 2) + (Length * 2) / 6,OriginCoord.Y + (Length * 6) / 5 }, 0x66);

		//5--SomeDecoration -- on the player side
		pDrawSolidRectangle({ OriginCoord.X + (Length * 3) / 6,OriginCoord.Y + Length }, { OriginCoord.X + (Length / 2),OriginCoord.Y + (Length)+(Length / 12) }, 0xff);

		//6 -- Sidemost pointing design
		pDrawLine({ OriginCoord.X + Length - 5,OriginCoord.Y + (Length * 6) / 5 }, { OriginCoord.X + Length,OriginCoord.Y + (Length * 6) / 5 }, 0xff, Length / 25);
		pDrawLine({ OriginCoord.X + Length - 5,OriginCoord.Y + Length }, { OriginCoord.X + Length,OriginCoord.Y + Length }, 0xff, Length / 25);
	}
}


short PIXEL_ENGINE::pBuild_Screen(Screen_Layout& Screen)
{
	//Draws Main Screen 
	if (!Screen.bScreen_Transperency)
		pDrawSolidRectangle(Screen.gvsScreen_Coordinates, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width,Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height }, Screen.sScreen_Color);


	if (Screen.sText_Width < Screen.sScreen_Width && Screen.sText_Height < Screen.sScreen_Height)
		pDrawText(Screen.stText_ToDisplay, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX,Screen.gvsScreen_Coordinates.Y + Screen.sText_OffsetY }, Screen.sText_Width, Screen.sText_Height, Screen.sText_FontSize, Screen.sText_Color, 2);


	if (!Screen.bButtonAlignH)//Alignment Vertically
	{
		switch (Screen.sTotal_Buttons)
		{
		case 1:
		{

			//Draws Button
			pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);



			//Draws Selected 
			if (Screen.sButton_Selected == 1)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);
			}


			//Draws Border to the Button
			pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height },Screen.sButton_BorderColor);


			//Draws Text on Button 
			pDrawText(Screen.Button1_Name, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4+2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY+2 }, Screen.sButton_Width*100, Screen.sButton_Height*100, Screen.sButton_TextFontSize,Screen.sButton_TextColor, Screen.sButton_TextFontDepth);



			if (GetAsyncKeyState(VK_DOWN))
			{
				if (Screen.sButton_Selected == 0)
					Screen.sButton_Selected = 1;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (Screen.sButton_Selected > 0 && Screen.sButton_Selected < 2)
					return Screen.sButton_Selected;
			}

			break;
		}

		case 2:
		{
			//Draws 1st Button
			if (Screen.sButton_Selected != 1)
				if (Screen.gvsScreen_Coordinates.X + Screen.sButton_Width < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);


			//Draws 2nd Button
			if (Screen.sButton_Selected != 2)
				if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height + Screen.sButton_OffsetBetButton }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY * 2) + (Screen.sButton_Height * 2) }, Screen.sButton_Color);


			//Draws Selected Button
			if (Screen.sButton_Selected == 1)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);

			}
			else if (Screen.sButton_Selected == 2)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height + Screen.sButton_OffsetBetButton }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY * 2) + (Screen.sButton_Height * 2) }, Screen.sButton_SelectColor);

			}


			//Draws Border to the Button

			//Button 1
			if (Screen.gvsScreen_Coordinates.X + Screen.sButton_Width < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
				pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_BorderColor);

			//Button 2
			if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
				pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height + Screen.sButton_OffsetBetButton }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY * 2) + (Screen.sButton_Height * 2) }, Screen.sButton_BorderColor);


			//Draws Text on Button

			//Button 1
			pDrawText(Screen.Button1_Name, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + 2 }, Screen.sButton_Width * 50, Screen.sButton_Height * 50,Screen.sButton_TextFontSize,Screen.sButton_TextColor,Screen.sButton_TextFontDepth);
			//Button 2
			pDrawText(Screen.Button2_Name, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height + Screen.sButton_OffsetBetButton +2 }, Screen.sButton_Width * 50, Screen.sButton_Height * 50, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);



			if (GetAsyncKeyState(VK_UP))
			{
				if (Screen.sButton_Selected > 1)
					Screen.sButton_Selected--;
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				if (Screen.sButton_Selected < 2)
					Screen.sButton_Selected++;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (Screen.sButton_Selected > 0 && Screen.sButton_Selected < 3)
					return Screen.sButton_Selected;
			}

			break;
		}

		case 3:
		{
			//Draws 1st Button
			if (Screen.sButton_Selected != 1)
				if (Screen.gvsScreen_Coordinates.X + Screen.sButton_Width < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);


			//Draws 2nd Button
			if (Screen.sButton_Selected != 2)
				if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height + Screen.sButton_OffsetBetButton }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY * 2) + (Screen.sButton_Height * 2) }, Screen.sButton_Color);


			//Draws 3nd Button 
			if(Screen.sButton_Selected!=3)
				if((Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height * 3) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height))
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + (Screen.sButton_Height + Screen.sButton_OffsetBetButton) * 2 }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY * 3) + (Screen.sButton_Height * 3) }, Screen.sButton_Color);

			//Draws Selected Button
			if (Screen.sButton_Selected == 1)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);

			}
			else if (Screen.sButton_Selected == 2)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height + Screen.sButton_OffsetBetButton }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY * 2) + (Screen.sButton_Height * 2) }, Screen.sButton_SelectColor);

			}
			else if (Screen.sButton_Selected == 3)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + (Screen.sButton_Height + Screen.sButton_OffsetBetButton) * 2 }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY * 3) + (Screen.sButton_Height * 3) }, Screen.sButton_SelectColor);

			}

			//Draws Border to the Button

			//Button 1
			if (Screen.gvsScreen_Coordinates.X + Screen.sButton_Width < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
				pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_BorderColor);

			//Button 2
			if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
				pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height + Screen.sButton_OffsetBetButton }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY * 2) + (Screen.sButton_Height * 2) }, Screen.sButton_BorderColor);

			//Button 3
			if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
				pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + (Screen.sButton_Height + Screen.sButton_OffsetBetButton) * 2 }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY * 3) + (Screen.sButton_Height * 3) }, Screen.sButton_BorderColor);


			//Draws Text on Button

			//Button 1
			pDrawText(Screen.Button1_Name, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);
			//Button 2
			pDrawText(Screen.Button2_Name, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height + Screen.sButton_OffsetBetButton + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);
			//Button 3
			pDrawText(Screen.Button3_Name, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + (Screen.sButton_Height + Screen.sButton_OffsetBetButton)*2 + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);



			if (GetAsyncKeyState(VK_UP))
			{
				if (Screen.sButton_Selected > 1)
					Screen.sButton_Selected--;
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				if (Screen.sButton_Selected < 3)
					Screen.sButton_Selected++;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (Screen.sButton_Selected > 0 && Screen.sButton_Selected < 4)
					return Screen.sButton_Selected;
			}



			break;
		}

		default:
		{
			//Draws Button
			pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);



			//Draws Selected 
			if (Screen.sButton_Selected == 1)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);
			}


			//Draws Border to the Button
			pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_BorderColor);


			//Draws Text on Button 
			pDrawText(Screen.Button1_Name, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);



			if (GetAsyncKeyState(VK_DOWN))
			{
				if (Screen.sButton_Selected == 0)
					Screen.sButton_Selected = 1;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (Screen.sButton_Selected > 0 && Screen.sButton_Selected < 2)
					return Screen.sButton_Selected;
			}



			break;
		}
		}


	}
	else          //Alignment Horzontally
	{
		switch (Screen.sTotal_Buttons)
		{
		case 1:
		{

			//Draws Button
			pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);



			//Draws Selected 
			if (Screen.sButton_Selected == 1)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);
			}


			//Draws Border to the Button
			pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_BorderColor);


			//Draws Text on Button 
			pDrawText(Screen.Button1_Name, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);



			if (GetAsyncKeyState(VK_RIGHT))
			{
				if (Screen.sButton_Selected == 0)
					Screen.sButton_Selected = 1;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (Screen.sButton_Selected > 0 && Screen.sButton_Selected < 2)
					return Screen.sButton_Selected;
			}



			break;
		}

		case 2:
		{
			//Draws 1st Button
			if (Screen.sButton_Selected != 1)
				if (Screen.gvsScreen_Coordinates.X + Screen.sButton_Width < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);


			//Draws 2nd Button
			if (Screen.sButton_Selected != 2)
				if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height  < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX+Screen.sButton_Width+Screen.sButton_OffsetBetButton,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY  }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton+Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height +Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);


			//Draws Selected Button
			if (Screen.sButton_Selected == 1)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);

			}
			else if (Screen.sButton_Selected == 2)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);

			}


			//Draws Border to the Button

			//Button 1
			if (Screen.gvsScreen_Coordinates.X + Screen.sButton_Width < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
				pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_BorderColor);

			//Button 2
			if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height ) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
				pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_BorderColor);


			//Draws Text on Button

			//Button 1
			pDrawText(Screen.Button1_Name, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);
			//Button 2
			pDrawText(Screen.Button2_Name, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + 2 +Screen.sButton_Width + Screen.sButton_OffsetBetButton ,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);



			if (GetAsyncKeyState(VK_LEFT))
			{
				if (Screen.sButton_Selected > 1)
					Screen.sButton_Selected--;
			}
			else if (GetAsyncKeyState(VK_RIGHT))
			{
				if (Screen.sButton_Selected < 2)
					Screen.sButton_Selected++;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (Screen.sButton_Selected > 0 && Screen.sButton_Selected < 3)
					return Screen.sButton_Selected;
			}

			break;
		}

		case 3:
		{
			
				//Draws 1st Button
				if (Screen.sButton_Selected != 1)
					if (Screen.gvsScreen_Coordinates.X + Screen.sButton_Width < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
						pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);


				//Draws 2nd Button
				if (Screen.sButton_Selected != 2)
					if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
						pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);

				//Draws 3nd Button 
				if (Screen.sButton_Selected != 3)
					if ((Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width*3) + (Screen.sButton_OffsetBetButton*2) < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height))
						pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX+ (Screen.sButton_Width*2) + (Screen.sButton_OffsetBetButton*2),Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY  }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + (Screen.sButton_Width * 2) + (Screen.sButton_OffsetBetButton * 2)+Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY ) + (Screen.sButton_Height ) }, Screen.sButton_Color);


				//Draws Selected Button
				if (Screen.sButton_Selected == 1)
				{
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);

				}
				else if (Screen.sButton_Selected == 2)
				{
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);

				}
				else if (Screen.sButton_Selected == 3)
				{
					pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + (Screen.sButton_Width * 2) + (Screen.sButton_OffsetBetButton * 2),Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + (Screen.sButton_Width * 2) + (Screen.sButton_OffsetBetButton * 2) + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY) + (Screen.sButton_Height) }, Screen.sButton_SelectColor);

				}


				//Draws Border to the Button

				//Button 1
				if (Screen.gvsScreen_Coordinates.X + Screen.sButton_Width < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + Screen.sButton_Height < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
					pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_BorderColor);

				//Button 2
				if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
					pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + Screen.sButton_Width + Screen.sButton_OffsetBetButton + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_BorderColor);

				//Button 3
				if (Screen.gvsScreen_Coordinates.X + (Screen.sButton_Width * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width && Screen.gvsScreen_Coordinates.Y + (Screen.sButton_Height * 2) + Screen.sButton_OffsetBetButton < Screen.gvsScreen_Coordinates.Y + Screen.sScreen_Height)
					pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + (Screen.sButton_Width * 2) + (Screen.sButton_OffsetBetButton * 2),Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + (Screen.sButton_Width * 2) + (Screen.sButton_OffsetBetButton * 2) + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + (Screen.sText_OffsetY) + (Screen.sButton_Height) }, Screen.sButton_BorderColor);


				//Draws Text on Button

				//Button 1
				pDrawText(Screen.Button1_Name, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);
				//Button 2
				pDrawText(Screen.Button2_Name, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + 2 + Screen.sButton_Width + Screen.sButton_OffsetBetButton ,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);
				//Button 3
				pDrawText(Screen.Button3_Name, { Screen.gvsScreen_Coordinates.X + Screen.sText_OffsetX + (Screen.sButton_Width * 2) + (Screen.sButton_OffsetBetButton * 2)+2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY +2}, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);



					if (GetAsyncKeyState(VK_LEFT) )
					{

						if (Screen.sButton_Selected > 1)
							Screen.sButton_Selected--;

						
					}
					else if (GetAsyncKeyState(VK_RIGHT) )
					{


						if (Screen.sButton_Selected < 3)
							Screen.sButton_Selected++;

						
					}
						
		
					if (GetAsyncKeyState(VK_SPACE))
					{
						if (Screen.sButton_Selected > 0 && Screen.sButton_Selected < 4)
							return Screen.sButton_Selected;
						
					}
			

			break;
		}

		default:
		{

			//Draws Button
			pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_Color);



			//Draws Selected 
			if (Screen.sButton_Selected == 1)
			{
				pDrawSolidRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_SelectColor);
			}


			//Draws Border to the Button
			pDrawRectangle({ Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY }, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + Screen.sButton_Width,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + Screen.sButton_Height }, Screen.sButton_BorderColor);


			//Draws Text on Button 
			pDrawText(Screen.Button1_Name, { Screen.gvsScreen_Coordinates.X + Screen.sScreen_Width / 4 + 2,Screen.gvsScreen_Coordinates.Y + Screen.sText_Height + Screen.sText_OffsetY + 2 }, Screen.sButton_Width * 100, Screen.sButton_Height * 100, Screen.sButton_TextFontSize, Screen.sButton_TextColor, Screen.sButton_TextFontDepth);



			if (GetAsyncKeyState(VK_RIGHT))
			{
				if (Screen.sButton_Selected == 0)
					Screen.sButton_Selected = 1;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (Screen.sButton_Selected > 0 && Screen.sButton_Selected < 2)
					return Screen.sButton_Selected;
			}



			break;
		}
		}



	}


	return 0;
}


void PIXEL_ENGINE::pDrawLeveledGround(const Generic_Vector<short>& OriginCoord, const short& Length, const short& Height, const short& Pixel_Color_Upper, const short& Pixel_Color_Lower, short Thickness)
{


	//Upper line 
	pDrawLine({ OriginCoord.X,OriginCoord.Y + Height / 4 }, { OriginCoord.X + Length,OriginCoord.Y + Height / 4 }, Pixel_Color_Upper, Thickness/2);

	//Lower line 
	pDrawLine({ OriginCoord.X,OriginCoord.Y + (Height *3) / 4 }, { OriginCoord.X + Length,OriginCoord.Y + (Height * 3) / 4 }, Pixel_Color_Lower, Thickness/2);

}










