![GitHub stars](https://img.shields.io/github/stars/user19870/EasyWinGui?style=social)
![License](https://img.shields.io/github/license/user19870/EasyWinGui)
# EasyWinGui
 **EasyWinGui: a simple gui library for c++ ---windows only**
## install
set the folder put easywingui.h in devc++ like \......\w\include or something in vscode setting
 
### feature
  - xxx.creatw(L"title",weight,height) >is used to creat a window(only show one window)`
 - xxx.button(L"buttonText",x,y,weight,height,func) > can creat a button and call a void function with no parameter when click the button (y=0 is top,not bottom)
 - xxx.inputbox("id",x,y,weight,height,func) > can creat an inputbox with its own id, func is same as that in button but usually be nullptr 
-  xxx.getinput_w("id") or .getinput_s("id") > is method to get index from an inputbox with specific id and w/s is wchar_t/string (char*)
-  xxx.loop() > without loop() the window will close quickly. It must be put after th last feature because when it is called button/inputbox won't update anymore 

 ### example
``` cpp
  #include<stdio.h>
  #include "easywingui.h"
 
 using namespace easywingui;easyw c;
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

## 安裝
EasyWinGui:簡單的c++ 圖形庫
**在dev c++設定放easywingui.h的目錄如\....\w\include 或在vscode的類似設定**
### 功能
- xxx.creatw(L"title",weight,height) >用於創建視窗(一次只能顯示一個)
 - xxx.button(L"buttonText",x,y,weight,height,func) > 創建按鈕且按下可呼叫無參數void 函數，但被呼叫函數寫func而不是func()
 - xxx.inputbox("id",x,y,weight,height,func) > 創建輸入框並為輸入框設定字串id，func欄位 和button()相同但通常設為nullptr
-  xxx.getinput_w("id") or .getinput_s("id") > 可以從指定id的輸入框獲得寬字串、字串
-  xxx.loop() >有這個才能避免視窗閃退，但呼叫後按鈕、輸入框等物件不能更新或新增

### 範例
```cpp
  #include<stdio.h>
  #include "easywingui.h"
 
 using namespace easywingui;easyw c;
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
