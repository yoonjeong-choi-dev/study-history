clear all
clc
close all


level=6;
error_idx = 240;
target = 16;

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
% x=x0:dx:x1;
% y(nsR+1)=1;
% for j1=1:nsR
%     for i1=1:nsR+1
%         y(i1)=y0+dy*j1;
%         
%     end
%     plot(x,y,'k')
% end
% 
% y=y0:dy:y1;
% x(nsR+1)=1;
% for j1=1:nsR
%     for i1=1:nsR+1
%         x(i1)=x0+dx*j1;
%         
%     end
%     plot(x,y,'k')
% end


for t=1:256/target
    
    str_1='CEIP';
    str_2=num2str(level);
    str_3='_';
    str_4=num2str(t*target);
    str_5='.txt';
    str=[str_1 str_2 str_3 str_4 str_5];
    CEIP=load(str);
    nCEIP=size(CEIP,1);
    
    
    for k=1:nCEIP/2
        
        x2(1)=CEIP(k*2-1,1);
        x2(2)=CEIP(k*2,1);
        
        y2(1)=CEIP(k*2-1,2);
        y2(2)=CEIP(k*2,2);
        
        plot(x2,y2,'k-', 'LineWidth', 1)
        
    end
    
end



axis equal;
xlim([-1,1]);
ylim([-1,1]);
xlabel('X');
ylabel('Y');


