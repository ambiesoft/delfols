#include "stdafx.h"
#include "helper.h"

namespace delfols {
	using namespace System;
	using namespace System::Windows::Forms;

	void ShowErrorMessage(IWin32Window^ win, String^ s)
	{
		Ambiesoft::CenteredMessageBox::Show(win,
			s,
			Application::ProductName,
			MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	void ShowErrorMessage(Exception^ ex)
	{
		ShowErrorMessage(ex->Message);
	}



}


