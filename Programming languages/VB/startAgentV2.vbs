Set objShell = WScript.CreateObject("WScript.Shell")
WScript.Sleep 60*1000
strCommand = "cmd /c C:\SecureNOK\SNOK-agent\bin\SNOK-Agent-Release1_2Multithreading.exe > AgentLog.txt"
objShell.Run(strCommand), 0, True