#pragma once

namespace delfols {
	
	using namespace System;
	
	ref class ThreadParam
	{
		bool dryrun_;
		bool useShell_;
		bool closeOnFinish_;
		System::Collections::Generic::List<String^>^ allToDel_;
	public:
		ThreadParam(bool dryrun, bool useShell, bool closeOnFinish, System::Collections::Generic::List<String^>^ allToDel) :
			dryrun_(dryrun), useShell_(useShell), closeOnFinish_(closeOnFinish), allToDel_(allToDel)
		{}

		property cli::array<String^>^ AllToDel
		{
			cli::array<String^>^ get()
			{
				return allToDel_->ToArray();
			}
		}
		property bool IsDryrun
		{
			bool get()
			{
				return dryrun_;
			}
		}
		property bool IsShellDelete
		{
			bool get()
			{
				return useShell_;
			}
		}
		property bool IsCloseOnFinish
		{
			bool get()
			{
				return closeOnFinish_;
			}
		}
	};

}