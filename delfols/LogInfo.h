namespace delfols {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref struct LogInfo
	{
		String^ file_;
		String^ result_;
		
		LogInfo(String^ file, String^ result) :file_(file), result_(result)
		{}

		property String^ Filename
		{
			String^ get()
			{
				return file_;
			}
		}
		property String^ Result
		{
			String^ get()
			{
				return result_;
			}
		}
	
	};
}