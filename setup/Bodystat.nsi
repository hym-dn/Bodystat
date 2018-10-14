; 该脚本使用 HM VNISEdit 脚本编辑器向导产生

; 安装程序初始定义常量
!define PRODUCT_NAME "Bodystat"
!define PRODUCT_VERSION "1.0.0.1"
!define PRODUCT_PUBLISHER "yameng_he"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 许可协议页面
;!insertmacro MUI_PAGE_LICENSE "..\..\..\path\to\licence\YourSoftwareLicence.txt"
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "D:\Bodystat"
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File /r "bin\*.*"
SectionEnd

Section -AdditionalIcons
  CreateDirectory "$SMPROGRAMS\Bodystat"
  CreateShortCut "$SMPROGRAMS\Bodystat\Uninstall.lnk" "$INSTDIR\uninst.exe"
  CreateShortCut "$DESKTOP\Bodystat.lnk" "$INSTDIR\Bodystat.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Section Install
   System::Call 'msi::MsiQueryProductState(t"{6B66663C-055F-3A2E-A09D-168840A82362}")i.R0'
   IntCmp $R0 5 INSTALLSTATE_DEFAULT STATE_OTHER
	 STATE_OTHER:
	 IntCmp $R0 1 INSTALLSTATE_ADVERTISED INSTALLSTATE_ABSENT INSTALLSTATE_UNKNOWN
	 INSTALLSTATE_UNKNOWN:
  	DetailPrint "安装状态：该产品未被广告或安装"
  	ExecWait '"$INSTDIR\vc_redist.x64.exe" /q'
    Goto Done
	 INSTALLSTATE_ADVERTISED:
    DetailPrint "安装状态：该产品已广告但未安装"
    ExecWait '"$INSTDIR\vc_redist.x64.exe" /q'
    Goto Done
	 INSTALLSTATE_ABSENT:
    DetailPrint "安装状态：该产品为不同的用户安装"
    ExecWait '"$INSTDIR\vc_redist.x64.exe" /q'
    Goto Done
	 INSTALLSTATE_DEFAULT:
    DetailPrint "安装状态：该产品已为当前用户安装"
  done:
SectionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
  Delete "$INSTDIR\uninst.exe"

  Delete "$SMPROGRAMS\Bodystat\Uninstall.lnk"
  
  Delete "$DESKTOP\Bodystat.lnk"

  RMDir "$SMPROGRAMS\Bodystat"

  RMDir /r "$INSTDIR\temp"
  RMDir /r "$INSTDIR\sqldrivers"
  RMDir /r "$INSTDIR\report"
  RMDir /r "$INSTDIR\platforms"

  RMDir /r "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  SetAutoClose true
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从您的计算机移除。"
FunctionEnd
