#include "DataForm.h"
#include <stdlib.h>
#include <math.h>
#include <string>

int flag;
double x[10];
double y[10];
double f[10];
double eps[10];
double E;
double emax;
double s1;
double s2;
double s3;
double s4;
double s5, s6, s7, s8, s9, s10, s11, s12, s13;
double d;
double da0;
double da1, da3;
double da2, da4;
double a0;
double a1, a3;
double a2, a4;

SpecialMath1::DataForm::DataForm(int _flag)
{
	InitializeComponent();	
	flag = _flag;
	if (flag == 5)
	{
		label3->Text = "b = ";
		label4->Text = "a = ";
		label6->Text = "k = ";
	}
	else
	{
		label3->Text = "a0 = ";
		label4->Text = "a1 = ";
	}	
	dataGrid->Columns->Clear();
	dataGrid->ColumnCount = 11;
	dataGrid->RowCount = 7;
	dataGrid->Rows[0]->Cells[0]->Value = "x";
	dataGrid->Rows[1]->Cells[0]->Value = "y";
	if (flag == 1)
	{
		dataGrid->Rows[2]->Cells[0]->Value = "f=a1*x+a0";
		dataGrid->Rows[3]->Cells[0]->Value = "eps";
	}
	if (flag == 2)
	{
		dataGrid->Rows[2]->Cells[0]->Value = "f2=a2*x*x+a1*x+a0";
		dataGrid->Rows[3]->Cells[0]->Value = "eps2";
	}
	if (flag == 3)
	{
		dataGrid->Rows[2]->Cells[0]->Value = "f3=a3*x*x*x+a2*x*x+a1*x+a0";
		dataGrid->Rows[3]->Cells[0]->Value = "eps3";
	}
	if (flag == 4)
	{
		dataGrid->Rows[2]->Cells[0]->Value = "f4=a4*x*x*x*x+a3*x*x*x+a2*x*x+a1*x+a0";
		dataGrid->Rows[3]->Cells[0]->Value = "eps4";
	}
	if (flag == 5)
	{
		dataGrid->Rows[2]->Cells[0]->Value = "f5=a*e^(k*x)+b";
		dataGrid->Rows[3]->Cells[0]->Value = "eps5";
	}
	if (flag == 6)
	{
		dataGrid->Rows[2]->Cells[0]->Value = "f6=a*ln(x+1)+b";
		dataGrid->Rows[3]->Cells[0]->Value = "eps6";
	}
	double dx[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	double dy[10] = { 7.7, 9.3, 11.6, 13.4, 16.0, 17.8, 19.9, 21.6, 22.7, 24.1 };
	UpdateGrid(dx, dy);
	ResetVariables();
}

System::Void SpecialMath1::DataForm::Hidebutton_Click(System::Object^ sender, System::EventArgs^ e)
{
	Close();
}

System::Void SpecialMath1::DataForm::Cbutton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (flag == 1)
		DoLineAppr();
	if (flag == 2)
		DoSqAppr();
	if (flag == 3)
		DoCoubAppr();
	if (flag == 4)
		DoFourStAppr();
	if (flag == 5)
		DoExpAppr();
 	if (flag == 6)
		DoLgAppr();
}

double SpecialMath1::DataForm::GetOpred2x2(double a11, double a12, double a21, double a22)
{
	return a11 * a22 - a12 * a21;
}

double SpecialMath1::DataForm::GetOpred3x3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
{
	return a11 * GetOpred2x2(a22, a23, a32, a33) - a21 * 
		GetOpred2x2(a12, a13, a32, a33) + a31 * GetOpred2x2(a12, a13, a22, a23);
}

double SpecialMath1::DataForm::GetOpred4x4(double a11, double a12, double a13, double a14, double a21, double a22, double a23, double a24, double a31, double a32, double a33, double a34, double a41, double a42, double a43, double a44)
{
	return a11 * GetOpred3x3(a22, a23, a24, a32, a33, a34, a42, a43, a44) - a12 * GetOpred3x3(a21, a23, a24, a31, a33, a34, a41, a43, a44) + a13 * GetOpred3x3(a21, a22, a24, a31, a32, a34, a41, a42, a44) - a14 * GetOpred3x3(a21, a22, a23, a31, a32, a33, a41, a42, a43);
}

double SpecialMath1::DataForm::Getopred5x5(double a11, double a12, double a13, double a14, double a15, double a21, double a22, double a23, double a24, double a25, double a31, double a32, double a33, double a34, double a35, double a41, double a42, double a43, double a44, double a45, double a51, double a52, double a53, double a54, double a55)
{
	return a11 * GetOpred4x4(a22, a23, a24, a25, a32, a33, a34, a35, a42, a43, a44, a45, a52, a53, a54, a55) - a12 * GetOpred4x4(a21, a23, a24, a25, a31, a33, a34, a35, a41, a43, a44, a45, a51, a53, a54, a55) + a13 * GetOpred4x4(a21, a22, a24, a25, a31, a32, a34, a35, a41, a42, a44, a45, a51, a52, a54, a55) - a14 * GetOpred4x4(a21, a22, a23, a25, a31, a32, a33, a35, a41, a42, a43, a45, a51, a52, a53, a55) + a15 * GetOpred4x4(a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44, a51, a52, a53, a54);
}

void SpecialMath1::DataForm::UpdateGrid(double x[10], double y[10])
{
	for (int i = 0; i <= 9; i++)
	{
		dataGrid->Rows[0]->Cells[i + 1]->Value = x[i].ToString();
		dataGrid->Rows[1]->Cells[i + 1]->Value = y[i].ToString();
	}
}

void SpecialMath1::DataForm::ResetVariables()
{
	x[10] = { 0 };
	y[10] = { 0 };
	f[10] = { 0 };
	eps[10] = { 0 };
	E = 0;
	emax = 0;
	s1 = 0;
	s2 = 0;
	s3 = 0;
	s4 = 0;
	s5 = 0;
	s6 = 0;
	s7 = 0;
	s8 = 0;
	s9 = 0;
	s10 = 0;
	s11 = 0;
	s12 = 0;
	s13 = 0;
	d = 0;
	da0 = 0;
	da1 = 0;
	da2 = 0;
	da4 = 0;
	da3 = 0;
	a0 = 0;
	a1 = 0;
	a2 = 0;
	a3 = 0;
	a4 = 0;
}

void SpecialMath1::DataForm::DoLineAppr()
{
	ResetVariables();
	for (int i = 0; i <= 9; i++)
	{
		x[i] = Convert::ToDouble(dataGrid->Rows[0]->Cells[i + 1]->Value);
		y[i] = Convert::ToDouble(dataGrid->Rows[1]->Cells[i + 1]->Value);
		s1 += x[i];
		s2 += x[i] * x[i];
		s3 += y[i];
		s4 += x[i] * y[i];
	}

	d = GetOpred2x2(s2, s1, s1, 10);
	da0 = GetOpred2x2(s2, s4, s1, s3);
	da1 = GetOpred2x2(s4, s1, s3, 10);
	a0 = da0 / d;
	a1 = da1 / d;

	for (int i = 0; i <= 9; i++)
	{
		f[i] = a1 * x[i] + a0;
		eps[i] = f[i] - y[i];
		E += eps[i] * eps[i];
		if (Math::Abs(eps[i]) > emax)
			emax = Math::Abs(eps[i]);
	}

	for (int i = 0; i <= 9; i++)
	{
		dataGrid->Rows[2]->Cells[i + 1]->Value = f[i].ToString();
		dataGrid->Rows[3]->Cells[i + 1]->Value = eps[i].ToString();
	}

	textBox1->Text = E.ToString();
	textBox2->Text = emax.ToString();
	textBox3->Text = a0.ToString();
	textBox4->Text = a1.ToString();
}

void SpecialMath1::DataForm::DoSqAppr()
{
	ResetVariables();
	for (int i = 0; i < 10; i++)
	{
		x[i] = Convert::ToDouble(dataGrid->Rows[0]->Cells[i + 1]->Value);
		y[i] = Convert::ToDouble(dataGrid->Rows[1]->Cells[i + 1]->Value);
		s1 += x[i];
		s2 += x[i] * x[i];
		s3 += x[i] * x[i] * x[i];
		s4 += x[i] * x[i] * x[i] * x[i];
		s5 += y[i];
		s6 += x[i] * y[i];
		s7 += x[i] * x[i] * y[i];
	}

	d = GetOpred3x3(10, s1, s2, s1, s2, s3, s2, s3, s4);
	da0 = GetOpred3x3(s5, s1, s2, s6, s2, s3, s7, s3, s4);
	da1 = GetOpred3x3(10, s5, s2, s1, s6, s3, s2, s7, s4);
	da2 = GetOpred3x3(10, s1, s5, s1, s2, s6, s2, s3, s7);

	a0 = da0 / d;
	a1 = da1 / d;
	a2 = da2 / d;
	for (int i = 0; i < 10; i++)
	{
		f[i] = a2 * x[i] * x[i] + a1 * x[i] + a0;
		eps[i] = f[i] - y[i];
		E += eps[i] * eps[i];
		if (Math::Abs(eps[i]) > emax)
			emax = Math::Abs(eps[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		dataGrid->Rows[2]->Cells[i + 1]->Value = f[i].ToString();
		dataGrid->Rows[3]->Cells[i + 1]->Value = eps[i].ToString();
	}

	textBox1->Text = E.ToString();
	textBox2->Text = emax.ToString();
	textBox3->Text = a0.ToString();
	textBox4->Text = a1.ToString();
	textBox5->Text = a2.ToString();	
}

void SpecialMath1::DataForm::DoCoubAppr()
{
	ResetVariables();
	for (int i = 0; i < 10; i++)
	{
		x[i] = Convert::ToDouble(dataGrid->Rows[0]->Cells[i + 1]->Value);
		y[i] = Convert::ToDouble(dataGrid->Rows[1]->Cells[i + 1]->Value);
		s1 += x[i];
		s2 += x[i] * x[i];
		s3 += x[i] * x[i] * x[i];
		s4 += x[i] * x[i] * x[i] * x[i];
		s5 += x[i] * x[i] * x[i] * x[i] * x[i];
		s6 += x[i] * x[i] * x[i] * x[i] * x[i] * x[i];
		s7 += y[i];
		s8 += x[i] * y[i];
		s9 += x[i] * x[i] * y[i];
		s10 += x[i] * x[i] * x[i] * y[i];
	}
	d = GetOpred4x4(10, s1, s2, s3, s1, s2, s3, s4, s2, s3, s4, s5, s3, s4, s5, s6);
	da0 = GetOpred4x4(s7, s1, s2, s3, s8, s2, s3, s4, s9, s3, s4, s5, s10, s4, s5, s6);
	da1 = GetOpred4x4(10, s7, s2, s3, s1, s8, s3, s4, s2, s9, s4, s5, s3, s10, s5, s6);
	da2 = GetOpred4x4(10, s1, s7, s3, s1, s2, s8, s4, s2, s3, s9, s5, s3, s4, s10, s6);
	da3 = GetOpred4x4(10, s1, s2, s7, s1, s2, s3, s8, s2, s3, s4, s9, s3, s4, s5, s10);
	a0 = da0 / d;
	a1 = da1 / d;
	a2 = da2 / d;
	a3 = da3 / d;

	for (int i = 0; i < 10; i++)
	{
		f[i] = a3 * x[i] * x[i] * x[i] + a2 * x[i] * x[i] + a1 * x[i] + a0;
		eps[i] = f[i] - y[i];
		E += eps[i] * eps[i];
		if (Math::Abs(eps[i]) > emax)
			emax = Math::Abs(eps[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		dataGrid->Rows[2]->Cells[i + 1]->Value = f[i].ToString();
		dataGrid->Rows[3]->Cells[i + 1]->Value = eps[i].ToString();
	}
	textBox1->Text = E.ToString();
	textBox2->Text = emax.ToString();
	textBox3->Text = a0.ToString();
	textBox4->Text = a1.ToString();
	textBox5->Text = a2.ToString();
	textBox7->Text = a3.ToString();

}

void SpecialMath1::DataForm::DoFourStAppr()
{
	ResetVariables();
	for (int i = 0; i < 10; i++)
	{
		x[i] = Convert::ToDouble(dataGrid->Rows[0]->Cells[i + 1]->Value);
		y[i] = Convert::ToDouble(dataGrid->Rows[1]->Cells[i + 1]->Value);
		s1 += x[i];
		s2 += x[i] * x[i];
		s3 += x[i] * x[i] * x[i];
		s4 += x[i] * x[i] * x[i] * x[i];
		s5 += x[i] * x[i] * x[i] * x[i] * x[i];
		s6 += x[i] * x[i] * x[i] * x[i] * x[i] * x[i];
		s7 += x[i] * x[i] * x[i] * x[i] * x[i] * x[i] * x[i];
		s8 += x[i] * x[i] * x[i] * x[i] * x[i] * x[i] * x[i] * x[i];
		s9 += y[i];
		s10 += x[i] * y[i];
		s11 += x[i] * x[i] * y[i];
		s12 += x[i] * x[i] * x[i] * y[i];
		s13 += x[i] * x[i] * x[i] * x[i] * y[i];
	}
	d = Getopred5x5(10, s1, s2, s3, s4, s1, s2, s3, s4, s5, s2, s3, s4, s5, s6, s3, s4, s5, s6, s7, s4, s5, s6, s7, s8);
	da0 = Getopred5x5(s9, s1, s2, s3, s4, s10, s2, s3, s4, s5, s11, s3, s4, s5, s6, s12, s4, s5, s6, s7, s13, s5, s6, s7, s8);
	da1 = Getopred5x5(10, s9, s2, s3, s4, s1, s10, s3, s4, s5, s2, s11, s4, s5, s6, s3, s12, s5, s6, s7, s4, s13, s6, s7, s8);
	da2 = Getopred5x5(10, s1, s9, s3, s4, s1, s2, s10, s4, s5, s2, s3, s11, s5, s6, s3, s4, s12, s6, s7, s4, s5, s13, s7, s8);
	da3 = Getopred5x5(10, s1, s2, s9, s4, s1, s2, s3, s10, s5, s2, s3, s4, s11, s6, s3, s4, s5, s12, s7, s4, s5, s6, s13, s8);
	da4 = Getopred5x5(10, s1, s2, s3, s9, s1, s2, s3, s4, s10, s2, s3, s4, s5, s11, s3, s4, s5, s6, s12, s4, s5, s6, s7, s13);
	a0 = da0 / d;
	a1 = da1 / d;
	a2 = da2 / d;
	a3 = da3 / d;
	a4 = da4 / d;
	for (int i = 0; i < 10; i++)
	{
		f[i] = a4 * x[i] * x[i] * x[i] * x[i] + a3 * x[i] * x[i] * x[i] + a2 * x[i] * x[i] + a1 * x[i] + a0;
		eps[i] = f[i] - y[i];
		E += eps[i] * eps[i];
		if (Math::Abs(eps[i]) > emax)
			emax = Math::Abs(eps[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		dataGrid->Rows[2]->Cells[i + 1]->Value = f[i].ToString();
		dataGrid->Rows[3]->Cells[i + 1]->Value = eps[i].ToString();
	}
	textBox1->Text = E.ToString();
	textBox2->Text = emax.ToString();
	textBox3->Text = a0.ToString();
	textBox4->Text = a1.ToString();
	textBox5->Text = a2.ToString();
	textBox7->Text = a3.ToString();
	textBox6->Text = a4.ToString();

}

void SpecialMath1::DataForm::DoExpAppr()
{
	double MinE = 0;	
	for (double k = 0.00001; k <= 1.0; k += 0.00001)
	{
		ResetVariables();
		for (int i = 0; i <= 9; i++)
		{
			x[i] = Convert::ToDouble(dataGrid->Rows[0]->Cells[i + 1]->Value);
			y[i] = Convert::ToDouble(dataGrid->Rows[1]->Cells[i + 1]->Value);
			s1 += Math::Exp(2 * k * x[i]);
			s2 += Math::Exp(k * x[i]);
			s3 += Math::Exp(k * x[i]) * y[i];
			s4 += y[i];
		}

		d = GetOpred2x2(s1, s2, s2, 10);
		da0 = GetOpred2x2(s3, s2, s4, 10);
		da1 = GetOpred2x2(s1, s3, s2, s4);
		a0 = da0 / d;
		a1 = da1 / d;

		for (int i = 0; i <= 9; i++)
		{
			f[i] = a0 * Math::Exp(k * x[i]) + a1;
			eps[i] = f[i] - y[i];
			E += eps[i] * eps[i];
			if (Math::Abs(eps[i]) > emax)
				emax = Math::Abs(eps[i]);
		}
		MinE = (k == 0.00001) ? E : MinE;
		if (E > MinE) continue;			
		MinE = E;
		textBox1->Text = E.ToString();
		textBox2->Text = emax.ToString();
		textBox3->Text = a0.ToString();
		textBox4->Text = a1.ToString();
		textBox5->Text = k.ToString();
		for (int i = 0; i <= 9; i++)
		{
			dataGrid->Rows[2]->Cells[i + 1]->Value = f[i].ToString();
			dataGrid->Rows[3]->Cells[i + 1]->Value = eps[i].ToString();
		}
	}

}

void SpecialMath1::DataForm::DoLgAppr()
{
	ResetVariables();
	for (int i = 0; i <= 9; i++)
	{
		x[i] = Convert::ToDouble(dataGrid->Rows[0]->Cells[i + 1]->Value);
		y[i] = Convert::ToDouble(dataGrid->Rows[1]->Cells[i + 1]->Value);
		s1 += Math::Log(x[i] * 10) * y[i];
		s2 += Math::Log(x[i] * 10);
		s3 += y[i];
		s4 += Math::Pow(Math::Log(x[i] * 10), 2);
	}

	a0 = (10 * s1 - s2 * s3) / (10 * s4 - s2 * s2);
	a1 = (s4 * s3 - s2 * s1) / (10 * s4 - s2 * s2);


	for (int i = 0; i <= 9; i++)
	{
		f[i] = a0 * Math::Log(x[i] * 10 + 1.0) + a1;
		eps[i] = f[i] - y[i];
		E += eps[i] * eps[i];
		if (Math::Abs(eps[i]) > emax)
			emax = Math::Abs(eps[i]);
	}

	for (int i = 0; i <= 9; i++)
	{
		dataGrid->Rows[2]->Cells[i + 1]->Value = f[i].ToString();
		dataGrid->Rows[3]->Cells[i + 1]->Value = eps[i].ToString();
	}

	textBox1->Text = E.ToString();
	textBox2->Text = emax.ToString();
	textBox3->Text = a0.ToString();
	textBox4->Text = a1.ToString();
}

