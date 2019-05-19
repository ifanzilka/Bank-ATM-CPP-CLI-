#pragma once
#include"Client.h"

namespace WindowsForms {

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


		void Connect()
		{
			
			try
			{
				c = gcnew Client(IpAddress->Text);
				c->OnEnterResult += gcnew LoginHandler(this, &MainForm::LoginResponse);//привязываем событие классу MainForm
				c->OnMessageReceived += gcnew MessageHandler(this, &MainForm::MessageReceived);//событие
				connected = true;
				BtnEnter->Enabled = true;
				IpAddress->Enabled = false;
				Btn->Enabled = false;
			}
			catch (Exception^ex) {
				
				tbChat->Text += ex->Message + "\r\n";//если не вошли то в чат выводим ощибку
				c = nullptr;
			}
		}

		MainForm(void)
		{
			InitializeComponent();
			BtnEnter->Enabled = false;
			btnBalanc->Enabled = false;
			btnRemove->Enabled = false;
			btnInsert->Enabled = false;
			textBox1->Enabled = false;
			textBox2->Enabled = false;
			btnTransfer->Enabled = false;
			textBox3->Enabled = false;
			textBox4->Enabled = false;
			
			
			

				

		
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
	private: System::Windows::Forms::Button^  Btn;
	public: System::Windows::Forms::TextBox^  IpAddress;
	private:
	protected:

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txNumberCard;

	private: System::Windows::Forms::TextBox^  txPin;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  BtnEnter;
	private: System::Windows::Forms::TextBox^  tbChat;
	private: System::Windows::Forms::Button^  BtnBalance;
	private: System::Windows::Forms::Button^  btnBalanc;
	private: System::Windows::Forms::Button^  btnRemove;
	private: System::Windows::Forms::Button^  btnInsert;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  btnTransfer;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label7;

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
			this->tbChat = (gcnew System::Windows::Forms::TextBox());
			this->Btn = (gcnew System::Windows::Forms::Button());
			this->IpAddress = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txNumberCard = (gcnew System::Windows::Forms::TextBox());
			this->txPin = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->BtnEnter = (gcnew System::Windows::Forms::Button());
			this->btnBalanc = (gcnew System::Windows::Forms::Button());
			this->btnRemove = (gcnew System::Windows::Forms::Button());
			this->btnInsert = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->btnTransfer = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// tbChat
			// 
			this->tbChat->Cursor = System::Windows::Forms::Cursors::No;
			this->tbChat->Location = System::Drawing::Point(13, 42);
			this->tbChat->MaxLength = 32767000;
			this->tbChat->Multiline = true;
			this->tbChat->Name = L"tbChat";
			this->tbChat->ReadOnly = true;
			this->tbChat->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->tbChat->Size = System::Drawing::Size(583, 190);
			this->tbChat->TabIndex = 8;
			// 
			// Btn
			// 
			this->Btn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Btn->Location = System::Drawing::Point(466, 400);
			this->Btn->Name = L"Btn";
			this->Btn->Size = System::Drawing::Size(130, 36);
			this->Btn->TabIndex = 0;
			this->Btn->Text = L"Подключиться";
			this->Btn->UseVisualStyleBackColor = true;
			this->Btn->Click += gcnew System::EventHandler(this, &MainForm::Btn_Click);
			// 
			// IpAddress
			// 
			this->IpAddress->Location = System::Drawing::Point(128, 407);
			this->IpAddress->Name = L"IpAddress";
			this->IpAddress->Size = System::Drawing::Size(332, 22);
			this->IpAddress->TabIndex = 1;
			this->IpAddress->Text = L"127.0.0.1";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 407);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(110, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Адрес сервера:";
			// 
			// txNumberCard
			// 
			this->txNumberCard->Location = System::Drawing::Point(128, 445);
			this->txNumberCard->Name = L"txNumberCard";
			this->txNumberCard->Size = System::Drawing::Size(262, 22);
			this->txNumberCard->TabIndex = 3;
			// 
			// txPin
			// 
			this->txPin->Location = System::Drawing::Point(128, 484);
			this->txPin->MaxLength = 4;
			this->txPin->Name = L"txPin";
			this->txPin->PasswordChar = '*';
			this->txPin->Size = System::Drawing::Size(100, 22);
			this->txPin->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 448);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(99, 17);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Номер карты:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(15, 488);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(65, 17);
			this->label3->TabIndex = 6;
			this->label3->Text = L"PinCode:";
			// 
			// BtnEnter
			// 
			this->BtnEnter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->BtnEnter->Location = System::Drawing::Point(466, 476);
			this->BtnEnter->Name = L"BtnEnter";
			this->BtnEnter->Size = System::Drawing::Size(130, 60);
			this->BtnEnter->TabIndex = 7;
			this->BtnEnter->Text = L"Войти";
			this->BtnEnter->UseVisualStyleBackColor = true;
			this->BtnEnter->Click += gcnew System::EventHandler(this, &MainForm::BtnEnter_Click);
			// 
			// btnBalanc
			// 
			this->btnBalanc->Location = System::Drawing::Point(13, 252);
			this->btnBalanc->Name = L"btnBalanc";
			this->btnBalanc->Size = System::Drawing::Size(174, 83);
			this->btnBalanc->TabIndex = 9;
			this->btnBalanc->Text = L"Проверить Баланс";
			this->btnBalanc->UseVisualStyleBackColor = true;
			this->btnBalanc->Click += gcnew System::EventHandler(this, &MainForm::btnBalanc_Click);
			// 
			// btnRemove
			// 
			this->btnRemove->Location = System::Drawing::Point(279, 252);
			this->btnRemove->Name = L"btnRemove";
			this->btnRemove->Size = System::Drawing::Size(138, 39);
			this->btnRemove->TabIndex = 10;
			this->btnRemove->Text = L"Cнять";
			this->btnRemove->UseVisualStyleBackColor = true;
			this->btnRemove->Click += gcnew System::EventHandler(this, &MainForm::btnRemove_Click);
			// 
			// btnInsert
			// 
			this->btnInsert->Location = System::Drawing::Point(279, 296);
			this->btnInsert->Name = L"btnInsert";
			this->btnInsert->Size = System::Drawing::Size(138, 39);
			this->btnInsert->TabIndex = 11;
			this->btnInsert->Text = L"Внести";
			this->btnInsert->UseVisualStyleBackColor = true;
			this->btnInsert->Click += gcnew System::EventHandler(this, &MainForm::btnInsert_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(423, 260);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 22);
			this->textBox1->TabIndex = 12;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(423, 305);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 13;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(530, 264);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(37, 17);
			this->label4->TabIndex = 14;
			this->label4->Text = L"RUB";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(530, 305);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(37, 17);
			this->label5->TabIndex = 15;
			this->label5->Text = L"RUB";
			// 
			// btnTransfer
			// 
			this->btnTransfer->Location = System::Drawing::Point(13, 355);
			this->btnTransfer->Name = L"btnTransfer";
			this->btnTransfer->Size = System::Drawing::Size(119, 29);
			this->btnTransfer->TabIndex = 16;
			this->btnTransfer->Text = L"Перевести";
			this->btnTransfer->UseVisualStyleBackColor = true;
			this->btnTransfer->Click += gcnew System::EventHandler(this, &MainForm::btnTransfer_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(148, 361);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(69, 17);
			this->label6->TabIndex = 17;
			this->label6->Text = L"на карту:";
			this->label6->Click += gcnew System::EventHandler(this, &MainForm::label6_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(220, 361);
			this->textBox3->MaxLength = 20;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(153, 22);
			this->textBox3->TabIndex = 18;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(409, 360);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 22);
			this->textBox4->TabIndex = 19;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(533, 361);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(37, 17);
			this->label7->TabIndex = 20;
			this->label7->Text = L"RUB";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(608, 548);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->btnTransfer);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->btnInsert);
			this->Controls->Add(this->btnRemove);
			this->Controls->Add(this->btnBalanc);
			this->Controls->Add(this->tbChat);
			this->Controls->Add(this->BtnEnter);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->txPin);
			this->Controls->Add(this->txNumberCard);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->IpAddress);
			this->Controls->Add(this->Btn);
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximumSize = System::Drawing::Size(626, 680);
			this->MinimumSize = System::Drawing::Size(626, 580);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MainForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		void MessageReceived( String^ data)
		{
			if (InvokeRequired)
			{
				Invoke(
					gcnew MessageHandler(this, &MainForm::MessageReceived),					
					data
				);
			}
			else {
				tbChat->Text += data + "\r\n";
				tbChat->SelectionStart = tbChat->TextLength;
				tbChat->ScrollToCaret();
			}
		}
		void LoginResponse(bool result)
		{
			if (InvokeRequired)//так как элемент создан в другом потоке то создам и еще раз вызываем
			{
				Invoke(
					gcnew LoginHandler(this, &MainForm::LoginResponse),
					result
				);
			}
			else {
				if (result)
				{	
					txNumberCard->Enabled = false;
					txPin->Enabled = false;
					BtnEnter->Enabled = false;
					tbChat->Text = "Вы успешно вошли!"+"\r\n";
					tbChat->SelectionStart = tbChat->TextLength;
					btnBalanc->Enabled = true;
					btnRemove->Enabled = true;
					btnInsert->Enabled = true;
					textBox1->Enabled = true;
					textBox2->Enabled = true;



					btnTransfer->Enabled = true;
					textBox3->Enabled = true;
					textBox4->Enabled = true;

					//btnSend->Text = "Отправить";
					enters = true;
				}
				else
				{
					tbChat->Text += "Неверный номер карты или пин" + "\r\n";
					tbChat->SelectionStart = tbChat->TextLength;
				}
			}
		}
		void BtnGeneration()
		{
			//btnBalance
			
			this->Controls->Add(this->BtnBalance);
			this->BtnBalance = (gcnew System::Windows::Forms::Button());
			this->BtnBalance->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->BtnBalance->Location = System::Drawing::Point(12, 226);
			this->BtnBalance->Name = L"BtnBalnce";
			this->BtnBalance->Size = System::Drawing::Size(130, 50);
			this->BtnBalance->TabIndex = 10;
			this->BtnBalance->Text = L"Проверить баланс";
			this->BtnBalance->UseVisualStyleBackColor = true;
			this->BtnBalance->Click += gcnew System::EventHandler(this, &MainForm::BtnEnter_Click);
			
		}
		

		Client^c;
		bool connected = false;
		bool enters = false;

	private: System::Void Btn_Click(System::Object^  sender, System::EventArgs^  e) {
		
		
	
		
		if(!connected)
		{
			Connect();


		}


	}
	private: System::Void BtnEnter_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!enters)
		{
			String^NumberCard = txNumberCard->Text;
			String^Pin = txPin->Text;
			c->Enters(NumberCard, Pin);
		}
		


	}
private: System::Void btnRemove_Click(System::Object^  sender, System::EventArgs^  e) {

	try
	{
		Convert::ToDouble(textBox1->Text);
		c->Remove(textBox1->Text);

	}
	catch (Exception^ex) 
	{

		tbChat->Text += ex->Message+"\r\n";
		tbChat->SelectionStart = tbChat->TextLength;

	}


}
private: System::Void btnInsert_Click(System::Object^  sender, System::EventArgs^  e) {
	try
	{
		Convert::ToDouble(textBox2->Text);
		c->Insert(textBox2->Text);

	}
	catch (Exception^ex)
	{

		tbChat->Text += ex->Message + "\r\n";

	}


}
private: System::Void btnBalanc_Click(System::Object^  sender, System::EventArgs^  e) {

	c->Balance();
	
}
private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {

	c->Stop();//обрываем подкючение

}
private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void btnTransfer_Click(System::Object^  sender, System::EventArgs^  e) {

	c->Transfer(textBox3->Text, textBox4->Text);

}
};
}
