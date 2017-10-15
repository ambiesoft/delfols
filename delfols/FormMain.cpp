#include "stdafx.h"

#include <vcclr.h>

#include "../../lsMisc/SHMoveFile.h"

#include "FormMain.h"
#include "helper.h"
#include "noStdafxHelper.h"
#include "ThreadParam.h"
#include "StartDeleteDialog.h"

// thread suspend and resume
#pragma warning(disable:4947)

namespace delfols {
	using namespace System::Diagnostics;
	using namespace System::Threading;
	using namespace System::Collections::Generic;
	using namespace std;
	using namespace Ambiesoft;

	FormMain::FormMain(void)
	{
		InitializeComponent();
		String^ inipath = Path::Combine(System::IO::Path::GetDirectoryName(Application::ExecutablePath), Application::ProductName + L".ini");
	}
	


//System::Void FormMain::clbMain_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
//{
//	if (e->Data->GetDataPresent(DataFormats::FileDrop, true) )
//	{
//		e->Effect = DragDropEffects::Copy;
//	}
//}
//
//System::Void FormMain::clbMain_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
//{
//	if (e->Data->GetDataPresent(DataFormats::FileDrop, true) )
//	{
//		array<Object^>^ os = (array<Object^>^)e->Data->GetData(DataFormats::FileDrop, true);
//		for each(Object^ o in os)
//		{
//			if(System::IO::Directory::Exists(o->ToString()))
//			{
//				clbMain->Items->Add(o->ToString(), true);
//			}
//		}
//	}
//}

	System::Void FormMain::tbAdd_Click(System::Object^  sender, System::EventArgs^  e)
	{
		String^ s = System::Environment::GetFolderPath(System::Environment::SpecialFolder::LocalApplicationData);
	}

	void FormMain::deleteAll(ThreadParam ^tp, DirectoryInfo^ di)
	{
		cli::array<DirectoryInfo^>^ subdirs = nullptr;
		try
		{
			subdirs = di->GetDirectories();
		}
		catch(System::Exception^ ex)
		{
			addToLog(di->FullName, false, ex->Message);
			return;
		}

		for each(DirectoryInfo^ subdir in subdirs)
		{
			if ((subdir->Attributes & System::IO::FileAttributes::ReparsePoint)==System::IO::FileAttributes::ReparsePoint)
			{
				theDeleteDir(tp, subdir->FullName);
				continue;
			}
			
			deleteAll(tp, subdir);
			theDeleteDir(tp, subdir->FullName);
		}

		cli::array<FileInfo^>^ files = di->GetFiles();
		for each(FileInfo^ f in files)
		{
			try
			{
				String^ full = f->FullName;
				theDeleteFile(tp, full);
			}
			catch(System::Exception^ ex)
			{
				addToLog(di->FullName, false, ex->Message);
			}
		}
	}
	
	bool FormMain::OnThreadStarted()
	{
		return true;
	}
	bool FormMain::OnThreadEnded()
	{
		CppUtils::CenteredMessageBox(
			this,
			TOI18NS(L"Completed"),
			Application::ProductName,
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
		return true;
	}

	void FormMain::threadStart(Object^ obj)
	{
		ThreadParam^ tp = (ThreadParam^)obj;

		BeginInvoke(gcnew BVDelegate(this,&FormMain::OnThreadStarted));


		for each(String^ path in tp->AllToDel)
		{
			if(File::Exists(path))
			{
				theDeleteFile(tp, path);
				continue;
			}

			if(!Directory::Exists(path))
				continue;

			DirectoryInfo^ di = gcnew DirectoryInfo(path);
			deleteAll(tp, di);

			if(!path->EndsWith(L"\\"))
			{
				theDeleteDir(tp, di->FullName);
			}
		}
		BeginInvoke(gcnew BVDelegate(this,&FormMain::OnThreadEnded));
	}


	System::Void FormMain::tbExecute_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!checkThreadCanContinue(TOI18NS(L"stop current operation")))
		{
			return;
		}

		//if(System::Windows::Forms::DialogResult::Yes != CppUtils::CenteredMessageBox(
		//	this,
		//	TOI18NS(L"Are you sure to delete files and folders on the list?"),
		//	Application::ProductName,
		//	MessageBoxButtons::YesNo,
		//	MessageBoxIcon::Question))
		//{
		//	return;
		//}
		StartDeleteDialog dlg;
		if (System::Windows::Forms::DialogResult::OK != dlg.ShowDialog())
			return;
		
		lvLog->Items->Clear();

		List<String^>^ allToDel = gcnew List<String^>();

		for each(ListViewItem^ item in lvMain->Items)
		{
			String^ path = L"";
			try
			{
				path = item->SubItems[1]->Text;
			}
			catch(System::Exception^)
			{
				continue;
			}

			if(!path || path->Length < 3)
				continue;

			if(path[1] != L':' || path[2] != L'\\')
				continue;

			allToDel->Add(path);
		}

		thread_ = gcnew Thread(gcnew ParameterizedThreadStart(this, &FormMain::threadStart));
		thread_->IsBackground = true;
		thread_->Start(gcnew ThreadParam(dlg.IsDryrun, dlg.IsShellDelete, allToDel));
	}

	static String^ trans(System::Text::RegularExpressions::Match^ m)
	{
		String^ ret = String::Empty;
        String^ x = m->ToString();

		if(x == L"${$}")
		{
			ret = L"$";
		}
		else if(x == L"${LocalApplicationData}")
		{
			ret = System::Environment::GetFolderPath(System::Environment::SpecialFolder::LocalApplicationData);
		}
		else if(x == L"${InternetCache}")
		{
			ret = System::Environment::GetFolderPath(System::Environment::SpecialFolder::InternetCache);
		}
		else if(x == L"${Recent}")
		{
			ret = System::Environment::GetFolderPath(System::Environment::SpecialFolder::Recent);
		}
		else if(x->StartsWith(L"${%"))
		{
			String^ envval = x->Substring(3,x->Length-5);
			ret = myGetEnvironmentVariable(envval);
		}
		else
		{
			throw gcnew System::Exception();
		}
		ret = ret->TrimEnd(gcnew cli::array<System::Char>{L'\\'});
		return ret;
	}
	void FormMain::SetPath(cli::array<String^>^ paths)
	{
		lvMain->Items->Clear();
		if(!paths)
			return;

		for each(String^ path in paths)
		{
			ListViewItem^ item = gcnew ListViewItem();
			item->Text = path;

			String^ actualpath = L"";
			try
			{
				actualpath = System::Text::RegularExpressions::Regex::Replace(path, L"\\${.*}", 
					gcnew System::Text::RegularExpressions::MatchEvaluator(trans));
				
				if(actualpath)
				{
					if(File::Exists(actualpath))
					{
						FileInfo fi(actualpath);
						actualpath = fi.FullName;
						item->SubItems->Add(actualpath);
					}
					else if(Directory::Exists(actualpath))
					{
						DirectoryInfo di(actualpath);
						actualpath = di.FullName;
						item->SubItems->Add(actualpath);
					}
				}	
			}
			catch(System::Exception^)
			{}

			lvMain->Items->Add(item);
		}
	}

	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		cli::array<String^>^ paths;
		String^ confpath = Path::Combine(System::IO::Path::GetDirectoryName(Application::ExecutablePath), L"config.ini");
		if(File::Exists(confpath))
		{
			//Ambiesoft::WProfiler::HashIni^ ini = Ambiesoft::WProfiler::WProfile::ReadAll(confpath, true);
			Ambiesoft::HashIni^ ini = Ambiesoft::Profile::ReadAll(confpath, true);
			Ambiesoft::Profile::GetStringArray(L"dirs", L"dir", paths, ini);
		}

		SetPath(paths);

		if(IsUserAnAdmin())
		{
			this->Text += L" " + TOI18NS(L"(Admin)");
			tbAsAdmin->Visible = false;
		}
		else
		{
			tbAsAdmin->Visible = true;
		}

	}
	bool FormMain::checkThreadCanContinue(String^ message)
	{
		if (thread_ && thread_->IsAlive)
		{
			thread_->Suspend();
			if (System::Windows::Forms::DialogResult::Yes != CppUtils::CenteredMessageBox(
				this,
				String::Format(
					TOI18NS(L"Thread is still running. Are you sure to {0}?"),
					message),
				Application::ProductName,
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Question))
			{
				// User said NO, so continu thread cancel current operation
				thread_->Resume();
				return false;
			}
			// User said YES, delete thread and continue user operation
			delete thread_;
			thread_=nullptr;
			return true;
		}

		// No threads, user operation can continue
		return true;
	}
	System::Void FormMain::FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		if (!checkThreadCanContinue(TOI18NS(L"close")))
		{
			e->Cancel = true;
			return;
		}
	}
	delegate void LogDelegate(String^ filename, bool ok, String^ desc);
	void FormMain::addToLog(String^ filename, bool ok, String^ desc)
	{
		if(InvokeRequired)
		{
			BeginInvoke(gcnew LogDelegate(this, &FormMain::addToLog),
				filename,ok,desc);
			return;
		}
		int count = lvLog->Items->Count + 1;
		ListViewItem^ item = gcnew ListViewItem();
		item->Text = count.ToString();
		item->SubItems->Add(filename);
		item->SubItems->Add((ok ? L"OK" : L"NG") + L" (" + desc + L")");

		lvLog->Items->Add(item);
		lvLog->EnsureVisible(lvLog->Items->IndexOf(item));
	}
	void FormMain::theDeleteFile(ThreadParam ^tp, String^ path)
	{
		if(!path || path->Length < 3 || path[1] != L':' || path[2] != L'\\')
		{
			addToLog(path, false, TOI18NS(L"Not Fullpath"));
			return;
		}

		try
		{
			if (tp->IsDryrun)
			{
				addToLog(path, true, L"Dryrun File");
			}
			else if (tp->IsShellDelete)
			{
				pin_ptr<const wchar_t> pPath = PtrToStringChars(path);
				int ret;
				bool bOK = !!SHDeleteFile(pPath, 
					FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT, 
					&ret);
				addToLog(path, bOK, gcnew String(GetSHFileOpErrorString(ret).c_str()));
			}
			else
			{
				File::Delete(path);
				addToLog(path, true, L"");
			}
		}
		catch(System::Exception^ ex)
		{
			addToLog(path, false, ex->Message);
		}
	}
	
	void FormMain::theDeleteDir(ThreadParam ^tp, String^ path)
	{
		if(!path || path->Length < 3 || path[1] != L':' || path[2] != L'\\')
		{
			addToLog(path, false, TOI18NS(L"Not Fullpath"));
			return;
		}

		try
		{
			if (tp->IsDryrun)
			{
				addToLog(path, true, L"Dryrun Directory");
			}
			else if (tp->IsShellDelete)
			{
				pin_ptr<const wchar_t> pPath = PtrToStringChars(path);
				int ret;
				bool bOK = !!SHDeleteFile(pPath, 
					FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT,
					&ret);
				addToLog(path, bOK, gcnew String(GetSHFileOpErrorString(ret).c_str()));
			}
			else
			{
				Directory::Delete(path);
				addToLog(path, true, L"");
			}
		}
		catch(System::Exception^ ex)
		{
			addToLog(path, false, ex->Message);
		}
	}




	System::Void FormMain::tbAsAdmin_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!checkThreadCanContinue(TOI18NS(L"stop")))
			return;

		try
		{
			ProcessStartInfo psi(Application::ExecutablePath);
			psi.Verb = L"runas";
			Process::Start(%psi);
			this->Close();
		}
		catch(Exception^ ex)
		{
			ShowErrorMessage(this, ex);
		}
	}

}