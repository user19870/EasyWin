
# easywin
 a simple abstraction of windows.h
# install
**set the folder put easywin.h in devc++ like \......\w\include or something in vscode setting**
---
 **example**
``` 
  #include<stdio.h>
  #include "easywin.h"
 
 using namespace easywin;easyw c;
   void c1(){
   wchar_t* td =c.getinput_w("id1");MessageBox(NULL,td,L"",MB_ICONEXCLAMATION | MB_YESNO);
 } 
 void c2(){
   wchar_t* td =c.getinput_w("id2");MessageBox(NULL,td,L"",MB_ICONEXCLAMATION | MB_YESNO);
 } 
 int main(){ 
 
 	c.creatw(L"hellowinTitle",400,400);c.button(L"textinbutton",150,500,100,100,c1);c.inputbox("id1",500,150,100,100,nullptr);
	 c.button(L"textinbutton",1500,500,100,100,c2);c.inputbox("id2",500,300,100,100,nullptr);c.loop();  
 
 	return 0;
 }
```
# 安裝
**在dev c++設定放easywin.h的目錄如\....\w\include 或在vscode的類似設定**
---
**範例**
```
  #include<stdio.h>
  #include "easywin.h"
 
 using namespace easywin;easyw c;
   void c1(){
   wchar_t* td =c.getinput_w("id1");MessageBox(NULL,td,L"",MB_ICONEXCLAMATION | MB_YESNO);
 } 
 void c2(){
   wchar_t* td =c.getinput_w("id2");MessageBox(NULL,td,L"",MB_ICONEXCLAMATION | MB_YESNO);
 } 
 int main(){ 
 
 	c.creatw(L"你好",400,400);c.button(L"按鈕",150,500,100,100,c1);c.inputbox("id1",500,150,100,100,nullptr);
	 c.button(L"按鈕",1500,500,100,100,c2);c.inputbox("id2",500,300,100,100,nullptr);c.loop();  
 
 	return 0;
 }
```
