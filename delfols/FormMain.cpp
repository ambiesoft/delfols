#include "stdafx.h"
#include "FormMain.h"

using System::IO;

namespace delfols {
	
System::Void FormMain::clbMain_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
	if (e->Data->GetDataPresent(DataFormats::FileDrop, true) )
	{
		e->Effect = DragDropEffects::Copy;
	}
}

System::Void FormMain::clbMain_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
	if (e->Data->GetDataPresent(DataFormats::FileDrop, true) )
	{
		array<Object^>^ os = (array<Object^>^)e->Data->GetData(DataFormats::FileDrop, true);
		for each(Object^ o in os)
		{
			if(System::IO::Directory::Exists(o->ToString()))
			{
				clbMain->Items->Add(o->ToString(), true);
			}
		}
	}
}









}