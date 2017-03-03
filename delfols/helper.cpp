#include "stdafx.h"
#include "helper.h"

namespace delfols {
	using namespace System;
	using namespace System::Windows::Forms;

	void ShowErrorMessage(String^ s)
	{
		MessageBox::Show(s,
			Application::ProductName,
			MessageBoxButtons::OK,
			MessageBoxIcon::Error);
	}
	void ShowErrorMessage(Exception^ ex)
	{
		ShowErrorMessage(ex->Message);
	}



}


