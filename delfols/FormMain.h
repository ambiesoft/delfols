#pragma once

#include "ThreadParam.h"
#include "LogInfo.h"

namespace delfols {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class FormMain : public System::Windows::Forms::Form
	{
		literal String^ SECTION_FORMPOS = L"FormPosition";
		
		literal String^ SECTION_LIST = L"List";
		literal String^ KEY_MAIN_LIST = L"Main";
		literal String^ KEY_MAIN_LOG = L"Log";
		

	public:
		System::Collections::Generic::List<LogInfo^> logInfos_;
		System::Collections::Generic::List<ListViewItem^> logCache_;

	public:
		FormMain(void);

	protected:
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
	private: System::Windows::Forms::ColumnHeader^  chActualPath;

	private: System::Windows::Forms::ToolStrip^  toolMain;
	private: System::Windows::Forms::ToolStripButton^  tbAdd;
	private: System::Windows::Forms::ToolStripButton^  tbExecute;
	private: System::Windows::Forms::SplitContainer^  spRoot;
	private: System::Windows::Forms::ListView^  lvLog;
	private: System::Windows::Forms::ColumnHeader^  chNo;
	private: System::Windows::Forms::ColumnHeader^  chFile;
	private: System::Windows::Forms::ColumnHeader^  chResult;


	private: System::Windows::Forms::ToolStripButton^  tbAsAdmin;



	protected: 

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void);
#pragma endregion

	private:
		delegate void VVDelegate();
		delegate bool BVDelegate();
		delegate void VParamDelegate(ThreadParam^ tp);
		System::Threading::Thread^ thread_;
		System::Collections::Generic::List<LogInfo^> sendCache_;

	private:
		void SetPath(array<String^>^ paths);
		void deleteAll(ThreadParam ^tp, DirectoryInfo^ di);
		void theDeleteFile(ThreadParam ^tp, String^ path);
		void theDeleteDir(ThreadParam ^tp, String^ path);
		void addToLog(String^ filename, bool ok, String^ desc);
		void addToLogMain();
		void addToLogEnd();
		void threadStart(Object^ obj);
		void OnThreadStarted(ThreadParam^ tp);
		void OnThreadEnded(ThreadParam^ tp);
		bool checkThreadCanContinue(String^ message);
	private:
		System::Void tbAdd_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void tbExecute_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tbAsAdmin_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		System::Void lvLog_RetrieveVirtualItem(System::Object^  sender, System::Windows::Forms::RetrieveVirtualItemEventArgs^  e);
		System::Void lvLog_CacheVirtualItems(System::Object^  sender, System::Windows::Forms::CacheVirtualItemsEventArgs^  e);

};
















}

