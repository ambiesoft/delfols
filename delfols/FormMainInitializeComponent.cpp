#include "stdafx.h"

#include "LogListView.h"
#include "FormMain.h"

namespace delfols {

	// this->lvLog = (gcnew System::Windows::Forms::ListView());
	// this->lvLog = (gcnew LogListView());
	void FormMain::InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMain::typeid));
		this->lvMain = (gcnew System::Windows::Forms::ListView());
		this->chEntry = (gcnew System::Windows::Forms::ColumnHeader());
		this->chActualPath = (gcnew System::Windows::Forms::ColumnHeader());
		this->toolMain = (gcnew System::Windows::Forms::ToolStrip());
		this->tbAdd = (gcnew System::Windows::Forms::ToolStripButton());
		this->tbExecute = (gcnew System::Windows::Forms::ToolStripButton());
		this->tbAsAdmin = (gcnew System::Windows::Forms::ToolStripButton());
		this->spRoot = (gcnew System::Windows::Forms::SplitContainer());
		this->lvLog = (gcnew LogListView());
		this->chNo = (gcnew System::Windows::Forms::ColumnHeader());
		this->chFile = (gcnew System::Windows::Forms::ColumnHeader());
		this->chResult = (gcnew System::Windows::Forms::ColumnHeader());
		this->toolMain->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->spRoot))->BeginInit();
		this->spRoot->Panel1->SuspendLayout();
		this->spRoot->Panel2->SuspendLayout();
		this->spRoot->SuspendLayout();
		this->SuspendLayout();
		// 
		// lvMain
		// 
		this->lvMain->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->chEntry, this->chActualPath });
		this->lvMain->Dock = System::Windows::Forms::DockStyle::Fill;
		this->lvMain->Location = System::Drawing::Point(0, 25);
		this->lvMain->Name = L"lvMain";
		this->lvMain->Size = System::Drawing::Size(699, 200);
		this->lvMain->TabIndex = 0;
		this->lvMain->UseCompatibleStateImageBehavior = false;
		this->lvMain->View = System::Windows::Forms::View::Details;
		// 
		// chEntry
		// 
		this->chEntry->Text = L"Entry";
		this->chEntry->Width = 271;
		// 
		// chActualPath
		// 
		this->chActualPath->Text = L"Actual Path";
		this->chActualPath->Width = 320;
		// 
		// toolMain
		// 
		this->toolMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
			this->tbAdd, this->tbExecute,
				this->tbAsAdmin
		});
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
		this->tbExecute->Size = System::Drawing::Size(67, 22);
		this->tbExecute->Text = L"Execute";
		this->tbExecute->Click += gcnew System::EventHandler(this, &FormMain::tbExecute_Click);
		// 
		// tbAsAdmin
		// 
		this->tbAsAdmin->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tbAsAdmin.Image")));
		this->tbAsAdmin->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tbAsAdmin->Name = L"tbAsAdmin";
		this->tbAsAdmin->Size = System::Drawing::Size(79, 22);
		this->tbAsAdmin->Text = L"As Admin";
		this->tbAsAdmin->ToolTipText = L"As Admin";
		this->tbAsAdmin->Click += gcnew System::EventHandler(this, &FormMain::tbAsAdmin_Click);
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
		this->spRoot->Size = System::Drawing::Size(699, 453);
		this->spRoot->SplitterDistance = 225;
		this->spRoot->TabIndex = 2;
		// 
		// lvLog
		// 
		this->lvLog->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) { this->chNo, this->chFile, this->chResult });
		this->lvLog->Dock = System::Windows::Forms::DockStyle::Fill;
		this->lvLog->FullRowSelect = true;
		this->lvLog->Location = System::Drawing::Point(0, 0);
		this->lvLog->Name = L"lvLog";
		this->lvLog->Size = System::Drawing::Size(699, 224);
		this->lvLog->TabIndex = 0;
		this->lvLog->UseCompatibleStateImageBehavior = false;
		this->lvLog->View = System::Windows::Forms::View::Details;
		this->lvLog->VirtualMode = true;
		this->lvLog->CacheVirtualItems += gcnew System::Windows::Forms::CacheVirtualItemsEventHandler(this, &FormMain::lvLog_CacheVirtualItems);
		this->lvLog->RetrieveVirtualItem += gcnew System::Windows::Forms::RetrieveVirtualItemEventHandler(this, &FormMain::lvLog_RetrieveVirtualItem);
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
		// FormMain
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(699, 453);
		this->Controls->Add(this->spRoot);
		this->Name = L"FormMain";
		this->Text = L"delfols";
		this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMain::FormMain_FormClosing);
		this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
		this->toolMain->ResumeLayout(false);
		this->toolMain->PerformLayout();
		this->spRoot->Panel1->ResumeLayout(false);
		this->spRoot->Panel1->PerformLayout();
		this->spRoot->Panel2->ResumeLayout(false);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->spRoot))->EndInit();
		this->spRoot->ResumeLayout(false);
		this->ResumeLayout(false);

	}

}