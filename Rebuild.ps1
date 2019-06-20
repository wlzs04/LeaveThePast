Write-Output "开始清除文件"
if(Test-Path .vs)
{
    Remove-Item .vs -recurse -Force
}
if(Test-Path Binaries)
{
    Remove-Item Binaries -recurse
}
if(Test-Path Intermediate)
{
    Remove-Item Intermediate -recurse
}
if(Test-Path Saved)
{
    Remove-Item Saved -recurse
}
if(Test-Path LeaveThePast.sln)
{
    Remove-Item LeaveThePast.sln -recurse
}
Write-Output "文件已清理！"
Write-Output "开始生成文件。"
D:/Unreal/UE_4.22/Engine/Binaries/DotNET/UnrealBuildTool.exe -projectfiles -project="E:/LeaveThePast/LeaveThePast.uproject" -game -rocket -progress
Write-Output "文件已生成！"
Write-Output "点击任意键退出！"