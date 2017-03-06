#include "stdafx.h"
#include "helper.h"

namespace delfols {
	using namespace System;
	using namespace System::Windows::Forms;

	void ShowErrorMessage(Form^ win, String^ s)
	{
		Ambiesoft::CenteredMessageBox::Show(win,
			s,
			Application::ProductName,
			MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	void ShowErrorMessage(Exception^ ex)
	{
		ShowErrorMessage(nullptr, ex->Message);
	}
	void ShowErrorMessage(Form^ win, Exception^ ex)
	{
		ShowErrorMessage(win, ex->Message);
	}



}


