clear all
clc
close all


level=6;
nsR=2^level;

x0=-2;
x1=2;
y0=-2;
y1=2;


dx=(x1-x0)/(2^level);
dy=(y1-y0)/(2^level);


x2(2)=0;
y2(2)=0;

nIP=0;



close

figure
hold on
x=x0:dx:x1;
y(nsR+1)=1;
for j1=1:nsR
    for i1=1:nsR+1
        y(i1)=y0+dy*j1;
        
    end
    plot(x,y,'k')
end

y=y0:dy:y1;
x(nsR+1)=1;
for j1=1:nsR
    for i1=1:nsR+1
        x(i1)=x0+dx*j1;
        
    end
    plot(x,y,'k')
end


str_1='ERROR_CP';
str_1='CP6_2';
str_5='.txt';
str2=[str_1 str_5];
CP=load(str2);
nCP_V=size(CP);
nCP=nCP_V(1);



x_ =  CP(:,1);
y_ = CP(:,2);
   
scatter(x_, y_);
 
 for j=1:nCP
        txt1 = '\bullet \rightarrow ';
        txt2 = num2str(j);
        txt =[txt1 txt2];
        %text(x_(j),y_(j),txt)
 end



xlim([x0 x1])
ylim([y0 y1])
pause(0.2);
    
    
    
  
    
   
    
    
