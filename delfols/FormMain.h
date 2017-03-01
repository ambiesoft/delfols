#pragma once


namespace delfols {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::IO;

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
		FormMain(void);

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
	private: System::Windows::Forms::SplitContainer^  spRoot;
	private: System::Windows::Forms::ListView^  lvLog;
	private: System::Windows::Forms::ColumnHeader^  chNo;
	private: System::Windows::Forms::ColumnHeader^  chFile;
	private: System::Windows::Forms::ColumnHeader^  chResult;
	private: System::Windows::Forms::ToolStrip^  toolLog;
	private: System::Windows::Forms::ToolStripButton^  tbAll;



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
			this->spRoot = (gcnew System::Windows::Forms::SplitContainer());
			this->lvLog = (gcnew System::Windows::Forms::ListView());
			this->chNo = (gcnew System::Windows::Forms::ColumnHeader());
			this->chFile = (gcnew System::Windows::Forms::ColumnHeader());
			this->chResult = (gcnew System::Windows::Forms::ColumnHeader());
			this->toolLog = (gcnew System::Windows::Forms::ToolStrip());
			this->tbAll = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolMain->SuspendLayout();
			this->spRoot->Panel1->SuspendLayout();
			this->spRoot->Panel2->SuspendLayout();
			this->spRoot->SuspendLayout();
			this->toolLog->SuspendLayout();
			this->SuspendLayout();
			// 
			// lvMain
			// 
			this->lvMain->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->chEntry, this->chActualPass});
			this->lvMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lvMain->Location = System::Drawing::Point(0, 25);
			this->lvMain->Name = L"lvMain";
			this->lvMain->Size = System::Drawing::Size(699, 201);
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
			this->tbAdd->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tbAdd.Image")));
			this->tbAdd->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tbAdd->Name = L"tbAdd";
			this->tbAdd->Size = System::Drawing::Size(49, 22);
			this->tbAdd->Text = L"Add";
			this->tbAdd->ToolTipText = L"Add New Entry";
			this->tbAdd->Click += gcnew System::EventHandler(this, &FormMain::tbAdd_Click);
			// 
			// tbExecute
			// 
			this->tbExecute->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tbExecute.Image")));
			this->tbExecute->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tbExecute->Name = L"tbExecute";
			this->tbExecute->Size = System::Drawing::Size(73, 22);
			this->tbExecute->Text = L"Execute";
			this->tbExecute->Click += gcnew System::EventHandler(this, &FormMain::tbExecute_Click);
			// 
			// spRoot
			// 
			this->spRoot->Dock = System::Windows::Forms::DockStyle::Fill;
			this->spRoot->Location = System::Drawing::Point(0, 0);
			this->spRoot->Name = L"spRoot";
			this->spRoot->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// spRoot.Panel1
			// 
			this->spRoot->Panel1->Controls->Add(this->lvMain);
			this->spRoot->Panel1->Controls->Add(this->toolMain);
			// 
			// spRoot.Panel2
			// 
			this->spRoot->Panel2->Controls->Add(this->lvLog);
			this->spRoot->Panel2->Controls->Add(this->toolLog);
			this->spRoot->Size = System::Drawing::Size(699, 453);
			this->spRoot->SplitterDistance = 226;
			this->spRoot->TabIndex = 2;
			// 
			// lvLog
			// 
			this->lvLog->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->chNo, this->chFile, this->chResult});
			this->lvLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lvLog->Location = System::Drawing::Point(0, 25);
			this->lvLog->Name = L"lvLog";
			this->lvLog->Size = System::Drawing::Size(699, 198);
			this->lvLog->TabIndex = 0;
			this->lvLog->UseCompatibleStateImageBehavior = false;
			this->lvLog->View = System::Windows::Forms::View::Details;
			// 
			// chNo
			// 
			this->chNo->Text = L"No";
			// 
			// chFile
			// 
			this->chFile->Text = L"File";
			this->chFile->Width = 532;
			// 
			// chResult
			// 
			this->chResult->Text = L"Result";
			// 
			// toolLog
			// 
			this->toolLog->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tbAll});
			this->toolLog->Location = System::Drawing::Point(0, 0);
			this->toolLog->Name = L"toolLog";
			this->toolLog->Size = System::Drawing::Size(699, 25);
			this->toolLog->TabIndex = 1;
			this->toolLog->Text = L"toolStrip1";
			// 
			// tbAll
			// 
			this->tbAll->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tbAll->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tbAll.Image")));
			this->tbAll->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tbAll->Name = L"tbAll";
			this->tbAll->Size = System::Drawing::Size(23, 22);
			this->tbAll->Text = L"toolStripButton1";
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(699, 453);
			this->Controls->Add(this->spRoot);
			this->Name = L"FormMain";
			this->Text = L"delfols";
			this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
			this->toolMain->ResumeLayout(false);
			this->toolMain->PerformLayout();
			this->spRoot->Panel1->ResumeLayout(false);
			this->spRoot->Panel1->PerformLayout();
			this->spRoot->Panel2->ResumeLayout(false);
			this->spRoot->Panel2->PerformLayout();
			this->spRoot->ResumeLayout(false);
			this->toolLog->ResumeLayout(false);
			this->toolLog->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		void SetPath(array<String^>^ paths);
		void deleteAll(DirectoryInfo^ di);
		void theDeleteFile(String^ path);
		void theDeleteDir(String^ path);
		void addToLog(String^ filename, bool ok, String^ desc);
	private:
		System::Void tbAdd_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void tbExecute_Click(System::Object^  sender, System::EventArgs^  e);







};
















}

