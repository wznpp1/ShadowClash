Set objArgs = WScript.Arguments
path = objArgs.Item(0)
gateway = objArgs.Item(1)
option = objArgs.Item(2)

Set objShell = CreateObject("WScript.Shell")

If option = "start" Then
    'set tun device to be the default gateway
    command = "route delete 0.0.0.0 mask 0.0.0.0"
    objShell.Run command,0
    command = "route add 0.0.0.0 mask 0.0.0.0 10.0.0.1 metric 6"
    objShell.Run command,0
    command = "route add " & gateway & " 10.0.2.2 metric 5"
    objShell.Run command,0
    command = ""
Else If option = "stop" Then
    command = "route delete 0.0.0.0 mask 0.0.0.0"
    objShell.Run command,0
    command = "route add 0.0.0.0 mask 0.0.0.0 10.0.2.2 metric 50"
    objShell.Run command,0
    command = "taskkill /f /im tun2socks.exe"
    objShell.Run command,0
End If

