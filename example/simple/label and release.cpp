  #include<stdio.h>
  #include "easywingui.h" // or <easywingui.h>
 
 using namespace easywingui;easyw c;
   void c1(){
   wchar_t* td =c.getinput_w("id1");MessageBox(NULL,td,L"",MB_ICONEXCLAMATION | MB_YESNO);
 } 
  
 int main(){ 
 
 	c.creatw(L"hellowinTitle",400,400);c.button(L"textinbutton",150,500,100,100,c1);c.inputbox("id1",500,150,100,100,nullptr);
	 c.release();
     c.label(L"left",100,100,100,30,"left");
			    c.label(L"center",100,200,100,30,"center");
			     c.label(L"right",100,300,100,30,"right");
	  c.loopAndStopProcessing();  
 
 	return 0;
 }
