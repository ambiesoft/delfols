#pragma once


namespace delfols {

	using namespace System;

	public ref class LogListView : public System::Windows::Forms::ListView
	{
	public:
		LogListView()
		{
			SetStyle(System::Windows::Forms::ControlStyles::OptimizedDoubleBuffer, true);
			SetStyle(System::Windows::Forms::ControlStyles::AllPaintingInWmPaint, true);
		}
	};

}

