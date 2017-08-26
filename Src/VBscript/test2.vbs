Option Explicit

Dim strFile, objFSO, objFile, objFolder
Dim strFileName, intIndex

strFile = "D:\src\vbscript\01 - I'm Just a Fun Loving Woman.mp3"

Set objFSO = CreateObject("Scripting.FileSystemObject")
Set objFile = objFSO.GetFile(strFile)
Set objFolder = objFile.ParentFolder

Wscript.Echo "Name: " & objFile.Name
Wscript.Echo "ParentFolder: " & objFile.ParentFolder
Wscript.Echo "Path: " & objFile.Path
Wscript.Echo "Type: " & objFile.Type
Wscript.Echo "Parent Folder: " & objFolder.Name
Wscript.Echo "Drive: " & objFolder.Drive
Wscript.Echo "Parent Folder Path: " & objFolder.Path
strFileName = objFile.Name
intIndex = InStr(strFileName, ".")
If (intIndex > 0) Then
  Wscript.Echo "File Extension: " & Mid(strFilename, intIndex + 1)
Else
  Wscript.Echo "File Extension: "
End If
