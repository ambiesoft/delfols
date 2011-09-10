#include "stdafx.h"
#include "FormMain.h"

namespace delfols {

	using namespace System::IO;
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

	void deleteAll(DirectoryInfo^ di)
	{
		array<DirectoryInfo^>^ subdirs = di->GetDirectories();
		for each(DirectoryInfo^ subdir in subdirs)
		{
			deleteAll(subdir);
			try
			{
				subdir->Delete();
			}
			catch(System::Exception^)
			{

			}
		}

		array<FileInfo^>^ files = di->GetFiles();
		for each(FileInfo^ f in files)
		{
			try
			{
				f->Delete();
			}
			catch(System::Exception^)
			{
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
				File::Delete(path);
				continue;
			}

			if(!Directory::Exists(path))
				continue;

			DirectoryInfo^ di = gcnew DirectoryInfo(path);
			deleteAll(di);

			if(path->EndsWith(L"\\"))
			{
				try
				{
					di->Delete();
				}
				catch(System::Exception^)
				{}
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
		else if(x == L"${%Tmp%}")
		{
			ret = System::Environment::GetEnvironmentVariable(L"Tmp");
		}
		else if(x == L"${%Temp%}")
		{
			ret = System::Environment::GetEnvironmentVariable(L"Temp");
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
		String^ inipath = Path::Combine(System::IO::Path::GetDirectoryName(Application::ExecutablePath), L"config.ini");
		if(File::Exists(inipath))
		{
			Ambiesoft::WProfiler::HashIni^ ini = Ambiesoft::WProfiler::WProfile::ReadAll(inipath, true);
			Ambiesoft::WProfiler::WProfile::WGetPrivateProfileStringArray(L"dirs", L"dir", paths, ini);
		}

		SetPath(paths);
	}






}