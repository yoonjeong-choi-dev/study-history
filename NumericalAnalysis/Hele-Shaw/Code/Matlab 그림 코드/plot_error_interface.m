clear all
clc
close all


level=6;
error_idx = 2;

x0=-2;
x1=2;
y0=-2;
y1=2;

nsR=2^level;
dx=(x1-x0)/(2^level);
dy=(y1-y0)/(2^level);







x2(2)=0;
y2(2)=0;

nIP=0;
for i=error_idx:error_idx
    i
    
    close
    
    figure
    hold all
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
    
    str_1='IP';
    str_2=num2str(level);
    str_3='_';
    str_4=num2str(i);
    str_5='.txt';
    str1=[str_1 str_2 str_3 str_4 str_5];
    IP=load(str1);
    nIP_V=size(IP);
    nIP=nIP_V(1);
    IP(nIP+1,1)=IP(1,1);
    IP(nIP+1,2)=IP(1,2);
    
    str_1='CP';
    str_2=num2str(level);
    str_3='_';
    str_4=num2str(i);
    str_5='.txt';
    str2=[str_1 str_2 str_3 str_4 str_5];
    CP=load(str2);
    nCP_V=size(CP);
    nCP=nCP_V(1);
    CP(nCP+1,1)=CP(1,1);
    CP(nCP+1,2)=CP(1,2);
    
   plot(IP(:,1), IP(:,2),'k-o', CP(:,1), CP(:,2), 'b--', 'LineWidth', 2);
    
    x2(1)=IP(1,1);
    x2(2)=IP(2,1);
    
    y2(1)=IP(1,2);
    y2(2)=IP(2,2);
    
    plot(x2,y2,'r-', 'LineWidth', 3)
    
    x2(1)=CP(1,1);
    x2(2)=CP(2,1);
    
    y2(1)=CP(1,2);
    y2(2)=CP(2,2);
    
    plot(x2,y2,'r-', 'LineWidth', 3)
    
    
    xlim([x0 x1])
    ylim([y0 y1])
    pause(0.2);
    
    for j=1:nCP
        x2(1)=IP(j,1);
        x2(2)=CP(j,1);
        
        y2(1)=IP(j,2);
        y2(2)=CP(j,2);
        plot(x2,y2,'y-', 'LineWidth', 1);
        txt1 = '\bullet \rightarrow ';
        txt2 = num2str(j);
        txt =[txt1 txt2];
        text(x2(2),y2(2),txt)
    end
    
    
    
    if (i>1)
        str_1='CEIP';
        str_2=num2str(level);
        str_3='_';
        str_4=num2str(i);
        str_5='.txt';
        str=[str_1 str_2 str_3 str_4 str_5];
        CEIP=load(str);
        nCEIP=size(CEIP,1);
        
        
        for k=1:nCEIP/2
            
            x2(1)=CEIP(k*2-1,1);
            x2(2)=CEIP(k*2,1);
            
            y2(1)=CEIP(k*2-1,2);
            y2(2)=CEIP(k*2,2);
            
            plot(x2,y2,'b^', 'LineWidth', 3)
            
        end
        x2(1)=CEIP(1,1);
        x2(2)=CEIP(2,1);
        
        y2(1)=CEIP(1,2);
        y2(2)=CEIP(2,2);
        
        %plot(x2,y2,'r-', 'LineWidth', 3)
    end
    
    str_1='Time: ';
    str_2=num2str(i);
    str=[str_1 str_2];
    
    legend(str);
    
    
end