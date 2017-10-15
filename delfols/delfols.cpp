
#include "stdafx.h"
#include "FormMain.h"

using namespace delfols;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	Application::Run(gcnew FormMain());
	return 0;
}
