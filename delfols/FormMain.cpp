#include "stdafx.h"
#include "FormMain.h"
#include "helper.h"
#include "noStdafxHelper.h"
#include "../../MyUtility/getStdString.net.h"
#include "../../MyUtility/StartProcess.h"

namespace delfols {
	using namespace System::Diagnostics;
	using namespace std;

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

	void FormMain::deleteAll(DirectoryInfo^ di)
	{
		array<DirectoryInfo^>^ subdirs = nullptr;
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
				theDeleteDir(subdir->FullName);
				continue;
			}
			
			deleteAll(subdir);
			theDeleteDir(subdir->FullName);
		}

		array<FileInfo^>^ files = di->GetFiles();
		for each(FileInfo^ f in files)
		{
			try
			{
				String^ full = f->FullName;
				theDeleteFile(full);
			}
			catch(System::Exception^ ex)
			{
				addToLog(di->FullName, false, ex->Message);
			}
		}
	}
	System::Void FormMain::tbExecute_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(System::Windows::Forms::DialogResult::Yes != MessageBox::Show(TOI18NS(L"Are you sure to delete files and folders on the list?"),
			Application::ProductName,
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Question))
		{
			return;
		}

		lvLog->Items->Clear();

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

			if(File::Exists(path))
			{
				theDeleteFile(path);
				continue;
			}

			if(!Directory::Exists(path))
				continue;

			DirectoryInfo^ di = gcnew DirectoryInfo(path);
			deleteAll(di);

			if(!path->EndsWith(L"\\"))
			{
				theDeleteDir(di->FullName);
			}
		}
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
		ret = ret->TrimEnd(gcnew array<System::Char>{L'\\'});
		return ret;
	}
	void FormMain::SetPath(array<String^>^ paths)
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
		array<String^>^ paths;
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
		}

	}


	void FormMain::addToLog(String^ filename, bool ok, String^ desc)
	{
		int count = lvLog->Items->Count + 1;
		ListViewItem^ item = gcnew ListViewItem();
		item->Text = count.ToString();
		item->SubItems->Add(filename);
		item->SubItems->Add(ok ? L"OK" : desc);

		lvLog->Items->Add(item);
	}
	void FormMain::theDeleteFile(String^ path)
	{
		if(!path || path->Length < 3 || path[1] != L':' || path[2] != L'\\')
		{
			addToLog(path, false, TOI18NS(L"Not Fullpath"));
			return;
		}

		try
		{
			File::Delete(path);
			addToLog(path, true, L"");
		}
		catch(System::Exception^ ex)
		{
			addToLog(path, false, ex->Message);
		}
	}
	
	void FormMain::theDeleteDir(String^ path)
	{
		if(!path || path->Length < 3 || path[1] != L':' || path[2] != L'\\')
		{
			addToLog(path, false, TOI18NS(L"Not Fullpath"));
			return;
		}

		try
		{
			Directory::Delete(path);
			addToLog(path, true, L"");
		}
		catch(System::Exception^ ex)
		{
			addToLog(path, false, ex->Message);
		}
	}




	System::Void FormMain::tbAsAdmin_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//std::wstring app = Ambiesoft::getStdWstring(System::Environment::CommandLine);
		//if(!StartProcess(app.c_str()))
		//{
		//	ShowErrorMessage(TOI18NS(L"Failed : Process start"));
		//}

		try
		{
			ProcessStartInfo psi(Application::ExecutablePath);
			psi.Verb = L"runas";
			Process::Start(%psi);
			this->Close();
		}
		catch(Exception^ ex)
		{
			ShowErrorMessage(ex);
		}
	}

}