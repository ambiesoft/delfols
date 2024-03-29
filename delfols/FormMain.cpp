#include "stdafx.h"

#include <vcclr.h>

#include "../../lsMisc/SHMoveFile.h"
#include "../../lsMisc/ReentBlocker.h"
#include "../../lsMisc/ExpandPath.h"

#include <C:/Linkout/CommonDLL/TimedMessageBox.h>

#include "FormMain.h"
#include "helper.h"
#include "noStdafxHelper.h"
#include "ThreadParam.h"
#include "StartDeleteDialog.h"
using namespace System::Text;

// thread suspend and resume
#pragma warning(disable:4947)

#pragma comment(lib, "user32.lib")

namespace delfols {

	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Threading;
	using namespace System::Collections::Generic;
	using namespace std;
	using namespace Ambiesoft;



	FormMain::FormMain(void)
	{
		InitializeComponent();
		String^ inipath = AmbLib::GetIniPath();
		HashIni^ ini = Profile::ReadAll(inipath);

		AmbLib::LoadFormXYWH(this, SECTION_FORMPOS, ini);
		AmbLib::LoadListViewColumnWidth(lvMain, SECTION_LIST, KEY_MAIN_LIST, ini);
		AmbLib::LoadListViewColumnWidth(lvLog, SECTION_LIST, KEY_MAIN_LOG, ini);
	}

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
		catch (System::Exception^ ex)
		{
			addToLog(di->FullName, false, ex->Message);
			return;
		}

		for each(DirectoryInfo^ subdir in subdirs)
		{
			if ((subdir->Attributes & System::IO::FileAttributes::ReparsePoint) == System::IO::FileAttributes::ReparsePoint)
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
			catch (System::Exception^ ex)
			{
				addToLog(di->FullName, false, ex->Message);
			}
		}
	}

	void FormMain::OnThreadStarted(ThreadParam^ tp)
	{
		return;
	}
	void FormMain::OnThreadEnded(ThreadParam^ tp)
	{
		DASSERT(tp);
		if (!tp->IsCloseOnFinish)
		{
			CppUtils::CenteredMessageBox(
				this,
				TOI18NS(L"Completed"),
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Information);
			return;
		}

		HMODULE hModule = LoadLibrary(L"TimedMessageBox.dll");
		if (!hModule)
		{
			CppUtils::CenteredMessageBox(
				this,
				TOI18NS(L"Failed to load TimedMessageBox.dll"),
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Information);
			return;
		}

		FNTimedMessageBox2 func2 = NULL;
		func2 = (FNTimedMessageBox2)GetProcAddress(hModule, "fnTimedMessageBox2");
		if (!func2)
		{
			CppUtils::CenteredMessageBox(
				this,
				TOI18NS(L"Failed to load function fnTimedMessageBox2"),
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Information);
			return;
		}
	

		TIMEDMESSAGEBOX_PARAMS tmbparam = { 0 };
		tmbparam.size = sizeof(tp);
		tmbparam.flags = TIMEDMESSAGEBOX_FLAGS_POSITION |
			TIMEDMESSAGEBOX_FLAGS_SHOWCMD |
			TIMEDMESSAGEBOX_FLAGS_HIDERETRY;
		tmbparam.hWndCenterParent = (HWND)this->Handle.ToPointer();
		tmbparam.position = TIMEDMESSAGEBOX_POSITION_CENTERPARENT;
		tmbparam.nShowCmd = SW_SHOW;

		wstring messageTitle = TOI18NS(L"Finished Deleting");
		wstring message = TOI18NS(L"Finished Deleting. Click OK to close.");
		MessageBeep(MB_ICONINFORMATION);
		int dret = func2((HWND)this->Handle.ToPointer(),
			30,
			messageTitle.c_str(),
			message.c_str(),
			&tmbparam);

		switch (dret)
		{
		case IDCANCEL:
			return;
		}

		Close();
		return;
	}

	void FormMain::threadStart(Object^ obj)
	{
		ThreadParam^ tp = (ThreadParam^)obj;

		BeginInvoke(gcnew VParamDelegate(this, &FormMain::OnThreadStarted), tp);


		for each(String^ path in tp->AllToDel)
		{
			if (File::Exists(path))
			{
				theDeleteFile(tp, path);
				continue;
			}

			if (!Directory::Exists(path))
				continue;

			DirectoryInfo^ di = gcnew DirectoryInfo(path);
			deleteAll(tp, di);

			if (!path->EndsWith(L"\\"))
			{
				theDeleteDir(tp, di->FullName);
			}
		}
		addToLogEnd();
		BeginInvoke(gcnew VParamDelegate(this, &FormMain::OnThreadEnded), tp);
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

		logInfos_.Clear();
		logCache_.Clear();
		lvLog->VirtualListSize = 0;

		List<String^>^ allToDel = gcnew List<String^>();

		for each(ListViewItem^ item in lvMain->Items)
		{
			String^ path = L"";
			try
			{
				path = item->SubItems[1]->Text;
			}
			catch (System::Exception^)
			{
				continue;
			}

			cli::array<String^>^ parts = path->Split(L';');
			for each(String^ part in parts)
			{
				if (!part || part->Length < 3)
					continue;

				if (part[1] != L':' || part[2] != L'\\')
					continue;

				allToDel->Add(part);
			}
		}

		thread_ = gcnew Thread(gcnew ParameterizedThreadStart(this, &FormMain::threadStart));
		thread_->IsBackground = true;
		if (dlg.IsDryrun)
			thread_->Priority = ThreadPriority::Lowest;
		thread_->Start(gcnew ThreadParam(dlg.IsDryrun, dlg.IsShellDelete, dlg.IsCloseOnFinish, allToDel));
	}
	System::Void FormMain::lvLog_RetrieveVirtualItem(System::Object^  sender, System::Windows::Forms::RetrieveVirtualItemEventArgs^  e)
	{
		if (logCache_.Count <= e->ItemIndex)
		{
			// not in cache
			ListViewItem^ ret = gcnew ListViewItem();
			ret->Text = (e->ItemIndex + 1).ToString();
			LogInfo^ info = logInfos_[e->ItemIndex];
			ret->SubItems->Add(info->Filename);
			ret->SubItems->Add(info->Result);
			e->Item = ret;
		}
		else
		{
			e->Item = logCache_[e->ItemIndex];
		}
		DASSERT(e->Item);
	}
	System::Void FormMain::lvLog_CacheVirtualItems(System::Object^  sender, System::Windows::Forms::CacheVirtualItemsEventArgs^  e)
	{
		// IF count = 2, e->EndIndex = 5,
		// It needs start from index 2 to 5
		//
		// IF count = 4, e->EndIndex = 5 
		// it needs start from index 5 to 5
		//
		// IF count = 0, e->EndIndex = 0,
		// it needs start from index 0 to 0
		// int iStart = logCache_.Count == 0 ? 0 : e->EndIndex - logCache_.Count - 1;
		for (int i = logCache_.Count; i <= e->EndIndex; ++i)
		{
			ListViewItem^ item = gcnew ListViewItem();
			item->Text = (i + 1).ToString();
			LogInfo^ info = logInfos_[i];
			item->SubItems->Add(info->Filename);
			item->SubItems->Add(info->Result);

			logCache_.Add(item);
		}
	}
	static String^ trans(System::Text::RegularExpressions::Match^ m)
	{
		String^ ret = String::Empty;
		String^ x = m->ToString();

		if (x == L"${$}")
		{
			ret = L"$";
		}
		else if (x == L"${LocalApplicationData}")
		{
			ret = System::Environment::GetFolderPath(System::Environment::SpecialFolder::LocalApplicationData);
		}
		else if (x == L"${InternetCache}")
		{
			ret = System::Environment::GetFolderPath(System::Environment::SpecialFolder::InternetCache);
		}
		else if (x == L"${Recent}")
		{
			ret = System::Environment::GetFolderPath(System::Environment::SpecialFolder::Recent);
		}
		else if (x->StartsWith(L"${%"))
		{
			String^ envval = x->Substring(3, x->Length - 5);
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
		if (!paths)
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

				if (actualpath)
				{
					if (File::Exists(actualpath))
					{
						FileInfo fi(actualpath);
						actualpath = fi.FullName;
						item->SubItems->Add(actualpath);
					}
					else if (Directory::Exists(actualpath))
					{
						DirectoryInfo di(actualpath);
						actualpath = di.FullName;
						item->SubItems->Add(actualpath);
					}
					else if (actualpath->IndexOf(L"*") >= 0)
					{
						wstring strap = getStdWstring(actualpath);
						vector<wstring> results;
						ExpandPath(strap, results);

						System::Text::StringBuilder sbSubItem;
						for (size_t i = 0; i < results.size(); ++i)
						{
							wstring t = results[i];
							sbSubItem.Append(gcnew String(t.c_str()));

							if ((i + 1) != results.size())
								sbSubItem.Append(L";");
						}
						item->SubItems->Add(sbSubItem.ToString());
					}
				}
			}
			catch (System::Exception^)
			{
			}

			lvMain->Items->Add(item);
		}
	}

	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		cli::array<String^>^ paths;
		String^ confpath = Path::Combine(System::IO::Path::GetDirectoryName(Application::ExecutablePath), L"config.ini");
		if (File::Exists(confpath))
		{
			//Ambiesoft::WProfiler::HashIni^ ini = Ambiesoft::WProfiler::WProfile::ReadAll(confpath, true);
			Ambiesoft::HashIni^ ini = Ambiesoft::Profile::ReadAll(confpath, true);
			Ambiesoft::Profile::GetStringArray(L"dirs", L"dir", paths, ini);
		}

		SetPath(paths);

		if (IsUserAnAdmin())
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
			thread_ = nullptr;
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

		// from here, no cancelling
		String^ inipath = AmbLib::GetIniPath();
		HashIni^ ini = Profile::ReadAll(inipath);

		AmbLib::SaveListViewColumnWidth(lvMain, SECTION_LIST, KEY_MAIN_LIST, ini);
		AmbLib::SaveListViewColumnWidth(lvLog, SECTION_LIST, KEY_MAIN_LOG, ini);
		AmbLib::SaveFormXYWH(this, SECTION_FORMPOS, ini);
		if (!Profile::WriteAll(ini, inipath))
		{
			CppUtils::Alert(this,TOI18NS(L"Failed to save to ini file."));
		}
	}

	ref struct ListUpdateLocker
	{
		System::Windows::Forms::ListView^ c_;
		ListUpdateLocker(System::Windows::Forms::ListView^ c) :c_(c)
		{
			DASSERT(c && c->IsHandleCreated && !c->IsDisposed);
			c_->BeginUpdate();
		}
		~ListUpdateLocker()
		{
			c_->EndUpdate();
		}
	};
	delegate void LogDelegate();
	void FormMain::addToLogMain()
	{
		DASSERT(!InvokeRequired);
		DTRACE(sendCache_.Count);
		logInfos_.AddRange(sendCache_.ToArray());
		sendCache_.Clear();
		lvLog->VirtualListSize = logInfos_.Count;

		ListUpdateLocker lul(lvLog);
		lvLog->Items[lvLog->Items->Count - 1]->EnsureVisible();
	}
	void FormMain::addToLog(String^ filename, bool ok, String^ desc)
	{
		// cache data for logging in sendCache_,
		// each 100 millisec, it send to main thread.

		// must be in thread
		DASSERT(InvokeRequired);

		String^ result = (ok ? L"OK" : L"NG");
		if (!String::IsNullOrEmpty(desc))
			result += L" (" + desc + L")";

		sendCache_.Add(gcnew LogInfo(filename, result));

		static int slastTick;
		int nowTick = Environment::TickCount;
		if ((nowTick - slastTick) > 100)
		{
			IAsyncResult^ r = BeginInvoke(gcnew LogDelegate(this, &FormMain::addToLogMain));
			EndInvoke(r);
			slastTick = nowTick;
		}

		return;
	}

	void FormMain::addToLogEnd()
	{
		// send remnant sendCache_

		DASSERT(InvokeRequired);
		IAsyncResult^ r = BeginInvoke(gcnew LogDelegate(this, &FormMain::addToLogMain));
		EndInvoke(r);
	}
	void FormMain::theDeleteFile(ThreadParam ^tp, String^ path)
	{
		if (!path || path->Length < 3 || path[1] != L':' || path[2] != L'\\')
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

				int ret = SHDeleteFileEx(pPath,FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT);
				addToLog(path, ret==0, gcnew String(GetSHFileOpErrorString(ret).c_str()));
			}
			else
			{
				File::Delete(path);
				addToLog(path, true, L"");
			}
		}
		catch (System::Exception^ ex)
		{
			addToLog(path, false, ex->Message);
		}
	}

	void FormMain::theDeleteDir(ThreadParam ^tp, String^ path)
	{
		if (!path || path->Length < 3 || path[1] != L':' || path[2] != L'\\')
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
				int ret = SHDeleteFileEx(pPath, FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT);
				addToLog(path, ret==0, gcnew String(GetSHFileOpErrorString(ret).c_str()));
			}
			else
			{
				Directory::Delete(path);
				addToLog(path, true, L"");
			}
		}
		catch (System::Exception^ ex)
		{
			addToLog(path, false, ex->Message);
		}
	}




	System::Void FormMain::tbAsAdmin_Click(System::Object^  sender, System::EventArgs^  e)
	{
		static bool reent;
		if (reent)
			return;
		ReentBlocker rb(&reent, true, false);

		if (!checkThreadCanContinue(TOI18NS(L"stop")))
			return;

		try
		{
			ProcessStartInfo psi(Application::ExecutablePath);
			psi.Verb = L"runas";
			Process::Start(%psi);
			this->Close();
		}
		catch (Exception^ ex)
		{
			ShowErrorMessage(this, ex);
		}
	}
	System::Void FormMain::tsmiAbout_Click(System::Object^ sender, System::EventArgs^ e)
	{
		StringBuilder sb;
		sb.AppendLine(String::Format(L"{0} v{1}",
			Application::ProductName,
			AmbLib::getAssemblyVersion(System::Reflection::Assembly::GetExecutingAssembly(), 3)));
		sb.AppendLine();
		sb.AppendLine(L"https://ambiesoft.com/");
	
		JR::Utils::GUI::Forms::FlexibleMessageBox::Show(
			this,
			sb.ToString(),
			Application::ProductName,
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
}