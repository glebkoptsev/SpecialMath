#include "MainForm.h"
#include "DataForm.h"
#include <stdlib.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace std;


[STAThread]
void main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	SpecialMath1::MainForm form;
	Application::Run(% form);
}

System::Void SpecialMath1::MainForm::CloseButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	auto result = MessageBox::Show(
		"Вы действительно хотите выйти из программы?",
		"Подтвердите выход",
		MessageBoxButtons::YesNo,
		MessageBoxIcon::Question);
	if (result == System::Windows::Forms::DialogResult::Yes) 
		Application::Exit();
}

System::Void SpecialMath1::MainForm::ApprButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	int flag = 0;
	if (sender == LineApprButton)
		flag = 1;
	if (sender == KvApprButton)
		flag = 2;
	if (sender == CoubApprButton)
		flag = 3;
	if (sender == FourStButton)
		flag = 4;
	if (sender == ExpApprButton)
		flag = 5;
	if (sender == LgApprButton)
		flag = 6;
	DataForm^ df = gcnew DataForm(flag);
	df->ShowDialog();
	delete df;
}

