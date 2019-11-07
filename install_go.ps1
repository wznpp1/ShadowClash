$goDistPath = "$env:TEMP\go1.13.3.windows-amd64.zip"
(New-Object Net.WebClient).DownloadFile('https://dl.google.com/go/go1.13.3.windows-amd64.zip', $goDistPath)
7z x $goDistPath -oC:\go1133-x64 | Out-Null
[IO.Directory]::Move('C:\go1133-x64\go', 'C:\go113')
Remove-Item 'C:\go1133-x64' -Recurse -Force
del $goDistPath