
#include "noStdafxHelper.h"

namespace delfols {
	using namespace System;
	using namespace System::Windows::Forms;

	String^ myGetEnvironmentVariable(String^ envval)
	{
		return System::Environment::GetEnvironmentVariable(envval);
	}



}


