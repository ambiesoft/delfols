#pragma once


namespace delfols {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 �̊T�v
	///
	/// �x��: ���̃N���X�̖��O��ύX����ꍇ�A���̃N���X���ˑ����邷�ׂĂ� .resx �t�@�C���Ɋ֘A�t����ꂽ
	///          �}�l�[�W ���\�[�X �R���p�C�� �c�[���ɑ΂��� 'Resource File Name' �v���p�e�B��
	///          �ύX����K�v������܂��B���̕ύX���s��Ȃ��ƁA
	///          �f�U�C�i�ƁA���̃t�H�[���Ɋ֘A�t����ꂽ���[�J���C�Y�ς݃��\�[�X�Ƃ��A
	///          ���������݂ɗ��p�ł��Ȃ��Ȃ�܂��B
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
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
		/// �K�v�ȃf�U�C�i�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�ŕύX���Ȃ��ł��������B
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

