#pragma once

namespace SpecialMath1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ CloseButton;
	private: System::Windows::Forms::Button^ LineApprButton;
	private: System::Windows::Forms::Button^ KvApprButton;
	private: System::Windows::Forms::Button^ CoubApprButton;
	private: System::Windows::Forms::Button^ FourStButton;
	private: System::Windows::Forms::Button^ ExpApprButton;
	private: System::Windows::Forms::Button^ LgApprButton;


	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->CloseButton = (gcnew System::Windows::Forms::Button());
			this->LineApprButton = (gcnew System::Windows::Forms::Button());
			this->KvApprButton = (gcnew System::Windows::Forms::Button());
			this->CoubApprButton = (gcnew System::Windows::Forms::Button());
			this->FourStButton = (gcnew System::Windows::Forms::Button());
			this->ExpApprButton = (gcnew System::Windows::Forms::Button());
			this->LgApprButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// CloseButton
			// 
			this->CloseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->CloseButton->Location = System::Drawing::Point(411, 295);
			this->CloseButton->Name = L"CloseButton";
			this->CloseButton->Size = System::Drawing::Size(75, 23);
			this->CloseButton->TabIndex = 0;
			this->CloseButton->Text = L"Выход";
			this->CloseButton->UseVisualStyleBackColor = true;
			this->CloseButton->Click += gcnew System::EventHandler(this, &MainForm::CloseButton_Click);
			// 
			// LineApprButton
			// 
			this->LineApprButton->Location = System::Drawing::Point(172, 5);
			this->LineApprButton->Name = L"LineApprButton";
			this->LineApprButton->Size = System::Drawing::Size(150, 32);
			this->LineApprButton->TabIndex = 1;
			this->LineApprButton->Text = L"Линейная";
			this->LineApprButton->UseVisualStyleBackColor = true;
			this->LineApprButton->Click += gcnew System::EventHandler(this, &MainForm::ApprButton_Click);
			// 
			// KvApprButton
			// 
			this->KvApprButton->Location = System::Drawing::Point(172, 53);
			this->KvApprButton->Name = L"KvApprButton";
			this->KvApprButton->Size = System::Drawing::Size(150, 32);
			this->KvApprButton->TabIndex = 1;
			this->KvApprButton->Text = L"Квадратичная";
			this->KvApprButton->UseVisualStyleBackColor = true;
			this->KvApprButton->Click += gcnew System::EventHandler(this, &MainForm::ApprButton_Click);
			// 
			// CoubApprButton
			// 
			this->CoubApprButton->Location = System::Drawing::Point(172, 102);
			this->CoubApprButton->Name = L"CoubApprButton";
			this->CoubApprButton->Size = System::Drawing::Size(150, 32);
			this->CoubApprButton->TabIndex = 1;
			this->CoubApprButton->Text = L"Кубическая";
			this->CoubApprButton->UseVisualStyleBackColor = true;
			this->CoubApprButton->Click += gcnew System::EventHandler(this, &MainForm::ApprButton_Click);
			// 
			// FourStButton
			// 
			this->FourStButton->Location = System::Drawing::Point(172, 153);
			this->FourStButton->Name = L"FourStButton";
			this->FourStButton->Size = System::Drawing::Size(150, 32);
			this->FourStButton->TabIndex = 1;
			this->FourStButton->Text = L"4-й степени";
			this->FourStButton->UseVisualStyleBackColor = true;
			this->FourStButton->Click += gcnew System::EventHandler(this, &MainForm::ApprButton_Click);
			// 
			// ExpApprButton
			// 
			this->ExpApprButton->Location = System::Drawing::Point(172, 202);
			this->ExpApprButton->Name = L"ExpApprButton";
			this->ExpApprButton->Size = System::Drawing::Size(150, 32);
			this->ExpApprButton->TabIndex = 2;
			this->ExpApprButton->Text = L"Экспоненциальная";
			this->ExpApprButton->UseVisualStyleBackColor = true;
			this->ExpApprButton->Click += gcnew System::EventHandler(this, &MainForm::ApprButton_Click);
			// 
			// LgApprButton
			// 
			this->LgApprButton->Location = System::Drawing::Point(172, 250);
			this->LgApprButton->Name = L"LgApprButton";
			this->LgApprButton->Size = System::Drawing::Size(150, 32);
			this->LgApprButton->TabIndex = 3;
			this->LgApprButton->Text = L"Логарифмическая";
			this->LgApprButton->UseVisualStyleBackColor = true;
			this->LgApprButton->Click += gcnew System::EventHandler(this, &MainForm::ApprButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(498, 330);
			this->Controls->Add(this->LgApprButton);
			this->Controls->Add(this->ExpApprButton);
			this->Controls->Add(this->FourStButton);
			this->Controls->Add(this->CoubApprButton);
			this->Controls->Add(this->KvApprButton);
			this->Controls->Add(this->LineApprButton);
			this->Controls->Add(this->CloseButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->Text = L"Аппроксимация";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void CloseButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ApprButton_Click(System::Object^ sender, System::EventArgs^ e);
};
}
