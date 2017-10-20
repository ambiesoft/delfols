
#include "stdafx.h"
#include "FormMain.h"

using namespace delfols;
using namespace Ambiesoft;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// CppUtils::testMessageBox("AAA");

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	Application::Run(gcnew FormMain());
	return 0;
}
