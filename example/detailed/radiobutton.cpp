//#include<stdio.h>
  #include "easywingui.h"

 using namespace easywingui;easyw c; bool r[6];
   void run(){ 
     if(c.radiostate(1)) c.changelabel("g1",L"Group 1: Selected");
	  if(c.radiostate(2)) c.changelabel("g2",L"Group 2: Selected");
}
 
 int main(){ 
 	c.creatw(L" ",400,300);
	 	c.label("g1",L"Group 1:",0,70,200,30,"center");
	c.label("g2",L"Group 2:",0,160,200,30,"center");
	   for(int i=0;i<6;i++){
	    r[i]=(i<3)?c.radiobutton(L"g1",100+(i*100),100,100,30,1,nullptr):c.radiobutton(L"g2",100+(i-3)*100,130,100,30,2,nullptr); 
	   }
	   while(IsWindow(c.hwnd)){       
	   	c.runMessage(run);Sleep(16);  }
 	return 0;
 }
 
