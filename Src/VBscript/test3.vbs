Dim fso
Dim folder
Dim files
Dim filename

Set fso = CreateObject("Scripting.FileSystemObject")
Set folder = fso.GetFolder("g:\Crystal Music\(1998) Tarzan  OST Italiano")
Set files = folder.files

Set objRE = New RegExp
With objRE
	.Pattern = "([\d]+)(?:[\. ]?)[.]+"
	.Global = False
End With

For Each fileIdx In files
  If (inStr(fileIdx.Name, ".mpc")) Then
	Set Matches = objRE.Execute(fileIdx.Name)
'	s = ""
'	For Each Match in Matches
'		s = s & Match.Value
'	Next
	s = Matches(0)
	Wscript.Echo s
  End If
Next
