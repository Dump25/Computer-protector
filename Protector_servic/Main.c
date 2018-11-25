/*#include <Windows.h>
#include <Winsvc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "MyString.h"
//#include "global.h"
//#include "Debug.h"

#pragma warning(disable : 4996)

SERVICE_STATUS m_ServiceStatus;
SERVICE_STATUS_HANDLE m_ServiceStatusHandle;
int bRunning = 1;
void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);
void WINAPI ServiceCtrlHandler(DWORD Opcode);
int InstallService();
int StartingService();
int StoppingService();
int DeleteingService();

int main(int argc, char* argv[])
{
	bRunning = 1;
	if (argc>1)
	{
		if (strcmp(argv[1], "-i") == 0)
		{
			if (InstallService() == 0)
				printf("\n\nService Installed Sucessfully\n");
			else
				printf("\n\nError Installing Service\n");
		}
		if (strcmp(argv[1], "-d") == 0)
		{
			if (DeleteingService() == 0)
				printf("\n\nService UnInstalled Sucessfully\n");
			else
				printf("\n\nError UnInstalling Service\n");
		}
		if (strcmp(argv[1], "-start") == 0)
		{
			if (StartingService() == 0)
				printf("\n\nService Start Sucessfully\n");
			else
				printf("\n\nError Start Service\n");
		}
		if (strcmp(argv[1], "-stop") == 0)
		{
			if (StoppingService() == 0)
				printf("\n\nService Stop Sucessfully\n");
			else
				printf("\n\nError Stop Service\n");
		}
		else
		{
			printf("\n\nUnknown Switch Usage\n\nFor Install use services.exe -i\
				\n\nFor UnInstall use services.exe - d\
				\n\nFor Start use services.exe - start\
				\n\nFor Stop use services.exe - stop");
		}
	}
	else
	{
		SERVICE_TABLE_ENTRY DispatchTable[] =
		{ { "Service1",ServiceMain },{ NULL,NULL } };
		StartServiceCtrlDispatcher(DispatchTable);
	}
	return 0;
}

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
	m_ServiceStatus.dwServiceType = SERVICE_WIN32;
	m_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	m_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	m_ServiceStatus.dwWin32ExitCode = 0;
	m_ServiceStatus.dwServiceSpecificExitCode = 0;
	m_ServiceStatus.dwCheckPoint = 0;
	m_ServiceStatus.dwWaitHint = 0;

	m_ServiceStatusHandle = RegisterServiceCtrlHandler("Service1", ServiceCtrlHandler);
	if (m_ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0)
	{
		return;
	}
	m_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	m_ServiceStatus.dwCheckPoint = 0;
	m_ServiceStatus.dwWaitHint = 0;
	if (!SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus))
	{

	}


	bRunning = 1;
	//MyCode();

	//initDbg();
	//scFilePrint("hi all.");
	//cleanDbg();
	FILE* file_ptr = fopen("amid.txt", "w");
	fclose(file_ptr);

	///while (bRunning)
	///{
	///
	///	Sleep(5000);
	///	//Place Your Code for processing here....
	///}
	return;
}

void WINAPI ServiceCtrlHandler(DWORD Opcode)
{
	switch (Opcode)
	{
	case SERVICE_CONTROL_PAUSE:
		m_ServiceStatus.dwCurrentState = SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE:
		m_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		break;
	case SERVICE_CONTROL_STOP:
		m_ServiceStatus.dwWin32ExitCode = 0;
		m_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		m_ServiceStatus.dwCheckPoint = 0;
		m_ServiceStatus.dwWaitHint = 0;

		SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus);
		bRunning = 0;
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	}
	return;
}

int InstallService()
{
	char strDir[1024];

	//_memset(strDir, '\0', 1024);

	SC_HANDLE schSCManager, schService;
	GetCurrentDirectory(1024, strDir);
	///strcat_s(strDir, strlen("\\Amid_Protector_service.exe"), "\\Amid_Protector_service.exe");
	strcat(strDir, "\\Amid_Protector_service.exe");
	//_strCCat(strDir, "\\Amid_Protector_service.exe");

	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (schSCManager == NULL)
	{
		return 1;
	}

	LPCTSTR lpszBinaryPathName = strDir;

	schService = CreateService(schSCManager, "Service1",
		"The Display Name Needed", // service name to display
		SERVICE_ALL_ACCESS, // desired access 
		SERVICE_WIN32_OWN_PROCESS, // service type 
		SERVICE_DEMAND_START, // start type 
		SERVICE_ERROR_NORMAL, // error control type 
		lpszBinaryPathName, // service's binary 
		NULL, // no load ordering group 
		NULL, // no tag identifier 
		NULL, // no dependencies
		NULL, // LocalSystem account
		NULL); // no password

	if (schService == NULL)
		return 1;

	CloseServiceHandle(schService);
	return 0;
}

int StartingService()
{
	SERVICE_STATUS_PROCESS ssStatus;
	DWORD dwBytesNeeded;

	SC_HANDLE schSCManager, schService;

	// Get a handle to the SCM database. 
	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // servicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		printf("OpenSCManager failed (%d)\n", GetLastError());
		return 1;
	}

	// Get a handle to the service.
	schService = OpenService(
		schSCManager,         // SCM database 
		"Service1",            // name of service 
		SERVICE_ALL_ACCESS);  // full access 

	if (schService == NULL)
	{
		printf("OpenService failed (%d)\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return 1;
	}

	// Check the status in case the service is not stopped. 

	if (!QueryServiceStatusEx(
		schService,                     // handle to service 
		SC_STATUS_PROCESS_INFO,         // information level
		(LPBYTE)&ssStatus,             // address of structure
		sizeof(SERVICE_STATUS_PROCESS), // size of structure
		&dwBytesNeeded))              // size needed if buffer is too small
	{
		printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return 1;
	}

	// Check if the service is already running. It would be possible 
	// to stop the service here, but for simplicity this example just returns. 

	if (ssStatus.dwCurrentState != SERVICE_STOPPED
		&& ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
	{
		printf("Cannot start the service because it is already running\n");
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return 1;
	}

	// Attempt to start the service.
	if (!StartService(
		schService,  // handle to service 
		0,           // number of arguments 
		NULL))      // no arguments 
	{
		printf("StartService failed (%d)\n", GetLastError());
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return 1;
	}
	else printf("Service start pending...\n");

	// Check the status until the service is no longer start pending. 
	if (!QueryServiceStatusEx(
		schService,       // handle to service 
		SC_STATUS_PROCESS_INFO,    // info level
		(LPBYTE)&ssStatus,         // address of structure
		sizeof(SERVICE_STATUS_PROCESS), // size of structure
		&dwBytesNeeded))              // if buffer too small
	{
		printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return 1;
	}

	// Determine whether the service is running.
	if (ssStatus.dwCurrentState == SERVICE_RUNNING)
	{
		printf("Service started successfully.\n");
	}
	else
	{
		printf("Service not started. \n");
		printf("  Current State: %d\n", ssStatus.dwCurrentState);
		printf("  Exit Code: %d\n", ssStatus.dwWin32ExitCode);
		printf("  Check Point: %d\n", ssStatus.dwCheckPoint);
		printf("  Wait Hint: %d\n", ssStatus.dwWaitHint);
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
	return 0;
}

int StoppingService()
{
	SC_HANDLE schSCManager, schService;

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,            // local computer
		NULL,            // ServicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		printf("OpenSCManager failed (%d)\n", GetLastError());
		return 1;
	}

	// Get a handle to the service.
	schService = OpenService(
		schSCManager,         // SCM database 
		"Service1",            // name of service 
		SERVICE_STOP |
		SERVICE_QUERY_STATUS |
		SERVICE_ENUMERATE_DEPENDENTS);

	if (schService == NULL)
	{
		printf("OpenService failed (%d)\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return 1;
	}

	if (m_ServiceStatus.dwCurrentState == SERVICE_STOPPED)
	{
		printf("Service is already stopped.\n");
		CloseServiceHandle(schSCManager);
		return 1;
	}

	// Send a stop code to the service.
	if (!ControlService(schService, SERVICE_CONTROL_STOP, &m_ServiceStatus))
	{
		printf("ControlService failed (%d)\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return 1;
	}

	printf("Service stopped successfully\n");
	CloseServiceHandle(schSCManager);
	return 0;
}

int DeleteingService()
{
	SC_HANDLE schSCManager;
	SC_HANDLE hService;
	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (schSCManager == NULL)
		return 1;
	hService = OpenService(schSCManager, "Service1", SERVICE_ALL_ACCESS);
	if (hService == NULL)
		return 1;
	if (DeleteService(hService) == 0)
		return 1;
	if (CloseServiceHandle(hService) == 0)
		return 1;

	return 0;
}
*/

#include <Windows.h>
#include <Winsvc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MyCode.h"
#include "global.h"


SERVICE_STATUS_HANDLE g_ServiceStatusHandle;
DWORD g_CurrentState = 0;
BOOL g_SystemShutdown = 0;// false;

void ReportStatus(DWORD state)
{
	g_CurrentState = state;
	SERVICE_STATUS serviceStatus = {
		SERVICE_WIN32_OWN_PROCESS,
		g_CurrentState,
		state == SERVICE_START_PENDING ? 0 : SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,
		NO_ERROR,
		0,
		0,
		0,
	};
	SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
}

void ReportProgressStatus(DWORD state, DWORD checkPoint, DWORD waitHint)
{
	g_CurrentState = state;
	SERVICE_STATUS serviceStatus = {
		SERVICE_WIN32_OWN_PROCESS,
		g_CurrentState,
		state == SERVICE_START_PENDING ? 0 : SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,
		NO_ERROR,
		0,
		checkPoint,
		waitHint,
	};
	SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
}

void ReportErrorStatus(DWORD errorCode)
{
	g_CurrentState = SERVICE_STOPPED;
	SERVICE_STATUS serviceStatus = {
		SERVICE_WIN32_OWN_PROCESS,
		g_CurrentState,
		0,
		ERROR_SERVICE_SPECIFIC_ERROR,
		errorCode,
		0,
		0,
	};
	SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
}

// Handler for service control events.
DWORD WINAPI HandlerEx(DWORD control, DWORD eventType, void *eventData, void *context)
{
	switch (control)
	{
		// Entrie system is shutting down.
	case SERVICE_CONTROL_SHUTDOWN:
		g_SystemShutdown = 1;// true;
		// continue...
		// Service is being stopped.
	case SERVICE_CONTROL_STOP:
		ReportStatus(SERVICE_STOP_PENDING);
		SetEvent(g_StopEvent);
		break;
		// Ignoring all other events, but we must always report service status.
	default:
		ReportStatus(g_CurrentState);
		break;
	}
	return NO_ERROR;
}

// Main function to be executed as entire service code.
void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
	// Must be called at start.
	g_ServiceStatusHandle = RegisterServiceCtrlHandlerEx(TEXT("SERVICE NAME"), &HandlerEx, NULL);

	// Startup code.
	ReportStatus(SERVICE_START_PENDING);
	g_StopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	/* Here initialize service...
	Load configuration, acquire resources etc. */
	ReportStatus(SERVICE_RUNNING);

	/* Main service code
	Loop, do some work, block if nothing to do,
	wait or poll for g_StopEvent... */
	MyCode();


	ReportStatus(SERVICE_STOP_PENDING);
	/* Here finalize service...
	Save all unsaved data etc., but do it quickly.
	If g_SystemShutdown, you can skip freeing memory etc. */
	CloseHandle(g_StopEvent);
	ReportStatus(SERVICE_STOPPED);
}

// Standard console application entry point.
int main(int argc, char **argv)
{
	SERVICE_TABLE_ENTRY serviceTable[] = { { "SERVICE NAME", ServiceMain },{ NULL, NULL } };

	if (StartServiceCtrlDispatcher(serviceTable))
		return 0;
	else if (GetLastError() == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT)
		return -1; // Program not started as a service.
	else
		return -2; // Other error.
}
