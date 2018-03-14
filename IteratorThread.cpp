//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "IteratorThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall IteratorThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall IteratorThread::IteratorThread(WCHAR *filePath, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;

	// ������� �������� �������
}
//---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute()
{
	// ���������� ������ ��������
	int clusterSize = 4096;
	BYTE *dataBuffer = new BYTE[clusterSize];
	MySearchThread = new SearchThread(dataBuffer,clusterSize,false);

	// ������� ��������� �����
	for(int i = 0; i<10000; i++)
	{
		// ������������� ������ � ������
		//BufferAccessCS->Enter();

		// ������� ������ � ��������� �����
		Sleep(50);

		// �������������� ������ � ������
		//BufferAccessCS->Leave();

		// ��������� ���� ���������� ������
		MySearchThread->BufferReadyEvent->SetEvent();



		// ������� ��������� ����������� ������
		while(MySearchThread->BufferCopiedEvent->WaitFor(WaitDelayMs) != wrSignaled)
		{
		}

		MySearchThread->BufferCopiedEvent->ResetEvent();
	}

	// ��������� �����
	MySearchThread->Terminate();

	delete[] dataBuffer;
}
//---------------------------------------------------------------------------