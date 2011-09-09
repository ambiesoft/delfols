#pragma once


namespace delfols {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^  lvMain;
	protected: 

	protected: 
	private: System::Windows::Forms::ColumnHeader^  chEntry;
	private: System::Windows::Forms::ColumnHeader^  chActualPass;
	private: System::Windows::Forms::ToolStrip^  toolMain;
	private: System::Windows::Forms::ToolStripButton^  tbAdd;
	private: System::Windows::Forms::ToolStripButton^  tbExecute;

	protected: 

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMain::typeid));
			this->lvMain = (gcnew System::Windows::Forms::ListView());
			this->chEntry = (gcnew System::Windows::Forms::ColumnHeader());
			this->chActualPass = (gcnew System::Windows::Forms::ColumnHeader());
			this->toolMain = (gcnew System::Windows::Forms::ToolStrip());
			this->tbAdd = (gcnew System::Windows::Forms::ToolStripButton());
			this->tbExecute = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolMain->SuspendLayout();
			this->SuspendLayout();
			// 
			// lvMain
			// 
			this->lvMain->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->chEntry, this->chActualPass});
			this->lvMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lvMain->Location = System::Drawing::Point(0, 25);
			this->lvMain->Name = L"lvMain";
			this->lvMain->Size = System::Drawing::Size(699, 393);
			this->lvMain->TabIndex = 0;
			this->lvMain->UseCompatibleStateImageBehavior = false;
			this->lvMain->View = System::Windows::Forms::View::Details;
			// 
			// chEntry
			// 
			this->chEntry->Text = L"Entry";
			this->chEntry->Width = 271;
			// 
			// chActualPass
			// 
			this->chActualPass->Text = L"Pass";
			this->chActualPass->Width = 320;
			// 
			// toolMain
			// 
			this->toolMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tbAdd, this->tbExecute});
			this->toolMain->Location = System::Drawing::Point(0, 0);
			this->toolMain->Name = L"toolMain";
			this->toolMain->Size = System::Drawing::Size(699, 25);
			this->toolMain->TabIndex = 1;
			this->toolMain->Text = L"toolStrip1";
			// 
			// tbAdd
			// 
			this->tbAdd->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tbAdd->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tbAdd.Image")));
			this->tbAdd->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tbAdd->Name = L"tbAdd";
			this->tbAdd->Size = System::Drawing::Size(23, 22);
			this->tbAdd->Text = L"Add";
			this->tbAdd->ToolTipText = L"Add New Entry";
			this->tbAdd->Click += gcnew System::EventHandler(this, &FormMain::tbAdd_Click);
			// 
			// tbExecute
			// 
			this->tbExecute->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tbExecute->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tbExecute.Image")));
			this->tbExecute->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tbExecute->Name = L"tbExecute";
			this->tbExecute->Size = System::Drawing::Size(23, 22);
			this->tbExecute->Text = L"Execute";
			this->tbExecute->Click += gcnew System::EventHandler(this, &FormMain::tbExecute_Click);
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(699, 418);
			this->Controls->Add(this->lvMain);
			this->Controls->Add(this->toolMain);
			this->Name = L"FormMain";
			this->Text = L"FormMain";
			this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
			this->toolMain->ResumeLayout(false);
			this->toolMain->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		void SetPath(array<String^>^ paths);
	private:
		System::Void tbAdd_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void tbExecute_Click(System::Object^  sender, System::EventArgs^  e);







};
















}

