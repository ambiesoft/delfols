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
	private: System::Windows::Forms::CheckedListBox^  clbMain;
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
			this->clbMain = (gcnew System::Windows::Forms::CheckedListBox());
			this->SuspendLayout();
			// 
			// clbMain
			// 
			this->clbMain->AllowDrop = true;
			this->clbMain->FormattingEnabled = true;
			this->clbMain->Location = System::Drawing::Point(26, 136);
			this->clbMain->Name = L"clbMain";
			this->clbMain->Size = System::Drawing::Size(650, 270);
			this->clbMain->TabIndex = 1;
			this->clbMain->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &FormMain::clbMain_DragDrop);
			this->clbMain->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &FormMain::clbMain_DragEnter);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(699, 418);
			this->Controls->Add(this->clbMain);
			this->Name = L"FormMain";
			this->Text = L"FormMain";
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		System::Void clbMain_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
		System::Void clbMain_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);

	};
}

