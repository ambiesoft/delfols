#pragma once

namespace delfols {
	using namespace System;
	using namespace System::Windows::Forms;

	void ShowErrorMessage(Form^ win, String^ s);
	void ShowErrorMessage(Exception^ ex);
	void ShowErrorMessage(Form^ win, Exception^ ex);
}