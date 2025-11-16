 #include "easywingui.h"

 using namespace easywingui;easyw c;  wchar_t wc[64];int a=1;

   void conv(int x){
   	    swprintf_s(wc, 64, L"%d", x);   
   }
   void r(){
   	 conv(a);c.changelabel("1",wc);
   }
 int main(){ 
   
 	c.creatw(L"scrollbar and trackbar",1200,900);c.label("1",L"test",300,500,100,30,"left"); 
	 c.scrollbar(60,50,301,20,"horz");// c.scrollbar(10,10,301,20,"horz");
	 c.scrollbar(10,10,20,301,"vert");  
	  c.trackbar(&a,-999,999,30,30,100,20,"horz"); 
	   
	   while(IsWindow(c.hwnd)){       
	   	c.runMessage(r);Sleep(16);  }
 
 	return 0;
 }