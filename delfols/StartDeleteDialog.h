#pragma once

namespace delfols {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// StartDeleteDialog の概要
	/// </summary>
	public ref class StartDeleteDialog : public System::Windows::Forms::Form
	{
	public:
		StartDeleteDialog(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~StartDeleteDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^  chkDryrun;
	private: System::Windows::Forms::CheckBox^  chkShellDelete;
	private: System::Windows::Forms::Button^  btnOK;
	private: System::Windows::Forms::Button^  btnCancel;
	protected: 

	protected: 


	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->chkDryrun = (gcnew System::Windows::Forms::CheckBox());
			this->chkShellDelete = (gcnew System::Windows::Forms::CheckBox());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// chkDryrun
			// 
			this->chkDryrun->AutoSize = true;
			this->chkDryrun->Location = System::Drawing::Point(12, 13);
			this->chkDryrun->Name = L"chkDryrun";
			this->chkDryrun->Size = System::Drawing::Size(57, 17);
			this->chkDryrun->TabIndex = 0;
			this->chkDryrun->Text = L"&Dryrun";
			this->chkDryrun->UseVisualStyleBackColor = true;
			// 
			// chkShellDelete
			// 
			this->chkShellDelete->AutoSize = true;
			this->chkShellDelete->Location = System::Drawing::Point(12, 37);
			this->chkShellDelete->Name = L"chkShellDelete";
			this->chkShellDelete->Size = System::Drawing::Size(81, 17);
			this->chkShellDelete->TabIndex = 0;
			this->chkShellDelete->Text = L"&Shell delete";
			this->chkShellDelete->UseVisualStyleBackColor = true;
			// 
			// btnOK
			// 
			this->btnOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btnOK->Location = System::Drawing::Point(144, 113);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(218, 25);
			this->btnOK->TabIndex = 1;
			this->btnOK->Text = L"&Delete Files on the list";
			this->btnOK->UseVisualStyleBackColor = true;
			// 
			// btnCancel
			// 
			this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnCancel->Location = System::Drawing::Point(368, 113);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(75, 25);
			this->btnCancel->TabIndex = 2;
			this->btnCancel->Text = L"&Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			// 
			// StartDeleteDialog
			// 
			this->AcceptButton = this->btnOK;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->btnCancel;
			this->ClientSize = System::Drawing::Size(455, 151);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnOK);
			this->Controls->Add(this->chkShellDelete);
			this->Controls->Add(this->chkDryrun);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"StartDeleteDialog";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Delete Files";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		public:
			property bool IsDryrun
			{
				bool get()
				{
					return chkDryrun->Checked;
				}
			}
			property bool IsShellDelete
			{
				bool get()
				{
					return chkShellDelete->Checked;
				}
			}
	};
}
